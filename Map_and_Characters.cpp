#include "Map_and_Characters.h"

Coord::Coord(const int X, const int Y)
{
	this->x = X;
	this->y = Y;
}

Coord::~Coord() {}

Coord& Coord::operator=(const Coord& other)
{
	x = other.x;
	y = other.y;
	return *this;
}




Square::Square()
{
	this->kitu = (char)32;
	this->color = 15;
}

Square::~Square() {}






Map::Map()
{
	//Khoi tao map 
	Playground.resize(MapHeight);
	for (int y = 0; y < MapHeight; y++)
		Playground[y].resize(MapWidth);

	for (int y = 0; y < MapHeight; y++)
		for (int x = 0; x < MapWidth; x++)
		{
			if (x == 0)
				Playground.at(y).at(x).kitu = 221;
			if (x == MapWidth - 1)
				Playground.at(y).at(x).kitu = 222;
			if (y == 0)
				Playground.at(y).at(x).kitu = 220;
			if (y == MapHeight - 1)
				Playground.at(y).at(x).kitu = 223;
			if (y == HeightCenter - 1)
				if (x != 0 && x != MapWidth - 1)
					Playground.at(y).at(x).kitu = 254;
		}
}

void Map::drawMap()
{
	textcolor(white);
	//Tro con tro toi goc trai man hinh console
	gotoxy(1, 1);
	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++)
			putchar(Playground.at(y).at(x).kitu);
		cout << endl;
	}
}


Map::~Map() {}




Paddle::Paddle(int first_yPos, const int pLong)
{
	this->Center_Pos.x = WidthCenter;
	this->Center_Pos.y = first_yPos;

	shape.resize(pLong);
	half_long = pLong / 2;

	for (int i = 0; i < half_long * 2 + 1; i++)
		shape.at(i).kitu = 254;
}

Paddle::~Paddle() {}

void Paddle::pMove()
{

	switch (pDir)
	{
	case Up:
		if (Center_Pos.y - 1 == 1 || Center_Pos.y - 1 == HeightCenter)  // Paddle không được di chuyển ra ngoài map hoặc qua phần sân bên kia
		{
			pDir = Stop;
			break;
		}
		Center_Pos.y--;
		break;
	case Down:
		if (Center_Pos.y + 1 == MapHeight || Center_Pos.y + 1 == HeightCenter)	// Paddle không được di chuyển ra ngoài map hoặc qua phần sân bên kia
		{
			pDir = Stop;
			break;
		}
		Center_Pos.y++;
		break;
	case Left:
		if (Center_Pos.x - half_long - 1 == 1)	// Paddle không được di chuyển ra ngoài map hoặc qua phần sân bên kia
		{
			pDir = Stop;
			break;
		}
		Center_Pos.x--;
		break;
	case Right:
		if (Center_Pos.x + half_long + 1 == MapWidth)	// Paddle không được di chuyển ra ngoài map hoặc qua phần sân bên kia
		{
			pDir = Stop;
			break;
		}
		Center_Pos.x++;
		break;
	default:
		break;
	}
}

void Paddle::drawPaddle()
{
	//Neu thanh dung yen thi khong can ve
	if (this->pDir == Stop)
		return;

	if (Center_Pos.y < HeightCenter)	//Neu la paddle nam nua tren san dau
		textcolor(yellow);
	else if (Center_Pos.y > HeightCenter)	//Neu la paddle nam nua duoi san dau
		textcolor(blue);

	gotoxy(Center_Pos.x - half_long, Center_Pos.y);
	for (int i = 0; i < half_long * 2 + 1; i++)
		putchar(shape.at(i).kitu);

	//Tra ve mau trang
	textcolor(white);
}


