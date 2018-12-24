// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) throw - 1;
	BitLen = len;
	MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
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
	return n >> sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n - sizeof(TELEM)*GetMemIndex(n));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else throw - 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else throw - 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else throw - 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		if (pMem != NULL) delete[]pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	}
	else throw - 1;
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			res = 0; break;
		}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 0;
	if (BitLen != bf.BitLen) res = 1;
	else for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			res = 1; break;
		}
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = bf.BitLen;
	if (BitLen > len) len = BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++) tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	(BitLen > bf.BitLen) ? len = BitLen : len = bf.BitLen;
	TBitField tmp(len);
	int minlen;
	(bf.BitLen < BitLen) ? minlen = bf.BitLen : minlen = BitLen;
	for (int i = 0; i<minlen; i++)
		if ((GetBit(i)) & (bf.GetBit(i)))
			tmp.SetBit(i);
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < tmp.BitLen; i++)
		if (GetBit(i) == 0) tmp.SetBit(i);
		else tmp.ClrBit(i);
		return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char ch;
	do {
		istr >> ch;
	} while (ch != ' ');
	while (1) {
		istr >> ch;
		if (ch == '0') bf.ClrBit(i++);
		else if (ch == '1') bf.SetBit(i++);
		else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int n = bf.GetLength();
	for (int i = 0; i < n; i++)
	{
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
	}
	return ostr;
}
