#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <iostream>
#include "bst.h"

using namespace std;

static BST		database;

static void displayDatabase(bool all)
{
	database.displayArrayOrder(cout);
	cout << endl;
	if (! all)
		return;
	database.displayPreOrder(cout);
	cout << endl;
	database.displayInOrder(cout);
	cout << endl;
	database.displayPostOrder(cout);
	cout << endl;
}

static void retrieveItem(char *name, data& aData)
{
	cout << ">>> retrieve " << name << endl << endl;
	if (database.retrieve(name, aData))
		cout << aData << endl;
	else
		cout << "not found\n";
	cout << endl;
}

static void removeItem(char *name)
{
	cout << ">>> remove " << name << endl << endl;
	if (database.remove(name))
		cout << name << " removed\n";
	else
		cout << name << " not found\n";
	cout << endl;
}

int main()
{
#ifdef _WIN32
	// request memory leak report in Output Window after main returns
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	data	aData;

	cout << "Corey Mattis"
		 << endl << endl
		 << "Database Of Great Computer Scientists\n\n";

	database.insert(data("Ralston, Anthony"));
	database.insert(data("Liang, Li"));
	database.insert(data("Jones, Doug"));
	database.insert(data("Goble, Colin"));
	database.insert(data("Knuth, Donald"));
	database.insert(data("Kay, Alan"));
	database.insert(data("Von Neumann, John"));
	database.insert(data("Trigoboff, Michael"));
	database.insert(data("Turing, Alan"));
	displayDatabase(true);
	retrieveItem("Trigoboff, Michael", aData);
	retrieveItem("Kaye, Danny", aData);
	
	removeItem("Ralston, Anthony");
	displayDatabase(true);
	removeItem("Jones, Doug");
	displayDatabase(true);
	removeItem("Kay, Alan");
	displayDatabase(true);
	removeItem("Kay, Alan");
	removeItem("Von Neumann, John");
	displayDatabase(true);
	removeItem("Turing, Alan");
	displayDatabase(true);
	removeItem("Goble, Colin");
	displayDatabase(true);
	
	return 0;
}
