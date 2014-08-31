#include "BST.h"
#include <iostream> 
#include <iomanip>
#pragma warning(disable:4996)
using namespace std;

/**
* BST: Constructor
* in: capacity
* out: none
* return: none
**/
BST::BST(int capacity) : size(0), parent(0),
items(new item[capacity])
{

	maxsize = capacity;
	items->isLeaf = true;      // set to true which actually means false..
	this->items->empty = true; // wouldnt work if it was set to false


}
/**
* BST: destructor
* in: capacity
* out: none
* return: none
**/
BST::~BST()
{
	//delete items; 
	delete [] items;
}

/**
* BST: Insert - helper function for recursion.
* in: parent,aData
* out: none
* return: none
**/
void BST::insert(int parent, const data &aData) 
{

	if(parent >= maxsize) // if over array size lets expand it
	{
		this->expand(parent); 
	}
	if (items[parent].empty)  // if empty we can add
	{
		items[parent].instanceData = aData;
		items[parent].empty = false;
		size++;	
	}
	else if (aData < items[parent].instanceData) // indicates we want this to be the left child
	{
		parent = (2 * parent)+ 1; 
		this->insert(parent,aData);   //recursion

	}
	else // indicates we want this to be the right child.
	{
		parent = (2 * parent)+ 2; 
		this->insert(parent,aData); 
	}

}
/**
* BST: insert
* in: aData
* out: none
* return: none
**/
void BST::insert (const data& aData)
{
	this->insert(parent, aData); // call the helper function
}

/**
* BST: expand - expand the tree size
* in: grow
* out: none
* return: none
**/
void BST::expand(int grow)
{


	// help our BST get bigger when needed.

	item *swap = new item[maxsize+grow]; // allocate space to swap


	for ( int index = 0; index < maxsize; index++ ) 
	{
		if ( !items[index].empty )
		{

			swap[index].instanceData = items[index].instanceData; // swap
			swap[index].empty = items[index].empty;
		}


	}

	maxsize += size;
	delete [] items;  
	items = NULL;
	items = swap;  // swap items
}

/**
* BST: retrieve - helper function
* in: aData, parent
* out: none
* return: bool
**/
bool BST::retrieve(const char *key, data &aData, int parent) const
{


	if (!items[parent].empty && parent <= maxsize ) // stay within our array
	{

		if (key == items[parent].instanceData) // check for a match with the key
		{
			aData.setName(key); // asign aData with the match
			return true;
		}
		else if (key < items[parent].instanceData ) // if key is less than let search the left side of tree
		{
			parent =(2*parent) + 1;
			retrieve(key, aData, parent);
		}
		else                                     // search right side.
		{
			parent =( 2*parent) + 2;
			retrieve(key, aData, parent);
		}
		return false;

	} 

return false;
}


/**
* BST: retrieve
* in: aData
* out: none
* return: none
**/
bool BST::retrieve(const char *key, data& aData) const
{

	retrieve(key, aData, parent); // call the helper function

	if (key == aData)   // check if we actually have the match
	{
		return true;
	}
	else
	{
		return false;
	}

}



/**
* BST: remove
* in: key
* out: none
* return: none
**/
bool BST::remove(const char* key)
{

	Searchremove(key, parent);  // call search function to find the key in the tree

	return true;


}

/**
* BST: remove - helper function
* in: parent
* out: none
* return: none
**/
bool BST::remove(int parent)
{

//*********** isLeaf is set to true but means its flase

	// delete if its a leaf.
	if(!items[parent].isLeaf)
	{
		items[parent].empty = true;
		size--;
	}
	// one child
	else if((items[2*parent+1].empty && !items[2*parent+2].empty) ||(!items[2*parent+1].empty && items[2*parent+2].empty))
	{
		//one child
		if(!items[2*parent+1].empty && items[2*parent+2].empty)// left child of parent?
		{
			items[parent].instanceData = items[2*parent+1].instanceData;
			items[2*parent+1].empty = true;
			size--;

		}
		else
		{
			parent = 2*parent+2;
			size--;
			return true;
		}
	}

	else // 2 children
	{
		int index;
		index = SearchinorderSuccessor(2*parent+2);

		items[parent] = items[index]; //copy inorder successor into root
		items[parent].instanceData = items[index].instanceData; //copy inorder successor data into root data
		if(!items[index].isLeaf) // if its a leaf set the leaf to true. which means false.
		{
			items[parent].isLeaf = true; // actually false
		}


		if(!items[2*index+2].empty)
		{
			items[index].instanceData = items[2 * index + 2].instanceData; //...copy right branch of inorder successor into the inorder successor's place
			items[2 * index + 2].empty = true; //set right branch to "empty"

		}

		// isLeaf is set to true when its false
		if(!items[index].isLeaf)
		{
			items[index].empty = true;
			items[index].isLeaf = true;

		}


		size--;




	}

return false;
}

int BST::SearchinorderSuccessor(int parent)
{

	// find the inorder successor.

	if (!items[2*parent+1].empty) // if not empty advance left
	{
		parent = (2*parent+1);

		if(items[2*parent+1].isLeaf) // if we get to the end return
		{

			return parent;
		}
		SearchinorderSuccessor(parent); // recursive



	}
	else
	{

		return parent;

	}


return false;
}



