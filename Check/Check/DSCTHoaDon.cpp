#include "DSCTHoaDon.h"



float DSCTHoaDon::ToTalCost()
{
	float total = 0;
	ChiTietHoaDon temp = this->GetChiTietHoaDon();
	for (int i = 0; i < temp.soLuongVatTu; i++)
		total = total + temp.nodesChiTiet[i].soLuong * temp.nodesChiTiet[i].donGia * (1 + temp.nodesChiTiet[i].VAT / 100);
	return total;
}

DSCTHoaDon::DSCTHoaDon()
{
	//this->DrawChiTietHD();
}


DSCTHoaDon::~DSCTHoaDon()
{
}

int DSCTHoaDon::ViTriEndList()
{
	int run;
	int t = viTriFirst + 10;
	for (run = viTriFirst; run < t && run < this->GetChiTietHoaDon().soLuongVatTu; run++); //run -> next != NULL de ko bi chay lo them dong run = run -> next
	return --run;
}

void DSCTHoaDon::Travese()
{
	//int keyHit = 0;
	if (keypress == 224)
	{
		keypress = _getch();
		if (keypress == KEY_UP) {
			if (viTriCurrent != viTriFirst) {
				viTriCurrent--;
			}
			else if (viTriCurrent == viTriFirst) {
				if (viTriFirst > 0) {
					viTriFirst -= 10;
					viTriCurrent = this->ViTriEndList();
				}
			}
		}
		else if (keypress == KEY_DOWN) {
			if (viTriCurrent != this->ViTriEndList()) {
				viTriCurrent++;
			}
			else if (viTriCurrent == this->ViTriEndList()) {
				if (this->ViTriEndList() != this->GetChiTietHoaDon().soLuongVatTu - 1) {
					viTriFirst = this->ViTriEndList() + 1;
					viTriCurrent = viTriFirst;
				}
			}
		}
		else if (keypress == KEY_RIGHT) {
			if (this->ViTriEndList() != this->GetChiTietHoaDon().soLuongVatTu - 1) {
				viTriFirst = this->ViTriEndList() + 1;
				if (viTriCurrent + 10 <= this->GetChiTietHoaDon().soLuongVatTu - 1)
					viTriCurrent += 10;
				else viTriCurrent = ViTriEndList();
			}
		}
		else if (keypress == KEY_LEFT) {
			if (viTriFirst > 0) {
				viTriFirst -= 10;
				viTriCurrent -= 10;
			}
		}
	}
}

void DSCTHoaDon::TraverseDT()
{
	if (keypress == 224)
	{
		keypress = _getch();
		if (keypress == KEY_UP) {

			if (currRank != firstRank)
				currRank = currRank->left;
			if (currRank == firstListRank && firstListRank != this->firstRank)
			{
				firstListRank = firstListRank->left;
				lastListRank = lastListRank->left;
			}
		}
		else if (keypress == KEY_DOWN) {
			if (currRank != lastRank)
				currRank = currRank->right;
			if (currRank == lastListRank && lastListRank != this->lastRank)
			{
				firstListRank = firstListRank->right;
				lastListRank = lastListRank->right;
			}
		}
	}
}

