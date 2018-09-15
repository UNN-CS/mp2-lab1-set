// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = int((len - 1) / (sizeof(TELEM) * 8)) + 1;
	pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if(this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		memcpy(bf.pMem, pMem, MemLen * sizeof(TELEM));
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
	return 1 << (n % (8 * sizeof(TELEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0) ? 0 : 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		TBitField::BitLen = bf.BitLen;
		TBitField::MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		memcpy(bf.pMem, TBitField::pMem, TBitField::MemLen * sizeof(TELEM));
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (this == &bf)
	{
		return 1;
	}
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	int r;
	r = memcmp(pMem, bf.pMem, (BitLen - 1) * sizeof(TELEM));
	if (r == 0)
	{
		return 0;
	}
	TELEM m = 1;
	for (int i = 0; i < BitLen / (sizeof(TELEM) * 8) ; i++)
	{
		if (m & pMem[MemLen - 1] != m & bf.pMem[MemLen - 1])
		{
			return 0;
		}
		m <<= 1;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (this == &bf)
	{
		return 0;
	}
	if (BitLen != bf.BitLen)
	{
		return 1;
	}
	int r;
	r = memcmp(pMem, bf.pMem, (BitLen - 1) * sizeof(TELEM));
	if (r == 0)
	{
		return 1;
	}
	TELEM m = 1;
	for (int i = 0; i < BitLen / (sizeof(TELEM) * 8); i++)
	{
		if (m & pMem[MemLen - 1] != m & bf.pMem[MemLen - 1])
		{
			return 1;
		}
		m <<= 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
