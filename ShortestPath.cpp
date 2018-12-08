#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Graph
{
	
public:
	Graph(int, int);
	void addRoute(int, int, int);
	bool isRoute(int, int);
	int adjMatrix[100][100];
	int weightMatrix[100][100];
	string colors[100];
	void calcShortestRoutes(void);
	int shortestRoute(string, string);
	int returnStation(string);
	int routes;
	int stations;
};

Graph::Graph(int routes, int stations)
{
	routes = routes;
	stations = stations;

	for (int i = 0; i < 100; i++)
	{
		colors[i] = "";
		for (int j = 0; j < 100; j++)
		{
			adjMatrix[i][j] = INT16_MAX;
		}
	}
}

void Graph::addRoute(int from, int to, int weight)
{
	adjMatrix[from][to] = weight;
}

void Graph::calcShortestRoutes(void)
{
	int i, j, k;
	for (k = 0; k < 100; k++)
	{
		for (i = 0; i < 100; i++)
		{
			for (j = 0; j < 100; j++)
			{
				if (adjMatrix[i][k] != INT16_MAX &&  adjMatrix[k][j] != INT16_MAX && i != j)
				{
					if ((adjMatrix[i][k] + adjMatrix[k][j] < adjMatrix[i][j]) || (adjMatrix[i][j] == 0))
					{
						adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];
					}
				}
			}
		}
	}
}

int Graph::shortestRoute(string src, string dst)
{
	return adjMatrix[returnStation(src)][returnStation(dst)];
}

int Graph::returnStation(string color)
{
	int i = 0;
	for (; i < 100; i++)
	{
		if (colors[i] == color)
		{
        	return i;
			break;
		}
	}
	return -1;
}

bool Graph::isRoute(int from, int to)
{
	bool isRoute = false;
	queue<int> q;
	bool visited[100][100] = { false };

	int weight = 0;
	for (int i = 0; i < 100; i++)
	{
		if (adjMatrix[from][to] != INT16_MAX)
		{
			
			isRoute = true;
			break;
		}
		else
		{
			if (adjMatrix[from][i] != INT16_MAX)
			{
				q.push(i);
			}
		}
	}

	while (!q.empty() && isRoute == false)
	{
		for (int i = 0; i < 100; i++)
		{
			if (adjMatrix[q.front()][to] != INT16_MAX)
			{
				isRoute = true;
				break;
			}
			else if (visited[q.front()][i] == false && adjMatrix[q.front()][i] != INT16_MAX)
			{
				q.push(i);
				visited[q.front()][i] = true;
			}
		}
		q.pop();
	}

	return isRoute;
}


int main()
{
	ifstream myFile("sample.txt");
	ifstream colorFile("colors.txt");

	int n = 2;
	int routes = 0;
	int stations = 0;
	int start;
	int end;

	string begin;
	string finish;

	myFile >> stations;
	myFile >> routes;

	Graph g = Graph(stations, routes);

	while (colorFile.eof() != true)
	{
		string s;
		int i;
		colorFile >> i;
		colorFile >> s;
		s[0] = tolower(s[0]);

		g.colors[i] = s;
	}

	while (myFile.eof() != true)
	{
		int x, y, z = 0;

		myFile >> x;
		myFile >> y;
		myFile >> z;

		g.addRoute(x, y, z);

		n++;
	}

	g.calcShortestRoutes();
	
	while (1 == 1)
	{

		cout << "--Menu--   " << endl << "0 = > Exit" << endl << "1 = > Print Menu" << endl << "2 = > Check if path exist"<< endl;
		int selection = 0;
		cin >> selection;
		if (selection == 0)
		{
			break;
		}
		if(selection == 2 )
		{ 
			while (1 == 1)
			{
				bool isCorrect = false;

				while (isCorrect == false)
				{
					cout << "Where would you like to start?";
					cin >> begin;
					start = g.returnStation(begin);
					if (start >= 0)
					{
						isCorrect = true;
					}
					else
					{
						cout << "Invalid Station " <<  endl;
					}
				}
				isCorrect = false;
				while (isCorrect == false)
				{
					cout << "Where would you like to end?";
					cin >> finish;
					end = g.returnStation(finish);
					if (start >= 0)
					{
						isCorrect = true;
					}
					else
					{
						cout << "Invalid Station" << endl;
					}
				}
				if (g.isRoute(start, end) == true)
				{
					g.calcShortestRoutes();
					cout << "Yes there is a path from station " << begin << " to station " << finish << " with a minimum distance of " <<
						g.shortestRoute(begin, finish) <<  "miles." << endl;
					
				}
				else
				{
					cout << "No you would not be able to travel from station " << begin << " to station " << finish << endl;
				}
				cout << "Return to Menu?(y/n)";
				string s = "";
				cin >> s;

				if (s == "y")
				{
					break;
				}
			}
		}
		
	}
	return 0;
}