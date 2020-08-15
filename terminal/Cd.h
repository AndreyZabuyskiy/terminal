#pragma once
#include "Command.h"

class Cd : public Command
{
public:
	Cd();
	void execute(const char* argument, char* path) override;

private:
	char* dir;
	bool set_dir(const char* argument);

	bool is_exist_direct(const char* argument);

	char* dir_up(char* direct);
	int find_idx_bottom_slash(char* direct);
	void str_copy(char* destination, int number_char, char* sourse);
};