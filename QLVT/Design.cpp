#include "Design.h"

using namespace std;

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0, 0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void textbk(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void DrawBorder(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc)
{
	gotoXY(toaDoX, toaDoY); //goc trai tren
	cout << char(218);
	gotoXY(toaDoX, toaDoY + chieuDoc); 	//goc trai duoi
	cout << char(192);
	gotoXY(toaDoX + chieuNgang, toaDoY); //goc phai tren
	cout << char(191);
	gotoXY(toaDoX + chieuNgang, toaDoY + chieuDoc); //goc phai duoi
	cout << char(217);

	//ve hang
	gotoXY(toaDoX + 1, toaDoY);
	for (int i = 0; i < chieuNgang - 1; i++) {
		cout << char(196);
	}
	gotoXY(toaDoX + 1, toaDoY + chieuDoc);
	for (int i = 0; i < chieuNgang - 1; i++) {
		cout << char(196);
	}
	//ve cot
	for (int i = 0; i < chieuDoc - 1; i++) {
		gotoXY(toaDoX, toaDoY + i + 1);
		cout << char(179);
		gotoXY(toaDoX + chieuNgang, toaDoY + i + 1);
		cout << char(179);
	}
	cout << "\n";
}

void RemoveScroll()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(hstdout, csbi.dwSize);

	HWND x = GetConsoleWindow();
	ShowScrollBar(x, SB_BOTH, FALSE);
}

