// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if(len % sizeof(TELEM) == 0)
        MemLen = len / sizeof(TELEM);
    else
        MemLen = len / sizeof(TELEM) + 1;
    
    BitLen = len;
    
    pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    if(this != &bf) // &bf возвращает адрес объекта
    {
        BitLen = bf.BitLen;
        
        MemLen = bf.MemLen;
        
        pMem = new TELEM[MemLen];
        
        for (int i = 0; i < BitLen; i++)
            pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    BitLen = NULL;
    MemLen = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n/sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int m = n % sizeof(TELEM);
    TELEM mask = 1<<m;
    return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    TELEM tMask = GetMemMask(n);
    
    if ( (pMem[GetMemIndex(n)] & tMask) == 0 )
        pMem[GetMemIndex(n)] += tMask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    TELEM tMask = GetMemMask(n);
    
    if ( (pMem[GetMemIndex(n)] & tMask) == 1 )
        pMem[GetMemIndex(n)] -= tMask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    
}

TBitField TBitField::operator~(void) // отрицание
{
    
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    
}