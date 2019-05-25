#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include"SDL/SDL.h"
#include "graphic.h"
using namespace std;
struct prob
{
	double r;
	double b;
	double g;
	double y;
	double o;
};
void print_all(vector<string> row);
char rand_to_char(prob& color);
int make_rand_num();
vector<string> check_logic(vector<string>& row,vector<string> temp,int& score,prob& color,graphic& graph);
void fill_the_blank(vector<string>& row);
void crush (vector<string>& row,int y,int x,int& score,char axis);
void change_empty(vector<string>& row,prob& color);
vector<string> make_table(int m,int n);
bool available_move(vector<string> row);
bool avail_logic(vector<string> temp);
void make_cells_zero(vector<string>& row);
bool check_swap(int y1,int x1,int y2,int x2);
void get_input(int& m,int& n,prob& color);

