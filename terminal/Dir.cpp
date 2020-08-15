#include "Dir.h"

Dir::Dir() : dir(nullptr)
{
	an_indication = (char*)"dir";
}

void Dir::execute(const char* argument, char* path)
{
	if (set_dir(argument))
	{
		show_dir();
	}
}

bool Dir::set_dir(const char* argument)
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

void Dir::show_dir()
{
	char buff[SIZE_BUFF];
	strcpy(buff, dir);
	strcat(buff, "\\*.*");

	_finddata_t* data = new _finddata_t;
	long handle = _findfirst(buff, data);

	if (handle != -1)
	{
		int end = handle;

		while (end != -1)
		{
			cout << data->name << (data->attrib & _A_SUBDIR ? "(Folder)" : "(File)") << endl;
			end = _findnext(handle, data);
		}
	}
	else
	{
		cout << "Directory not found" << endl;
	}

	delete data;
	_findclose(handle);
}
