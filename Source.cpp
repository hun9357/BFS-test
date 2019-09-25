

#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

void buildWorld(gameGraph &world)
{
	world.addVertex("The Wall");
	world.addVertex("Winterfell");
	world.addVertex("Old Town");
	world.addVertex("King's Landing");
	world.addVertex("Iron Islands");
	world.addVertex("Sunspear");
	world.addVertex("Dungeon");
	world.addVertex("White Harbor");
	world.addVertex("Inn at the Crossroads");
	world.addVertex("Lannisport");
	world.addVertex("Essos");
	world.addVertex("Dragonstone");
	world.addVertex("Death");

	//Add a one-direction edge from king's landing to dungeon
	world.addDirectedEdge("King's Landing", "Dungeon");
	world.addDirectedEdge("Dungeon", "Death");
	world.addDirectedEdge("Dungeon", "The Wall");
	world.addDirectedEdge("The Wall", "Death");

	//Add a two-way edge connection the wall and winterfell
	world.addEdge("The Wall", "Winterfell");
	world.addEdge("White Harbor", "Winterfell");
	world.addEdge("Inn at the Crossroads", "Winterfell");
	world.addEdge("Lannisport", "Winterfell");
	world.addEdge("Lannisport", "Iron Islands");
	world.addEdge("King's Landing", "White Harbor");
	world.addEdge("King's Landing", "Inn at the Crossroads");
	world.addEdge("King's Landing", "Old Town");
	world.addEdge("Old Town", "Sunspear");
	world.addEdge("Inn at the Crossroads", "Lannisport");
	world.addEdge("Essos", "White Harbor");
	world.addEdge("Essos", "Dragonstone");
	world.addEdge("Essos", "Sunspear");
	world.addEdge("King's Landing", "Dragonstone");


}

int main()
{
	gameGraph world;
	buildWorld(world);

	//Begin text-based adventure game
	world.setPlayerLocation("Lannisport");

	while (true) //Or you die, or whatever..
	{
		//Tell player where they are
		cout << "You are at " << world.getPlayerLocation() << endl;

		//Tell player where they can go
		cout << "You see roads going to : " << world.getExits() << endl;

		//Tell the player the shortest route to King's Landing:
		world.shortestPathTo("King's Landing");

		//Ask them where they want to go, get that info
		cout << "Where would you like to travel to brave knight?" << endl;
		string destination;
		getline(cin,destination);

		//Try to move them to their desired destination
		cout << "You try to travel to " << destination << "..." << endl;
		if (world.travelTo(destination))
		{
			cout << "...and it works..." << endl;
		}
		else
			cout << "BANG! You run into a mountain!  You can't go that way idiot!" << endl;
	}
	//world.ouput("King's Landing");

	return 0;
}