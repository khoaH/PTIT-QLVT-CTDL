#include "ConnectFile.h"


void ConnectFile::readFile()
{
	string line; //TUNG DONG CUA FILE
	if (read.is_open()) {
		int currLine = 0;
		int readMode = 1; //1 = read Vat Tu, 2 = read Nhan Vien
		while (getline(read, line))
		{
			if (line[0] == '-' && readMode == 1)
			{
				readMode = 2;
				this->dsVatTuChinh.TraverseToList();
				continue;
			}
			if (readMode == 1)
			{
				VatTu newVatTu;
				char maVT[11];
				LineToVatTu(line, newVatTu, maVT);
				int done = this->dsVatTuChinh.InsertOrder(newVatTu, maVT);
				if(done == 0)
				{
					system("color f0");
					clrscr();
					cout << "Ma vat tu bi trung tai dong " << currLine + 1 << endl;
					exit(1);
				}
				currLine++;
			}
			if (readMode == 2)
			{
				int done = 1;
				NhanVien newNhanVien;
				LineToNhanVien(line, newNhanVien);
				done = this->dsNhanVienChinh.ThemNhanVienTheoTen(newNhanVien);
				if (done == -1)
				{
					system("color f0");
					clrscr();
					cout << "Ma nhan vien bi trung tai dong " << currLine + 1 << endl;
					exit(1);
				}
				else if (done == 0)
				{
					system("color f0");
					clrscr();
					cout << "Nhan vien bi qua tai, xoa bot nhan vien trong du lieu" << endl;
					exit(1);
				}
				currLine++;
			}
		}
	}
	else
		cout << "Loi doc file";
}

void ConnectFile::writeFile()
{
	if (write.is_open())
	{
		for (ListVatTu temp = this->dsVatTuChinh.GetFirstListVatTu(); temp != NULL; temp = temp->right)
		{
			write << temp->maVT;
			write << "+";
			write << temp->info.tenVT;
			write << "+";
			write << temp->info.soLuongTon;
			write << "+";
			write << temp->info.donViTinh;
			write << "+" << endl;
		}
		write << "-" << endl;
		for(int i = 0; i < this->getDanhSachNhanVien().soLuongNhanVien; i++)
		{
			write << this->getDanhSachNhanVien().nodes[i]->maNV;
			write << "+";
			write << this->getDanhSachNhanVien().nodes[i]->ho;
			write << "+";
			write << this->getDanhSachNhanVien().nodes[i]->ten;
			write << "+";
			write << this->getDanhSachNhanVien().nodes[i]->phai;
			write << "+";
			if (this->getDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first != NULL)
				for (PTRHoaDon p = this->getDanhSachNhanVien().nodes[i]->PTRHoaDonNhanVien.first; p != NULL; p = p->next)
				{
					write << p->infoHoaDon.soHoaDon;
					write << "*";
					write << DateToString(p->infoHoaDon.ngayNhapHoaDon);
					write << "*";
					write << p->infoHoaDon.loai;
					write << "*";
					for (int j = 0; j < p->PTRChiTietHoaDon->soLuongVatTu; j++)
					{
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].maVT;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].donGia;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].VAT;
						write << "/";
					}
					write << "#";
				}
			write << "@" << endl;
		}
	}
	else
		cout << "Loi doc file" << endl;
}

void ConnectFile::readOldData()
{
	string line; //TUNG DONG CUA FILE
	if (read.is_open()) {
		int currLine = 0;
		int readMode = 1; //1 = read Vat Tu, 2 = read Nhan Vien
		while (getline(read, line))
		{
			if (line[0] == '-' && readMode == 1)
			{
				readMode = 2;
				this->dsVatTuPhu.TraverseToList();
				currLine++;
				continue;
			}
			if (line[0] == '*' && readMode == 2)
			{
				readMode = 3;
				currLine++;
				continue;
			}
			if (readMode == 1)
			{
				VatTu newVatTu;
				char maVT[11];
				LineToVatTu(line, newVatTu, maVT);
				int done = this->dsVatTuPhu.InsertOrder(newVatTu, maVT);
				if (done == 0)
				{
					system("color f0");
					clrscr();
					cout << "Old Data: Ma vat tu bi trung tai dong " << currLine + 1 << endl;
					exit(1);
				}
				currLine++;
			}
			if (readMode == 2)
			{
				int done = 1;
				NhanVien newNhanVien;
				LineToNhanVien(line, newNhanVien);
				done = this->dsNhanVienPhu.ThemNhanVienTheoTen(newNhanVien);
				if (done == -1 || this->dsNhanVienChinh.TimNhanVien(newNhanVien.maNV) >= 0)
				{
					system("color f0");
					clrscr();
					cout << "Old Data: Ma nhan vien bi trung tai dong " << currLine + 1 << endl;
					exit(1);
				}
				else if (done == 0)
				{
					system("color f0");
					clrscr();
					cout << "Old Data: Nhan vien bi qua tai, xoa bot nhan vien trong du lieu" << endl;
					exit(1);
				}
				currLine++;
			}
			if (readMode == 3)
			{
				int done = 1;
				NhanVien newNhanVien;
				LineToNhanVien(line, newNhanVien);
				if (this->dsNhanVienChinh.TimNhanVien(newNhanVien.maNV) < 0)
				{
					system("color f0");
					clrscr();
					cout << "Old Data: Ma nhan vien khong ton tai " << currLine + 1 << endl;
					exit(1);
				}
				done = this->dsNhanVienPhu2.ThemNhanVienTheoTen(newNhanVien);
				if (done == -1 || this->dsNhanVienPhu.TimNhanVien(newNhanVien.maNV) >= 0)
				{
					system("color f0");
					clrscr();
					cout << "Old Data: Ma nhan vien bi trung tai dong " << currLine + 1 << endl;
					exit(1);
				}
				else if (done == 0)
				{
					system("color f0");
					clrscr();
					cout << "Old Data: Nhan vien bi qua tai, xoa bot nhan vien trong du lieu" << endl;
					exit(1);
				}
				currLine++;
			}
		}
	}
	else
		cout << "Loi doc file";
}

