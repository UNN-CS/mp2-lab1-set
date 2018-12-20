// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define sizeMem (sizeof(TELEM)*8)

TBitField::TBitField(int len) : BitLen(len)
{
	if (len < 0) throw "Subzero win";
	!(len % (sizeMem)) ? MemLen = len / sizeMem : MemLen = (len / sizeMem) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) : BitLen(bf.BitLen), MemLen(bf.MemLen) // конструктор копирования
{
	pMem = new TELEM[MemLen];
	if (MemLen != 0)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0) throw "Subzero win";
	if (MemLen * 32 < n) throw "Sooooo far away";
	return n / sizeMem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % sizeMem);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen)) throw "Subzero or soooo far away";
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen)) throw "Subzero or soooo far away";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen)) throw "Subzero or soooo far away";
	return pMem[GetMemIndex(n)] & GetMemMask(n) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (*this == bf)
		return *this;

	if (BitLen > 0) delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen; i++)
		if (bf.pMem[i] != pMem[i]) return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int max_BitLen = bf.BitLen > BitLen ? bf.BitLen : BitLen;
	TBitField tmp(max_BitLen);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxLen = bf.BitLen > BitLen ? bf.BitLen : BitLen,
		minLen = BitLen + bf.BitLen - maxLen;
	int minMem = bf.BitLen > BitLen ? bf.MemLen : MemLen;
	TBitField tmp(maxLen);
	for (int i = 0; i < minMem; i++)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];
	int last_index_begin = (sizeMem * (minMem - 1));
	for (int i = last_index_begin; i < minLen; i++)
		(this->GetBit(i) && bf.GetBit(i)) ? tmp.SetBit(i) : tmp.ClrBit(i);
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < MemLen - 1; i++)
		tmp.pMem[i] = ~pMem[i];
	for (int i = ((MemLen - 1) * sizeMem); i < BitLen; i++)
		GetBit(i) ? tmp.ClrBit(i) : tmp.SetBit(i);
	return tmp;
}

// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	char in;
	int i = 0;
	while (i < bf.BitLen)
	{
		istr >> in;
		if (in == '0') bf.ClrBit(i);
		else if (in == '1') bf.SetBit(i);
		else return istr;
		i++;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
