#include "Terminal.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc == 1)
	{
		Terminal terminal(argv[0]);
		terminal.run();
	}
	else
	{
		Terminal terminal(argv[1]);
		terminal.run();
	}

	return 0;
}