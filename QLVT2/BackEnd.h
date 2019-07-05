#pragma once
#include "Header.h"
#include "DanhSachTuyenTinh.h"
#include "DSLienKetDon.h"
#include "CayNhiPhan.h"
#include "MangConTro.h"
#include "Design.h"
class BackEnd
{
public:
	void FixText(string& Text);
	void LineToVatTu(string line, VatTu& newVatTu, char maVT[11]);
	void LineToNhanVien(string line, NhanVien &newNhanVien);
	BackEnd();
	~BackEnd();
};
