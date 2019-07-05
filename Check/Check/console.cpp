#include"console.h"

int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}


//-------------------------Screen-------------------------
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


//screen: goto [x,y]
void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//screen: get [x]
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}


//screen: get [y]
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}


void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


/* ======================================= HÀM XỬ LÍ ĐỘ HỌA ======================================= */

// hàm vẽ khung băt đầu tại tọa độ (x, y) với chiều dài width và chiều cao height
void Ve_Khung(int x, int y, int width, int height)
{
	char a = 218, b = 196, c = 191, d = 179, e = 192, f = 217;//Ki tu dac biet 
	gotoXY(x, y);
	cout << a;                // goc tren trai
	for (int i = 1; i < width; i++){
		gotoXY(x + i, y);
		cout << b;
	}
	gotoXY(x + width, y);     // goc tren phai
	cout << c;
	for (int i = 1; i < height; i++){
		gotoXY(x, y + i);
		cout << d;
	}
	gotoXY(x, y + height);    // goc duoi trai
	cout << e;
	for (int i = 1; i < width; i++){
		gotoXY(x + i, y + height);
		cout << b;
	}
	gotoXY(x + width, y + height);   // goc duoi phai
	cout << f;
	for (int i = 1; i < height; i++){
		gotoXY(x + width, y + i);
		cout << d;
	}
}

