#pragma once
#include "Motion.h"

class Move : public Motion
{
public:
	Move();

	void execute(const char* argument, char* path) override;
};