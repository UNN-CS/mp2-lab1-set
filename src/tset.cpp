// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
  MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
  MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
  MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{    
  return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  if (this != &s)
  {
    MaxPower = s.MaxPower;
    BitField = s.BitField;
  }

  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  if (this == &s)
    return 1;

  return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return !operator==(s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
  return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet ret(*this);

  ret.InsElem(Elem);

  return ret;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet ret(*this);

  ret.DelElem(Elem);

  return ret;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
  return TSet(~BitField);
}

// перегрузка ввода/вывода

int _atoi(char *str) {
  if (*str == 0)
    throw(-4);
  char *p = str;
  int r = 0;
  int e = 1;
  while (*(++p));
  while (p != str)
  {
    --p;
    if ((*p < '0' || *p > '9') && *p != '-')
      throw(-4);
    else if (*p == '-')
      return -r;
    else
    {
      r += (*p - '0') * e;
      e *= 10;
    }
  }
  return r;
}

istream &operator>>(istream &istr, TSet &s) // ввод
{
  TSet res(s);
  char input[1024];
  char tmp[16] = { 0 };
  int i = 0;
  const int mp = s.GetMaxPower();
  char *p = input;

  for (int j = 0; j < mp; ++j)
    s.DelElem(j);

  cin.getline(input, 1024);

  while (*p != 0)
  {
    while ((*p >= '0' && *p <= '9') || *p == '-')
    {
      tmp[i] = *p;
      ++i;
      ++p;
    }

    if (tmp[0] != 0)
    {
      int el;
      try
      {
        el = _atoi(tmp);
      }
      catch (...)
      {
        s = res;
        throw(-3);
      }

      s.InsElem(el);

      for (int j = 0; j < 16; ++j)
        tmp[j] = 0;
      i = 0;
    }

    ++p;
  }

  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  int i;

  cout << "{ ";
  for (i = 0; i < s.MaxPower; ++i)
  {
    if (s.IsMember(i))
    {
      cout << i;
      ++i;
      break;
    }
  }
  for (; i < s.MaxPower; ++i)
    if (s.IsMember(i))
      cout << ", " << i;
  cout << " }";

  return ostr;
}
