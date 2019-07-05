#include "DSVatTu.h"



DSVatTu::DSVatTu()
{
	keypress = 0;
	sttNum = 1;
	ClearInsideBox();
	this->DrawVatTu();
}


DSVatTu::~DSVatTu()
{
}

void DSVatTu::SetViTriEndList()
{
	if (this->GetSoLoaiVatTu() <= 10)
	{
		viTriEndList = this->GetLastListVatTu();
		return;
	}
	int i = 0;
	for (viTriEndList = viTriFirst; viTriEndList != GetLastListVatTu(); viTriEndList = viTriEndList->right)
	{
		i++;
		if (i > 9)
			break;
	}
}

void DSVatTu::Travese()
{
	if (keypress == 224)
	{
		keypress = _getch();
		if (keypress == KEY_UP) {
			if (viTriCurrent != this->GetFirstListVatTu())
				viTriCurrent = viTriCurrent->left;
			if (viTriCurrent == viTriFirst && viTriFirst != this->GetFirstListVatTu())
			{
				viTriFirst = viTriFirst->left;
				viTriEndList = viTriEndList->left;
				sttNum--;
			}
		}
		else if (keypress == KEY_DOWN) {
			if (viTriCurrent != this->viTriEndList)
				viTriCurrent = viTriCurrent->right;
			if (viTriCurrent == viTriEndList && viTriEndList != this->GetLastListVatTu())
			{
				viTriFirst = viTriFirst->right;
				viTriEndList = viTriEndList->right;
				sttNum++;
			}
		}
	}
}

