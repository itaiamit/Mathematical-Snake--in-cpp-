#include "Replay.h"

void Replay::resetReplay()
{
	numsRep.clear();
	reviveRep.clear();
	keyPressedRep.clear();
	repCounter = 0;
	replayMode = false;
	currMission = -1;
}
