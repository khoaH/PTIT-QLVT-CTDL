#pragma once
#include "Header.h"
#include "Design.h"

class DanhSachTuyenTinh
{
private:
	ChiTietHoaDon dsHoaDon;
public:
	int CheckChiTiet(ChiTietVatTu info);
	int FullList();
	int EmptyList();
	int InsertOrder(ChiTietVatTu info, int diaChi);
	int DeleteCell(int diaChi);
	int ChangeCell(int diaChi, ChiTietVatTu info);
	int Search(ChiTietVatTu info);
	ChiTietHoaDon GetChiTietHoaDon();
	void SetChiTietHoaDon(ChiTietHoaDon value);
	DanhSachTuyenTinh();
	~DanhSachTuyenTinh();
};

