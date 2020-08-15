#pragma once
#include "Command.h"

#define SIZE_PARAMETER 200

class Motion : public Command
{
public:
	virtual void execute(const char* argument, char* path) = 0;

	char* get_source();
	char* get_destination();

protected:
	char* source;
	char* destination;

	int idenfity_file_or_folder(char* parameter);

	bool is_exist_dir_destination();
	char* dir_up_destination();
	int find_idx_last_slash();
};

struct Copy_file
{
	static bool execute(const char* from, const char* to);
};

struct Copy_folder
{
	static bool execute(const char* from, const char* to);
};

struct Move_file
{
	static bool execute(const char* from, const char* to);
};

struct Move_folder
{
	static bool execute(const char* from, const char* to);

private:
	static void delete_dir(const char* path);
};

struct Delete_folder
{
	static bool execute(const char* path);
};

namespace Split_argument_NS
{
	char* get_first_parameter(const char* argument);
	char* set_first_parameter(const char* argument);
	char* get_second_parameter(const char* argument);
	char* set_second_parameter(const char* argument, const int idx);
	char* copy_from_buff_to_second_parameter(const char* buff);
}