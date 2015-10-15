#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Hashtable.h"

#define DATAPATH "testdaten.csv"
#define TABLESIZE 500

using namespace std;

int file_size(char *path)
{
	FILE *pf;
	int len;
	pf = fopen(path, "r");

	if (!pf)
	{
		std::cout << "Datei nicht gefunden!" << endl;
		system("PAUSE");
		return 0;
	}

	fseek(pf, 0, SEEK_END);
	len = ftell(pf);
	fclose(pf);
	return len;
}

int readFromFile(Hashtable *h, char *path)
{
	char *str, *ptr, *splitString;
	int len, splitInt;
	fstream *file = new fstream(path, fstream::in);
	
	if(false == file->good() || !(len = file_size(path)))
	{
		cout << "Datei nicht gefunden!" << endl;
		system("PAUSE");
		return 0;
	}

	str = (char *)malloc(len+1);
	file->read(str, len);
	file->close();
	ptr = str;

	while(*ptr != str[len])	//Dies dient nur dazu Müll am Ende des Strings zu entfernen
		ptr++;
	*ptr = '\0';
	cout << "Datei gelesen: " << file->gcount() << endl;
	
	splitString = strtok(str, ";");
	while(splitString != NULL)
	{
		splitInt = stoi(strtok(NULL, "\n"));
		h->insert(splitString, splitInt);

		splitString = strtok(NULL, ";");
	}

	free(str);
	return 1;
}

void main()
{
	Hashtable *table;
	table = new Hashtable(TABLESIZE);

	readFromFile(table, DATAPATH);
	//table->print();
	cout << table->getFillFactor() << endl;

	cout << "Fill Factor: " << table->getFillFactor() << "( " << table->getElementCount() << " / " << TABLESIZE << " )" << endl;
	cout << table->find("Kareem")->text << endl;
	delete table;
}