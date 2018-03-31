#pragma once
class Consts
{
public:
	const int startCellValue = 9;
	const int pixelsInCell = 10;
	const int moleToGroundPercent = 10;
	const int moleMaxTimeOnGround = 10;
	const double moleMaxSpeed = 0.9;
	const double moleMinSpeed = 0.2;
	const double moleBirthRange = 2;
	const int maleMolesBirthTime=15;
	const int femaleMolesBirthTime = 15;
	const int childCreationTime = 8;

	static Consts& instance()
	{

		static Consts s;
		return s;
	}

private:
	Consts() {  }  
	~Consts() {  } 

						
	Consts(Consts const&) = delete;
	Consts& operator= (Consts const&) = delete;

};

