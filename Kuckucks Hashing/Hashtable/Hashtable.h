#include <stdlib.h>
#include <iostream>
#include <iomanip>

struct ht_data
{
	char *text;
	int number;
};

class Hashtable
{
private:
	int capacity;
	int maxLoop;
	int elementCount;
	ht_data **table;
	unsigned int function1(char *text);
	unsigned int function2(char *text);

public:
	Hashtable(int siz);
	~Hashtable();
	ht_data* find(char *text);
	int insert(char *newText, int newNumber);
	void print();
	double getFillFactor();
	int getElementCount();
};
