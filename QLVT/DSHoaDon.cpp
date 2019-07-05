#include "DSHoaDon.h"

using namespace std;

DSHoaDon::DSHoaDon()
{
}


DSHoaDon::~DSHoaDon()
{
}

PTRHoaDon DSHoaDon::endList(PTRHoaDon first)
{
	PTRHoaDon run = first;
	for (int i = 0; /*run != NULL &&*/ i < 9 && run->next != NULL; i++, run = run->next); //run -> next != NULL de ko bi chay lo them dong run = run -> next
	return run;
}

PTRHoaDon DSHoaDon::prevList(PTRHoaDon firstList, PTRHoaDon currentList)
{
	PTRHoaDon run;
	for (run = firstList; run->next != currentList; run = run->next);
	return run;
}

string DSHoaDon::TimTenNV(PTRHoaDon run)
{
	for (int i = 0; i < this->dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; i++)
	{
		for (PTRHoaDon j = dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first; j != NULL; j = j->next)
		{
			if (stricmp(run->infoHoaDon.soHoaDon, j->infoHoaDon.soHoaDon) == 0)
			{
				return dsThongKe.GetDanhSachNhanVien().nodes[i]->ho + " " + dsThongKe.GetDanhSachNhanVien().nodes[i]->ten;
			}
		}
	}
	return "";
}

float DSHoaDon::TriGiaHD(PTRHoaDon run)
{
	float total = 0;
	if (run->PTRChiTietHoaDon->soLuongVatTu == 0)
		return 0;
	ChiTietHoaDon temp = *run->PTRChiTietHoaDon;
	for (int i = 0; i < temp.soLuongVatTu; i++)
		total = total + temp.nodesChiTiet[i].soLuong * temp.nodesChiTiet[i].donGia * (1 + temp.nodesChiTiet[i].VAT / 100);
	return total;
}

