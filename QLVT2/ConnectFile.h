#pragma once
#include "BackEnd.h"
#include "Header.h"
#include "CayNhiPhan.h"
#include "DSLienKetDon.h"
#include "DanhSachTuyenTinh.h"
#include "MangConTro.h"
#include <string>
#include <iostream>
#include <fstream>
class ConnectFile : public BackEnd
{
private:
	ifstream read;
	ofstream write;
	MangConTro dsNhanVienChinh;
	MangConTro dsNhanVienPhu; //ds nhan vien da xoa
	MangConTro dsNhanVienPhu2; // ds hoa don da xoa, nhung nhan vien chua xoa
	CayNhiPhan dsVatTuChinh;
	CayNhiPhan dsVatTuPhu;
	DSLienKetDon dsLienKetDon;
	DanhSachTuyenTinh danhSachTuyenTinh;
public:
	void readFile();
	void writeFile();
	PTRVatTu getVatTu();
	int getSoLoaiVT();
	DanhSachNhanVien getDanhSachNhanVien();
	void setDanhSachSinhVien(DanhSachNhanVien value);
	void setDanhSachVatTu(PTRVatTu value);
	//
	void readOldData();
	void writeOldData();
	PTRVatTu getVatTuPhu();
	int getSoLoaiVTPhu();
	DanhSachNhanVien getDanhSachNhanVienPhu();
	void setDanhSachSinhVienPhu(DanhSachNhanVien value);
	void setDanhSachVatTuPhu(PTRVatTu value);
	DanhSachNhanVien getDanhSachNhanVienPhu2();
	void setDanhSachSinhVienPhu2(DanhSachNhanVien value);
	//
	ConnectFile();
	~ConnectFile();
};