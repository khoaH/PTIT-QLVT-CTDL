#include "CayNhiPhan.h"



PTRVatTu CayNhiPhan::Search(char maVT[11])
{
	PTRVatTu result;
	result = this->cayVatTu;
	while (result != NULL && stricmp(maVT, result->maVT) != 0)
	{
		if (stricmp(result->maVT, maVT) > 0)
			result = result->left;
		else
			result = result->right;
	}
	return result;
}


PTRVatTu CayNhiPhan::GetPTRVatTu()
{
	return cayVatTu;
}

int CayNhiPhan::GetSoLoaiVatTu()
{
	return this->soLoaiVatTu;
}

void CayNhiPhan::SetPTRVatTu(PTRVatTu value)
{
	DeleteAll(this->cayVatTu);
	this->cayVatTu = NULL;
	this->SetPTRRecursive(value);
	this->ResetList();
}

void CayNhiPhan::SetPTRRecursive(PTRVatTu value)
{
	if (value != NULL)
	{
		SetPTRRecursive(value->left);
		SetPTRRecursive(value->right);
		this->InsertOrder(value->info, value->maVT);
	}
}

CayNhiPhan::CayNhiPhan()
{
	this->soLoaiVatTu = 0;
	this->first = NULL;
	this->last = NULL;
}


CayNhiPhan::~CayNhiPhan()
{
}

void CayNhiPhan::RotateRight(PTRVatTu& root)
{
	PTRVatTu temp = root->left;
	root->left = temp->right;
	temp->right = root;
	if (temp->balanceFactor == 1)
	{
		root->balanceFactor = 0;
		temp->balanceFactor = 0;
	}
	else if (temp->balanceFactor == 0)
	{
		root->balanceFactor = 1;
		temp->balanceFactor = -1;
	}
	root = temp;
}

void CayNhiPhan::RotateLeft(PTRVatTu& root)
{
	PTRVatTu temp = root->right;
	root->right = temp->left;
	temp->left = root;
	if (temp->balanceFactor == -1)
	{
		root->balanceFactor = 0;
		temp->balanceFactor = 0;
	}
	else if (temp->balanceFactor == 0)
	{
		root->balanceFactor = -1;
		temp->balanceFactor = 1;
	}
	root = temp;
}

void CayNhiPhan::RotateLeftRight(PTRVatTu& root)
{
	PTRVatTu temp1 = root->left;
	PTRVatTu temp2 = temp1->right;
	root->left = temp2->right;
	temp2->right = root;
	temp1->right = temp2->left;
	temp2->left = temp1;
	switch (temp2->balanceFactor)
	{
	case 1:
		root->balanceFactor = -1;
		temp1->balanceFactor = 0;
		break;
	case 0:
		root->balanceFactor = 0;
		temp1->balanceFactor = 0;
	case -1:
		root->balanceFactor = 0;
		temp1->balanceFactor = 1;
	}
	temp2->balanceFactor = 0;
	root = temp2;
}

void CayNhiPhan::RotateRightLeft(PTRVatTu& root)
{
	PTRVatTu temp1 = root->right;
	PTRVatTu temp2 = temp1->left;
	root->right = temp2->left;
	temp2->left = root;
	temp1->left = temp2->right;
	temp2->right = temp1;
	switch (temp2->balanceFactor)
	{
	case 1:
		root->balanceFactor = 1;
		temp1->balanceFactor = 0;
		break;
	case 0:
		root->balanceFactor = 0;
		temp1->balanceFactor = 0;
	case -1:
		root->balanceFactor = 0;
		temp1->balanceFactor = -1;
	}
	temp2->balanceFactor = 0;
	root = temp2;
}

int CayNhiPhan::BalanceLeft(PTRVatTu& root)
{
	PTRVatTu temp = root->left;
	switch (temp->balanceFactor)
	{
	case 1:
		RotateRight(root);
		return 2; //chieu cao thay doi return 2
	case 0:
		RotateRight(root);
		return 1; //chieu cao khong doi return 1
	case -1:
		RotateLeftRight(root); //chieu cao thay doi return 2
		return 2;
	}
	return 0;
}

