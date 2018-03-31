#include "stdafx.h"
#include "drawer.h"
#include <iostream>
#include "consts.h"
#include <Windows.h>

using namespace std;

Drawer::Drawer()
{
}


Drawer::~Drawer()
{
}

void Drawer::draw(Field* field) {
	setcur(0, 0);
	int sizeX = field->getCellsWidth() * Consts::instance().pixelsInCell;
	int sizeY = (field->getCellsHeight()) * Consts::instance().pixelsInCell;
	char symbol;

	std::cout << "Moles: "<< field->getMoleCount()<< '\n';
	std::cout << "Crop: " << field->getTotalCellsValue() << "  \n";

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			if (x % Consts::instance().pixelsInCell == 0 && y % Consts::instance().pixelsInCell == 0) {
				symbol = '0' + field->getCellValue(x / Consts::instance().pixelsInCell, y / Consts::instance().pixelsInCell);
			}
			else {
				Mole* mole = field->getMoleThere(x, y);
				if (mole != NULL && mole->isOnGround()) {
					if (dynamic_cast<MaleMole*>(mole) != nullptr)
						symbol = 'M';
					else if (dynamic_cast<FemaleMole*>(mole) != nullptr)
						symbol = 'F';
				}
				else if (mole != NULL && !mole->isOnGround())
				{
					if (dynamic_cast<MaleMole*>(mole) != nullptr)
						symbol = 'm';
					else if (dynamic_cast<FemaleMole*>(mole) != nullptr)
						symbol = 'f';
				}
				else if (field->isDachaManThere(x, y))
					symbol = '#';
				else
					symbol = ' ';
			}
			cout<<symbol;
		}
		cout << '\n';
	}
	for (int i = 0; i < 5; i++)
		cout << '\n';
}

void Drawer::setcur(int x, int y)//установка курсора на позицию  x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};