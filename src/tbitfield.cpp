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
    MemLen = BitLen div (8 * sizeof(TELEM));
    if (BitLen mod (8 * sizeof(TELEM)) <> 0)
        MemLen++;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    if (&bf != NULL)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete []pMem;
    pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int Mem = n / (8 * sizeof(TELEM));
    return Mem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < BitLen)
        pMem[GetMemIndex(n)] |=  GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < BitLen)
        pMem[GetMemIndex(n)] &=  ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < BitLen)
    {
        TELEM result = pMem[GetMemIndex(n)] & GetMemMask(n);
        if (result != 0) return 1;
        else return 0;
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf != this)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        if (pMem != NULL) delete []pMem;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }    if (&bf != NULL)
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    for (int i = 0; i < MemLen: i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
      if (BitLen != bf.BitLen)
        return 1;
    for (int i = 0; i < MemLen: i++)
        if (pMem[i] != bf.pMem[i])
            return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int Mem, Bit, MinMem;
    TELEM *p = NULL;
    if (BitLen > bf.BitLen)
    {
        Mem = MemLen;
        Bit = BitLen;
        MinMem = bf.MemLen;
        p = pMem;
    }
    else
    {
        Mem = bf.MemLen;
        Bit = bf.BitLen;
        MinMem = MemLen;
        p = bf.pMem;
    }
    TBitField tmp(Bit);
    for (int i = 0; i < MinMem; i++)
    {
        tmp.pMem[i] = pMem[i] | bf.pMem[i];
    }
    for (int i = MinMem; i < Mem; i++)
    {
        tmp.pMem[i] = p[i]
    }
    p = NULL;
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int MinBit;
    if (BitLen > bf.BitLen)
    {
        MinBit = bf.BitLen;
    }
    else
    {
        MinBit = BitLen;
    }
    TBitField tmp(MinBit);
    for (int i = 0; i < tmp.MemLen; i++)
    {
        tmp.pMem[i] = bf.pMem[i] & pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(* this);
    for (int i = 0; i < MemLen; i++)
        tmp.pMem[i] = ~tmp.pMem[i];
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

}
