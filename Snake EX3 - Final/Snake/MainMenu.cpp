#include "MainMenu.h"
#include "Game.h"

void printBigSnake()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN | FOREGROUND_INTENSITY);
	cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | FOREGROUND_INTENSITY);
	cout << "        ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ ~        " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN | FOREGROUND_INTENSITY);
	cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN | FOREGROUND_INTENSITY);
	cout << "                                                                               " << endl;
	cout << "                                                                               " << endl;
	cout << "         SSSSSS     NN      NN         AA         KK    KK    EEEEEEEE         " << endl;
	cout << "        SS    SS    NNN     NN        AAAA        KK   KK     EE               " << endl;
	cout << "        SS    SS    NN NN   NN       AA  AA       KK KK       EE               " << endl;
	cout << "          SS        NN  NN  NN      AA    AA      KKKK        EEEEEEE          " << endl;
	cout << "            SS      NN   NN NN     AAAAAAAAAA     KK KK       EE               " << endl;
	cout << "        SS    SS    NN     NNN    AA        AA    KK   KK     EE               " << endl;
	cout << "         SSSSSS     NN      NN   AA          AA   KK    KK    EEEEEEEE         " << endl;
	cout << "                                                                               " << endl;
	cout << "                                                                               " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN | FOREGROUND_INTENSITY);
	cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | FOREGROUND_INTENSITY);
	cout << "        ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ ~        " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN | FOREGROUND_INTENSITY);
	cout << "        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREY | FOREGROUND_INTENSITY);
	cout << "                           By Itai Amit and Gil Reuven                         " << endl;
	Sleep(2200);
	clrscr();
}

void MainMenu(bool MainOrSecond, bool& run, Game& game)
{
	while (run)
	{
		int select = 0;

		clrscr();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED | FOREGROUND_INTENSITY);
		//	     12345678901234567890123456789012345678901234567890123456789012345678901234567890
		cout << "                                      MENU                                      " << endl;
		cout << "                                      ----                                      " << endl << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | FOREGROUND_INTENSITY);
		cout << "                               (1) Instructions." << endl;
		cout << "                               (2) Start a new game." << endl;
		cout << "                               (9) Exit." << endl;
		PlaySound(TEXT("Videogame2.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP | SND_NODEFAULT);
		cin >> select;

		while (select != EXIT_MAIN && select != NEW_GAME_MAIN && select != INSTRUCTIONS)
			cin >> select;

		switch (select)
		{
		case 1:
			Instructions();
			break;
		case 9:
			ExitGame(1, run);
			break;
		case 2:
			PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
			GoodLuck();
			game.run(run);
			break;
		}
	}	
}

void Instructions()
{
	clrscr();

	PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED | FOREGROUND_INTENSITY);
	cout << "Instructions:" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGREY | FOREGROUND_INTENSITY);
	cout << "~~~~~~~~~~~~" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | FOREGROUND_INTENSITY);
	cout << "*This is a mathematical snake game." << endl << endl;
	cout << "*Mathematical questions will be on top of the screen." << endl << endl;
	cout << "*The first player to get 12 points is the Winner!" << endl << endl;
	cout << "*If you pick up a wrong number, the second player will get a point." << endl << endl;
	cout << "*Missions will be changed after picking a number." << endl << endl;
	cout << "*After each mission, half of the numbers on the board will disappear." << endl << endl;
	cout << "*You can neutralize your enemy by shooting him." << endl << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTCYAN | FOREGROUND_INTENSITY);
	cout << "Keys:" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGREY | FOREGROUND_INTENSITY);
	cout << "~~~~" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | FOREGROUND_INTENSITY);
	cout << "Player 1: UP: 'w', DOWN: 'x', RIGHT: 'd', LEFT: 'a', SHOOT: 'z'" << endl;
	cout << "Player 2: UP: 'i', DOWN: ',', RIGHT: 'l', LEFT: 'j', SHOOT: 'n'";
	gotoxy(0, 23);
	cout << "(Press any key to go back)" << endl;

	getch();
}

void GoodLuck()
{
	clrscr();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED | FOREGROUND_INTENSITY);
	gotoxy(34, 10);
	cout << "Good Luck ;)" << endl;
	for (int i = 0; i < 3; i++)
	{
		PlaySound(TEXT("readySet"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(850);
	}

	PlaySound(TEXT("go"), NULL, SND_ASYNC | SND_NODEFAULT);
}

void ExitGame(bool MainOrSecondary,bool& go)
{
	PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
	if (MainOrSecondary)
		clrscr();

	else
		gotoxy(0, 1);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW | FOREGROUND_INTENSITY);
	cout << "Are you sure? (Y \\ N)                                                          ";
	
	char choice;
	gotoxy(23, 1);
	cin >> choice;
	PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);

	while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
	{
		cin >> choice;
		PlaySound(TEXT("sfx_sounds_button3.wav"), NULL, SND_SYNC | SND_NODEFAULT);
	}

	switch (choice)
	{
	case 'y':
	case 'Y':
		clrscr();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW | FOREGROUND_INTENSITY);
		cout << "Bye-Bye!, See you next time ;)" << endl;
		Sleep(1500);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | FOREGROUND_INTENSITY);
		go= false;
		break;
	case 'n':
	case 'N':
		break;
	}
}
