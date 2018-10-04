//
// Created by rootreddragon on 9/29/2018.
//


// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"



#include <gtest/gtest.h>



#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
    if (len < 0)
        throw "negative length";
    BitLen = len;
    MemLen = BitLen / BITS_IN_ONE_MEM + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}


TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = BitLen / BITS_IN_ONE_MEM + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n > BitLen))
        throw "Negative bit";
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > BitLen))
        throw "Negative bit";
    pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > BitLen))
        throw "Negative bit";
    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)
        return 0;
    else
        return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (BitLen == bf.BitLen)
    {
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    else
    {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = BitLen / BITS_IN_ONE_MEM + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    else
    {
        int f = 1;
        for (int i = 0; (i < bf.MemLen) && (f); i++)
            if (pMem[i] != bf.pMem[i])
                f = 0;

        return f;
    }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen > bf.BitLen)
    {
        TBitField b(BitLen);
        for (int i = 0; i < bf.MemLen; i++)
            b.pMem[i] = pMem[i] | bf.pMem[i];
        for (int i = bf.MemLen; i < b.MemLen; i++)
            b.pMem[i] = pMem[i];
        return b;
    }
    else
    {
        TBitField b(bf.BitLen);
        for (int i = 0; i < MemLen; i++)
            b.pMem[i] = pMem[i] | bf.pMem[i];
        for (int i = MemLen; i < b.MemLen; i++)
            b.pMem[i] = bf.pMem[i];
        return b;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen > bf.BitLen)
    {
        TBitField b(BitLen);
        for (int i = 0; i < bf.MemLen; i++)
            b.pMem[i] = pMem[i] & bf.pMem[i];
        for (int i = bf.MemLen; i < b.MemLen; i++)
            b.pMem[i] = 0;
        return b;
    }
    else
    {
        TBitField b(bf.BitLen);
        for (int i = 0; i < MemLen; i++)
            b.pMem[i] = pMem[i] & bf.pMem[i];
        for (int i = MemLen; i < b.MemLen; i++)
            b.pMem[i] = 0;
        return b;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField b(BitLen);
    for (int i = 0; i < MemLen - 1; i++)
        b.pMem[i] = ~pMem[i];
    for (int i = ((MemLen - 1) * BITS_IN_ONE_MEM); i < BitLen; i++)
        if (GetBit(i) == 0)
            b.SetBit(i);
        else
            b.ClrBit(i);
    return b;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    cout << "BitLen ?" << endl;
    int len = 0;
    istr >> len;
    for (int i = 0; i < len; i++)
    {
        int f = 0;
        istr >> f;
        if (f == 1)
            bf.SetBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    ostr << "{ ";
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    ostr << "}\n";
    return ostr;
}