#include "DSNhanVien.h"

int DSNhanVien::vitri_endList()
{
	int run;
	int t = viTriFirst + 10;
	for (run = viTriFirst; run < t && run < this->GetDanhSachNhanVien().soLuongNhanVien; run++); //run -> next != NULL de ko bi chay lo them dong run = run -> next
	return --run;
}

void DSNhanVien::travese() {
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
					viTriCurrent = this->vitri_endList();
				}
			}
		}
		else if (keypress == KEY_DOWN) {
			if (viTriCurrent != this->vitri_endList()) {
				viTriCurrent++;
			}
			else if (viTriCurrent == this->vitri_endList()) {
				if (this->vitri_endList() != this->GetDanhSachNhanVien().soLuongNhanVien - 1) {
					viTriFirst = this->vitri_endList() + 1;
					viTriCurrent = viTriFirst;
				}
			}
		}
		else if (keypress == KEY_RIGHT) {
			if (this->vitri_endList() != this->GetDanhSachNhanVien().soLuongNhanVien - 1) {
				viTriFirst = this->vitri_endList() + 1;
				if (viTriCurrent + 10 <= this->GetDanhSachNhanVien().soLuongNhanVien - 1)
					viTriCurrent += 10;
				else viTriCurrent = vitri_endList();
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

//int DSNhanVien::getLastRow()
//{
//	int listAmount;
//	if ((this->page + 1) * 10 > this->GetDanhSachNhanVien().soLuongNhanVien)
//		listAmount = this->GetDanhSachNhanVien().soLuongNhanVien - this->page * 10;
//	else
//		listAmount = 10;
//	if (this->GetDanhSachNhanVien().soLuongNhanVien == 0)
//		return 0;
//	return listAmount;
//}

void DSNhanVien::DrawNhanVien()
{
	ClearInsideBox();
	TextColor(0);
	textbk(15);
	DrawBorderList(35, 15, 11, 5, BOXNVWIDE, 1);
	DrawTitle(NHANVIENTITLE, 40, 6);
	TextColor(10);
	textbk(15);
	int i = 0;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("STT", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("MA NHAN VIEN", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("HO", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("TEN", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("PHAI", BOXNVWIDE - 1);
	TextColor(0);
	textbk(15);
}

void DSNhanVien::DrawFormThemNhanVien()
{
	ClearInsideBox();
	int i = 0;
	gotoXY(36, 10);
	cout << "Ma Nhan Vien";
	gotoXY(56, 10);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Ho";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Ten";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Phai";
	gotoXY(56, 10 + i);
	cout << ":";
	DrawBorder(60, 9 + i, 4, 2);
	gotoXY(66, 10 + i);
	cout << "Nam";
	DrawBorder(75, 9 + i, 4, 2);
	gotoXY(81, 10 + i);
	cout << "Nu";
}

void DSNhanVien::WriteNhanVien()
{
	//int listAmount = 0;
	//int listStart = this->page * 10;
	//if ((this->page + 1) * 10 > this->GetDanhSachNhanVien().soLuongNhanVien)
	//	listAmount = this->GetDanhSachNhanVien().soLuongNhanVien - this->page * 10;
	//else
	//	listAmount = 10;
	/*int listStart = viTriFirst;*/
	int listStart = viTriFirst;
	int listAmount = this->vitri_endList();
	if (!TrongNhanVien())
	{
		for (int i = listStart; i <= listAmount; i++)
		{
			if (i == viTriCurrent)
			{
				TextColor(4);
				textbk(15);
			}
			int j = 0;
			gotoXY(36 + j, 18 + (i - listStart) * 2);
			cout << CenterTextInSpace(to_string(i + 1), BOXNVWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + (i - listStart) * 2);
			cout << CenterTextInSpace(this->GetDanhSachNhanVien().nodes[i]->maNV, BOXNVWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + (i - listStart) * 2);
			cout << CenterTextInSpace(this->GetDanhSachNhanVien().nodes[i]->ho, BOXNVWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + (i - listStart) * 2);
			cout << CenterTextInSpace(this->GetDanhSachNhanVien().nodes[i]->ten, BOXNVWIDE - 1);
			j += 25;
			gotoXY(36 + j, 18 + (i - listStart) * 2);
			cout << CenterTextInSpace(getSex(*this->GetDanhSachNhanVien().nodes[i]), BOXNVWIDE - 1);
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
				int j = 0;
				gotoXY(36 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(36 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(36 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(36 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
				j += 25;
				gotoXY(36 + j, 18 + (i - listStart) * 2);
				cout << CenterTextInSpace("", BOXNVWIDE - 1);
			}
		}
	}
}

//void DSNhanVien::WriteNhanVien(int first, int last, int current)
//{
//	//int listAmount = 0;
//	//int listStart = this->page * 10;
//	//if ((this->page + 1) * 10 > this->GetDanhSachNhanVien().soLuongNhanVien)
//	//	listAmount = this->GetDanhSachNhanVien().soLuongNhanVien - this->page * 10;
//	//else
//	//	listAmount = 10;
//	/*int listStart = viTriFirst;*/
//	int listStart = first;
//	int listAmount = last;
//	if (!TrongNhanVien())
//	{
//		for (int i = listStart; i < listAmount; i++)
//		{
//			int j = 0;
//			gotoXY(36 + j, 18 + i * 2);
//			cout << CenterTextInSpace(to_string(listStart + i + 1), BOXNVWIDE - 1);
//			j += 25;
//			gotoXY(36 + j, 18 + i * 2);
//			cout << CenterTextInSpace(this->GetDanhSachNhanVien().nodes[listStart + i]->maNV, BOXNVWIDE - 1);
//			j += 25;
//			gotoXY(36 + j, 18 + i * 2);
//			cout << CenterTextInSpace(this->GetDanhSachNhanVien().nodes[listStart + i]->ho, BOXNVWIDE - 1);
//			j += 25;
//			gotoXY(36 + j, 18 + i * 2);
//			cout << CenterTextInSpace(this->GetDanhSachNhanVien().nodes[listStart + i]->ten, BOXNVWIDE - 1);
//			j += 25;
//			gotoXY(36 + j, 18 + i * 2);
//			cout << CenterTextInSpace(getSex(*this->GetDanhSachNhanVien().nodes[listStart + i]), BOXNVWIDE - 1);
//		}
//	}
//}

void DSNhanVien::ThemNhanVien()
{
	NhanVien addNV;
	addNV.phai = 1;
	addNV.PTRHoaDonNhanVien.first = addNV.PTRHoaDonNhanVien.last = NULL;
	if (keypress == INS)
	{
		char choice[2][15] = { "Them","Thoat" };
		this->DrawFormThemNhanVien();
		DrawTitle(THEMNHANVIEN, 55, 3);
		DrawOptionChoice(choice, 80, 30, 2, 3);
		this->infoAddSelect = themMa;
		gotoXY(62, 25);
		cout << "X";
		DrawMenu(THEMNHANVIEN);
		while (true)
		{
			this->InputAddMode(addNV);
			this->ChangeInput();
			if (this->ExitMenu(keypress) || keypress == INS)
			{
				if (keypress == INS)
				{
					char choiceSure[3][15] = { "Them","Huy","Thoat" };
					char thongBaoThem[10][78] =
					{
						"",
						"",
						"Ban muon them nhan vien ?",
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
						int k = CheckNhanVien(addNV);
						if (k == 1)
						{
							MangConTro dsCu;
							dsCu.SetDanhSachNhanVien(con->getDanhSachNhanVienPhu());
							if (dsCu.TimNhanVien(addNV.maNV) >= 0)
							{
								int identical = this->ThongBaoTrung();
								if (identical == 0)
								{
									this->ExitOption(2, choice, 2, addNV);
									DrawTitle(THEMNHANVIEN, 55, 3);
								}
								else
								{
									this->ExitOption(1, choice, 2, addNV);
									break;
								}
							}
							else if (this->ThemNhanVienTheoTen(addNV) == -1)
							{
								int identical = this->ThongBaoTrung();
								if (identical == 0)
								{
									this->ExitOption(2, choice, 2, addNV);
									DrawTitle(THEMNHANVIEN, 55, 3);
								}
								else
								{
									this->ExitOption(1, choice, 2, addNV);
									break;
								}
							}
							else
							{
								this->ExitOption(1, choice, 2, addNV);
								break;
							}
						}
						else
						{
							this->ExitOption(2, choice, 2, addNV);
							DrawTitle(THEMNHANVIEN, 55, 3);
							char thongBaoSai[10][78] =
							{
								"",
								"",
								"Nhan vien cua ban vua them vao sai",
								"",
								"",
								"",
								"",
								"",
								"",
								""
							};
							if (k == 2)
								strcpy(thongBaoSai[5], "Note: Ho nhan vien sai,ho nhan vien chi co ky tu, khong duoc rong");
							else if (k == 3)
								strcpy(thongBaoSai[5], "Note: Ten nhan vien sai,ten nhan vien chi co ky tu, khong duoc rong");
							else if (k == 4)
								strcpy(thongBaoSai[5], "Note: Ma nhan vien sai,ma nhan vien chi co ky tu va so, khong duoc rong");
							else if (k == 5)
								strcpy(thongBaoSai[5], "Note: Phai nhan vien sai,phai nhan vien chi la nam hoac nu");
							char choiceSai[2][15] = { "Sua lai","Thoat" };
							int j = DrawNoti(thongBaoSai, choiceSai, 2);
							if (j == 0)
							{
								this->ExitOption(2, choice, 2, addNV);
								DrawTitle(THEMNHANVIEN, 55, 3);
								continue;
							}
							else if(j == 1 || j == 2)
							{
								this->ExitOption(1, choice, 2, addNV);
								break;
							}
						}
					}
					else if (i == 2 || i == 3)
					{
						this->ExitOption(1, choice, 2, addNV);
						break;
					}
					else if (i == 1)
					{
						this->ExitOption(2, choice, 2, addNV);
						DrawTitle(THEMNHANVIEN, 55, 3);
						continue;
					}
				}
				else
				{
					this->ExitOption(1, choice, 2, addNV);
					break;
				}
			}
		}
	}
}

int DSNhanVien::ThongBaoTrung()
{
	char choiceTrung[2][15] = { "Sua","Thoat" };
	char thongBaoTrung[10][78] =
	{
		"",
		"",
		"",
		"",
		"Ma nhan vien bi trung",
		"",
		"",
		"",
		"",
		"",
	};
	int i = DrawNoti(thongBaoTrung, choiceTrung, 2);
	return i;
}

void DSNhanVien::ExitOption(int choice,char choiceArr[][15],int soOption, NhanVien nhanVien)
{
	//Them : 1 la thoat, 2 la o lai
	//Sua : 2 la tro ve man hinh truoc, 1 khong dung;	
	if (choice == 1)
	{
		ClearInsideBox();
		this->DrawNhanVien();
		this->WriteNhanVien();
		travese();
		keypress = 0;
	}
	else if (choice == 2)
	{
		ClearInsideBox();
		this->DrawFormThemNhanVien();
		DrawOptionChoice(choiceArr, 80, 30, soOption, 3);
		gotoXY(60, 10);
		cout << nhanVien.maNV;
		gotoXY(60, 15);
		cout << nhanVien.ho;
		gotoXY(60, 20);
		cout << nhanVien.ten;
		this->infoAddSelect = themMa;

		if (nhanVien.phai == 1)
			gotoXY(62, 25);
		else
			gotoXY(77, 25);
		cout << "X";
	}
}

void DSNhanVien::InputAddMode(NhanVien &newNhanVien)
{
	switch (this->infoAddSelect)
	{
	case DSNhanVien::themMa:
		InputInfo(newNhanVien.maNV, 30, 60, 10, keypress, 1);
		break;
	case DSNhanVien::themHo:
		InputInfo(newNhanVien.ho, 30, 60, 15, keypress, 3);
		break;
	case DSNhanVien::themTen:
		InputInfo(newNhanVien.ten, 30, 60, 20, keypress, 3);
		break;
	case DSNhanVien::themPhai:
		ChooseSex(newNhanVien.phai);
		break;
	case DSNhanVien::chonOption:
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
	default:
		break;
	}
}

void DSNhanVien::InputFixMode(NhanVien &info)
{
	switch (this->infoAddSelect)
	{
	case DSNhanVien::themMa:
		InputInfo(info.maNV, 30, 60, 10, keypress, 1);
		break;
	case DSNhanVien::themHo:
		InputInfo(info.ho, 30, 60, 15, keypress, 3);
		break;
	case DSNhanVien::themTen:
		InputInfo(info.ten, 30, 60, 20, keypress, 3);
		break;
	case DSNhanVien::themPhai:
		ChooseSex(info.phai);
		break;
	case DSNhanVien::chonOption:
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

void DSNhanVien::ChangeInput()
{
	if (keypress == KEY_UP || keypress == KEY_DOWN)
	{
		//keypress = _getch();
		switch (keypress)
		{
		case KEY_UP:
		{
			switch (this->infoAddSelect)
			{
			case DSNhanVien::themMa:
				this->infoAddSelect = chonOption;
				break;
			case DSNhanVien::themHo:
				this->infoAddSelect = themMa;
				break;
			case DSNhanVien::themTen:
				this->infoAddSelect = themHo;
				break;
			case DSNhanVien::themPhai:
				this->infoAddSelect = themTen;
				break;
			case DSNhanVien::chonOption:
				this->infoAddSelect = themPhai;
				break;
			}
			break;
		}
			
		case KEY_DOWN:
		{
			switch (infoAddSelect)
			{
			case DSNhanVien::themMa:
				this->infoAddSelect = themHo;
				break;
			case DSNhanVien::themHo:
				this->infoAddSelect = themTen;
				break;
			case DSNhanVien::themTen:
				this->infoAddSelect = themPhai;
				break;
			case DSNhanVien::themPhai:
				this->infoAddSelect = chonOption;
				break;
			case DSNhanVien::chonOption:
				this->infoAddSelect = themMa;
				break;
			}
			break;
		}
		}
	}
}

void DSNhanVien::ChooseSex(int &sex)
{
	if (sex == 1)
		gotoXY(63, 25);
	else
		gotoXY(78, 25);
	while (true)
	{
		keypress = _getch();
		if (keypress == 224)
			keypress = _getch();
		if (keypress == KEY_UP || keypress == KEY_DOWN || keypress == INS)
			return;
		else if (keypress == ENTER || keypress == ESC)
			return;
		else if (keypress == KEY_LEFT)
		{
			if (sex == 1)
			{
				gotoXY(62, 25);
				cout << " ";
				gotoXY(77, 25);
				cout << "X";
				sex = 0;
			}
			else
			{
				gotoXY(77, 25);
				cout << " ";
				gotoXY(62, 25);
				cout << "X";
				sex = 1;
			}
		}
		else if (keypress == KEY_RIGHT)
		{
			if (sex == 1)
			{
				gotoXY(62, 25);
				cout << " ";
				gotoXY(77, 25);
				cout << "X";
				sex = 0;
			}
			else
			{
				gotoXY(77, 25);
				cout << " ";
				gotoXY(62, 25);
				cout << "X";
				sex = 1;
			}
		}
	}
}

void DSNhanVien::SuaNhanVien()
{
	infoAddSelect = themMa;
	char choice[2][15] = { "Sua" , "Thoat" };
	char choiceBack[3][15] = { "Sua","Xem Hoa Don","Thoat" };
	this->ExitOption(2, choice, 2, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
	DrawTitle(SUANHANVIEN, 55, 3);
	NhanVien temp;
	temp.PTRHoaDonNhanVien.first = temp.PTRHoaDonNhanVien.last = NULL;
	temp = *this->GetDanhSachNhanVien().nodes[viTriCurrent];
	string tempMaNV = temp.maNV;
	DrawMenu(SUANHANVIEN);
	while (true)
	{
		this->InputFixMode(temp);
		this->ChangeInput();
		if (this->ExitMenu(keypress) || keypress == INS)
		{
			if (keypress == INS)
			{
				char choiceSua[3][15] = { "Sua","Huy","Thoat" };
				char thongBaoSua[10][78] =
				{
					"",
					"",
					"Ban co chac chan muon sua nhan vien ?",
					"",
					"",
					"",
					"",
					"Note: Thong tin se duoc tu dong sua in hoa, khoang trang thich hop",
					"",
					"",
				};
				int i = DrawNoti(thongBaoSua, choiceSua, 3);
				if (i == 0)
				{//
					int k = CheckNhanVien(temp);
					if (k == 1)
					{
						MangConTro dsCu;
						dsCu.SetDanhSachNhanVien(con->getDanhSachNhanVienPhu());
						if (dsCu.TimNhanVien(temp.maNV) >= 0)
						{
							int identical = this->ThongBaoTrung();
							if (identical == 0)
							{
								this->ExitOption(2, choice, 2, temp);
								DrawTitle(SUANHANVIEN, 55, 3);
							}
							else
							{
								this->ExitOption(1, choice, 2, temp);
								break;
							}
						}
						else if (this->UpdateNhanVienViTiX(viTriCurrent, temp) == -1)
						{
							int identical = this->ThongBaoTrung();
							if (identical == 0)
							{
								this->ExitOption(2, choice, 2, temp);
								DrawTitle(SUANHANVIEN, 55, 3);
							}
							else
							{
								this->ExitOption(2, choiceBack, 3, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
								break;
							}
						}
						else
						{
							MangConTro dsCu2;
							dsCu2.SetDanhSachNhanVien(con->getDanhSachNhanVienPhu2());
							int idX = dsCu2.TimNhanVien(tempMaNV);
							if (idX >= 0)
							{
								dsCu2.UpdateNhanVienViTiX(idX, temp);
								con->setDanhSachSinhVienPhu2(dsCu2.GetDanhSachNhanVien());
							}
							this->ExitOption(2, choiceBack, 3, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
							break;
						}
						//this->FixNhanVienViTiX(viTriCurrent, temp);
						//this->ExitOption(2, choiceBack, 3, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
						//break;
					}
					else
					{
						ClearInsideBox();
						this->ExitOption(2, choice, 2, temp);
						DrawTitle(SUANHANVIEN, 55, 3);
						char thongBaoSai[10][78] =
						{
							"",
							"",
							"Nhan vien cua ban sua vao sai",
							"",
							"",
							"",
							"",
							"",
							"",
							""
						};
						if (k == 2)
							strcpy(thongBaoSai[5], "Note: Ho nhan vien sai,ho nhan vien chi co ky tu, khong duoc rong");
						else if (k == 3)
							strcpy(thongBaoSai[5], "Note: Ten nhan vien sai,ten nhan vien chi co ky tu, khong duoc rong");
						else if (k == 4)
							strcpy(thongBaoSai[5], "Note: Ma nhan vien sai,ma nhan vien chi co ky tu va so, khong duoc rong");
						else if (k == 5)
							strcpy(thongBaoSai[5], "Note: Phai nhan vien sai,phai nhan vien chi la nam hoac nu");
						char choiceSai[2][15] = { "Sua lai","Thoat" };
						int j = DrawNoti(thongBaoSai, choiceSai, 2);
						if (j == 0)
						{
							this->ExitOption(2, choice, 2, temp);
							DrawTitle(SUANHANVIEN, 55, 3);
							continue;
						}
						else if (j == 1 || j == 2)
						{
							this->ExitOption(2, choiceBack, 3, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
							break;
						}
					}
				}
				else if (i == 2 || i == 3)
				{
					this->ExitOption(2, choiceBack, 3, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
					break;
				}
				else if (i == 1)
				{
					this->ExitOption(2, choice, 2, temp);
					DrawTitle(SUANHANVIEN, 55, 3);
					continue;
				}
			}
			else
			{
				this->ExitOption(2, choiceBack, 3, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
				keypress = 0;
				break;
			}
		}
	}
}

void DSNhanVien::SelectNhanVien()
{
	if (!this->TrongNhanVien())
		if (keypress == ENTER)
		{
			this->DrawFormThemNhanVien();
			DrawTitle(CHITIETNHANVIEN, 50, 3);
			TextColor(8);
			textbk(15);
			gotoXY(60, 10);
			cout << this->GetDanhSachNhanVien().nodes[viTriCurrent]->maNV;
			gotoXY(60, 15);
			cout << this->GetDanhSachNhanVien().nodes[viTriCurrent]->ho;
			gotoXY(60, 20);
			cout << this->GetDanhSachNhanVien().nodes[viTriCurrent]->ten;
			gotoXY(60, 25);
			if (this->GetDanhSachNhanVien().nodes[viTriCurrent]->phai == 1)
				gotoXY(62, 25);
			else
				gotoXY(77, 25);
			cout << "X";;
			textbk(15);
			char choice[3][15] = { "Sua","Lap Hoa Don","Thoat" };
			DrawOptionChoice(choice, 80, 30, 3, 3);
			DrawMenu(CHITIETNHANVIEN);
			while (true)
			{
				int i = ChooseOption(choice, 80, 30, 3, 3, 1);
				if (i == 2 || i == 3)
					keypress = ESC;
				else if (i == 0)
				{
					this->SuaNhanVien();
					DrawTitle(CHITIETNHANVIEN, 50, 3);
					DrawMenu(CHITIETNHANVIEN);
					gotoXY(110, 30);
				}
				else
				{
					this->HoaDon();
					ExitOption(2, choice, 3, *this->GetDanhSachNhanVien().nodes[viTriCurrent]);
					DrawTitle(CHITIETNHANVIEN, 50, 3);
					DrawMenu(CHITIETNHANVIEN);
				}
				if (this->ExitMenu(keypress))
				{
					ClearInsideBox();
					DrawNhanVien();
					WriteNhanVien();
					break;
				}
				keypress = _getch();
			}
		}
}

void DSNhanVien::XoaNhanVien()
{
	if (keypress == DEL)
	{
		char choiceXoa[2][15] = { "Xoa","Huy" };
		char thongBaoXoa[10][78] =
		{
			"",
			"",
			"Ban co chac chan muon xoa nhan vien ?",
			"",
			"",
			"",
			"",
			"Note: Thong tin bi xoa bao gom ca hoa don, chi tiet hoa don",
			"",
			"",
		};
		int i = DrawNoti(thongBaoXoa, choiceXoa, 2);
		if (i == 0)
		{
			MangConTro dsXoa;
			dsXoa.SetDanhSachNhanVien(con->getDanhSachNhanVienPhu());
			MangConTro dsNVphu2;
			dsNVphu2.SetDanhSachNhanVien(con->getDanhSachNhanVienPhu2());
			NhanVien temp = *this->GetDanhSachNhanVien().nodes[viTriCurrent];
			int idNV = dsNVphu2.TimNhanVien(temp.maNV);
			if (idNV >= 0)
			{
				temp.PTRHoaDonNhanVien.last->next = NULL;
				if (temp.PTRHoaDonNhanVien.first != NULL)
				{
					temp.PTRHoaDonNhanVien.last->next = dsNVphu2.GetDanhSachNhanVien().nodes[idNV]->PTRHoaDonNhanVien.first;
					temp.PTRHoaDonNhanVien.last = dsNVphu2.GetDanhSachNhanVien().nodes[idNV]->PTRHoaDonNhanVien.last;
				}
			}
			int idThem = dsXoa.TimViTriThichHopX(temp.ho, temp.ten);
			dsXoa.ThemNhanVienVaoX(temp, idThem);
			dsNVphu2.XoaNhanVienViTiX(idNV);
			con->setDanhSachSinhVienPhu2(dsNVphu2.GetDanhSachNhanVien());
			con->setDanhSachSinhVienPhu(dsXoa.GetDanhSachNhanVien());
			XoaNhanVienViTiX(viTriCurrent);
			if (viTriCurrent == viTriFirst && viTriFirst > 0)
			{
				viTriFirst -= 10;
				viTriCurrent = this->vitri_endList();
			}
			if (viTriCurrent - 1 == vitri_endList() && viTriCurrent != viTriFirst)
				viTriCurrent--;
			ClearInsideBox();
			DrawNhanVien();
			this->WriteNhanVien();
		}
		else
		{
			ClearInsideBox();
			DrawNhanVien();
			this->WriteNhanVien();
		}
	}
}

void DSNhanVien::HoaDon()
{
	con->setDanhSachSinhVien(this->GetDanhSachNhanVien());
	DSHoaDon dsHD;
	//dsHD.SetListHoaDon(this->GetDanhSachNhanVien().nodes[viTriCurrent]->PTRHoaDonNhanVien);
	dsHD.MainHD(con, viTriCurrent);
	//this->SetDanhSachNhanVien(con->getDanhSachNhanVien());
}

int DSNhanVien::ExitMenu(int keyhit)
{
	if (keyhit == ESC)
		return 1;
	return 0;
}



DSNhanVien::DSNhanVien()
{
	this->DrawNhanVien();
	this->WriteNhanVien();
	viTriFirst = viTriCurrent = 0;
	this->keypress = 0;
	con = new ConnectFile();
	this->SetDanhSachNhanVien(con->getDanhSachNhanVien());
	while (true)
	{
		if (this->ExitMenu(keypress))
			break;
		this->travese();
		this->WriteNhanVien();
		this->ThemNhanVien();
		this->SelectNhanVien();
		this->XoaNhanVien();
		DrawMenu(NHANVIENTITLE);
		keypress = _getch();
	}
	con->setDanhSachSinhVien(this->GetDanhSachNhanVien());
	con->~ConnectFile();
}


DSNhanVien::~DSNhanVien()
{
}