void fullScreen()
{
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

void DrawBorderList(int toaDoX, int toaDoY, int soDong, int soCot, int chieuNgangO, int chieuDocO)
{
	for (int i = 0; i < soDong; i++) {
		int tempX = toaDoX;
		for (int j = 0; j < soCot; j++) {
			DrawBorder(tempX, toaDoY, chieuNgangO, chieuDocO + 1);

			if (i == 0 && j > 0) {
				gotoXY(tempX, toaDoY);
				cout << char(194); //doi goc trai tren cua cac o hang tren cung			
			}
			if (i == soDong - 1 && j > 0) {
				gotoXY(tempX, toaDoY + chieuDocO + 1); //doi goc trai duoi cua cac o hang cuoi cung
				cout << char(193);
			}
			if (j == 0 && i > 0) {
				gotoXY(tempX, toaDoY);//doi goc trai tren cua nhung o cot dau tien
				cout << char(195);
			}
			if (j == soCot - 1 && i > 0) {
				gotoXY(tempX + chieuNgangO, toaDoY); //doi goc phai duoi cua nhung o cot cuoi cung
				cout << char(180);
			}
			if (j > 0 && j < soCot && i > 0 && i < soDong) {
				gotoXY(tempX, toaDoY); //con cac goc phai tren cua cac o con lai cho thanh dau cong la xong
				cout << char(197);
			}

			tempX += chieuNgangO;
		}
		toaDoY += chieuDocO + 1;
	}
}

string CenterTextInSpace(string center, int wide)
{
	string centered;
	centered.resize(wide, ' ');
	int centerStart = (wide - center.size()) / 2 + (wide - center.size()) % 2;
	for (int i = 0; i < center.size(); i++)
	{
		centered[centerStart + i] = center[i];
	}
	return centered;
}

void ClearInsideBox()
{
	string blankFill;
	blankFill.resize(CHIEUNGANG - 21, ' ');
	//	for (int i = 0; i < CHIEUNGANG - 23; i++)
	//		blankFill[i] = ' ';
	textbk(15);
	for (int i = 0; i < CHIEUDOC - 1; i++)
	{
		gotoXY(TOADOX + 21, TOADOY + 1 + i);
		cout << blankFill;
	}
}

Ngay StringToDate(string temp)
{
	Ngay result;
	result.date = 0;
	result.month = 0;
	result.year = 0;
	result.date = (int)(temp[0] - '0') * 10 + (int)(temp[1] - '0');
	result.month = (int)(temp[2] - '0') * 10 + (int)(temp[3] - '0');
	for (int i = 4; i < temp.length(); i++)
		result.year = result.year * 10 + (int)(temp[i] - '0');
	return result;
}

int DateCmp(Ngay no1, Ngay no2)
{
	if (no1.year > no2.year)
		return 1;
	else if (no1.month > no2.month && no1.year == no2.year)
		return 1;
	else if (no1.date > no2.date && no1.month == no2.month && no1.year == no2.year)
		return 1;
	if (no1.year < no2.year)
		return -1;
	else if (no1.month < no2.month && no1.year == no2.year)
		return -1;
	else if (no1.date < no2.date && no1.month == no2.month && no1.year == no2.year)
		return -1;
	return 0;
}

int CheckDate(Ngay thisDay)
{
	time_t ht = time(0);
	tm* now = localtime(&ht);
	Ngay temp;
	temp.date = now->tm_mday;
	temp.month = now->tm_mon + 1;
	temp.year = now->tm_year + 1900;
	if (thisDay.year <= 0 || thisDay.month <= 0 || thisDay.month > 12 || thisDay.date <= 0 || thisDay.date > 31)
		return 0;
	else if (DateCmp(temp, thisDay) == -1)
		return 0;
	else
	{
		if (thisDay.month == 4 || thisDay.month == 6 || thisDay.month == 9 || thisDay.month == 11)
		{
			if (thisDay.date <= 30)
				return 1;
		}
		else if (thisDay.month == 2)
		{
			if ((thisDay.year % 4 == 0 && thisDay.year % 100 != 0) || (thisDay.year % 400 == 0))
			{
				if (thisDay.date <= 29)
					return 1;
			}
			else
			{
				if (thisDay.date <= 28)
					return 1;
			}
		}
		else
			if (thisDay.date <= 31)
				return 1;
	}
	return 0;
}

string DateToString(Ngay value)
{
	string convert = "";
	convert += (int)value.date / 10 + '0';
	convert += value.date % 10 + '0';
	convert += (int)value.month / 10 + '0';
	convert += value.month % 10 + '0';
	int reverse = 0;
	do
	{
		reverse = reverse * 10 + value.year % 10;
		value.year /= 10;
	} while (value.year != 0);
	int i = 4;
	do
	{
		convert += (int)(reverse % 10) + '0';
		reverse /= 10;
	} while (reverse != 0);
	return convert;
}

int CheckString(string check, int checkKind)
{
	/*
		1 = check chuoi ky tu
		2 = check chuoi so
		3 = check chuoi
		4 = check chuoi khong khoang trang
		5 = check chuoi khong rong
		return dung = 1 or sai = 0
	*/
	if (checkKind == 1)
	{
		for (int i = 0; i < check.length(); i++)
		{
			if ((check[i] >= 'A' && check[i] <= 'Z') || (check[i] >= 'a' && check[i] <= 'z') || (check[i] == (char)SPACEBAR))
				continue;
			else
				return 0;
		}
	}
	else if (checkKind == 2)
	{
		for (int i = 0; i < check.length(); i++)
		{
			if ((check[i] >= '0' && check[i] <= '9') || check[i] == DOT)
				continue;
			else
				return 0;
		}
	}
	else if (checkKind == 3)
	{
		for (int i = 0; i < check.length(); i++)
		{
			if ((check[i] >= '0' && check[i] <= '9') || (check[i] >= 'A' && check[i] <= 'Z') || (check[i] >= 'a' && check[i] <= 'z') || check[i] == (char)SPACEBAR || check[i] == DOT)
				continue;
			else
				return 0;
		}
	}
	else if (checkKind == 4)
	{
		for (int i = 0; i < check.length(); i++)
		{
			if (check[i] != (char)SPACEBAR)
				continue;
			else
				return 0;
		}
	}
	else if (checkKind == 5)
	{
		if (check.length() == 0)
			return 0;
		else
			return 1;
	}
	//Nhieu kieu check se duoc them vao sau
	return 1;
}

void FixString(string & str, int mode)
{
	/*	mode 1: ABCD
		mode 2: Abcd
		mode 3: Ab Cd Ef
		mode 4: AB CD EF
		mode 5: 12345
		mode 6: 12 34 56
		mode 7: aBcdDef123
		mode 8: 00/00/0000... (Nhap ngay)
		Co the them nhung mode khac,
		nhung hien tai chi can toi da nhat la nhung cai nay
	*/
	if (mode == 1 || mode == 2 || mode == 5 || mode == 7 || mode == 8)
	{
		//Xoa khoang trang
		if (str.length() == 0)
			return;
		int i = 0;
		while (i < str.length())
		{
			if (str[i] == ' ')
			{
				str.erase(i, 1);
				i--;
			}
			i++;
		}
	}
	if (mode == 3 || mode == 4 || mode == 6)
	{
		//Xoa khoang trang dau cuoi
		if (str.length() == 0)
			return;
		while (str[0] == ' ')
			str.erase(0, 1);
		while (str[str.length() - 1] == ' ')
			str.erase(str.length() - 1, 1);
		//Xoa khoang trang giua cac ky tu
		for (int i = 0; i < str.length() - 1; i++)
		{
			if (str[i] == ' ' && str[i + 1] == ' ')
			{
				str.erase(i, 1);
				i--;
			}
		}
		//In hoa ky tu dau
	}
	if (mode == 1 || mode == 4)
	{
		if (str.length() == 0)
			return;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] -= 32;
		}
	}
	if (mode == 2 || mode == 3 || mode == 6)
	{
		if (str.length() == 0)
			return;
		if (str[0] >= 'a' && str[0] <= 'z')
			str[0] -= 32;
		if (mode == 2 || mode == 3)
			for (int i = 1; i < str.length(); i++)
				if (str[i] >= 'A' && str[i] <= 'Z' && str[i - 1] != ' ')
					str[i] += 32;
		if (mode == 3)
			for (int i = 0; i < str.length() - 1; i++)
				if (str[i] == ' ' && str[i + 1] != ' ')
					if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
						str[i + 1] -= 32;
	}
	if (mode == 5 || mode == 6)
	{
		while (str.length() > 1 && str[0] == '0' && str[1] != '.')
			str.erase(0, 1);
	}
}

