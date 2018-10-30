// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) throw -1;
	BitLen = len;
    MemLen = BitLen / (8 * sizeof(TELEM));
    if (BitLen % (8 * sizeof(TELEM)) > 0)
        MemLen++;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
		if (pMem == NULL) return;
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen)) throw -1;
	return (n / (8 * sizeof(TELEM)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen)) throw -1;
	return (1 << (n % (sizeof(TELEM) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen)) throw -1;
	pMem[GetMemIndex(n)] |=  GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) throw -1;
	pMem[GetMemIndex(n)] &=  ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen)) throw - 1;
	TELEM result = pMem[GetMemIndex(n)] & GetMemMask(n);
	if (result != 0) return 1;
	else return 0;
}
// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf != this)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        if (pMem != NULL) delete []pMem;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }    
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int minMem;
	if (MemLen > bf.MemLen) minMem = bf.MemLen;
	else minMem = MemLen;
	for (int i = 0; i < minMem; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	if (MemLen > bf.MemLen)
	{
		for (int i = minMem; i < MemLen; i++)
			if (pMem != 0) return 0;
	}
	else
		for (int i = minMem; i < bf.MemLen; i++)
			if (pMem != 0) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (*this == bf)
            return 0;
    return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int Mem, Bit, MinMem;
    TELEM *p = NULL;
    if (BitLen > bf.BitLen)
    {
        Mem = MemLen;
        Bit = BitLen;
        MinMem = bf.MemLen;
        p = pMem;
    }
    else
    {
        Mem = bf.MemLen;
        Bit = bf.BitLen;
        MinMem = MemLen;
        p = bf.pMem;
    }
    TBitField tmp(Bit);
    for (int i = 0; i < MinMem; i++)
    {
        tmp.pMem[i] = pMem[i] | bf.pMem[i];
    }
    for (int i = MinMem; i < Mem; i++)
    {
		tmp.pMem[i] = p[i];
    }
    p = NULL;
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int MinBit;
    if (BitLen > bf.BitLen)
    {
        MinBit = bf.BitLen;
    }
    else
    {
        MinBit = BitLen;
    }
    TBitField tmp(MinBit);
    for (int i = 0; i < tmp.MemLen; i++)
    {
        tmp.pMem[i] = bf.pMem[i] & pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
 	TBitField tmp(BitLen);
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i)) tmp.ClrBit(i);
		else tmp.SetBit(i);
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i = 0;
	char ch;
	do
    {
		istr >> ch;
	}
	while (ch != ' ');
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

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    int len = bf.GetLength();
    for (int i = 0; i++; i < len)
        if (bf.GetBit(i)) ostr << '1';
        else ostr << '0';
    return ostr;
}
