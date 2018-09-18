// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)   // предполагается, что len - это не индекс, а количество
{
    BitLen = len;
    MemLen = ((len)/((sizeof(TELEM))*8));  // для ровно 32 бит (и кратных чисел) длина массива - 1.
    if ((len)%((sizeof(TELEM))*8) > 0)  // если количество больше или меньше чисел, кратных 32, то добавляем ещё ячейку.
    {
        MemLen++;
    }
    TELEM * pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    TELEM * pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)  // копируем по одному элементы динамического массива
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
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
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
  //return 0;
}

void TBitField::SetBit(const int n) // установить бит
{
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    TELEM[memindex] = TELEM[memindex] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    mask = ~mask;
    TELEM[memindex] = TELEM[memindex] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int memindex = GetMemIndex(n);
    int mask = GetMemMask(n);
    return TELEM[memindex] & mask;
  //return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        TELEM * pMem = new TELEM[MemLen];
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
                if (GetBit(i) != bf.GetBit(i)
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
                if (GetBit(i) != bf.GetBit(i)
                    return 1;
            }

            return 0; // вернет 1 в том случае, если всё совпало

        }
    }
    return 1; // если что-то не равно
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen >= bf.BitLen)     // создаем объект с наибольшей длиной
        TBitField tmp(BitLen);
    else
        TBitField tmp(bf.BitLen);

    for (int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i) || bf.GetBit(i))
            tmp.SetBit(i);
    }

    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen >= bf.BitLen)     // создаем объект с наибольшей длиной
        TBitField tmp(BitLen);
    else
        TBitField tmp(bf.BitLen);

    for (int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i) && bf.GetBit(i))
            tmp.SetBit(i);
    }

    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i))
            ClrBit(i);
        else
            SetBit(i);
    }
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