string DelFloatTrail(string & floatStr)
{
	while (floatStr[floatStr.length() - 1] == '0')
		floatStr.erase(floatStr.length() - 1, 1);
	if (floatStr[floatStr.length() - 1] == '.')
		floatStr.erase(floatStr.length() - 1);
	return floatStr;
}

void DrawMenu(int title)
{
	TextColor(4);
	textbk(15);
	gotoXY(TOADOX, TOADOY + 1 + CHIEUDOC);
	cout << CenterTextInSpace("", 146);
	gotoXY(TOADOX, TOADOY + 1 + CHIEUDOC);
	if (title == -1)
		cout << "UP/DOWN ARROW = Thay doi lua chon \tENTER = CHhon \tESC = Thoat";
	else if (title == VATTUTITLE)
		cout << "UP/DOWN ARROW = Thay doi vat tu \tENTER = Sua Vat Tu \tINSERT = Them Vat Tu \tDELETE = Xoa Vat Tu \tESC = Thoat";
	else if (title == VATTUTHEM)
		cout << "UP/DOWN ARROW = Thay doi thong tin nhap \tENTER = Chuan Hoa \tINSERT = Them Vat Tu \tESC = Thoat";
	else if (title == VATTUSUA)
		cout << "UP/DOWN ARROW = Thay doi thong tin nhap \tENTER = Chuan Hoa \tINSERT = Sua Vat Tu \tESC = Thoat";

	else if (title == NHANVIENTITLE)
		cout << "UP/DOWN ARROW = Thay doi nhan vien   ENTER = Xem Chi Tiet (Xem/Lap Hoa Don, Sua)   INSERT = Them Nhan Vien   DELETE = Xoa Nhan Vien   ESC = Thoat";
	else if (title == THEMNHANVIEN)
		cout << "UP/DOWN ARROW = Thay doi thong tin nhap \tENTER = Chuan Hoa \tINSERT = Them Nhan Vien \tESC = Thoat";
	else if (title == CHITIETNHANVIEN)
		cout << "LEFT/RIGHT ARROW = Thay doi lua chon \tENTER = CHON \tESC = THOAT";
	else if (title == SUANHANVIEN)
		cout << "UP/DOWN ARROW = Thay doi thong tin nhap \tENTER = Chuan Hoa \tINSERT = Sua Nhan Vien \tESC = Thoat";

	else if (title == HOADONTITLE)
		cout << "UP/DOWN ARROW = Thay doi lua chon \tENTER = CHON \tINSERT = Them Hoa Don \tESC = Thoat";
	else if (title == THEMHOADONTITLE)
		cout << "UP/DOWN ARROW = Thay doi lua chon \tENTER = Chuan Hoa \tINSERT = Nhap Vat Tu \tESC = Thoat";
	else if (title == INHOADONTITLE)
		cout << "UP/DOWN ARROW = Thay doi lua chon     INSERT = Tim Hoa Don    ENTER = CHON   CTRL+F = Tim Tat Ca Hoa Don   ESC = Thoat";
	else if (title == THONGKETITLE)
		cout << "UP/DOWN ARROW = Thay doi lua chon \tINSERT = Xem Thong Ke \tESC = Thoat";
	else if (title == THONGKEMENU)
		cout << "UP/DOWN ARROW = Thay doi lua chon \tENTER (In Hoa Don) = Xem Chi Tiet \tESC = Thoat";

	else if (title == CHITIETTITLE)
		cout << "UP/DOWN ARROW = Len/xuong \tESC = Tro ve";
	else if (title == TOPDTTITLE)
		cout << "UP/DOWN/LEFT/RIGHT ARROW = Thay doi thong tin nhap \tINS = Tinh Doanh Thu \tESC = Thoat";
	else if (title == TOPDTDANHSACH)
		cout << "UP/DOWN ARROW = Len/xuong \tESC = Tro ve";
	else if (title == THEMCHITIETHD)
		cout << "UP/DOWN ARROW = Thay doi thong tin nhap    INS = Them Vat Tu    ENTER = Chuan Hoa    CTRL+F = Tim Vat Tu    ESC = Thoat";
	else if (title == THEMCHITIETNEWHD)
		cout << "UP/DOWN ARROW = Thay doi lua chon    INS = Them Vat Tu    ENTER = Sua Vat Tu    DEL  = Xoa Vat Tu    ESC = Thoat";
	else if (title == SUACHITIETHD)
		cout << "UP/DOWN ARROW = Thay doi thong tin nhap    INS = Sua Vat Tu    ENTER = Chuan Hoa    CTRL+F = Tim Vat Tu    ESC = Thoat";
	TextColor(0);
	textbk(15);
}

