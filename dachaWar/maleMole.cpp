#include "stdafx.h"
#include "dachaWarClasses.h"
#include <math.h>
#include "consts.h"
#include <random>

MaleMole::MaleMole(double x, double y) : Mole(x, y)
{

}


MaleMole::~MaleMole()
{
}

void MaleMole::tick() {
	bool willChangeState = false;

	if (birthTimeCount > 0) {
		if (birthTimeCount <= Consts::instance().maleMolesBirthTime)
			birthTimeCount++;
		else {
			birthTimeCount = 0;
		}
	}
	else {

		if ((rand() % 101) <= Consts::instance().moleToGroundPercent) {
			onGround = true;
		}

		if (isOnGround()) {
			tryDamageCrop();
		}
		if (!isOnGround()) {
			FemaleMole* female = getClosestFemale();
			if (female != NULL) {
				double distX = female->getPosX() - getPosX();
				double distY = female->getPosY() - getPosY();
				double range = sqrt(distX*distX+distY*distY);
				double cosAlpha = distX / range;
				double sinAlpha = distY / range;
				double  speedX = speed * cosAlpha;
				double speedY = speed * sinAlpha;
				posX += speedX;
				posY += speedY;
			}
			else
			randomMovement();
		}

		checkCollision();
	}
}


void MaleMole::checkCollision() {
	if (!wasChild) {
		double distX;
		double distY;
		double range;
		FemaleMole* female;

		for (int i = 0; i < field->getMoleCount(); i++) {
			female = dynamic_cast<FemaleMole*>(field->getMole(i));
			if (female != nullptr && !female->checkWasChild()) {
				distX = posX - female->getPosX();
				distY = posY - female->getPosY();
				range = sqrt(distX*distX + distY * distY);
				if (range < Consts::instance().moleBirthRange) {
					goUnderground();
					birthTimeCount = 1;
					wasChild = true;
					female->startBirthProcess();
				}
			}
		}
	}
}

FemaleMole* MaleMole::getClosestFemale() {
	int field_height = field->getCellsHeight() * Consts::instance().pixelsInCell;
	int field_width = field->getCellsWidth() * Consts::instance().pixelsInCell;
	double minRange = sqrt(field_height*field_height + field_width * field_width), minDistX, minDistY;
	FemaleMole* minMole = NULL;
	double range, distX, distY;
	FemaleMole* current;

	for (int i = 0; i < field->getMoleCount(); i++) {
		current = dynamic_cast<FemaleMole*>(field->getMole(i));

		if (current != nullptr && !current->checkWasChild()) {
			distX = current->getPosX() - getPosX();
			distY = current->getPosY() - getPosY();

			range = sqrt(distX*distX + distY * distY);
			if (range < minRange) {
				minRange = range;
				minMole = current;
				minDistX = distX;
				minDistY = distY;
			}
			
		}
	}

	return minMole;
}