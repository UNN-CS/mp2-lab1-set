// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw len;
	else
	{
		BitLen = len;
		MemLen = BitLen / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0)
		throw n;
	else
		return(n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		throw n;
	else
	{
		int n1 = n % (sizeof(int) * 8);
		TELEM mask = 1 << n;
		return mask;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{

	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		int tmp = n;
		pMem[GetMemIndex(tmp)] = pMem[GetMemIndex(tmp)] | GetMemMask(tmp);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int tmp = n;
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		pMem[GetMemIndex(tmp)] &= ~(GetMemMask(tmp));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		int temp = pMem[GetMemIndex(n)];
		temp &= GetMemMask(n);
		if (temp != 0)
			return 1;
		else return 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int n = 0;
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			n = 1;
	}
	return n;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmpsize = 0;
	int n = 0;
	if (BitLen >= bf.BitLen)
	{
		tmpsize = BitLen;
		n = bf.BitLen;
	}
	else
	{
		tmpsize = bf.BitLen;
		n = BitLen;
	}
	TBitField tmp(tmpsize);
	if (tmpsize == BitLen)
		tmp = *this;
	else tmp = bf;

	for (int i = 0; i < n; i++)
		if ((GetBit(i) || bf.GetBit(i)))
			tmp.SetBit(i);
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmpsize = 0;
	int n = 0;
	if (BitLen >= bf.BitLen)
	{
		tmpsize = BitLen;
		n = bf.BitLen;
	}

	else
	{
		tmpsize = bf.BitLen;
		n = BitLen;
	}

	TBitField tmp(tmpsize);
	for (int i = 0; i < n; i++)
		if (GetBit(i) && bf.GetBit(i))
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