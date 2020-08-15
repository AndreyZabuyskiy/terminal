#pragma once
#include "Command.h"
#include "Dir.h"
#include "Cd.h"
#include "Copy.h"
#include "Move.h"
#include "Delete.h"
#include "Rename.h"
#include "Size_dir.h"

#define NUMBER_OF_COMMAND 7

class Terminal
{
public:
	Terminal(const char* path);
	char* get_path();
	void run();

private:
	char* path;
	Dir dir;
	Cd cd;
	Copy copy;
	Move move;
	Delete _delete;
	Rename rename;
	Size_dir size_dir;
	Command** command = new Command * [NUMBER_OF_COMMAND]{ &dir, &cd, &copy, &move, &_delete, &rename, &size_dir };
};