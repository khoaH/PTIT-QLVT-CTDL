#include "Header.h"
#include "Design.h"
#pragma once
class MangConTro
{
private:
	DanhSachNhanVien dsNhanVien;
public:
//	void InserOrder(NhanVien infor);
//	void DeleteCell(int index);
//	void ChangeCell(int index, NhanVien infor);
	void GiaiPhong();
	int CheckNhanVien(NhanVien nhanVien);
	int TrongNhanVien();
	int DayNhanVien();
	int TimNhanVien(std::string maNV);
	int TimViTriThichHopX(std::string ho, std::string ten);
	int ThemNhanVienVaoX(NhanVien nhanVien, int diaChi);
	int ThemNhanVienTheoTen(NhanVien nhanVien);
	int XoaNhanVienViTiX(int diaChi);
	int UpdateNhanVienViTiX(int &diaChi, NhanVien info);
	string getSex(NhanVien nhanVien);
	void SetDanhSachNhanVien(DanhSachNhanVien value);
	DanhSachNhanVien GetDanhSachNhanVien();
	MangConTro();
	~MangConTro();
};

