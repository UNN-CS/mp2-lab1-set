// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if(len<0)
        throw -1;
    BitLen = len;
    MemLen = (len+sizeof(TELEM)-1)/sizeof(TELEM);
    pMem = new TELEM[MemLen];
    for(int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for(int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1<<(n-sizeof(TELEM)*GetMemIndex(n));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if(n < 0 || n >= BitLen)
        throw -1;
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)]|GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if(n < 0 || n >= BitLen)
        throw -1;
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)]&(~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if(n < 0 || n >= BitLen)
        throw -1;
    return ((pMem[GetMemIndex(n)]&GetMemMask(n))>>(n-sizeof(TELEM)*GetMemIndex(n)));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    delete[]pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for(int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen || MemLen != bf.MemLen)
        return 0;
    for(int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen || MemLen != bf.MemLen)
        return 1;
    for(int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return 1;
    }
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField tmp(max(BitLen, bf.BitLen));
    for(int i = 0; i < min(MemLen, bf.MemLen); i++)
    {
        tmp.pMem[i] = pMem[i]|bf.pMem[i];
    }
    if(BitLen < bf.BitLen)
    {
        for(int i = MemLen; i < bf.MemLen; i++)
            tmp.pMem[i] = bf.pMem[i];
    }
    else
    {
        for(int i = bf.MemLen; i < MemLen; i++)
            tmp.pMem[i] = pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField tmp(max(BitLen, bf.BitLen));
    for(int i = 0; i<min(MemLen, bf.MemLen); i++)
    {
        tmp.pMem[i] = pMem[i]&bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for(int i = 0; i < tmp.BitLen; i++)
    {
        if (GetBit(i) == 0)
            tmp.SetBit(i);
        else
            tmp.ClrBit(i);
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string str;
    cin>>str;
    delete[] bf.pMem;
    bf.BitLen = str.size();
    bf.MemLen = (bf.BitLen+sizeof(TELEM)-1)/sizeof(TELEM);
    bf.pMem = new TELEM[bf.MemLen];
    for(int i = 0; i < bf.MemLen; i++)
        bf.pMem[i] = 0;
    for(int i = 0; i < (int)str.size(); i++)
    {
        if(str[i] == '0')
            bf.ClrBit(i);
        else if(str[i] == '1')
            bf.SetBit(i);
        else
            throw -1;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for(int i = 0; i < bf.BitLen; i++)
    {
        cout<<bf.GetBit(i);
    }
    return ostr;
}
