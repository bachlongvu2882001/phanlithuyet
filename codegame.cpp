#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "console.h"
#define consoleWidth	80
#define consoleHeight	25
#define roadWidth		25
#include <windows.h>
//hien thi toa do: goto [x,y]
void gotoXY (int cot, int hang)
{
	COORD toado;
	toado.X = cot;
	toado.Y = hang;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),toado);
}

struct ToaDo
{
	int y, x;	
};
struct HinhDang
{
	char a[3][3];
};


struct Xe
{
	ToaDo td;	// tọa độ tại vị trí hd.a[1][1]
	HinhDang hd;
	int diem;
};


struct VatCan
{
	ToaDo td;
	HinhDang hd;
};


void KhoiTao (Xe &xe, VatCan &vc)
{
	//------ Xe
#define pHD xe.hd.a

	xe.diem = 0;
	xe.td.y = consoleHeight - 2;
	xe.td.x = roadWidth / 2;

	pHD[0][0] = pHD[0][2] = pHD[2][0] = pHD[2][2] = 'o';	// banh xe
	pHD[0][1] = '^';	// dau xe
	pHD[1][0] = pHD[1][2] = '|';	// than xe
	pHD[2][1] = '-';
	pHD[1][1] = ' ';


	//--------- vat can

	vc.td.x = 2 + rand() % (roadWidth - 4);
	vc.td.y = -2;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			vc.hd.a[i][j] = 173;
}


void HienThi (Xe xe, VatCan vc)
{
	system("cls");



	system("color 2");
	for (int i = 0; i < consoleHeight; i++)
		printf ("%c\n", 179);

	for (int i = 0; i < consoleHeight; i++)
	{
		gotoXY (roadWidth, i);
		putchar (179);
	}

	system("color 2");
	for (int kDong = -1; kDong <= 1; kDong++)
		for (int kCot = -1; kCot <= 1; kCot++)
		{
			int x = kCot + xe.td.x;
			int y = kDong + xe.td.y;

			gotoXY (x, y);
			putchar (xe.hd.a[kDong+1][kCot+1]);	//a[0][0] --> a[2][2]
		}


	// hien thi vat can
	system("color 2");
	for (int kDong = -1; kDong <= 1; kDong++)
		for (int kCot = -1; kCot <= 1; kCot++)
		{
			int x = kCot + vc.td.x;
			int y = kDong + vc.td.y;

			if (y >= 0 && y < consoleHeight)
			{
				gotoXY (x, y);
				putchar (vc.hd.a[kDong+1][kCot+1]);	//a[0][0] --> a[2][2]
			}
		}


	// hien thi trang thai game
	gotoXY (roadWidth + 2, 10);
	printf ("Diem = %d", xe.diem);
}


void DieuKhien (Xe &xe)
{
	if (_kbhit())
	{
		int key = _getch();

		if ((key == 'A' || key == 'a') && xe.td.x > 2)
			xe.td.x--;
		else if ((key == 'D' || key == 'd') && xe.td.x < roadWidth - 2)
			xe.td.x++;
	}
}

// tra ve 0 neu khong co gi
// tra ve -1 la va cham
int XuLy (Xe &xe, VatCan &vc)
{
	// tao cam giac xe di chuyen--> vat can di xuong duoi
	vc.td.y++;


	// neu vat can di xuong duoi day tuc la xe da vuot qua vat can
	// thi tang diem
	if (vc.td.y > consoleHeight)
	{
		xe.diem++;
		vc.td.x = 2 + rand() % (roadWidth - 4);
		vc.td.y = -2;
	
	}

	// xu li tinh huong va cham
	int dX = abs (xe.td.x - vc.td.x);
	int dY = abs (xe.td.y - vc.td.y);

	if (dX < 3 && dY < 3)
	{
		return -1;
	}


	return 0;
}

int main()
{
	srand (time (NULL));	// khoi tao bo xin so ngau nhien

	Xe xe;
	VatCan vc;
	
	KhoiTao (xe, vc);

	int ma = 0;
	while (1)
	{
		// hien thi
		HienThi (xe, vc);

		// dieu khien
		DieuKhien (xe);
		
		// xu li
		ma = XuLy (xe, vc);

		// game over
		if (ma == -1)
		{
			gotoXY (0,0);
			printf ("Ban thua game rui, liu liu :P ");

			while (_getch() != 13)	;

			break;
		}

		Sleep (200);
	}

	return 0;
}
