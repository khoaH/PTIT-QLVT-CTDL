#include "BackEnd.h"



void BackEnd::FixText(string& Text)
{
}

void BackEnd::LineToVatTu(string line, VatTu &newVatTu, char maVT[11])
{
	//ma+ten+sl+dvt+
	string temp;
	int i = 0;
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	FixString(temp, 1);
	if (temp.length() > 10)
	{
		clrscr();
		cout << "Ma vat tu qua dai" << endl;
		exit(0);
	}
	strcpy(maVT, temp.c_str());
	i++;
	temp = "";

	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	FixString(temp, 3);
	newVatTu.tenVT = temp;
	i++;
	temp = "";

	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	FixString(temp, 2);
	newVatTu.soLuongTon = stoi(temp);
	i++;
	temp = "";

	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	FixString(temp, 3);
	newVatTu.donViTinh = temp;
	i++;
	temp = "";

}

void BackEnd::LineToNhanVien(string line, NhanVien &newNhanVien)
{
	//newNhanVien.PTRHoaDonNhanVien.first->PTRChiTietHoaDon = new ChiTietHoaDon;
	newNhanVien.PTRHoaDonNhanVien.first = NULL;
	newNhanVien.PTRHoaDonNhanVien.last = NULL;
	string temp = "";
	int i = 0;
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	FixString(temp, 1);
	newNhanVien.maNV = temp;
	i++;
	temp = "";

	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	FixString(temp, 3);
	newNhanVien.ho = temp;
	i++;
	temp = "";

	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	FixString(temp, 3);
	newNhanVien.ten = temp;
	i++;
	temp = "";

	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	newNhanVien.phai = (int)temp[0] - '0';
	i++;
	temp = "";
	DSLienKetDon newListHoaDon;
	newListHoaDon.Create_ListHoaDon();
	int j = 0;
	while (line[i] != '@')
	{
		j++;
		HoaDon hoaDon;
		ChiTietHoaDon cthd;
		cthd.soLuongVatTu = 0;
		DanhSachTuyenTinh newListVatTu;
		newListVatTu.SetChiTietHoaDon(cthd);
		while (line[i] != '*')
		{
			temp += line[i];
			i++;
		}
		strcpy(hoaDon.soHoaDon, temp.c_str());
		i++;
		temp = "";

		while (line[i] != '*')
		{
			temp += line[i];
			i++;
		}
		hoaDon.ngayNhapHoaDon = StringToDate(temp);
		temp = "";
		i++;

		while (line[i] != '*')
		{
			temp += line[i];
			i++;
		}
		strcpy(hoaDon.loai, temp.c_str());
		i++;
		temp = "";
		while (line[i] != '#')
		{
			ChiTietVatTu ctvt;
			strcpy(ctvt.maVT, "");
			ctvt.soLuong = 0;
			ctvt.donGia = 0;
			ctvt.VAT = 0;
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			strcpy(ctvt.maVT, temp.c_str());
			i++;
			temp = "";
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			ctvt.soLuong = stof(temp);
			i++;
			temp = "";
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			ctvt.donGia = stof(temp);
			i++;
			temp = "";
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			ctvt.VAT = stof(temp);
			i++;
			temp = "";
			newListVatTu.InsertOrder(ctvt,newListVatTu.GetChiTietHoaDon().soLuongVatTu);
		}

		//		XuatHoaDon(hoaDon);
		i++;
		temp = "";
		newListHoaDon.InsertLast(hoaDon);
		newListHoaDon.InsertLastChiTietHoaDon(newListVatTu.GetChiTietHoaDon());
		//		XuatDayHoaDon(newNhanVien.PTRHoaDonNhanVien.first);
	}
	newNhanVien.PTRHoaDonNhanVien = newListHoaDon.GetListHoaDon();
}

BackEnd::BackEnd()
{
}


BackEnd::~BackEnd()
{
}
