#include "Utilities.h"

Option::Option(const int _x, const int _y, const string _data)
{
	Pos.x = _x;
	Pos.y = _y;
	data = _data;
}

Option::~Option() {}




Menu::Menu()
{
	//Tao menu
	list_Option.resize(0);
	Option temp;
	
	temp.data = "1 PLAYER ";
	temp.Pos.x = 35;
	temp.Pos.y = 20;
	list_Option.push_back(temp);

	temp.data = "2 PLAYERS ";
	temp.Pos.x = 35;
	temp.Pos.y = 23;
	list_Option.push_back(temp);

	temp.data = "GUIDE ";
	temp.Pos.x = 35;
	temp.Pos.y = 26;
	list_Option.push_back(temp);

	temp.data = "ABOUT ";
	temp.Pos.x = 35;
	temp.Pos.y = 29;
	list_Option.push_back(temp);

	temp.data = "EXIT ";
	temp.Pos.x = 35;
	temp.Pos.y = 32;
	list_Option.push_back(temp);

	//Tao khung cho menu
	menu_Frames += "-----------------------------------";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "|                                 |";
	menu_Frames += "-----------------------------------";

	menu_guide = "W: up, S: down, A: left, D: right, Enter: choose, Backspace: back";
}

Menu::~Menu() {}

void Menu::Print_GameName()
{
	//Mo 2 file ten game
	fstream Ping("GameName_Ping.txt", ios::in);
	fstream Pong("GameName_Pong.txt", ios::in);
	if (Ping.fail() || Pong.fail())
	{
		cout << "Failed when open GameName file" << endl;
		return;
	}

	string line;
	string GN_Ping;
	string GN_Pong;

	while (!Ping.eof())
	{
		getline(Ping, line);
		GN_Ping += line + '\n';
	}

	while (!Pong.eof())
	{
		getline(Pong, line);
		GN_Pong += line + '\n';
	}
	//Random mau ve ten game
	int color = rand() % 14 +1;
	textcolor(color);
	gotoxy(1, 1);
	cout << GN_Ping << endl;

	color = rand() % 14 + 1;
	textcolor(color);
	cout << GN_Pong << endl;
	//Tra ve mau trang
	textcolor(white);

	Ping.close();
	Pong.close();
}

void Menu::Print()
{
	resizeConsole(580, 800);

	for (int y = 0; y < HeighMenu; y++)
	{
		gotoxy(22, 17 + y);
		for (int x = 0; x < WidthMenu; x++)
			cout << menu_Frames[y*WidthMenu + x];
		cout << endl;
	}

	for (int i = 0; i < list_Option.size(); i++)
	{
		gotoxy(list_Option[i].Pos.x, list_Option[i].Pos.y);
		cout << list_Option[i].data << endl;
	}
	Cursor_On(0);

	textcolor(yellow);
	gotoxy(8, 38);
	cout << menu_guide;
	textcolor(white);

	AnConTro();
}

void Menu::Cursor_On(int current)
{
	textcolor(green);
	gotoxy(list_Option[current].Pos.x - 1, list_Option[current].Pos.y);
	cout << (char)175 << " " << list_Option[current].data;
	textcolor(15);
}

void Menu::del_Old_Cur(int old_Pos)
{
	gotoxy(list_Option[old_Pos].Pos.x - 1, list_Option[old_Pos].Pos.y);
	cout << " ";
}

int Menu::Player_Choose()
{
	int curr = 0;
	bool check_Choose = false;
	int key;

	while (!check_Choose)
	{
		Print_GameName();
		if (_kbhit())
		{
			key = _getch();
			if (key == 'W' || key == 'w') // UP
			{
				gotoxy(list_Option[curr].Pos.x, list_Option[curr].Pos.y);
				cout << list_Option[curr].data;

				del_Old_Cur(curr);

				if (curr == 0)
				{
					curr = list_Option.size() - 1;
				}
				else
					curr--;

				Cursor_On(curr);

			}
			else if (key == 's' || key == 'S') // DOWN
			{
				gotoxy(list_Option[curr].Pos.x, list_Option[curr].Pos.y);
				cout << list_Option[curr].data;

				del_Old_Cur(curr);

				if (curr == list_Option.size() - 1)
				{
					curr = 0;
				}
				else
					curr++;

				Cursor_On(curr);
			}
			else if(key == 13)
				check_Choose = true;
		}
	}
		return curr;
}

