#pragma once
#include "CayNhiPhan.h"
#include "console.h"
#include "ConnectFile.h"
#include "Design.h"
#include "Header.h"
#include <iostream>

using namespace std;

class DSVatTu :public CayNhiPhan
{
private:
	int keypress;
	ConnectFile* con;
	ListVatTu viTriFirst;
	ListVatTu viTriCurrent;
	ListVatTu viTriEndList;
	int sttNum;
	enum InfoAdd
	{
		themMa,
		themTen,
		themSoLuong,
		themDVT,
		chonOption
	};
	InfoAdd infoAdd;
	enum InfoFix
	{
		suaTen,
		suaDVT,
		chonOptionFix
	};
	InfoFix infoFix;
public:
	void SetViTriEndList();
	void Travese();
	void DrawVatTu(); //ke bang nhan vien
	void DrawFormVatTu();
	void WriteVatTu(); //viet thong tin nhan vien
	void ThemVatTu(); //nut insert
	int ThongBaoTrung();
	void ExitOption(int choice, char choiceArr[][15], int soOption, VatTu vatTu, char maVT[11]);
	void InputAddMode(VatTu& info, string& maVT);
	void InputFixMode(PTRVatTu& vatTu);
	void ChangeInput();
	void ChangeInputFix();
	void XoaVatTu(); //nut delete
	void UpdateVatTu(); //dung nut enter cho sua vat tu
	ListVatTu SelectVatTu(ConnectFile* connect); //dung nut enter cho chon cthd
	int UpdateFromCTHD(ChiTietHoaDon cthd, int loaiHD);
	int ExitMenu(int keyhit); //dung nut escape
	void mainVatTU();
	DSVatTu();
	~DSVatTu();
};

