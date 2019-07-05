#pragma once
#include "Header.h"
#include "Design.h"

using namespace std;

class CayNhiPhan
{
private:
	PTRVatTu cayVatTu = NULL;
	int soLoaiVatTu;
	ListVatTu first;
	ListVatTu last;
public:
	void RotateRight(PTRVatTu& root); //xoay don TH left - left
	void RotateLeft(PTRVatTu& root); //xoay don TH right - right
	void RotateLeftRight(PTRVatTu& root); // xoay kep TH left - right
	void RotateRightLeft(PTRVatTu& root); // xoay kep TH right - left
	
	int BalanceLeft(PTRVatTu& root);
	int BalanceRight(PTRVatTu& root);
	
	int CheckVatTu(PTRVatTu vatTu);
	PTRVatTu CreateNodesVT(VatTu info, char maVT[11]);
	
	int InsertList(VatTu info, char maVT[11]);
	void InsertListFirst(VatTu info, char maVT[11]);
	int InsertListRight(ListVatTu nodePos,VatTu info, char maVT[11]);
	int InsertListLeft(ListVatTu nodePos, VatTu info, char maVT[11]);
	int DeleteListFirst();
	int DeleteListNode(ListVatTu nodePos);
	void DeleteAllList();
	void ResetList();
	
	void TraverseToList();
	void TraversRecursive(PTRVatTu root); // ham de quy cho TraverseToList
	
	int InsertOrder(VatTu info, char maVT[11]);
	int InsertRecursive(PTRVatTu& root, PTRVatTu newVatTu);
	
	int DeleteNode(char maVT[11]);
	int DeleteRecursive(PTRVatTu& root, char maVT[11]);
	
	void DeleteAll(PTRVatTu& root);
	int SearchReplace(PTRVatTu& root, PTRVatTu& vatTu);
	
	int UpdateNode(PTRVatTu &Change, VatTu info);
	
	ListVatTu GetFirstListVatTu(); 
	ListVatTu GetLastListVatTu();
	
	PTRVatTu Search(char maVT[11]);
	PTRVatTu GetPTRVatTu();
	
	int GetSoLoaiVatTu();
	void SetPTRVatTu(PTRVatTu value);
	void SetPTRRecursive(PTRVatTu value);
	CayNhiPhan();
	~CayNhiPhan();
};
