#ifndef _REPLAY_H_
#define _REPLAY_H_
#include <map>
#include <list>
#include "Numbers.h"
#include "Point.h"
using namespace std;

class Replay
{
	list<Numbers> numsRep;
	list<Point> reviveRep;
	map<int, char> keyPressedRep;
	int repCounter;
	int numsLeft; // How many numbers left from last mission.
	bool replayMode = false;
	int currMission;

public:
	Replay() : repCounter(0), numsLeft(0), replayMode(false), currMission(-1){}
	void resetReplay();
	list<Numbers>& getNumsRep() { return numsRep; }
	list<Point>& getReviveRep() { return reviveRep; }
	map<int, char>& getKeyPressedRep() { return keyPressedRep; }
	int& getRepCounter() { return repCounter; }
	int getNumsLeft() { return numsLeft; }
	void setNumsLeft(int _numsLeft) { numsLeft = _numsLeft; }
	bool isReplayOn() { return replayMode; }
	void setReplayMode(bool mode) { replayMode = mode; }
	void setCurrMission(int _currMission) { currMission = _currMission; }
};
#endif // !_REPLAY_H_
