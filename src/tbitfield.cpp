// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define TELEM_SIZE (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
  if (len < 0) throw length_error("Negative length of a bit field");

  BitLen = len;
  MemLen = len / TELEM_SIZE + (len % TELEM_SIZE != 0);
  pMem = new TELEM[MemLen];

  for (int i = 0; i < MemLen; i++) {
    pMem[i] = 0;
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  pMem = new TELEM[MemLen];

  for (int i = 0; i < MemLen; i++) {
    pMem[i] = bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n >= BitLen) throw out_of_range("Bit number is out of range");
  
  return n / TELEM_SIZE;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n >= BitLen) throw out_of_range("Bit number is out of range");

  return (1 << (n % TELEM_SIZE));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n >= BitLen) throw out_of_range("Bit number is out of range");

  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n >= BitLen) throw out_of_range("Bit number is out of range");

  pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n >= BitLen) throw out_of_range("Bit number is out of range");
  
  return ((pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this != &bf) {
    if (MemLen != bf.MemLen) {
      delete[] pMem;
      pMem = new TELEM[bf.MemLen];
    }
    
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;

    for (int i = 0; i < MemLen; i++) {
      pMem[i] = bf.pMem[i];
    }
  }

  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (MemLen >= bf.MemLen) {
    for (int i = 0; i < bf.MemLen; i++) {
      if (pMem[i] != bf.pMem[i]) return 0;
    }

    for (int i = bf.MemLen; i < MemLen; i++) {
      if (pMem[i] != 0) return 0;
    }
  }
  else {
    for (int i = 0; i < MemLen; i++) {
      if (pMem[i] != bf.pMem[i]) return 0;
    }

    for (int i = MemLen; i < bf.MemLen; i++) {
      if (bf.pMem[i] != 0) return 0;
    }
  }

  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return ((*this == bf) ? 0 : 1);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  if (MemLen >= bf.MemLen) {
    TBitField newBitField(*this);

    for (int i = 0; i < bf.MemLen; i++) {
      newBitField.pMem[i] |= bf.pMem[i];
    }

    return newBitField;
  }
  else {
    TBitField newBitField(bf);

    for (int i = 0; i < MemLen; i++) {
      newBitField.pMem[i] |= pMem[i];
    }

    return newBitField;
  }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  if (MemLen >= bf.MemLen) {
    TBitField newBitField(*this);

    for (int i = 0; i < bf.MemLen; i++) {
      newBitField.pMem[i] &= bf.pMem[i];
    }

    return newBitField;
  }
  else {
    TBitField newBitField(bf);

    for (int i = 0; i < MemLen; i++) {
      newBitField.pMem[i] &= pMem[i];
    }

    return newBitField;
  }
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField newBitField(*this);

  for (int i = 0; i < MemLen-1; i++) {
    newBitField.pMem[i] = ~newBitField.pMem[i];
  }
  for (int i = TELEM_SIZE*(MemLen-1); i < BitLen; i++) {
    if (newBitField.GetBit(i)) {
      newBitField.ClrBit(i);
    }
    else {
      newBitField.SetBit(i);
    }
  }

  return newBitField;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char bit;

  for (int i = 1; i <= bf.BitLen; i++) {
    istr >> bit;
    
    if (bit == '1') {
      bf.SetBit(i);
    }
    else if (bit == '0') {
      bf.ClrBit(i);
    }
    else throw runtime_error("Bit value is not 0 or 1");
  }

  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.BitLen; i++) {
    ostr << bf.GetBit(i);
  }

  return ostr;
}