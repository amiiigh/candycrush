#include "graphic.h"
bool startgame(graphic& graph)
{
	SDL_Rect pos;
	pos.x=79;
	pos.y=300;
	graph.screen= SDL_SetVideoMode(300,533,32,SDL_HWSURFACE);
	SDL_BlitSurface(graph.startmenu,NULL,graph.screen,NULL);
	SDL_BlitSurface(graph.startbutt,NULL,graph.screen,&pos);
	SDL_Event event;
	bool exit=false;
	SDL_Flip(graph.screen);
	while (!exit)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
			case SDL_MOUSEBUTTONDOWN:
				if( event.button.button == SDL_BUTTON_LEFT ) 
				{
					if((event.button.x > 79 && event.button.x <222)&& (event.button.y > 300 && event.button.y < 358 ))
					{
						pos.y=pos.y + 5;
						SDL_BlitSurface(graph.startmenu,NULL,graph.screen,NULL);
						SDL_BlitSurface(graph.startbutt,NULL,graph.screen,&pos);
						SDL_Flip(graph.screen);
						usleep(500000);
						return true;
					}
				} 
				break;
			case SDL_QUIT:
				exit=true;
			}
		}
	}
}
void load_file(graphic& graph,scoreitem& scoreimg,int m,int n)
{
	graph.screen= SDL_SetVideoMode(n*50,m*50,32,SDL_HWSURFACE);
	graph.red= SDL_LoadBMP("red.bmp");
	graph.yellow = SDL_LoadBMP("yellow.bmp");
	graph.orange = SDL_LoadBMP("orange.bmp");
	graph.green = SDL_LoadBMP("green.bmp");
	graph.blue = SDL_LoadBMP("blue.bmp");
	graph.empty =SDL_LoadBMP("empty.bmp");
	graph.redclick = SDL_LoadBMP("redglow.bmp");
	graph.blueclick = SDL_LoadBMP("blueglow.bmp");
	graph.greenclick = SDL_LoadBMP("greenglow.bmp");
	graph.orangeclick = SDL_LoadBMP("orangeglow.bmp");
	graph.yellowclick = SDL_LoadBMP("yellowglow.bmp");
	graph.startmenu = SDL_LoadBMP("startmenu.bmp");
	graph.startbutt = SDL_LoadBMP("playbutt.bmp");

	scoreimg.bronz=SDL_LoadBMP("bronzstar.bmp");
	scoreimg.silver=SDL_LoadBMP("silverstar.bmp");
	scoreimg.gold=SDL_LoadBMP("goldstar.bmp");
	scoreimg.girlupset=SDL_LoadBMP("girlupset.bmp");
}
void show_all(vector<string> row,graphic& graph)
{
	SDL_Rect pos;
	pos.x=0;
	pos.y=0;
	for (int j=1;j<row.size();j++)
	{
		pos.x=0;
		for(int i=1;i<row[j].size();i++)
		{
			if ( row [j][i]=='r')
			{
				SDL_BlitSurface(graph.red,NULL,graph.screen,&pos);
			}
			else if ( row [j][i]=='b')
			{
				SDL_BlitSurface(graph.blue,NULL,graph.screen,&pos);
			}
			else if ( row [j][i]=='g')
			{
				SDL_BlitSurface(graph.green,NULL,graph.screen,&pos);
			}
			else if ( row [j][i]=='y')
			{
				SDL_BlitSurface(graph.yellow,NULL,graph.screen,&pos);
			}
			else if ( row [j][i]=='o')
			{
				SDL_BlitSurface(graph.orange,NULL,graph.screen,&pos);
			}
			else 
				SDL_BlitSurface(graph.empty,NULL,graph.screen,&pos);
			pos.x=pos.x + 50;
		}
		pos.y=pos.y +50;
	}
}
void changXandY(int& y,int& x)
{
	int position;
	position=x /100; 
	if ((x % 100) < 50)
		x=position*100 + 50;
	else if((x % 100) > 50)
	{
		x=position*100 + 100;
	}
	position=y/100;
	if ((y % 100 ) < 50)
		y=position*100 + 50;
	else if((y % 100) > 50)
	{
		y=position*100 + 100;
	}
	y=y/50;
	x=x/50;
}
void logic_score(int score,scoreitem& scoreimg,graphic& graph)
{
	SDL_Rect starbronz,starsilver,stargold,girl;
	starbronz.y=51;
	starbronz.x=34;
	starsilver.y=44;
	starsilver.x=115;
	stargold.y=52;
	stargold.x=198;
	girl.y=180;
	girl.x=90;
	if (score >=300 && score <=500)
	{
		SDL_BlitSurface(scoreimg.bronz,NULL,graph.screen,&starbronz);
		SDL_BlitSurface(scoreimg.girlupset,NULL,graph.screen,&girl);
	}
	else if (score >500 && score <= 800 )
	{
		SDL_BlitSurface(scoreimg.bronz,NULL,graph.screen,&starbronz);
		SDL_BlitSurface(scoreimg.silver,NULL,graph.screen,&starsilver);
	}
	else if (score >800 )
	{
		SDL_BlitSurface(scoreimg.bronz,NULL,graph.screen,&starbronz);
		SDL_BlitSurface(scoreimg.silver,NULL,graph.screen,&starsilver);
		SDL_BlitSurface(scoreimg.gold,NULL,graph.screen,&stargold);
	}
	else
		SDL_BlitSurface(scoreimg.girlupset,NULL,graph.screen,&girl);
}
void show_click(vector<string> row,int i,int j,graphic& graph)
{
	SDL_Rect pos;
	pos.x=(i-1)*50;
	pos.y=(j-1)*50;
	if ( row [j][i]=='r')
	{
		SDL_BlitSurface(graph.redclick,NULL,graph.screen,&pos);
	}
	else if ( row [j][i]=='b')
	{
		SDL_BlitSurface(graph.blueclick,NULL,graph.screen,&pos);
	}
	else if ( row [j][i]=='g')
	{
		SDL_BlitSurface(graph.greenclick,NULL,graph.screen,&pos);
	}
	else if ( row [j][i]=='y')
	{
		SDL_BlitSurface(graph.yellowclick,NULL,graph.screen,&pos);
	}
	else if ( row [j][i]=='o')
	{
		SDL_BlitSurface(graph.orangeclick,NULL,graph.screen,&pos);
	}
	SDL_Flip(graph.screen);
}
void cleanup(graphic& graph,scoreitem& scoreimg)
{
	SDL_FreeSurface(graph.red);
	SDL_FreeSurface(graph.blue);
	SDL_FreeSurface(graph.green);
	SDL_FreeSurface(graph.yellow);
	SDL_FreeSurface(graph.orange);
	SDL_FreeSurface(graph.redclick);
	SDL_FreeSurface(graph.blueclick);
	SDL_FreeSurface(graph.greenclick);
	SDL_FreeSurface(graph.yellowclick);
	SDL_FreeSurface(graph.orangeclick);
	SDL_FreeSurface(graph.empty);
	SDL_FreeSurface(graph.screen);

	SDL_FreeSurface(scoreimg.bronz);
	SDL_FreeSurface(scoreimg.silver);
	SDL_FreeSurface(scoreimg.gold);
	SDL_FreeSurface(scoreimg.girlupset);
}