void DSHoaDon::WriteThongKe()
{
	int j = 0;
	int i = 0;
	int t = (x.trangHienTai - 1) * 10;
	for (PTRHoaDon run = firstList; run != lastList->next; run = run->next) {
		if (run == currentList) 
		{
			TextColor(4);
			textbk(15);
		}
		else
		{
			TextColor(0);
			textbk(15);
		}
		j = 0;
		t += 1;
		gotoXY(36 + j, 18 + i);
		cout << CenterTextInSpace(run->infoHoaDon.soHoaDon, BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		string temp_date;
		temp_date = IntToString(run->infoHoaDon.ngayNhapHoaDon.date) + " / " + IntToString(run->infoHoaDon.ngayNhapHoaDon.month) + " / " + IntToString(run->infoHoaDon.ngayNhapHoaDon.year);
		cout << CenterTextInSpace(temp_date, BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		cout << CenterTextInSpace(CharToString(run->infoHoaDon.loai), BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		cout << CenterTextInSpace(this->TimTenNV(run), BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		string temp_trigia = to_string(this->TriGiaHD(run));
		cout << CenterTextInSpace(DelFloatTrail(temp_trigia), BOXHDWIDE - 1);
		i += 2;
	}
	TextColor(0);
	textbk(15);
	if (t < (x.trangHienTai - 1) * 10 + 10) {
		for (int k = t; k <= (x.trangHienTai - 1) * 10 + 10; k++) {
			j = 0;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			i += 2;
		}
	}
}

void DSHoaDon::TimTatCaHoaDon()
{
	if (keyhitHD == CTRL_F)
	{
		firstList = currentList = x.hoaDonDauTrang[x.trangHienTai] = this->GetListHoaDon().first;
		if (this->firstList != NULL)
		{
			lastList = endList(firstList);
			this->DrawThongKe();
			keyhitHD = 0;
			while (true)
			{
				this->travese();
				this->WriteThongKe();
				if (keyhitHD == ENTER)
				{
					this->XemChiTietHoaDon(this->currentList);
					ClearInsideBox();
					this->DrawThongKe();
					this->travese();
					this->WriteThongKe();
				}
					
				if (this->ExitHD(keyhitHD))
				{
					this->TurnBackInputInHD();
					keyhitHD = 0;
					break;
				}
				keyhitHD = _getch();
			}
		}
		else
		{
			char thongBaoRong[10][78] =
			{
				"",
				"",
				"",
				"Khong co hoa don nao",
				"",
				"",
				"",
				"",
				"",
				""
			};
			char ok[1][15] = { "OK" };
			DrawNoti(thongBaoRong, ok, 1);
			this->DrawFormThongKe();
			keyhitHD = 0;
		}
	}
}

void DSHoaDon::traveseList()
{
	int j = 0;
	int i = 0;
	int t = (x.trangHienTai - 1) * 10;
	for (PTRHoaDon run = firstList; run != lastList->next; run = run->next) {
		if (run == currentList)
		{
			TextColor(4);
			textbk(15);
		}
		else
		{
			TextColor(0);
			textbk(15);
		}
		j = 0;
		t += 1;
		gotoXY(36 + j, 18 + i);
		cout << CenterTextInSpace(to_string(t), BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		cout << CenterTextInSpace(run->infoHoaDon.soHoaDon, BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		string temp_date;
		temp_date = IntToString(run->infoHoaDon.ngayNhapHoaDon.date) + " / " + IntToString(run->infoHoaDon.ngayNhapHoaDon.month) + " / " + IntToString(run->infoHoaDon.ngayNhapHoaDon.year);
		cout << CenterTextInSpace(temp_date, BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		cout << CenterTextInSpace(run->infoHoaDon.loai, BOXHDWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + i);
		string temp_trigia = to_string(this->TriGiaHD(run));
		cout << CenterTextInSpace(DelFloatTrail(temp_trigia), BOXHDWIDE - 1);
		i += 2;
	}
	TextColor(0);
	textbk(15);
	if (t < (x.trangHienTai - 1) * 10 + 10) {
		for (int k = t; k <= (x.trangHienTai - 1) * 10 + 10; k++) {
			j = 0;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + i);
			cout << CenterTextInSpace("", BOXHDWIDE - 1);
			i += 2;
		}
	}
}

void DSHoaDon::travese()
{
	if (keyhitHD == 224)
	{
		keyhitHD = _getch();
		if (keyhitHD == KEY_UP) {
			if (currentList != firstList) {
				currentList = prevList(firstList, currentList);
			}
			else if (currentList == firstList) {
				currentList = lastList;
			}
		}
		else if (keyhitHD == KEY_DOWN) {
			if (currentList != lastList) {
				currentList = currentList->next;
			}
			else if (currentList == lastList) {
				currentList = firstList;
			}
		}
		else if (keyhitHD == KEY_RIGHT) {
			if (lastList->next != NULL) {
				x.hoaDonDauTrang[++x.trangHienTai] = lastList->next;
				firstList = lastList->next;
				lastList = endList(firstList);
				currentList = firstList;
			}
		}
		else if (keyhitHD == KEY_LEFT) {
			if (x.trangHienTai > 1) {
				//delete x.hoadondautrang[x.tranghientai];
				firstList = x.hoaDonDauTrang[--x.trangHienTai];
				lastList = endList(firstList);
				currentList = firstList;
			}
		}
	}
}

void DSHoaDon::DrawHoaDon()
{
	ClearInsideBox();
	TextColor(0);
	textbk(15);
	DrawBorderList(35, 15, 11, 5, BOXHDWIDE, 1);
	DrawMenu(HOADONTITLE);
	DrawTitle(HOADONTITLE, 44, 6);
	TextColor(10);
	textbk(15);
	int i = 0;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("STT", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("SO HOA DON", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("NGAY NHAP", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("LOAI", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("TONG TIEN", BOXHDWIDE - 1);
	TextColor(0);
	textbk(15);
}

void DSHoaDon::DrawFormThemHoaDon()
{
	ClearInsideBox();
	int i = 0;
	//DrawTitle();
	//gotoXY(36, 10);
	//cout << "So Hoa Don";
	//gotoXY(56, 10);
	//cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "So Hoa Don";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Ngay Nhap";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Loai";
	gotoXY(56, 10 + i);
	cout << ":";
	DrawBorder(60, 9 + i, 4, 2);
	gotoXY(66, 10 + i);
	cout << "Nhap";
	DrawBorder(75, 9 + i, 4, 2);
	gotoXY(81, 10 + i);
	cout << "Xuat";
	DrawTitle(THEMHOADONTITLE, 48, 4);
	DrawMenu(THEMHOADONTITLE);
}

void DSHoaDon::DrawFormThongKe()
{
	//drawtile
//drawmemu
	ClearInsideBox();
	int i = 0;
	TextColor(0);
	textbk(15);
	gotoXY(36, 15 + i);
	cout << "Ngay bat dau";
	gotoXY(56, 15 + i);
	cout << ":";
	gotoXY(63, 15);
	cout << "/";
	gotoXY(68, 15);
	cout << "/";
	i += 5;
	gotoXY(36, 15 + i);
	cout << "Ngay ket thuc";
	gotoXY(56, 15 + i);
	cout << ":";
	gotoXY(63, 15 + i);
	cout << "/";
	gotoXY(68, 15 + i);
	cout << "/";
	DrawTitle(THONGKETITLE, 60, 5);
	DrawMenu(THONGKETITLE);
}

void DSHoaDon::DrawFormInHD()
{
	ClearInsideBox();
	TextColor(0);
	textbk(15);
	gotoXY(65, 13);
	cout << "Nhap So Hoa Don";
	gotoXY(81, 13);
	cout << ":";
	DrawTitle(INHOADONTITLE, 55, 5);
	DrawMenu(INHOADONTITLE);
}

void DSHoaDon::DrawThongKe()
{
	ClearInsideBox();
	TextColor(0);
	textbk(15);
	DrawBorderList(35, 15, 11, 5, BOXHDWIDE, 1);
	TextColor(10);
	textbk(15);
	int i = 0;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("SO HOA DON", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("NGAY LAP", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("LOAI HOA DON", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("HO TEN NV LAP", BOXHDWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("TRI GIA HOA DON", BOXHDWIDE - 1);
	TextColor(0);
	textbk(15);
	DrawTitle(HOADONTITLE, 46, 3);
	DrawMenu(THONGKEMENU);
}

void DSHoaDon::InputAdd(HoaDon & newHoaDon)
{
	string temp = CharToString(newHoaDon.soHoaDon);
	string temp_date = IntToString(newHoaDon.ngayNhapHoaDon.date);
	string temp_month = IntToString(newHoaDon.ngayNhapHoaDon.month);
	string temp_year = IntToString(newHoaDon.ngayNhapHoaDon.year);
	switch (this->currentAdd)
	{
	case DSHoaDon::themSoHD:
		InputInfo(temp, 19, 60, 15, keyhitHD, 5);
		strcpy(newHoaDon.soHoaDon, temp.c_str());
		break;
	case DSHoaDon::themDate_date:
		InputInfo(temp_date, 2, 60, 20, keyhitHD, 8);
		newHoaDon.ngayNhapHoaDon.date = StringToInt(temp_date);
		break;
	case DSHoaDon::themDate_month:
		InputInfo(temp_month, 2, 60 + 4, 20, keyhitHD, 8);
		newHoaDon.ngayNhapHoaDon.month = StringToInt(temp_month);
		break;
	case DSHoaDon::themDate_year:
		InputInfo(temp_year, 4, 60 + 8, 20, keyhitHD, 8);
		newHoaDon.ngayNhapHoaDon.year = StringToInt(temp_year);
		break;
	case DSHoaDon::chonLoai:
		ChooseType(newHoaDon.loai);
		break;
	case DSHoaDon::option:
	{
		char choice[2][15] = { "Nhap vat tu", "Thoat" };
		int i = ChooseOption(choice, 80, 30, 2, 3, 0);
		if (i >= 0)
		{
			if (i == 0)
				keyhitHD = INS;
			else if (i == 1 || i == 2)
				keyhitHD = ESC;
		}
		else
			keyhitHD = -i;
		break;
	}
	default:
		break;
	}
}

void DSHoaDon::InputAddDT(Ngay& start, Ngay& end)
{
	switch (this->inputDay)
	{
	case DSHoaDon::chonNgayChay:
	{
		string temp = IntToString(start.date);
		InputInfo(temp, 2, 60, 15, keyhitHD, 8);

		start.date = StringToInt(temp);
		break;
	}
	case DSHoaDon::chonThangChay:
	{
		string temp = IntToString(start.month);
		InputInfo(temp, 2, 65, 15, keyhitHD, 8);
		start.month = StringToInt(temp);
		break;
	}
	case DSHoaDon::chonNamChay:
	{
		string temp = IntToString(start.year);
		InputInfo(temp, 4, 70, 15, keyhitHD, 8);
		start.year = StringToInt(temp);
		break;
	}
	case DSHoaDon::chonNgayDung:
	{
		string temp = IntToString(end.date);
		InputInfo(temp, 2, 60, 20, keyhitHD, 8);
		end.date = StringToInt(temp);
		break;
	};
	case DSHoaDon::chonThangDung:
	{
		string temp = IntToString(end.month);
		InputInfo(temp, 2, 65, 20, keyhitHD, 8);
		end.month = StringToInt(temp);
		break;
	}
	case DSHoaDon::chonNamDung:
	{
		string temp = IntToString(end.year);
		InputInfo(temp, 4, 70, 20, keyhitHD, 8);
		end.year = StringToInt(temp);
		break;
	}
	case DSHoaDon::chonOption:
	{
		char choice[2][15] = { "Xem Thong Ke", "Thoat" };
		int i = ChooseOption(choice, 80, 25, 2, 3, 0);
		if (i >= 0)
		{
			if (i == 0)
				keyhitHD = INS;
			else if (i == 1 || i == 2)
				keyhitHD = ESC;
		}
		else
			keyhitHD = -i;
		break;
	}
	default:
		break;
	}
}

void DSHoaDon::InputInHD(HoaDon& find)
{
	switch (this->inHD)
	{
	case DSHoaDon::chonSoHD:
	{
		string temp = CharToString(find.soHoaDon);
		InputInfo(temp, 19, 83, 13, keyhitHD, 8);
		strcpy(find.soHoaDon, temp.c_str());
		break;
	}
	case DSHoaDon::TimTrongDSHD:
	{
		char browse[1][15] = { "Tim tu DSHD" };
		int i = ChooseOption(browse, 80, 16, 1, 0, 0);
		if (i >= 0)
		{
			if (i == 0)
				keyhitHD = CTRL_F;
			else if (i == 1)
				keyhitHD = ESC;
		}
		else
			keyhitHD = -i;
		break;
	}
	case DSHoaDon::Option:
	{
		char choice[2][15] = { "Tim Hoa Don", "Thoat" };
		int i = ChooseOption(choice, 85, 20, 2, 3, 0);
		if (i >= 0)
		{
			if (i == 0)
				keyhitHD = INS;
			else if (i == 1 || i == 2)
				keyhitHD = ESC;
		}
		else
			keyhitHD = -i;
		break;
	}
	default:
		break;
	}
}

void DSHoaDon::ChangeInputAdd()
{
	if (keyhitHD == KEY_UP || keyhitHD == KEY_DOWN || keyhitHD == KEY_LEFT || keyhitHD == KEY_RIGHT)
	{
		//keypress = _getch();
		switch (keyhitHD)
		{
		case KEY_UP:
		{
			switch (this->currentAdd)
			{
			case DSHoaDon::themSoHD:
				this->currentAdd = option;
				break;
			case DSHoaDon::themDate_date:
				this->currentAdd = themSoHD;
				break;
			case DSHoaDon::themDate_month:
				this->currentAdd = themSoHD;
				break;
			case DSHoaDon::themDate_year:
				this->currentAdd = themSoHD;
				break;
			case DSHoaDon::chonLoai:
				this->currentAdd = themDate_date;
				break;
			case DSHoaDon::option:
				this->currentAdd = chonLoai;
				break;
			}
			break;
		}

		case KEY_DOWN:
		{
			switch (currentAdd)
			{
			case DSHoaDon::themSoHD:
				this->currentAdd = themDate_date;
				break;
			case DSHoaDon::themDate_date:
				this->currentAdd = chonLoai;
				break;
			case DSHoaDon::themDate_month:
				this->currentAdd = chonLoai;
				break;
			case DSHoaDon::themDate_year:
				this->currentAdd = chonLoai;
				break;
			case DSHoaDon::chonLoai:
				this->currentAdd = option;
				break;
			case DSHoaDon::option:
				this->currentAdd = themSoHD;
				break;
			}
			break;
		}
		case KEY_LEFT:
		{
			switch (currentAdd)
			{
			case DSHoaDon::themDate_date:
				this->currentAdd = themDate_year;
				break;
			case DSHoaDon::themDate_month:
				this->currentAdd = themDate_date;
				break;
			case DSHoaDon::themDate_year:
				this->currentAdd = themDate_month;
				break;
			}
			break;
		}
		case KEY_RIGHT:
		{
			switch (currentAdd)
			{
			case DSHoaDon::themDate_date:
				this->currentAdd = themDate_month;
				break;
			case DSHoaDon::themDate_month:
				this->currentAdd = themDate_year;
				break;
			case DSHoaDon::themDate_year:
				this->currentAdd = themDate_date;
				break;
			}
			break;
		}
		}
	}
}

void DSHoaDon::ChangeInputDT()
{
	if (keyhitHD == KEY_UP || keyhitHD == KEY_DOWN || keyhitHD == KEY_LEFT || keyhitHD == KEY_RIGHT)
	{
		switch (keyhitHD)
		{
		case KEY_UP:
		{
			switch (this->inputDay)
			{
			case DSHoaDon::chonNgayChay:
				inputDay = chonOption;
				break;
			case DSHoaDon::chonThangChay:
				inputDay = chonOption;
				break;
			case DSHoaDon::chonNamChay:
				inputDay = chonOption;
				break;
			case DSHoaDon::chonNgayDung:
				inputDay = chonNgayChay;
				break;
			case DSHoaDon::chonThangDung:
				inputDay = chonThangChay;
				break;
			case DSHoaDon::chonNamDung:
				inputDay = chonNamChay;
				break;
			case DSHoaDon::chonOption:
				inputDay = chonNgayDung;
				break;
			default:
				break;
			}
			break;
		}
		case KEY_DOWN:
		{
			switch (this->inputDay)
			{
			case DSHoaDon::chonNgayChay:
				inputDay = chonNgayDung;
				break;
			case DSHoaDon::chonThangChay:
				inputDay = chonThangDung;
				break;
			case DSHoaDon::chonNamChay:
				inputDay = chonNamDung;
				break;
			case DSHoaDon::chonNgayDung:
				inputDay = chonOption;
				break;
			case DSHoaDon::chonThangDung:
				inputDay = chonOption;
				break;
			case DSHoaDon::chonNamDung:
				inputDay = chonOption;
				break;
			case DSHoaDon::chonOption:
				inputDay = chonNgayChay;
				break;
			default:
				break;
			}
			break;
		}
		case KEY_RIGHT:
		{
			switch (this->inputDay)
			{
			case DSHoaDon::chonNgayChay:
				inputDay = chonThangChay;
				break;
			case DSHoaDon::chonThangChay:
				inputDay = chonNamChay;
				break;
			case DSHoaDon::chonNamChay:
				inputDay = chonNgayChay;
				break;
			case DSHoaDon::chonNgayDung:
				inputDay = chonThangDung;
				break;
			case DSHoaDon::chonThangDung:
				inputDay = chonNamDung;
				break;
			case DSHoaDon::chonNamDung:
				inputDay = chonNgayDung;
				break;
			default:
				break;
			}
			break;
		}
		case KEY_LEFT:
		{
			switch (this->inputDay)
			{
			case DSHoaDon::chonNgayChay:
				inputDay = chonNamChay;
				break;
			case DSHoaDon::chonThangChay:
				inputDay = chonNgayChay;
				break;
			case DSHoaDon::chonNamChay:
				inputDay = chonThangChay;
				break;
			case DSHoaDon::chonNgayDung:
				inputDay = chonNamDung;
				break;
			case DSHoaDon::chonThangDung:
				inputDay = chonNgayDung;
				break;
			case DSHoaDon::chonNamDung:
				inputDay = chonThangDung;
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}

void DSHoaDon::ChangeInputInHD()
{
	if (keyhitHD == KEY_UP || keyhitHD == KEY_DOWN)
	{
		switch (keyhitHD)
		{
		case KEY_UP:
		{
			switch (this->inHD)
			{
			case DSHoaDon::chonSoHD:
				inHD = Option;
				break;
			case DSHoaDon::TimTrongDSHD:
				inHD = chonSoHD;
				break;
			case DSHoaDon::Option:
				inHD = TimTrongDSHD;
				break;
			default:
				break;
			}
			break;
		}
		break;
		case KEY_DOWN:
		{
			switch (this->inHD)
			{
			case DSHoaDon::chonSoHD:
				inHD = TimTrongDSHD;
				break;
			case DSHoaDon::TimTrongDSHD:
				inHD = Option;
				break;
			case DSHoaDon::Option:
				inHD = chonSoHD;
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
	}
}

void DSHoaDon::TurnBackInput(HoaDon newHoaDon)
{
	ClearInsideBox();
	string temp = CharToString(newHoaDon.soHoaDon);
	string temp_date = IntToString(newHoaDon.ngayNhapHoaDon.date);
	string temp_month = IntToString(newHoaDon.ngayNhapHoaDon.month);
	string temp_year = IntToString(newHoaDon.ngayNhapHoaDon.year);
	char choice[2][15] = { "Nhap vat tu","Thoat" };
	this->DrawFormThemHoaDon();
	DrawOptionChoice(choice, 80, 30, 2, 3);
	this->currentAdd = themSoHD;
	if (newHoaDon.loai[0] == 'N')
		gotoXY(62, 25);
	else
		gotoXY(77, 25);
	cout << "X";
	gotoXY(60 + 3, 20);
	cout << "/";
	gotoXY(60 + 7, 20);
	cout << "/";
	gotoXY(60, 20);
	cout << temp_date;
	gotoXY(60 + 4, 20);
	cout << temp_month;
	gotoXY(60 + 8, 20);
	cout << temp_year;
	gotoXY(60, 15);
	cout << temp;
}

void DSHoaDon::TurnBackInputInHD()
{
	ClearInsideBox();
	char browse[1][15] = { "Tim tu DSHD" };
	char choice[2][15] = { "Tim Hoa Don", "Thoat" };
	inHD = chonSoHD;
	this->DrawFormInHD();
	DrawOptionChoice(browse, 80, 16, 1, 0);
	DrawOptionChoice(choice, 85, 20, 2, 3);
}

int DSHoaDon::EscInputAdd(HoaDon newHoaDon)
{
	if (keyhitHD == ESC)
	{
		char choice[2][15] = { "Dong y","Huy" };
		char thoatCT[10][78] =
		{
			"",
			"",
			"",
			"",
			"Ban muon huy viec lap hoa don ?",
			"",
			"",
			"",
			"",
			"",
		};
		TextColor(MAUCHUX);
		textbk(MAUNENO);
		int i = DrawNoti(thoatCT, choice, 2);
		if (i == 0)
		{
			return 1;
		}
		else
		{
			TurnBackInput(newHoaDon);
		}
	}
	return 0;
}

void DSHoaDon::ChooseType(char type[])
{
	if (type[0] == 'N')
		gotoXY(63, 25);
	else
		gotoXY(78, 25);
	while (true)
	{
		keyhitHD = _getch();
		if (keyhitHD == 224)
			keyhitHD = _getch();
		if (keyhitHD == KEY_UP || keyhitHD == KEY_DOWN || keyhitHD == INS)
			return;
		else if (keyhitHD == ENTER || keyhitHD == ESC)
			return;
		else if (keyhitHD == KEY_LEFT)
		{
			if (type[0] == 'N')
			{
				gotoXY(62, 25);
				cout << " ";
				gotoXY(77, 25);
				cout << "X";
				type[0] = 'X';
			}
			else
			{
				gotoXY(77, 25);
				cout << " ";
				gotoXY(62, 25);
				cout << "X";
				type[0] = 'N';
			}
		}
		else if (keyhitHD == KEY_RIGHT)
		{
			if (type[0] == 'N')
			{
				gotoXY(62, 25);
				cout << " ";
				gotoXY(77, 25);
				cout << "X";
				type[0] = 'X';
			}
			else
			{
				gotoXY(77, 25);
				cout << " ";
				gotoXY(62, 25);
				cout << "X";
				type[0] = 'N';
			}
		}
	}
}

void DSHoaDon::ThemHoaDon()
{
	HoaDon addHoaDon;
	ChiTietHoaDon cthd;
	cthd.soLuongVatTu = 0;
	addHoaDon.soHoaDon[0] = '\0';
	strcpy(addHoaDon.loai, "N");
	time_t hientai = time(0);
	tm* now = localtime(&hientai);
	addHoaDon.ngayNhapHoaDon.date = now->tm_mday;
	addHoaDon.ngayNhapHoaDon.month = now->tm_mon + 1;
	addHoaDon.ngayNhapHoaDon.year = now->tm_year + 1900;
	if (keyhitHD == INS) {
		char choice[2][15] = { "Nhap vat tu","Thoat" };
		this->DrawFormThemHoaDon();
		DrawOptionChoice(choice, 80, 30, 2, 3);
		this->currentAdd = themSoHD;
		gotoXY(62, 25);
		cout << "X";
		gotoXY(60 + 3, 20);
		cout << "/";
		gotoXY(60 + 7, 20);
		cout << "/";
		while (true)
		{
			this->InputAdd(addHoaDon);
			this->ChangeInputAdd();
			if (keyhitHD == INS)
			{
				DanhSachNhanVien dsCu = connectFile->getDanhSachNhanVienPhu();
				DanhSachNhanVien dsCu2 = connectFile->getDanhSachNhanVienPhu2();
				int i = this->CheckHoaDon(addHoaDon, this->dsNhanVien);
				int j = this->CheckHoaDon(addHoaDon, dsCu);
				int k = this->CheckHoaDon(addHoaDon, dsCu2);
				if (i != 1 || j != 1|| k!= 1)
				{
					char choiceSua[3][15] = { "Dong y" };
					char thongBaoSua[10][78] =
					{
						"",
						"",
						"Thong tin nhap bi sai!",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
					};
					if (i == 2)
						strcpy(thongBaoSua[5], "Note: So hoa don khong duoc rong.");
					else if (i == 3 || j == 3 || k == 3)
						strcpy(thongBaoSua[5], "Note: So hoa don bi trung.");
					else if (i == 4)
						strcpy(thongBaoSua[5], "Note: Ngay khong hop le.");
					DrawNoti(thongBaoSua, choiceSua, 1);
					this->TurnBackInput(addHoaDon);
				}
				else
				{
					char choiceSua[3][15] = { "Dong y","Huy" };
					char thongBaoSua[10][78] =
					{
						"",
						"",
						"Thong tin nhap hop le!",
						"",
						"",
						"",
						"Ban chac chan muon lap chi tiet hoa don?",
						"",
						"",
						"",
					};
					int i = DrawNoti(thongBaoSua, choiceSua, 2);
					if (i == 0)
					{
						int t = this->ThemChiTietHoaDon(addHoaDon, cthd);//int i = 0:them or i = 1:huy
						if (t == 0)
						{
							InsertLast(addHoaDon);
							InsertLastChiTietHoaDon(cthd);
							this->firstList = this->currentList = this->GetListHoaDon().first;
							this->lastList = endList(this->firstList);
							this->DrawHoaDon();
							this->travese();
							this->traveseList();
							keyhitHD = 0;
							break;
						}
						else if (t == 1)
						{
							ClearInsideBox();
							keyhitHD = ESC;
							return;
						}
					}
					else
						this->TurnBackInput(addHoaDon);
				}
			}
			if (this->EscInputAdd(addHoaDon)) {
				if (this->GetListHoaDon().first != NULL)
				{
					this->DrawHoaDon();
					this->traveseList();
				}
				else
					keyhitHD = ESC;
				break;
			}
		}
	}
}

void DSHoaDon::SelectHD()
{
	if (keyhitHD == ENTER)
	{
		ClearInsideBox();
		string temp = CharToString(this->currentList->infoHoaDon.soHoaDon);
		string temp_date = IntToString(this->currentList->infoHoaDon.ngayNhapHoaDon.date);
		string temp_month = IntToString(this->currentList->infoHoaDon.ngayNhapHoaDon.month);
		string temp_year = IntToString(this->currentList->infoHoaDon.ngayNhapHoaDon.year);
		this->DrawFormThemHoaDon();
		//this->currentAdd = themSoHD;
		if (this->currentList->infoHoaDon.loai[0] == 'N')
			gotoXY(62, 25);
		else
			gotoXY(77, 25);
		cout << "X";
		gotoXY(60 + 3, 20);
		cout << "/";
		gotoXY(60 + 7, 20);
		cout << "/";
		gotoXY(60, 20);
		cout << temp_date;
		gotoXY(60 + 4, 20);
		cout << temp_month;
		gotoXY(60 + 8, 20);
		cout << temp_year;
		gotoXY(60, 15);
		cout << temp;
		char choice[3][15] = { "Xoa","Xem chi tiet","Thoat" };
		DrawOptionChoice(choice, 80, 30, 3, 3);
		int i = ChooseOption(choice, 80, 30, 3, 3, 1);
		if (i == 0)
		{
			DanhSachNhanVien dsCu2 = connectFile->getDanhSachNhanVienPhu2();
			int check = 0;
			for (int i = 0; i < dsCu2.soLuongNhanVien; i++)
			{
				if (this->dsNhanVien.nodes[this->viTriCurrent]->maNV == dsCu2.nodes[i]->maNV)
				{
					check = 1;
					dsCu2.nodes[i]->PTRHoaDonNhanVien.last->next = new NodesHoaDon;
					dsCu2.nodes[i]->PTRHoaDonNhanVien.last->next->infoHoaDon = this->currentList->infoHoaDon;
					dsCu2.nodes[i]->PTRHoaDonNhanVien.last->next->PTRChiTietHoaDon = new ChiTietHoaDon;
					*dsCu2.nodes[i]->PTRHoaDonNhanVien.last->next->PTRChiTietHoaDon = *this->currentList->PTRChiTietHoaDon;
					dsCu2.nodes[i]->PTRHoaDonNhanVien.last = dsCu2.nodes[i]->PTRHoaDonNhanVien.last->next;
					dsCu2.nodes[i]->PTRHoaDonNhanVien.last->next = NULL;
					/*if (this->currentList->PTRChiTietHoaDon->soLuongVatTu != 0)
					{
						DSLienKetDon dshdCu;
						DanhSachTuyenTinh dsCTHDCu;
						dshdCu.SetListHoaDon(dsCu2.nodes[i]->PTRHoaDonNhanVien);
						for (int k = 0; k < this->currentList->PTRChiTietHoaDon->soLuongVatTu; k++)
							dsCTHDCu.InsertOrder(this->currentList->PTRChiTietHoaDon->nodesChiTiet[k], dsCTHDCu.GetChiTietHoaDon().soLuongVatTu);
						dshdCu.InsertLast(this->currentList->infoHoaDon);
						dshdCu.InsertLastChiTietHoaDon(dsCTHDCu.GetChiTietHoaDon());
						dsCu2.nodes[i]->PTRHoaDonNhanVien = dshdCu.GetListHoaDon();
						connectFile->setDanhSachSinhVienPhu2(dsCu2);
						break;
					}
					else
					{
						DSLienKetDon dshdCu;
						dshdCu.InsertLast(this->currentList->infoHoaDon);
					}*/
				}
			}
			if (check == 0)
			{
				dsCu2.nodes[dsCu2.soLuongNhanVien] = new NhanVien;
				dsCu2.nodes[dsCu2.soLuongNhanVien]->PTRHoaDonNhanVien.first = dsCu2.nodes[dsCu2.soLuongNhanVien]->PTRHoaDonNhanVien.last = NULL;
				PTRHoaDon p = new NodesHoaDon;
				p->next = NULL;
				p->infoHoaDon = this->currentList->infoHoaDon;
				p->PTRChiTietHoaDon = new ChiTietHoaDon;
				*p->PTRChiTietHoaDon = *this->currentList->PTRChiTietHoaDon;
				dsCu2.nodes[dsCu2.soLuongNhanVien]->ho = this->dsNhanVien.nodes[this->viTriCurrent]->ho;
				dsCu2.nodes[dsCu2.soLuongNhanVien]->maNV = this->dsNhanVien.nodes[this->viTriCurrent]->maNV;
				dsCu2.nodes[dsCu2.soLuongNhanVien]->phai = this->dsNhanVien.nodes[this->viTriCurrent]->phai;
				dsCu2.nodes[dsCu2.soLuongNhanVien]->ten = this->dsNhanVien.nodes[this->viTriCurrent]->ten;
				dsCu2.nodes[dsCu2.soLuongNhanVien]->PTRHoaDonNhanVien.first = dsCu2.nodes[dsCu2.soLuongNhanVien]->PTRHoaDonNhanVien.last = p;
				dsCu2.soLuongNhanVien++;
				//connectFile->setDanhSachSinhVienPhu2(dsCu2);
			}
			connectFile->setDanhSachSinhVienPhu2(dsCu2);
			if (this->currentList == x.hoaDonDauTrang[x.trangHienTai]) //cur la dau trang
			{
				if (this->currentList != this->GetListHoaDon().first) //cur ko phai la fisrt toan bo danh sach
				{
					this->lastList = endList(x.hoaDonDauTrang[--x.trangHienTai]);
					this->firstList = x.hoaDonDauTrang[x.trangHienTai];
					this->CapnhatNodesdautrang();
					delete this->currentList->PTRChiTietHoaDon;
					DeleteInfo(this->currentList->infoHoaDon);
					this->currentList = this->lastList;
				}
				else //cur la first toan bo danh sach
				{
					if (this->GetListHoaDon().first->next == NULL) // truong hop toan bo danh sach co 1 phan tu
					{
						delete this->currentList->PTRChiTietHoaDon;
						DeleteInfo(this->currentList->infoHoaDon);
						dsNhanVien.nodes[viTriCurrent]->PTRHoaDonNhanVien.first = this->GetListHoaDon().first;
						//this->firstList = this->lastList = this->currentList = NULL;
						//-----------------------------------------------------------------------------------------------------------------------------------------------		
						char choice[2][15] = { "Them","Huy" };
						char ThemHD[10][78] =
						{
							"",
							"",
							"",
							"Nhan vien chua co hoa don",
							"Ban co muon them hoa don?",
							"",
							"",
							"",
							"",
							"",
						};
						int i = DrawNoti(ThemHD, choice, 2);
						if (i == 0)
						{
							keyhitHD = INS;
							this->ThemHoaDon();
							if (this->ExitHD(keyhitHD))
							{
								ClearInsideBox();
								return;
							}
						}
						else
						{
							keyhitHD = ESC;
							ClearInsideBox();
							return;
						}
						//--------------------------------------------------------------------------------------------------------------------------------------
					}
					else // con nhieu phan tu
					{
						x.hoaDonDauTrang[x.trangHienTai] = x.hoaDonDauTrang[x.trangHienTai]->next;
						this->firstList = this->firstList->next;
						this->lastList = endList(this->firstList);
						this->CapnhatNodesdautrang();
						delete this->currentList->PTRChiTietHoaDon;
						DeleteInfo(this->currentList->infoHoaDon);
						this->currentList = this->firstList;
					}
				}
			}

			else if (this->currentList == this->lastList) // truong hop cur la lastlist (last toan bo ds cung la 1 lastlist)
			{
				this->CapnhatNodesdautrang();
				delete this->currentList->PTRChiTietHoaDon;
				DeleteInfo(this->currentList->infoHoaDon);
				this->lastList = this->currentList = endList(this->firstList);
			}
			else // truong hop cur binh thuong
			{
				this->CapnhatNodesdautrang();
				PTRHoaDon temp = this->currentList ->next;
				delete this->currentList->PTRChiTietHoaDon;
				DeleteInfo(this->currentList->infoHoaDon);
				this->currentList = temp;
				this->lastList = endList(this->firstList);
			}
			ClearInsideBox();
			this->DrawHoaDon();
			this->travese();
			this->traveseList();
		}
		else if (i == 1)
		{
			XemChiTietHoaDon(this->currentList);
		}
		else
		{
			ClearInsideBox();
			this->DrawHoaDon();
			this->travese();
			this->traveseList();
		}
	}
}

void DSHoaDon::CapnhatNodesdautrang()
{
	for (int i = x.trangHienTai + 1; i < MAXTRANGHD; i++)
	{
		if (x.hoaDonDauTrang[i] == NULL)
			break;
		x.hoaDonDauTrang[i] = x.hoaDonDauTrang[i]->next;
	}
}

int DSHoaDon::ExitHD(int keyhit)
{
	if (keyhit == ESC)
		return 1;
	return 0;
}

void DSHoaDon::MainHD(ConnectFile * connect, int vitrinhanvien)
{
	this->connectFile = connect;
	this->dsNhanVien = connect->getDanhSachNhanVien();
	this->viTriCurrent = vitrinhanvien;
	this->SetListHoaDon(dsNhanVien.nodes[viTriCurrent]->PTRHoaDonNhanVien);
	this->DrawHoaDon();
	this->keyhitHD = 0;
	firstList = currentList = x.hoaDonDauTrang[x.trangHienTai] = this->GetListHoaDon().first;
	if (this->GetListHoaDon().first != NULL) 
	{ 
		lastList = endList(firstList);
	}
	else //truong hop nhan vien khong co hoa don nao, ma ham travese list, endlist chi dung dc cho danh sach da co it nhat 1 hoa don
	{
		char choice[2][15] = { "Them","Huy" };
		char ThemHD[10][78] =
		{
			"",
			"",
			"",
			"Nhan vien chua co hoa don",
			"Ban co muon them hoa don?",
			"",
			"",
			"",
			"",
			"",
		};
		int i = DrawNoti(ThemHD, choice, 2);
		if (i == 0)
		{
			keyhitHD = INS;
			this->ThemHoaDon();
			if (this->ExitHD(keyhitHD))
			{
				ClearInsideBox();
				return;
			}		
		}
		else
		{
			ClearInsideBox();
			return;
		}
	}
	while (true) {
		if (this->ExitHD(keyhitHD))
			break;
		this->travese();
		this->traveseList();
		this->ThemHoaDon();
		this->SelectHD();
		if (this->ExitHD(keyhitHD))
			break;
		keyhitHD = _getch();
	}
	dsNhanVien.nodes[viTriCurrent]->PTRHoaDonNhanVien.first = this->GetListHoaDon().first;
	dsNhanVien.nodes[viTriCurrent]->PTRHoaDonNhanVien.last = this->GetListHoaDon().last;
	connect->setDanhSachSinhVien(this->dsNhanVien);
}

void DSHoaDon::TimDSHD_InHoaDon()
{
	DanhSachNhanVien ds[3];
	ds[0] = connectFile->getDanhSachNhanVien();
	ds[1] = connectFile->getDanhSachNhanVienPhu();
	ds[2] = connectFile->getDanhSachNhanVienPhu2();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < ds[i].soLuongNhanVien; j++)
		{
			for (PTRHoaDon k = ds[i].nodes[j]->PTRHoaDonNhanVien.first; k != NULL; k = k->next)
			{
				int check = 0;
				for (int t = 0; t < dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; t++)
				{
					if (dsThongKe.GetDanhSachNhanVien().nodes[t]->maNV == ds[i].nodes[j]->maNV)
					{
						check = 1;
						PTRHoaDon temp = new NodesHoaDon;
						temp->infoHoaDon = k->infoHoaDon;
						temp->PTRChiTietHoaDon = new ChiTietHoaDon;
						*temp->PTRChiTietHoaDon = *k->PTRChiTietHoaDon;
						temp->next = dsThongKe.GetDanhSachNhanVien().nodes[t]->PTRHoaDonNhanVien.first;
						dsThongKe.GetDanhSachNhanVien().nodes[t]->PTRHoaDonNhanVien.first = temp;
						break;
					}
				}
				if (check == 0)
				{
					NhanVien temp;
					temp.ho = ds[i].nodes[j]->ho;
					temp.ten = ds[i].nodes[j]->ten;
					temp.maNV = ds[i].nodes[j]->maNV;
					temp.phai = ds[i].nodes[j]->phai;
					PTRHoaDon tempHD = new NodesHoaDon;
					tempHD->infoHoaDon = k->infoHoaDon;
					tempHD->PTRChiTietHoaDon = new ChiTietHoaDon;
					*tempHD->PTRChiTietHoaDon = *k->PTRChiTietHoaDon;
					tempHD->next = NULL;
					temp.PTRHoaDonNhanVien.first = temp.PTRHoaDonNhanVien.last = tempHD;
					dsThongKe.ThemNhanVienTheoTen(temp);
				}

			}
		}
	}
}

void DSHoaDon::MainInHoaDon(ConnectFile* connect)
{
	this->connectFile = connect;
	this->TimTuDSHD();
	if (this->GetListHoaDon().first == NULL)
	{
		char choice[3][15] = { "Dong y" };
		char thongBao[10][78] =
		{
			"",
			"",
			"",
			"",
			"Khong co hoa don nao!",
			"",
			"",
			"",
			"",
			"",
		};
		TextColor(0);
		textbk(15);
		DrawNoti(thongBao, choice, 1);
		ClearInsideBox();
		return;
	}
	HoaDon findHD;
	findHD.soHoaDon[0] = '\0';
	char browse[1][15] = { "Tim tu DSHD" };
	char choice[2][15] = { "Tim Hoa Don", "Thoat" };
	inHD = chonSoHD;
	this->DrawFormInHD();
	DrawOptionChoice(browse, 80, 16, 1, 0);
	DrawOptionChoice(choice, 85, 20, 2, 3);
	while (true)
	{
		this->InputInHD(findHD);
		this->ChangeInputInHD();
		this->TimTatCaHoaDon();
		this->SelectInHoaDon(findHD);
		if (this->ExitHD(keyhitHD))
		{
			ClearInsideBox();
			keyhitHD = 0;
			/*this->SetListHoaDon(this->dsThongKe.);*/
			//this->GiaiPhongList();
			//this->GiaiPhong_dsThongKe();
			break;
		}
	}
}

void DSHoaDon::TimDSHDTheoNgay(Ngay startDay, Ngay endDay)
{
	DanhSachNhanVien ds[3];
	/*this->SetListHoaDon(dsThongKe);
	this->Create_ListHoaDon();*/
	ds[0] = connectFile->getDanhSachNhanVien();
	ds[1] = connectFile->getDanhSachNhanVienPhu();
	ds[2] = connectFile->getDanhSachNhanVienPhu2();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < ds[i].soLuongNhanVien; j++)
		{
			for (PTRHoaDon k = ds[i].nodes[j]->PTRHoaDonNhanVien.first; k != NULL; k = k->next)
			{
				if (DateCmp(endDay, k->infoHoaDon.ngayNhapHoaDon) >= 0 && DateCmp(k->infoHoaDon.ngayNhapHoaDon, startDay) >= 0)
				{
					//this->InsertLast(k->infoHoaDon);
					int check = 0;
					for (int t = 0; t < dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; t++)
					{
						if (dsThongKe.GetDanhSachNhanVien().nodes[t]->maNV == ds[i].nodes[j]->maNV)
						{
							check = 1;
							PTRHoaDon temp = new NodesHoaDon;
							temp->infoHoaDon = k->infoHoaDon;
							temp->PTRChiTietHoaDon = new ChiTietHoaDon;
							*temp->PTRChiTietHoaDon = *k->PTRChiTietHoaDon;
							temp->next = dsThongKe.GetDanhSachNhanVien().nodes[t]->PTRHoaDonNhanVien.first;
							dsThongKe.GetDanhSachNhanVien().nodes[t]->PTRHoaDonNhanVien.first = temp;
							break;
						}
					}
					if (check == 0)
					{
						NhanVien temp;
						temp.ho = ds[i].nodes[j]->ho;
						temp.ten = ds[i].nodes[j]->ten;
						temp.maNV = ds[i].nodes[j]->maNV;
						temp.phai = ds[i].nodes[j]->phai;
						PTRHoaDon tempHD = new NodesHoaDon;
						tempHD->infoHoaDon = k->infoHoaDon;
						tempHD->PTRChiTietHoaDon = new ChiTietHoaDon;
						*tempHD->PTRChiTietHoaDon = *k->PTRChiTietHoaDon;
						tempHD->next = NULL;
						temp.PTRHoaDonNhanVien.first = temp.PTRHoaDonNhanVien.last = tempHD;
						dsThongKe.ThemNhanVienTheoTen(temp);
					}
				}
			}
		}
	}
}

void DSHoaDon::TimTuDSHD()
{
	ListHoaDon listDSThongKe;
	listDSThongKe.first = listDSThongKe.last = NULL;
	this->SetListHoaDon(listDSThongKe);
	this->TimDSHD_InHoaDon();
	for (int i = 0; i < this->dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; i++)
	{
		for (PTRHoaDon j = dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first; j != NULL; j = j->next)
		{
			InsertLast(j->infoHoaDon);
			InsertLastChiTietHoaDon(*j->PTRChiTietHoaDon);
		}
	}
}

void DSHoaDon::SelectInHoaDon(HoaDon& find)
{
	if (keyhitHD == INS)
	{

		for (int i = 0; i < dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; i++)
		{
			for (PTRHoaDon j = dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first; j != NULL; j = j->next)
			{
				if (strcmp(j->infoHoaDon.soHoaDon, find.soHoaDon) == 0) //neu tim dc se cho xem hoa don
				{
					while (true)
					{

						ClearInsideBox();
						//viet cac thong tin cua hoa don
						gotoXY(70, 10);
						cout << "Nhan vien phu trach: " << this->TimTenNV(j);
						gotoXY(70, 12);
						cout << "So hoa don: " << CharToString(j->infoHoaDon.soHoaDon);
						gotoXY(70, 14);
						string temp_date = IntToString(j->infoHoaDon.ngayNhapHoaDon.date) + " / " + IntToString(j->infoHoaDon.ngayNhapHoaDon.month) + " / " + IntToString(j->infoHoaDon.ngayNhapHoaDon.year);
						cout << "Ngay Nhap Hoa Don: " << temp_date;
						gotoXY(70, 16);
						cout << "Loai: " << j->infoHoaDon.loai;
						gotoXY(70, 18);
						string temp_trigia = to_string(this->TriGiaHD(j));
						cout << "Tri gia hoa don: " << DelFloatTrail(temp_trigia);
						//
						char choice[2][15] = { "Xem Chi Tiet","Thoat" };
						DrawOptionChoice(choice, 80, 25, 2, 3);
						while (true)
						{
							int i = ChooseOption(choice, 80, 25, 2, 3, 1);
							if (i == 0)
							{
								//xem chi tiet
								this->XemChiTietHoaDon(j);
								break;
							}
							else if (i == 1 || i == 2)
								keyhitHD = ESC;
							if (keyhitHD == ESC)
							{
								this->TurnBackInputInHD();
								keyhitHD = 0;
								return;
							}

						}
					}
				}
			}
		}
		char thongBaoRong[10][78] =
		{
			"",
			"",
			"",
			"Hoa Don Khong Ton Tai",
			"",
			"",
			"",
			"",
			"",
			""
		};
		char ok[1][15] = { "OK" };
		DrawNoti(thongBaoRong, ok, 1);
		this->TurnBackInputInHD();
		keyhitHD = 0;
	}
}

void DSHoaDon::MainThongKeHD(ConnectFile* connect)
{
	this->connectFile = connect;
	char choice[2][15] = { "Xem Thong Ke", "Thoat" };
	Ngay startDay, endDay;
	time_t hientai = time(0);
	tm* now = localtime(&hientai);
	startDay.date = now->tm_mday;
	startDay.month = now->tm_mon + 1;
	startDay.year = now->tm_year + 1900;
	endDay.date = now->tm_mday;
	endDay.month = now->tm_mon + 1;
	endDay.year = now->tm_year + 1900;
	inputDay = chonNgayChay;
	this->DrawFormThongKe();
	gotoXY(60, 15);
	cout << startDay.date;
	gotoXY(65, 15);
	cout << startDay.month;
	gotoXY(70, 15);
	cout << startDay.year;
	gotoXY(60, 20);
	cout << endDay.date;
	gotoXY(65, 20);
	cout << endDay.month;
	gotoXY(70, 20);
	cout << endDay.year;
	DrawOptionChoice(choice, 80, 25, 2, 3);
	while (true)
	{
		this->InputAddDT(startDay, endDay);
		this->ChangeInputDT();
		this->ThongKe(startDay, endDay);
		if (this->ExitHD(keyhitHD))
		{
			keyhitHD = 0;
			break;
		}
	}
}

void DSHoaDon::ThongKe(Ngay startDay, Ngay endDay)
{
	if (keyhitHD == INS)
	{
		char choice[2][15] = { "Xem Thong Ke", "Thoat" };
		if (!CheckDate(startDay) || !CheckDate(endDay) || DateCmp(startDay, endDay) == 1)
		{
			char choiceSai[2][15] = { "Sua Lai", "Thoat" };
			char thongBaoSai[10][78] =
			{
				"",
				"",
				"",
				"Loi Nhap du lieu",
				"",
				"",
				"",
				"",
				"",
				""
			};
			if (!CheckDate(startDay))
				strcpy(thongBaoSai[5], "Ngay bat dau sai");
			else if (!CheckDate(endDay))
				strcpy(thongBaoSai[5], "Ngay ket thuc Sai");
			else if (DateCmp(startDay, endDay) == 1)
				strcpy(thongBaoSai[5], "Ngay ket thuc phai lon hon ngay bat dau Sai");
			int i = DrawNoti(thongBaoSai, choiceSai, 2);
			if (i == 0)
			{
				this->DrawFormThongKe();
				gotoXY(60, 15);
				cout << startDay.date;
				gotoXY(65, 15);
				cout << startDay.month;
				gotoXY(70, 15);
				cout << startDay.year;
				gotoXY(60, 20);
				cout << endDay.date;
				gotoXY(65, 20);
				cout << endDay.month;
				gotoXY(70, 20);
				cout << endDay.year;
				DrawOptionChoice(choice, 80, 25, 2, 3);
				keyhitHD = 0;
				return;
			}
			else if (i == 1 || i == 2)
			{
				ClearInsideBox();
				keyhitHD = ESC;
				return;
			}
		}
		this->TimDSHDTheoNgay(startDay, endDay); //tim dsThongKe
		//SetListHoaDon roi dung cac ham trong DSLienKetDon
		ListHoaDon listDSThongKe;
		listDSThongKe.first = listDSThongKe.last = NULL;
		this->SetListHoaDon(listDSThongKe);
		/*this->Create_ListHoaDon();*/
		for (int i = 0; i < this->dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; i++)
		{
			for (PTRHoaDon j = dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first; j != NULL; j = j->next)
			{
				InsertLast(j->infoHoaDon);
				InsertLastChiTietHoaDon(*j->PTRChiTietHoaDon);
			}
		}
		firstList = currentList = x.hoaDonDauTrang[x.trangHienTai] = this->GetListHoaDon().first;
		
		/*this->firstList = this->firstRank = this->currRank = this->TinhTopDoanhThu(startDay, endDay);
		int stop = 0;*/

		if (this->firstList != NULL)
		{
			lastList = endList(firstList);
			this->DrawThongKe();
			keyhitHD = 0;
			while (true)
			{
				this->travese();
				this->WriteThongKe();
				if (this->ExitHD(keyhitHD))
				{
					//this->GiaiPhongList();
					this->GiaiPhong_dsThongKe();
					this->DrawFormThongKe();
					gotoXY(60, 15);
					cout << startDay.date;
					gotoXY(65, 15);
					cout << startDay.month;
					gotoXY(70, 15);
					cout << startDay.year;
					gotoXY(60, 20);
					cout << endDay.date;
					gotoXY(65, 20);
					cout << endDay.month;
					gotoXY(70, 20);
					cout << endDay.year;
					DrawOptionChoice(choice, 80, 25, 2, 3);
					keyhitHD = 0;
					break;
				}
				keyhitHD = _getch();
			}
		}
		else
		{
			char thongBaoRong[10][78] =
			{
				"",
				"",
				"",
				"Khong co hoa don nao trong khoang thoi gian nay",
				"",
				"",
				"",
				"",
				"",
				""
			};
			char ok[1][15] = { "OK" };
			DrawNoti(thongBaoRong, ok, 1);
			this->DrawFormThongKe();
			gotoXY(60, 15);
			cout << startDay.date;
			gotoXY(65, 15);
			cout << startDay.month;
			gotoXY(70, 15);
			cout << startDay.year;
			gotoXY(60, 20);
			cout << endDay.date;
			gotoXY(65, 20);
			cout << endDay.month;
			gotoXY(70, 20);
			cout << endDay.year;
			DrawOptionChoice(choice, 80, 25, 2, 3);
			keyhitHD = 0;
		}
	}
}

void DSHoaDon::GiaiPhong_dsThongKe()
{
	/*for (int i = 0; i < dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; i++)
	{
		this->SetListHoaDon(dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien);
		this->GiaiPhongList();
	}*/
	PTRHoaDon temp;
	for (int i = 0; i < dsThongKe.GetDanhSachNhanVien().soLuongNhanVien; i++)
	{
		while (dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first != NULL)
		{
			delete dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first->PTRChiTietHoaDon;
			temp = dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first;
			dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first = dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first->next;
			delete temp;
		}
		this->dsThongKe.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.last = NULL;
	}
	dsThongKe.GiaiPhong();
}


DanhSachNhanVien DSHoaDon::ReturnDSNhanVien()
{
	return this->dsNhanVien;
}

int DSHoaDon::ThemChiTietHoaDon(HoaDon newHoaDon, ChiTietHoaDon& cthd) //co the la int 0: hoan thanh, 1: huy
{
	int i = 1;
	char option[3][15] = { "Hoan Thanh", "Them Chi Tiet", "Huy" };
	//PTRHoaDon temp_addHD = this->GetListHoaDon().last;
	PTRHoaDon temp_addHD = new NodesHoaDon;
	temp_addHD->infoHoaDon = newHoaDon;
	temp_addHD->PTRChiTietHoaDon = new ChiTietHoaDon;
	*temp_addHD->PTRChiTietHoaDon = cthd;

	while (true)
	{	
		if (i == 1) //neu == 1: nhap them vat tu //continue
		{
			/*DSCTHoaDon chiTietHoaDon;*/
			/*chiTietHoaDon.SetChiTietHoaDon(cthd);*/
			//chiTietHoaDon.MainThemCTHD(this->connectFile, cthd);
			DSCTHoaDon* chiTietHoaDon = new DSCTHoaDon();
			chiTietHoaDon->MainCTHD(this->connectFile, temp_addHD);
			cthd = chiTietHoaDon->GetChiTietHoaDon();
			delete chiTietHoaDon;
			//this->InsertLastChiTietHoaDon(*temp_addHD->PTRChiTietHoaDon);
			ClearInsideBox();
			this->DrawFormThemHoaDon();
			DrawOptionChoice(option, 80, 30, 3, 3);
			//viet cac thong tin cua hoa don lai
			string temp = CharToString(newHoaDon.soHoaDon);
			string temp_date = IntToString(newHoaDon.ngayNhapHoaDon.date);
			string temp_month = IntToString(newHoaDon.ngayNhapHoaDon.month);
			string temp_year = IntToString(newHoaDon.ngayNhapHoaDon.year);
			if (newHoaDon.loai[0] == 'N')
				gotoXY(62, 25);
			else
				gotoXY(77, 25);
			cout << "X";
			gotoXY(60 + 3, 20);
			cout << "/";
			gotoXY(60 + 7, 20);
			cout << "/";
			gotoXY(60, 20);
			cout << temp_date;
			gotoXY(60 + 4, 20);
			cout << temp_month;
			gotoXY(60 + 8, 20);
			cout << temp_year;
			gotoXY(60, 15);
			cout << temp;
			//ve 3 lua chon, cho ket qua == ?? 
		}
		i = ChooseOption(option, 80, 30, 3, 3, 1);
		if (i == 0)
			return 0; //neu == 0: hoan thanh => nhap hoa don // tra ve 0
		else if (i == 1)
			continue;
		if (i == 2 || i == 3)
			return 1;//neu == 2 || == 3 : huy hoa don, thoat ra ngoai danh sach hoa don //tra ve 1
		//i = chonoption (lock)
	}
}

void DSHoaDon::XemChiTietHoaDon(PTRHoaDon xem)
{
	DSCTHoaDon cthd;
	cthd.MainXemCTHD(this->connectFile, xem);
}

