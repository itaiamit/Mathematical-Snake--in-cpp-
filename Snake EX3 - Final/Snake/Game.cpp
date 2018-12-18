#include "Game.h"
#include "Snake.h"
#include "Point.h"
#include <math.h>
#include "Numbers.h"
#include <string>
#include "ScondaryMenu.h"
#include "MainMenu.h"

bool isSnakePaused[2] = { false, false };

Game::Game()
{
	srand(time(NULL));
	snakes[0].setKeys('a', 'd', 'w', 'x');
	snakes[1].setKeys('j', 'l', 'i', ',');
	creature[0] = new rowFlies(Point(30, 23), RIGHT, true);
	creature[1] = new rowFlies(Point(50, 15), LEFT, false);
	creature[2] = new colFlies(Point(45, 23), UP, true);
	creature[3] = new colFlies(Point(55, 15), DOWN, false);
	creature[4] = new numEater(Point(10, 19), RIGHT, true);
}

void Game::setActiveMissions(int * missionsArr)
{
	for (int i = 0; i < activeMissionCount; i++)
		activeMissions[i] = missionsArr[i];
}

// Inserts the numbers that have remained from the last mission to the Replay-Numbers storage.
void Game::insertRemainedNums()
{
	for (int i = 0; i < nums.getHowMany(); i++)
		gameReplay.getNumsRep().push_back(nums.getNumberByIndex(i));
}

// Shows the numbers that have remained from the last mission.
void Game::showRemainedNums()
{
	for (int i = 0; i < gameReplay.getNumsLeft(); i++)
		setNumsForReplay(i);
}

void Game::setNumsForReplay(int i)
{
	int currNum = gameReplay.getNumsRep().begin()->num;
	int x = gameReplay.getNumsRep().begin()->x;
	int y = gameReplay.getNumsRep().begin()->y;
	bool isGoodNum = gameReplay.getNumsRep().begin()->goodNum;

	nums.setNum(nums.getNumbersArray(), i, currNum, x, y, isGoodNum);
	printAndSetNumOnBoard(currNum, x, y);

	if (isGoodNum && !((numEater*)creature[4])->getDisappeared())
		setDistanceAndDestination(x, y);

	gameReplay.getNumsRep().erase(gameReplay.getNumsRep().begin());
}

void Game::firstReplayActs(bool& firstTurn)
{
	getReplay().setReplayMode(true);
	board.clearSnakesBoard();

	if (firstTurn)
	{
		resetCreatures();
		::isSnakePaused[0] = false;
		::isSnakePaused[1] = false;
	}

	setCreaturesOnBoard();
	showRemainedNums();

	for (int i = 0; i < size; i++)
	{
		if (!gameReplay.getReviveRep().empty())
		{
			list<Point>::iterator it = gameReplay.getReviveRep().begin();
			Point p = { it->getX() ,it->getY() , it->getDirX() ,it->getDirY() };
			if (it != gameReplay.getReviveRep().end() && it->getX() != -1)
			{
				setSnakeHead(p, i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakes[i].getColor() | FOREGROUND_INTENSITY);
				snakes[i].getSnakesBodyPart(HEAD).draw(snakes[i].getChar());
				for (int j = 1; j < snakes[i].currLen; ++j)
				{
					snakes[i].getSnakesBodyPart(j) = snakes[i].getSnakesBodyPart(j - 1);
					snakes[i].getSnakesBodyPart(j).draw(snakes[i].getChar());
				}
			}
			snakes[i].setDirestion(snakes[i].getSnakesBodyPart(HEAD).getDir());
			gameReplay.getReviveRep().push_back(p);
			gameReplay.getReviveRep().pop_front();
			if (gameReplay.getReviveRep().size() == 1)
				break;
		}
	}

	resetBullets();
	setSnakesOnBoard();
}

void Game::resetGame()
{
	clrscr();
	snakes[0].setKeys('a', 'd', 'w', 'x');
	snakes[0].resetSnake({ 10, 9 }, '@', INIT_SIZE, Direction::RIGHT, CYAN, 'z');
	snakes[0].setPaused(0);
	::isSnakePaused[0] = false;

	snakes[1].setKeys('j', 'l', 'i', ',');
	snakes[1].resetSnake({ 70, 9 }, '#', INIT_SIZE, Direction::LEFT, LIGHTMAGENTA, 'n');
	snakes[1].setPaused(0);
	::isSnakePaused[1] = false;

	board.setBoard();
	board.displayBoard();
	setSnakesOnBoard();
	gameReplay.getReviveRep().push_back(snakes[0].getSnakesBodyPart(HEAD)); gameReplay.getReviveRep().begin()->changeDir(RIGHT);
	gameReplay.getReviveRep().push_back(snakes[1].getSnakesBodyPart(HEAD)); gameReplay.getReviveRep().rbegin()->changeDir(LEFT);
	resetCreatures();
	setCreaturesOnBoard();
	resetBullets();
	nums.resetAll();
	mission.makeNewMission(activeMissions, activeMissionCount);
	gameReplay.setCurrMission(mission.getCurrMission());
}

