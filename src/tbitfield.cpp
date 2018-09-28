// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "../include/tbitfield.h"
#include<cmath>

TBitField::TBitField(int len)
{
	if (len < 0)
		throw new bad_alloc;

	MemLen = ceil(static_cast<double>(len) / (sizeof(TELEM) * 8));
	BitLen = len;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];

	for (int i = MemLen - 1; i >= 0; i--)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	try
	{
		delete[] pMem;
	}
	catch (const exception&)
	{
		pMem = 0;
	}
	MemLen = BitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n > BitLen)
		throw "Unexpected bit index";
	else if (n != 0)
		return MemLen - ceil(static_cast<double>(n) / (sizeof(TELEM) * 8));
	else
		return MemLen - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen)
		throw "Unexpected bit index";
	else
		return 1 << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen)
		throw "Unexpected bit index";
	else if (GetBit(n) != 1)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen)
		throw "Unexpected bit index";
	else if (GetBit(n) != 0)
		pMem[GetMemIndex(n)] ^= GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen)
		throw "Unexpected bit index";
	else
		return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator = (const TBitField &bf) // присваивание
{
	if (bf.MemLen == 0)
		throw "Unxcpected bit field length";
	else
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];

		for (int i = MemLen - 1; i >= 0; i--)
		{
			pMem[i] = bf.pMem[i];
		}

		return *this;
	}
}

int TBitField::operator == (const TBitField &bf) const // сравнение
{
	if (bf.MemLen == 0)
		throw "Unxcpected bit field length";
	else
	{
		bool check = 1;
		int length;

		if (BitLen >= bf.BitLen)
		{
			length = bf.MemLen - 1;
			for (int i = MemLen - 1; i >= bf.MemLen - 1; i--, length--)
			{
				check &= pMem[i] == bf.pMem[length];
			}
		}
		else
		{
			length = MemLen - 1;
			for (int i = bf.MemLen - 1; i >= MemLen - 1; i--, length--)
			{
				check &= pMem[length] == bf.pMem[i];
			}
		}

		return check;
	}
}

int TBitField::operator != (const TBitField &bf) const // сравнение
{
	return !(operator==(bf));
}

TBitField TBitField::operator | (const TBitField &bf) // операция "или"
{
	if (bf.MemLen == 0)
		throw "Unxcpected bit field length";
	else
	{
		if (BitLen >= bf.BitLen)
		{
			TBitField tempBF(BitLen);

			int j = bf.MemLen - 1;
			for (int i = MemLen - 1; i >= bf.MemLen - 1; i--, j--)
				tempBF.pMem[i] = bf.pMem[j];
			for (int i = MemLen - 1; i >= 0; i--)
				tempBF.pMem[i] |= pMem[i];

			return tempBF;
		}
		else
		{
			TBitField tempBF(BitLen);

			int j = MemLen - 1;
			for (int i = bf.MemLen - 1; i >= MemLen - 1; i--, j--)
				tempBF.pMem[i] = pMem[j];
			for (int i = MemLen - 1; i >= 0; i--)
				tempBF.pMem[i] |= bf.pMem[i];

			return tempBF;
		}
	}
}

TBitField TBitField::operator & (const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~ (void) // отрицание
{
	TBitField tempBF(BitLen);
	TELEM mask = 0;

	for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
		mask += GetMemMask(i);
	tempBF.pMem[0] = pMem[0] ^ mask;

	for (int i = MemLen - 1; i > 0; i--)
		tempBF.pMem[i] = ~pMem[i];

	return tempBF;
}

// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	int length;

	cout << "Input bit field length: ";
	istr >> length;

	TBitField tempBF(length);

	for (int i = 0; i < tempBF.BitLen; i++)
	{
		int bit;
		istr >> bit;

		if (bit == 0)
			tempBF.ClrBit(i);
		else if (bit == 1)
			tempBF.SetBit(i);
		else
			throw "Unxepected bit value";
	}

	bf = tempBF;

	return istr;
}

ostream &operator << (ostream &ostr, const TBitField &bf) // вывод
{
	ostr << "Bit field length: " << bf.BitLen << endl;
	ostr << "Bit field TELEM count: " << bf.MemLen << endl;

	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);

	ostr << endl;

	return ostr;
}