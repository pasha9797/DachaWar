#pragma once

#include "dachaWarClasses.h"

class Drawer
{
public:
	Drawer();
	~Drawer();

	static void draw(Field* field);

private:
	static void setcur(int x, int y);
};

