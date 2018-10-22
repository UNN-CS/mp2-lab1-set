// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	try
	{
		if (len <= 0)
			throw 1;
		BitLen = len;

		int reckon = len / (sizeof(TELEM)* 8); // Деление на количество бит в одном телеме
		if (reckon == 0) // Выделяем один телем
			MemLen = 1;
		else
		{
			if (len % (sizeof(TELEM)* 8) == 0) // Проверка на остаток
				MemLen = reckon;
			else
				MemLen = reckon + 1; // Добавляем телем для остатка
		}
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) //Заполняем нулями
			pMem[i] = 0;
	}
	catch (int error)
	{
		cout << "Len can't be less 1" << endl;
		throw 1;
	}
}

TBitField::TBitField(const TBitField &bf) // Конструктор копирование
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const 
{
	int temp = n / (sizeof(TELEM)* 8);  
	return n - temp*(sizeof(TELEM)*8); 
		
}

TELEM TBitField::GetMemMask(const int n) const 
{
			return 1 << (GetMemIndex(n) - 1);
}

// Доступы

int TBitField::GetLength(void) const 
{
	return BitLen;
}

void TBitField::SetBit(const int n) 
{
	try
	{
		if (n < 0) throw 1;
		if (n > BitLen) throw 3;

		TELEM mask = GetMemMask(n);
		int Mem = n / (sizeof(TELEM)*8); 
		pMem[Mem] = pMem[Mem] | mask;
		
	}
	catch (int error)
	{ 
		if (error == 1)
		{
			cout << "n can't be less 0" << endl;
			throw 1;
		}
		else if (error == 3)
		{
			cout << "n can't be more BitLen" << endl;
			throw 3;
		}
	}
}

void TBitField::ClrBit(const int n) 
{
	try
	{
		if (n < 0) throw 1;
		if (n > BitLen) throw 3;

		TELEM mask = ~GetMemMask(n);
		int Mem = n / (sizeof(TELEM)* 8); 

		pMem[Mem] = pMem[Mem] & mask;

	}
	catch (int error)
	{
		if (error == 1)
		{
			cout << "n can't be less 0" << endl;
			throw 1;
		}
		else if (error == 3)
		{
			cout << "n can't be more BitLen" << endl;
			throw 3;
		}
	}
}

int TBitField::GetBit(const int n) const 
{
	try
	{
		if (n < 0) throw 1;
		if (n > BitLen) throw 3;

		int mask = GetMemMask(n);
		int Mem = n / (sizeof(TELEM)* 8);
		int index = GetMemIndex(n);
		return ((pMem[Mem] & mask) >> (index - 1));
	}
	catch (int error)
	{
		if (error == 1)
		{
			cout << "n can't be less 0" << endl;
			throw 1;
		}
		else if (error == 3)
		{
			cout << "n can't be more BitLen" << endl;
			throw 3;
		}
	}
}

// Битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // Присваивание
{
	if (this != &bf)
	{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // Сравнение
{
	if (this == &bf)
		return 1;
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < BitLen; i++)
	if (this->GetBit(i) != bf.GetBit(i))
		return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // Сравнение
{
	if (this == &bf)
		return 0;
	if (BitLen != bf.BitLen)
		return 1;
	for (int i = 0; i < BitLen; i++)
	if (this->GetBit(i) != bf.GetBit(i))
		return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // Операция "или"
{
	TBitField result((BitLen > bf.BitLen) ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i] | bf.pMem[i];
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // Операция "и"
{
	TBitField result((BitLen > bf.BitLen) ? BitLen : bf.BitLen);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i] & bf.pMem[i];
	return result;
}

TBitField TBitField::operator~(void) // Отрицание
{
	TBitField temp(*this);
	for (int i = 0; i < BitLen; i++)
	{
		if (!GetBit(i))
			temp.SetBit(i);
		else
			temp.ClrBit(i);
	}
	return temp;
}

// Ввод/Вывод

istream &operator>>(istream &istr, TBitField &bf)
{
	int temp;

	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> temp;

		if (temp == 1)
		{
			bf.SetBit(i);
		}
		else
		{
			bf.ClrBit(i);
		}
	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf)
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);

	ostr << endl;

	return ostr;
}