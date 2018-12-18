#ifndef _SNAKES_GAME_H_
#define _SNAKES_GAME_H_

#include "Utilities.h"
#include <iostream>
#include <typeinfo>
#include "Snake.h"
#include "Board.h"
#include "Colors.h"
#include "Missions.h"
#include <Windows.h>
#include <conio.h>
#include "Creature.h"
#include <type_traits>
#include <algorithm>
#include "Replay.h"
using namespace std;

enum KEYS { ESC = 27 };
enum {INIT_SIZE = 3};

extern bool isSnakePaused[2];
class Game
{
	enum { size = 2, CREAT_SIZE = 5};
	Missions mission;
	Board board;
	NumsOnScreen nums;
	Creature* creature[CREAT_SIZE];
	int activeMissions[NUM_OF_MISSIONS] = {};
	int activeMissionCount = 0;
	Replay gameReplay;
	Snake snakes[size] =
	{
		{ { 10, 9 }, '@',INIT_SIZE , Direction::RIGHT, CYAN, 'z' }, // snake 1
		{ { 70, 9 }, '#', INIT_SIZE, Direction::LEFT, LIGHTMAGENTA, 'n' } // snake 2
	};

public:
	//Game related methods
	Game();
	void resetGame();
	void run(bool& run);
	void generalUpdates(Point& leftDigPos);
	NumsOnScreen& getNums() { return nums; }
	void printAndSetNumOnBoard(int num, int x, int y);
	void prepareToContinue();
	void endOfGame(int i, bool& go);
	~Game();
	//Snake related methods
	void setSnakesOnBoard();
	bool checkIfCrashed(Snake & snake, char keyPressed, bool& inNumEater);
	void checkNextSnakeMove(int x, int y, int index, bool& inSnake, bool& inNumEater);
	bool isSnakeInLoop(Snake& snake);
	void resetSnake(Snake& snake);
	void resetLoop(bool* snakeLoop);
	void updateSnakeOnBoard(Snake & snake, Snake & updateSnake);
	void checkOppositeDir(Snake& snake, char& keyPressed);
	void afterEatingUpdates(bool isGoodNum, int index, int currNum);
	void printScoreAndAmmu(Snake & snake);
	void printHelper(int x, int y, Snake& snake);
	Snake getSnake(int index) { return snakes[index]; }
	void revive(Snake& snake);
	void setSnakeHead(Point head, int i);
	//Creatures and Bullets related methods
	void setCreaturesOnBoard();
	void afterShootingUpdates(const int& i, int& top);
	void objectInNumber(Point& pos, string str, bool& restartMission);
	void objectInSnake(int hurtedSnake, int snakeIndex, string str);
	int objectInbullet(Point& secondBulletPos);
	void bulletSwap(Bullet& b1, Bullet& b2);
	bool bulletCrash(Bullet& bullet, int snakeIndex);
	bool objectCrashUpdates(char ch, Point& futurePoint, Point& currPoint, int& snakeIndex, string str, bool& restartMission);
	void numEaterInSnake(bool& restartMission, int hurtedSnake);
	void deleteBullet(Bullet& bullet, int snakeIndex);
	void findAndDeleteFly(Point& point);
	void nextFlyMove(int snakeIndex, int creatureIndex);
	void nextNumEaterMove(int snakeIndex, bool& restartMission, Point& pos);
	void getNewNumEaterDestination();
	void setDistanceAndDestination(int x, int y);
	unsigned int checkDistanceX(int xEater, int xDest, Direction& dirX);
	void calcDistanceAndDirection(int coord1, int coord2, Direction dir, int max_margin, int min_margin, unsigned int& finalDistance, Direction& finalDir);
	unsigned int checkDistanceY(int yEater, int yDest, Direction& dirY);
	void resetBullets();
	void clearCreatures();
	void resetCreatures();
	void resetNumEater();
	//Missions related methods
	int& getActiveMissionCount() { return activeMissionCount; }
	void setActiveMissions(int* missionsArr);
	int* getActiveMissions() { return activeMissions; }
	//Replay related methods
	void insertRemainedNums();
	void showRemainedNums();
	void setNumsForReplay(int i);
	Replay& getReplay() { return gameReplay; }
	void firstReplayActs(bool& firstTurn);
};

#endif