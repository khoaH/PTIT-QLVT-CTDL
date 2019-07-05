#include <string>
#include "console.h"
#include <Windows.h>
#include <iostream>
#include "Header.h"
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include <windows.h>
//key
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define Bell 7
#define HOME 71
#define DEL 83
#define TAB 9
#define INS 82
#define SPACEBAR 32
#define DOT 46
#define CTRL_F 6

#define CHIEUNGANG 165
#define CHIEUDOC 40

#define TOADOX 5
#define TOADOY 2

#define BOXNVWIDE 25
#define BOXHDWIDE 25

#define MAUNENO 15
#define MAUCHUO 8
#define MAUNENX 7
#define MAUCHUX 0

#define VATTUTITLE 00
#define VATTUTHEM 01
#define VATTUSUA 02

#define NHANVIENTITLE 10
#define THEMNHANVIEN 11
#define SUANHANVIEN 12
#define CHITIETNHANVIEN 13

#define HOADONTITLE 20
#define THEMHOADONTITLE 21
#define INHOADONTITLE 22
#define THONGKETITLE 23
#define THONGKEMENU 24

#define CHITIETTITLE 30
#define TOPDTTITLE 31
#define TOPDTDANHSACH 32
#define THEMCHITIETNEWHD 33
#define THEMCHITIETHD 34
#define SUACHITIETHD 35

using namespace std;

void DrawBorder(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc);
void RemoveScroll();
void fullScreen();
void DrawBorderList(int toaDoX, int toaDoY, int soDong, int soCot, int chieuNgangO, int chieuDocO);
string CenterTextInSpace(string center, int wide);
void ClearInsideBox();
int InputInfo(string& info, int maxChuoi, int posX, int posY, int& keyVar, int mode);
string CharToString(char* c);
int ChooseOption(char arr[][15], int posX, int posY, int soOption, int spaceBetween, int lock);
void DrawOptionChoice(char arr[][15], int posX, int posY, int soOption, int spaceBetween);
int DrawNoti(char context[][78], char arr[][15], int soOption);
string IntToString(int a);
int StringToInt(string str);
Ngay StringToDate(string temp);
int DateCmp(Ngay no1, Ngay no2);
int CheckDate(Ngay thisDay);
string DateToString(Ngay value);
int CheckString(string check, int checkKind);//checkKind la loai can check vd: 1 = check chuoi chu, 2 = check chuoi so,...
void FixString(string& str, int mode);
string DelFloatTrail(string& floatStr);
void DrawMenu(int title);
void DrawTitle(int title, int posX, int posY);