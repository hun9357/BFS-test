#pragma once
#include <string>
#include <vector>
#include <queue>
using namespace std;

class gameGraph
{
private:
	class vertex
	{
	public:
		string data;
		bool mark;
		//List of all edges leaving this vertex
		vector<vertex*> neighbors;
		vertex*  bread;

		vertex(string x)
		{
			data = x;
			mark = false;
			bread = nullptr;
		}
	};

	vector<vertex*> vertexList;

	//Return the vertex with x as it's data field.
	//Return null if it doesn't exist.
	vertex * findVertex(string x)
	{
		for (int i = 0; i < vertexList.size(); i++)
		{
			if (vertexList[i]->data == x)
				return vertexList[i];
		}
		return nullptr;
	}

	///////////Game specific stuff////////////////
	vertex * playerLocation;


public:

	void addVertex(string x)
	{
		vertex * babyVertex = new vertex(x);
		vertexList.push_back(babyVertex);
	}

	void addDirectedEdge(string x, string y)
	{
		vertex * xVert = findVertex(x);
		vertex * yVert = findVertex(y);

		if (xVert == nullptr || yVert == nullptr)
		{
			cout << "Oh no!  You've hosed up!" << endl;
		}
		else
		{
			xVert->neighbors.push_back(yVert);
		}
	}

	void addEdge(string x, string y)
	{
		addDirectedEdge(x, y);
		addDirectedEdge(y, x);
	}

	/////////////Game specific methods///////////////

	void setPlayerLocation(string x)
	{
		playerLocation = findVertex(x);
	}

	string getPlayerLocation()
	{
		return playerLocation->data;
	}

	//Return list of locations player can get to from current location.
	string getExits()
	{
		string exits = "";
		for (int i = 0; i < playerLocation->neighbors.size(); i++)
		{
			exits = exits + ", " + playerLocation->neighbors[i]->data;
		}
		return exits;
	}

	//Attempt to move player to x.
	//If x is not directly reaching from player location,
	//return false.  Otherwise, move player and return true.
	bool travelTo(string x)
	{
		for (int i = 0; i < playerLocation->neighbors.size(); i++)
		{
			if (x == playerLocation->neighbors[i]->data)
			{
				playerLocation = playerLocation->neighbors[i];
				clear(playerLocation);
				return true;
			}
		}
		return false;
	}
	//find shortest path to destination
	void shortestPathTo(string d)
	{
		breadthFirstSearch(playerLocation);
		vertex*dvert = findVertex(d);
		trace(dvert);
	}
		
	void trace(vertex*d)
	{
		vertex*temp = d;
		vector<vertex*> l;
		bool thru = true;
		while (temp != playerLocation)
		{
			temp = temp->bread;
			if (temp == nullptr)
			{
				thru = false;
				break;
			}
			else if (temp == playerLocation)
			{ 
				break;
			}
			else
			{
				l.push_back(temp);
			}
		}
		int size = l.size() - 1;
		if (thru == true)
		{
			cout << "From " << playerLocation->data << " to ";
			for (int i = size; i >= 0; i--)
			{
				cout << l[i]->data << " to ";
			}
			cout << d->data << endl;
		}
		else
		{
			cout << "There is no path to King's Landing!" << endl;
		}
	}
	
	void ouput(string d)
	{
		breadthFirstSearch(playerLocation);
		vertex*dvert = findVertex(d);
		
	}
	void clear(vertex*s)
	{
		queue<vertex*>q;
		q.push(s);
		while (!q.empty())
		{
			vertex*x = q.front();
			q.pop();
			x->mark = false;
			x->bread = nullptr;
			for (int i = 0; i < x->neighbors.size(); i++)
			{
				vertex*y = x->neighbors[i];
				if (y->mark == true)
				{
					y->mark = false;
					q.push(y);
					y->bread = nullptr;
				}
			}
		}
	}
	void breadthFirstSearch(vertex *s)
	{
		queue<vertex*> q;
		q.push(s);
		while (!q.empty())
		{
			vertex *x = q.front();
			q.pop();
			x->mark = true;
			for (int i = 0; i < x->neighbors.size(); i++)
			{
				vertex*y = x->neighbors[i];
				if (y->mark == false)
				{
					y->mark = true;
					q.push(y);
					y->bread = x;
				}			
			}
		}
	}
};