// Sets snakes on board for the first time.
void Game::setSnakesOnBoard()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < snakes[i].currLen; j++)
		{
			Point p = snakes[i].getSnakesBodyPart(j);
			board.setDigit(p.getY(), p.getX(), snakes[i].getChar());
		}
}

void Game::setCreaturesOnBoard()
{
	for (int i = 0; i < CREAT_SIZE; i++)
		creature[i]->printCreature(board);
}

// Checks if a snake crashed himself or into another snake.
bool Game::checkIfCrashed(Snake &snake, char keyPressed, bool& inNumEater)
{
	Point pos = snake.getSnakesBodyPart(HEAD);
	int index = snake.getSnakeIndex();
	bool inSnake = false;

	checkOppositeDir(snake, keyPressed);
	snake.changeDir(keyPressed);

	switch (snake.getDirection())
	{
	case LEFT:
		checkNextSnakeMove(pos.getX() - 1, pos.getY(), index, inSnake, inNumEater);
		break;

	case RIGHT:
		checkNextSnakeMove(pos.getX() + 1, pos.getY(), index, inSnake, inNumEater);
		break;

	case UP:
		checkNextSnakeMove(pos.getX(), pos.getY() - 1, index, inSnake, inNumEater);
		break;

	case DOWN:
		checkNextSnakeMove(pos.getX(), pos.getY() + 1, index, inSnake, inNumEater);
		break;
	}

	return inSnake;
}

void Game::checkNextSnakeMove(int x, int y, int index, bool& inSnake, bool& inNumEater)
{
	if (board.isSnakesChar(y, x))
		inSnake = true;

	else if (board.getChar(y, x) == '%')
		inNumEater = true;

	else if (board.getChar(y, x) == '$' || board.getChar(y, x) == '!')
	{
		::isSnakePaused[index] = true;
		snakes[index].disappear(board);
	}
}

// Checks if a the pressed key (direction) is opposite from current direction.
void Game::checkOppositeDir(Snake& snake, char& keyPressed)
{
	switch (keyPressed)
	{
	case 'w':
		if (snake.getDirection() == DOWN)
			keyPressed = 'x';
		break;
	case 'i':
		if (snake.getDirection() == DOWN)
			keyPressed = ',';
		break;

	case 'x':
		if (snake.getDirection() == UP)
			keyPressed = 'w';
		break;
	case ',':
		if (snake.getDirection() == UP)
			keyPressed = 'i';
		break;

	case 'd':
		if (snake.getDirection() == LEFT)
			keyPressed = 'a';
		break;
	case 'l':
		if (snake.getDirection() == LEFT)
			keyPressed = 'j';
		break;

	case 'a':
		if (snake.getDirection() == RIGHT)
			keyPressed = 'd';
		break;
	case 'j':
		if (snake.getDirection() == RIGHT)
			keyPressed = 'l';
		break;
	}
}

// Checks if snake has gotten into a loop with himself.
bool Game::isSnakeInLoop(Snake& snake)
{
	Point head = snake.getSnakesBodyPart(HEAD);
	char ch = snake.getChar();

	if (board.getDigit(head.getY() - 1, head.getX()) == ch)
		if (board.getDigit(head.getY() + 1, head.getX()) == ch)
			if (board.getDigit(head.getY(), head.getX() - 1) == ch)
				if (board.getDigit(head.getY(), head.getX() + 1) == ch)
					return true;

	return false;
}

// Resets a snake after he has got into a loop with himself.
void Game::resetSnake(Snake& snake)
{
	for (int i = snake.currLen - 1; i > 0; i--)
	{
		snake.getSnakesBodyPart(i) = snake.getSnakesBodyPart(HEAD);
		snake.getSnakesBodyPart(i).draw(' ');
	}
}

void Game::resetLoop(bool * snakeLoop)
{
	snakeLoop[0] = false;
	snakeLoop[1] = false;
}

