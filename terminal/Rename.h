#pragma once
#include "Motion.h"

class Rename : public Motion
{
public:
	Rename();
	void execute(const char* argument, char* path) override;
};