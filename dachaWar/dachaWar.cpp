// dachaWar.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include "dachaWarClasses.h"
#include "drawer.h"
#include <random>
#include <ctime>

using namespace std;

int main()
{
	while (true) {
		srand(time(0));

		DachaMan* dachaMan = new DachaMan(15, 15, 2, 0.38);

		Mole* moles[6];
		moles[0] = new MaleMole(1, 2);
		moles[1] = new MaleMole(50, 2);
		moles[2] = new FemaleMole(10, 20);
		moles[3] = new FemaleMole(48, 4);
		moles[4] = new MaleMole(16, 12);
		moles[5] = new MaleMole(42, 6);

		Field* field = new Field(6, 3, moles, 6, dachaMan);
		Drawer::draw(field);
		while (!field->whoIsWinner()) {
			field->tick();
			Drawer::draw(field);
			//for (int i = 0; i < 1000000000; i++);
		}

		cout << "Winner: ";
		if (field->whoIsWinner() == 1)
			cout << "Dacha man";
		else
			cout << "Moles    ";

		delete dachaMan;
		delete field;

		cin.ignore();
		cin.ignore();
	}
	return 0;
}

