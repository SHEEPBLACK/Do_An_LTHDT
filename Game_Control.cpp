#include "Game_Control.h"

Game::Game() 
{
	srand(time(NULL));
}
Game::~Game() {}

void Game::game_Create()
{
	resizeConsole(800, 700);
	XoaManHinh();
	quit = false;
	
	table.drawMap();

	ball = new Ball();
	ball->drawBall();


	p1 = new Player(2);
	p1->pad->drawPaddle();

	p2 = new Player(MapHeight - 1);
	p2->pad->drawPaddle();
}

void Game::Pause()
{
	gotoxy(WidthCenter - 2, HeightCenter - 1);
	textcolor(red);
	string pause = "PAUSE";
	cout << pause;

	while (_getch() != 112)	{ }

	gotoxy(WidthCenter - 2, HeightCenter - 1);
	textcolor(white);
	pause = "     ";
	cout << pause;
	return;

}

void Game::Quit()
{
	string Sure_Ask;
	Sure_Ask += "--------------------------------";
	Sure_Ask += "|        ARE YOU SURE?         |";
	Sure_Ask += "|            Y/ YES            |";
	Sure_Ask += "|            N/ NO             |";
	Sure_Ask += "--------------------------------";

	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 32; x++)
		{
			gotoxy(WidthCenter - 16 + x, HeightCenter - 2 + y);
			cout << Sure_Ask[y * 32 + x];
		}

	ReChoice:
	char choice = _getch();

	if (choice == 'Y' || choice == 'y')
		quit = true;
	else if (choice == 'N' || choice == 'n')
	{
		//Xoa bang Sure_Ask
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 32; x++)
			{
				gotoxy(WidthCenter - 16 + x, HeightCenter - 2 + y);
				putchar(32);
			}
		//Ve lai thanh nam ngang giua map
		gotoxy(1, HeightCenter);
		for (int i = 0; i < MapWidth; i++)
			putchar(254);
		//Tiep tuc tro choi
		return;
	}
	else
		goto ReChoice;

}

void Game::Print_Score()
{

	if (mode == 1)
	{
		gotoxy(MapWidth + 3, 2);
		cout << "HIGH SCORE: " << Game::HighScore_1P;
		gotoxy(MapWidth + 3, 4);
		//Danh dau nguoi choi dang dieu khien thanh mau xanh
		textcolor(blue);
		cout << "YOUR SCORE: " << p2->Score;
		textcolor(white);
	}
	else if (mode == 2)
	{
		gotoxy(MapWidth + 3, 2);
		cout << "WHO REACHES " << Game::LimitScore_2P << " FIRST WILL WIN";

		gotoxy(MapWidth + 3, 4);
		//Danh dau nguoi choi 1 dang dieu khien thanh mau vang
		textcolor(yellow);
		cout << "PLAYER 1: " << p1->Score;
		textcolor(white);
		cout << " - ";
		//Danh dau nguoi choi 2 dang dieu khien thanh mau xanh
		textcolor(blue);
		cout << "PLAYER 2: " << p2->Score;
		//Tra ve mau trang
		textcolor(white);
	}
}

void Game::Print_HighScore_1P()
{
	ifstream Input_HS("HighScore.txt");
	if (Input_HS.fail())
		cout << "Fail to open High Score file!" << endl;
	Input_HS >> Game::HighScore_1P;
	
	Input_HS.close();
}

void Game::Update_HighScore_1P()
{
	if (p2->Score > HighScore_1P)	//Nếu điểm người chơi lớn hơn highscore
	{
		HighScore_1P = p2->Score;

		//Update HighScore trong file
		ofstream Output_HS;
		Output_HS.open("HighScore.txt");
		Output_HS << HighScore_1P;
		Output_HS.close();

	}
	else return;
}

void Game::player_Update_1P(const char &key)
{
	//Update nguoi dieu khien
	switch (key)
	{
	case 72: //UP
		p2->pad->pDir = Up;
		break;
	case 80: // DOWN
		p2->pad->pDir = Down;
		break;
	case 77: //RIGHT
		p2->pad->pDir = Right;
		break;
	case 75: // LEFT
		p2->pad->pDir = Left;
		break;
	default:
		return;
	}

	p2->pad->pMove();
	p2->pad->del_old_Paddle();
	p2->pad->drawPaddle();

}

