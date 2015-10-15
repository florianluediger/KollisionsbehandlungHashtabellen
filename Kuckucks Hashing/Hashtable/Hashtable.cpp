#include "Hashtable.h"

using namespace std;

unsigned int Hashtable::function2(char *text)	//FNV Hash
{
	unsigned long hash = 2166136261;
	while(*text)
	{
		hash += (hash<<1) + (hash<<4) + (hash<<7) + (hash<<8) + (hash<<24);
		hash ^= (unsigned long)*text++;
	}
	return hash % capacity;
}

unsigned int Hashtable::function1(char *text)	//jenkins one at a time hash
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
	table = (ht_data **)calloc(capacity, sizeof(ht_data *));
	maxLoop = 100;
}

Hashtable::~Hashtable()
{
	ht_data *e;
	for (int i = 0; i < capacity; i++)
	{
		if (table[i])
		{
			e = table[i];
			free(e->text);
			free(e);
		}
	}
	free(table);
}

ht_data* Hashtable::find(char *text)
{
	int var = function1(text);
	if (!table[function1(text)])
		return 0;
	if (!strcmp(text, table[function1(text)]->text))
		return table[function1(text)];
	if (!table[function2(text)])
		return 0;
	if (!strcmp(text, table[function2(text)]->text))
		return table[function2(text)];
	return 0;
}

int Hashtable::insert(char *newText, int newNumber)		
{
	ht_data *newE, *savE;
	int lastPosition = function2(newText);

	if (find(newText))
		return 0;

	newE = (ht_data *)malloc(sizeof(ht_data));
	newE->text = (char *)malloc(strlen(newText));
	strcpy(newE->text, newText);
	newE->number = newNumber;

	if(!table[function1(newText)])
	{
		table[function1(newText)] = newE;
		elementCount++;
		return 1;
	}
	else if(!table[function2(newText)])
	{
		table[function2(newE->text)] = newE;
		elementCount++;
		return 1;
	}

	for (int i = 0; i < maxLoop; i++)
	{
		if(lastPosition == function2(newE->text))
		{
			if(table[function1(newE->text)])
			{
				savE = table[function1(newE->text)];
				table[function1(newE->text)] = newE;
				lastPosition = function1(newE->text);
				newE = savE;
			}
			else
			{
				table[function1(newE->text)] = newE;
				elementCount++;
				return 1;
			}
		}
		else
		{
			if(table[function2(newE->text)])
			{
				savE = table[function2(newE->text)];
				table[function2(newE->text)] = newE;
				lastPosition = function2(newE->text);
				newE = savE;
			}
			else
			{
				table[function1(newE->text)] = newE;
				elementCount++;
				return 1;
			}
		}
	}
	return 0;
}

void Hashtable::print()
{
	for (int i = 0; i < capacity; i++)
	{
		if (table[i])
		{
			cout << setw(5) << setiosflags(ios::left) << i;
			cout << setw(20) << setiosflags(ios::left) << table[i]->text;
			cout << setw(5) << setiosflags(ios::left) << table[i]->number;
		}
		else
			cout << i << " ist leer!" << endl;
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