#pragma once
#include <iostream>
#include <fstream>
#include <io.h>
#include <direct.h>
#pragma warning (disable: 4996)
using namespace std;

#define SIZE_BUFF 200

class Command
{
public:
	virtual void execute(const char* argument, char* path) = 0;

	virtual char* get_an_indication()
	{
		return an_indication;
	}

protected:
	char* an_indication;
	char* argument;
};