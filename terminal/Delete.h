#pragma once
#include "Motion.h"

class Delete : public Command
{
public:
	Delete();
	void execute(const char* argument, char* path) override;

private:
	char* dir;

	bool set_dir(const char* argument);

	int identify_file_or_folder(const char* path);
};