int CayNhiPhan::BalanceRight(PTRVatTu& root)
{
	PTRVatTu temp = root->right;
	switch (temp->balanceFactor)
	{
	case 1:
		RotateRightLeft(root); //chieu cao thay doi return 2
		return 2;
	case 0:
		RotateLeft(root); //chieu cao khong doi return 1
		return 1;
	case -1:
		RotateLeft(root); //chieu cao thay doi return 2
		return 2;
	}
	return 0;
}

int CayNhiPhan::CheckVatTu(PTRVatTu vatTu)
{
	vatTu->info.donViTinh;
	vatTu->info.soLuongTon;
	vatTu->info.tenVT;
	vatTu->maVT;
	if (!CheckString(CharToString(vatTu->maVT), 3) || !CheckString(CharToString(vatTu->maVT), 4) || !CheckString(CharToString(vatTu->maVT), 5)) //la chuoi, khong khoang trang, khong rong
		return 2;
	if (!CheckString(vatTu->info.tenVT, 3) || !CheckString(vatTu->info.tenVT, 5))
		return 3;
	if (!CheckString(vatTu->info.donViTinh, 3) || !CheckString(vatTu->info.donViTinh, 5))
		return 4;
	if (vatTu->info.soLuongTon < 0)
		return 5;
	else
		return 1;
}

PTRVatTu CayNhiPhan::CreateNodesVT(VatTu info, char maVT[11])
{
	PTRVatTu newVatTu = new NodesVatTu;
	string temp = CharToString(maVT);
	FixString(temp, 1);
	strcpy_s(newVatTu->maVT, temp.c_str());
	newVatTu->info.tenVT = info.tenVT;
	FixString(newVatTu->info.tenVT, 3);
	newVatTu->info.donViTinh = info.donViTinh;
	FixString(newVatTu->info.donViTinh, 7);
	newVatTu->info.soLuongTon = info.soLuongTon;
	newVatTu->balanceFactor = 0;
	newVatTu->left = NULL;
	newVatTu->right = NULL;
	return newVatTu;
}

int CayNhiPhan::InsertList(VatTu info, char maVT[11])
{
	if (this->first == NULL)
		InsertListFirst(info, maVT);
	else if (info.tenVT > this->last->info.tenVT)
		this->InsertListRight(this->last, info, maVT);
	else
	{
		ListVatTu newNode = this->first;
		while (newNode->info.tenVT < info.tenVT)
			newNode = newNode->right;
		this->InsertListLeft(newNode, info, maVT);
	}
	return 1;
}

void CayNhiPhan::InsertListFirst(VatTu info, char maVT[11])
{
	ListVatTu newNode = new LinkListVatTu;
	newNode->info = info;
	strcpy_s(newNode->maVT, maVT);
	newNode->left = NULL;
	newNode->right = NULL;
	if (this->first == NULL)
		this->last = newNode;
	else
	{
		this->first->left = newNode;
		newNode->right = this->first;
	}
	this->first = newNode;
}

int CayNhiPhan::InsertListRight(ListVatTu nodePos,VatTu info, char maVT[11])
{
	if (nodePos == NULL)
		return 0; // khong co nut xac dinh de chen
	else
	{
		ListVatTu newNode, nodeAfter;
		newNode = new LinkListVatTu;
		newNode->info = info;
		strcpy_s(newNode->maVT, maVT);
		newNode->left = NULL;
		newNode->right = NULL;
		if (nodePos == this->last)
		{
			nodePos->right = newNode;
			newNode->left = nodePos;
			this->last = newNode;
		}
		else
		{
			nodeAfter = nodePos->right;
			nodeAfter->left = newNode;
			newNode->right = nodeAfter;
			newNode->left = nodePos;
			nodePos->right = newNode;
		}
	}
	return 1;
}

int CayNhiPhan::InsertListLeft(ListVatTu nodePos, VatTu info, char maVT[11])
{
	if (nodePos == NULL)
		return 0; // khong co nut xac dinh de chen
	else
	{
		ListVatTu newNode, nodeBefore;
		if (nodePos == this->first)
			this->InsertListFirst(info, maVT);
		else
		{
			newNode = new LinkListVatTu;
			newNode->info = info;
			strcpy_s(newNode->maVT, maVT);
			newNode->left = NULL;
			newNode->right = NULL;
			nodeBefore = nodePos->left;
			nodeBefore->right = newNode;
			newNode->left = nodeBefore;
			newNode->right = nodePos;
			nodePos->left = newNode;
		}
	}
	return 1;
}

