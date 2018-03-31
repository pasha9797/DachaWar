#include "stdafx.h"
#include "dachaWarClasses.h"
#include <random>
#include <random>
#include "consts.h"

FemaleMole::FemaleMole(double x, double y) : Mole(x, y)
{
}

FemaleMole::~FemaleMole()
{
}

void FemaleMole::tick() {
	bool willChangeState = false;


	if (birthTimeCount > 0) {
		if (birthTimeCount <= Consts::instance().femaleMolesBirthTime) {
			if(birthTimeCount==Consts::instance().childCreationTime)
				giveBirth();
			birthTimeCount++;
		}
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
			randomMovement();
		}
	}
}

void FemaleMole::startBirthProcess() {
	birthTimeCount = 1;
	goUnderground();
	wasChild = true;
}

void FemaleMole::giveBirth() {
	int gender = rand() % 2;
	if (gender == 0)
		field->addMole(new MaleMole(posX, posY));
	else
		field->addMole(new FemaleMole(posX, posY));
}

bool FemaleMole::checkWasChild() {
	return wasChild;
}
