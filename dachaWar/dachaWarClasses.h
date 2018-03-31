#pragma once

class DachaMan;
class Mole;
class MaleMole;
class FemaleMole;

class Field
{
private:
	DachaMan *dachaMan;
	int cellsWidth, cellsHeight;
	Mole **moleList;
	int moleCount;
	int ** cells;

public:
	int getCellsWidth();
	int getCellsHeight();
	void tick();
	int getMoleCount();
	Mole* getMoleThere(int x, int y);
	Mole* getMole(int id);
	bool isDachaManThere(int x, int y);
	int getCellValue(int cellX, int cellY);
	int getTotalCellsValue();
	void cellDecrease(int cellX, int cellY);
	int whoIsWinner();
	void deleteMole(Mole* mole);
	void addMole(Mole* mole);

public:
	Field(int width, int height, Mole* moles[], int cur_moles_count, DachaMan* dachaMan);
	~Field();
};

class DachaMan
{
private:
	double posX, posY;
	double hitRadius;
	double speed;
	Field* field;

public:
	void tick();
	double getPosX();
	double getPosY();
	void setField(Field* field);

public:
	DachaMan(double x, double y, double hitRadius, double speed);
	~DachaMan();
};

class Mole
{
protected:
	double posX, posY;
	bool onGround;
	bool wasChild;
	Field* field;
	int onGroundCount;
	int birthTimeCount;
	double shiftX, shiftY;
	double speed;

public:
	virtual void tick();
	void randomMovement();
	void tryDamageCrop();
	double getPosX();
	double getPosY();
	bool isOnGround();
	void goOnGround();
	void goUnderground();
	void setField(Field* field);

public:
	Mole(double x, double y);
	virtual ~Mole() = 0 {};
};

class FemaleMole :
	public Mole
{
private:

	void giveBirth();

public:
	FemaleMole(double x, double y);
	~FemaleMole();

	void tick();
	void startBirthProcess();
	bool checkWasChild();
};

class MaleMole :
	public Mole
{
private:

	FemaleMole* getClosestFemale();

public:
	MaleMole(double x, double y);
	~MaleMole();

	void tick();
	void checkCollision();
};
