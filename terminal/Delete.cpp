#include "Delete.h"

Delete::Delete()
{
	an_indication = (char*)"delete ";
}

void Delete::execute(const char* argument, char* path)
{
	if (set_dir(argument))
	{
		int identify = identify_file_or_folder(dir);

		if (identify > 0)
		{
			if (Delete_folder::execute(dir))
				cout << "Remove: success" << endl;
			else
				cout << "Remove: error" << endl;
		}
		else if (identify == 0)
		{
			if (remove(dir) != -1)
				cout << "Remove: success" << endl;
			else
				cout << "Remove: error" << endl;
		}
		else if (identify < 0)
		{
			cout << "Directory not found" << endl;
		}
	}
}

bool Delete::set_dir(const char* argument)
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

int Delete::identify_file_or_folder(const char* path)
{
	char buff[SIZE_BUFF];
	strcpy(buff, path);
	strcat(buff, "\\.");

	_finddata_t* data = new _finddata_t;
	long handle = _findfirst(buff, data);

	if (handle != -1)
	{
		if (data->attrib & _A_SUBDIR)
		{
			delete data;
			_findclose(handle);
			return 1;
		}
		else
		{
			delete data;
			_findclose(handle);
			return 0;
		}
	}

	delete data;
	_findclose(handle);
	return -1;
}
