#pragma once
#include "Map_and_Characters.h"

class Option	//Class các sự lựa chọn
{
public:
	Coord Pos;	//Vị trí sự lựa chọn
	string data;	//Tên sự lựa chọn
public:
	Option(const int _x = WidthCenter, const int _y = HeightCenter, const string _data = " ");
	~Option();

};

class Menu
{
private:
	vector<Option> list_Option;	//List sự lựa chọn
	string menu_Frames;	//Khung menu
	string menu_guide;	//Hướng dẫn sử dụng menu
public:
	Menu();	//Khởi tạo menu
	~Menu();
	void Print_GameName();	//In ra tên game
	void Print();	//In ra menu
	void Cursor_On(int current);	//Đặt con trỏ tại vị trí đang lựa chọn
	void del_Old_Cur(int old_Pos);	//Xóa con trỏ cũ
	int Player_Choose();	//Lựa chọn của người chơi
};