void ConnectFile::writeOldData()
{
	if (write.is_open())
	{
		for (ListVatTu temp = this->dsVatTuPhu.GetFirstListVatTu(); temp != NULL; temp = temp->right)
		{
			write << temp->maVT;
			write << "+";
			write << temp->info.tenVT;
			write << "+";
			write << temp->info.soLuongTon;
			write << "+";
			write << temp->info.donViTinh;
			write << "+" << endl;
		}
		write << "-" << endl;
		for (int i = 0; i < this->getDanhSachNhanVienPhu().soLuongNhanVien; i++)
		{
			write << this->getDanhSachNhanVienPhu().nodes[i]->maNV;
			write << "+";
			write << this->getDanhSachNhanVienPhu().nodes[i]->ho;
			write << "+";
			write << this->getDanhSachNhanVienPhu().nodes[i]->ten;
			write << "+";
			write << this->getDanhSachNhanVienPhu().nodes[i]->phai;
			write << "+";
			if (this->getDanhSachNhanVienPhu().nodes[i]->PTRHoaDonNhanVien.first != NULL)
				for (PTRHoaDon p = this->getDanhSachNhanVienPhu().nodes[i]->PTRHoaDonNhanVien.first; p != NULL; p = p->next)
				{
					write << p->infoHoaDon.soHoaDon;
					write << "*";
					write << DateToString(p->infoHoaDon.ngayNhapHoaDon);
					write << "*";
					write << p->infoHoaDon.loai;
					write << "*";
					for (int j = 0; j < p->PTRChiTietHoaDon->soLuongVatTu; j++)
					{
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].maVT;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].donGia;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].VAT;
						write << "/";
					}
					write << "#";
				}
			write << "@" << endl;
		}
		write << "*" << endl;
		for (int i = 0; i < this->getDanhSachNhanVienPhu2().soLuongNhanVien; i++)
		{
			write << this->getDanhSachNhanVienPhu2().nodes[i]->maNV;
			write << "+";
			write << this->getDanhSachNhanVienPhu2().nodes[i]->ho;
			write << "+";
			write << this->getDanhSachNhanVienPhu2().nodes[i]->ten;
			write << "+";
			write << this->getDanhSachNhanVienPhu2().nodes[i]->phai;
			write << "+";
			if (this->getDanhSachNhanVienPhu2().nodes[i]->PTRHoaDonNhanVien.first != NULL)
				for (PTRHoaDon p = this->getDanhSachNhanVienPhu2().nodes[i]->PTRHoaDonNhanVien.first; p != NULL; p = p->next)
				{
					write << p->infoHoaDon.soHoaDon;
					write << "*";
					write << DateToString(p->infoHoaDon.ngayNhapHoaDon);
					write << "*";
					write << p->infoHoaDon.loai;
					write << "*";
					for (int j = 0; j < p->PTRChiTietHoaDon->soLuongVatTu; j++)
					{
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].maVT;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].soLuong;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].donGia;
						write << "/";
						write << p->PTRChiTietHoaDon->nodesChiTiet[j].VAT;
						write << "/";
					}
					write << "#";
				}
			write << "@" << endl;
		}
	}
	else
		cout << "Loi doc file" << endl;
}

PTRVatTu ConnectFile::getVatTuPhu()
{
	return this->dsVatTuPhu.GetPTRVatTu();
}

int ConnectFile::getSoLoaiVTPhu()
{
	return this->dsVatTuPhu.GetSoLoaiVatTu();
}

DanhSachNhanVien ConnectFile::getDanhSachNhanVienPhu()
{
	return this->dsNhanVienPhu.GetDanhSachNhanVien();
}

void ConnectFile::setDanhSachSinhVienPhu(DanhSachNhanVien value)
{
	this->dsNhanVienPhu.SetDanhSachNhanVien(value);
}

void ConnectFile::setDanhSachVatTuPhu(PTRVatTu value)
{
	this->dsVatTuPhu.SetPTRVatTu(value);
}

DanhSachNhanVien ConnectFile::getDanhSachNhanVienPhu2()
{
	return this->dsNhanVienPhu2.GetDanhSachNhanVien();
}

void ConnectFile::setDanhSachSinhVienPhu2(DanhSachNhanVien value)
{
	this->dsNhanVienPhu2.SetDanhSachNhanVien(value);

}

PTRVatTu ConnectFile::getVatTu()
{
	return this->dsVatTuChinh.GetPTRVatTu();
}

int ConnectFile::getSoLoaiVT()
{
	return this->dsVatTuChinh.GetSoLoaiVatTu();
}

DanhSachNhanVien ConnectFile::getDanhSachNhanVien()
{
	return this->dsNhanVienChinh.GetDanhSachNhanVien();
}

void ConnectFile::setDanhSachSinhVien(DanhSachNhanVien value)
{
	this->dsNhanVienChinh.SetDanhSachNhanVien(value);
}

void ConnectFile::setDanhSachVatTu(PTRVatTu value)
{
	this->dsVatTuChinh.SetPTRVatTu(value);
}

ConnectFile::ConnectFile()
{
	read.open("data.txt");
	this->readFile();
	read.close();
	read.open("OldData.txt");
	this->readOldData();
	read.close();
}

ConnectFile::~ConnectFile()
{
	write.open("data.txt");
	this->writeFile();
	write.close();
	write.open("OldData.txt");
	this->writeOldData();
	write.close();
}