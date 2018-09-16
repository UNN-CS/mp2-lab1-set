// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len): BitLen(len)
{
	MemLen = (len / sizeof(TELEM) + 1);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{	
	if (&bf != NULL) {
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0, i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << (n % (sizeof(TELEM)) * 8);
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
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) 
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		if (pMem != NULL) delete []pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else for (int i = 0; i < MemLen; i++)
		if (pMem != bf.pMem) 
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
		if (pMem != bf.pMem)
		{
			res = 1; break;
		}
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	if (BitLen > bf.BitLen) len = Bitlen;
	else len = bf.BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++) tmp.bMem[i] = bMem[i];
	for (int i = 0; i < bf.MemLen; i++) tmp.bMem[i] |= bf.bMem;
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	if (BitLen > bf.BitLen) len = Bitlen;
	else len = bf.BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++) tmp.bMem[i] = bMem[i];
	for (int i = 0; i < bf.MemLen; i++) tmp.bMem[i] &= bf.bMem;
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++) tmp.pMem[i] = ~bMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
