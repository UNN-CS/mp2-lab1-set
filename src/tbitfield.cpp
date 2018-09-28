// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len): BitLen(len)
{
    if (len<1)
        throw -1;
    MemLen=(len+sizeof(TELEM)*8-1)/(sizeof(TELEM)*8);
    pMem= new TELEM[MemLen];
    for (int i=0;i<MemLen;++i)
        pMem[i]=0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen=bf.BitLen;
    MemLen=bf.MemLen;
    pMem=new TELEM[MemLen];
    for (int i=0;i<MemLen;++i)
        pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n+sizeof(TELEM)*8)/(sizeof(TELEM)*8)-1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1ull << (n%(sizeof(TELEM)*8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n<0)||(n>=BitLen))
        throw -1;
    pMem[GetMemIndex(n)]|=GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n<0)||(n>=BitLen))
        throw -1;
    pMem[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n<0)||(n>=BitLen))
        throw -1;
    if (pMem[GetMemIndex(n)]&GetMemMask(n))
        return 1;
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf==this)
        return *this;
    delete[] pMem;
    BitLen=bf.BitLen;
    MemLen=bf.MemLen;
    pMem=new TELEM[MemLen];
    for (int i=0;i<MemLen;++i)
        pMem[i]=bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen!=bf.BitLen)
        return 0;
    for (int i=0;i<bf.BitLen/(sizeof(TELEM)*8);++i)
        if (pMem[i]!=bf.pMem[i])
            return 0;
    for (int i=0;i<bf.BitLen%(sizeof(TELEM)*8);++i)
        if ((pMem[MemLen-1]&GetMemMask(i))!=(bf.pMem[MemLen-1]&GetMemMask(i)))
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen!=bf.BitLen)
        return 1;
    for (int i=0;i<bf.BitLen/(sizeof(TELEM)*8);++i)
        if (pMem[i]!=bf.pMem[i])
            return 1;
    for (int i=0;i<bf.BitLen%(sizeof(TELEM)*8);++i)
        if ((pMem[MemLen-1]&GetMemMask(i))!=(bf.pMem[MemLen-1]&GetMemMask(i)))
            return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen>bf.BitLen)
    {
        TBitField tmp(*this);
        for (int i=0;i<bf.MemLen;++i)
            tmp.pMem[i]|=bf.pMem[i];
        return tmp;
    }
    else
    {
        TBitField tmp(bf);
        for (int i=0;i<MemLen;++i)
            tmp.pMem[i]|=pMem[i];
        return tmp;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen>bf.BitLen)
    {
        TBitField tmp(BitLen);
        for (int i=0;i<bf.MemLen;++i)
            tmp.pMem[i]=bf.pMem[i]&pMem[i];
        return tmp;
    }
    else
    {
        TBitField tmp(bf.BitLen);
        for (int i=0;i<MemLen;++i)
            tmp.pMem[i]=bf.pMem[i]&pMem[i];
        return tmp;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(*this);
    for (int i=0;i<MemLen;++i)
        tmp.pMem[i]=~tmp.pMem[i];
    for (int i=(BitLen%(sizeof(TELEM)*8))?(BitLen%(sizeof(TELEM)*8)):sizeof(TELEM)*8;i<sizeof(TELEM)*8;++i)
        tmp.pMem[MemLen-1]&=~GetMemMask(i);
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char ch;
    int c,i=0;
    istr >> ch;
    c=ch;
    while (((c==49)||(c==48)))
    {
        if (c==49)
            bf.SetBit(i);
        else
            bf.ClrBit(i);
        ++i;
        c=istr.get();
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    TELEM tmp;
    for (int i=0;i<bf.BitLen/(sizeof(TELEM)*8);++i)
    {
        tmp=bf.pMem[i];
        for (int j=0;j<sizeof(TELEM)*8;++j)
        {
            ostr << (tmp&1ull);
            tmp=tmp >> 1;
        }
    }
    tmp=bf.pMem[bf.MemLen-1];
    for (int i=0;i<bf.BitLen%(sizeof(TELEM)*8);++i)
    {
        ostr << (tmp&1ull);
        tmp=tmp >> 1;
    }
    return ostr;
}
