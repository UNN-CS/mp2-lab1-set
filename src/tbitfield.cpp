// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) //количество битов  //
{
	if (len < 0)  throw (-1);  //negative lengh
	BitLen = len;
	// (len % (8 * sizeof(TELEM)) == 0) ? MemLen = len / (8*sizeof(TELEM)) : MemLen = len / (8 * sizeof(TELEM)) + 1; //set MemLen
	if (BitLen % (8 * sizeof(TELEM)) == 0)
	{
		MemLen = len / (8 * sizeof(TELEM));
	}
	else
	{
		MemLen = (len / (8 * sizeof(TELEM))) +1;
	}

	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) 
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (&bf != this)
		{
			/*delete[] pMem; //очистка исходного объекта
			pMem = NULL;*/
			BitLen = bf.BitLen; MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];// создать новый массив
			for (int i = 0; i < MemLen; i++)
			{
				pMem[i] = *(bf.pMem + i);//копируем
			}
		}
}

TBitField::~TBitField()
{
	delete[] pMem;// освобождаем память массива
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t = 1;
	return t << n % (sizeof(TELEM) * 8);// биты нумеруем с нуля
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0)||(n>BitLen)) throw (-2);//NegativeIndex
	int i = this->GetMemIndex(n);//index pMem
	//if (this->GetMemMask(n) * this->pMem[i] == 0) this->pMem[i] += this->GetMemMask(n); //а не включен ли уже бит?
	this->pMem[i]  |= this->GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) throw (-1); //NegativeIndex
	int i = GetMemIndex(n);//index pMem
	//if (this->GetMemMask(n) * this->pMem[i] != 0) this->pMem[i] -= this->GetMemMask(n); 
	pMem[i] = pMem[i] & (~GetMemMask(n));

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen)) throw (-2); //NegativeIndex
	int i = this->GetMemIndex(n);//index pMem
	if ((GetMemMask(n) * pMem[i]) == 0)  return 0;
	return 1;
	//return this->GetMemMask(n) * this->pMem[i];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание   (объект уже был создан)
{                                                           
	if (&bf != this) //////??? одинаковые длины заносить будем? ?????????????????????????????????????????
	{
		delete[] pMem; //очистка исходного объекта
		pMem = NULL;
		BitLen = bf.BitLen; MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];// создать новый массив
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = *(bf.pMem + i);//копируем
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{/*
	if (BitLen != bf.BitLen)
		return 0;
	else
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 0;
		}
	return 1;
	*/
	if (BitLen != bf.BitLen)
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i)) return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int MaxBitLen;
	(BitLen > bf.BitLen)? MaxBitLen = BitLen : MaxBitLen = bf.BitLen;
	TBitField t(MaxBitLen);
	for (int i = 0; i < MemLen; i++)
	{
		t.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		t.pMem[i] |= bf.pMem[i];
	}
	return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int MaxBitLen;
	(BitLen > bf.BitLen) ? MaxBitLen = BitLen : MaxBitLen = bf.BitLen;
	TBitField t(MaxBitLen);
		
	for (int i = 0; i < MemLen; i++)
	{
		t.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		t.pMem[i] &= bf.pMem[i];
	}
	return t;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < temp.BitLen; i++)
	{
		if (GetBit(i) == 0)
			temp.SetBit(i);
		else
			temp.ClrBit(i);
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char bit;
	while (i < bf.BitLen)
	{
		istr >> bit;
		if (bit == '0') bf.ClrBit(i);
		else if (bit == '1') bf.SetBit(i);
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
