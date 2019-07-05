#pragma once
#include<iostream>
using namespace std;
#include <stdio.h>
#include <conio.h>
#include<string>
#include<string.h>
#include<cmath>
#include <windows.h>
#pragma warning(disable:4996) // bỏ qua lỗi 4996 - lỗi bảo mật


#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1


int inputKey();

//-------------------------Screen-------------------------
void clrscr();

//screen: goto [x,y]
void gotoXY(int column, int line);

//screen: get [x]
int whereX();

//screen: get [y]
int whereY();

void TextColor (int color);
//end----------------------Screen----------------------end

/* ======================================= HÀM XỬ LÍ ĐỒ HỌA ======================================= */

// hàm vẽ khung băt đầu tại tọa độ (x, y) với chiều dài width và chiều cao height
void Ve_Khung(int x, int y, int width, int height);

//ẩn đi con trỏ chỉ vị nhấp nháy trên màn hình, Xu_Li_Con_Tro_Chi_Vi(0) -> Ẩn con trỏ ------- Xu_Li_Con_Tro_Chi_Vi(1)-> hiện lại con trỏ
void Xu_Li_Con_Tro_Chi_Vi(bool CursorVisibility);

// vẽ đường thẳng ngang từ tọa độ (x0, y) đến (x1, y)
void linex(int x0, int x1, int y);

//vẽ đường thẳng dọc từ tọa độ (x, y0) đến (x, y1)
void liney(int y0, int y1, int x);

//vẽ hình chữ nhật bằng đường thẳng có đường chéo qua 2 điểm (x0,y0) (x1,y1), loai: 1 vẽ đường đơn, 2 vẽ đường đôi, 0 xóa hình chữ nhật 
void chose(int x0, int y0, int x1, int y1, int loai);

// ========= CĂN LỀ CHO CHUỖI
// căn giữa
void aligncenter(string s, int y);

// căn trái n kí tự
void alignleft(string s, int n);

// căn phải n kí tự
void alignright(string s, int n);


//mau nen chu
void textbk(WORD color);

//nhan phim tu keyboard
bool checkKey(int key);

int khungyesno(int x, int y);
int khungync(int x, int y);
int khungthongbaotontai(int x, int y);
int khungcapnhatsinhvien(int x, int y);
bool Xac_Nhan(int x, int y);
void menutinh(string s[], int sodong, int y, int maunen, int mauchu, int mauchon, int &vitri);
void menu(string s[], int sodong, int y, int maunen, int mauchu, int mauchon, int &vitri);

/* ======================================= HÀM XỬ LÍ NHẬP DỮ LIỆU ======================================= */

bool Kiem_Tra_Ki_Tu_So(char c);

// hàm chuyển đổi chuỗi số sang số nguyên
int Chuoi_Sang_So(string str);

// hàm chuyển đổi chuỗi số thực sang số thực
float Chuoi_Sang_So_Thuc(string str);

// hàm chuẩn hóa chuỗi theo nguyên tắc: viết hoa chữ cái đầu và mỗi từ cách nhau 1 khoảng trắng
void Chuan_Hoa(string &str);

// hàm loại bỏ các khoảng trắng dư thừa
void Chuan_Hoa_Khoang_Trang(string &str);

// hàm chuẩn hóa theo nguyên tắc in hoa các kí tự của chuỗi
void Chuan_Hoa_In_Hoa(string &str);

// hàm trả về false nếu chuỗi toàn khoảng trắng. Ngược lại trả về true
bool Kiem_Tra_Khoang_Trang(string str);

// hàm có tác dụng tách dữ liệu ngày, tháng, năm từ chuỗi
void Tach_Ngay_Thang_Nam(string, int &, int &, int &);

// hàm chỉ cho nhập các kí tự số nguyên 
void Nhap_So_Nguyen(string &str, int &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right);

// hàm chỉ cho nhập các kí tự số nguyên 
void Nhap_So_Thuc(string &str, float &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right);

// Hàm chỉ cho nhập các kí tự a-->z. VD: họ, tên, giới tính. Toàn kí tự không có số . Đồ họa
void Nhap_Chuoi_Ki_Tu(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool &KT_ENTER, bool &left, bool &right);

// Hàm nhập dữ liệu chuỗi bình thường , gồm kí tự số và kí tự
void Nhap_Du_Lieu_Chuoi(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right);

// hàm nhập số điện thoại
void Nhap_So_Dien_Thoai(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right);


/* ========================================= HÀM NHẬP CHO CHỨC NĂNG LẬP HÓA ĐƠN NHẬP - XUẤT =========================================*/
// Hàm nhập dữ liệu chuỗi bình thường , gồm kí tự số và kí tự
void Nhap_Du_Lieu_Chuoi_Len_Xuong(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab);

// hàm nhập số điện thoại
void Nhap_So_Dien_Thoai_Len_Xuong(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab);

// hàm chỉ cho nhập các kí tự số nguyên 
void Nhap_So_Nguyen_Len_Xuong(string &str, int &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab);

// hàm chỉ cho nhập các kí tự số nguyên 
void Nhap_So_Thuc_Len_Xuong(string &str, float &a, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool&KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab);

// Hàm chỉ cho nhập các kí tự a-->z. VD: họ, tên, giới tính. Toàn kí tự không có số . Đồ họa
void Nhap_Loai_Hoa_Don(string &str, int cd, int x, int y, int &cd_max, bool &KT_ESC, bool &KT_ENTER, bool &left, bool &right, bool &down, bool &up, bool &tab);