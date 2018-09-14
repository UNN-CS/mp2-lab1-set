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
    MemLen = ((len)/((sizeof(TELEM))*8));
    if ((len)%((sizeof(TELEM))*8) > 0)
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
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    int SizeOfTelem = sizeof(TELEM)*8;
    return n / SizeOfTelem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int number = n % (sizeof(TELEM)*8);
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
    TBitField(bf);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    // последний элемент массива нужно сравнивать побитово
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
