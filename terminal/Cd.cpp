#include "Cd.h"

Cd::Cd() : dir(nullptr)
{
	an_indication = (char*)"cd";
}

void Cd::execute(const char* argument, char* path)
{
	if (set_dir(argument))
	{
		if (strcmp(dir, "..") == 0)
		{
			strcpy(path, dir_up(path));
			return;
		}

		if (is_exist_direct(dir))
		{
			strcpy(path, dir);
			return;
		}
		else
		{
			char* new_path = new char[200];
			strcpy(new_path, path);
			strcat(new_path, dir);

			if (is_exist_direct(new_path))
			{
				strcpy(path, new_path);
				return;
			}
		}
	}

	cout << "Directory not found" << endl;
}

bool Cd::set_dir(const char* argument)
{
	dir = new char[200];
	int idx = 0;

	for (int i = 0; i < strlen(argument); ++i)
	{
		if (argument[i] == '\"')
		{
			for (int j = i + 1; j < strlen(argument); ++j)
			{
				if (argument[j] == '\"')
				{
					dir[idx] = '\0';
					return true;
				}

				dir[idx++] = argument[j];
			}
		}
	}

	return false;
}

bool Cd::is_exist_direct(const char* argument)
{
	char buff[SIZE_BUFF];
	strcpy(buff, argument);
	strcat(buff, "*.*");

	_finddata_t* data = new _finddata_t;
	long handle = _findfirst(buff, data);

	if (handle != -1)
	{
		delete data;
		_findclose(handle);
		return true;
	}

	delete data;
	_findclose(handle);
	return false;
}

char* Cd::dir_up(char* direct)
{
	int size_new_direct = find_idx_bottom_slash(direct);

	if (size_new_direct != NULL)
	{
		++size_new_direct;
		char* new_direct = new char[size_new_direct];

		str_copy(new_direct, size_new_direct, direct);

		return new_direct;
	}

	return direct;
}

int Cd::find_idx_bottom_slash(char* direct)
{
	for (int i = strlen(direct) - 2; i > -1; --i)
	{
		if (direct[i] == '\\')
			return i;
	}

	return NULL;
}

void Cd::str_copy(char* destination, int number_char, char* sourse)
{
	for (int i = 0; i < number_char; ++i)
	{
		destination[i] = sourse[i];
	}
	destination[number_char] = '\0';
}
