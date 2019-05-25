#include<iostream>
#include<vector>
#include<string>
#include<unistd.h>
#include<sstream>
#include"SDL/SDL.h"
#include"SDL/SDL_ttf.h"
#include"candy.h"

#define limittime 60000
#define delaytime 300000
#define FONT_ADDRESS "CANDY.TTF"
using namespace std;


int main(int argc,char **argv)
{
	stringstream ss;
	string scorestring;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Surface *scoreback =SDL_LoadBMP("scoreback.bmp"),*nomove =SDL_LoadBMP("nomove.bmp"),*textSurface = NULL;
	int m,n;
	prob color;//struct prob 
	get_input(m,n,color);
	SDL_Event event;
	SDL_Rect pos,scorepos,erpos;
	TTF_Font *font = NULL;
	SDL_Color textColor = {255,255,255};
	SDL_SetColorKey(nomove,SDL_SRCCOLORKEY,0xff0000);
	SDL_WM_SetCaption("CANDY CRUSH SAGA",NULL);
	font = TTF_OpenFont(FONT_ADDRESS,30);
	vector<string> row;
	vector<string> temp;
	int score=0,posy1,posx1,posy2,posx2;
	double r,b,g,y,o;
	bool firsclick=false,readytoswap=false,exit = false,showscore=false;	
	srand (time(NULL));
	pos.x=0;
	pos.y=0;
	erpos.x=n*50/2 -100;
	erpos.y=m*50/2 -50;

	row=make_table(m,n);
	change_empty(row,color);
	graphic graph;
	scoreitem scoreimg;
	load_file(graph,scoreimg,m,n);

	if(startgame(graph))
	{
		graph.screen= SDL_SetVideoMode(n*50,m*50,32,SDL_HWSURFACE);
		do
		{
			temp=check_logic(row,row,score,color,graph);
		}
		while(temp!=row);
		score= 0;
		while(!exit)
		{

			while(SDL_GetTicks()<limittime && !exit)
			{
				while (!available_move(row))
				{
					SDL_BlitSurface(nomove,NULL,graph.screen,&erpos);
					SDL_Flip(graph.screen);
					make_cells_zero(row);
					change_empty(row,color);
					usleep(delaytime);//for showing no possible move img
					do
					{
						if (firsclick==false)
							temp=check_logic(row,row,score,color,graph);
					}
					while(temp!=row);
				}
				while(SDL_PollEvent(&event))
				{
					switch(event.type) 
					{
					case SDL_MOUSEBUTTONDOWN:
						if( event.button.button == SDL_BUTTON_LEFT ) 
						{
							if (firsclick==true)
							{
								posx2 = event.button.x; 
								posy2 = event.button.y;
								changXandY(posy2,posx2);
								firsclick=false;
								readytoswap=true;
							}
							else
							{
								posx1 = event.button.x; 
								posy1 = event.button.y;
								changXandY(posx1,posy1);
								show_click(row,posx1,posy1,graph);
								firsclick=true;
							}
						} 
						break;
					case SDL_QUIT:
						exit=true;
					}
				}
				if (firsclick==false)
				{
					show_all(row,graph);
					SDL_Flip(graph.screen);
				}

				if (readytoswap && check_swap(posy1,posx1,posy2,posx2) && firsclick==false)
				{
					swap(row[posy1][posx1],row[posy2][posx2]);
					if (!avail_logic(row))
					{
						show_all(row,graph);
						SDL_Flip(graph.screen);
						usleep(delaytime);
						swap(row[posy1][posx1],row[posy2][posx2]);
					}
					readytoswap=false;
				}
				do
				{
					if (firsclick==false)
						temp=check_logic(row,row,score,color,graph);
				}
				while(temp!=row);
				if (firsclick==false)
				{
					show_all(row,graph);
					SDL_Flip(graph.screen);
				}

			}
			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					exit = true;
			}
			if (showscore==false)
			{
				ss<<score;
				scorestring = ss.str();
				scorepos.x=130;
				scorepos.y=150;
				textSurface = TTF_RenderText_Solid(font,scorestring.c_str(),textColor);
				SDL_Surface *screen = SDL_SetVideoMode(300,342,32,SDL_HWSURFACE);
				SDL_BlitSurface(scoreback,NULL,graph.screen,NULL);
				SDL_BlitSurface(textSurface,NULL,graph.screen,&scorepos);
				logic_score(score,scoreimg,graph);
				SDL_Flip(graph.screen);
				showscore=true;
			}

		}
		//clean up
		cleanup(graph,scoreimg);
		SDL_FreeSurface(nomove);
		SDL_FreeSurface(scoreback);
		SDL_FreeSurface(textSurface);
		TTF_CloseFont( font );
		TTF_Quit();
		SDL_Quit();        	
		return 0;
	}
}
