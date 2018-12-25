// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)//конструктор
{
  if (len<0) throw "Error length";
  BitLen = len; 
  MemLen=(len+31)>>5; //в эл-те pMem 32 бит (TELEM==int)
  pMem=new TELEM[MemLen];
  if (pMem!= NULL)
  for (int i=0;i<MemLen;i++) 
  {
    pMem[i]=0;
   }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen=bf.BitLen;
  MemLen=bf.MemLen;
  pMem=new TELEM[MemLen];
  if (pMem!=NULL)
  for (int i=0;i<MemLen;i++)
 {
   pMem[i]=bf.pMem[i];
 }
}

TBitField::~TBitField()
{
  delete pMem;
  pMem=NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  //преобразовать к int, разделить на 32
  return n>>5; //в эл-те pMem 32 бит
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  //преобразовать к int, найти остаток от деения на 32 и сдвинуть
  return 1<< (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n>-1) && (n< BitLen))
  {
    int i=GetMemIndex(n);
    pMem[i] |= GetMemMask(n);
  }
  else 
    throw "Wrong Index";
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n>-1) && (n< BitLen))
  {
    int i=GetMemIndex(n);
    pMem[i] &= ~GetMemMask(n);
  }
  else 
    throw "Wrong Index";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n>-1) && (n< BitLen))
  {
    int i=GetMemIndex(n);
    return (pMem[i] & GetMemMask(n))  >> (n % 16);
  }
  else 
    throw "Wrong Index";
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  BitLen = bf.BitLen;
  if (MemLen != bf.MemLen)
  {
    MemLen=bf.MemLen;
    if (pMem != NULL) 
      delete pMem;
    pMem = new TELEM[MemLen];
  }
  if (pMem != NULL)
    for ( int i=0; i<MemLen; i++) 
      pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int res=1; int i=0;
	if (BitLen == bf.BitLen)
	{
		while ((pMem[i] == bf.pMem[i]) && (i < MemLen))
			i++;
	}

	else res = 0;
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    int res=0;
  if (BitLen != bf.BitLen) res=1;
  else
  for (int i=0;i<MemLen;i++) 
    if (pMem[i] !=bf.pMem[i])
    {
      res=1; 
      break;
    }
  return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int len = BitLen;
  if (bf.BitLen>len) 
    len = bf.BitLen;
  TBitField temp(len);
  for (int i=0; i<MemLen; i++)
    temp.pMem[i]= pMem[i];
  for (int i=0; i<bf.MemLen; i++) 
    temp.pMem[i] |= bf.pMem[i];
  return temp;  
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int len = BitLen;
  if (bf.BitLen>len) 
    len = bf.BitLen;
  TBitField temp(len);
  for (int i=0; i<MemLen; i++)
    temp.pMem[i]= pMem[i];
  for (int i=0; i<bf.MemLen; i++)
      temp.pMem[i] &= bf.pMem[i];
  for (int i= bf.BitLen; i<BitLen;i++)
  temp.ClrBit(i);
  return temp;  
}

TBitField TBitField::operator~(void) // отрицание
{
  int len=BitLen;
  TBitField temp(len);
  for (int i=0; i<MemLen; i++)
  temp.pMem[i]= ~pMem[i];
  return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  //формат данных - последовательность из 0 и 1 без пробелов
  //начальные пробелы игнорируются
  //при получении не 0 или 1 - завершение ввода
  int i=0;
  char ch;
  //поиск 
    do { istr >> ch;} while (ch != ' ');
    // ввод эл-ов и включение в множество
    while(1) 
    {
      istr >> ch;
      if (ch == '0') 
        bf.ClrBit(i++);
      else 
        if (ch == '1')
        bf.SetBit(i++);
        else  
          break;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  //формат данных - последовательность из 0 и 1
  //вывод элементов
  int len = bf.GetLength();
  for (int i=0; i<len; i++)
    if (bf.GetBit(i))
      ostr << '1';
      else
      ostr << '0';
  return ostr; 
}