// Updates board with the new locations of the snakes. 
void Game::updateSnakeOnBoard(Snake &snake, Snake &updateSnake)
{
	for (int i = 0; i < snake.currLen; i++)
		board.setDigit(snake.getSnakesBodyPart(i).getY(), snake.getSnakesBodyPart(i).getX(), ' ');
	for (int i = 0; i < updateSnake.currLen; i++)
		board.setDigit(updateSnake.getSnakesBodyPart(i).getY(), updateSnake.getSnakesBodyPart(i).getX(), updateSnake.getChar());
}

void Game::run(bool& run)
{
	bool go = true;
	bool pausedSaver0 = ::isSnakePaused[0], pausedSaver1 = ::isSnakePaused[1] ;
	char eatenNum, ch;
	int stepsCounter = 0, stepsCounterSaver = 0, replayCounter = 0, currNum, fx, fy, index, ammu;
	bool isGoodNum, isFirst = false, isCrashed = false, restartMission = false, inNumEater = false, firstTurn = true;
	Point pos[size] = { snakes[0].getSnakesBodyPart(HEAD) ,snakes[1].getSnakesBodyPart(HEAD) };
	Point leftDigPos, destination;
	bool snakeLoop[size] = { false, false };
	char keyPressed = 0;
	resetGame();

	nums.numbersLottery(board, pos, mission.getCurrMission(), &currNum, &fx, &fy);
	isGoodNum = mission.checkNumber(currNum);
	nums.setNum(nums.getNumbersArray(), nums.getHowMany(), currNum, fx, fy, isGoodNum);
	gameReplay.getNumsRep().push_back(nums.getNumberByIndex(nums.getHowMany() - 1));
	gameReplay.setNumsLeft(1);
	getNewNumEaterDestination();

	while (go)
	{
		if (_kbhit() && !gameReplay.isReplayOn())
		{
			keyPressed = _getch();

			if (keyPressed == KEYS::ESC)
			{
				PlaySound(TEXT("sfx_sounds_pause1_out.wav"), NULL, SND_SYNC | SND_NODEFAULT);
				SecondaryMenu(mission, board, go, run, firstTurn, *this);
				if (go)
					mission.printMission();
				else
					continue;
				if (gameReplay.isReplayOn())
				{
					stepsCounter = stepsCounterSaver;
					::isSnakePaused[0] = pausedSaver0;
					::isSnakePaused[1] = pausedSaver1;
				}
			}
			else
				gameReplay.getKeyPressedRep()[gameReplay.getRepCounter()] = keyPressed;
		}

		else
			keyPressed = 0;
		
		if (gameReplay.isReplayOn())
		{
			if (!gameReplay.getKeyPressedRep().empty())
			{
				map<int, char>::iterator it = gameReplay.getKeyPressedRep().find(replayCounter);
				if (it != gameReplay.getKeyPressedRep().end() && replayCounter == it->first)
					keyPressed = it->second;

				else if (firstTurn)
				{
					resetNumEater();
					keyPressed = 0;
					firstTurn = false;
				}
				else
					keyPressed = 0;
			}

			if (replayCounter == gameReplay.getRepCounter())
			{
				gameReplay.setReplayMode(false);
				replayCounter = 0;
				stepsCounterSaver = stepsCounter;
				pausedSaver0 = ::isSnakePaused[0];
				pausedSaver1 = ::isSnakePaused[1];
				prepareToContinue();
			}
		}

		Sleep(140);
		printScoreAndAmmu(snakes[0]);
		printScoreAndAmmu(snakes[1]);

		for (int i = 0; i < size; ++i)
		{
			if (!gameReplay.isReplayOn())
				gameReplay.getRepCounter()++;
			else
				replayCounter++;
			Snake tempSnake = snakes[i];
			inNumEater = false;
			isCrashed = checkIfCrashed(snakes[i], keyPressed, inNumEater);
			ammu = snakes[i].getAmmunition();
			int& top = snakes[i].getTop();
			isFirst = false;
			if (keyPressed == snakes[i].getShootKey() && ammu > 0 && !::isSnakePaused[i])
			{
				afterShootingUpdates(i, top);
				isFirst = true;
			}

			// numEater movement loop.
			destination = ((numEater*)creature[4])->getDestination();
			if (destination != Point(-1, -1))
			{
				restartMission = false;
				for (int j = 0; j < 2; j++)
				{
					// numEaterX = destinationX
					if (((numEater*)creature[4])->getPosition().getX() == destination.getX())
					{
						Direction dir = ((numEater*)creature[4])->getDirY();
						creature[4]->setDirection(dir);
						creature[4]->getPosition().changeDir(dir);
					}
					nextNumEaterMove(i, restartMission, leftDigPos);
					if (restartMission) break;
				}
				if (restartMission) continue;
			}
			// Flies movement loop.
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
					nextFlyMove(i, j);

				if (!creature[2 + j]->getDisappeared())
					nextFlyMove(i, 2 + j);
			}

			// Run it twice so the bullet will be twice as fast as the snake.
			for (int k = 0; k < size && top != 0; k++)
				for (int j = 0; j < top; j++)
				{
					bool fCrashed = false, crashed = false, temp = false; // temp is a garbage variable
					Bullet& currBullet = snakes[i].getBullet(j);
					Point p = currBullet.getPosition();
					p.moveImpl();
					ch = board.getChar(p.getY(), p.getX());

					if (isFirst && j == top - 1)
					{
						currBullet.getPosition().moveImpl();
						if (ch != ' ')
						{
							fCrashed = objectCrashUpdates(ch, p, currBullet.getPosition(), i, currBullet.getType(), temp);
							deleteBullet(snakes[i].getBullet(j), j);
						}
						isFirst = false;
					}

					if (!isFirst && !fCrashed)
						crashed = bulletCrash(currBullet, i);
					if (fCrashed)
						deleteBullet(snakes[i].getBullet(j), j);

					if (!crashed && currBullet.getPosition().getX() != -1)
						currBullet.moveBullet(board);
				}

			if (!::isSnakePaused[i])
			{
				if (!isCrashed)
				{
					if (inNumEater)
					{
						numEaterInSnake(restartMission, i);
						generalUpdates(nums.getRandomNumFromArray());
						break;
					}

					// move and check if the snake ate a number
					pos[i] = snakes[i].move(keyPressed);
					eatenNum = board.getDigit(pos[i].getY(), pos[i].getX());

					if (eatenNum != -1) // Ate a number.
					{
						index = i;
						currNum = nums.getNumber(pos[i], board, leftDigPos);
						isGoodNum = mission.checkNumber(currNum);

						if (isGoodNum)
							afterEatingUpdates(isGoodNum, i, currNum);

						else
						{
							afterEatingUpdates(isGoodNum, abs(i - 1), currNum);
							index = abs(i - 1);
						}

						if (snakes[index].currLen == MAX_BODY_SIZE)
						{
							endOfGame(index, go);
							break;
						}

						if (snakeLoop[abs(i - 1)])
						{
							resetSnake(snakes[abs(i - 1)]);
							resetLoop(snakeLoop);
							updateSnakeOnBoard(tempSnake, snakes[abs(i - 1)]);
						}

						generalUpdates(leftDigPos);
						replayCounter = 1;
						stepsCounterSaver = stepsCounter;
					}
					updateSnakeOnBoard(tempSnake, snakes[i]);
				}

				else
					snakeLoop[i] = isSnakeInLoop(snakes[i]);
			}

			if (++stepsCounter == 5)
			{
				if (gameReplay.isReplayOn() && !gameReplay.getNumsRep().empty())
					setNumsForReplay(nums.getHowMany());

				else
				{
					nums.numbersLottery(board, pos, mission.getCurrMission(), &currNum, &fx, &fy);
					isGoodNum = mission.checkNumber(currNum);
					nums.setNum(nums.getNumbersArray(), nums.getHowMany(), currNum, fx, fy, isGoodNum);
					gameReplay.getNumsRep().push_back(nums.getNumberByIndex(nums.getHowMany() - 1));
				}

				stepsCounter = 0;
				if (isGoodNum && !((numEater*)creature[4])->getDisappeared())
					setDistanceAndDestination(fx, fy);

				if (::isSnakePaused[i])
				{
					snakes[i].setPaused(snakes[i].getPaused() + 1);
					if (snakes[i].getPaused() == 5)
					{
						::isSnakePaused[i] = false;
						snakes[i].setPaused(0);
						revive(snakes[i]);
					}
				}
			}

			if (nums.getHowMany() == MAX_NUMS_ON_SCREEN)
			{
				nums.checkAndShowGoodNumbers(nums.getNumbersArray());
				generalUpdates(leftDigPos);
			}
		} // for

		if (snakeLoop[0] && snakeLoop[1]) // if both snake stuck in a loop, restart them.
		{
			for (int i = 0; i < size; i++)
			{
				Snake tempSnake = snakes[i];
				resetSnake(snakes[i]);
				updateSnakeOnBoard(tempSnake, snakes[i]);
			}

			generalUpdates(leftDigPos);
			resetLoop(snakeLoop);
		}

	} // while (go)
}

