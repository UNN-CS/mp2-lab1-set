// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = int((len - 1) / (sizeof(TELEM) * 8)) + 1;
		pMem = new TELEM[MemLen];
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= BitLen)
		throw range_error("out of range");
	return n / (8 * sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= BitLen)
		throw range_error("out of range");
	return 1 << (n % (8 * sizeof(TELEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen || n < 0)
		throw range_error("out of range with try to set bit");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen || n < 0)
		throw range_error("out of range with try to clear bit");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0)
		throw range_error("out of range with try to get bit");
	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0) ? 0 : 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
	}
	return *this;
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
	for (int i = 0; i < BitLen / (sizeof(TELEM) * 8); i++)
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
	return (*this == bf) == 0 ? 1 : 0;
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
		if (GetBit(i) == 0 && bf.GetBit(i) == 0)
		{
			t.ClrBit(i);
		}
		else
		{
			t.SetBit(i);
		}
	}
	return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int blmax = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int blmin = BitLen > bf.BitLen ? bf.BitLen : BitLen;
	TBitField t(blmax);
	int i = 0;
	for (; i < blmin; ++i)
	{
		if (GetBit(i) == 1 && bf.GetBit(i) == 1)
		{
			t.SetBit(i);
		}
		else
		{
			t.ClrBit(i);
		}
	}
	for (; i < blmax; ++i)
	{
		t.ClrBit(i);
	}
	return t;
}

TBitField TBitField::operator~(void) // отрицание
{
	//for (int i = 0; i < MemLen - 1; ++i)
	//{
	//	pMem[i] = ~pMem[i];
	//}
	TBitField t(BitLen);
	for (int i = 0; i < BitLen; ++i)
	{
		if (GetBit(i))
		{
			t.ClrBit(i);
		}
		else
		{
			t.SetBit(i);
		}
	}
	return t;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int l = bf.GetLength();
	char *input = new char[l + 1];
	for (int i = 0; i < l + 1; ++i)
		input[i] = 0;
	cin.getline(input, l + 1);
	for (int i = 0; i < l; ++i)
	{
		if (input[i] == '0')
		{
			bf.ClrBit(i);
		}
		else if (input[i] == '1')
		{
			bf.SetBit(i);
		}
		else {
			bf.ClrBit(i);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int l = bf.GetLength();
	for (int i = 0; i < l; i++)
	{
		cout << bf.GetBit(i);
	}
	return ostr;
}
