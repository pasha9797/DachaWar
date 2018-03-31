#include "stdafx.h"
#include "dachaWarClasses.h"
#include <random>
#include "consts.h"

Mole::Mole(double x, double y)
{
	this->posX = x;
	this->posY = y;
	onGround = false;
	onGroundCount = 0;
	birthTimeCount = 0;	
	wasChild = false;

	shiftX = Consts::instance().moleMinSpeed + (double(rand() % 101) / 100)*(Consts::instance().moleMaxSpeed - Consts::instance().moleMinSpeed);
	shiftY = Consts::instance().moleMinSpeed + (double(rand() % 101) / 100)*(Consts::instance().moleMaxSpeed - Consts::instance().moleMinSpeed);

	speed = sqrt(shiftX*shiftX + shiftY* shiftY)/2;
}

void Mole::tick() {};

void Mole::randomMovement() {
	double newPosX = posX + shiftX;
	double newPosY = posY + shiftY;

	if (newPosX < (field->getCellsWidth() - 1)*Consts::instance().pixelsInCell && newPosX >= 0)
		posX += shiftX;
	else
		shiftX = -shiftX;
	if (newPosY < (field->getCellsHeight() - 1)*Consts::instance().pixelsInCell && newPosY >= 0)
		posY += shiftY;
	else
		shiftY = -shiftY;
}

void Mole::tryDamageCrop() {
	int moleCellX = round(posX / Consts::instance().pixelsInCell);
	int moleCellY = round(posY / Consts::instance().pixelsInCell);

	field->cellDecrease(moleCellX, moleCellY);

	onGroundCount++;
	if (onGroundCount >= Consts::instance().moleMaxTimeOnGround || field->getCellValue(moleCellX, moleCellY) == 0) {
		onGround = false;
		onGroundCount = 0;
	}
}

double Mole::getPosX() {
	return posX;
}

double Mole::getPosY() {
	return posY;
}


bool Mole::isOnGround() {
	return onGround;
}

void Mole::goOnGround() {
	onGround = true;
}

void Mole::goUnderground() {
	onGround = false;
}

void Mole::setField(Field* field) {
	this->field = field;
}

