#include "candy.h"
void print_all(vector<string> row)
{
	for (int i=1;i<row.size();i++)
	{
		for (int j=1;j<row[i].size();j++)
		{
			cout<< row[i][j]<<'\t';
		}
		cout<<endl;
	}
}
bool check_swap(int y1,int x1,int y2,int x2)
{
	if (y2==y1-1 && x2==x1)
		return true;
	else if (y2==y1+1 && x2==x1)
		return true;
	else if (y2==y1 && x2==x1+1)
		return true;
	else if (y2==y1 && x2==x1-1)
		return true;
	else 
		return false;
}
void swap (char& from,char& to)
{
	char temp;
	temp = from;
	from=to;
	to= temp;
}
void fill_the_blank(vector<string>& row)
{
	for (int k=0;k<row.size();k++)
	{
		for (int j=row.size()-1;j>1;j--)
		{
			for (int i=1;i<row[j].size();i++)
			{
				if (row[j][i]=='0')
				{
					swap(row[j-1][i],row[j][i]);
				}
			}
		}
	}
}
vector<string> check_logic(vector<string>& row,vector<string> temp,int& score,prob& color,graphic& graph)
{
	for (int j=1;j<temp.size();j++)
	{
		for(int i=2;i<temp[j].size()-1;i++)
		{

			if (temp[j][i]==temp[j][i+1] && temp[j][i]==temp[j][i-1])
			{
				crush(row,j,i,score,'x');	
			}
		}		
	}
	for (int j=2;j<temp.size()-1;j++)
	{
		for(int i=1;i<temp[j].size();i++)
		{

			if (temp[j][i]==temp[j+1][i] && temp[j][i]==temp[j-1][i])
			{
				crush(row,j,i,score,'y');
			}
		}		
	}
	show_all(row,graph);
	SDL_Flip(graph.screen);
	usleep(300000);
	fill_the_blank(row);
	change_empty(row,color);
	return temp;
}
void crush (vector<string>& row,int y,int x,int& score,char axis)

{	
	score=score+10;
	if (axis=='x')
	{
		row[y][x]  ='0';				
		row[y][x-1]='0';				
		row[y][x+1]='0';
	}
	else if (axis =='y')
	{
		row[y][x]  ='0';				
		row[y-1][x]='0';				
		row[y+1][x]='0';
	}

}
char rand_to_char(prob& color)
{
	int rand;
	rand=make_rand_num();
	if (rand>=0 && rand <color.r*100)
		return 'r';
	else if(rand>=color.r*100 && rand <color.r*100 +color.b*100)
		return 'b';
	else if(rand>=color.r*100 +color.b*100 && rand <color.r*100 +color.b*100 +color.g*100)
		return 'g';
	else if(rand>=color.r*100 +color.b*100+color.g*100 && rand <color.r*100 +color.b*100 +color.g*100+color.y*100)
		return 'y';
	else if(rand>=color.r*100 +color.b*100+color.g*100+color.y*100 && rand <color.r*100 +color.b*100 +color.g*100+color.y*100+color.o*100)
		return 'o';
}	
int make_rand_num()
{
	return rand() % 100;
}
void change_empty(vector<string>& row,prob& color)
{
	for (int j=1;j<row.size();j++)
	{
		for (int i=1;i<row[j].size();i++)
		{
			if (row[j][i]=='0')
			{
				row[j][i]=rand_to_char(color);
			}
		}
	}

}
vector<string> make_table(int m,int n)
{
	char in;
	//uncomment this after debug
	//	r=0.2;
	//	b=0.2;
	//	g=0.2;
	//	y=0.2;
	//	o=0.2;
	vector<string> row(m+1);
	//	row[1]=" bogy";
	//	row[2]=" bror";
	//	row[3]=" oygb";
	//	row[4]=" borb";
	for (int j=1;j<row.size();j++)
	{
		row[j]=" ";
		for (int i=1;i<n+1;i++)
		{
			cin >>in;
			row[j]=row[j]+in ;// + '0'
		}
	}
	//change_empty(row,r,b,g,y,o);
	return row;
}
bool avail_logic(vector<string> temp)
{
	for (int j=1;j<temp.size();j++)
	{
		for(int i=2;i<temp[j].size()-1;i++)
		{

			if (temp[j][i]==temp[j][i+1] && temp[j][i]==temp[j][i-1])
			{
				return true;			
			}
		}		
	}
	for (int j=2;j<temp.size()-1;j++)
	{
		for(int i=1;i<temp[j].size();i++)
		{

			if (temp[j][i]==temp[j+1][i] && temp[j][i]==temp[j-1][i])
			{
				return true;
			}
		}		
	}
	return false;

}
bool available_move(vector<string> row)
{
	int i,j;
	for (j=2;j<row.size()-1;j++)
	{
		for (i=2;i<row[j].size()-1;i++)
		{
			swap (row[j][i],row[j+1][i]);
			if (avail_logic(row))
			{
				return true;
			}
			else 
				swap (row[j][i],row[j+1][i]);

			swap (row[j][i],row[j][i+1]);
			if (avail_logic(row))
			{

				return true;
			}
			else
				swap (row[j][i],row[j][i+1]);

			swap (row[j][i],row[j-1][i]);
			if (avail_logic(row))
			{
				return true;
			}
			else
				swap (row[j][i],row[j-1][i]);

			swap (row[j][i],row[j][i-1]);
			if (avail_logic(row))
			{
				return true;
			}
			else
				swap (row[j][i],row[j][i-1]);


		}
	}
	for (j=1;j<row.size();j=j+row.size()-2)//for two top
	{
		for(i=1;i<row[j].size();i++)
		{
			swap(row[j][i],row[j][i+1]);
			if (avail_logic(row))
			{
				return true;
			}
			else
				swap (row[j][i],row[j][i+1]);
		}
	}
	for (j=1;j<row.size()-1;j++)//for two side
	{
		for(i=1;i<row[j].size();i=i+row[j].size()-2)
		{
			swap(row[j][i],row[j+1][i]);
			if (avail_logic(row))
			{
				return true;
			}
			else
				swap (row[j][i],row[j+1][i]);
		}
	}
	return false;
}
void make_cells_zero(vector<string>& row)
{
	for (int j=1;j<row.size();j++)
	{
		for (int i=1;i<row[j].size();i++)
		{
			row[j][i]='0';
		}
	}
}
void get_input(int& m,int& n,prob& color)
{
	cin >>m>>n;
	cin >>color.r>>color.b>>color.g>>color.y>>color.o;

}