int InputInfo(string & info, int maxChuoi, int posX, int posY, int& keyVar, int mode)
{
	TextColor(0);
	textbk(15);
	int currentCursor = info.length();
	gotoXY(posX, posY);
	cout << CenterTextInSpace("", maxChuoi);
	gotoXY(posX, posY);
	cout << info;
	while (true)
	{
		keyVar = _getch();
		if (keyVar == 224)
		{
			keyVar = _getch();
			if (keyVar == KEY_UP || keyVar == KEY_DOWN || keyVar == INS)
			{
				FixString(info, mode);
				gotoXY(posX + info.length(), posY);
				for (int i = info.length(); i <= maxChuoi; i++)
					cout << " ";
				gotoXY(posX, posY);
				cout << info;
				return keyVar;
			}
			else if (keyVar == DEL)
			{
				info.erase(currentCursor, 1);
				gotoXY(posX + currentCursor, posY);
				for (int i = currentCursor; i < info.length() + 1; i++)
					cout << " ";
				gotoXY(posX + currentCursor, posY);
				for (int i = currentCursor; i < info.length(); i++)
					cout << info[i];
				gotoXY(posX + currentCursor, posY);
				continue;
			}
			else if (keyVar == KEY_LEFT)
			{
				if (currentCursor > 0)
				{
					currentCursor--;
					gotoXY(posX + currentCursor, posY);
				}
				else if (mode == 8)
					return keyVar;
			}
			else if (keyVar == KEY_RIGHT)
			{
				if (currentCursor < info.length())
				{
					currentCursor++;
					gotoXY(posX + currentCursor, posY);
				}
				else if (mode == 8)
					return keyVar;
			}
		}
		else if (keyVar == ENTER || keyVar == ESC)
		{
			FixString(info, mode);
			gotoXY(posX + info.length(), posY);
			for (int i = info.length(); i <= maxChuoi; i++)
				cout << " ";
			gotoXY(posX, posY);
			cout << info;
			return keyVar;
		}
		else if (keyVar == BACKSPACE && info.length() != 0 && currentCursor > 0)
		{
			info.erase(--currentCursor, 1);
			gotoXY(posX + currentCursor, posY);
			for (int i = currentCursor; i < info.length() + 1; i++)
				cout << " ";
			gotoXY(posX + currentCursor, posY);
			for (int i = currentCursor; i < info.length(); i++)
				cout << info[i];
			gotoXY(posX + currentCursor, posY);
		}
		else if ((keyVar >= 'a' && keyVar <= 'z' || keyVar >= 'A' && keyVar <= 'Z' || keyVar >= '0' && keyVar <= '9' || keyVar == SPACEBAR || keyVar == DOT) && info.length() < maxChuoi)
		{
			if ((mode == 5 || mode == 6 || mode == 8) && (keyVar >= 'a' && keyVar <= 'z' || keyVar >= 'A' && keyVar <= 'Z'))
				continue;
			if ((mode == 5 || mode == 6 || mode == 8) && keyVar == DOT)
			{
				if (mode == 8)
					continue;
				int conti = 0;
				for (int i = 0; i < info.length(); i++)
					if (info[i] == DOT)
					{
						conti = 1;
						break;
					}
				if (conti == 1)
					continue;
			}
			info.insert(currentCursor, 1, char(keyVar));
			for (int i = currentCursor; i < info.length(); i++)
				cout << info[i];
			currentCursor++;
			gotoXY(posX + currentCursor, posY);
		}
	}
}

