#pragma once
#ifndef CAUTRUCDULIEU_H
#define CAUTRUCDULIEU_H

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#define MAXNHANVIEN 500
#define MAXVATTU 20
#define MAXTRANGHD 100
using namespace std;

typedef struct
{
	int date;
	int month;
	int year;
} Ngay;

typedef struct
{
	string tenVT, donViTinh;  //DVT = don vi tinh
	float soLuongTon; // so luong ton
} VatTu;

struct NodesVatTu
{
	VatTu info;
	struct NodesVatTu* left;
	struct NodesVatTu* right;
	char maVT[11]; //key
	int balanceFactor;
};

typedef struct NodesVatTu* PTRVatTu;

struct LinkListVatTu
{
	char maVT[11];
	VatTu info;
	struct LinkListVatTu* left;
	struct LinkListVatTu* right;
};

typedef LinkListVatTu* ListVatTu;

typedef struct
{
	char maVT[11];
	float soLuong, donGia, VAT; //VAT se la duoi dang xxx%
} ChiTietVatTu;

typedef struct
{
	int soLuongVatTu;
	ChiTietVatTu nodesChiTiet[MAXVATTU + 1];
}ChiTietHoaDon;

typedef struct
{
	char soHoaDon[21];
	Ngay ngayNhapHoaDon;
	char loai[2];  //'N' = chi nhap 'X' = chi xuat
} HoaDon;

struct NodesHoaDon
{
	HoaDon infoHoaDon;
	struct NodesHoaDon* next;
	ChiTietHoaDon* PTRChiTietHoaDon;
};

typedef struct NodesHoaDon* PTRHoaDon;

typedef struct
{
	PTRHoaDon first;
	PTRHoaDon last;
}ListHoaDon;

typedef struct
{
	std::string maNV;
	//char Ho[30],Ten[30];
	std::string ho, ten;
	int phai;
	ListHoaDon PTRHoaDonNhanVien;   //danh sach hoa don nhan vien lam, chi den dia chi cua hoa don
} NhanVien;

typedef struct
{
	int soLuongNhanVien;
	NhanVien* nodes[MAXNHANVIEN + 1];
} DanhSachNhanVien;

struct NodeDauTrang {
	int trangHienTai = 1;
	NodesHoaDon* hoaDonDauTrang[MAXTRANGHD] = { NULL };
};

struct TopDT
{
	char maVT[11];
	string tenVT, donVi;
	float soLuong, donGiaTB, tonKho, total;
	struct TopDT* right;
	struct TopDT* left;
};

typedef struct TopDT* PTRTop;

#endif