#include "Terminal.h"

Terminal::Terminal(const char* path)
{
	this->path = new char[200];
	strcpy(this->path, path);
}

char* Terminal::get_path()
{
	return path;
}

void Terminal::run()
{
	char* give_command = new char[100];
	cout << path << ">";
	cin.getline(give_command, 100);

	while(strcmp(give_command, "exit") != 0)
	{
		for (int i = 0; i < NUMBER_OF_COMMAND; ++i)
		{
			char* find = (char*)command[i]->get_an_indication();
			char* iterator = (char*)strstr(give_command, find);

			if (iterator != NULL)
			{
				cout << iterator << endl;
				command[i]->execute(give_command, path);
			}
		}

		cout << path << ">";
		cin.getline(give_command, 100);
	}
}