void Game::afterEatingUpdates(bool isGoodNum, int index, int currNum)
{
	snakes[index].updateSnakeSize(snakes[index].currLen);
	gotoxy(60, 1);
	cout << "                    ";
	gotoxy(0, 1);

	if (isGoodNum) // If it's a good number for the current mission.
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
		cout << "Snake " << snakes[index].getChar() << " got the number: " << currNum << " !";
		PlaySound(TEXT("sfx_coin_double1.wav"), NULL, SND_SYNC | SND_NODEFAULT);
	}

	else // It's not a good number for the current mission.
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
		cout << "Snake " << snakes[abs(index - 1)].getChar() << " collected a wrong number!!! Point goes to snake " << snakes[index].getChar() << ".";
		PlaySound(TEXT("badpoint.wav"), NULL, SND_SYNC | SND_NODEFAULT);
	}

	Sleep(800);
}

void Game::printAndSetNumOnBoard(int num, int x, int y)
{
	string strNum = to_string(num);

	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	// Sets the number on the board.
	for (int j = 0; j < strNum.length(); j++)
	{
		board.setDigit(y, x + j, strNum.at(j));
		cout << board.getDigit(y, x + j);
	}
}

void Game::prepareToContinue()
{
	gotoxy(0, 0);
	cout << BLANK_ROW;
	gotoxy(0, 1);
	cout << BLANK_ROW;
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	cout << "Prepare to continue...";
	for (int i = 0; i < 3; i++)
	{
		PlaySound(TEXT("readySet"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(850);
	}

	PlaySound(TEXT("go"), NULL, SND_ASYNC | SND_NODEFAULT);
	gotoxy(0, 0);
	mission.printMission();
}

void Game::endOfGame(int i, bool& go)
{
	clrscr();
	gotoxy(4, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
	cout << "Congratulations!! snake ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakes[i].getColor());
	cout << snakes[i].getChar();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
	cout << " has won. See you next time ;)" << endl;
	PlaySound(TEXT("endofgame.wav"), NULL, SND_SYNC | SND_NODEFAULT);
	Sleep(1000);
	go = false;
}

// Prints the scrore and ammunition for each snake.
void Game::printScoreAndAmmu(Snake & snake)
{
	if (snake.getChar() == '@')
		printHelper(0, 1, snake);

	else
		printHelper(60, 1, snake);
}

// Helper for "printScoreAndAmmu" method.
void Game::printHelper(int x, int y, Snake & snake)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snake.getColor() | FOREGROUND_INTENSITY);
	gotoxy(x, y);
	cout << "Snake " << snake.getChar() << ": ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << snake.currLen - 3 << ", ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snake.getColor() | FOREGROUND_INTENSITY);
	cout << "Ammu: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	cout << snake.getAmmunition();
}

