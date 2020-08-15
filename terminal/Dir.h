#pragma once
#include "Command.h"

class Dir : public Command
{
public:
	Dir();
	void execute(const char* argument, char* path) override;

private:
	char* dir;

	bool set_dir(const char* argument);
	void show_dir();
};