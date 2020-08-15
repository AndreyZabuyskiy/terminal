#include "Move.h"

Move::Move()
{
	an_indication = (char*)"move ";
}

void Move::execute(const char* argument, char* path)
{
	source = Split_argument_NS::get_first_parameter(argument);
	destination = Split_argument_NS::get_second_parameter(argument);

	if (source != nullptr && destination != nullptr)
	{
		if (is_exist_dir_destination())
		{
			int idenfity = idenfity_file_or_folder(source);

			if (idenfity > 0)
			{
				cout << "Folder" << endl;

				if (Move_folder::execute(source, destination))
					cout << "Успешно" << endl;
				else
					cout << "Ошибка" << endl;
			}
			else if (idenfity == 0)
			{
				cout << "File" << endl;

				if (Move_file::execute(source, destination))
					cout << "succses" << endl;
				else
					cout << "error" << endl;
			}
			else if (idenfity < 0)
			{
				cout << "Directory not found" << endl;
			}
		}
	}
	else
	{
		cout << "Данные введены не корректно" << endl;
	}
}
