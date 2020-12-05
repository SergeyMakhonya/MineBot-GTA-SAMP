//Generated using ReClass 2011 by DrUnKeN ChEeTaH

class Player;
class CPed;
class Coords;

class Player
{
public:
	CPed* cped; //0x0000 
char _0x0004[2108];

};//Size=0x0840

class CPed
{
public:
char _0x0000[20];
	Coords* pos; //0x0014 
char _0x0018[324];
	BYTE Anim; //0x015C 
char _0x015D[983];
	__int32 statusMove; //0x0534 
char _0x0538[8];
	float Life; //0x0540 
	float MaxLife; //0x0544 
	float Shield; //0x0548 
char _0x054C[12];
	float Roll; //0x0558 
char _0x055C[520];
	CPed* KilledBy; //0x0764 
char _0x0768[92];

};//Size=0x07C4

class Coords
{
public:
char _0x0000[48];
	float X; //0x0030 
	float Z; //0x0034 
	float Y; //0x0038 

};//Size=0x003C

extern Player* player;