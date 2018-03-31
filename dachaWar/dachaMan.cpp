#include "stdafx.h"
#include "dachaWarClasses.h"
#include "consts.h"
#include <math.h>

DachaMan::DachaMan(double x, double y, double hitRadius, double speed)
{
	this->posX = x;
	this->posY = y;
	this->hitRadius = hitRadius;
	this->speed = speed;
}


DachaMan::~DachaMan()
{
}

void DachaMan::tick() {
	int field_height = field->getCellsHeight() * Consts::instance().pixelsInCell;
	int field_width = field->getCellsWidth() * Consts::instance().pixelsInCell;
	double minRange = sqrt(field_height*field_height + field_width * field_width), minDistX, minDistY;
	Mole* minMole = NULL;
	double range, distX, distY, cosAlpha, sinAlpha, speedX, speedY;

	/*get closest mole*/
	for (int i = 0; i < field->getMoleCount(); i++) {
		//if (field->getMole(i)->isOnGround()) {
			distX = field->getMole(i)->getPosX() - getPosX();
			distY = field->getMole(i)->getPosY() - getPosY();

			range = sqrt(distX*distX + distY * distY);
			if (range < minRange) {
				minRange = range;
				minMole = field->getMole(i);
				minDistX = distX;
				minDistY = distY;
			}
		//}
	}
	/*if mole is not within hit radius*/
	if (minMole != NULL) {
		if (minRange > hitRadius) {
			/*calculate x and y speed projections*/
			cosAlpha = distX / minRange;
			sinAlpha = distY / minRange;
			speedX = speed * cosAlpha;
			speedY = speed * sinAlpha;
			/*moving dacha man*/
			posX += speedX;
			posY += speedY;
		}
		/*hit the mole if it is within hit radius*/
		else {
			field->deleteMole(minMole);
		}
	}
}

double DachaMan::getPosX() {
	return posX;
}

double DachaMan::getPosY() {
	return posY;
}

void DachaMan::setField(Field* field) {
	this->field = field;
}