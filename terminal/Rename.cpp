#include "Rename.h"

Rename::Rename()
{
	an_indication = (char*)"rename";
}

void Rename::execute(const char* argument, char* path)
{
	source = Split_argument_NS::get_first_parameter(argument);
	destination = Split_argument_NS::get_second_parameter(argument);

	if (source != nullptr && destination != nullptr)
	{
		if (rename(source, destination) != -1)
		{
			cout << "Rename: success" << endl;
		}
		else
		{
			cout << "Rename: error" << endl;
		}
	}
}
