#pragma once
#include "Header.h"
#include "MangConTro.h"

using namespace std;

class DSLienKetDon
{
private:
	ListHoaDon dsHoaDon;
public:
	void InsertFirst(HoaDon info);
	void InsertLast(HoaDon hd);
	PTRHoaDon NodeDangTruocNodeCanXuLi(HoaDon hd);
	void GiaiPhongList();
	void DeleteFirst();
	void DeleteLast();
	void DeleteAfter(PTRHoaDon& p);
	void DeleteInfo(HoaDon hd);
	void DeleteNode(HoaDon Del);
	void UpdateNode(PTRHoaDon Change, HoaDon infor);
	PTRHoaDon Search(HoaDon sear);
	void Create_ListHoaDon();
	bool Empty();
	int InsertLastChiTietHoaDon(ChiTietHoaDon cthd);
	ListHoaDon GetListHoaDon();
	void SetListHoaDon(ListHoaDon value);
	int CheckTrung(PTRHoaDon first, char soHD[]);
	int CheckHoaDon(HoaDon newHoaDon, DanhSachNhanVien& dsNhanVien);
	DSLienKetDon();
	~DSLienKetDon();
};
