// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw "";
	BitLen = len;
	MemLen = (len) / (8 * sizeof(TELEM)) + 1;  
	pMem = new TELEM[MemLen];
	if (pMem != 0)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != 0)
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}

}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (8 * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM tmp = 1;
	return tmp << (n % (8 * sizeof(TELEM))); //что за 32???
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		pMem[i] = pMem[i] | GetMemMask(n);
	}
	else throw "  "; // нужно что-то напсиать!!!
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		pMem[i] = pMem[i] & ~GetMemMask(n);
	}
	else throw  "   ";// Нужно НАПИСАТЬ ЧТО_ТО!!!
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		return (pMem[i] & GetMemMask(n)) >> (n % 16);
	}
	else throw "  ";// Нужно НАПИСАТЬ ЧТО_ТО!!!
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (pMem != bf.pMem)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
		
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i]) return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((*this) == bf) return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int resLen = BitLen;
	if (bf.BitLen > BitLen) resLen = bf.BitLen;
	TBitField res(resLen);
	for (int i = 0; i < bf.MemLen; i++) {
		res.pMem[i] = pMem[i];
	}
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] |= bf.pMem[i];
	}
	return res;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int resLen = BitLen;
	if (bf.BitLen > BitLen) resLen = bf.BitLen;
	TBitField res(resLen);
	for (int i = 0; i < bf.MemLen; i++) {
		res.pMem[i] = pMem[i];
	}
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] &= bf.pMem[i];
	}
	return res;

}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < BitLen; i++)
		if ((tmp).GetBit(i)) tmp.ClrBit(i);
		else tmp.SetBit(i);
	return tmp;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	istr >> i;
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
