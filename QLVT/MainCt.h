#include "console.h"
#include "ConnectFile.h"
#include "Design.h"
#include "DSNhanVien.h"
#include "DSVatTu.h"
#include <iostream>
using namespace std;

class MainCt
{
private:
	enum Mode
	{
		VatTu,
		NhanVien,
		InHoaDon,
		ThongKe,
		TopBanChay,
	};
	Mode mode;
	ConnectFile Conn;
	enum {
		BATDAUX = 3
	};
	int keyhit;
	void FirstCT();
	void WriteCenterText(string str, int toaDoX, int toaDoY);
	void WriteWord();
	void ChangeSelect(string &First, string change);
	void ChangeMode();
	void ChangeCT();
	void EscCT();
	char choice[2][15] = { "Thoat","Huy" };
	char thoatCT[10][78] =
	{
		"",
		"",
		"",
		"",
		"Ban muon thoat chuong trinh ?",
		"",
		"",
		"",
		"",
		"",
	};
public:
	MainCt();
	~MainCt();
};