string CharToString(char* c)
{
	int i = 0;
	string result;
	while (c[i] != '\0')
	{
		result += c[i];
		i++;
	}
	return result;
}

int ChooseOption(char arr[][15], int posX, int posY, int soOption, int spaceBetween, int lock)
{
	int startX = posX - (int)((soOption * 17 + (soOption - 1) * spaceBetween) / 2);
	int startY = posY - 1;
	int keyHit = 0;
	int choice = 0;
	TextColor(MAUCHUX);
	textbk(MAUNENX);
	gotoXY(startX + 1, posY);
	cout << CenterTextInSpace(CharToString(arr[0]), 15);
	TextColor(MAUCHUX);
	textbk(MAUNENO);
	while (true)
	{
		keyHit = _getch();
		if (soOption <= 1)
		{
			if (keyHit == ENTER)
				return 0;
			else if (keyHit == ESC)
				return soOption;
			else if (lock != 1)
			{
				gotoXY(startX + choice * (17 + spaceBetween) + 1, posY);
				cout << CenterTextInSpace(CharToString(arr[choice]), 15);
				return -keyHit;
			}
		}
		else if (keyHit == 224)
		{
			keyHit = _getch();
			switch (keyHit)
			{
			case KEY_LEFT:
			{
				gotoXY(startX + choice * (17 + spaceBetween) + 1, posY);
				cout << CenterTextInSpace(CharToString(arr[choice]), 15);
				if (choice > 0)
					choice--;
				else choice = soOption - 1;
				break;
			}
			case KEY_RIGHT:
			{
				gotoXY(startX + choice * (17 + spaceBetween) + 1, posY);
				cout << CenterTextInSpace(CharToString(arr[choice]), 15);
				if (choice < soOption - 1)
					choice++;
				else choice = 0;
				break;
			}
			default:
			{
				if (lock != 1)
				{
					gotoXY(startX + choice * (17 + spaceBetween) + 1, posY);
					cout << CenterTextInSpace(CharToString(arr[choice]), 15);
					return -keyHit;
					break;
				}
				break;
			}
			}
		}
		else if (keyHit == ENTER)
		{
			return choice;
		}
		else if (keyHit == ESC)
			return soOption;
		else if (lock != 1)
			return -keyHit;
		TextColor(MAUCHUX);
		textbk(MAUNENX);
		gotoXY(startX + choice * (17 + spaceBetween) + 1, posY);
		cout << CenterTextInSpace(CharToString(arr[choice]), 15);
		TextColor(MAUCHUX);
		textbk(MAUNENO);
	}
}

void DrawOptionChoice(char arr[][15], int posX, int posY, int soOption, int spaceBetween)
{
	int startX = posX - (int)((soOption * 17 + (soOption - 1) * spaceBetween) / 2);
	int startY = posY - 1;
	if (startX < 0 || startY < 0 || (posX - startX) + posX > CHIEUNGANG || posY + 1 > CHIEUDOC)
	{
		clrscr();
		cout << "O lua chon vuot qua khung man hinh" << endl;
		exit(0);
	}
	TextColor(MAUCHUX);
	textbk(MAUNENO);
	for (int i = 0; i < soOption; i++)
	{
		TextColor(MAUCHUO);
		textbk(MAUNENO);
		DrawBorder(startX + i * (17 + spaceBetween), startY, 16, 2);
		TextColor(MAUCHUX);
		textbk(MAUNENO);
		gotoXY(startX + i * (17 + spaceBetween) + 1, posY);
		cout << CenterTextInSpace(CharToString(arr[i]), 15);
	}
}

