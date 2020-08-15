#include "Motion.h"

char* Motion::get_source()
{
	return source;
}

char* Motion::get_destination()
{
	return destination;
}

int Motion::idenfity_file_or_folder(char* parameter)
{
	char buff[SIZE_BUFF];
	strcpy(buff, parameter);
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

bool Motion::is_exist_dir_destination()
{
	if (idenfity_file_or_folder(destination) == -1)
	{
		if (idenfity_file_or_folder(dir_up_destination()) != -1)
			return true;
	}
	return false;
}

char* Motion::dir_up_destination()
{
	int idx_last_slash = find_idx_last_slash();

	if (idx_last_slash != NULL)
	{
		idx_last_slash++;
		char* up_destination = new char[SIZE_PARAMETER];

		for (int i = 0; i < idx_last_slash; ++i)
		{
			up_destination[i] = destination[i];
		}
		up_destination[idx_last_slash] = '\0';

		return up_destination;
	}

	return nullptr;
}

int Motion::find_idx_last_slash()
{
	for (int i = strlen(destination) - 1; i > -1; --i)
	{
		if (destination[i] == '\\')
			return i;
	}

	return NULL;
}

namespace Split_argument_NS
{
	char* get_first_parameter(const char* argument)
	{
		char* find = (char*)"\"";
		char* iterator = (char*)strstr(argument, find);

		if (iterator != nullptr)
		{
			iterator++;
			return set_first_parameter(iterator);
		}

		return nullptr;
	}

	char* set_first_parameter(const char* argument)
	{
		char* first_parameter = new char[SIZE_PARAMETER];
		int idx = 0;

		while (argument[idx] != '\0')
		{
			if (argument[idx] == '\"')
			{
				first_parameter[idx] = '\0';
				return first_parameter;
			}

			first_parameter[idx] = argument[idx];
			++idx;
		}

		return nullptr;
	}

	char* get_second_parameter(const char* argument)
	{
		for (int i = strlen(argument) - 1; i > -1; --i)
		{
			return set_second_parameter(argument, i - 1);
		}

		return nullptr;
	}

	char* set_second_parameter(const char* argument, const int idx)
	{
		char* buff = new char[SIZE_PARAMETER];
		int idx_buff = 0;

		for (int i = idx; i > -1; --i)
		{
			if (argument[i] == '\"')
			{
				buff[idx_buff] = '\0';
				return copy_from_buff_to_second_parameter(buff);
			}
			buff[idx_buff++] = argument[i];
		}

		return nullptr;
	}

	char* copy_from_buff_to_second_parameter(const char* buff)
	{
		char* second_parameter = new char[SIZE_BUFF];
		int idx = 0;

		for (int i = strlen(buff) - 1; i > -1; --i)
		{
			second_parameter[idx++] = buff[i];
		}
		second_parameter[idx] = '\0';

		return second_parameter;
	}
}

bool Copy_file::execute(const char* from, const char* to)
{
		ifstream f_in;
		ofstream f_out;

		f_in.open(from);
		f_out.open(to);

		if (!(f_in.is_open() && f_out.is_open()))
		{
			return false;
		}
		else
		{
			char buff;

			while (f_in.get(buff))
			{
				f_out << buff;
			}
		}

		return true;
}

bool Copy_folder::execute(const char* from, const char* to)
{
		char buff_source_path[200];
		strcpy(buff_source_path, from);
		strcat(buff_source_path, "\\*.*");

		_finddata_t* data = new _finddata_t;
		long handle = _findfirst(buff_source_path, data);

		if (handle != -1)
		{
			int end = handle;
			_mkdir(to);
			char buff_destination_path[SIZE_PARAMETER];

			while (end != -1)
			{
				strcpy(buff_source_path, from);
				strcat(buff_source_path, "\\");
				strcat(buff_source_path, data->name);

				strcpy(buff_destination_path, to);
				strcat(buff_destination_path, "\\");
				strcat(buff_destination_path, data->name);

				if (strcmp(data->name, ".") != 0 && strcmp(data->name, "..") != 0)
				{
					if (data->attrib & _A_SUBDIR)
					{
						Copy_folder::execute(buff_source_path, buff_destination_path);
					}
					else
					{
						Copy_file::execute(buff_source_path, buff_destination_path);
					}
				}

				end = _findnext(handle, data);
			}

			delete data;
			_findclose(handle);
			return true;
		}

		delete data;
		_findclose(handle);
		return false;
}

bool Move_file::execute(const char* from, const char* to)
{
	if (Copy_file::execute(from, to))
	{
		if (remove(from) != -1) {
			cout << "Remove: success" << endl;
			return true;
		}
		else {
			cout << "Remove: error" << endl;
		}
	}

	return false;
}

bool Move_folder::execute(const char* from, const char* to)
{
	if (Copy_folder::execute(from, to))
	{
		delete_dir(from);
		return true;
	}

	return false;
}

void Move_folder::delete_dir(const char* path)
{
	char buff[200];
	strcpy(buff, path);
	strcat(buff, "\\*.*");

	_finddata_t* data = new _finddata_t;
	long handle = _findfirst(buff, data);

	if (handle != -1)
	{
		int end = handle;

		while (end != -1)
		{
			strcpy(buff, path);
			strcat(buff, "\\");
			strcat(buff, data->name);

			if (strcmp(data->name, ".") != 0 && strcmp(data->name, "..") != 0)
			{
				if (data->attrib & _A_SUBDIR)
				{
					delete_dir(buff);
				}
				else
				{
					if (remove(buff) != -1) {
						cout << "Remove: success" << endl;
					}
					else {
						cout << "Remove: error" << endl;
					}
				}
			}

			end = _findnext(handle, data);
		}
		_rmdir(path);
	}

	delete data;
	_findclose(handle);
}

bool Delete_folder::execute(const char* path)
{
	char buff[200];
	strcpy(buff, path);
	strcat(buff, "\\*.*");

	_finddata_t* data = new _finddata_t;
	long handle = _findfirst(buff, data);

	if (handle != -1)
	{
		int end = handle;

		while (end != -1)
		{
			strcpy(buff, path);
			strcat(buff, "\\");
			strcat(buff, data->name);

			if (strcmp(data->name, ".") != 0 && strcmp(data->name, "..") != 0)
			{
				if (data->attrib & _A_SUBDIR)
				{
					execute(buff);
				}
				else
				{
					if (remove(buff) != -1) {
						cout << "Remove: success" << endl;
					}
					else {
						cout << "Remove: error" << endl;
					}
				}
			}

			end = _findnext(handle, data);
		}
		_rmdir(path);

		delete data;
		_findclose(handle);
		return true;
	}

	delete data;
	_findclose(handle);
	return false;
}
