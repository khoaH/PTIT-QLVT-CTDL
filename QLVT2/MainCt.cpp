#include "MainCt.h"

void MainCt::FirstCT()
{
	system("color f0");
	fullScreen();
	RemoveScroll();
	DrawBorder(TOADOX, TOADOY, CHIEUNGANG, CHIEUDOC);
	for (int i = 0; i < CHIEUDOC; i += (CHIEUDOC / 5)) {
		DrawBorder(TOADOX, TOADOY + i, 20, CHIEUDOC / 5);
	}
	for (int i = CHIEUDOC / 5; i < CHIEUDOC; i += CHIEUDOC / 5) {
		gotoXY(TOADOX, TOADOY + i);
		cout << char(195);
		gotoXY(TOADOX + 20, TOADOY + i);
		cout << char(180);
	}
	gotoXY(TOADOX + 20, TOADOY);
	cout << char(194);
	gotoXY(TOADOX + 20, TOADOY + CHIEUDOC);
	cout << char(193);
	gotoXY(0, CHIEUDOC + 2);
}

void MainCt::WriteCenterText(string str, int toaDoX, int toaDoY)
{
	gotoXY(toaDoX, toaDoY);
	cout << CenterTextInSpace("", 19);
	gotoXY(toaDoX, toaDoY + 1);
	cout << CenterTextInSpace("", 19);
	gotoXY(toaDoX, toaDoY + 2);
	cout << CenterTextInSpace("", 19);
	gotoXY(toaDoX, toaDoY + 3);
	cout << CenterTextInSpace(str, 19);
	gotoXY(toaDoX, toaDoY + 4);
	cout << CenterTextInSpace("", 19);
	gotoXY(toaDoX, toaDoY + 5);
	cout << CenterTextInSpace("", 19);
	gotoXY(toaDoX, toaDoY + 6);
	cout << CenterTextInSpace("", 19);
	gotoXY(toaDoX, toaDoY + 7);
}

void MainCt::WriteWord()
{
	string select;
	select.resize(18, ' ');
	string select1 = "Vat Tu", select2 = "Nhan Vien",
		select3 = "In Hoa Don", select4 = "Thong Ke", select5 = "Top Ban Chay";
	TextColor(0);
	textbk(15);
	int i = 0;
	this->ChangeSelect(select, select1);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select2);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select3);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select4);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;
	this->ChangeSelect(select, select5);
	WriteCenterText(select, TOADOX + 1, TOADOY + 1 + i);
	i += CHIEUDOC / 5;

	TextColor(0);
	textbk(14);
	switch (mode)
	{
	case MainCt::VatTu:
		this->ChangeSelect(select, select1);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1);
		break;
	case MainCt::NhanVien:
		this->ChangeSelect(select, select2);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5));
		break;
	case MainCt::InHoaDon:
		this->ChangeSelect(select, select3);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2);
		break;
	case MainCt::ThongKe:
		this->ChangeSelect(select, select4);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3);
		break;
	case MainCt::TopBanChay:
		this->ChangeSelect(select, select5);
		this->WriteCenterText(select, TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4);
		break;
	default:
		break;
	}
	TextColor(7);
	textbk(0);
	gotoXY(TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 5);
}
void MainCt::ChangeSelect(string& First, string change)
{
	First.clear();
	First.resize(change.size(), ' ');
	First = change;
}

void MainCt::ChangeMode()
{
	if (keyhit == 224) {
		keyhit = _getch();
		switch (keyhit)
		{
		case KEY_DOWN:
			switch (mode)
			{
			case MainCt::VatTu:
				mode = NhanVien;
				break;
			case MainCt::NhanVien:
				mode = InHoaDon;
				break;
			case MainCt::InHoaDon:
				mode = ThongKe;
				break;
			case MainCt::ThongKe:
				mode = TopBanChay;
				break;
			case MainCt::TopBanChay:
				mode = VatTu;
				break;
			default:
				break;
			}
			break;
		case KEY_UP:
			switch (mode)
			{
			case MainCt::VatTu:
				mode = TopBanChay;
				break;
			case MainCt::NhanVien:
				mode = VatTu;
				break;
			case MainCt::InHoaDon:
				mode = NhanVien;
				break;
			case MainCt::ThongKe:
				mode = InHoaDon;
				break;
			case MainCt::TopBanChay:
				mode = ThongKe;
				break;
			}
		}
	}
}

