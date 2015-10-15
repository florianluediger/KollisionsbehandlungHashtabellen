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

unsigned int Hashtable::offsetFunction(char *text)	//Kernighan & Ritchie
{
	unsigned long hash = 0;
	int c;
	while (c = *text++)
		hash += c;
	return hash % capacity;
}

int Hashtable::series(int j, char *text)		//Doppel Hashing
{
	return j * offsetFunction(text);
}

//int Hashtable::series(int j)		//Quadratisches Sondieren
//{
//	return j * j;
//}

int Hashtable::series(int j)		//Lineares Sondieren
{
	return j;
}

Hashtable::Hashtable(int siz)
{
	capacity = siz;
	elementCount = 0;
	table = (ht_data **)calloc(siz, sizeof(ht_data *));
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
	int hf = function(text);
	int index = hf;
	int i = 0, serI = 0;

	while (table[index] && strcmp(text, table[index]->text) && i < capacity)
	{
		index = (hf + series(i)) % capacity;
		i++;
	}

	if (i < capacity)
		return table[index];
	else
		return 0;
}

int Hashtable::insert(char *newText, int newNumber)
{
	ht_data **e, *newE;
	int i = 0, serI = 0;
	int hf = function(newText);
	int index = hf;

	while (table[index])
	{
		index = (hf + series(i)) % capacity;
		i++;
		if (i >= capacity)
			return 0;
	}

	e = table + index;

	newE = (ht_data *)malloc(sizeof(ht_data));
	newE->text = (char *)malloc(strlen(newText)+1);
	strcpy(newE->text, newText);
	newE->number = newNumber;
	*e = newE;
	elementCount++;
	return 1;
}

void Hashtable::print()
{
	for (int i = 0; i < capacity; i++)
	{
		if (table[i])
		{
			cout << setw(10) << setiosflags(ios::left) << i;
			cout << setw(50) << setiosflags(ios::left) << table[i]->text;
			cout << resetiosflags(ios::left) << table[i]->number << endl;
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