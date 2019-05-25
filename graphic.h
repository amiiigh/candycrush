#include"SDL/SDL.h"
#include<iostream>
#include<vector>
#include<string>
#include<unistd.h>
using namespace std;
struct graphic
{
	SDL_Surface *screen;
	SDL_Surface *red;
	SDL_Surface *blue;
	SDL_Surface *green;
	SDL_Surface *yellow;
	SDL_Surface *orange;
	SDL_Surface *empty;
	SDL_Surface *redclick;
	SDL_Surface *blueclick;
	SDL_Surface *greenclick;
	SDL_Surface *yellowclick;
	SDL_Surface *orangeclick;
	SDL_Surface *startmenu;
	SDL_Surface *startbutt;
};
struct scoreitem
{
	SDL_Surface *bronz;
	SDL_Surface *silver;
	SDL_Surface *gold;
	SDL_Surface *girlupset;
};
void show_all(vector<string> row,graphic& graph);
void changXandY(int& y,int& x);
void logic_score(int score,scoreitem& scoreimg,graphic& graph);
void show_click(vector<string> row,int i,int j,graphic& graph);
void load_file(graphic& graph,scoreitem& scoreimg,int m,int n);
void cleanup(graphic& graph,scoreitem& scoreimg);
bool startgame(graphic& graph);

