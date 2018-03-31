#include "stdafx.h"
#include "dachaWarClasses.h"
#include <math.h>
#include "consts.h"
#include <random>

using namespace std;

Field::Field(int width, int height, Mole* moles[], int cur_moles_count, DachaMan* dachaMan)
{
	this->dachaMan = dachaMan;
	this->dachaMan->setField(this);

	this->moleList = new Mole*[100];
	moleCount = 0;
	if (moles != NULL) {
		for (int i = 0; i < cur_moles_count; i++) {
			addMole(moles[i]);
		}
	}

	cellsWidth = width;
	cellsHeight = height;
	cells = new int*[height];
	for (int i = 0; i < height; i++) {
		cells[i] = new int[width];
		for (int k = 0; k < width; k++) {
			cells[i][k] = Consts::instance().startCellValue;
		}
	}
}


Field::~Field()
{
	for (int i = 0; i < moleCount; i++) {
		delete moleList[i];
	}
	delete moleList;

	for (int i = 0; i < cellsHeight; i++) {
		delete cells[i];
	}
	delete cells;
}

int Field::getCellsHeight() {
	return cellsHeight;
}

int Field::getCellsWidth() {
	return cellsWidth;
}

int Field::getMoleCount() {
	return moleCount;
}

Mole* Field::getMole(int id) {
	return moleList[id];
}



void Field::tick() {
	if (moleCount > 0) {
		for (int i = 0; i < moleCount; i++)
			moleList[i]->tick();
		dachaMan->tick();
	}
}

void Field::deleteMole(Mole* mole) {
	int id;
	for (int i = 0; i < moleCount; i++) {
		if (moleList[i] == mole) {
			id = i;
			break;
		}
	}
	for (int i = id; i < moleCount - 1; i++) {
		moleList[i] = moleList[i + 1];
	}
	;
	moleList[--moleCount] = NULL;
	delete(mole);
}

void Field::addMole(Mole* mole) {
	moleList[moleCount++] = mole;
	mole->setField(this);
}

Mole* Field::getMoleThere(int x, int y) {
	for (int i = 0; i < moleCount; i++) {
		if (round(moleList[i]->getPosX()) == x && round(moleList[i]->getPosY()) == y)
			return moleList[i];
	}
	return NULL;
}

bool Field::isDachaManThere(int x, int y) {
	return
		round(dachaMan->getPosX()) == x && round(dachaMan->getPosY()) == y;
}

int Field::getCellValue(int cellX, int cellY) {
	return cells[cellY][cellX];
}
void Field::cellDecrease(int cellX, int cellY) {
	if (cells[cellY][cellX] > 0)
		cells[cellY][cellX]--;
}

int Field::getTotalCellsValue() {
	int res = 0;
	for (int i = 0; i < cellsHeight; i++)
		for (int j = 0; j < cellsWidth; j++)
			res += cells[i][j];
	return res;
}

int Field::whoIsWinner() {
	if (moleCount == 0)
		return 1;
	else {
		int sum = 0;
		for (int i = 0; i < cellsHeight; i++) {
			for (int k = 0; k < cellsWidth; k++) {
				sum += cells[i][k];
			}
		}
		if (sum <= 0)
			return 2;
	}
	return 0;
}
