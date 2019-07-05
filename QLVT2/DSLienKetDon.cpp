#include "DSLienKetDon.h"


void DSLienKetDon::InsertFirst(HoaDon info)
{
	PTRHoaDon p = new NodesHoaDon;
	if (p == NULL)
	{
		cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return;
	}
	p->infoHoaDon = info;
	p->next = NULL;
	if (Empty())
	{
		this->dsHoaDon.first = this->dsHoaDon.last = p;
	}
	else
	{
		p->next = this->dsHoaDon.first;
		this->dsHoaDon.first = p;
	}
}

void DSLienKetDon::InsertLast(HoaDon hd)
{
	PTRHoaDon p = new NodesHoaDon;
	if (p == NULL)
	{
		cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return;
	}
	p->infoHoaDon = hd;
	p->next = NULL;
	if (Empty())
	{
		this->dsHoaDon.first = this->dsHoaDon.last = p;
	}
	else
	{
		this->dsHoaDon.last->next = p;
		this->dsHoaDon.last = p;
	}
}

PTRHoaDon DSLienKetDon::NodeDangTruocNodeCanXuLi(HoaDon hd)
{
	for (PTRHoaDon i = this->dsHoaDon.first; i->next != NULL; i = i->next)
	{
		if (strcmp(i->next->infoHoaDon.soHoaDon, hd.soHoaDon) == 0)
		{
			return i;
		}
	}
	return NULL;
}

void DSLienKetDon::GiaiPhongList()
{
	PTRHoaDon temp;
	while (dsHoaDon.first != NULL)
	{
		delete dsHoaDon.first->PTRChiTietHoaDon;
		temp = dsHoaDon.first;
		dsHoaDon.first = dsHoaDon.first->next;
		delete temp;
	}
	this->dsHoaDon.last = NULL;
}

void DSLienKetDon::DeleteFirst()
{
	if (Empty())
	{
		cout << "Khong co phan tu de xoa.";
		return;
	}
	//	if(l.First == l.Last)
	//	{
	//		l.First = l.Last = NULL;
	//	}
	//  Ko can vi truong hop 1 phan tu vs nhieu phan tu thi giai quyet giong nhau
	PTRHoaDon p = this->dsHoaDon.first;
	this->dsHoaDon.first = this->dsHoaDon.first->next;
	delete p;
}

void DSLienKetDon::DeleteLast()
{
	if (Empty())
	{
		cout << "Khong co phan tu de xoa.";
		return;
	}
	if (this->dsHoaDon.first == this->dsHoaDon.last) //danh sach chi 1 phan tu
	{
		this->dsHoaDon.first = this->dsHoaDon.last = NULL;
	}
	PTRHoaDon p = this->dsHoaDon.first;
	for (PTRHoaDon i = this->dsHoaDon.first; i != NULL; i = i->next)
	{
		if (i->next == this->dsHoaDon.last)
		{
			delete this->dsHoaDon.last;
			i->next = NULL;
			this->dsHoaDon.last = i;
		}
	}
}

void DSLienKetDon::DeleteAfter(PTRHoaDon& p)
{
	PTRHoaDon q;
	q = p->next;
	p->next = q->next;
	delete q;
}

void DSLienKetDon::DeleteInfo(HoaDon hd)
{
	if (Empty())
	{
		cout << "Khong the xoa vi danh sach rong.";
		return;
	}
	if (strcmp(this->dsHoaDon.first->infoHoaDon.soHoaDon, hd.soHoaDon) == 0)
	{
		//cout << "\nDa xoa xong" << endl;
		DeleteFirst();
		return;
	}
	PTRHoaDon q = NodeDangTruocNodeCanXuLi(hd);
	if (q != NULL) //dung cho ca truong hop neu hoa don can xoa la Last
	{
		//cout << "\nDa xoa xong" << endl;
		DeleteAfter(q);
	}
	else
	{
		cout << "\nHoa don ko ton tai, ko the xoa.";
	}
}

void DSLienKetDon::DeleteNode(HoaDon Del)
{
}

void DSLienKetDon::UpdateNode(PTRHoaDon Change, HoaDon infor)
{
}

PTRHoaDon DSLienKetDon::Search(HoaDon sear)
{
	return PTRHoaDon();
}

void DSLienKetDon::Create_ListHoaDon()
{
	this->dsHoaDon.first = NULL;
	this->dsHoaDon.last = NULL;
}

bool DSLienKetDon::Empty()
{
	if (this->dsHoaDon.first == NULL)
		return true;
	else return false;
}

int DSLienKetDon::InsertLastChiTietHoaDon(ChiTietHoaDon cthd)
{
	this->dsHoaDon.last->PTRChiTietHoaDon = new ChiTietHoaDon;
	*this->dsHoaDon.last->PTRChiTietHoaDon = cthd;
	return 0;
}

ListHoaDon DSLienKetDon::GetListHoaDon()
{
	return this->dsHoaDon;
}

void DSLienKetDon::SetListHoaDon(ListHoaDon value)
{
	this->dsHoaDon = value;
}

int DSLienKetDon::CheckTrung(PTRHoaDon first, char soHD[])
{
	for (PTRHoaDon i = first; i != NULL; i = i->next)
		if (stricmp(i->infoHoaDon.soHoaDon, soHD) == 0)
			return 1;
	return 0;
}

int DSLienKetDon::CheckHoaDon(HoaDon newHoaDon, DanhSachNhanVien & dsNhanVien)
{
	/*1.hop le
	2.so hoa don rong
	3.so hoa don trung
	4.ngay khong hop le*/

	string temp = CharToString(newHoaDon.soHoaDon);
	FixString(temp, 5);
	if (!CheckString(temp, 5))
		return 2;
	for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++)
	{
		if (CheckTrung(dsNhanVien.nodes[i]->PTRHoaDonNhanVien.first, newHoaDon.soHoaDon))
			return 3;
	}
	if (!CheckDate(newHoaDon.ngayNhapHoaDon))
		return 4;
	return 1;
}

DSLienKetDon::DSLienKetDon()
{
}


DSLienKetDon::~DSLienKetDon()
{
}
