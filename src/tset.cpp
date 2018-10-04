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
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField( bf.GetLength() )
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
    return ( BitField.GetBit(Elem) );
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
    
    return(*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if(MaxPower == s.MaxPower)
    {
        if(BitField == s.BitField)
            return 1;
    }
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return TSet ( (*this).BitField | s.BitField );
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet Temp(*this);
    Temp.BitField.SetBit(Elem);
    
    return Temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet Temp(*this);
    Temp.BitField.ClrBit(Elem);
    
    return Temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return TSet ( (*this).BitField & s.BitField );
}

TSet TSet::operator~(void) // дополнение
{
    return ~(*this);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << s.BitField;
    
    return ostr;
}