void MainCt::ChangeCT()
{
	if (keyhit == ENTER) {
		switch (mode)
		{
		case MainCt::VatTu:
		{
			TextColor(0);
			textbk(7);
			this->WriteCenterText("Vat Tu", TOADOX + 1, TOADOY + 1);
			TextColor(0);
			textbk(15);
			ClearInsideBox();
			DSVatTu * ct = new DSVatTu();
			ct->mainVatTU();
			delete ct;
			TextColor(0);
			textbk(14);
			this->WriteCenterText("Vat Tu", TOADOX + 1, TOADOY + 1);
			TextColor(15);
			textbk(0);
			ClearInsideBox();
		}
			break;
		case MainCt::NhanVien:
		{
			TextColor(0);
			textbk(7);
			this->WriteCenterText("Nhan Vien", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5));
			TextColor(0);
			textbk(15);
			DSNhanVien* nv = new DSNhanVien();
				delete nv;
			TextColor(0);
			textbk(14);
			this->WriteCenterText("Nhan Vien", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5));
			TextColor(15);
			textbk(0);
			ClearInsideBox();
		}
			break;
		case MainCt::InHoaDon:
		{
			TextColor(0);
			textbk(7);
			this->WriteCenterText("In Hoa Don", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2);
			TextColor(0);
			textbk(15);
			DSHoaDon* hd = new DSHoaDon();
			ConnectFile* connect = new ConnectFile();
			hd->MainInHoaDon(connect);
			delete connect;
			delete hd;
			TextColor(0);
			textbk(14);
			this->WriteCenterText("In Hoa Don", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 2);
			TextColor(15);
			textbk(0);
		}
			break;
		case MainCt::ThongKe:
		{
			TextColor(0);
			textbk(7);
			this->WriteCenterText("Thong Ke", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3);
			TextColor(0);
			textbk(15);
			ConnectFile* connect = new ConnectFile();
			DSHoaDon * thongke = new DSHoaDon();
			thongke->MainThongKeHD(connect);
			delete connect;
			delete thongke;
			TextColor(0);
			textbk(14);
			this->WriteCenterText("Thong Ke", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 3);
			TextColor(15);
			textbk(0);
			ClearInsideBox();
		}
			break;
		case MainCt::TopBanChay:
		{
			TextColor(0);
			textbk(7);
			this->WriteCenterText("Top Ban Chay", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4);
			TextColor(0);
			textbk(15);
			ConnectFile* connect = new ConnectFile();
			DSCTHoaDon * cthd = new DSCTHoaDon();
			cthd->MainDoanhThu(&this->Conn);
			delete connect;
			delete cthd;
			TextColor(0);
			textbk(14);
			this->WriteCenterText("Top Ban Chay", TOADOX + 1, TOADOY + 1 + (CHIEUDOC / 5) * 4);
			TextColor(15);
			textbk(0);
			ClearInsideBox();
		}
			break;
		}
	}
}

void MainCt::EscCT()
{
	if (keyhit == ESC)
	{ 
		TextColor(MAUCHUX);
		textbk(MAUNENO);
		int i = DrawNoti(thoatCT, choice, 2);
		if (i == 0)
		{
			system("color f0");
			clrscr();
			exit(0);
		}
		else
			ClearInsideBox();
	}
}

MainCt::MainCt()
{

	mode = VatTu;
	keyhit = 0;
	this->FirstCT();
	while (true)
	{
		this->ChangeMode();
		this->WriteWord();
		this->ChangeCT();
		this->EscCT();
		keyhit = _getch();
	}
	Conn.~ConnectFile();
}


MainCt::~MainCt()
{
}
