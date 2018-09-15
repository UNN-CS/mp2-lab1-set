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

        }
    }
    return 0; // если что-то не равно
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