//ẩn đi con trỏ chỉ vị nhấp nháy trên màn hình, Xu_Li_Con_Tro_Chi_Vi(0) -> Ẩn con trỏ ------- Xu_Li_Con_Tro_Chi_Vi(1)-> hiện lại con trỏ
void Xu_Li_Con_Tro_Chi_Vi(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

// vẽ đường thẳng ngang từ tọa độ (x0, y) đến (x1, y)
void linex(int x0, int x1, int y)
{
	gotoXY(x0, y);
	for (int i = x0; i < x1; i++)
	{
		cout << char(196);
	}
}

//vẽ đường thẳng dọc từ tọa độ (x, y0) đến (x, y1)
void liney(int y0, int y1, int x)
{
	for (int i = y0; i <= y1; i++)
	{
		gotoXY(x, i);
		cout << char(179);
	}
	gotoXY(whereX(), y0);
}

void chose(int x0, int y0, int x1, int y1, int loai)
{
	if (loai == 1)
	{
		gotoXY(x0, y0);	 cout << char(218);
		gotoXY(x0, y1);	cout << char(192);
		gotoXY(x1, y0);	cout << char(191);
		gotoXY(x1, y1);	cout << char(217);

		for (int i = x0 + 1; i < x1; i++)
		{
			gotoXY(i, y0);	cout << char(196);
			gotoXY(i, y1);	cout << char(196);
		}

		for (int i = y0 + 1; i < y1; i++)
		{
			gotoXY(x0, i);	cout << char(179);
			gotoXY(x1, i);	cout << char(179);
		}
	}

	if (loai == 2)
	{
		gotoXY(x0, y0);	 cout << char(201);
		gotoXY(x0, y1);	cout << char(200);
		gotoXY(x1, y0);	cout << char(187);
		gotoXY(x1, y1);	cout << char(188);

		for (int i = x0 + 1; i < x1; i++)
		{
			gotoXY(i, y0);	cout << char(205);
			gotoXY(i, y1);	cout << char(205);
		}

		for (int i = y0 + 1; i < y1; i++)
		{
			gotoXY(x0, i);	cout << char(186);
			gotoXY(x1, i);	cout << char(186);
		}
	}
	if (loai == 0)
	{
		for (int i = x0; i <= x1; i++)
		{
			gotoXY(i, y0);
			cout << " ";
			gotoXY(i, y1);
			cout << " ";
		}

		for (int i = y0; i <= y1; i++)
		{
			gotoXY(x0, i);
			cout << " ";
			gotoXY(x1, i);
			cout << " ";
		}
	}
}


// ========= CĂN LỀ CHO CHUỖI
// căn giữa
void aligncenter(string s, int y)
{
	gotoXY(39 - s.length() / 2, y);
	cout << s;
}
// căn trái n kí tự
void alignleft(string s, int n)
{
	gotoXY(n, whereY());
	cout << s;
}
// căn phải n kí tự
void alignright(string s, int n)
{
	gotoXY(80 - n - s.length(), whereY());
	cout << s;
}


//mau nen chu
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

//nhan phim tu keyboard
bool checkKey(int key)
{
	return GetAsyncKeyState(key);
}

int khungyesno(int x, int y)
{
	Xu_Li_Con_Tro_Chi_Vi(0);
	//chose(x, y, x + 30, y + 14, 2);
	chose(x, y, x + 30, y + 14, 2);
	gotoXY(x + 9, y + 7);	cout << " CO ";
	gotoXY(x + 17, y + 7);	cout << " KHONG ";
	int chon = 0;
	chose(x + 16, y + 6, x + 24, y + 8, 1);
	Beep(400, 100);
	Sleep(100);
	Beep(800, 200);
	while (getch() != 13)
	{
		char t = getch();
		if (checkKey(VK_LEFT) || checkKey(VK_RIGHT))	{
			if (chon == 0)	{
				chon = 1;
				chose(x + 8, y + 6, x + 13, y + 8, 1);
				chose(x + 16, y + 6, x + 24, y + 8, 0);
				Beep(500, 150);
			}
			else 		{
				chon = 0;
				chose(x + 16, y + 6, x + 24, y + 8, 1);
				chose(x + 8, y + 6, x + 13, y + 8, 0);
				Beep(500, 150);
			}
		}
	}
	gotoXY(x + 30, y + 17);
	Xu_Li_Con_Tro_Chi_Vi(1);
	// xóa cái khung yes - no
	for (int i = y; i <= y + 14; i++)
	{
		gotoXY(x, i);
		cout << "                                   ";
	}
	return chon;

}

// khung thông báo kiểm tra mã trùng
int khungthongbaotontai(int x, int y)
{
	Xu_Li_Con_Tro_Chi_Vi(0);
	chose(x, y, x + 30, y + 14, 2);
	gotoXY(x + 12, y + 7);	cout << " THOAT ";
	int chon = 1;
	chose(x + 11, y + 6, x + 19, y + 8, 1);
	Beep(400, 100);
	Sleep(100);
	Beep(800, 200);
	while (getch() != 13)
	{
		char t = getch();
		if (checkKey(VK_LEFT) || checkKey(VK_RIGHT))	{
			if (chon == 1)	{
				chon = 1;
				chose(x + 11, y + 6, x + 19, y + 8, 1);
				Beep(500, 150);
			}
		}
	}
	gotoXY(x + 30, y + 17);
	Xu_Li_Con_Tro_Chi_Vi(1);
	// xóa cái khung yes - no
	for (int i = y; i <= y + 14; i++)
	{
		gotoXY(x, i);
		cout << "                                   ";
	}
	return chon;
}


int khungcapnhatsinhvien(int x, int y)
{
	Xu_Li_Con_Tro_Chi_Vi(0);
	chose(x, y, x + 30, y + 14, 2);
	gotoXY(x + 2, y + 7);	cout << " THEM "; // trả về 1
	gotoXY(x + 13, y + 7);	cout << " XOA "; // trả về 0
	gotoXY(x + 23, y + 7);	cout << " SUA "; // trả về 2
	gotoXY(x + 13, y + 11);	cout << " THOAT "; // trả về 2

	int chon = 1;
	chose(x + 1, y + 6, x + 8, y + 8, 1); // thêm

	Beep(400, 100);
	Sleep(100);
	Beep(800, 200);

	while (getch() != 13)
	{
		bool left = false;
		char t = getch();
		if ((left = checkKey(VK_LEFT)) || checkKey(VK_RIGHT))
		{

			if (chon == 0)
			{
				if (left == true)
				{
					chon = 1;
					chose(x + 1, y + 6, x + 8, y + 8, 1); // thêm
					chose(x + 22, y + 6, x + 28, y + 8, 0); // sửa
					chose(x + 12, y + 6, x + 18, y + 8, 0); // xóa
					chose(x + 12, y + 10, x + 20, y + 12, 0); // thoát	
				}
				else
				{
					chon = 2;
					chose(x + 22, y + 6, x + 28, y + 8, 1); // sửa
					chose(x + 12, y + 6, x + 18, y + 8, 0); // xóa
					chose(x + 1, y + 6, x + 8, y + 8, 0); // thêm
					chose(x + 12, y + 10, x + 20, y + 12, 0); // thoát	
				}
				Beep(500, 150);

			}
			else if (chon == 1)
			{
				if (left == true)
				{
					chon = 2;
					chose(x + 22, y + 6, x + 28, y + 8, 1); // sửa
					chose(x + 1, y + 6, x + 8, y + 8, 0); // thêm
					chose(x + 12, y + 6, x + 18, y + 8, 0); // xóa
					chose(x + 12, y + 10, x + 20, y + 12, 0); // thoát	
				}
				else
				{
					chon = 0;
					chose(x + 12, y + 6, x + 18, y + 8, 1); // xóa
					chose(x + 22, y + 6, x + 28, y + 8, 0); // sửa
					chose(x + 1, y + 6, x + 8, y + 8, 0); // thêm
					chose(x + 12, y + 10, x + 20, y + 12, 0); // thoát	
				}
				Beep(500, 150);
			}
			else
			{
				if (left == true)
				{
					chon = 0;
					chose(x + 12, y + 6, x + 18, y + 8, 1); // xóa
					chose(x + 22, y + 6, x + 28, y + 8, 0); // sửa
					chose(x + 1, y + 6, x + 8, y + 8, 0); // thêm					
					chose(x + 12, y + 10, x + 20, y + 12, 0); // thoát	
				}
				else
				{
					chon = 1;
					chose(x + 1, y + 6, x + 8, y + 8, 1); // thêm
					chose(x + 22, y + 6, x + 28, y + 8, 0); // sửa
					chose(x + 12, y + 6, x + 18, y + 8, 0); // xóa
					chose(x + 12, y + 10, x + 20, y + 12, 0); // thoát	
				}
				Beep(500, 150);
			}
		}
		else if (checkKey(VK_UP) || checkKey(VK_DOWN))
		{
			if (chon != 3)
			{
				chon = 3;
				chose(x + 12, y + 10, x + 20, y + 12, 1); // thoát
				chose(x + 1, y + 6, x + 8, y + 8, 0); // thêm
				chose(x + 22, y + 6, x + 28, y + 8, 0); // sửa
				chose(x + 12, y + 6, x + 18, y + 8, 0); // xóa		
				Beep(500, 150);
			}
			else
			{
				chon = 0;
				chose(x + 1, y + 6, x + 8, y + 8, 1); // thêm
				chose(x + 12, y + 10, x + 20, y + 12, 0); // thoát
				chose(x + 22, y + 6, x + 28, y + 8, 0); // sửa
				chose(x + 12, y + 6, x + 18, y + 8, 0); // xóa	
				Beep(500, 150);

			}
		}
	}

	Xu_Li_Con_Tro_Chi_Vi(1);
	gotoXY(x + 30, y + 17);
	// xóa cái khung hiện tại
	for (int i = y; i <= y + 14; i++)
	{
		gotoXY(x, i);
		cout << "                                   ";
	}
	return chon;
}

int khungync(int x, int y)
{
	chose(x, y, x + 30, y + 14, 2);
	gotoXY(x + 9, y + 7);	cout << " YES ";
	gotoXY(x + 17, y + 7);	cout << " NO  ";
	gotoXY(x + 12, y + 11);	cout << "CANCLE";
	int chon = 0;
	chose(x + 16, y + 6, x + 22, y + 8, 1);
	Beep(400, 100);
	Sleep(100);
	Beep(800, 200);
	while (getch() != 13)
	{
		char t = getch();
		if (checkKey(VK_LEFT) || checkKey(VK_RIGHT))	{
			if (chon == 0)	{
				chon = 1;
				chose(x + 8, y + 6, x + 14, y + 8, 1);
				chose(x + 16, y + 6, x + 22, y + 8, 0);
				chose(x + 11, y + 10, x + 18, y + 12, 0);
				Beep(500, 150);
			}
			else 		{
				chon = 0;
				chose(x + 16, y + 6, x + 22, y + 8, 1);
				chose(x + 8, y + 6, x + 14, y + 8, 0);
				chose(x + 11, y + 10, x + 18, y + 12, 0);
				Beep(500, 150);
			}
		}
		if (checkKey(VK_UP) || checkKey(VK_DOWN))
		{
			if (chon != 3)
			{
				chon = 3;
				chose(x + 8, y + 6, x + 14, y + 8, 0);
				chose(x + 16, y + 6, x + 22, y + 8, 0);
				chose(x + 11, y + 10, x + 18, y + 12, 2);
			}
			else
			{
				chon = 0;
				chose(x + 8, y + 6, x + 14, y + 8, 0);
				chose(x + 16, y + 6, x + 22, y + 8, 1);
				chose(x + 11, y + 10, x + 18, y + 12, 0);
			}
		}
	}
	gotoXY(x + 30, y + 17);
	return chon;
}

void menutinh(string s[], int sodong, int y, int maunen, int mauchu, int mauchon, int &vitri)
{
	TextColor(10);
	chose(1, 0, 78, 24, 2);
	gotoXY(0, y);
	TextColor(mauchu);

	for (int i = 0; i < sodong; i++)
	{
		if (i == vitri)	{ TextColor(14); textbk(mauchon); aligncenter(s[i], whereY()); TextColor(mauchu); }
		else	{ textbk(maunen);	aligncenter(s[i], whereY()); }
		cout << endl << endl;
	}
	textbk(maunen);
}

void menu(string s[], int sodong, int y, int maunen, int mauchu, int mauchon, int &vitri)
{
	menutinh(s, sodong, y, maunen, mauchu, mauchon, vitri);
	while (getch() != 13)
	{
		if (checkKey(VK_UP))	{
			if (vitri == 0)	vitri = sodong - 1;
			else	vitri--;
			menutinh(s, sodong, y, maunen, mauchu, mauchon, vitri);
			Beep(500, 150);
		}



		if (checkKey(VK_DOWN))	{
			if (vitri == sodong - 1)	vitri = 0;
			else	vitri++;
			menutinh(s, sodong, y, maunen, mauchu, mauchon, vitri);
			Beep(500, 150);
		}
		if (checkKey(VK_ESCAPE))	{
			system("cls");
			aligncenter("BAN MUON THOAT???", 7);
			if (khungyesno(23, 5))	exit(1);
			else { system("cls");  menutinh(s, sodong, y, maunen, mauchu, mauchon, vitri); }
		}
	}
}

/* ======================================= HÀM XỬ LÍ NHẬP DỮ LIỆU ======================================= */
bool Kiem_Tra_Ki_Tu_So(char c)
{
	if (c < '0' || c > '9')
	{
		return false;
	}
	return true;
}

// hàm chuyển đổi chuỗi số sang số nguyên
int Chuoi_Sang_So(string str)
{
	int Sum = 0;
	int length = str.length();
	int mu = length - 1;
	for (int i = 0; i < length; i++)
	{
		Sum += ((str[i] - 48) * pow(10, mu-- * 1.0));
	}
	return Sum;
}

// hàm có tác dụng tách dữ liệu ngày, tháng, năm từ chuỗi
void Tach_Ngay_Thang_Nam(string str, int &x, int &y, int &z)
{
	string s;

	s.push_back(str[0]);
	str.erase(str.begin() + 0);
	s.push_back(str[0]);
	str.erase(str.begin() + 0);
	x = Chuoi_Sang_So(s);
	s.resize(0);


	s.push_back(str[0]);
	str.erase(str.begin() + 0);
	s.push_back(str[0]);
	str.erase(str.begin() + 0);
	y = Chuoi_Sang_So(s);

	z = Chuoi_Sang_So(str);
}

// hàm chuẩn hóa chuỗi theo nguyên tắc: viết hoa chữ cái đầu và mỗi từ cách nhau 1 khoảng trắng
void Chuan_Hoa(string &str)
{
	str.insert(str.begin() + 0, ' '); // thêm vào đầu kí tự khoảng trắng
	str.insert(str.begin() + str.length(), ' '); // thêm vào cuối kí tự khoảng trắng. Nếu không thêm thì sẽ không kiểm tra kí tự cuối cùng, vì i < chiều dài - 1

	for (int i = 0; i < str.length() - 1; i++)
	{

		if (str[i] == ' ' && str[i + 1] == ' ') // nếu 2 kí tự liên tiếp nhau là khoảng trắng thì xóa 1 kí tự khoảng trắng
		{
			str.erase(str.begin() + i);
			i--;
		}
		else if (str[i] == ' ' && str[i + 1] != ' ') // nếu kí tự thứ i là khoảng trắng và kí tự i + 1 khác khoảng trắng thì in hoa kí tự i + 1(nếu là kí tự thường)
		{
			if (str[i + 1] >= 97 && str[i + 1] <= 122)
			{
				str[i + 1] -= 32;

			}
			// vòng lặp có tác dụng chuẩn hóa các kí tự tiếp theo sau kí tự vừa được chuẩn hóa thành các kí tự thường
			for (int j = i + 2;; j++)
			{
				if (str[j] >= 65 && str[j] < 97)
				{
					str[j] += 32;
				}
				else if (str[j] == ' ') // khi gặp khoảng trằng thì dừng 
				{
					i = j - 1; // trả i bằng j - 1, bởi sau đó i++
					break;
				}
			}
		}
	}

	if (str[0] == ' ')
	{
		str.erase(str.begin() + 0);
	}
	if (str[str.length() - 1] == ' ')
	{
		str.erase(str.begin() + str.length() - 1);
	}
}

// hàm loại bỏ các khoảng trắng dư thừa
void Chuan_Hoa_Khoang_Trang(string &str)
{
	// xóa khoảng trắng mà vì i < str.length() - 1, nên chiều dài phải khác 0 thì mới duyệt
	if (str.length() != 0)
	{
		for (int i = 0; i < str.length() - 1; i++)
		{
			if (str[i] == ' ' && str[i + 1] == ' ')
			{
				str.erase(str.begin() + i);
				i--;
			}
		}
		if (str[0] == ' ')
		{
			str.erase(str.begin() + 0);
		}
		if (str[str.length() - 1] == ' ')
		{
			str.erase(str.begin() + str.length() - 1);
		}
	}
}

// hàm chuẩn hóa theo nguyên tắc in hoa các kí tự của chuỗi
void Chuan_Hoa_In_Hoa(string &str)
{
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (str[i] >= 97 && str[i] <= 122)
		{
			str[i] -= 32;
		}
	}
}