void Paddle::del_old_Paddle()	//Xoa phan con thua sau khi ve paddle o vi tri moi
{
	switch (pDir)
	{
	case Up:
		gotoxy(Center_Pos.x - half_long, Center_Pos.y + 1);
		for (int i = 0; i < half_long * 2 + 1; i++)
			putchar(32);
		break;
	case Down:
		gotoxy(Center_Pos.x - half_long, Center_Pos.y - 1);
		for (int i = 0; i < half_long * 2 + 1; i++)
			putchar(32);
		break;
	case Right:
		gotoxy(Center_Pos.x - half_long - 1, Center_Pos.y);
		putchar(32);
		break;
	case Left:
		gotoxy(Center_Pos.x + half_long + 1, Center_Pos.y);
		putchar(32);
		break;
	default:
		break;
	}
}




Ball::Ball(const int _radius)
{
	radius = _radius;
	shape.resize(radius * 2 + 1);
	
	//Ve qua banh bang ma ascii
	shape.at(0).kitu = 222;
	shape.at(1).kitu = 219;
	shape.at(2).kitu = 221;

	for (int i = 0; i < 3; i++)
		shape.at(i).color = 12;

	Old_Pos.x = Old_Pos.y = 0;

	Center_Pos.x = WidthCenter;
	Center_Pos.y = HeightCenter;

	bDir = bDirection(rand() % 12);
	
}

Ball::~Ball() {}

void Ball::drawBall()
{

	gotoxy(Center_Pos.x - radius, Center_Pos.y);
	for (int i = 0; i < 3; i++)
	{ 
		textcolor(shape.at(i).color);
		putchar(shape.at(i).kitu);
	}
	textcolor(white);
}


void Ball::bMove()
{
	Old_Pos = Center_Pos;
	switch (bDir)
	{
	case URU:
		Center_Pos.x++;
		Center_Pos.y -= 2;
		break;
	case UR:
		Center_Pos.x++;
		Center_Pos.y--;
		break;
	case URD:
		Center_Pos.x += 2;
		Center_Pos.y--;
		break;
	case ULU:
		Center_Pos.x--;
		Center_Pos.y -= 2;
		break;
	case UL:
		Center_Pos.x--;
		Center_Pos.y--;
		break;
	case ULD:
		Center_Pos.x -= 2;
		Center_Pos.y--;
		break;
	case DRU:
		Center_Pos.x += 2;
		Center_Pos.y++;
		break;
	case DR:
		Center_Pos.x++;
		Center_Pos.y++;
		break;
	case DRD:
		Center_Pos.x++;
		Center_Pos.y += 2;
		break;
	case DLU:
		Center_Pos.x -= 2;
		Center_Pos.y++;
		break;
	case DL:
		Center_Pos.x--;
		Center_Pos.y++;
		break;
	case DLD:
		Center_Pos.x--;
		Center_Pos.y += 2;
		break;

	}
}

void Ball::del_old_Ball()	//Xoa qua banh cu sau khi qua banh di den vi tri moi
{
	gotoxy(Old_Pos.x - radius, Old_Pos.y);
	for (int i = 0; i < 3; i++)
		putchar(32);
}

bool Ball::check_Collide_Vertical_Wall()
{
	return (Center_Pos.x + 2 == MapWidth || Center_Pos.x - 2 == 1);
}

//Xu ly va cham voi 2 ben cua map
void Ball::Collision_Wall()
{
	switch (bDir)
	{
		Old_Pos = Center_Pos;
	case URU:
		bDir = ULU;
		break;
	case UR:
		bDir = UL;
		break;
	case URD:
		bDir = ULD;
		break;
	case DRU:
		bDir = DLU;
		break;
	case DR:
		bDir = DL;
		break;
	case DRD:
		bDir = DLD;
		break;
	case ULU:
		bDir = URU;
		break;
	case UL:
		bDir = UR;
		break;
	case ULD:
		bDir = URD;
		break;
	case DLU:
		bDir = DRU;
		break;
	case DL:
		bDir = DR;
		break;
	case DLD:
		bDir = DRD;
		break;
	}
}

