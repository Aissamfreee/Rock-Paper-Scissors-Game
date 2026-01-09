#include <iostream>
#include <ctime>
using namespace std;

enum engame_Choices { stone = 1, scissor = 2, paper = 3 };
enum enWinner { player = 1, Computer = 2, Draw = 3 };

struct stRoundinfo
{
	short Round_Number = 0;
	engame_Choices Player_choice;
	engame_Choices Computer_choice;
	enWinner Winner;
	string Winner_name;
};

struct stGameResults
{
	short Game_Rounds;
	short Player_win_time;
	short Computer_win_time;
	short Draw_time;
	enWinner Game_winner;
	string winner_name = "";
};

int Random_variables(int from, int to)
{
	int rand_ = rand() % (to - from + 1) + from;
	return rand_;
}

string Winner_name(enWinner Winner)
{
	string arrWinnerName[3] = { "player","Computer","No Winner" };
	return  arrWinnerName[Winner - 1];
}

enWinner who_win_the_Round(stRoundinfo Roundinfo)
{
	if (Roundinfo.Player_choice == Roundinfo.Computer_choice)
		return enWinner::Draw;

	switch (Roundinfo.Player_choice)
	{
	case engame_Choices::stone:
		if (Roundinfo.Computer_choice == engame_Choices::paper)
		{
			return enWinner::Computer;
		}
		break;
	case engame_Choices::paper:
		if (Roundinfo.Computer_choice == engame_Choices::scissor)
		{
			return enWinner::Computer;
		}
		break;
	case engame_Choices::scissor:
		if (Roundinfo.Computer_choice == engame_Choices::stone)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::player;
}

string Choice_name(engame_Choices Choice)
{
	string arrgame_Choices[3] = { "Stone", "Scissor", "Paper" };
	return  arrgame_Choices[Choice - 1];
}

void set_winner_screen_color(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::player:
		system("color 2F");

		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

void print_Round_result(stRoundinfo Roundinfo)
{

	cout << "\n________________________Round [" << Roundinfo.Round_Number << "]" << " ______________________:";
	cout << "\nplayer choice:" << Choice_name(Roundinfo.Player_choice) << endl;
	cout << "Computer choice:" << Choice_name(Roundinfo.Computer_choice) << endl;
	cout << "Round  Winner:" << "[" << Roundinfo.Winner_name << "]" << endl;
	cout << "\n----------------------------------------------\n";

	set_winner_screen_color(Roundinfo.Winner);

}

enWinner WhoWonTheGame(short Player_win_time, short Computer_win_time)
{
	if (Player_win_time > Computer_win_time)
		return enWinner::player;
	else if (Computer_win_time > Player_win_time)
		return enWinner::Computer;
	else return enWinner::Draw;
}

stGameResults fill_game_Result(short Game_Rounds, short Player_win_time, short Computer_win_time, short Draw_time)
{
	stGameResults GameResults;
	GameResults.Game_Rounds = Game_Rounds;
	GameResults.Player_win_time = Player_win_time;
	GameResults.Computer_win_time = Computer_win_time;
	GameResults.Draw_time = Draw_time;
	GameResults.Game_winner = WhoWonTheGame(Player_win_time, Computer_win_time);
	GameResults.winner_name = Winner_name(GameResults.Game_winner);

	return GameResults;
}

engame_Choices  read_player_choice()
{
	short choice = 1;
	do
	{
		cout << "your choice : [1]:stone , [2]:scissor ,[3]:paper ?:";
		cin >> choice;
	} while (choice < 1 || choice > 3);
	return (engame_Choices)choice;
}

engame_Choices  get_Computer_choice()
{
	return (engame_Choices)Random_variables(1, 3);
}

stGameResults play_Game(short How_many_Round)
{
	stRoundinfo Roundinfo;
	short Player_win_time = 0; short Computer_win_time = 0; short Draw_time = 0;
	for (short Game_round = 1; Game_round <= How_many_Round; Game_round++)
	{
		cout << "round [" << Game_round << "]" << "begin:\n";
		Roundinfo.Round_Number = Game_round;
		Roundinfo.Player_choice = read_player_choice();
		Roundinfo.Computer_choice = get_Computer_choice();
		Roundinfo.Winner = who_win_the_Round(Roundinfo);
		Roundinfo.Winner_name = Winner_name(Roundinfo.Winner);

		if (Roundinfo.Winner == enWinner::player)
			Player_win_time++;
		else if (Roundinfo.Winner == enWinner::Computer)
			Computer_win_time++;
		else
			Draw_time++;

		print_Round_result(Roundinfo);



	}

	return fill_game_Result(How_many_Round, Player_win_time, Computer_win_time, Draw_time);
}

string Tabs(short Number_of_Tabs)
{
	string t = "";
	for (int i = 1; i < Number_of_Tabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void show_Game_over_screen()
{
	cout << Tabs(2) << "--------------------------------------------\n\n";
	cout << Tabs(2) << "         *** G a m e O v e r ***            \n\n";
	cout << Tabs(2) << "--------------------------------------------\n\n";
}

void show_final_Game_result(stGameResults GameResults)
{


	cout << Tabs(2) << "--------------[Game Results]------------------\n";
	cout << Tabs(2) << "Game Rounds :" << GameResults.Game_Rounds << endl;
	cout << Tabs(2) << "Player won time :" << GameResults.Player_win_time << endl;
	cout << Tabs(2) << "Computer won time :" << GameResults.Computer_win_time << endl;
	cout << Tabs(2) << "Draw times :" << GameResults.Draw_time << endl;
	cout << Tabs(2) << "final winner :" << GameResults.winner_name << endl;
	cout << Tabs(2) << "-----------------------------------------------\n" << endl;

	set_winner_screen_color(GameResults.Game_winner);
}

short Read_How_many_Round()
{
	int Game_Round = 1;
	do
	{
		cout << "how many rounds 1 to 10?: " << endl;
		cin >> Game_Round;
	} while (Game_Round < 1 || Game_Round > 10);
	return Game_Round;
}

void Reset_screen()
{
	system("cls");
	system("color 0F");
}

void start_game()
{
	char play_again = 'Y';
	do
	{
		Reset_screen();
		stGameResults Game_Results = play_Game(Read_How_many_Round());
		show_Game_over_screen();
		show_final_Game_result(Game_Results);


		cout << Tabs(2) << "Do you want to play again? Y/N ?:";
		cin >> play_again;
	} while (play_again == 'Y' || play_again == 'y');

}

int main()
{
	srand((unsigned)time(NULL));
	start_game();

	return 0;
}