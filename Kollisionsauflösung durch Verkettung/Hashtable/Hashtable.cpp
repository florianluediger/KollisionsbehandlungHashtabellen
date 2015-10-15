#include "Hashtable.h"

using namespace std;

unsigned int Hashtable::function(char *text)	//jenkins one at a time hash
{
	int hash, i;
    for(hash = i = 0; i < strlen(text); ++i)
    {
        hash += text[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return abs(hash%capacity);
}

Hashtable::Hashtable(int siz)
{
	capacity = siz;
	elementCount = 0;
	table = (ht_entry **)calloc(siz, sizeof(ht_entry *));
}

Hashtable::~Hashtable()
{
	ht_entry *e;

	for (int i = 0; i < capacity; i++)
	{
		while (e = table[i])
		{
			table[i] = e->nxt;
			free(e->dat->text);
			free(e->dat);
			free(e);
		}
	}
	free(table);
}

ht_data* Hashtable::find(char *text)
{
	ht_entry *e;

	for (e = table[function(text)]; e; e = e->nxt)
	{
		if (!strcmp(text, e->dat->text))
		{
			return e->dat;
		}
	}
	return 0;
}

int Hashtable::insert(char *newText, int newNumber)
{
	ht_data *newData;
	ht_entry **e, *newE;
	newData = (ht_data *)malloc(sizeof(ht_data));
	newData->text = (char *)malloc(strlen(newText)+1);
	strcpy(newData->text, newText);
	newData->number = newNumber;

	for (e = table + function(newData->text); *e; e = &((*e)->nxt))
	{
		if(strcmp(newData->text, (*e)->dat->text) == 0)
			return 0;
	}
	newE = (ht_entry *)malloc(sizeof(ht_entry));
	newE->nxt = *e;
	newE->dat = newData;
	*e = newE;
	elementCount++;
	return 1;
}

void Hashtable::print()
{
	ht_entry *e;
	for (int i = 0; i < capacity; i++)
	{
		while (e = table[i])
		{
			table[i] = e->nxt;
			cout << setw(10) << setiosflags(ios::left) << function(e->dat->text);
			cout << setw(50) << setiosflags(ios::left) << e->dat->text;
			cout << resetiosflags(ios::left) << e->dat->number << endl;
		}
	}	
}

double Hashtable::getFillFactor()
{
	return (double)elementCount / (double)capacity;
}

int Hashtable::getElementCount()
{
	return elementCount;
}