void DSVatTu::DrawVatTu()
{
	ClearInsideBox();
	TextColor(0);
	textbk(15);
	DrawBorderList(35, 15, 11, 5, BOXNVWIDE, 1);
	DrawTitle(VATTUTITLE, 50, 7);
	DrawMenu(VATTUTITLE);
	TextColor(10);
	textbk(15);
	int i = 0;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("STT", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("MA VAT TU", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("TEN VAT TU", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("SO LUONG TON", BOXNVWIDE - 1);
	i += 25;
	gotoXY(36 + i, 16);
	cout << CenterTextInSpace("DON VI TINH", BOXNVWIDE - 1);
	TextColor(0);
	textbk(15);
}

void DSVatTu::DrawFormVatTu()
{
	ClearInsideBox();
	int i = 0;
	gotoXY(36, 10);
	cout << "Ma Vat Tu";
	gotoXY(56, 10);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Ten Vat Tu";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "So Luong ton";
	gotoXY(56, 10 + i);
	cout << ":";
	i += 5;
	gotoXY(36, 10 + i);
	cout << "Don Vi Tinh";
	gotoXY(56, 10 + i);
	cout << ":";
}

void DSVatTu::WriteVatTu()
{
	int currNum = 0;
	for (ListVatTu temp = viTriFirst; temp != viTriEndList->right; temp = temp->right)
	{
		if (temp == viTriCurrent)
		{
			TextColor(4);
			textbk(15);
		}
		int j = 0;
		gotoXY(36 + j, 18 + currNum * 2);
		cout << CenterTextInSpace(to_string(sttNum + currNum), BOXNVWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + currNum * 2);
		cout << CenterTextInSpace(CharToString(temp->maVT), BOXNVWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + currNum * 2);
		cout << CenterTextInSpace(temp->info.tenVT, BOXNVWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + currNum * 2);
		string str = to_string(temp->info.soLuongTon);
		str = DelFloatTrail(str);
		cout << CenterTextInSpace(str, BOXNVWIDE - 1);
		j += 25;
		gotoXY(36 + j, 18 + currNum * 2);
		cout << CenterTextInSpace(temp->info.donViTinh, BOXNVWIDE - 1);
		if (temp == viTriCurrent)
		{
			TextColor(0);
			textbk(15);
		}
		currNum++;
	}
}

void DSVatTu::ThemVatTu()
{
	VatTu newVT;
	newVT.soLuongTon = 0;
	string maVT;
	if (keypress == INS)
	{
		char choice[2][15] = { "Them","Thoat" };
		this->DrawFormVatTu();
		DrawTitle(VATTUTHEM, 60, 3);
		DrawMenu(VATTUTHEM);
		DrawOptionChoice(choice, 80, 30, 2, 3);
		this->infoAdd = themMa;
		while (true)
		{
			this->InputAddMode(newVT, maVT);
			this->ChangeInput();
			char maVatTu[11];
			strcpy_s(maVatTu, maVT.c_str());
			if (this->ExitMenu(keypress) || keypress == INS)
			{
				if (keypress == INS)
				{
					char choiceSure[3][15] = { "Them","Huy","Thoat" };
					char thongBaoThem[10][78] =
					{
						"",
						"",
						"Ban muon them vat tu ?",
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
						int k = CheckVatTu(CreateNodesVT(newVT, maVatTu));
						if (k == 1)
						{
							CayNhiPhan cayPhu;
							cayPhu.SetPTRVatTu(con->getVatTuPhu());
							if (cayPhu.Search(maVatTu) != NULL)
							{
								int identical = this->ThongBaoTrung();
								if (identical == 0)
									this->ExitOption(2, choice, 2, newVT, maVatTu);
								else
								{
									this->ExitOption(1, choice, 2, newVT, maVatTu);
									break;
								}
							}
							else if (this->InsertOrder(newVT, maVatTu) == 0)
							{
								int identical = this->ThongBaoTrung();
								if (identical == 0)
									this->ExitOption(2, choice, 2, newVT, maVatTu);
								else
								{
									this->ExitOption(1, choice, 2, newVT, maVatTu);
									break;
								}
							}
							else
							{
								this->InsertList(newVT, maVatTu);
								viTriFirst = this->GetFirstListVatTu();
								this->SetViTriEndList();
								viTriCurrent = viTriFirst;
								this->ExitOption(1, choice, 2, newVT, maVatTu);
								break;
							}
						}
						else
						{
							ClearInsideBox();
							this->ExitOption(2, choice, 2, newVT, maVatTu);
							char thongBaoSai[10][78] =
							{
								"",
								"",
								"Vat cua ban vua them vao sai",
								"",
								"",
								"",
								"",
								"",
								"",
								""
							};
							if (k == 2)
								strcpy(thongBaoSai[5], "Note: Ma vat tu sai, ma vat tu chi co ky tu hoac so, khong duoc rong");
							else if (k == 3)
								strcpy(thongBaoSai[5], "Note: Ten vat tu sai, ten vat tu chi co ky tu, khong duoc rong");
							else if (k == 4)
								strcpy(thongBaoSai[5], "Note: So luong ton sai, so luong ton chi co so, khong duoc rong");
							else if (k == 5)
								strcpy(thongBaoSai[5], "Note: Don vi tinh sai, don vi tinh chi co ky tu hoac so, khong duoc rong");
							char choiceSai[2][15] = { "Sua lai","Thoat" };
							int j = DrawNoti(thongBaoSai, choiceSai, 2);
							if (j == 0)
							{
								this->ExitOption(2, choice, 2, newVT, maVatTu);
								continue;
							}
							else if (j == 1 || j == 2)
							{
								this->ExitOption(1, choice, 2, newVT, maVatTu);
								break;
							}
						}
					}
					else if (i == 2 || i == 3)
					{
						this->ExitOption(1, choice, 2, newVT, maVatTu);
						break;
					}
					else if (i == 1)
					{
						this->ExitOption(2, choice, 2, newVT, maVatTu);
						continue;
					}
				}
				else
				{
					this->ExitOption(1, choice, 2, newVT, maVatTu);
					break;
				}
			}
		}
	}
}

int DSVatTu::ThongBaoTrung()
{
	char choiceTrung[2][15] = { "Sua","Thoat" };
	char thongBaoTrung[10][78] =
	{
		"",
		"",
		"",
		"",
		"Ma vat tu bi trung",
		"",
		"",
		"",
		"",
		"",
	};
	int i = DrawNoti(thongBaoTrung, choiceTrung, 2);
	return i;
}

void DSVatTu::ExitOption(int choice, char choiceArr[][15], int soOption, VatTu vatTu, char maVT[11])
{
	//Them : 1 la thoat, 2 la o lai
	//Sua : 1 la thoat, 3 la o lai;
	if (choice == 1)
	{
		ClearInsideBox();
		this->DrawVatTu();
		this->WriteVatTu();
		Travese();
		keypress = 0;
	}
	else if (choice == 2)
	{
		ClearInsideBox();
		this->DrawFormVatTu();
		DrawTitle(VATTUTHEM, 60, 3);
		DrawMenu(VATTUTHEM);
		DrawOptionChoice(choiceArr, 80, 30, soOption, 3);
		gotoXY(60, 10);
		cout << maVT;
		gotoXY(60, 15);
		cout << vatTu.tenVT;
		gotoXY(60, 20);
		cout << vatTu.soLuongTon;
		gotoXY(60, 25);
		cout << vatTu.donViTinh;
		this->infoAdd = themMa;
	}
	else if (choice == 3)
	{
		ClearInsideBox();
		this->DrawFormVatTu();
		DrawTitle(VATTUSUA, 60, 3);
		DrawMenu(VATTUSUA);
		DrawOptionChoice(choiceArr, 80, 30, soOption, 3);
		TextColor(8);
		textbk(15);
		gotoXY(60, 10);
		cout << maVT;
		TextColor(0);
		textbk(15);
		gotoXY(60, 15);
		cout << vatTu.tenVT;
		gotoXY(60, 20);
		TextColor(8);
		textbk(15);
		gotoXY(60, 20);
		cout << vatTu.soLuongTon;
		TextColor(0);
		textbk(15);
		gotoXY(60, 25);
		cout << vatTu.donViTinh;
		this->infoAdd = themMa;
	}
}

void DSVatTu::InputAddMode(VatTu & info, string & maVT)
{
	string SoLuong = to_string(info.soLuongTon);
	SoLuong = DelFloatTrail(SoLuong);
	switch (this->infoAdd)
	{
	case DSVatTu::themMa:
		InputInfo(maVT, 10, 60, 10, keypress, 1);
		break;
	case DSVatTu::themTen:
		InputInfo(info.tenVT, 30, 60, 15, keypress, 3);
		break;
	case DSVatTu::themSoLuong:
	{
		InputInfo(SoLuong, 10, 60, 20, keypress, 5);
		if (SoLuong == "")
			break;
		info.soLuongTon = stof(SoLuong);
		break;
	}
	case DSVatTu::themDVT:
		InputInfo(info.donViTinh, 30, 60, 25, keypress, 7);
		break;
	case DSVatTu::chonOption:
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

void DSVatTu::InputFixMode(PTRVatTu & vatTu)
{
	switch (this->infoFix)
	{
	case DSVatTu::suaTen:
		InputInfo(vatTu->info.tenVT, 30, 60, 15, keypress, 3);
		break;
	case DSVatTu::suaDVT:
		InputInfo(vatTu->info.donViTinh, 30, 60, 25, keypress, 7);
		break;
	case DSVatTu::chonOptionFix:
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

void DSVatTu::ChangeInput()
{
	if (keypress == KEY_UP || keypress == KEY_DOWN)
	{
		//keypress = _getch();
		switch (keypress)
		{
		case KEY_UP:
		{
			switch (this->infoAdd)
			{
			case DSVatTu::themMa:
				this->infoAdd = chonOption;
				break;
			case DSVatTu::themTen:
				this->infoAdd = themMa;
				break;
			case DSVatTu::themSoLuong:
				this->infoAdd = themTen;
				break;
			case DSVatTu::themDVT:
				this->infoAdd = themSoLuong;
				break;
			case DSVatTu::chonOption:
				this->infoAdd = themDVT;
				break;
			}
			break;
		}

		case KEY_DOWN:
		{
			switch (this->infoAdd)
			{
			case DSVatTu::themMa:
				this->infoAdd = themTen;
				break;
			case DSVatTu::themTen:
				this->infoAdd = themSoLuong;
				break;
			case DSVatTu::themSoLuong:
				this->infoAdd = themDVT;
				break;
			case DSVatTu::themDVT:
				this->infoAdd = chonOption;
				break;
			case DSVatTu::chonOption:
				this->infoAdd = themMa;
				break;
			}
			break;
		}
		}
	}
}

void DSVatTu::ChangeInputFix()
{
	if (keypress == KEY_UP || keypress == KEY_DOWN)
	{
		//keypress = _getch();
		switch (keypress)
		{
		case KEY_UP:
		{
			switch (this->infoFix)
			{
			case DSVatTu::suaTen:
				this->infoFix = chonOptionFix;
				break;
			case DSVatTu::suaDVT:
				this->infoFix = suaTen;
				break;
			case DSVatTu::chonOptionFix:
				this->infoFix = suaDVT;
				break;
			}
			break;
		}

		case KEY_DOWN:
		{
			switch (this->infoFix)
			{
			case DSVatTu::suaTen:
				this->infoFix = suaDVT;
				break;
			case DSVatTu::suaDVT:
				this->infoFix = chonOptionFix;
				break;
			case DSVatTu::chonOptionFix:
				this->infoFix = suaTen;
				break;
			}
			break;
		}
		}
	}
}

void DSVatTu::XoaVatTu()
{
	if (keypress == DEL)
	{
		char choiceXoa[2][15] = { "Xoa","Huy" };
		char thongBaoXoa[10][78] =
		{
			"",
			"",
			"Ban co chac chan muon xoa vat tu ?",
			"",
			"",
			"",
			"",
			"Note: Ma vat tu nay sau nay co the su dung lai",
			"",
			"",
		};
		int i = DrawNoti(thongBaoXoa, choiceXoa, 2);
		if (i == 0)
		{
			CayNhiPhan cayXoa;
			cayXoa.SetPTRVatTu(con->getVatTuPhu());
			cayXoa.InsertOrder(viTriCurrent->info, viTriCurrent->maVT);
			con->setDanhSachVatTuPhu(cayXoa.GetPTRVatTu());
			this->DeleteNode(viTriCurrent->maVT);
			this->DeleteListNode(viTriCurrent);
			viTriFirst = this->GetFirstListVatTu();
			this->SetViTriEndList();
			viTriCurrent = viTriFirst;
			ClearInsideBox();
			DrawVatTu();
			this->WriteVatTu();
		}
		else
		{
			ClearInsideBox();
			DrawVatTu();
			this->WriteVatTu();
		}
	}
}

void DSVatTu::UpdateVatTu()
{
	if (this->GetFirstListVatTu() != NULL)
	{
		if (keypress == ENTER)
		{
			infoFix = suaTen;
			char choice[2][15] = { "Sua" , "Thoat" };
			PTRVatTu fixPos = Search(this->viTriCurrent->maVT);
			PTRVatTu temp = CreateNodesVT(this->viTriCurrent->info, this->viTriCurrent->maVT);
			if (fixPos == NULL)
			{
				char ok[1][15] = { "OK" };
				char thongBaoKTonTai[10][78] =
				{
					"",
					"",
					"",
					"",
					"Vat tu khong ton tai, danh sach se bi reset",
					"",
					"",
					"",
					"",
					"",
				};
				DrawNoti(thongBaoKTonTai, ok, 1);
				this->ResetList();
				viTriFirst = this->GetFirstListVatTu();
				viTriCurrent = viTriFirst;
				this->SetViTriEndList();
				this->ExitOption(1, choice, 2, temp->info, temp->maVT);
			}
			this->ExitOption(3, choice, 2, temp->info, temp->maVT);
			while (true)
			{
				this->InputFixMode(temp);
				this->ChangeInputFix();
				if (this->ExitMenu(keypress) || keypress == INS)
				{
					if (keypress == INS)
					{
						char choiceSua[3][15] = { "Sua","Huy","Thoat" };
						char thongBaoSua[10][78] =
						{
							"",
							"",
							"Ban co chac chan muon sua vat tu ?",
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
						{
							int k = CheckVatTu(temp);
							if (k == 1)
							{
								this->UpdateNode(fixPos, temp->info);
								this->viTriCurrent->info = temp->info;
								this->ExitOption(1, choice, 2, temp->info, temp->maVT);
								delete temp;
								break;
							}
							else
							{
								ClearInsideBox();
								this->ExitOption(2, choice, 2, temp->info, temp->maVT);
								char thongBaoSai[10][78] =
								{
									"",
									"",
									"Vat cua ban vua them vao sai",
									"",
									"",
									"",
									"",
									"",
									"",
									""
								};
								if (k == 2)
									strcpy(thongBaoSai[5], "Note: Ma vat tu sai, ma vat tu chi co ky tu hoac so, khong duoc rong");
								else if (k == 3)
									strcpy(thongBaoSai[5], "Note: Ten vat tu sai, ten vat tu chi co ky tu, khong duoc rong");
								else if (k == 4)
									strcpy(thongBaoSai[5], "Note: So luong ton sai, so luong ton chi co so, khong duoc rong");
								else if (k == 5)
									strcpy(thongBaoSai[5], "Note: Don vi tinh sai, don vi tinh chi co ky tu hoac so, khong duoc rong");
								char choiceSai[2][15] = { "Sua lai","Thoat" };
								int j = DrawNoti(thongBaoSai, choiceSai, 2);
								if (j == 0)
								{
									this->ExitOption(2, choice, 2, temp->info, temp->maVT);
									continue;
								}
								else if (j == 1 || j == 2)
								{
									this->ExitOption(1, choice, 2, temp->info, temp->maVT);
									delete temp;
									break;
								}
							}
						}
						else if (i == 2 || i == 3)
						{
							this->ExitOption(1, choice, 2, temp->info, temp->maVT);
							delete temp;
							break;
						}
						else if (i == 1)
						{
							this->ExitOption(2, choice, 2, temp->info, temp->maVT);
							continue;
						}
					}
					else
					{
						this->ExitOption(1, choice, 2, temp->info, temp->maVT);
						delete temp;
						break;
					}
				}
			}
		}
	}
}

ListVatTu DSVatTu::SelectVatTu(ConnectFile * connect)
{
	con = connect;
	this->SetPTRVatTu(con->getVatTu());
	viTriFirst = this->GetFirstListVatTu();
	viTriCurrent = viTriFirst;
	this->SetViTriEndList();
	while (true)
	{
		if (this->ExitMenu(keypress))
		{
			return NULL;
			break;
		}
		this->Travese();
		if (keypress == ENTER)
		{
			ClearInsideBox();
			return viTriCurrent;
		}
		this->WriteVatTu();
		keypress = _getch();
	}
}

int DSVatTu::UpdateFromCTHD(ChiTietHoaDon cthd, int loaiHD)
{
	for (int i = 0; i < cthd.soLuongVatTu; i++)
	{
		PTRVatTu temp = Search(cthd.nodesChiTiet[i].maVT);
		if (temp != NULL)
		{
			if (loaiHD == 1) //xuat
			{
				if (temp->info.soLuongTon < cthd.nodesChiTiet[i].soLuong)
					return i;
				else
					temp->info.soLuongTon -= cthd.nodesChiTiet[i].soLuong;
			}
			else if (loaiHD == 2) //nhap
				temp->info.soLuongTon += cthd.nodesChiTiet[i].soLuong;
		}
		else
			return -1;
	}
	return cthd.soLuongVatTu;
}

int DSVatTu::ExitMenu(int keyhit)
{
	if (keyhit == ESC)
		return 1;
	return 0;
}

void DSVatTu::mainVatTU()
{
	con = new ConnectFile();
	this->SetPTRVatTu(con->getVatTu());
	viTriFirst = this->GetFirstListVatTu();
	viTriCurrent = viTriFirst;
	this->SetViTriEndList();
	while (true)
	{
		if (this->ExitMenu(keypress))
			break;
		this->Travese();
		this->WriteVatTu();
		this->ThemVatTu();
		this->UpdateVatTu();
		this->XoaVatTu();
		keypress = _getch();
	}
	con->setDanhSachVatTu(this->GetPTRVatTu());
	con->~ConnectFile();
}