// General updates after a mission has ended.
void Game::generalUpdates(Point& leftDigPos)
{
	gameReplay.resetReplay();
	nums.updateArray(nums.getHowMany() / 2, leftDigPos);
	gameReplay.setNumsLeft(nums.getHowMany());
	board.clearSnakesBoard();
	nums.printNewArray(board);
	resetBullets();
	resetCreatures();
	setCreaturesOnBoard();
	mission.makeNewMission(activeMissions, activeMissionCount);
	gameReplay.setCurrMission(mission.getCurrMission());
	nums.setGoodNumbers(mission);
	insertRemainedNums();
	getNewNumEaterDestination();
	for(int i = 0; i < size; i++)
		if (!::isSnakePaused[i])
		{
			Point p = snakes[i].getSnakesBodyPart(HEAD);
			gameReplay.getReviveRep().push_back(p);
		}	
}

// Reset ammunition to default.
void Game::resetBullets()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = snakes[i].getTop() - 1; j >= 0; j--)
			deleteBullet(snakes[i].getBullet(j), i);
		snakes[i].updateAmmunition(5);
	}
}

void Game::clearCreatures()
{
	for (int i = 0; i < CREAT_SIZE; i++)
	{
		Point pos = creature[i]->getPosition();
		if (!creature[i]->getDisappeared())
		{
			board.setDigit(pos.getY(), pos.getX(), ' ');
			pos.draw(' ');
		}
	}
}

void Game::resetCreatures()
{
	clearCreatures();

	creature[0]->resetCreature('!', Point(30, 23), RIGHT, LIGHTRED, true);
	creature[1]->resetCreature('!', Point(50, 15), LEFT, LIGHTRED, false);
	creature[2]->resetCreature('$', Point(45, 23), UP, GREEN, true);
	creature[3]->resetCreature('$', Point(55, 15), DOWN, GREEN, false);
	creature[2]->setDisappeared(false);
	creature[3]->setDisappeared(false);
	resetNumEater();
}

