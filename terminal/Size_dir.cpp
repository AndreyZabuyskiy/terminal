#include "Size_dir.h"

Size_dir::Size_dir() : dir(nullptr)
{
	an_indication = (char*)"size ";
}

void Size_dir::execute(const char* argument, char* path)
{
	if (set_path(argument))
	{
		int identify = identify_file_or_folder(dir);

		if (identify > 0)
		{
			cout << size_folder(dir) << endl;
		}
		else if (identify == 0)
		{
			cout << size_file(dir) << endl;
		}
		else if (identify < 0)
		{
			cout << "Directory not found" << endl;
		}
	}
}

int Size_dir::identify_file_or_folder(const char* path)
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

int Size_dir::size_file(const char* path)
{
	char buff[200];
	strcpy(buff, path);
	strcat(buff, "*.*");

	_finddata_t* data = new _finddata_t;
	long handle = _findfirst(buff, data);

	if (handle != -1)
	{
		return data->size;
	}

	delete data;
	_findclose(handle);
	return 0;
}

int Size_dir::size_folder(const char* path)
{
	{
		char buff[200];
		strcpy(buff, path);
		strcat(buff, "\\*.*");

		_finddata_t* data = new _finddata_t;
		long handle = _findfirst(buff, data);

		if (handle != -1)
		{
			int end = handle;
			int size = 0;

			while (end != -1)
			{
				if (strcmp(data->name, ".") != 0 && strcmp(data->name, "..") != 0)
				{
					strcpy(buff, path);
					strcat(buff, "\\");
					strcat(buff, data->name);

					if (data->attrib & _A_SUBDIR)
					{
						size += size_folder(buff);
					}
					else
					{
						size += size_file(buff);
					}
				}

				end = _findnext(handle, data);
			}
			return size;
		}

		delete data;
		_findclose(handle);
		return 0;
	}
}

bool Size_dir::set_path(const char* argument)
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