int CayNhiPhan::DeleteListFirst()
{
	if (this->first == NULL)
		return 0;
	else
	{
		ListVatTu nodeDel = this->first;
		if (this->first->right == NULL)
			this->first = NULL;
		else
			this->first = nodeDel->right;
		delete nodeDel;
	}
	return 1;
}

int CayNhiPhan::DeleteListNode(ListVatTu nodePos)
{
	if (nodePos == NULL)
		return -1;
	else if (this->first == NULL)
		return 0;
	else
	{
		int i = this->DeleteNode(nodePos->maVT);
		if (nodePos == this->first)
			DeleteListFirst();
		else
		{
			ListVatTu nodeBefore, nodeAfter;
			nodeBefore = nodePos->left;
			nodeAfter = nodePos->right;
			nodeBefore->right = nodeAfter;
			nodeAfter->left = nodeBefore;
			delete nodePos;
		}
		if (i == 0)
			return 0;
		else
			return 1;
	}
}

void CayNhiPhan::DeleteAllList()
{
	while (this->first != NULL)
		DeleteListFirst();
}

void CayNhiPhan::ResetList()
{
	this->DeleteAllList();
	this->TraverseToList();
}

void CayNhiPhan::TraverseToList()
{
	this->TraversRecursive(this->cayVatTu);
}

void CayNhiPhan::TraversRecursive(PTRVatTu root)
{
	if (root != NULL)
	{
		TraversRecursive(root->left);
		this->InsertList(root->info, root->maVT);
		TraversRecursive(root->right);
	}
}

int CayNhiPhan::InsertOrder(VatTu info, char maVT[11])
{
	int i = InsertRecursive(this->cayVatTu, CreateNodesVT(info, maVT));
	if (i > 0)
		this->soLoaiVatTu++;
	return i;
}

int CayNhiPhan::InsertRecursive(PTRVatTu& root, PTRVatTu newVatTu)
{
	int result;
	if (root != NULL)
	{
		if (stricmp(root->maVT, newVatTu->maVT) == 0) //TRUNG
			return 0;
		if (stricmp(root->maVT, newVatTu->maVT) > 0)
		{
			result = InsertRecursive(root->left, newVatTu); //de quy ben trai
			if (result < 2) //khong co su thay doi ve chieu cao o cay con, bo qua buoc dieu chinh lai bf
				return result; //tra ve khong co thay doi chieu cao 
			switch (root->balanceFactor)
			{
			case -1: //TH1
				root->balanceFactor = 0; //chieu cao cua root khong doi, nen return 1
				return 1; 
			case 0: //TH2
				root->balanceFactor = 1; //chieu cao cua root thay doi (+1), nen return 2
				return 2; 
			case 1: //TH3
				BalanceLeft(root); //chieu cao cua root khong doi, nen return 1
				return 1;
			}
		}
		else
		{
			result = InsertRecursive(root->right, newVatTu); //de quy ben phai
			if (result < 2) //khong co su thay doi chieu cao o cay con, bo qua buoc dieu chinh lai bf
				return result; //tra ve khong co thay doi chieu cao 
			switch (root->balanceFactor)
			{
			case -1: //TH3
				BalanceRight(root); //chieu cao cua root khong doi, nen return 1
				return 1;
			case 0: //TH2
				root->balanceFactor = -1; //chieu cao cua root thay doi (+1), nen return 2
				return 2;
			case 1: //TH1
				root->balanceFactor = 0; //chieu cao cua root khong doi, nen return 1
				return 1;
			}
		}
	}
	root = newVatTu;
	return 2;
}

int CayNhiPhan::DeleteNode(char maVT[11])
{
	return DeleteRecursive(this->cayVatTu, maVT);
}

