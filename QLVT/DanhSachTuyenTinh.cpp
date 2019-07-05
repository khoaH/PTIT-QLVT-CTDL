#include "DanhSachTuyenTinh.h"



int DanhSachTuyenTinh::CheckChiTiet(ChiTietVatTu info)
{
	if (!CheckString(CharToString(info.maVT), 3) || !CheckString(CharToString(info.maVT), 4) || !CheckString(CharToString(info.maVT), 5)) //la chuoi, khong khoang trang, khong rong
		return 2;
	else if (info.soLuong < 1)
		return 3;
	else if (info.donGia < 0)
		return 4;
	else if (info.VAT < 0)
		return 5;
}

int DanhSachTuyenTinh::FullList()
{
	return this->dsHoaDon.soLuongVatTu == MAXVATTU;
}

int DanhSachTuyenTinh::EmptyList()
{
	return this->dsHoaDon.soLuongVatTu == 0;
}

int DanhSachTuyenTinh::InsertOrder(ChiTietVatTu info, int diaChi)
{
	if (this->CheckChiTiet(info) > 1)
	{
		clrscr();
		cout << "Loi nhap chi tiet hoa don";
		exit(this->CheckChiTiet(info));
	}
	if (diaChi <0 || diaChi>dsHoaDon.soLuongVatTu || FullList())
		return 0;
	for (int i = dsHoaDon.soLuongVatTu - 1; i >= diaChi; i--)
		dsHoaDon.nodesChiTiet[i + 1] = dsHoaDon.nodesChiTiet[i];
	dsHoaDon.nodesChiTiet[diaChi] = info;
	dsHoaDon.soLuongVatTu++;
	return 1;
}

int DanhSachTuyenTinh::DeleteCell(int diaChi)
{
	if (diaChi < 0 || diaChi>dsHoaDon.soLuongVatTu || EmptyList())
		return 0;
	for (int i = diaChi + 1; i < dsHoaDon.soLuongVatTu; i++)
		dsHoaDon.nodesChiTiet[i - 1] = dsHoaDon.nodesChiTiet[i];
	dsHoaDon.soLuongVatTu--;
	return 1;
}

int DanhSachTuyenTinh::ChangeCell(int diaChi, ChiTietVatTu info)
{
	if (this->CheckChiTiet(info) > 1)
	{
		clrscr();
		cout << "Loi nhap chi tiet hoa don";
		exit(this->CheckChiTiet(info));
	}
	if (diaChi <0 || diaChi>dsHoaDon.soLuongVatTu || FullList())
		return 0;
	dsHoaDon.nodesChiTiet[diaChi] = info;
	return 1;
}

int DanhSachTuyenTinh::Search(ChiTietVatTu info)
{
	for (int i = 0; i < dsHoaDon.soLuongVatTu; i++)
	{
		if (stricmp(dsHoaDon.nodesChiTiet[i].maVT, info.maVT) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}

ChiTietHoaDon DanhSachTuyenTinh::GetChiTietHoaDon()
{
	return this->dsHoaDon;
}

void DanhSachTuyenTinh::SetChiTietHoaDon(ChiTietHoaDon value)
{
	this->dsHoaDon = value;
}

DanhSachTuyenTinh::DanhSachTuyenTinh()
{
}


DanhSachTuyenTinh::~DanhSachTuyenTinh()
{
}
