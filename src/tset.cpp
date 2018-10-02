// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tset.cpp - Copyright (c) ������� �.�. 04.10.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ��������� - ���������� ����� ������� ����

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// ����������� �����������
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// ����������� �������������� ����
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField tmp(this->BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
	return  MaxPower;
}

int TSet::IsMember(const int Elem) const // ������� ���������?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
	BitField.ClrBit(Elem);
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet &s) // ������������
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return(*this);
}

int TSet::operator==(const TSet &s) const // ���������
{
	int res = 0;
	if (BitField == s.BitField)
		res = 1;
	return res;
}

int TSet::operator!=(const TSet &s) const // ���������
{
	int res = 0;
	if (BitField != s.BitField)
		res = 1;
	return res;
}

TSet TSet::operator+(const TSet &s) // �����������
{
	return(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
	TSet temp(MaxPower);
	temp = (*this);
	temp.InsElem(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
	TSet temp(MaxPower);
	temp = (*this);
	temp.DelElem(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // �����������
{
	TSet tmp(BitField & s.BitField);
	return tmp;
}

TSet TSet::operator~(void) // ����������
{
	return (~BitField);
}

// ���������� �����/������

istream &operator>>(istream &istr, TSet &s) // ����
{
	int numb;
	for (int i = 0; i < s.MaxPower; i++)
	{
		istr >> numb;
		if ((numb >= 0) && (numb < s.MaxPower))
			s.InsElem(numb);
		else break;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // �����
{
	int i;
	ostr << "{ ";
	for (i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i))
			ostr << i << " ";
	}
	ostr << "}";
	return ostr;
}