int DrawNoti(char context[][78], char arr[][15], int soOption)
{
	DrawBorder(57, 15, 80, 15);
	for (int i = 0; i < 14; i++)
	{
		if (i < 10)
		{
			gotoXY(58, 16 + i);
			cout << CenterTextInSpace(CharToString(context[i]), 79);
		}
		else
		{
			gotoXY(58, 16 + i);
			cout << CenterTextInSpace("", 79);
		}
	}
	DrawOptionChoice(arr, 97, 28, soOption, 1);
	return ChooseOption(arr, 97, 28, soOption, 1, 1);
	//Example max choice and context
	//char arr[4][15] = { "1","2","3","4" };
	//char str[10][78] =
	//{
	//	"",
	//	"This is a test string",
	//	"It contain a lot of line",
	//	"I'll test it with the maximum amount of line = 10",
	//	"The line after gonna be a maximum string the you can write on a line",
	//	".............................................................................",
	//	"About that much, you can copy it and insert on it to be sure and more secure",
	//	"All the context will be centered inside the box",
	//	"I say it is 10 but you have to be care full, because the choose box",
	//	"This is the 9 line, i suggest you stop here",
	//};
}

string IntToString(int a)
{
	string result;
	while (a != 0) {
		result += a % 10 + '0';
		a /= 10;
	}
	for (int i = 0; i < result.length() / 2; i++)
	{
		swap(result[i], result[result.length() - 1 - i]);
	}
	return result;
}

int StringToInt(string str)
{
	int result = 0;
	for (int i = 0; i < str.length(); i++)
	{
		result = result * 10 + (int)(str[i] - '0');
	}
	return result;
}

