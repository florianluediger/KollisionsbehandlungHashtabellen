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
	int maxLoop;
	int capacity;
	int elementCount;
	ht_data **table;
	unsigned int function(char *text);
	unsigned int offsetFunction(char *text);
	int series(int j, char *text);

public:
	Hashtable(int siz);
	~Hashtable();
	int findIndex(char *text);
	ht_data* find(char *text);
	int insert(char *newText, int newNumber);
	void print();
	double getFillFactor();
	int getElementCount();
};
