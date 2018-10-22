// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#define k 32

TBitField::TBitField(int len)
{
	if (len < 0) throw - 1;
	else
	{
		BitLen = len;
		if (BitLen%k == 0) MemLen = BitLen / k;
		else MemLen = BitLen / k + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i<MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / k;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	int m = n % k;
	mask = 1 << m;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen)) throw - 1;
	else 
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen)) throw - 1;
	else
	if (pMem[GetMemIndex(n)]) pMem[GetMemIndex(n)] &= ~ GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n<0) || (n>BitLen))
		throw - 1;
	else
	{
		int tmp = pMem[GetMemIndex(n)];
		tmp &= GetMemMask(n);
		if (tmp != 0)
			return 1;
		else return 0;
	}

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
		delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	for (int i = 0; i<BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int i = 0;
	if (bf.BitLen == BitLen)
		while (pMem[i] == bf.pMem[i])
			i++;
	else return 1;
	if (i == MemLen) return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int Max = 0;
	int Min = 0;
	if (BitLen >= bf.BitLen)
	{
		Max = BitLen;
	    Min = bf.BitLen;
	}
	else
	{
		Max = bf.BitLen;
		Min = BitLen;
	}
	TBitField tmp(Max);
	if (Max == BitLen)
		tmp = *this;
	else tmp = bf;

	for (int i = 0; i < Min; i++)
		if ((GetBit(i) || bf.GetBit(i)))
			tmp.SetBit(i);
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{ 
	int Max = 0;
	int Min = 0;
	if (BitLen >= bf.BitLen)
	{
		Max = BitLen;
		Min = bf.BitLen;
	}
	else
	{
		Max = bf.BitLen;
		Min = BitLen;
	}
	TBitField tmp(Max);
	for (int i = 0; i < Min; i++)
		if ((GetBit(i) && bf.GetBit(i)))
			tmp.SetBit(i);
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{ 
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < bf.BitLen))
	{
		bf.SetBit(i);
		istr >> i;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
