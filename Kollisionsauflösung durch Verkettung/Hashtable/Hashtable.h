#include <stdlib.h>
#include <iostream>
#include <iomanip>

struct ht_data
{
	char *text;
	int number;
};

struct ht_entry
{
	ht_entry *nxt;
	ht_data *dat;
};

class Hashtable
{
private:
	int capacity;
	int elementCount;
	ht_entry **table;
	unsigned int function(char *text);

public:
	Hashtable(int siz);
	~Hashtable();
	ht_data* find(char *text);
	int insert(char *newText, int newNumber);
	void print();
	double getFillFactor();
	int getElementCount();
};