int CayNhiPhan::DeleteRecursive(PTRVatTu& root, char maVT[11])
{
	int result;
	if (root == NULL)
		return 0; // khong co nut
	if (stricmp(root->maVT, maVT) > 0) // nut to hon, xoa ben trai
	{
		result = DeleteRecursive(root->left, maVT); //de quy trai
		if (result < 2) //khong co thay doi ve chieu cao
			return result; //tra ve khong thay doi chieu cao
		switch (root->balanceFactor) // cay co thay doi chieu cao, nen phai can bang lai
		{
		case 1: //th lech trai
			root->balanceFactor = 0; //xoa trai, cay can bang
			return 2; //chieu cao thay doi
		case 0: //th khong lech
			root->balanceFactor = -1; //cay can bang, xoa trai thi lech phai
			return 1; //Khong co thay doi chieu cao
		case -1://th lech phai
			return BalanceRight(root); // lech phai, xoa trai lam cay mat can bang. tra ve xem cay co thay doi chieu cao khong
		}
	}
	if (stricmp(root->maVT, maVT) < 0) // nut nho hon, xoa ben phai
	{
		result = DeleteRecursive(root->right, maVT); //tuong tu truong hop tren
		if (result < 2)
			return result; 
		switch (root->balanceFactor) 
		{
		case 1:
			return BalanceLeft(root); 
		case 0:
			root->balanceFactor = 1;
			return 1;
		case -1:
			root->balanceFactor = 0;
			return 2;
		}
	}
	else //nut bang maVT can tim
	{
		PTRVatTu temp = root;
		if (root->left == NULL) //chi co con phai
		{
			root = root->right;
			return 2;
		}
		else if (root->right == NULL) //chi co con trai
		{
			root = root->left;
			return 2;
		}
		else //co ca 2 con
		{
			result = SearchReplace(root->right, temp);//tim nut nho nhat ben phai
			if (result < 2) //neu khong co thay doi chieu cao
				return result; //tra ve khong thay doi chieu cao, khong can can bang
			switch (root->balanceFactor) //xoa nut ben phai, nen can bang lai
			{
			case -1: //th lech phai
				root->balanceFactor = 0; //cay can bang, nhung thay doi chieu cao
				return 2; //tra ve co thay doi chieu cao
			case 0: //th can bang
				root->balanceFactor = 1; //do chieu cao 2 nut bang nhau, xoa nut phai khong anh huong chieu cao, nhung lech trai 
				return 1; //khong thay doi chieu cao
			case 1: //th lech trai
				return BalanceLeft(root); //gay mat can bang, can bang lai, tra ve gia tri thay doi chieu cao
			}
		}
		delete temp; //xoa bo nho nut can xoa
		return result;
	}
}

void CayNhiPhan::DeleteAll(PTRVatTu& root)
{
	if(root != NULL)
	{
		DeleteAll(root->left);
		DeleteAll(root->right);
		delete root;
	}
}

int CayNhiPhan::SearchReplace(PTRVatTu& root, PTRVatTu& vatTu)
{
	int result;
	if (root->left != NULL) //tim nut nho nhat ben phai
	{
		result = SearchReplace(root->left, vatTu);
		if (result < 2) //khong co thay doi ve chieu cao
			return result;
		switch (root->balanceFactor)
		{
		case 1: //TH lech trai, xoa nut ben trai thi cay can bang lai
			root->balanceFactor = 0;
			return 2; //tra ve tin hieu chieu cao thay doi (2)
		case 0: //TH cay me can bang, xoa nut van con nut phai => chieu cao khong doi
			root->balanceFactor = -1;
			return 1; //khong thay doi chieu cao, do 2 node con bang chieu cao
		case -1: //Th cay me lech phai, cay mat can bang
			return BalanceRight(root); //can bang lai cay, tra ve xem chieu cao thay doi (2 = co; 1 = khong)
		}
	}
	else // tim duoc nut cuoi
	{
		strcpy(vatTu->maVT, root->maVT);
		vatTu = root;
		root = root->right; //di chuyen thong tin cua nut thay the
		return 2; //tra ve co thay doi chieu cao (2)
	}
	return result;
}

int CayNhiPhan::UpdateNode(PTRVatTu &Change, VatTu info)
{
	Change->info = info;
	return 1;
}

ListVatTu CayNhiPhan::GetFirstListVatTu()
{
	return this->first;
}

ListVatTu CayNhiPhan::GetLastListVatTu()
{
	return this->last;
}
