
#include <Windows.h>
#include <math.h>
#include "Game.h"
#include "Logs.h"
#include "Bot.h"

#define sqr(x) ((x)*(x))

Player* player = (Player*)0xB7CD98; //0xB7CD98
float* CameraYaw = (float*)0xB6F258;

bool IsActivateBot = false;
bool IsKeyDown_W = false;
bool IsKeyDown_Space = false;

WAYPOINT wp[50];
int wpCount = 4;
int wpCurrent = 4;
bool wpDirectSelect = false;

WAYPOINT MAIN_CENTER;
WAYPOINT START;


void Init()
{
	MAIN_CENTER.X = -1839.14;
	MAIN_CENTER.Z = -1630.53;

	START.X = -1108.26;
	START.Z = 1067.84;

	wp[0].X = -1866.97;
	wp[0].Z = -1612.49;

	wp[1].X = -1853.4230;
	wp[1].Z = -1629.0076;

	wp[2].X = -1821.4504;
	wp[2].Z = -1649.8788;

	wp[3].X = -1810.04;
	wp[3].Z = -1655.91;
}

bool Bot::Update()
{
	if (player)
	{
		// Запись информации
		if (GetAsyncKeyState(VK_F11)&1)
		{
			LogPoint(player->cped->pos);

			/*Log((char*)0x409D97F);
			Log("PLAYER COORDS");
			Log("X="); LogFloat(player->cped->pos->X);
			Log("Z="); LogFloat(player->cped->pos->Z);
			Log("Anim="); LogBYTE(player->cped->Anim);*/
		}

		// ТЕЛЕПОРТ!!!
		if (GetAsyncKeyState(VK_F10)&1)
		{
			player->cped->pos->X = wp[2].X;
			player->cped->pos->Y = 21.7500;
			player->cped->pos->Z = wp[2].Z;
		}

		// Расстояние до шахты
		float centerDist = GetDistance(MAIN_CENTER);

		if (centerDist > 150)
		{
			if (IsActivateBot || IsKeyDown_W || IsKeyDown_Space) DisableBot();
		}
		else
		{
			if (GetAsyncKeyState(VK_F12)&1)
			{
				if (!IsActivateBot)
				{
					IsActivateBot = true;
				}
				else
				{
					DisableBot();
				}
			}

			if (IsActivateBot)
			{
				float dist = GetDistance(w);

				if (dist > 0.5f)
				{
					float tx, tz;

					tx = player->cped->pos->X - w.X;
					tz = player->cped->pos->Z - w.Z;

					angle = atan2(tz, tx);	// Fuck EAAAHHH!!!!! =)

					if (*CameraYaw < angle) *CameraYaw += 0.00002f;
					else if (*CameraYaw > angle) *CameraYaw -= 0.00002f;
					else *CameraYaw = angle;

					if (*CameraYaw > 3.14f || *CameraYaw < -3.14f) *CameraYaw = -*CameraYaw;

					if (!IsKeyDown_W) { keybd_event('W',0,0,0); IsKeyDown_W = true; } // Нажали W
					if (!IsKeyDown_Space && wpDirectSelect && dist > 10.0f) { keybd_event(VK_SPACE,0,0,0); IsKeyDown_Space = true; } // Нажали Пробел

					if (IsKeyDown_Space && dist < 10.0f && wpCurrent == wpCount) { keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0); IsKeyDown_Space = false; } // Отпустили Пробел
				}
				else
				{
					if (IsKeyDown_W) { keybd_event('W',0,KEYEVENTF_KEYUP,0); IsKeyDown_W = false; } // Отпустили W

					if (wpDirectSelect) 
					{
						wpCurrent++;
						if (wpCurrent > wpCount)
						{
							if (IsKeyDown_W) { keybd_event('W',0,KEYEVENTF_KEYUP,0); IsKeyDown_W = false; } // Отпустили W
							Sleep(12000);
							if (!IsKeyDown_W) { keybd_event('W',0,0,0); IsKeyDown_W = true; } // Нажали W

							wpCurrent--; wpDirectSelect = false;
						}
					}
					else
					{
						wpCurrent--;
						if (wpCurrent < 1)
						{
							if (IsKeyDown_W) { keybd_event('W',0,KEYEVENTF_KEYUP,0); IsKeyDown_W = false; } // Отпустили W
							Sleep(1000);
							if (!IsKeyDown_W) { keybd_event('W',0,0,0); IsKeyDown_W = true; } // Нажали W

							wpCurrent++; wpDirectSelect = true; count++;
						}
					}

					if (count < 2)
						w = wp[wpCurrent - 1];
					else
						w = START;
				}
			}
		}

		// Отключение чита
		if (GetAsyncKeyState(VK_END))
		{
			DisableBot();
			ExitThread(0);
			return false;
		}
	}

	return true;
}

void Bot::FindPoint(WAYPOINT target)
{
	float dist, w_dist;
	float minDist = 150.0f;
	float w_minDist = 150.0f;
	WAYPOINT minW = { };
	
	for (int i=0; i<wpCount; i++)
	{
		dist = GetDistance(wp[i]);
		w_dist = GetDistanceFrom(wp[i], target);

		if (dist < minDist && w_dist < w_minDist)
		{
			minW = wp[i];
			minDist = dist;
			w_minDist = w_dist;
		}
	}

	w = minW;
}

Bot::Bot()
{
	angle = 0.0f;	// Угол поворота
	count = 0;		// Кол-во кругов

	w = wp[wpCurrent - 1];
}

Bot::~Bot()
{
	DisableBot();
}

void DisableBot()
{
	IsActivateBot = false;

	if (IsKeyDown_W) { keybd_event('W',0,KEYEVENTF_KEYUP,0); IsKeyDown_W = false; } // Отпустили W
	if (IsKeyDown_Space) { keybd_event(VK_SPACE,0,KEYEVENTF_KEYUP,0); IsKeyDown_Space = false; } // Отпустили Пробел
}

float GetDistance(WAYPOINT wp)
{
	return sqrt(sqr(player->cped->pos->X - wp.X) + sqr(player->cped->pos->Z - wp.Z));
}

float GetDistanceFrom(WAYPOINT start, WAYPOINT finish)
{
	return sqrt(sqr(start.X - finish.X) + sqr(start.Z - finish.Z));
}