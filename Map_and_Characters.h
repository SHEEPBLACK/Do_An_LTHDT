#pragma once
#include "Graphics.h"

enum pDirection { Up, Down, Left, Right, Stop }; // Các trạng thái di chuyển của paddle
enum bDirection { URU, UR, URD, ULU, UL, ULD, DRU, DR, DRD, DLU, DL, DLD };  //Các trạng thái di chuyển của quả banh

class Coord	//class tọa độ
{
public:
	int x, y;

	Coord(const int X = 1, const int Y = 1);
	~Coord();
	Coord& operator=(const Coord& other);
};

class Square	//class ô vuông (pixel)
{
public:
	char kitu;
	int color;

	Square();
	~Square();
	
};

class Paddle	//class thanh trượt
{
public:
	Coord Center_Pos;	//Tọa độ tâm thanh trượt
	vector <Square> shape;	//Hình dáng thanh
	int half_long;	//Nửa độ dài thanh
	pDirection pDir;	//Hướng đi của thanh trượt

public:
	Paddle(int first_yPos, const int pLong = 15);
	~Paddle();
	void pMove();	//Cập nhật trạng thái di chuyển của thanh trượt
	void drawPaddle();	//Vẽ thanh trượt ở vị trí mới
	void del_old_Paddle();	//Xóa thanh trượt cũ
};

class Player	//class người chơi
{
private:
	int Score;	//Điểm của người chơi
	int first_yPos;	//Tung độ ban đầu
	Paddle* pad;	//Thanh trượt của người chơi
public:
	Player(int _first_yPos);
	~Player();
	void Score_Up();	//Cộng điểm cho người chơi

	friend class Game;
};

class Ball
{
public:
	Coord Center_Pos;	//Tọa độ tâm quả banh hiện tại
	Coord Old_Pos;	//Tọa độ tâm quả banh ở vị trí cũ
	vector<Square> shape;	//Hình dáng quả banh
	static int speed;	//Tốc độ quả banh
	int radius;	//Bán kính quả banh
	bDirection bDir;	//Hướng di chuyển của quả banh
public:
	Ball(const int _radius = 1);	//Khởi tạo quả banh
	~Ball();
	void drawBall();	//Vẽ quả banh hiện tại
	void bMove();	//Cập nhật hướng di chuyển của quả banh
	void del_old_Ball();	//Xóa quả banh ở vị trí cũ (Sau khi di chuyển)

	bool check_Collide_Vertical_Wall();	//Kiểm tra có va chạm với mép dọc của sân đấu hay không
	void Collision_Wall();	//Va chạm với tường

	bool check_Collide_Pad(Paddle *p);	//Kiểm tra có va chạm với thanh trượt hay không
	void Collision_Pad();	//Va chạm với thanh trượt

	bool check_Scored_Condition(Paddle *p);	//Kiểm tra điều kiện bị ghi điểm (đỡ hụt quả banh) của thanh trượt p
	void Restart();	//Cập nhật quả banh về giữa sân và cộng điểm cho người chơi

	void repaint_middle_line();	//Vẽ lại vạch giữa sân khi quả banh đi qua

	bool check_Override_Pad(Paddle *p);	//Kiểm tra nếu quả banh nằm đè lên thanh trượt
	void repaint_Pad();	//Vẽ lại thanh trượt
	friend class Game;
};


class Map
{
private:
	vector<vector<Square>> Playground;

public:
	Map();
	~Map();
	void drawMap();

	friend class Game;

};
