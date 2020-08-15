#pragma once
#include "Motion.h"

class Copy : public Motion
{
public:
	Copy();
	void execute(const char* argument, char* path) override;
};