void Game::bot_Update_1P()
{
	//Update bot dieu khien
	if (p1->pad->Center_Pos.x < ball->Center_Pos.x)
	{
		p1->pad->pDir = Right;

	}
	else if (p1->pad->Center_Pos.x > ball->Center_Pos.x)
	{
		p1->pad->pDir = Left;
	}
	else
		p1->pad->pDir = Stop;

	p1->pad->pMove();
	p1->pad->del_old_Paddle();
	p1->pad->drawPaddle();
}

void Game::player_Update_2P(const char &key)
{
	//Update Thanh di chuyen
	if (key > 96)	//Kiem tra xem phim nhap vao thuoc phim WASD hay thuoc phim mui ten
	{
		switch (key)
		{
		case 'w':
			p1->pad->pDir = Up;
			p1->pad->pMove();
			p1->pad->del_old_Paddle();
			break;
		case 's':
			p1->pad->pDir = Down;
			p1->pad->pMove();
			p1->pad->del_old_Paddle();
			break;
		case 'd':
			p1->pad->pDir = Right;
			p1->pad->pMove();
			p1->pad->del_old_Paddle();
			break;
		case 'a':
			p1->pad->pDir = Left;
			p1->pad->pMove();
			p1->pad->del_old_Paddle();
			break;
		}
		p1->pad->drawPaddle();
	}
	else
	{
		switch (key)
		{
		case 72: //UP
			p2->pad->pDir = Up;
			p2->pad->pMove();
			p2->pad->del_old_Paddle();
			break;
		case 80: // DOWN
			p2->pad->pDir = Down;
			p2->pad->pMove();
			p2->pad->del_old_Paddle();
			break;
		case 77: //RIGHT
			p2->pad->pDir = Right;
			p2->pad->pMove();
			p2->pad->del_old_Paddle();
			break;
		case 75: // LEFT
			p2->pad->pDir = Left;
			p2->pad->pMove();
			p2->pad->del_old_Paddle();
			break;
		}
		p2->pad->drawPaddle();
	}
}

void Game::Input_Limit()
{
	do {
		XoaManHinh();
		gotoxy(WidthCenter - 6, HeightCenter - 1);
		cout << "Hay nhap muc diem chien thang: ";
		cin >> LimitScore_2P;
	} while (LimitScore_2P <= 0);
}

bool Game::check_Limit_2P()
{
	if (p1->Score == LimitScore_2P || p2->Score == LimitScore_2P)
		return true;
	return false;
}

void Game::print_Winner_2P()
{
	if (p1->Score > p2->Score)
	{
		gotoxy(WidthCenter - 6, HeightCenter);
		textcolor(yellow);
		cout << "PLAYER 1 WINS!";
		textcolor(white);
	}
	else
	{
		gotoxy(WidthCenter - 6, HeightCenter);
		textcolor(yellow);
		cout << "PLAYER 2 WINS!";
		textcolor(white);
	}
	_getch();
}

bool Game::check_Continue()
{
	string cont;
	cont += "--------------------------------";
	cont += "|  DO YOU WANT TO PLAY AGAIN?  |";
	cont += "|            Y/ YES            |";
	cont += "|            N/ NO             |";
	cont += "--------------------------------";

	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 32; x++)
		{
			gotoxy(WidthCenter - 16 + x, HeightCenter - 2 + y);
			cout << cont[y * 32 + x];
		}

	char Player_choose;
ReChoice:
	Player_choose = getch();
	if (Player_choose == 'y' || Player_choose == 'Y')
		return true;
	else if (Player_choose == 'n' || Player_choose == 'N')
		return false;
	else 
		goto ReChoice;
}