void DSCTHoaDon::DrawChiTietHD()
{
	ClearInsideBox();
	TextColor(0);
	textbk(15);
	DrawBorderList(44, 15, 11, 5, BOXNVWIDE, 1);
	DrawBorderList(26, 15, 11, 1, 18, 1);
	gotoXY(44, 15);
	cout << char(194);
	gotoXY(44, 37);
	cout << char(193);
	for (int i = 17; i < 37; i += 2)
	{
		gotoXY(44, i);
		cout << char(197);
	}
	DrawTitle(CHITIETTITLE, 40, 6);
	TextColor(10);
	textbk(15);
	int i = 0;
	gotoXY(27, 16);
	cout << CenterTextInSpace("MA VAT TU", 17);
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("TEN VAT TU", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("SO LUONG", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("DON GIA", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("VAT", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("THANH TIEN", BOXNVWIDE - 1);
	TextColor(0);
	textbk(15);
}

void DSCTHoaDon::DrawDoanhThu()
{
	ClearInsideBox();
	TextColor(0);
	textbk(15);
	DrawBorderList(44, 15, 11, 5, BOXNVWIDE, 1);
	DrawBorderList(26, 15, 11, 1, 18, 1);
	gotoXY(44, 15);
	cout << char(194);
	gotoXY(44, 37);
	cout << char(193);
	for (int i = 17; i < 37; i += 2)
	{
		gotoXY(44, i);
		cout << char(197);
	}
	DrawTitle(TOPDTTITLE, 50, 6);
	DrawMenu(TOPDTDANHSACH);
	TextColor(10);
	textbk(15);
	int i = 0;
	gotoXY(27, 16);
	cout << CenterTextInSpace("MA VAT TU", 17);
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("TEN VAT TU", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("SO LUONG", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("GIA TRUNG BINH", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("TON KHO", BOXNVWIDE - 1);
	i += 25;
	gotoXY(45 + i, 16);
	cout << CenterTextInSpace("DOANH THU", BOXNVWIDE - 1);
	TextColor(0);
	textbk(15);
}

void DSCTHoaDon::DrawFormChiTietVatTu()
{
	//drawtile
	//drawmemu
	ClearInsideBox();
	int i = 0;
	TextColor(0);
	textbk(15);
	gotoXY(36, 10);
	cout << "Ma Vat Tu";
	gotoXY(56, 10);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "So Luong";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Don Gia";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "VAT";
	gotoXY(56, 10 + i);
	cout << ":";
}

void DSCTHoaDon::DrawFormDoanhThu()
{
	//drawtile
	//drawmemu
	ClearInsideBox();
	DrawTitle(TOPDTTITLE, 50, 6);
	DrawMenu(TOPDTTITLE);
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
}

void DSCTHoaDon::WriteHang()
{
	int listStart = viTriFirst;
	int listAmount = this->ViTriEndList();
	if (!EmptyList())
	{
		for (int i = listStart; i <= listAmount; i++)
		{
			if (i == viTriCurrent)
			{
				TextColor(4);
				textbk(15);
			}
			gotoXY(27, 18 + (i - listStart) * 2);
			cout << CenterTextInSpace(CharToString(this->GetChiTietHoaDon().nodesChiTiet[i].maVT), 17);
			int j = 0;
			gotoXY(45 + j, 18 + (i - listStart) * 2);
			PTRVatTu temp = dataVatTu.Search(this->GetChiTietHoaDon().nodesChiTiet[i].maVT);
			if (temp == NULL)
				temp = dataVatTuCu.Search(this->GetChiTietHoaDon().nodesChiTiet[i].maVT);
			if (temp == NULL)
				cout << CenterTextInSpace("Khong Ton Tai", 24);
			else
				cout << CenterTextInSpace(temp->info.tenVT, 24);
			j += 25;
			gotoXY(45 + j, 18 + (i - listStart) * 2);
			string tempStr = to_string(this->GetChiTietHoaDon().nodesChiTiet[i].soLuong);
			cout << CenterTextInSpace(DelFloatTrail(tempStr), BOXNVWIDE - 1);
			j += 25;
			gotoXY(45 + j, 18 + (i - listStart) * 2);
			string donVi = (temp == NULL ? "NULL" : temp->info.donViTinh);
			tempStr = to_string(this->GetChiTietHoaDon().nodesChiTiet[i].donGia);
			cout << CenterTextInSpace(DelFloatTrail(tempStr) + "/" + donVi, BOXNVWIDE - 1);
			j += 25;
			gotoXY(45 + j, 18 + (i - listStart) * 2);
			tempStr = to_string(this->GetChiTietHoaDon().nodesChiTiet[i].VAT);
			cout << CenterTextInSpace(DelFloatTrail(tempStr) + "%", BOXNVWIDE - 1);
			j += 25;
			gotoXY(45 + j, 18 + (i - listStart) * 2);
			tempStr = to_string(this->GetChiTietHoaDon().nodesChiTiet[i].soLuong * (this->GetChiTietHoaDon().nodesChiTiet[i].donGia * (1 + (this->GetChiTietHoaDon().nodesChiTiet[i].VAT / 100))));
			cout << CenterTextInSpace(DelFloatTrail(tempStr), BOXNVWIDE - 1);
			if (i == viTriCurrent)
			{
				TextColor(0);
				textbk(15);
			}
		}
		if (listStart + 9 != listAmount)
		{
			textbk(15);
			for (int i = listAmount + 1; i <= listStart + 9; i++)
			{
				gotoXY(27, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", 17);
				int j = 0;
				gotoXY(45 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(45 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(45 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(45 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(45 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
			}
		}
	}
}

void DSCTHoaDon::WriteDT()
{
	int i = 0;
	for (PTRTop p = this->firstListRank; p != lastListRank->right; p = p->right)
	{
		if (p == this->currRank)
		{
			TextColor(4);
			textbk(15);
		}
		gotoXY(27, 18 + i * 2);
		cout << CenterTextInSpace(CharToString(p->maVT), 17);
		int j = 0;
		gotoXY(45 + j, 18 + i * 2);
		cout << CenterTextInSpace(p->tenVT, BOXNVWIDE - 1);
		j += 25;
		gotoXY(45 + j, 18 + i * 2);
		string tempStr = to_string(p->soLuong);
		cout << CenterTextInSpace(DelFloatTrail(tempStr), BOXNVWIDE - 1);
		j += 25;
		gotoXY(45 + j, 18 + i * 2);
		tempStr = to_string(p->donGiaTB);
		cout << CenterTextInSpace(DelFloatTrail(tempStr) + "/" + p->donVi, BOXNVWIDE - 1);
		j += 25;
		gotoXY(45 + j, 18 + i * 2);
		tempStr = to_string(p->tonKho);
		cout << CenterTextInSpace(DelFloatTrail(tempStr), BOXNVWIDE - 1);
		j += 25;
		gotoXY(45 + j, 18 + i * 2);
		tempStr = to_string(p->total);
		cout << CenterTextInSpace(DelFloatTrail(tempStr), BOXNVWIDE - 1);
		i++;
		if (p == this->currRank)
		{
			TextColor(0);
			textbk(15);
		}
	}
}

void DSCTHoaDon::ThemHang()
{
	if (keypress == INS && this->GetChiTietHoaDon().soLuongVatTu < MAXVATTU)
	{
		infoSelect = themMa;
		ChiTietVatTu addVT;
		strcpy_s(addVT.maVT, "");
		addVT.soLuong = 1;
		addVT.donGia = 1000;
		addVT.VAT = 10;
		char choice[2][15] = { "Them","Thoat" };
		char browse[1][15] = { "Tim tu CSDL" };
		this->DrawFormChiTietVatTu();
		DrawOptionChoice(browse, 67, 13, 1, 0);
		DrawOptionChoice(choice, 80, 30, 2, 3);
		this->ExitOption(2, choice, 2, addVT);
		DrawTitle(THEMCHITIETHD, 50, 3);
		DrawMenu(THEMCHITIETHD);
		//drawtitle
		//drawmenu
		while (true)
		{
			this->InputAdd(addVT);
			this->FindVatTu(addVT);
			this->ChangeInput();
			int trung = CheckTrung(addVT);
			int j = this->CheckHang(addVT);
			if (this->ExitMenu(keypress) || keypress == INS)
			{
				if (keypress == INS)
				{
					char choiceSure[3][15] = { "Them","Huy","Thoat" };
					char thongBaoThem[10][78] =
					{
						"",
						"",
						"Ban muon them vat tu vao hoa don ?",
						"",
						"",
						"",
						"",
						"Note: Thong tin se duoc tu dong sua in hoa, khoang trang thich hop",
						"",
						"",
					};
					int i = DrawNoti(thongBaoThem, choiceSure, 3);
					if (i == 0)
					{
						int k = CheckChiTiet(addVT);
						if (k == 1 && j == 1)
						{
							if (trung == 1)
							{
								addVT.soLuong += this->GetChiTietHoaDon().nodesChiTiet[this->Search(addVT)].soLuong;
								this->ChangeCell(this->Search(addVT), addVT);
								this->ExitOption(1, choice, 2, addVT);

							}
							else
							{
								this->InsertOrder(addVT, this->GetChiTietHoaDon().soLuongVatTu);
								this->ExitOption(1, choice, 2, addVT);
							}
							break;
						}
						else if ((j == 0 || j == 3) && k == 1)
						{
							char thongBaoKhongDu[10][78] =
							{
								"",
								"",
								"",
								"Het hang trong kho!",
								"",
								"",
								"",
								"",
								"",
								""
							};
							string str = to_string(dataVatTu.Search(addVT.maVT)->info.soLuongTon);
							str = DelFloatTrail(str);
							string thongBaoHang = "So luong Ton : " + str;
							if (j == 0)
								strcpy_s(thongBaoKhongDu[5], thongBaoHang.c_str());
							char choiceKhongDu[2][15] = { "Nhap lai","Thoat" };
							if (j == 3)
								strcpy_s(thongBaoKhongDu[3], "Ma Vat Tu Khong Ton Tai");
							int t = DrawNoti(thongBaoKhongDu, choiceKhongDu, 2);
							if (t == 0)
							{
								this->ExitOption(2, choice, 2, addVT);
								DrawTitle(THEMCHITIETHD, 50, 3);
								DrawMenu(THEMCHITIETHD);
								continue;
							}
							else if (t == 1 || t == 2)
							{
								this->ExitOption(1, choice, 2, addVT);
								break;
							}
						}
						else if (k > 0)
						{
							char thongBaoSai[10][78] =
							{
								"",
								"",
								"Vat Tu cua ban nhap sai!",
								"",
								"",
								"",
								"",
								"",
								"",
								""
							};
							if (k == 2)
								strcpy(thongBaoSai[5], "Note: Ma vat tu sai,ma vat tu chi co ky tu, khong duoc rong");
							else if (k == 3)
								strcpy(thongBaoSai[5], "Note: So luong sai, so luong phai lon hon 0");
							else if (k == 4)
								strcpy(thongBaoSai[5], "Note: Don gia sai, don gia phai lon hon hoac bang 0");
							else if (k == 5)
								strcpy(thongBaoSai[5], "Note: VAT sai, VAT phai lon hon hoac bang 0");
							char choiceSai[2][15] = { "Nhap lai","Thoat" };
							int t = DrawNoti(thongBaoSai, choiceSai, 2);
							if (t == 0)
							{
								this->ExitOption(2, choice, 2, addVT);
								DrawTitle(THEMCHITIETHD, 50, 3);
								DrawMenu(THEMCHITIETHD);
								continue;
							}
							else if (t == 1 || t == 2)

							{
								this->ExitOption(1, choice, 2, addVT);
								break;
							}
						}
					}
					else if (i == 2 || i == 3)
					{
						this->ExitOption(1, choice, 2, addVT);
						break;
					}
					else if (i == 1)
					{
						this->ExitOption(2, choice, 2, addVT);
						this->CheckHang(addVT);
						DrawTitle(THEMCHITIETHD, 50, 3);
						DrawMenu(THEMCHITIETHD);
						continue;
					}
				}
				else
				{
					this->ExitOption(1, choice, 2, addVT);
					break;
				}
			}
		}
	}
	else if (keypress == INS && this->GetChiTietHoaDon().soLuongVatTu > MAXVATTU)
	{

	}
}

void DSCTHoaDon::FindVatTu(ChiTietVatTu & newVatTu)
{
	if (keypress == CTRL_F)
	{
		DSVatTu* timVatTU = new DSVatTu();
		ListVatTu temp = timVatTU->SelectVatTu(this->con);
		char choice[2][15] = { "Them","Thoat" };
		if (temp != NULL)
			strcpy_s(newVatTu.maVT, temp->maVT);
		this->ExitOption(2, choice, 2, newVatTu);
		DrawTitle(THEMCHITIETHD, 50, 3);
		DrawMenu(THEMCHITIETHD);
		delete timVatTU;
	}
}

void DSCTHoaDon::ExitOption(int choice, char choiceArr[][15], int soOption, ChiTietVatTu vatTu)
{
	// 1 = o lai, 2 = thoat ra, 3 = o lai (sua chi tiet)
	if (choice == 2)
	{
		char browse[1][15] = { "Tim tu CSDL" };
		DrawFormChiTietVatTu();
		DrawOptionChoice(browse, 67, 13, 1, 0);
		DrawOptionChoice(choiceArr, 80, 30, 2, 3);
		gotoXY(60, 10);
		cout << vatTu.maVT;
		gotoXY(60, 15);
		string temp_sl = to_string(vatTu.soLuong);
		cout << DelFloatTrail(temp_sl);
		gotoXY(60, 20);
		string temp_dg = to_string(vatTu.donGia);
		cout << DelFloatTrail(temp_dg);;
		string temp_vat = to_string(vatTu.VAT);
		gotoXY(60, 25);
		cout << DelFloatTrail(temp_vat);;
	}
	else if (choice == 1)
	{
		ClearInsideBox();
		this->DrawChiTietHD();
		DrawMenu(THEMCHITIETNEWHD);
		this->WriteHang();
		this->Travese();
		keypress = 0;
	}
	else if (choice == 3)
	{
		char browse[1][15] = { "Tim tu CSDL" };
		DrawFormChiTietVatTu();
		DrawOptionChoice(browse, 67, 13, 1, 0);
		DrawOptionChoice(choiceArr, 80, 30, 2, 3);
		TextColor(8);
		textbk(15);
		gotoXY(60, 10);
		cout << vatTu.maVT;
		TextColor(0);
		textbk(15);
		gotoXY(60, 15);
		cout << vatTu.soLuong;
		gotoXY(60, 20);
		cout << vatTu.donGia;
		gotoXY(60, 25);
		cout << vatTu.VAT;
	}
}

void DSCTHoaDon::InputAdd(ChiTietVatTu & newVatTu)
{
	switch (this->infoSelect)
	{
	case DSCTHoaDon::themMa:
	{
		string temp = CharToString(newVatTu.maVT);
		InputInfo(temp, 10, 60, 10, keypress, 1);
		strcpy_s(newVatTu.maVT, temp.c_str());
		break;
	}
	case DSCTHoaDon::timVT:
	{
		char browse[1][15] = { "Tim tu CSDL" };
		int i = ChooseOption(browse, 67, 13, 1, 0, 0);
		if (i >= 0)
		{
			if (i == 0)
				keypress = CTRL_F;
			else if (i == 1)
				keypress = ESC;
		}
		else
			keypress = -i;
		//DrawOptionChoice(browse,)
		break;
	}
	case DSCTHoaDon::themSL:
	{
		string temp = to_string(newVatTu.soLuong);
		temp = DelFloatTrail(temp);
		InputInfo(temp, 30, 60, 15, keypress, 5);
		if (temp == "")
			break;
		newVatTu.soLuong = stof(temp);
		break;
	}
	case DSCTHoaDon::themDG:
	{
		string temp = to_string(newVatTu.donGia);
		temp = DelFloatTrail(temp);
		InputInfo(temp, 30, 60, 20, keypress, 5);
		if (temp == "")
			break;
		newVatTu.donGia = stof(temp);
		break;
	}
	case DSCTHoaDon::themVAT:
	{
		string temp = to_string(newVatTu.VAT);
		temp = DelFloatTrail(temp);
		InputInfo(temp, 30, 60, 25, keypress, 5);
		if (temp == "")
			break;
		newVatTu.VAT = stof(temp);
		break;
	}
	case DSCTHoaDon::chonOptionThem:
	{
		char choice[2][15] = { "Them", "Thoat" };
		int i = ChooseOption(choice, 80, 30, 2, 3, 0);
		if (i >= 0)
		{
			if (i == 0)
				keypress = INS;
			else if (i == 1 || i == 2)
				keypress = ESC;
		}
		else
			keypress = -i;
		break;
	}
	case DSCTHoaDon::chonOptionSua:
	{
		char choice[2][15] = { "Sua", "Thoat" };
		int i = ChooseOption(choice, 80, 30, 2, 3, 0);
		if (i >= 0)
		{
			if (i == 0)
				keypress = INS;
			else if (i == 1 || i == 2)
				keypress = ESC;
		}
		else
			keypress = -i;
		break;
	}
	default:
		break;
	}
}

void DSCTHoaDon::InputAddDT(Ngay & start, Ngay & end)
{
	switch (this->inputDay)
	{
	case DSCTHoaDon::chonNgayChay:
	{
		string temp = IntToString(start.date);
		InputInfo(temp, 2, 60, 15, keypress, 8);

		start.date = StringToInt(temp);
		break;
	}
	case DSCTHoaDon::chonThangChay:
	{
		string temp = IntToString(start.month);
		InputInfo(temp, 2, 65, 15, keypress, 8);
		start.month = StringToInt(temp);
		break;
	}
	case DSCTHoaDon::chonNamChay:
	{
		string temp = IntToString(start.year);
		InputInfo(temp, 4, 70, 15, keypress, 8);
		start.year = StringToInt(temp);
		break;
	}
	case DSCTHoaDon::chonNgayDung:
	{
		string temp = IntToString(end.date);
		InputInfo(temp, 2, 60, 20, keypress, 8);
		end.date = StringToInt(temp);
		break;
	};
	case DSCTHoaDon::chonThangDung:
	{
		string temp = IntToString(end.month);
		InputInfo(temp, 2, 65, 20, keypress, 8);
		end.month = StringToInt(temp);
		break;
	}
	case DSCTHoaDon::chonNamDung:
	{
		string temp = IntToString(end.year);
		InputInfo(temp, 4, 70, 20, keypress, 8);
		end.year = StringToInt(temp);
		break;
	}
	case DSCTHoaDon::chonOption:
	{
		char choice[2][15] = { "Tinh Doanh Thu", "Thoat" };
		int i = ChooseOption(choice, 80, 25, 2, 3, 0);
		if (i >= 0)
		{
			if (i == 0)
				keypress = INS;
			else if (i == 1 || i == 2)
				keypress = ESC;
		}
		else
			keypress = -i;
		break;
	}
	default:
		break;
	}
}

void DSCTHoaDon::ChangeInput()
{
	if (keypress == KEY_UP || keypress == KEY_DOWN)
	{
		//keypress = _getch();
		switch (keypress)
		{
		case KEY_UP:
		{
			switch (this->infoSelect)
			{
			case DSCTHoaDon::themMa:
				this->infoSelect = chonOptionThem;
				break;
			case DSCTHoaDon::timVT:
				this->infoSelect = themMa;
				break;
			case DSCTHoaDon::themSL:
				this->infoSelect = timVT;
				break;
			case DSCTHoaDon::themDG:
				this->infoSelect = themSL;
				break;
			case DSCTHoaDon::themVAT:
				this->infoSelect = themDG;
				break;
			case DSCTHoaDon::chonOptionThem:
				this->infoSelect = themVAT;
				break;
			}
			break;
		}

		case KEY_DOWN:
		{
			switch (infoSelect)
			{
			case DSCTHoaDon::themMa:
				this->infoSelect = timVT;
				break;
			case DSCTHoaDon::timVT:
				this->infoSelect = themSL;
				break;
			case DSCTHoaDon::themSL:
				this->infoSelect = themDG;
				break;
			case DSCTHoaDon::themDG:
				this->infoSelect = themVAT;
				break;
			case DSCTHoaDon::themVAT:
				this->infoSelect = chonOptionThem;
				break;
			case DSCTHoaDon::chonOptionThem:
				this->infoSelect = themMa;
				break;
			}
			break;
		}
		}
	}
}

void DSCTHoaDon::ChangeInputFix()
{
	if (keypress == KEY_UP || keypress == KEY_DOWN)
	{
		//keypress = _getch();
		switch (keypress)
		{
		case KEY_UP:
		{
			switch (this->infoSelect)
			{
			case DSCTHoaDon::themSL:
				this->infoSelect = chonOptionSua;
				break;
			case DSCTHoaDon::themDG:
				this->infoSelect = themSL;
				break;
			case DSCTHoaDon::themVAT:
				this->infoSelect = themDG;
				break;
			case DSCTHoaDon::chonOptionSua:
				this->infoSelect = themVAT;
				break;
			}
			break;
		}

		case KEY_DOWN:
		{
			switch (infoSelect)
			{
			case DSCTHoaDon::themSL:
				this->infoSelect = themDG;
				break;
			case DSCTHoaDon::themDG:
				this->infoSelect = themVAT;
				break;
			case DSCTHoaDon::themVAT:
				this->infoSelect = chonOptionSua;
				break;
			case DSCTHoaDon::chonOptionSua:
				this->infoSelect = themSL;
				break;
			}
			break;
		}
		}
	}
}

void DSCTHoaDon::ChangeInputDT()
{
	if (keypress == KEY_UP || keypress == KEY_DOWN || keypress == KEY_LEFT || keypress == KEY_RIGHT)
	{
		switch (keypress)
		{
		case KEY_UP:
		{
			switch (this->inputDay)
			{
			case DSCTHoaDon::chonNgayChay:
				inputDay = chonOption;
				break;
			case DSCTHoaDon::chonThangChay:
				inputDay = chonOption;
				break;
			case DSCTHoaDon::chonNamChay:
				inputDay = chonOption;
				break;
			case DSCTHoaDon::chonNgayDung:
				inputDay = chonNgayChay;
				break;
			case DSCTHoaDon::chonThangDung:
				inputDay = chonThangChay;
				break;
			case DSCTHoaDon::chonNamDung:
				inputDay = chonNamChay;
				break;
			case DSCTHoaDon::chonOption:
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
			case DSCTHoaDon::chonNgayChay:
				inputDay = chonNgayDung;
				break;
			case DSCTHoaDon::chonThangChay:
				inputDay = chonThangDung;
				break;
			case DSCTHoaDon::chonNamChay:
				inputDay = chonNamDung;
				break;
			case DSCTHoaDon::chonNgayDung:
				inputDay = chonOption;
				break;
			case DSCTHoaDon::chonThangDung:
				inputDay = chonOption;
				break;
			case DSCTHoaDon::chonNamDung:
				inputDay = chonOption;
				break;
			case DSCTHoaDon::chonOption:
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
			case DSCTHoaDon::chonNgayChay:
				inputDay = chonThangChay;
				break;
			case DSCTHoaDon::chonThangChay:
				inputDay = chonNamChay;
				break;
			case DSCTHoaDon::chonNamChay:
				inputDay = chonNgayChay;
				break;
			case DSCTHoaDon::chonNgayDung:
				inputDay = chonThangDung;
				break;
			case DSCTHoaDon::chonThangDung:
				inputDay = chonNamDung;
				break;
			case DSCTHoaDon::chonNamDung:
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
			case DSCTHoaDon::chonNgayChay:
				inputDay = chonNamChay;
				break;
			case DSCTHoaDon::chonThangChay:
				inputDay = chonNgayChay;
				break;
			case DSCTHoaDon::chonNamChay:
				inputDay = chonThangChay;
				break;
			case DSCTHoaDon::chonNgayDung:
				inputDay = chonNamDung;
				break;
			case DSCTHoaDon::chonThangDung:
				inputDay = chonNgayDung;
				break;
			case DSCTHoaDon::chonNamDung:
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

int DSCTHoaDon::CheckTrung(ChiTietVatTu & vatTu)
{
	int idTrung = this->Search(vatTu);
	if (idTrung >= 0)
	{
		if (this->GetChiTietHoaDon().nodesChiTiet[idTrung].donGia == vatTu.donGia && this->GetChiTietHoaDon().nodesChiTiet[idTrung].VAT == vatTu.VAT)
		{
			gotoXY(90, 16);
			cout << "Da co mat hang nay o danh sach, so luong se duoc cong don";
			return 1;
		}
		else
		{
			gotoXY(90, 16);
			cout << CenterTextInSpace("", 58);
			return 0;
		}
	}
}

int DSCTHoaDon::CheckHang(ChiTietVatTu & vatTu)
{
	int result = 0;
	PTRVatTu temp = dataVatTu.Search(vatTu.maVT);
	if (temp != NULL)
	{
		if (stricmp(this->currentHoaDon->infoHoaDon.loai, "X") == 0)
		{
			if (temp->info.soLuongTon < vatTu.soLuong)
			{
				string str = to_string(temp->info.soLuongTon);
				str = DelFloatTrail(str);
				gotoXY(90, 15);
				cout << "Het hang, chi con : " << str << " " << temp->info.donViTinh;
			}
			else
			{
				gotoXY(90, 15);
				cout << CenterTextInSpace("", 10);
				result = 1;
			}
		}
		else
			result = 1;
		gotoXY(90, 10);
		cout << CenterTextInSpace("", 26);
		gotoXY(90, 10);
		cout << "(" << temp->info.tenVT << ")";
		gotoXY(90, 20);
		cout << CenterTextInSpace("", 25);
		gotoXY(90, 20);
		cout << "/ " << temp->info.donViTinh;
	}
	else
	{
		gotoXY(90, 10);
		cout << CenterTextInSpace("", 26);
		gotoXY(90, 15);
		cout << CenterTextInSpace("", 10);
		gotoXY(90, 20);
		cout << CenterTextInSpace("", 25);
		gotoXY(90, 16);
		cout << CenterTextInSpace("", 58);
		gotoXY(90, 10);
		cout << "Vat Tu Khong Ton Tai";
		result = 3;
	}
	return result;
}

void DSCTHoaDon::XoaHang()
{
	if (keypress == DEL)
	{
		char choiceXoa[2][15] = { "Xoa","Huy" };
		char thongBaoXoa[10][78] =
		{
			"",
			"",
			"Ban muon them vat tu vao hoa don ?",
			"",
			"",
			"",
			"",
			"Note: Thong tin se duoc tu dong sua in hoa, khoang trang thich hop",
			"",
			"",
		};
		int i = DrawNoti(thongBaoXoa, choiceXoa, 2);
		if (i == 0)
		{
			this->DeleteCell(viTriCurrent);
			if (viTriCurrent == viTriFirst && viTriFirst > 0)
			{
				viTriFirst -= 10;
				viTriCurrent = this->ViTriEndList();
			}
			ClearInsideBox();
			this->DrawChiTietHD();
			this->WriteHang();
		}
		else if (i == 1 || i == 2)
		{
			ClearInsideBox();
			this->DrawChiTietHD();
			this->WriteHang();
		}
	}
}

void DSCTHoaDon::SuaNHang()
{
	if (keypress == ENTER && this->EmptyList() != 1)
	{
		ChiTietVatTu fixVT;
		fixVT = this->GetChiTietHoaDon().nodesChiTiet[viTriCurrent];
		char choice[2][15] = { "Sua","Thoat" };
		char browse[1][15] = { "Tim tu CSDL" };
		this->DrawFormChiTietVatTu();
		DrawOptionChoice(browse, 67, 13, 1, 0);
		DrawOptionChoice(choice, 80, 30, 2, 3);
		this->ExitOption(3, choice, 2, fixVT);
		DrawTitle(SUACHITIETHD, 50, 3);
		DrawMenu(SUACHITIETHD);
		this->CheckHang(fixVT);
		//drawtitle
		//drawmenu
		this->infoSelect = this->themSL;
		while (true)
		{
			this->InputAdd(fixVT);
			this->ChangeInputFix();
			int j = this->CheckHang(fixVT);
			if (this->ExitMenu(keypress) || keypress == INS)
			{
				if (keypress == INS)
				{
					char choiceSure[3][15] = { "Sua","Huy","Thoat" };
					char thongBaoThem[10][78] =
					{
						"",
						"",
						"Ban muon sua vat tu tu hoa don ?",
						"",
						"",
						"",
						"",
						"Note: Thong tin se duoc tu dong sua in hoa, khoang trang thich hop",
						"",
						"",
					};
					int i = DrawNoti(thongBaoThem, choiceSure, 3);
					if (i == 0)
					{
						int k = CheckChiTiet(fixVT);
						if (k == 1 && j == 1)
						{
							this->ChangeCell(viTriCurrent, fixVT);
							this->ExitOption(1, choice, 2, fixVT);
							break;
						}
						else if ((j == 0 || j == 3) && k == 1)
						{
							char thongBaoKhongDu[10][78] =
							{
								"",
								"",
								"",
								"Het hang trong kho!",
								"",
								"",
								"",
								"",
								"",
								""
							};
							string str = to_string(dataVatTu.Search(fixVT.maVT)->info.soLuongTon);
							str = DelFloatTrail(str);
							string thongBaoHang = "So luong Ton : " + str;
							if (j == 0)
								strcpy_s(thongBaoKhongDu[5], thongBaoHang.c_str());
							char choiceKhongDu[2][15] = { "Nhap lai","Thoat" };
							if (j == 3)
								strcpy_s(thongBaoKhongDu[3], "Ma Vat Tu Khong Ton Tai");
							int t = DrawNoti(thongBaoKhongDu, choiceKhongDu, 2);
							if (t == 0)
							{
								this->ExitOption(3, choice, 2, fixVT);
								DrawTitle(SUACHITIETHD, 50, 3);
								DrawMenu(SUACHITIETHD);
								continue;
							}
							else if (t == 1 || t == 2)
							{
								this->ExitOption(1, choice, 2, fixVT);
								break;
							}
						}
						else if (k > 0)
						{
							char thongBaoSai[10][78] =
							{
								"",
								"",
								"Vat Tu cua ban nhap sai!",
								"",
								"",
								"",
								"",
								"",
								"",
								""
							};
							if (k == 2)
								strcpy(thongBaoSai[5], "Note: Ma vat tu sai,ma vat tu chi co ky tu, khong duoc rong");
							else if (k == 3)
								strcpy(thongBaoSai[5], "Note: So luong sai, so luong phai lon hon 0");
							else if (k == 4)
								strcpy(thongBaoSai[5], "Note: Don gia sai, don gia phai lon hon hoac bang 0");
							else if (k == 5)
								strcpy(thongBaoSai[5], "Note: VAT sai, VAT phai lon hon hoac bang 0");
							char choiceSai[2][15] = { "Nhap lai","Thoat" };
							int t = DrawNoti(thongBaoSai, choiceSai, 2);
							if (t == 0)
							{
								this->ExitOption(3, choice, 2, fixVT);
								DrawTitle(SUACHITIETHD, 50, 3);
								DrawMenu(SUACHITIETHD);
								continue;
							}
							else if (t == 1 || t == 2)

							{
								this->ExitOption(1, choice, 2, fixVT);
								break;
							}
						}
					}
					else if (i == 2 || i == 3)
					{
						this->ExitOption(1, choice, 2, fixVT);
						break;
					}
					else if (i == 1)
					{
						this->ExitOption(3, choice, 2, fixVT);
						this->CheckHang(fixVT);
						DrawTitle(SUACHITIETHD, 50, 3);
						DrawMenu(SUACHITIETHD);
						continue;
					}
				}
				else
				{
					this->ExitOption(1, choice, 2, fixVT);
					break;
				}
			}
		}
	}
}

int DSCTHoaDon::ExitMenu(int keyhit)
{
	if (keyhit == ESC)
		return 1;
	return 0;
}

void DSCTHoaDon::MainCTHD(ConnectFile * connect, PTRHoaDon & currentHD)
{
	con = connect;
	dataVatTu.SetPTRVatTu(con->getVatTu());
	this->currentHoaDon = currentHD;
	this->SetChiTietHoaDon(*currentHD->PTRChiTietHoaDon);
	this->DrawChiTietHD();
	DrawMenu(THEMCHITIETNEWHD);
	this->WriteHang();
	viTriFirst = viTriCurrent = 0;
	this->keypress = 0;
	while (true)
	{
		if (this->ExitMenu(keypress))
			break;
		this->Travese();
		this->WriteHang();
		this->ThemHang();
		this->SuaNHang();
		this->XoaHang();
		keypress = _getch();
	}
	*currentHD->PTRChiTietHoaDon = this->GetChiTietHoaDon();
	//ton kho
	for (int i = 0; i < this->GetChiTietHoaDon().soLuongVatTu; i++)
	{
		PTRVatTu temp = dataVatTu.Search(this->GetChiTietHoaDon().nodesChiTiet[i].maVT);
		if (stricmp(currentHD->infoHoaDon.loai, "X") == 0)
			temp->info.soLuongTon -= this->GetChiTietHoaDon().nodesChiTiet[i].soLuong;
		else
			temp->info.soLuongTon += this->GetChiTietHoaDon().nodesChiTiet[i].soLuong;
	}
	connect->setDanhSachVatTu(dataVatTu.GetPTRVatTu());
}

void DSCTHoaDon::MainXemCTHD(ConnectFile * connect, PTRHoaDon & currentHD)
{
	con = connect;
	dataVatTu.SetPTRVatTu(con->getVatTu());
	dataVatTuCu.SetPTRVatTu(con->getVatTuPhu());
	this->currentHoaDon = currentHD;
	this->SetChiTietHoaDon(*currentHD->PTRChiTietHoaDon);
	this->DrawChiTietHD();
	DrawMenu(CHITIETTITLE);
	this->WriteHang();
	viTriFirst = viTriCurrent = 0;
	this->keypress = 0;
	while (true)
	{
		if (this->ExitMenu(keypress))
			break;
		this->Travese();
		this->WriteHang();
		keypress = _getch();
	}
}

void DSCTHoaDon::CopyDataDT(PTRTop a, PTRTop& b)
{
	PTRTop temp = new TopDT;
	temp->donGiaTB = a->donGiaTB;
	temp->donVi = a->donVi;
	strcpy_s(temp->maVT, a->maVT);
	temp->soLuong = a->soLuong;
	temp->tenVT = a->tenVT;
	temp->tonKho = a->tonKho;
	temp->total = a->total;

	b->donGiaTB = temp->donGiaTB;
	b->donVi = temp->donVi;
	strcpy_s(b->maVT, temp->maVT);
	b->soLuong = temp->soLuong;
	b->tenVT = temp->tenVT;
	b->tonKho = temp->tonKho;
	b->total = temp->total;

	delete temp;
}

void DSCTHoaDon::SwapDataDt(PTRTop& a, PTRTop& b)
{
	PTRTop temp = new TopDT;
	this->CopyDataDT(a, temp);
	this->CopyDataDT(b, a);
	this->CopyDataDT(temp, b);
	delete temp;
}

PTRTop DSCTHoaDon::DivideListDT(PTRTop& a, PTRTop& b)
{
	float truc = b->total;

	PTRTop i = a->left;

	for (PTRTop j = a; j != b; j = j->right)
	{
		if (j->total >= truc)
		{
			if (i == NULL)
				i = a;
			else
				i = i->right;
			SwapDataDt(i, j);
		}
	}
	if (i == NULL)
		i = a;
	else
		i = i->right;
	SwapDataDt(i, b);
	return i;
}

PTRTop DSCTHoaDon::LastAllRank(PTRTop topList)
{
	while (topList != NULL && topList->right != NULL)
		topList = topList->right;
	return topList;
}

void DSCTHoaDon::QuickSortDT(PTRTop& a, PTRTop& b)
{
	if (b != NULL && a != b && a != b->right)
	{
		PTRTop p = DivideListDT(a, b);
		QuickSortDT(a, p->left);
		QuickSortDT(p->right, b);
	}
}

PTRTop DSCTHoaDon::TinhTopDoanhThu(Ngay start, Ngay end)
{
	PTRTop topList = NULL;
	rankAmount = 0;
	for (int dsNV = 0; dsNV < 3; dsNV++)
	{
		MangConTro dsTemp;
		if (dsNV == 0)
			dsTemp.SetDanhSachNhanVien(con->getDanhSachNhanVien());
		else if (dsNV == 1)
			dsTemp.SetDanhSachNhanVien(con->getDanhSachNhanVienPhu());
		else
			dsTemp.SetDanhSachNhanVien(con->getDanhSachNhanVienPhu2());
		for (int i = 0; i < dsTemp.GetDanhSachNhanVien().soLuongNhanVien; i++)
		{
			for (PTRHoaDon p = dsTemp.GetDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first; p != NULL; p = p->next)
			{
				if (DateCmp(end, p->infoHoaDon.ngayNhapHoaDon) >= 0 && DateCmp(p->infoHoaDon.ngayNhapHoaDon, start) >= 0 && stricmp(p->infoHoaDon.loai,"X") == 0)
					for (int j = 0; j < p->PTRChiTietHoaDon->soLuongVatTu; j++)
					{
						int newVT = 0;
						if (topList == NULL)
						{
							topList = new TopDT;
							PTRTop temp = new TopDT;
							PTRVatTu tempVT = dataVatTu.Search(p->PTRChiTietHoaDon->nodesChiTiet[j].maVT);
							if (tempVT == NULL)
								tempVT = dataVatTuCu.Search(p->PTRChiTietHoaDon->nodesChiTiet[j].maVT);
							temp->donVi = tempVT->info.donViTinh;
							strcpy_s(temp->maVT, tempVT->maVT);
							temp->donGiaTB = p->PTRChiTietHoaDon->nodesChiTiet[j].donGia;
							temp->soLuong = p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong;
							temp->tenVT = tempVT->info.tenVT;
							temp->tonKho = tempVT->info.soLuongTon;
							temp->total = p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong * p->PTRChiTietHoaDon->nodesChiTiet[j].donGia * (1 + p->PTRChiTietHoaDon->nodesChiTiet[j].VAT / 100);
							*topList = *temp;
							newVT = 1;
							topList->right = NULL;
							topList->left = NULL;
						}
						else if (topList != NULL)
							for (PTRTop t = topList; t != NULL; t = t->right)
							{
								if (stricmp(p->PTRChiTietHoaDon->nodesChiTiet[j].maVT, t->maVT) == 0)
								{
									t->donGiaTB = (t->donGiaTB * t->soLuong + p->PTRChiTietHoaDon->nodesChiTiet[j].donGia * p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong) / (t->soLuong + p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong);
									t->soLuong += p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong;
									t->total += p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong * p->PTRChiTietHoaDon->nodesChiTiet[j].donGia * (1 + p->PTRChiTietHoaDon->nodesChiTiet[j].VAT / 100);
									newVT = 1;
									break;
								}
							}
						if (newVT == 0)
						{
							PTRTop temp = new TopDT;
							PTRVatTu tempVT = dataVatTu.Search(p->PTRChiTietHoaDon->nodesChiTiet[j].maVT);
							if (tempVT == NULL)
								tempVT = dataVatTuCu.Search(p->PTRChiTietHoaDon->nodesChiTiet[j].maVT);
							temp->donVi = tempVT->info.donViTinh;
							strcpy_s(temp->maVT, tempVT->maVT);
							temp->donGiaTB = p->PTRChiTietHoaDon->nodesChiTiet[j].donGia;
							temp->soLuong = p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong;
							temp->tenVT = tempVT->info.tenVT;
							temp->tonKho = tempVT->info.soLuongTon;
							temp->total = p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong * p->PTRChiTietHoaDon->nodesChiTiet[j].donGia * (1 + p->PTRChiTietHoaDon->nodesChiTiet[j].VAT / 100);
							PTRTop t = new TopDT;
							*t = *temp;
							t->right = topList;
							t->left = NULL;
							topList->left = t;
							topList = t;
						}
					}
			}
		}
	}
	this->lastRank = LastAllRank(topList);
	QuickSortDT(topList, this->lastRank);
	for (PTRTop p = topList; p != NULL; p = p->right)
	{
		rankAmount++;
		if (p->right != NULL && rankAmount >= 10)
		{
			if (p->total != p->left->total)
			{
				if (rankAmount == 10)
					this->lastListRank = p;
				this->lastRank = p->left;
				break;
			}
			else
			{
				if(rankAmount == 10)
					this->lastListRank = p;
			}
		}
		else
		{
			this->lastRank = p;
			if (rankAmount < 10)
				this->lastListRank = p;
		}
	}
	return topList;
}

void DSCTHoaDon::DoanhThu(Ngay startDay, Ngay endDay)
{
	if (keypress == INS)
	{
		char choice[2][15] = { "Tinh Doanh Thu", "Thoat" };
		if (!CheckDate(startDay) || !CheckDate(startDay) || DateCmp(startDay, endDay) == 1)
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
				strcpy_s(thongBaoSai[5], "Ngay bat dau sai");
			else if (!CheckDate(endDay))
				strcpy_s(thongBaoSai[5], "Ngay ket thuc Sai");
			else if (DateCmp(startDay, endDay) == 1)
				strcpy_s(thongBaoSai[5], "Ngay ket thuc phai lon hon ngay bat dau Sai");
			int i = DrawNoti(thongBaoSai, choiceSai, 2);
			if (i == 0)
			{
				this->DrawFormDoanhThu();
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
				keypress = 0;
				return;
			}
			else if (i == 1 || i == 2)
			{
				ClearInsideBox();
				keypress = ESC;
				return;
			}
		}
		this->firstListRank = this->firstRank = this->currRank = this->TinhTopDoanhThu(startDay, endDay);
		int stop = 0;

		if (this->firstListRank != NULL)
		{
			this->DrawDoanhThu();
			keypress = 0;
			while (true)
			{
				this->TraverseDT();
				this->WriteDT();
				if (this->ExitMenu(keypress))
				{
					this->DrawFormDoanhThu();
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
					keypress = 0;
					break;
				}
				keypress = _getch();
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
			this->DrawFormDoanhThu();
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
			keypress = 0;
		}
	}
}

void DSCTHoaDon::MainDoanhThu(ConnectFile * connect)
{
	char choice[2][15] = { "Tinh Doanh Thu", "Thoat" };
	con = connect;
	dataVatTu.SetPTRVatTu(con->getVatTu());
	dataVatTuCu.SetPTRVatTu(con->getVatTuPhu());
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
	this->DrawFormDoanhThu();
	this->DrawFormDoanhThu();
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
	this->firstListRank = new TopDT;
	this->firstRank = new TopDT;
	this->lastListRank = new TopDT;
	this->lastRank = new TopDT;
	this->currRank = new TopDT;
	while (true)
	{
		this->InputAddDT(startDay, endDay);
		this->ChangeInputDT();
		this->DoanhThu(startDay, endDay);
		if (this->ExitMenu(keypress))
		{
			keypress = 0;
			break;
		}
	}
}
