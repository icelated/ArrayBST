#define _CRT_SECURE_NO_DEPRECATE	// stop deprecation warnings, needs to be on first line

#include "data.h"
#include <iostream>
#include <iomanip>
#pragma warning(disable:4996)
using namespace std;



/** Data: constructor
* in: name
* out: name
* return:  
**/
data::data(char const * const name) : name(new char[strlen(name)+1])
{

		strcpy(this->name , name); // copy name

}

/** data: destructor
* in: 
* out: none
* return:  
**/
data::~data()
{
	delete [] name ; 
}

   
/** data: assignment operator overload
* in: 
* out: none
* return:  
**/
data& data::operator=(const data& data2)
{
	if ( this == &data2) //check ofr self assignment
	{
		return *this;
	}
	
	delete [] name; 
	name = NULL;

	name = new char[strlen(data2.name)+1];	// allocate new space
	strcpy(this->name, data2.name);	//copy
	return *this;
}

/** data: getname
* in: 
* out: none
* return:  name
**/
char const * const data::getName() const
{
	return this->name;
}


/** data: setname
* in: name
* out: none
* return:  
**/
void data::setName (char const * const name)
{

     
     delete [] this->name;
     this->name = NULL;
     this->name = new char[strlen(name)+1]; //alocate space
    
	strcpy(this->name, name); //copy

}


/** data: less than operator overload - return true if d1 is "less than" d2, false otherwise
* in: 
* out: none
* return: bool 
**/
bool operator< (const data& d1, const data& d2)
{

 return strcmp(d1.getName(), d2.getName()) < 0;
	

}


/** data: equal to operator overload - return true if d1 is "equal to" d2, false otherwise
* in: 
* out: none
* return:  
**/
bool operator== (const data& d1, const data& d2)
{

return strcmp(d1.getName(), d2.getName()) == 0;


}


/** data: operator<<  - print the data instance referred to by outData
* in: 
* out: none
* return:  
**/
ostream& operator<< (ostream& out, const data& outData)
{

  out << outData.name;
  //out << endl;
	return out;
}
