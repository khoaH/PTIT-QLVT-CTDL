#include "MangConTro.h"

DanhSachNhanVien MangConTro::GetDanhSachNhanVien()
{
	return this->dsNhanVien;
}

void MangConTro::GiaiPhong()
{
	for (int i = 0; i < this->dsNhanVien.soLuongNhanVien; i++)
	{
		delete this->dsNhanVien.nodes[i];
	}
	this->dsNhanVien.soLuongNhanVien = 0;
}

int MangConTro::CheckNhanVien(NhanVien nhanVien)
{
	if (!CheckString(nhanVien.ho, 1) || !CheckString(nhanVien.ho, 5))
		return 2;
	else if (!CheckString(nhanVien.ten, 1) || !CheckString(nhanVien.ten, 5))
		return 3;
	else if (!CheckString(nhanVien.maNV, 3) || !CheckString(nhanVien.maNV, 5) || !CheckString(nhanVien.maNV, 4))
		return 4;
	else if (nhanVien.phai != 0 && nhanVien.phai != 1)
		return 5;
	else
		return 1;
}

int MangConTro::TrongNhanVien()
{
	return this->dsNhanVien.soLuongNhanVien == 0;
}

int MangConTro::DayNhanVien()
{
	return (this->dsNhanVien.soLuongNhanVien == MAXNHANVIEN ? 1 : 0);
}

int MangConTro::TimNhanVien(std::string maNV)
{
	for (int i = 0; i < this->dsNhanVien.soLuongNhanVien; i++)
	{
		if (this->dsNhanVien.nodes[i]->maNV == maNV)
			return i;
	}
	return -1;
}

int MangConTro::TimViTriThichHopX(std::string ho, std::string ten)
{
	string t1 = ten + ho;
	string t2;
	for (int i = 0; i < this->dsNhanVien.soLuongNhanVien; i++)
	{
		t2 = this->dsNhanVien.nodes[i]->ten + this->dsNhanVien.nodes[i]->ho;
		if (t2 > t1)
			return i;
	}
	return this->dsNhanVien.soLuongNhanVien;
}

int MangConTro::ThemNhanVienVaoX(NhanVien nhanVien, int diaChi)
{
	if (diaChi < 0 || diaChi > this->dsNhanVien.soLuongNhanVien || DayNhanVien())
		return 0;
	this->dsNhanVien.nodes[this->dsNhanVien.soLuongNhanVien] = new NhanVien;
	for (int i = this->dsNhanVien.soLuongNhanVien; i > diaChi; i--)
		* this->dsNhanVien.nodes[i] = *this->dsNhanVien.nodes[i - 1];
	this->dsNhanVien.soLuongNhanVien++;
	*this->dsNhanVien.nodes[diaChi] = nhanVien;
	return 1;
}

int MangConTro::ThemNhanVienTheoTen(NhanVien nhanVien)
{
	if (this->CheckNhanVien(nhanVien) > 1)
	{
		clrscr();
		cout << "Loi nhap nhan vien";
		exit(this->CheckNhanVien(nhanVien));
	}
	if (this->TimNhanVien(nhanVien.maNV) >= 0)
		return -1;
	int diaChi = TimViTriThichHopX(nhanVien.ho, nhanVien.ten);
	int kq = ThemNhanVienVaoX(nhanVien, diaChi);
	return kq;
}

int MangConTro::XoaNhanVienViTiX(int diaChi)
{
	if (diaChi < 0 || diaChi > this->dsNhanVien.soLuongNhanVien - 1 || TrongNhanVien())
		return 0;
	for (int i = diaChi; i < this->dsNhanVien.soLuongNhanVien - 1; i++)
		* this->dsNhanVien.nodes[i] = *this->dsNhanVien.nodes[i + 1];
		delete this->dsNhanVien.nodes[this->dsNhanVien.soLuongNhanVien--];
	return 1;
}

int MangConTro::UpdateNhanVienViTiX(int &diaChi, NhanVien info)
{
	if (this->CheckNhanVien(info) > 1)
	{
		clrscr();
		cout << "Loi nhap nhan vien";
		exit(this->CheckNhanVien(info));
	}
	int idTrung = this->TimNhanVien(info.maNV);
	if (idTrung >= 0 && idTrung != diaChi)
		return -1;
	if (diaChi < 0 || diaChi > this->dsNhanVien.soLuongNhanVien)
		return 0;
	int diaChiChuyen = TimViTriThichHopX(info.ho, info.ten);
	if (diaChiChuyen > diaChi)
	{
		for (int i = diaChi; i < diaChiChuyen - 1; i++)
			* this->dsNhanVien.nodes[i] = *this->dsNhanVien.nodes[i + 1];
		*this->dsNhanVien.nodes[diaChiChuyen - 1] = info;
		diaChi = diaChiChuyen - 1;
	}
	else if (diaChiChuyen <= diaChi)
	{
		for (int i = diaChi; i > diaChiChuyen; i--)
			* this->dsNhanVien.nodes[i] = *this->dsNhanVien.nodes[i - 1];
		*this->dsNhanVien.nodes[diaChiChuyen] = info;
		diaChi = diaChiChuyen;
	}
	return 1;
}

string MangConTro::getSex(NhanVien nhanVien)
{
	return (nhanVien.phai == 1 ? "Nam" : "Nu");
}

void MangConTro::SetDanhSachNhanVien(DanhSachNhanVien value)
{
	this->dsNhanVien = value;
}

MangConTro::MangConTro()
{
	dsNhanVien.soLuongNhanVien = 0;
}


MangConTro::~MangConTro()
{
}