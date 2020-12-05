
class Bot;

struct WAYPOINT
{
	float X, Z;
};

enum BOTSTATE
{
	РАБОТА,
	СТАРТ,
	ФИНИШ
};

class Bot
{
public:
	WAYPOINT w;	// Текущая цель
	BOTSTATE state;	// Состояние бота (Работа, Начало, Завершение)

	float angle;	// Угол поворота
	int count; // Кол-во кругов

	Bot();
	~Bot();

	bool Update();		// Обновление бота, если возвращаемое значение равно false, то отключаем чит
	void FindPoint(WAYPOINT target);	// Поиск ближайшей точки
};

void Init();
void DisableBot();
float GetDistance(WAYPOINT wp);
float GetDistanceFrom(WAYPOINT start, WAYPOINT finish);
float GetDirectX(WAYPOINT wp);
float GetDirectZ(WAYPOINT wp);