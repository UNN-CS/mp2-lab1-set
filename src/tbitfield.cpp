// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <algorithm>

TBitField::TBitField(int len)
{
    if (len<0) throw -1;
    BitLen=len;
    MemLen = (len+sizeof(TELEM)*8-1)/(sizeof(TELEM)*8);
    pMem = new TELEM[MemLen];
    for (int i=0;i<MemLen;++i) pMem[i]=0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i=0;i<MemLen;++i) pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
    delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM cnt = 1 << (n%(sizeof(TELEM)*8));
    return cnt;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n>=0&&n<BitLen)
    {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }
    else throw -1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n>=0&&n<BitLen)
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    else throw -1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n>=0&&n<BitLen)
        return (pMem[GetMemIndex(n)]&GetMemMask(n))>0;
    else throw -1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this!=&bf)
    {
        BitLen = bf.BitLen;
       if (MemLen!=bf.MemLen)
       {
           MemLen=bf.MemLen;
           delete [] pMem;
           pMem = new TELEM [MemLen];
       }
       for (int i=0;i<MemLen;++i) pMem[i]=bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int ans=1;
    if (BitLen!=bf.BitLen) ans=0;
    else
    {
        for (int i=0;i<MemLen;++i)
        if (pMem[i]!=bf.pMem[i])
        {
            ans=0;break;
        }
    }
    return ans;
    //return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return (*this==bf?0:1);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = max(BitLen,bf.BitLen);
    TBitField tmp(len);
    for (int i=0;i<MemLen;++i) tmp.pMem[i] = pMem[i];
    for (int i=0;i<bf.MemLen;++i) tmp.pMem[i]|=bf.pMem[i];
    return tmp;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len = max(BitLen,bf.BitLen);
    TBitField tmp(len);
    int k=min(MemLen,bf.MemLen),k1=max(MemLen,bf.MemLen);
    for (int i=0;i<k;++i) tmp.pMem[i] = (MemLen<bf.MemLen?pMem[i]:bf.pMem[i]);
    for (int i=0;i<k1;++i) tmp.pMem[i] &= (MemLen<bf.MemLen?bf.pMem[i]:pMem[i]);
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (int i=0;i<MemLen-1;++i)
        tmp.pMem[i] = ~pMem[i];
    for (int i=(MemLen-1)*8*sizeof(TELEM);i<BitLen;++i)
        if (!GetBit(i)) tmp.SetBit(i);
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i=0;char c;
    for (int j=0;j<bf.BitLen;++j)
    {
        istr>>c;
        if (c=='0') bf.ClrBit(j);
        else if (c=='1') bf.SetBit(j);
        else throw -1;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    int l = bf.GetLength();
    for (int i=0;i<l;++i)
       cout<<bf.GetBit(i);
    return ostr;
}

