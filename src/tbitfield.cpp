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
	if (memcmp(pMem, bf.pMem, (MemLen - 1) * sizeof(TELEM)) == 0)
	{
		return 0;
	}
	TELEM tmpMask = 1;
	for (int i = 0; i < BitLen / (sizeof(TELEM) * 8) ; i++)
	{
		if (tmpMask & pMem[MemLen - 1] != tmpMask & bf.pMem[MemLen - 1])
		{
			return 0;
		}
		tmpMask <<= 1;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
	//if (this == &bf)
	//{
	//	return 0;
	//}
	//if (BitLen != bf.BitLen)
	//{
	//	return 1;
	//}
	//int r;
	//r = memcmp(pMem, bf.pMem, (BitLen - 1) * sizeof(TELEM));
	//if (r == 0)
	//{
	//	return 1;
	//}
	//TELEM m = 1;
	//for (int i = 0; i < BitLen / (sizeof(TELEM) * 8); i++)
	//{
	//	if (m & pMem[MemLen - 1] != m & bf.pMem[MemLen - 1])
	//	{
	//		return 1;
	//	}
	//	m <<= 1;
	//}
	//return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	//int blmax = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int blmin = BitLen > bf.BitLen ? bf.BitLen : BitLen;
	TBitField t = BitLen > bf.BitLen ? *this : bf;
	for (int i = 0; i < blmin; ++i)
	{
		if (GetBit(i) | bf.GetBit(i))
		{
			t.SetBit(i);
		} else
		{
			t.ClrBit(i);
		}
	}
	return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	//int blmax = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int blmin = BitLen > bf.BitLen ? bf.BitLen : BitLen;
	TBitField t = BitLen > bf.BitLen ? *this : bf;
	for (int i = 0; i < blmin; ++i)
	{
		if (GetBit(i) & bf.GetBit(i))
		{
			t.SetBit(i);
		}
		else
		{
			t.ClrBit(i);
		}
	}
	return t;
}

TBitField TBitField::operator~(void) // отрицание
{
	//for (int i = 0; i < MemLen - 1; ++i)
	//{
	//	pMem[i] = ~pMem[i];
	//}
	for (int i = 0; i < BitLen; ++i)
	{
		if (GetBit(i))
		{
			ClrBit(i);
		}
		else
		{
			SetBit(i);
		}
	}
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
