#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include "denizumut_eser_denizumut_hw1_Stack.h"
using namespace std;

//Deniz Umut Eser

struct cell
{
	int x = 0, y = 0;
	int l = 1, r = 1, u = 1, d = 1;
	bool visited = false;

	cell()
	{}
};

void writeMaze(vector<vector<cell>>& maze, int k, int m, int n)
{
	//writing maze wall info to a file
	ofstream output;
	string filename = "maze_" + to_string(k) + ".txt";
	output.open(filename);
	output << m << " " << n << endl;
	for (int y = 0; y < m; y++)
	{
		for (int x = 0; x < n; x++)
		{
			output << "x=" << maze[x][y].x << " ";
			output << "y=" << maze[x][y].y << " ";
			output << "l=" << maze[x][y].l << " ";
			output << "r=" << maze[x][y].r << " ";
			output << "u=" << maze[x][y].u << " ";
			output << "d=" << maze[x][y].d << " ";
			output << endl;
		}
	}
	output.close();
}

bool randomWall(vector<vector<cell>> & maze, cell & currentCell, cell & nextCell, int m, int n, string id="smash")
{
	//multi purpose random wall chooser among all possible directions for both maze generation and path finding
	vector<cell> valid_sides; //for choosing path
	vector<char> valid_directions; //for going in the direction
	int x = currentCell.x, y = currentCell.y;
	//left
	if (x - 1 >= 0) //if not out of maze boundary
		if (!maze[x-1][y].visited) //if not visited
		{
			if ((id=="path" && currentCell.l == 0) || (id=="smash")) //for path finding checks if there is a wall or not
			{
				valid_sides.push_back(maze[x - 1][y]);
				valid_directions.push_back('l');
			}			
		}
	//right
	if (x + 1 < n)
		if (!maze[x+1][y].visited)
		{
			if ((id == "path" && currentCell.r == 0) || (id == "smash"))
			{
				valid_sides.push_back(maze[x + 1][y]);
				valid_directions.push_back('r');
			}
		}
	//up
	if (y + 1 < m)
		if (!maze[x][y+1].visited)
		{
			if ((id == "path" && currentCell.u == 0) || (id == "smash"))
			{
				valid_sides.push_back(maze[x][y+1]);
				valid_directions.push_back('u');
			}
		}
	//down
	if (y - 1 >= 0)
		if (!maze[x][y-1].visited)
		{
			if ((id == "path" && currentCell.d == 0) || (id == "smash"))
			{
				valid_sides.push_back(maze[x][y-1]);
				valid_directions.push_back('d');
			}
		}
	
	int num_valid_walls = valid_sides.size();

	//no possible wall return
	if (num_valid_walls == 0)
		return false;
	
	//random
	int rando = (rand() % num_valid_walls);
	nextCell = valid_sides[rando]; //chose one side from valid sides

	//change current and next cells wall information
	if (valid_directions[rando] == 'l') //move left
	{
		currentCell.l = 0;
		nextCell.r = 0;
	}
	else if (valid_directions[rando] == 'r') //move right
	{
		currentCell.r = 0;
		nextCell.l = 0;
	}
	else if (valid_directions[rando] == 'u') //move up
	{
		currentCell.u = 0;
		nextCell.d = 0;
	}	
	else if (valid_directions[rando] == 'd') //move down
	{
		currentCell.d = 0;
		nextCell.u = 0;
	}
	nextCell.visited = true;

	return true;
}

void smashWalls(vector<vector<cell>> & maze, int m,  int n)
{
	//from given all walled maze, produce uniquely pathed maze
	cell currentCell = maze[0][0];
	cell nextCell;
	bool found_wall;
	Stack<cell> myStack; //create an empty stack
	currentCell.visited = true;
	myStack.push(currentCell); //push (0,0) to stack
	while (!myStack.isEmpty()) //if there is no cell left to go, finish
	{
		//break random wall from initial stack
		found_wall = randomWall(maze, currentCell, nextCell, m, n);
		maze[currentCell.x][currentCell.y] = currentCell;
		maze[nextCell.x][nextCell.y] = nextCell;

		if (found_wall)
		{
			// add next cell to stack, next cell becomes current cell
			currentCell = maze[nextCell.x][nextCell.y];
			myStack.push(nextCell);
		}
		else
		{
			//if no wall found to be smashed, step back by poping recent cell from stack
			myStack.pop();
			if(!myStack.isEmpty())
				currentCell = maze[myStack.top().x][myStack.top().y];
		}
	}
}