void Game::ball_Update()
{

	//Collide with Verticall wall
	if (ball->check_Collide_Vertical_Wall()) 
		ball->Collision_Wall();

	//Check collide with pad
	if (ball->check_Collide_Pad(p1->pad))
		ball->Collision_Pad();

	else if (ball->check_Collide_Pad(p2->pad))
	{
		if(mode == 1)	//Neu la mode 1 Player thi cong diem nguoi choi khi do duoc trai banh
			p2->Score_Up();
		ball->Collision_Pad();
	}

	//Banh cham vao 2 dau san, reset vi tri trai banh va cong diem nguoi choi
	if (ball->check_Scored_Condition(p2->pad)) //Neu banh cham vao vach ke map phia duoi nhung khong va cham voi nguoi choi
	{
		ball->Restart();

		if (mode == 1)
			p2->Score = 0;
		else if (mode == 2)
			p1->Score_Up();

		ball->del_old_Ball();
		ball->drawBall();
		return;
	}

	else if (ball->check_Scored_Condition(p1->pad))
	{
		ball->Restart();
		p2->Score_Up();

		ball->del_old_Ball();
		ball->drawBall();
		return;
	}

	ball->bMove();
	ball->drawBall();
	ball->del_old_Ball();

	//Neu banh di qua vach o giua map -> son lai vach
	if (ball->Old_Pos.y == HeightCenter)
		ball->repaint_middle_line();

	//Neu banh dung ngay thanh truot -> son lai thanh
	if (ball->check_Override_Pad(p1->pad) || ball->check_Override_Pad(p2->pad))
		ball->repaint_Pad();
}


void Game::game_Update()
{
	if (_kbhit())
	{
		char key = _getch();
		//Bam 'p' de dung game
		if (key == 112)
			Pause();
		//Bam ESC de thoat game
		else if (key == 27)
			Quit();
		else
		{
			if (mode == 1)
				Game::player_Update_1P(key);
			else if (mode == 2)
				Game::player_Update_2P(key);
		}
	}
	
}


void Game::game_Play_1P()
{
	
	game_Create();
	Print_HighScore_1P();
	int frame_Count = 0;

	while (1)
	{
		frame_Count++;
		Game::game_Update();
		if (quit == true)
			return;
		if (frame_Count % ((700 - Ball::speed * 70) /2) == 0)
			bot_Update_1P();
		if (frame_Count == (700 - Ball::speed * 70))	//Cong thuc tinh speed cua 1 player
		{
			Game::ball_Update();
			frame_Count = 0;
		}
		Print_Score();
		Update_HighScore_1P();
		AnConTro();
	}

}

void Game::game_Play_2P()
{
play_Again:

	Input_Limit();
	game_Create();

	int frame_Count = 0;
	while (1)
	{
		if (check_Limit_2P())	//Check có player nào đạt đủ điểm chiến thắng chưa
		{
			print_Winner_2P();	//In ra người chiến thắng
			if (check_Continue())	//Hỏi xem người chơi có muốn chơi lại không
				goto play_Again;	//Nếu có thì quay lại nhập điểm chiến thắng mới
			else return;	//Nếu không thì thoát ra ngoài menu
		}

		frame_Count++;
		Game::game_Update();
		if (quit == true)
			return;
		if (frame_Count == (500 - Ball::speed * 50))	//Cong thuc tinh speed cua mode 2 players
		{
			Game::ball_Update();
			frame_Count = 0;
		}
		Print_Score();
		AnConTro();
	}
}

void Game::print_Guide()
{
	XoaManHinh();
	string line;
	string data;

	fstream Guide("Guide.txt",ios::in);
	if (Guide.fail())
	{
		cout << "Failed to open guide!";
		_getch();
		return;
	}

	while (!Guide.eof())
	{
		getline(Guide, line);
		data += line + '\n';
	}
	cout << data;
	while (_getch() != 8) {}
	return;
}

void Game::Exit()
{
	exit(0);
}

void Game::print_About()
{
	XoaManHinh();
	string line;
	string data;

	fstream About("About.txt", ios::in);
	if (About.fail())
	{
		cout << "Failed to open about!";
		_getch();
		return;
	}

	while (!About.eof())
	{
		getline(About, line);
		data += line + '\n';
	}
	cout << data;
	while (_getch() != 8) {}
	return;
}

void Game::Start()
{
back_to_Menu:
	XoaManHinh();
	menu.Print();
	mode = menu.Player_Choose() + 1;
	switch (mode)
	{
	case 1:
		game_Play_1P();
		break;
	case 2:
		game_Play_2P();
		break;
	case 3:
		print_Guide();
		break;
	case 4:
		print_About();
		break;
	case 5:
		Exit();
		break;
	
	}
	goto back_to_Menu;


}











