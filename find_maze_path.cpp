#include <iostream>
#include <vector>
using namespace std;
short maze[8][8]{
	{0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 0, 1, 1, 0, 1},
	{0, 0, 0, 1, 0, 0, 0, 1},
	{0, 1, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 1, 1},
	{0, 1, 0, 0, 0, 1, 0, 1},
	{0, 0, 0, 1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0, 1, 0, 2}
};
bool find_maze_path(int x, int y){
	if(maze[y][x] == 2) 
	{
		cout << "x: " << x << ", y: " << y << endl;
		return true;
	}
	else if(x < 0 || x > 7 || y < 0 || y > 7 || maze[y][x])
		return false;
	else{
		cout << "x: " << x << ", y: " << y << endl;
		maze[y][x] = 1;
		if( find_maze_path(x+1, y) || 
			find_maze_path(x-1, y) || 
			find_maze_path(x, y+1) || 
			find_maze_path(x, y-1)
		)
			return true;
		else return false;
	}
}

int main()
{
	cout << find_maze_path(0,0) << endl;
	return 0;
}
