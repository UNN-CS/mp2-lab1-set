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
    int Mem = n div (8 * sizeof(TELEM));
    if (n % (8 * sizeof(TELEM)) <> 0)
        Mem++;
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

}

void TBitField::ClrBit(const int n) // очистить бит
{

}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return 0;
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