/**
* BST: Searchremove- a search for the delete function
* in: key, parent
* out: none
* return: bool
**/
bool BST::Searchremove(const char *key, int parent)
{

	if (!items[parent].empty && parent <= maxsize ) // stay within array
	{

		if (key == items[parent].instanceData) // if a match call the remove function
		{
			remove(parent);
			return true;
		}
		else if (key < items[parent].instanceData ) // process left child
		{
			parent =(2*parent) + 1;
			Searchremove(key,  parent);
		}
		else                                  // process right child
		{
			parent =( 2*parent) + 2;
			Searchremove(key,  parent);
		}

	} 
return false;
}


/**
* BST: Display headers
* in: out
* out: none
* return:
**/
void BST::displayHeaders(ostream& out)const
{
	out << endl;
	out << right;
	out << "name  " 
		<< setw(26)<< "leaf?" << setw(7)
		<< "index" << setw(7)
		<< endl;
	out << left;
	out << setw(27) 
		<< "----" 
		<< setw(7) << "-----" 
		<< setw(9) << "-----" 
		<< endl;

}

/**
* BST: displayarrayorder - display items in the tree by traversing the array from beginning to end
* in: out
* out: none
* return: 
**/
void BST::displayArrayOrder (ostream& out) const
{

	out << ">>> array order:" << endl;
	displayHeaders(out);      // call display headers


	for(int index=0; index < maxsize+1; index++)
	{

		if (!items[index].empty)    //if not empty
		{
			out << left
				<< setw(27) << items[index].instanceData;  // items
			out	<< right
				<< setw(10);

			if(index > size)          // this indicates there is a leaf
			{
				items[index].isLeaf = false;   // set to false is actually setting it to true
				out << left

					<< setw(10) << "leaf";   // we found a leaf..
			}
			if(items[2*index+1].empty && items[2*index+2].empty && index < size)  // indicates there is a leaf
			{
				items[index].isLeaf = false;       // set to false is actually setting it to true
				out << left

					<< setw(11) << "leaf";
			}

			out << setw(12) << index;    // display node
			out << endl;


		}


	}


	if(!parent)
	{
		itemsPrinted(out,size);  // call itemsprinted
	}


}

/**
* BST: displaypreorder - helper function - display items in the tree 
* in: out, parent
* out: none
* return: 
**/
void BST::displayPreOrder(std::ostream &out, int parent)const
{

	if (parent <= maxsize)  // stay within array
	{
		printRecord(out,parent);

		this->displayPreOrder(out, 2 * parent + 1);  // recursion call for traversing preorder
		this->displayPreOrder(out, 2 * parent + 2);  // left and right


	}


	if(!parent)
	{
		itemsPrinted(out,size);
	}

}

/**
* BST: displaypreorder - main function
* in: out
* out: none
* return: 
**/
void BST::displayPreOrder (ostream& out) const
{
	out << endl;
	out << ">>> preorder:" << endl;
	out << endl;

	this->displayHeaders(out);
	this->displayPreOrder(out, parent);   // call the helper function

}

/**
* BST: displayinorder -Helper function - display items in the tree 
* in: out, parent
* out: none
* return: 
**/
void BST::displayInOrder(ostream& out, int parent)const
{


	if (parent <= maxsize)  // stay within array
	{

		this->displayInOrder(out, 2 * parent + 1);    // process left side first
		printRecord(out,parent);

		this->displayInOrder(out, 2 * parent + 2 );  // then process right side of tree

	}

	if(!parent)
	{
		itemsPrinted(out,size);
	}

}

/**
* BST: displayinorder 
* in: out
* out: none
* return: 
**/
void BST::displayInOrder (ostream& out) const
{
	out << endl;
	out << ">>> inorder:" << endl;
	out << endl;

	this->displayHeaders(out);

	this->displayInOrder(out,parent);  // call the helper function

}

/**
* BST: displaypostorder -Helper function -  display items in the tree 
* in: out, parent
* out: none
* return: 
**/
void BST::displayPostOrder(std::ostream &out, int parent) const
{


	if (parent <= maxsize) // stay within array bounds
	{

		this->displayPostOrder(out, 2 * parent + 1);   // process left side than right side
		this->displayPostOrder(out, 2 * parent + 2 );
		printRecord(out,parent);
	

	}



	if(!parent)
	{
		itemsPrinted(out,size); // call itemsprinted
		out << endl;
	}

}

/**
* BST: displaypostorder 
* in: out, parent
* out: none
* return: 
**/
void BST::displayPostOrder (ostream& out) const
{
	out << endl;
	out << ">>> postorder:" << endl;
	out << endl;

	this->displayHeaders(out);
	this->displayPostOrder(out,parent);  // call helper function


}



/** BST: getsize - return number of data items contained in the BST
* in: 
* out: none
* return:  maxsize
**/
int BST::getSize (void) const
{
	return maxsize;
}

/** BST: itemsprinted
* in: 
* out: none
* return: 
**/
void BST::itemsPrinted(ostream &out, int size) const
{
	out << left
		<< setw(41) << "(items printed)" 
		<< setw(0) <<"(" << size << ")";

}

/** BST: printrecord
* in: index
* out: none
* return:  
**/

void BST::printRecord(std::ostream & out, int index)const
{


	if (index <= maxsize) // stay within array bounds
	{

		if (!items[index].empty)    //if not empty
		{
			out << left
				<< setw(27) << items[index].instanceData;  // items
			out	<< right
				<< setw(10);

			if(!items[index].isLeaf) // indicates there is a leaf
			{

				out << left

					<< setw(10) << "leaf";
			}

			out << setw(12) << index;    // display node
			out << endl;

		}

	}
}