bool Ball::check_Collide_Pad(Paddle *p)
{
	if (p->Center_Pos.y < HeightCenter) //Neu la paddle o nua tren san dau
	{
		if (Center_Pos.y - 1 == p->Center_Pos.y || Center_Pos.y == p->Center_Pos.y)  //Kiem tra toa do y cua qua banh voi thanh
			if ((Center_Pos.x <= p->Center_Pos.x + p->half_long) && (Center_Pos.x >= p->Center_Pos.x - p->half_long)) //Kiem tra neu qua banh nam trong chieu dai thanh
				return true;
	}
	else if (p->Center_Pos.y > HeightCenter) //Neu la paddle o nua duoi san dau
	{
		if (Center_Pos.y + 1 == p->Center_Pos.y || Center_Pos.y == p->Center_Pos.y)  //Kiem tra toa do y cua qua banh voi thanh
			if ((Center_Pos.x <= p->Center_Pos.x + p->half_long) && (Center_Pos.x >= p->Center_Pos.x - p->half_long)) //Kiem tra neu qua banh nam trong chieu dai thanh
				return true;
	}
	return false;
}

void Ball::Collision_Pad()
{
	//Phan loai ra de tranh truong hop nguoi choi dieu khien paddle chay xuyen qua banh => may tinh check va cham 2 lan
	if (Center_Pos.y < HeightCenter)	//Neu la paddle o nua tren san dau
	{
		switch (bDir)
		{
			Old_Pos = Center_Pos;
		case URU:
			bDir = DRD;
			break;
		case UR:
			bDir = DR;
			break;
		case URD:
			bDir = DRU;
			break;
		case ULU:
			bDir = DLD;
			break;
		case UL:
			bDir = DL;
			break;
		case ULD:
			bDir = DLU;
			break;
		default:
			break;
		}
	}
	else if(Center_Pos.y > HeightCenter)	//Neu la paddle o nua duoi san dau
	{
		switch (bDir)
		{
			Old_Pos = Center_Pos;
		case DRU:
			bDir = URD;
			break;
		case DR:
			bDir = UR;
			break;
		case DRD:
			bDir = URU;
			break;
		case DLU:
			bDir = ULD;
			break;
		case DL:
			bDir = UL;
			break;
		case DLD:
			bDir = ULU;
			break;
		}
	}
	else return;

	//Tang toc do qua banh sau khi cham voi paddle
	if (Ball::speed != 9)
		Ball::speed++;
}


	


bool Ball::check_Scored_Condition(Paddle * p)	//Kiem tra truong hop do hut banh
{
	if (p->Center_Pos.y < HeightCenter)
		return (Center_Pos.y - 1 == 1 && !check_Collide_Pad(p));

	else if (p->Center_Pos.y > HeightCenter) //Neu paddle nam nua duoi san dau
		return (Center_Pos.y + 1 == MapHeight && !check_Collide_Pad(p));

	return false;
}

void Ball::Restart()	//Tra qua banh ve vi tri giua map
{
	Old_Pos = Center_Pos;

	Center_Pos.x = WidthCenter;
	Center_Pos.y = HeightCenter;

	Ball::speed = 0;
	//Random lai huong di cua qua banh
	bDir = bDirection(rand() % 12);
}

void Ball::repaint_middle_line()	//Ve lai vach giua san
{
	textcolor(15);
	gotoxy(Old_Pos.x - radius, Old_Pos.y);

	for (int i = 0; i < 2*radius + 1; i++)
		putchar(254);
}

bool Ball::check_Override_Pad(Paddle *p)	//Kiem tra neu qua banh nam de len paddle
{
	if (Old_Pos.y == p->Center_Pos.y)
		return(Old_Pos.x >= p->Center_Pos.x - p->half_long && Old_Pos.x <= p->Center_Pos.x + p->half_long);
	return false;
}

void Ball::repaint_Pad()	//Ve lai phan ma paddle bi qua banh de len
{
	gotoxy(Old_Pos.x - radius, Old_Pos.y);
	for (int i = 0; i < radius * 2 + 1; i++)
	{
		putchar(254);
	}
}

Player::Player(int _first_yPos)
{
	Score = 0;
	first_yPos = _first_yPos;
	pad = new Paddle(first_yPos);
}

Player::~Player() {}

void Player::Score_Up()
{
	Score++;
}


