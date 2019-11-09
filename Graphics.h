#pragma once
#pragma warning(disable: 4996)
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <conio.h>

using namespace std;



#define MapWidth 69 // tọa độ Xmax của Map
#define MapHeight 39 // tọa độ Ymax của Map
#define WidthCenter  35  // tọa độ chính giữa chiều rộng Map
#define HeightCenter 20  // tọa độ chính giữa chiều cao Map
#define GuideWidth   30 // độ rộng max của bảng hưởng dẫn
#define GuideHeigh   40 // độ cao max của bảng hướng dẫn
#define WidthMenu    35 // độ rộng max của Menu
#define HeighMenu    20 // độ cao max của Menu

#define dack		0
#define darkBlue	1
#define darkGreen	2
#define darkCyan	3
#define darkRed		4
#define darkPink	5
#define darkYellow	6
#define darkWhite	7
#define grey		8
#define blue		9
#define green		10
#define cyan		11
#define red			12
#define pink		13
#define yellow		14
#define white		15


// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height);

// Hàm tô màu.
void textcolor(int x);

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x, int y);

// Hàm xóa màn hình.
void XoaManHinh();
void AnConTro();



