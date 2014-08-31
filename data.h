#ifndef DATA_H
#define DATA_H
#include <ostream>

using namespace std;

class data
{
public:
	data() : name(NULL) {}				// default constructor
	data(char const * const name);		// constructor
	~data();							// destructor

	data& operator=(const data& data2);

	char const * const getName() const;
	void setName(char const * const name);

private:
	char * name;

	friend ostream& operator<< (ostream& out, const data& outData);
	friend bool operator< (const data& d1, const data& d2);
	friend bool operator== (const data& d1, const data& d2);
};


#endif // DATA_H
