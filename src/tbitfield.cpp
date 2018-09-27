// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����

#include "tbitfield.h"


TBitField::TBitField(int len)   // ��������������, ��� len - ��� �� ������, � ����������
{
	if (len < 0) throw "negative length";
    BitLen = len;
    MemLen = ((len)/((sizeof(TELEM))*8));  // ��� ����� 32 ��� (� ������� �����) ����� ������� - 1.
    if ((len)%((sizeof(TELEM))*8) > 0)  // ���� ���������� ������ ��� ������ �����, ������� 32, �� ��������� ��� ������.
    {
        MemLen++;
    }
    pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField() // ����������� �� ���������
{
	BitLen = 0;
	MemLen = 0;
	pMem = NULL;
}

TBitField::TBitField(const TBitField &bf) // ����������� �����������
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)  // �������� �� ������ �������� ������������� �������
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
	pMem = NULL;
    BitLen = 0;
    MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // ������ ��� ��� ���� n
{
    int SizeOfTelem = sizeof(TELEM)*8; // � �����
    return n / SizeOfTelem;
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
    int number = n % (sizeof(TELEM)*8); // ������� ���� � �����
    TELEM mask = 0;
    mask = 1 << number;
	return mask;
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
  return BitLen;
  //return 0;
}

void TBitField::SetBit(const int n) // ���������� ���
{
	if (n < 0) throw "negative index";
	if (n > BitLen) throw "too large index";
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    pMem[memindex] = pMem[memindex] | mask;
}

void TBitField::ClrBit(const int n) // �������� ���
{
	if (n < 0) throw "negative index";
	if (n > BitLen) throw "too large index";
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    mask = ~mask;
    pMem[memindex] = pMem[memindex] & mask;
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
	if (n < 0) throw "negative index";
	if (n > BitLen) throw "too large index";
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    return pMem[memindex] & mask;
  //return 0;
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField &bf) // ������������
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)  // �������� �� ������ �������� ������������� �������
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // ���������
{
    // ��������� ������� ������� ����� ���������� ��������
    if (BitLen == bf.BitLen)  // ���� ����� ����� � �����
    {
        if (MemLen == bf.MemLen) // ���� ��������� ���-�� �����
        {
            for (int i = 0; i < MemLen - 2; i++) // ��������� ��� ������, ����� ��������� (memlen - ��� ����������, � �� ������)
            {
                if (pMem[i] != bf.pMem[i]) // ���� �����-�� ������ �� �������
                    return 0;
            }

            for (int i = BitLen - 1; i > BitLen - ((BitLen - 1) % (sizeof(TELEM)*8 * BitLen / (sizeof(TELEM)*8))) ; i--) // �������� �� ����� ���������� �������� �������, ������� �� ��������
            {
                if (GetBit(i) != bf.GetBit(i))
                    return 0;
            }

            return 1; // ������ 1 � ��� ������, ���� �� �������

        }
    }
    return 0; // ���� ���-�� �� �����
}

int TBitField::operator!=(const TBitField &bf) const // ���������
{
    // ��� operator==, �� ��������
    if (BitLen == bf.BitLen)  // ���� ����� ����� � �����
    {
        if (MemLen == bf.MemLen) // ���� ��������� ���-�� �����
        {
            for (int i = 0; i < MemLen - 2; i++) // ��������� ��� ������, ����� ��������� (memlen - ��� ����������, � �� ������)
            {
                if (pMem[i] != bf.pMem[i]) // ���� �����-�� ������ �� �������
                    return 1;
            }

            for (int i = BitLen - 1; i > BitLen - ((BitLen - 1) % (sizeof(TELEM)*8 * BitLen / (sizeof(TELEM)*8))) ; i--) // �������� �� ����� ���������� �������� �������, ������� �� ��������
            {
                if (GetBit(i) != bf.GetBit(i))
                    return 1;
            }

            return 0; // ������ 1 � ��� ������, ���� �� �������

        }
    }
    return 1; // ���� ���-�� �� �����
}

TBitField TBitField::operator|(const TBitField &bf) // �������� "���"
{
    int max;

    if (BitLen >= bf.BitLen)     // ������� ������ � ���������� ������
        max = BitLen;
    else
        max = bf.BitLen;

    TBitField tmp(max);
	tmp.BitLen = max;

    for (int i = 0; i < MemLen; i++)
    {
       // if (GetBit(i) || bf.GetBit(i))
       //     tmp.SetBit(i);

		tmp.pMem[i] = pMem[i];
    }

	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}

    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // �������� "�"
{
    int max;

    if (BitLen >= bf.BitLen)     // ������� ������ � ���������� ������
        max = BitLen;
    else
        max = bf.BitLen;

    TBitField tmp(max);
	tmp.BitLen = max;

    for (int i = 0; i < MemLen; i++)
    {
       // if (GetBit(i) && bf.GetBit(i))
       //     tmp.SetBit(i);
		tmp.pMem[i] = pMem[i];
    }

	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}

    return tmp;
}

TBitField TBitField::operator~(void) // ���������
{
	TBitField tmp(*this);

    for (int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i))
            tmp.ClrBit(i);
        else
            tmp.SetBit(i);
    }
	return tmp;
}

// ����/�����

istream &operator>>(istream &istr, TBitField &bf) // ����
{
    int bit;

    for (int i = 0; i < bf.BitLen; i++)
    {
        cin >> bit;
        if (bit)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // �����
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        cout << bf.GetBit(i);
    }
    cout << endl;

    return ostr;
}