void generateMaze(int k, int m, int n)
{
	//generate maze with all walls
	vector<vector<cell>> maze(n, vector<cell> (m));
	for (int x = 0; x < maze.size(); x++)
	{
		for (int y = 0; y < maze[x].size(); y++)
		{
			maze[x][y].x = x;
			maze[x][y].y = y;
		}	
	}
	smashWalls(maze, m, n); //smash walls of the generated all walled maze
	writeMaze(maze, k, m, n); //write maze wall information to txt file
}

vector<vector<cell>> readMaze(int mazeID)
{
	int m, n; //maze dimensions
	string x_, y_, l_, r_, u_, d_; //for taking inputs
	string filename = "maze_" + to_string(mazeID) + ".txt";
	ifstream input;
	input.open(filename); //read file
	input >> m >> n;
	vector<vector<cell>> maze(n, vector<cell>(m)); //create empty maze
	
	for (int i = 0; i < (m*n); i++)
	{
		input >> x_ >> y_ >> l_ >> r_ >> u_ >> d_;
		//populate the maze
		maze[stoi(x_.substr(2))][stoi(y_.substr(2))].x = stoi(x_.substr(2));
		maze[stoi(x_.substr(2))][stoi(y_.substr(2))].y = stoi(y_.substr(2));
		maze[stoi(x_.substr(2))][stoi(y_.substr(2))].l = stoi(l_.substr(2));
		maze[stoi(x_.substr(2))][stoi(y_.substr(2))].r = stoi(r_.substr(2));
		maze[stoi(x_.substr(2))][stoi(y_.substr(2))].u = stoi(u_.substr(2));
		maze[stoi(x_.substr(2))][stoi(y_.substr(2))].d = stoi(d_.substr(2));
	}
	return maze;
}

void findPath(int mazeID, int entryX, int entryY, int exitX, int exitY, int m, int n)
{
	//find unique path from starting point to exit point by going in random directions and not visiting same cell again unless backtracking
	vector<vector<cell>> maze = readMaze(mazeID);
	cell currentCell = maze[entryX][entryY];
	cell nextCell;
	bool has_path = true;

	//stack for reversing myStack
	Stack<cell> temp;

	//for writing the path
	ofstream output;
	string filename = "maze_" + to_string(mazeID) + "_path_"+ to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + ".txt";
	output.open(filename);
	
	Stack<cell> myStack; //create empty stack
	currentCell.visited = true;
	myStack.push(currentCell); //add starting cell

	//move until exit is found
	while ((currentCell.x != exitX) || (currentCell.y != exitY))
	{
		//chose next cell
		has_path = randomWall(maze, currentCell, nextCell, m, n, "path");
		maze[currentCell.x][currentCell.y] = currentCell;
		maze[nextCell.x][nextCell.y] = nextCell;
		if (has_path)
		{
			//add next cell to stack
			currentCell = maze[nextCell.x][nextCell.y];
			myStack.push(nextCell);
		}
		else
		{
			//back track one cell
			myStack.pop();
		}	
		//get current cell
		currentCell = maze[myStack.top().x][myStack.top().y];

	}
	while (!myStack.isEmpty())
	{
		//cout << myStack.top().x << " " << myStack.top().y << endl;
		temp.push(myStack.top());
		myStack.pop();
	}
	while (!temp.isEmpty())
	{
		output << temp.top().x << " " << temp.top().y << endl;
		temp.pop();
	}
	output.close();
}

int main()
{
	///PHASE ONE///
	srand(time(0)); //random coefficent to be used in randomWall()
	//take inputs for k, m, n
	int k, m, n;
	cout << "Enter the number of mazes: ";
	cin >> k;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> m >> n;

	//generate k number of mazes with size mxn and write maze into a file
	for (int i = 1; i <= k; i++)
	{
		generateMaze(i, m, n);
	}
	cout << "All mazes are generated." << endl << endl;

	///PHASE TWO///
	//take inputs for mazeID, entryX, entryY, exitX, exitY
	int mazeID, entryX, entryY, exitX, exitY;
	cout << "Enter a maze ID between 1 to " << k << " inclusive to find a path: ";
	cin >> mazeID;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;

	//find unique maze path, write path into a file
	findPath(mazeID, entryX, entryY, exitX, exitY, m, n);

	//no maze runners were harmed in the creation of this maze of a code.
	return 0;
}
