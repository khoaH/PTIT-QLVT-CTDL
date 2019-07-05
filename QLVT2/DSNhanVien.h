#pragma once
#include "MangConTro.h"
#include "Design.h"
#include "console.h"
#include "DSHoaDon.h"
#include "ConnectFile.h"

class DSNhanVien :public MangConTro
{
private:
	enum InfoAddSelect {
		themTen,
		themHo,
		themPhai,
		themMa,
		chonOption
	};
	InfoAddSelect infoAddSelect;
	int keypress;
	ConnectFile* con;
	int viTriFirst;
	int viTriCurrent;
	//int current;
public:
	int vitri_endList();
	void travese();
	void DrawNhanVien(); //ke bang nhan vien
	void DrawFormThemNhanVien();
	void WriteNhanVien(); //viet thong tin nhan vien
	void ThemNhanVien(); //nut insert
	int ThongBaoTrung();
	void ExitOption(int choice, char choiceArr[][15], int soOption, NhanVien nhanVien);
	void InputAddMode(NhanVien &newNhanVien);
	void InputFixMode(NhanVien &info);
	void ChangeInput();
	void ChooseSex(int &sex);
	void XoaNhanVien(); //nut delete
	void SuaNhanVien();
	void SelectNhanVien(); //dung nut enter
	void HoaDon();
	int ExitMenu(int keyhit); //dung nut escape
	DSNhanVien();
	~DSNhanVien();
};

