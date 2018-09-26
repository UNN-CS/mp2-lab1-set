// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "C:\Users\1\Documents\Visual Studio 2015\Projects\mp2-lab1-set\include\tbitfield.h"


TBitField::TBitField(int len)   // предполагается, что len - это не индекс, а количество
{
	if (len < 0) throw "negative length";
    BitLen = len;
    MemLen = ((len)/((sizeof(TELEM))*8));  // для ровно 32 бит (и кратных чисел) длина массива - 1.
    if ((len)%((sizeof(TELEM))*8) > 0)  // если количество больше или меньше чисел, кратных 32, то добавляем ещё ячейку.
    {
        MemLen++;
    }
    pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField() // конструктор по умолчанию
{
	BitLen = 0;
	MemLen = 0;
	pMem = NULL;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)  // копируем по одному элементы динамического массива
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
	pMem = NULL;
    BitLen = 0;
    MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int SizeOfTelem = sizeof(TELEM)*8; // в битах
    return n / SizeOfTelem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int number = n % (sizeof(TELEM)*8); // порядок бита в маске
    TELEM mask = 0;
    mask = 1 << number;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
  //return 0;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) throw "negative index";
	if (n > BitLen) throw "too large index";
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    pMem[memindex] = pMem[memindex] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw "negative index";
	if (n > BitLen) throw "too large index";
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    mask = ~mask;
    pMem[memindex] = pMem[memindex] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw "negative index";
	if (n > BitLen) throw "too large index";
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    return pMem[memindex] & mask;
  //return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)  // копируем по одному элементы динамического массива
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    // последний элемент массива нужно сравнивать побитово
    if (BitLen == bf.BitLen)  // если равна длина в битах
    {
        if (MemLen == bf.MemLen) // если совпадает кол-во ячеек
        {
            for (int i = 0; i < MemLen - 2; i++) // проверяем все ячейки, кроме последней (memlen - это количество, а не индекс)
            {
                if (pMem[i] != bf.pMem[i]) // если какая-то ячейка не совпала
                    return 0;
            }

            for (int i = BitLen - 1; i > BitLen - ((BitLen - 1) % (sizeof(TELEM)*8 * BitLen / (sizeof(TELEM)*8))) ; i--) // проходим по битам последнего элемента массива, начиная со старшего
            {
                if (GetBit(i) != bf.GetBit(i))
                    return 0;
            }

            return 1; // вернет 1 в том случае, если всё совпало

        }
    }
    return 0; // если что-то не равно
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    // как operator==, но наоборот
    if (BitLen == bf.BitLen)  // если равна длина в битах
    {
        if (MemLen == bf.MemLen) // если совпадает кол-во ячеек
        {
            for (int i = 0; i < MemLen - 2; i++) // проверяем все ячейки, кроме последней (memlen - это количество, а не индекс)
            {
                if (pMem[i] != bf.pMem[i]) // если какая-то ячейка не совпала
                    return 1;
            }

            for (int i = BitLen - 1; i > BitLen - ((BitLen - 1) % (sizeof(TELEM)*8 * BitLen / (sizeof(TELEM)*8))) ; i--) // проходим по битам последнего элемента массива, начиная со старшего
            {
                if (GetBit(i) != bf.GetBit(i))
                    return 1;
            }

            return 0; // вернет 1 в том случае, если всё совпало

        }
    }
    return 1; // если что-то не равно
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int max;

    if (BitLen >= bf.BitLen)     // создаем объект с наибольшей длиной
        max = BitLen;
    else
        max = bf.BitLen;

    TBitField tmp(max);
	tmp.BitLen = max;

    for (int i = 0; i < MemLen; i++)
    {
       // if (GetBit(i) || bf.GetBit(i))
       //     tmp.SetBit(i);

		tmp.pMem[i] = pMem[i];
    }

	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}

    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int max;

    if (BitLen >= bf.BitLen)     // создаем объект с наибольшей длиной
        max = BitLen;
    else
        max = bf.BitLen;

    TBitField tmp(max);
	tmp.BitLen = max;

    for (int i = 0; i < MemLen; i++)
    {
       // if (GetBit(i) && bf.GetBit(i))
       //     tmp.SetBit(i);
		tmp.pMem[i] = pMem[i];
    }

	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}

    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);

    for (int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i))
            tmp.ClrBit(i);
        else
            tmp.SetBit(i);
    }
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int bit;

    for (int i = 0; i < bf.BitLen; i++)
    {
        cin >> bit;
        if (bit)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        cout << bf.GetBit(i);
    }
    cout << endl;

    return ostr;
}