// hàm trả về false nếu chuỗi toàn khoảng trắng. Ngược lại trả về true
bool Kiem_Tra_Khoang_Trang(string str)
{
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (str[i] != ' ')
		{
			return true;
		}
	}
	return false;
}


int Nhap_So_Nguyen()
{
	string str;
	char c;
	c = getch(); // nhập kí tự đầu tiên

	// vòng lặp lặp vô tận cho đến khi ta nhấn phím enter <=> kết thúc việc nhập
	while ((int)c != 13)
	{

		if (int(c) == 8)
		{

			if (str.length() != 0) // nếu như độ dài chuỗi bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else // nếu không phải là kí tự enter và Backpace thì kiểm tra nếu là kí tự số thì thêm vào chuỗi
		{
			cout << c;
			if (Kiem_Tra_Ki_Tu_So(c) == false)
			{
				cout << "\nKieu du lieu khong hop le. Xin nhap lai\n";
				str.resize(0);
			}
			else
			{
				str.push_back(c);
			}
		}
		c = getch();
	}
	return Chuoi_Sang_So(str);
}

void Nhap_So_Nguyen(string &str, int &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right)
{
	//string str;
	char c;
	int length = cd;
	bool KT;

	//	do{

	// vòng lặp lặp vô tận cho đến khi ta nhấn phím enter <=> kết thúc việc nhập
	while (true)
	{

		c = getch();
		if (int(c) == 8)
		{

			if (length != 0) // nếu như độ dài chuỗi bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if (c >= '0' && c <= '9')// nếu không phải là kí tự enter và Backpace thì kiểm tra nếu là kí tự số thì thêm vào chuỗi
		{

			if (str.length() < cd_max)
			{
				cout << c;

				str.push_back(c);

				length++;
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " con so . Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                   ";
				gotoXY(x + length, y);
				TextColor(7);
			}

		}
		else if ((int)c == 27)
		{

			KT_ESC = true;
			return;

		}
		else if ((int)c == 13)
		{
			KT_ENTER = true;
			break;
		}
		else if (c == -32)
		{
			c = getch();
			if ((int)c == 75)
			{
				a = Chuoi_Sang_So(str);
				left = true;
				return;

			}
			else if ((int)c == 77)
			{
				a = Chuoi_Sang_So(str);
				right = true;
				return;
			}

		}
	}
	a = Chuoi_Sang_So(str);
}

// hàm nhập số điện thoại
void Nhap_So_Dien_Thoai(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right)
{
	//string str;
	char c;
	int length = cd;
	bool KT;

	//	do{

	// vòng lặp lặp vô tận cho đến khi ta nhấn phím enter <=> kết thúc việc nhập
	while (true)
	{

		c = getch();
		if (int(c) == 8)
		{

			if (length != 0) // nếu như độ dài chuỗi bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if (c >= '0' && c <= '9')// nếu không phải là kí tự enter và Backpace thì kiểm tra nếu là kí tự số thì thêm vào chuỗi
		{

			if (str.length() < cd_max)
			{
				cout << c;

				str.push_back(c);

				length++;
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " con so . Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                   ";
				gotoXY(x + length, y);
				TextColor(7);
			}

		}
		else if ((int)c == 27)
		{

			KT_ESC = true;
			return;

		}
		else if ((int)c == 13)
		{
			KT_ENTER = true;
			break;
		}
		else if (c == -32)
		{
			c = getch();
			if ((int)c == 75)
			{
				left = true;
				return;

			}
			else if ((int)c == 77)
			{
				right = true;
				return;
			}

		}
	}
}

// Hàm nhập dữ liệu . VD: họ, tên, giới tính. Toàn kí tự không có số . Đồ họa
void Nhap_Chuoi_Ki_Tu(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool &KT_ENTER, bool &left, bool &right)
{
	// nếu nhập kí tự enter thì chuỗi hiểu đó là kí tự kết thúc chuỗi <=> length = 0, ko tính là 1 kí tự
	bool KT;
	int length = cd; // biến cho con trỏ dịch đến cuối
	char c;

	//	do
	//	{


	while (true)
	{
		c = getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{

			if (length > 0) // nếu như độ dài biến con trỏ dịch bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if (c >= 65 && c <= 122 || c == ' ')
		{
			if (str.length() < cd_max)
			{
				cout << c;
				length++; // cập nhật vị trí con trỏ chỉ vị
				str.push_back(c);
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " ki tu . Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                   ";
				gotoXY(x + length, y);
				TextColor(7);
			}
		}
		else if (c > '0' && c < '9')
		{
			TextColor(12);
			gotoXY(20, y + 2);
			cout << "Du lieu phai la ki tu. Xin nhap lai";
			getch();
			gotoXY(20, y + 2);
			cout << "                                   ";
			gotoXY(x + length, y);
			TextColor(7);
		}
		else if ((int)c == 27)
		{
			KT_ESC = true;
			return;
		}
		else if ((int)c == 13)
		{
			KT_ENTER = true;
			if (Kiem_Tra_Khoang_Trang(str) == false)
			{
				str.erase(0);
			}
			break;
		}
		else if (c == -32)
		{
			c = getch();
			if ((int)c == 75)
			{
				left = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;


			}
			else if ((int)c == 77)
			{
				right = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
		}
	}

}


// Hàm nhập dữ liệu chuỗi bình thường , kí tự số và kí tự
void Nhap_Du_Lieu_Chuoi(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right)
{
	// nếu nhập kí tự enter thì chuỗi hiểu đó là kí tự kết thúc chuỗi <=> length = 0, ko tính là 1 kí tự
	bool KT;
	int length = cd; // biến cho con trỏ dịch đến cuối
	char c;


	while (true)
	{
		c = getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{

			if (length > 0) // nếu như độ dài biến con trỏ dịch bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if ((int)c == 27)
		{
			KT_ESC = true; // nếu nhấn kí tự ESC thì thoát
			return;
		}
		else if ((int)c == 13)
		{
			KT_ENTER = true; // nếu nhấn kí tự enter thì lưu
			if (Kiem_Tra_Khoang_Trang(str) == false)
			{
				str.erase(0);
			}
			break;
		}
		else if (c == -32)
		{

			c = getch();
			if ((int)c == 75)
			{
				left = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
			else if ((int)c == 77)
			{

				right = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
		}
		else
		{
			if (str.length() < cd_max)
			{
				cout << c;
				length++; // cập nhật vị trí con trỏ chỉ vị
				str.push_back(c);
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " ki tu. Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                ";
				gotoXY(x + length, y);
				TextColor(7);
			}

		}
	}
}

// hàm chỉ cho nhập các kí tự số nguyên 
void Nhap_So_Thuc(string &str, float &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right)
{
	////string str;
	//char c;
	//int length = cd;
	//bool KT;

	////	do{

	//// vòng lặp lặp vô tận cho đến khi ta nhấn phím enter <=> kết thúc việc nhập
	//while (true)
	//{

	//	c = getch();
	//	if (int(c) == 8)
	//	{

	//		if (length != 0) // nếu như độ dài chuỗi bằng 0 thì ko cho xóa tiếp
	//		{
	//			cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
	//			length--;
	//		}
	//		if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
	//		{
	//			str.erase(str.begin() + (str.length() - 1));
	//		}
	//	}
	//	else if (c >= '0' && c <= '9')// nếu không phải là kí tự enter và Backpace thì kiểm tra nếu là kí tự số thì thêm vào chuỗi
	//	{

	//		if (str.length() < cd_max)
	//		{
	//			cout << c;

	//			str.push_back(c);

	//			length++;
	//		}
	//		else
	//		{
	//			TextColor(12);
	//			gotoXY(20, y + 2);
	//			cout << "Du lieu toi da " << cd_max << " con so . Xin kiem tra lai !";
	//			getch();
	//			gotoXY(20, y + 2);
	//			cout << "                                                                   ";
	//			gotoXY(x + length, y);
	//			TextColor(7);
	//		}

	//	}
	//	else if ((int)c == 27)
	//	{

	//		KT_ESC = true;
	//		return;

	//	}
	//	else if ((int)c == 13)
	//	{
	//		KT_ENTER = true;
	//		break;
	//	}
	//	else if (c == -32)
	//	{
	//		c = getch();
	//		if ((int)c == 75)
	//		{
	//			a = Chuoi_Sang_So(str);
	//			left = true;
	//			return;

	//		}
	//		else if ((int)c == 77)
	//		{
	//			a = Chuoi_Sang_So(str);
	//			right = true;
	//			return;
	//		}

	//	}
	//}
	//a = Chuoi_Sang_So(str);
}

// hàm chuyển đổi chuỗi số thực sang số thực
float Chuoi_Sang_So_Thuc(string str)
{
	// bước 1 : cắt lấy phần nguyên
	string phannguyen;
	int size = str.length();
	int i;
	for (i = 0; i < size; i++)
	{
		if (str[i] != '.')
		{
			phannguyen += str[i];
		}
		else
		{
			break;
		}
	}
	string phanthapphan;
	int dem = 0;
	// bước 2: lấy phần thập phân
	for (i = i + 1; i < size; i++)
	{
		dem++;
		phanthapphan += str[i];
	}
	// bước 3: chuyển phần nguyên và phần thập phân về dạng số nguyên
	int nguyen = Chuoi_Sang_So(phannguyen);
	int thapphan = Chuoi_Sang_So(phanthapphan);
	// bước 3: chuyển sang số thực bắng cách lấy phần nguyên + phần thực
	return nguyen + (thapphan * pow(10, -(dem)));
}

/* ========================================= HÀM NHẬP CHO CHỨC NĂNG LẬP HÓA ĐƠN NHẬP - XUẤT =========================================*/


// Hàm nhập dữ liệu chuỗi bình thường , gồm kí tự số và kí tự
void Nhap_Du_Lieu_Chuoi_Len_Xuong(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab)
{
	// nếu nhập kí tự enter thì chuỗi hiểu đó là kí tự kết thúc chuỗi <=> length = 0, ko tính là 1 kí tự
	bool KT;
	int length = cd; // biến cho con trỏ dịch đến cuối
	char c;


	while (true)
	{
		c = getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{

			if (length > 0) // nếu như độ dài biến con trỏ dịch bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if ((int)c == 27)
		{
			KT_ESC = true; // nếu nhấn kí tự ESC thì thoát
			return;
		}
		else if ((int)c == 13)
		{
			KT_ENTER = true; // nếu nhấn kí tự enter thì lưu
			if (Kiem_Tra_Khoang_Trang(str) == false)
			{
				str.erase(0);
			}
			break;
		}
		else if ((int)c == 9) // tab
		{

			tab = true;
			if (Kiem_Tra_Khoang_Trang(str) == false)
			{
				str.erase(0);
			}
			return;
		}
		else if (c == -32)
		{

			c = getch();
			if ((int)c == 75)
			{
				left = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
			else if ((int)c == 77)
			{

				right = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
			else if ((int)c == 72) // mũi tên up
			{
				up = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;

			}
			else if ((int)c == 80) // mũi tên down
			{
				down = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
		}
		else
		{
			if (str.length() < cd_max)
			{
				cout << c;
				length++; // cập nhật vị trí con trỏ chỉ vị
				str.push_back(c);
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " ki tu. Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                ";
				gotoXY(x + length, y);
				TextColor(7);
			}

		}
	}
}

// hàm nhập số điện thoại
void Nhap_So_Dien_Thoai_Len_Xuong(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab)
{
	char c;
	int length = cd;
	bool KT;


	// vòng lặp lặp vô tận cho đến khi ta nhấn phím enter <=> kết thúc việc nhập
	while (true)
	{

		c = getch();
		if (int(c) == 8)
		{

			if (length != 0) // nếu như độ dài chuỗi bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if (c >= '0' && c <= '9')// nếu không phải là kí tự enter và Backpace thì kiểm tra nếu là kí tự số thì thêm vào chuỗi
		{

			if (str.length() < cd_max)
			{
				cout << c;

				str.push_back(c);

				length++;
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " con so . Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                   ";
				gotoXY(x + length, y);
				TextColor(7);
			}

		}
		else if ((int)c == 27)
		{

			KT_ESC = true;
			return;

		}
		else if ((int)c == 13)
		{
			KT_ENTER = true;
			if (Kiem_Tra_Khoang_Trang(str) == false)
			{
				str.erase(0);
			}
			break;
		}
		else if ((int)c == 9) // tab
		{
			
			tab = true;
			if (Kiem_Tra_Khoang_Trang(str) == false)
			{
				str.erase(0);
			}
			return;
		}
		else if (c == -32)
		{
			c = getch();
			if ((int)c == 75)
			{
				left = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;

			}
			else if ((int)c == 77)
			{
				right = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
			else if ((int)c == 72) // mũi tên up
			{
				up = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;

			}
			else if ((int)c == 80) // mũi tên down
			{
				down = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}

		}
	}
}

// hàm chỉ cho nhập các kí tự số nguyên 
void Nhap_So_Nguyen_Len_Xuong(string &str, int &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab)
{
	//string str;
	char c;
	int length = cd;
	bool KT;

	//	do{

	// vòng lặp lặp vô tận cho đến khi ta nhấn phím enter <=> kết thúc việc nhập
	while (true)
	{

		c = getch();
		if (int(c) == 8)
		{

			if (length != 0) // nếu như độ dài chuỗi bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if (c >= '0' && c <= '9')// nếu không phải là kí tự enter và Backpace thì kiểm tra nếu là kí tự số thì thêm vào chuỗi
		{

			if (str.length() < cd_max)
			{
				cout << c;

				str.push_back(c);

				length++;
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " con so . Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                   ";
				gotoXY(x + length, y);
				TextColor(7);
			}

		}
		else if ((int)c == 27)
		{

			KT_ESC = true;
			return;

		}
		else if ((int)c == 13)
		{
			KT_ENTER = true;
			break;
		}
		else if ((int)c == 9) // tab
		{
			a = Chuoi_Sang_So(str);
			tab = true;
			return;
		}
		else if (c == -32)
		{
			c = getch();
			if ((int)c == 75)
			{
				a = Chuoi_Sang_So(str);
				left = true;
				return;

			}
			else if ((int)c == 77)
			{
				a = Chuoi_Sang_So(str);
				right = true;
				return;
			}
			else if ((int)c == 72) // up
			{
				a = Chuoi_Sang_So(str);
				up = true;
				return;
			}
			else if ((int)c == 80) // down
			{
				a = Chuoi_Sang_So(str);
				down = true;
				return;
			}
		}
	}
	a = Chuoi_Sang_So(str);
}


// hàm chỉ cho nhập các kí tự số nguyên 
void Nhap_So_Thuc_Len_Xuong(string &str, float &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab)
{
	//string str;
	char c;
	int length = cd;
	bool KT;

	//	do{

	// vòng lặp lặp vô tận cho đến khi ta nhấn phím enter <=> kết thúc việc nhập
	while (true)
	{

		c = getch();
		if (int(c) == 8)
		{

			if (length != 0) // nếu như độ dài chuỗi bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if (c >= '0' && c <= '9' || c == '.')// nếu không phải là kí tự enter và Backpace thì kiểm tra nếu là kí tự số thì thêm vào chuỗi
		{

			if (str.length() < cd_max)
			{
				cout << c;

				str.push_back(c);

				length++;
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " con so . Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                   ";
				gotoXY(x + length, y);
				TextColor(7);
			}

		}
		else if ((int)c == 27)
		{

			KT_ESC = true;
			return;

		}
		else if ((int)c == 13)
		{
			KT_ENTER = true;
			break;
		}
		else if ((int)c == 9) // tab
		{
			a = Chuoi_Sang_So_Thuc(str);
			tab = true;
			return;
		}
		else if (c == -32)
		{
			c = getch();
			if ((int)c == 75)
			{
				a = Chuoi_Sang_So_Thuc(str);
				left = true;
				return;

			}
			else if ((int)c == 77)
			{
				a = Chuoi_Sang_So_Thuc(str);
				right = true;
				return;
			}
			else if ((int)c == 72) // up
			{
				a = Chuoi_Sang_So_Thuc(str);
				up = true;
				return;
			}
			else if ((int)c == 72) // down
			{
				a = Chuoi_Sang_So_Thuc(str);
				down = true;
				return;
			}

		}
	}
	a = Chuoi_Sang_So_Thuc(str);
}

// Hàm chỉ cho nhập các kí tự a-->z. VD: họ, tên, giới tính. Toàn kí tự không có số . Đồ họa
void Nhap_Loai_Hoa_Don(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool &KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab)
{
	// nếu nhập kí tự enter thì chuỗi hiểu đó là kí tự kết thúc chuỗi <=> length = 0, ko tính là 1 kí tự
	bool KT;
	int length = cd; // biến cho con trỏ dịch đến cuối
	char c;

	//	do
	//	{


	while (true)
	{
		c = getch();
		if (int(c) == 8) // nếu ấn phím Backspace thì xóa 1 kí tự ở cuối
		{

			if (length > 0) // nếu như độ dài biến con trỏ dịch bằng 0 thì ko cho xóa tiếp
			{
				cout << "\b \b"; // khi bấm phím Backspace thì sẽ xóa từng kí tự của chuỗi kí tự hiện tại
				length--;
			}
			if (str.length() != 0) // xóa kí tự cuối trong chuỗi string 
			{
				str.erase(str.begin() + (str.length() - 1));
			}
		}
		else if (c == 'x' || c == 'X' || c == 'n' || c == 'N')
		{
			if (str.length() < cd_max)
			{
				cout << c;
				length++; // cập nhật vị trí con trỏ chỉ vị
				str.push_back(c);
			}
			else
			{
				TextColor(12);
				gotoXY(20, y + 2);
				cout << "Du lieu toi da " << cd_max << " ki tu . Xin kiem tra lai !";
				getch();
				gotoXY(20, y + 2);
				cout << "                                                                   ";
				gotoXY(x + length, y);
				TextColor(7);
			}
		}
		else if (c > '0' && c < '9')
		{
			TextColor(12);
			gotoXY(20, y + 2);
			cout << "Du lieu phai la ki tu. Xin nhap lai";
			getch();
			gotoXY(20, y + 2);
			cout << "                                   ";
			gotoXY(x + length, y);
			TextColor(7);
		}
		else if ((int)c == 9) // tab
		{
			
			tab = true;
			return;
		}
		else if ((int)c == 27)
		{
			KT_ESC = true;

			return;
		}
		else if ((int)c == 13)
		{
			KT_ENTER = true;
			if (Kiem_Tra_Khoang_Trang(str) == false)
			{
				str.erase(0);
			}
			break;
		}
		else if (c == -32)
		{
			c = getch();
			if ((int)c == 75)
			{
				left = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;


			}
			else if ((int)c == 77)
			{
				right = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
			else if ((int)c == 72) // up
			{
			
				up = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
			else if ((int)c == 80) // down
			{
			
				down = true;
				if (Kiem_Tra_Khoang_Trang(str) == false)
				{
					str.erase(0);
				}
				return;
			}
		}
	}
}