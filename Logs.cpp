#include <Windows.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "Game.h"
#include "Logs.h"

using namespace std;

char* GetTime();

void Log(char* msg)
{
	ofstream file("C:/MainHack_log.txt", ios::app);
	file << "[" << GetTime() << "]: " << msg << endl;
	file.close();
}

void LogInt(int msg)
{
	ofstream file("C:/MainHack_log.txt", ios::app);
	file << "[" << GetTime() << "]: " << msg << endl;
	file.close();
}

void LogFloat(float msg)
{
	ofstream file("C:/MainHack_log.txt", ios::app);
	file << "[" << GetTime() << "]: " << msg << endl;
	file.close();
}

void LogBYTE(BYTE msg)
{
	ofstream file("C:/MainHack_log.txt", ios::app);
	file << "[" << GetTime() << "]: " << (int)msg << endl;
	file.close();
}

void LogPoint(Coords* pos)
{
	ofstream file("C:/MainHack_log.txt", ios::app);
	file << "wp[].X = " << pos->X << ";" << endl;
	file << "wp[].Z = " << pos->Z << ";" << endl;
	file << endl;
	file.close();
}

char* GetTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,80,"%X",timeinfo);
    puts (buffer);

	return buffer;
}