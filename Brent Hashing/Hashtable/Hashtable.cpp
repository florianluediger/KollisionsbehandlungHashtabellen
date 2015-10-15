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
    return (abs(hash) % capacity);
}

unsigned int Hashtable::offsetFunction(char *text)
{
	unsigned long hash = 5381;
    int c;

    while (c = *text++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return abs((int)hash % capacity);
}

int Hashtable::series(int j, char *text)		//Doppel Hashing
{
	j = j + offsetFunction(text);
	return j;
}

//int Hashtable::series(int j, char *text)		//Quadratisches Sondieren
//{
//	j = j * j;
//	return j;
//}

//int Hashtable::series(int j, char *text)		//Lineares Sondieren
//{
//	j = j + 1;
//	return j;
//}

Hashtable::Hashtable(int siz)
{
	capacity = siz;
	elementCount = 0;
	table = (ht_data **)calloc(siz, sizeof(ht_data *));
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
	int hf = function(text);
	int index = hf;
	int j = 0, i = 0;

	while (table[index] && strcmp(text, table[index]->text) && i < capacity)
	{
		index = (hf + series(j, text)) % capacity;
		i++;
		j++;
	}
	if (i < capacity)
		return table[index];
	else
		return 0;
}

int Hashtable::insert(char *newText, int newNumber)
{
	ht_data *newE, *savE;
	newE = (ht_data *)malloc(sizeof(ht_data));
	newE->text = (char *)malloc(strlen(newText)+1);
	strcpy(newE->text, newText);
	newE->number = newNumber;

	int index = function(newText);
	int alter1, alter2, loop = 0;
	while(table[index] && loop < maxLoop)
	{
		alter1 = series(index, newE->text) % capacity;
		alter2 = series(index, table[index]->text) % capacity;
		if(table[alter1] && !table[alter2])
		{
			savE = newE;
			newE = table[index];
			table[index] = savE;
			index = alter2;
		}
		else
			index = alter1;
		loop++;
	}
	table[index] = newE;
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