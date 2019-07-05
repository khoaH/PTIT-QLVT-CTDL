#pragma once
#include "DSLienKetDon.h"
#include "Design.h"
#include "console.h"
#include "DSCTHoaDon.h"
#include <ctime>

class DSHoaDon :public DSLienKetDon
{
private:
	enum CurrentAdd {
		themSoHD,
		themDate_date,
		themDate_month,
		themDate_year,
		chonLoai,
		option
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
	enum InHD
	{
		chonSoHD,
		TimTrongDSHD,
		Option
	};
	InputDay inputDay;
	CurrentAdd currentAdd;
	InHD inHD;
	int keyhitHD;
	PTRHoaDon firstList, lastList, currentList;
	NodeDauTrang x;
	DanhSachNhanVien dsNhanVien;
	MangConTro dsThongKe;
	int viTriCurrent;
	ConnectFile* connectFile;
public:
	PTRHoaDon endList(PTRHoaDon first);
	PTRHoaDon prevList(PTRHoaDon firstList, PTRHoaDon currentList);
	string TimTenNV(PTRHoaDon run);
	float TriGiaHD(PTRHoaDon run);
	void WriteThongKe();
	void TimTatCaHoaDon();
	void traveseList();
	void travese();
	void DrawHoaDon();
	void DrawFormThemHoaDon();
	void DrawFormThongKe();
	void DrawFormInHD();
	void DrawThongKe();
	void InputAdd(HoaDon& newHoaDon);
	void InputAddDT(Ngay& start, Ngay& end);
	void InputInHD(HoaDon& find);
	void ChangeInputAdd();
	void ChangeInputDT();
	void ChangeInputInHD();
	void TurnBackInput(HoaDon newHoaDon);
	void TurnBackInputInHD();
	int EscInputAdd(HoaDon newHoaDon);
	void ChooseType(char type[]);
	void ThemHoaDon();
	void SelectHD();
	void CapnhatNodesdautrang();
	int ExitHD(int keyhit);
	void MainHD(ConnectFile* connect, int vitrinhanvien);
	void TimDSHD_InHoaDon();
	void MainInHoaDon(ConnectFile* connect);
	void TimDSHDTheoNgay(Ngay startDay, Ngay endDay);
	void TimTuDSHD();
	void SelectInHoaDon(HoaDon &find);
	void MainThongKeHD(ConnectFile* connect);
	void ThongKe(Ngay startDay, Ngay endDay);
	void GiaiPhong_dsThongKe();
	DanhSachNhanVien ReturnDSNhanVien();
	int ThemChiTietHoaDon(HoaDon newHoaDon, ChiTietHoaDon& cthd);
	void XemChiTietHoaDon(PTRHoaDon xem);
	DSHoaDon();
	~DSHoaDon();
};