void DrawTitle(int title, int posX, int posY)
{
	TextColor(4);
	textbk(15);
	if (title == VATTUTITLE)
	{
		char inTitle[6][120] =
		{
			"  _____                 _        _____               _      __      __     _     _______     ",
			" |  __ \\               | |      / ____|             | |     \\ \\    / /    | |   |__   __|    ",
			" | |  | |  __ _  _ __  | |__   | (___    __ _   ___ | |__    \\ \\  / /__ _ | |_     | | _   _ ",
			" | |  | | / _` || '_ \\ | '_ \\   \\___ \\  / _` | / __|| '_ \\    \\ \\/ // _` || __|    | || | | |",
			" | |__| || (_| || | | || | | |  ____) || (_| || (__ | | | |    \\  /| (_| || |_     | || |_| |",
			" |_____/  \\__,_||_| |_||_| |_| |_____/  \\__,_| \\___||_| |_|     \\/  \\__,_| \\__|    |_| \\__,_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	if (title == NHANVIENTITLE)
	{
		char inTitle[6][120] =
		{
			"  _____                 _        _____               _       _   _  _                    __      __ _              ",
			" |  __ \\               | |      / ____|             | |     | \\ | || |                   \\ \\    / /(_)             ",
			" | |  | |  __ _  _ __  | |__   | (___    __ _   ___ | |__   |  \\| || |__    __ _  _ __    \\ \\  / /  _   ___  _ __  ",
			" | |  | | / _` || '_ \\ | '_ \\   \\___ \\  / _` | / __|| '_ \\  | . ` || '_ \\  / _` || '_ \\    \\ \\/ /  | | / _ \\| '_ \\ ",
			" | |__| || (_| || | | || | | |  ____) || (_| || (__ | | | | | |\\  || | | || (_| || | | |    \\  /   | ||  __/| | | |",
			" |_____/  \\__,_||_| |_||_| |_| |_____/  \\__,_| \\___||_| |_| |_| \\_||_| |_| \\__,_||_| |_|     \\/    |_| \\___||_| |_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}

	else if (title == CHITIETTITLE)
	{
		char inTitle[6][120] =
		{
			"  _____                 _        _____               _        _____  _      _   _______  _        _   ",
			" |  __ \\               | |      / ____|             | |      / ____|| |    (_) |__   __|(_)      | |  ",
			" | |  | |  __ _  _ __  | |__   | (___    __ _   ___ | |__   | |     | |__   _     | |    _   ___ | |_ ",
			" | |  | | / _` || '_ \\ | '_ \\   \\___ \\  / _` | / __|| '_ \\  | |     | '_ \\ | |    | |   | | / _ \\| __|",
			" | |__| || (_| || | | || | | |  ____) || (_| || (__ | | | | | |____ | | | || |    | |   | ||  __/| |_ ",
			" |_____/  \\__,_||_| |_||_| |_| |_____/  \\__,_| \\___||_| |_|  \\_____||_| |_||_|    |_|   |_| \\___| \\__|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == THEMNHANVIEN)
	{
		char inTitle[6][120] =
		{
			"  _______  _                        _   _  _                    __      __ _              ",
			" |__   __|| |                      | \\ | || |                   \\ \\    / /(_)             ",
			"    | |   | |__    ___  _ __ ___   |  \\| || |__    __ _  _ __    \\ \\  / /  _   ___  _ __  ",
			"    | |   | '_ \\  / _ \\| '_ ` _ \\  | . ` || '_ \\  / _` || '_ \\    \\ \\/ /  | | / _ \\| '_ \\ ",
			"    | |   | | | ||  __/| | | | | | | |\\  || | | || (_| || | | |    \\  /   | ||  __/| | | |",
			"    |_|   |_| |_| \\___||_| |_| |_| |_| \\_||_| |_| \\__,_||_| |_|     \\/    |_| \\___||_| |_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == SUANHANVIEN)
	{
		char inTitle[6][120] =
		{
			"   _____                 _   _  _                    __      __ _              ",
			"  / ____|               | \\ | || |                   \\ \\    / /(_)             ",
			" | (___   _   _   __ _  |  \\| || |__    __ _  _ __    \\ \\  / /  _   ___  _ __  ",
			"  \\___ \\ | | | | / _` | | . ` || '_ \\  / _` || '_ \\    \\ \\/ /  | | / _ \\| '_ \\ ",
			"  ____) || |_| || (_| | | |\\  || | | || (_| || | | |    \\  /   | ||  __/| | | |",
			" |_____/  \\__,_| \\__,_| |_| \\_||_| |_| \\__,_||_| |_|     \\/    |_| \\___||_| |_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == CHITIETNHANVIEN || title == THEMCHITIETNEWHD)
	{
		char inTitle[6][120] =
		{
			"   _____  _      _   _______  _        _     _   _  _                    __      __ _              ",
			"  / ____|| |    (_) |__   __|(_)      | |   | \\ | || |                   \\ \\    / /(_)             ",
			" | |     | |__   _     | |    _   ___ | |_  |  \\| || |__    __ _  _ __    \\ \\  / /  _   ___  _ __  ",
			" | |     | '_ \\ | |    | |   | | / _ \\| __| | . ` || '_ \\  / _` || '_ \\    \\ \\/ /  | | / _ \\| '_ \\ ",
			" | |____ | | | || |    | |   | ||  __/| |_  | |\\  || | | || (_| || | | |    \\  /   | ||  __/| | | |",
			"  \\_____||_| |_||_|    |_|   |_| \\___| \\__| |_| \\_||_| |_| \\__,_||_| |_|     \\/    |_| \\___||_| |_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == TOPDTTITLE)
	{
		char inTitle[6][120] =
		{
			"  _______ ____  _____    _____                    _       _______ _           ",
			" |__   __/ __ \\|  __ \\  |  __ \\                  | |     |__   __| |          ",
			"    | | | |  | | |__) | | |  | | ___   __ _ _ __ | |__      | |  | |__  _   _ ",
			"    | | | |  | |  ___/  | |  | |/ _ \\ / _` | '_ \\| '_ \\     | |  | '_ \\| | | |",
			"    | | | |__| | |      | |__| | (_) | (_| | | | | | | |    | |  | | | | |_| |",
			"    |_|  \\____/|_|      |_____/ \\___/ \\__,_|_| |_|_| |_|    |_|  |_| |_|\\__,_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == VATTUTHEM)
	{
		char inTitle[6][120] =
		{
			"  _______ _                     __      __   _     _______    ",
			" |__   __| |                    \\ \\    / /  | |   |__   __|   ",
			"    | |  | |__   ___ _ __ ___    \\ \\  / /_ _| |_     | |_   _ ",
			"    | |  | '_ \\ / _ \\ '_ ` _ \\    \\ \\/ / _` | __|    | | | | |",
			"    | |  | | | |  __/ | | | | |    \\  / (_| | |_     | | |_| |",
			"    |_|  |_| |_|\\___|_| |_| |_|     \\/ \\__,_|\\__|    |_|\\__,_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == VATTUSUA)
	{
		char inTitle[6][120] =
		{
			"   _____              __      __   _     _______    ",
			"  / ____|             \\ \\    / /  | |   |__   __|   ",
			" | (___  _   _  __ _   \\ \\  / /_ _| |_     | |_   _ ",
			"  \\___ \\| | | |/ _` |   \\ \\/ / _` | __|    | | | | |",
			"  ____) | |_| | (_| |    \\  / (_| | |_     | | |_| |",
			" |_____/ \\__,_|\\__,_|     \\/ \\__,_|\\__|    |_|\\__,_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == HOADONTITLE)
	{
		char inTitle[6][120] =
		{
			"  _____              _        _____            _       _    _               _____              ",
			" |  __ \\            | |      / ____|          | |     | |  | |             |  __ \\             ",
			" | |  | | __ _ _ __ | |__   | (___   __ _  ___| |__   | |__| | ___   __ _  | |  | | ___  _ __  ",
			" | |  | |/ _` | '_ \\| '_ \\   \\___ \\ / _` |/ __| '_ \\  |  __  |/ _ \\ / _` | | |  | |/ _ \\| '_ \\ ",
			" | |__| | (_| | | | | | | |  ____) | (_| | (__| | | | | |  | | (_) | (_| | | |__| | (_) | | | |",
			" |_____/ \\__,_|_| |_|_| |_| |_____/ \\__,_|\\___|_| |_| |_|  |_|\\___/ \\__,_| |_____/ \\___/|_| |_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}

	else if (title == THEMHOADONTITLE)
	{
		char inTitle[6][120] =
		{
				"  _______ _                      _    _               _____              ",
				" |__   __| |                    | |  | |             |  __ \\             ",
				"    | |  | |__   ___ _ __ ___   | |__| | ___   __ _  | |  | | ___  _ __  ",
				"    | |  | '_ \\ / _ \\ '_ ` _ \\  |  __  |/ _ \\ / _` | | |  | |/ _ \\| '_ \\ ",
				"    | |  | | | |  __/ | | | | | | |  | | (_) | (_| | | |__| | (_) | | | |",
				"    |_|  |_| |_|\\___|_| |_| |_| |_|  |_|\\___/ \\__,_| |_____/ \\___/|_| |_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == INHOADONTITLE)
	{
		char inTitle[6][120] =
		{
			"  _____         _    _               _____              ",
			" |_   _|       | |  | |             |  __ \\             ",
			"   | |  _ __   | |__| | ___   __ _  | |  | | ___  _ __  ",
			"   | | | '_ \\  |  __  |/ _ \\ / _` | | |  | |/ _ \\| '_ \\ ",
			"  _| |_| | | | | |  | | (_) | (_| | | |__| | (_) | | | |",
			" |_____|_| |_| |_|  |_|\\___/ \\__,_| |_____/ \\___/|_| |_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == THONGKETITLE)
	{
		char inTitle[8][120] =
		{
			"  _______ _                         _  __    ",
			" |__   __| |                       | |/ /    ",
			"    | |  | |__   ___  _ __   __ _  | ' / ___ ",
			"    | |  | '_ \\ / _ \\| '_ \\ / _` | |  < / _ \\",
			"    | |  | | | | (_) | | | | (_| | | . \\  __/",
			"    |_|  |_| |_|\\___/|_| |_|\\__, | |_|\\_\\___|",
			"                             __/ |           ",
			"                            |___/            "
		};
		for (int i = 0; i < 8; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == THEMCHITIETHD)
	{
		char inTitle[6][120] =
		{
			"  _______ _                     __      __   _     _______    ",
			" |__   __| |                    \\ \\    / /  | |   |__   __|   ",
			"    | |  | |__   ___ _ __ ___    \\ \\  / __ _| |_     | |_   _ ",
			"    | |  | '_ \\ / _ | '_ ` _ \\    \\ \\/ / _` | __|    | | | | |",
			"    | |  | | | |  __| | | | | |    \\  | (_| | |_     | | |_| |",
			"    |_|  |_| |_|\\___|_| |_| |_|     \\/ \\__,_|\\__|    |_|\\__,_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	else if (title == SUACHITIETHD)
	{
		char inTitle[6][120] =
		{
			"   _____              __      __   _     _______    ",
			"  / ____|             \\ \\    / /  | |   |__   __|   ",
			" | (___  _   _  __ _   \\ \\  / __ _| |_     | |_   _ ",
			"  \\___ \\| | | |/ _` |   \\ \\/ / _` | __|    | | | | |",
			"  ____) | |_| | (_| |    \\  | (_| | |_     | | |_| |",
			" |_____/ \\__,_|\\__,_|     \\/ \\__,_|\\__|    |_|\\__,_|"
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}
	TextColor(0);
	textbk(15);
	/*else if (title == )
	{
		char inTitle[6][120] =
		{
			"",
			"",
			"",
			"",
			"",
			""
		};
		for (int i = 0; i < 6; i++)
		{
			gotoXY(posX, posY + i);
			cout << inTitle[i];
		}
	}*/
}
