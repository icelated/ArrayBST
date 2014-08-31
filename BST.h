#ifndef BST_H
#define BST_H

#include "data.h"

class BST								// a Binary Search Tree (BST)
{
public:
	BST(int capacity = 5);				// constructor (default if no arg supplied)
	BST(const BST& aTable);				// copy constructor
	~BST();								// destructor

	void insert(const data& aData);		
	bool remove(const char *key);
	bool retrieve(const char *key, data& aData) const;
	void displayArrayOrder(ostream& out) const;		
	void displayPreOrder(ostream& out) const;
	void displayInOrder(ostream& out) const;
	void displayPostOrder(ostream& out) const;
	int getSize(void) const;

private:

    int size;
    int maxsize;  
    int parent;
    
 
    void expand(int grow);

	struct item
	{
		bool	empty;
		data instanceData;
		bool  isLeaf;
	};
	
	item *items;
	
	/************* Helper functions***********************/
	void insert(int index, const data & aData );                      // helper function for insert
	void displayHeaders(ostream& out)const;
	void BST::displayPreOrder(std::ostream &out, int parent)const;    // helper functions 
	void BST::displayInOrder(std::ostream &out, int parent)const;
	void BST::displayPostOrder(std::ostream &out, int parent)const;
	bool BST::retrieve(const char *key, data& aData, int parent) const;
	void itemsPrinted(ostream &out,int size)const;                         // just displays items
	bool BST::Searchremove(const char *key, int parent); // search for a key for the delete function
	bool BST::remove(int parent);                        // helper for remove function
	void BST::printRecord(std::ostream & out, int index)const;
	int BST::SearchinorderSuccessor(int parent);
	bool BST::hasToPrintLeaf(int index)const;
};


#endif // BST_H
