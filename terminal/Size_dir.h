#pragma once
#include "Command.h"

class Size_dir : public Command
{
public:
	Size_dir();
	void execute(const char* argument, char* path) override;

private:
	char* dir;

	int identify_file_or_folder(const char* path);
	int size_file(const char* path);
	int size_folder(const char* path);

	bool set_path(const char* argument);
};