#pragma once
#include "ConnectFile.h"
#include "DanhSachTuyenTinh.h"
#include "Header.h"
#include "DSVatTu.h"
#include <ctime>
class DSCTHoaDon :public DanhSachTuyenTinh
{
	enum InfoSelect {
		themMa,
		timVT,
		themSL,
		themDG,
		themVAT,
		chonOptionThem,
		chonOptionSua
	};
	enum InputDay
	{
		chonNgayChay,
		chonThangChay,
		chonNamChay,
		chonNgayDung,
		chonThangDung,
		chonNamDung,
		chonOption
	};
	InfoSelect infoSelect;
	InputDay inputDay;
	int keypress;
	ConnectFile* con;
	int viTriFirst;
	int viTriCurrent;
	CayNhiPhan dataVatTu;
	CayNhiPhan dataVatTuCu;
	PTRHoaDon currentHoaDon;
	PTRTop firstRank;
	PTRTop lastRank;
	PTRTop currRank;
	PTRTop firstListRank;
	PTRTop lastListRank;
	int rankAmount;
public:
	int ViTriEndList();
	void Travese();
	void TraverseDT();
	void DrawChiTietHD(); //ke bang chi tiet hd
	void DrawDoanhThu();
	void DrawFormChiTietVatTu();
	void DrawFormDoanhThu();
	void WriteHang(); //viet thong tin hoa don
	void WriteDT();
	void ThemHang(); //nut insert
	void FindVatTu(ChiTietVatTu& newVatTu);
	void ExitOption(int choice, char choiceArr[][15], int soOption, ChiTietVatTu vatTu);
	void InputAdd(ChiTietVatTu& newVatTu);
	void InputAddDT(Ngay& start, Ngay& end);
	void ChangeInput();
	void ChangeInputFix();
	void ChangeInputDT();
	int CheckTrung(ChiTietVatTu& vatTu);
	int CheckHang(ChiTietVatTu& vatTu);
	void XoaHang(); //nut delete
	void SuaNHang();
	int ExitMenu(int keyhit); //dung nut escape
	void MainCTHD(ConnectFile* connect, PTRHoaDon& currentHD);
	void MainXemCTHD(ConnectFile* connect, PTRHoaDon& currentHD);
	void CopyDataDT(PTRTop a, PTRTop& b);
	void SwapDataDt(PTRTop& a, PTRTop& b);
	PTRTop DivideListDT(PTRTop& a, PTRTop& b);
	PTRTop LastAllRank(PTRTop topList);
	void QuickSortDT(PTRTop& a, PTRTop& b);
	PTRTop TinhTopDoanhThu(Ngay start, Ngay end);
	void DoanhThu(Ngay startDay, Ngay endDay);
	void MainDoanhThu(ConnectFile* connect);
	float ToTalCost();
	DSCTHoaDon();
	~DSCTHoaDon();
};

