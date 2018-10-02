// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����

#include "tbitfield.h"
TBitField::TBitField(int len)
{
	if (len < 0) throw "Negative Length";
	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	if (pMem != 0)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // ����������� �����������
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != 0)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // ������ ��� ��� ���� n
{ 
		return (n >> 5);
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
		return 1 << (n & 31);
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
	if ((n > -1) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		pMem[i] = pMem[i] | GetMemMask(n);
	}
	else
		throw "Invalid Index";
}

void TBitField::ClrBit(const int n) // �������� ���
{
	if ((n > -1) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		pMem[i] = pMem[i] & ~GetMemMask(n);
	}
	else
		throw  "Invalid Index";
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
	if ((n > -1) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		return (pMem[i] & GetMemMask(n)) >> (n % 16);
	}
	else
		throw "Invalid Index";
	return 0;
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField &bf) // ������������
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL)
			delete[]pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // ���������
{
	int res= 1; 
	int i = 0;
	if (BitLen == bf.BitLen)
	{
		while ((pMem[i] == bf.pMem[i]) && (i < MemLen))
			i++;
	}
	else res = 0;
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // ���������
{
	int n = 0;
	if (BitLen != bf.BitLen)
		n = 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				n = 1;
				break;
			}
	return n;
}

TBitField TBitField::operator|(const TBitField &bf) // �������� "���"
{
	int len = BitLen;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // �������� "�"
{
	int len = BitLen;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	for (int i = bf.BitLen; i < BitLen; i++)
		tmp.ClrBit(i);
	return tmp;
}

TBitField TBitField::operator~(void) // ���������
{
	TBitField ty(BitLen);
	for (int i = 0; i < MemLen; i++)
		ty.pMem[i] = ~pMem[i];
	return ty;
}

// ����/�����

istream &operator>>(istream &istr, TBitField &bf) // ����
{
	int i = 0;
	char ch;
	do { istr >> ch; } while (ch != ' ');
	while (1)
	{
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else if (ch == '1')
			bf.SetBit(i++);
		else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // �����
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
		return ostr;
}