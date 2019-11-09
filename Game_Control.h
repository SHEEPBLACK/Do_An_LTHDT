#pragma once
#include "Utilities.h"

class Game	
{
private:
	Player* p1;	//Người chơi 1							
	Player* p2;	//Người chơi 2				
	Ball* ball;	//Quả banh							
	Map table;	//Sân đấu							
	Menu menu;	//Menu							
	static int mode;	//Chế độ chơi
	static bool quit;	//Kiểm tra thoát ra ngoài menu
	static int HighScore_1P;	//HighScore của chế độ 1P
	static int LimitScore_2P;	//Điểm chiến thắng của chế độ 2P
public:
	Game();	//Khởi tạo game
	~Game();
	void game_Create();	//Tạo lập các đối tượng trong game
	
	void Pause();	//Tạm dừng 
	void Quit();	//Thoát game (đang chơi)
	void Print_Score();	//In điểm người chơi

	void Print_HighScore_1P();	//In HighScore
	void Update_HighScore_1P();	//Cập nhật HighScore
	void player_Update_1P(const char &key);	//Cập nhật người chơi
	void bot_Update_1P();	//Cập nhật bot

	void player_Update_2P(const char &key);	//Cập nhật 2 người chơi
	void Input_Limit();	//Nhập điểm chiến thắng
	bool check_Limit_2P();	//Kiểm tra có người chơi nào vượt được điểm chiến thắng chưa
	void print_Winner_2P();	//In ra người chơi chiến thắng
	bool check_Continue();	//Kiểm tra người chơi có muốn tiếp tục chơi game

	void ball_Update();	//Cập nhật trạng thái quả banh
	void game_Update();	//Cập nhật game (Cập nhật quit hay pause game)

	void game_Play_1P();	
	void game_Play_2P();
	void print_Guide();	//In ra hướng dẫn chơi game
	void print_About();	//In ra thông tin người làm
	void Exit(); //Thoát game

	void Start(); //Bắt đầu game
};