void Game::resetNumEater()
{
	findAndDeleteFly(creature[4]->getPosition());
	creature[4]->resetCreature('%', Point(10, 19), RIGHT, YELLOW, true);
	creature[4]->setDisappeared(false);
	((numEater*)creature[4])->setDestination(Point(-1, -1));
	((numEater*)creature[4])->setDirY(Direction(UP));
	((numEater*)creature[4])->setDistance(max_x + max_y);
	int x = creature[4]->getPosition().getX();
	int y = creature[4]->getPosition().getY();
	board.setDigit(y, x, creature[4]->getSign());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), creature[4]->getColor());
	creature[4]->getPosition().draw(creature[4]->getSign());
}

// Shoting updates after the first shot.
void Game::afterShootingUpdates(const int& i, int& top)
{
	PlaySound(TEXT("laser.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
	snakes[i].setFirstBullet(top);
	snakes[i].getBullet(top).updateBulletOnBoard(board);
	snakes[i].updateAmmunition(snakes[i].getAmmunition() - 1);
	snakes[i].setTop(++top);
}

// Deletes a number from the screen in case an object has crashed into it.
void Game::objectInNumber(Point& pos, string str, bool& restartMission)
{
	Point leftDigPos;

	nums.getNumber(pos, board, leftDigPos);

	if (str == "numEater" && leftDigPos == ((numEater*)creature[4])->getDestination())
	{
		gotoxy(0, 1);
		cout << BLANK_ROW;
		gotoxy(0, 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
		cout << "The Number-Eater ate number ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		cout << nums.getNumberByPosition(leftDigPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
		cout << " and was faster than you....";
		PlaySound(TEXT("sfx_coin_double7"), NULL, SND_SYNC | SND_NODEFAULT);
		Sleep(1000);
		gotoxy(0, 1);
		cout << BLANK_ROW;
		nums.deleteNumberFromArray(leftDigPos);
		resetNumEater();
		getNewNumEaterDestination();
	}
	//If the Num-Eater's destination was eaten by another creature.
	else if (leftDigPos == ((numEater*)creature[4])->getDestination())
	{
		nums.deleteNumberFromArray(leftDigPos);
		resetNumEater();
		getNewNumEaterDestination();
	}

	else
		nums.deleteNumberFromArray(leftDigPos);

	pos = leftDigPos;
}

// In case that an object has crashed into a snake.
void Game::objectInSnake(int hurtedSnake, int snakeIndex, string str)
{
	PlaySound(TEXT("explotion.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
	snakes[hurtedSnake].disappear(board);

	if (hurtedSnake != snakeIndex && str == "bullet")
		snakes[snakeIndex].updateAmmunition(snakes[snakeIndex].getAmmunition() + 1);
}

// In case that an object has crashed a bullet.
int Game::objectInbullet(Point& secondBulletPos)
{
	bool found = false;
	int currSnake = 0;

	do
	{
		int top = snakes[currSnake].getTop();
		for (int j = 0; j < top && !found; j++)
		{
			if (secondBulletPos.getX() == snakes[currSnake].getBullet(j).getPosition().getX()
				&& secondBulletPos.getY() == snakes[currSnake].getBullet(j).getPosition().getY())
			{
				deleteBullet(snakes[currSnake].getBullet(j), currSnake);
				found = true;
			}
		}
		if (found)
			return currSnake;
		currSnake = abs(currSnake - 1);
	} while (!found);

	return currSnake;
}

void Game::bulletSwap(Bullet & b1, Bullet & b2)
{
	Bullet temp;
	temp = b1;
	b1 = b2;
	b2 = temp;
}

// Gets the character the bullet is going to "meet".
bool Game::bulletCrash(Bullet & bullet, int snakeIndex)
{
	bool temp; // temp is a garbage variable
	char ch;
	Point point;

	point.setX(bullet.getPosition().getX());
	point.setY(bullet.getPosition().getY());

	switch (bullet.getDirection())
	{
	case LEFT:
		ch = board.getChar(point.getY(), point.getX() - 1);
		point.setX(bullet.getPosition().getX() - 1);
		break;

	case RIGHT:
		ch = board.getChar(point.getY(), point.getX() + 1);
		point.setX(bullet.getPosition().getX() + 1);
		break;

	case UP:
		ch = board.getChar(point.getY() - 1, point.getX());
		point.setY(bullet.getPosition().getY() - 1);
		break;

	case DOWN:
		ch = board.getChar(point.getY() + 1, point.getX());
		point.setY(bullet.getPosition().getY() + 1);
		break;
	}

	return objectCrashUpdates(ch, point, bullet.getPosition(), snakeIndex, bullet.getType(), temp);
}

// Checks if an object has crashed into another object.
bool Game::objectCrashUpdates(char ch, Point& futurePoint, Point& currPoint, int& snakeIndex, string str, bool& restartMission)
{
	int hurtedSnake;
	bool crashed = false;

	switch (ch)
	{
	case '*':
		hurtedSnake = objectInbullet(futurePoint);
		if (str == "colFlies" || str == "numEater")
		{
			snakes[hurtedSnake].updateAmmunition(snakes[hurtedSnake].getAmmunition() + 1);
			findAndDeleteFly(currPoint);
		}

		crashed = true;
		break;

	case '@':
		hurtedSnake = 0;
		objectInSnake(hurtedSnake, snakeIndex, str);
		crashed = true;
		if (str != "numEater")
			::isSnakePaused[hurtedSnake] = true;
		else
			numEaterInSnake(restartMission, hurtedSnake);
		break;

	case '#':
		hurtedSnake = 1;
		objectInSnake(hurtedSnake, snakeIndex, str);
		crashed = true;
		if (str != "numEater")
			::isSnakePaused[hurtedSnake] = true;
		else
			numEaterInSnake(restartMission, hurtedSnake);
		break;

	case '!':
		break;

	case '$':
		if (str == "bullet")
		{
			hurtedSnake = objectInbullet(currPoint);
			snakes[hurtedSnake].updateAmmunition(snakes[hurtedSnake].getAmmunition() + 1);
			findAndDeleteFly(futurePoint);
		}
		break;

	case '%':
		if (str == "bullet")
		{
			hurtedSnake = objectInbullet(currPoint);
			snakes[hurtedSnake].updateAmmunition(snakes[hurtedSnake].getAmmunition() + 1);
			findAndDeleteFly(futurePoint);
		}
		break;

	default:
		if (isdigit(ch))
		{
			objectInNumber(futurePoint, str, restartMission);
			crashed = true;
		}
		break;
	}

	return crashed;
}

void Game::numEaterInSnake(bool & restartMission, int hurtedSnake)
{
	gotoxy(0, 1);
	cout << BLANK_ROW;
	gotoxy(0, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
	cout << "The Number-Eater crashed into Snake: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakes[hurtedSnake].getColor());
	cout << snakes[hurtedSnake].getChar();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
	cout << ". Point goes to Snake: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), snakes[abs(hurtedSnake - 1)].getColor());
	cout << snakes[abs(hurtedSnake - 1)].getChar() << ".";
	PlaySound(TEXT("badpoint.wav"), NULL, SND_SYNC | SND_NODEFAULT);
	Sleep(800);
	gotoxy(0, 1);
	cout << BLANK_ROW;

	restartMission = true;
	revive(snakes[hurtedSnake]);
	snakes[abs(hurtedSnake - 1)].currLen++;
}

// Deletes a bullet if needed.
void Game::deleteBullet(Bullet& bullet, int snakeIndex)
{
	int top, x, y;
	top = snakes[snakeIndex].getTop();
	x = bullet.getPosition().getX();
	y = bullet.getPosition().getY();

	board.setDigit(y, x, ' ');
	bullet.getPosition().draw(' ');
	bulletSwap(bullet, snakes[snakeIndex].getBullet(top - 1));
	snakes[snakeIndex].getBullet(top - 1).setBullet();
	snakes[snakeIndex].setTop(--top);
}

void Game::findAndDeleteFly(Point & point)
{
	board.setDigit(point.getY(), point.getX(), ' ');
	point.draw(' ');

	//$
	if (point.getX() == 45)
		creature[2]->setDisappeared(true);
	//$
	else if (point.getX() == 55)
		creature[3]->setDisappeared(true);
	//%
	else
	{
		creature[4]->setDisappeared(true);
		((numEater*)creature[4])->setDestination(Point(-1, -1));
	}
}

void Game::nextFlyMove(int snakeIndex, int creatureIndex)
{
	char ch;
	Point pos, currPos;
	bool temp = false; // temp is a garbage variable

	currPos = creature[creatureIndex]->getPosition();
	pos = currPos;
	pos.moveImpl();
	ch = board.getChar(pos.getY(), pos.getX());
	if (ch == ' ' || ch == '!' || ch == '$' || ch == '%')
		creature[creatureIndex]->move(board);
	else
		objectCrashUpdates(ch, pos, currPos, snakeIndex, creature[creatureIndex]->getType(), temp);
}

// Checks the next move of the Num-Eater (if he crashed or not).
void Game::nextNumEaterMove(int snakeIndex, bool& restartMission, Point& pos)
{
	char ch;
	unsigned int distance = ((numEater*)creature[4])->getDistance();
	Point currPos, destination;
	currPos = creature[4]->getPosition();
	pos = currPos;
	pos.moveImpl();
	ch = board.getChar(pos.getY(), pos.getX());
	destination = ((numEater*)creature[4])->getDestination();

	if (destination != Point(-1, -1) && (ch == ' ' || ch == '!' || ch == '$'))
	{
		creature[4]->move(board);
		((numEater*)creature[4])->setDistance(distance - 1);
	}
	else if (destination == Point(-1, -1) || creature[4]->getDisappeared());
	else
		objectCrashUpdates(ch, pos, currPos, snakeIndex, creature[4]->getType(), restartMission);
}

// Gets a new destination for the Num-Eater.
void Game::getNewNumEaterDestination()
{
	for (int i = 0; i < nums.getHowMany(); ++i)
	{
		if (nums.getIsGoodNum(i))
			setDistanceAndDestination(nums.getX(i), nums.getY(i));
	}
}

// Sets the distance and the destination for the Num-Eater.
void Game::setDistanceAndDestination(int x, int y)
{
	unsigned int distX, distY, currDistance = ((numEater*)creature[4])->getDistance();
	Direction dirX, dirY;

	Point p = Point(creature[4]->getPosition().getX(), creature[4]->getPosition().getY());
	distX = checkDistanceX(p.getX(), x, dirX);
	distY = checkDistanceY(p.getY(), y, dirY);
	unsigned int newDistance = distX + distY;

	if (newDistance < currDistance)
	{
		((numEater*)creature[4])->setDistance(newDistance);
		((numEater*)creature[4])->setDestination(Point(x, y));
		((numEater*)creature[4])->setDirection(dirX);
		creature[4]->getPosition().changeDir(dirX);
		((numEater*)creature[4])->setDirY(dirY);
	}
}

unsigned int Game::checkDistanceX(int xEater, int xDest, Direction& dirX)
{
	unsigned int distance;

	if (xEater > xDest) // Eater is righter on board.
		calcDistanceAndDirection(xEater, xDest, LEFT, max_x, min_x, distance, dirX);

	else // Destination is righter on board.
		calcDistanceAndDirection(xDest, xEater, RIGHT, max_x, min_x, distance, dirX);

	return distance;
}

unsigned int Game::checkDistanceY(int yEater, int yDest, Direction& dirY)
{
	unsigned int distance;

	if (yEater > yDest) // Eater is higher on board.
		calcDistanceAndDirection(yEater, yDest, UP, max_y, min_y, distance, dirY);

	else // Destination is higher on board.
		calcDistanceAndDirection(yDest, yEater, DOWN, max_y, min_y, distance, dirY);

	return distance;
}

// Calculates the distance and the direction for the next destination of the Num-Eater.
void Game::calcDistanceAndDirection(int coord1, int coord2, Direction dir, int max_margin, int min_margin, unsigned int& finalDistance, Direction& finalDir)
{
	unsigned int dist1, dist2;
	Direction dir1, dir2;

	dist1 = coord1 - coord2;
	dir1 = dir;
	dist2 = max_margin - coord1 + coord2 - min_margin + 1;
	dir2 = reverseDir(dir1);

	if (dist1 < dist2)
	{
		finalDistance = dist1;
		finalDir = dir1;
	}

	else
	{
		finalDistance = dist2;
		finalDir = dir2;
	}
}

// Revives the snake after he was hitten.
void Game::revive(Snake & snake)
{
	int x, y;

	if (!gameReplay.isReplayOn())
	{
		do { generateLocation(x, y, 1); } while (!board.isSpace(y, x));
		snake.getSnakesBodyPart(HEAD).setX(x);
		snake.getSnakesBodyPart(HEAD).setY(y);
		gameReplay.getReviveRep().push_back(snake.getSnakesBodyPart(HEAD));
	}
	else
	{
		list<Point>::iterator it = gameReplay.getReviveRep().begin();
		if (it != gameReplay.getReviveRep().end())
		{
			x = it->getX();
			y = it->getY();
			Point p = { x, y };
			snake.getSnakesBodyPart(HEAD).setX(x);
			snake.getSnakesBodyPart(HEAD).setY(y);
			gameReplay.getReviveRep().push_back(p);
			gameReplay.getReviveRep().erase(it);
		}
	}

	resetSnake(snake);
}

void Game::setSnakeHead(Point head, int i)
{
	snakes[i].getSnakesBodyPart(HEAD) = head;
}

Game::~Game()
{
	for (int i = 0; i < CREAT_SIZE; i++)
		delete creature[i];
}
