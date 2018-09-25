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
TSet::TSet(const TSet &s) : BitField(s.BitField) //иниц-я к копи
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
	TBitField t(BitField);          //this->BF
	return t;
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
	if (*this != s)
	{
		BitField.operator=(s.BitField);
		MaxPower = s.MaxPower;
	}
	return *this;	
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
	{
		return BitField.operator==(s.BitField);
	}
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
	{
		return BitField.operator!=(s.BitField);
	}
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet t(BitField | s.BitField);
	return t;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet t(*this);
	t.InsElem(Elem);
	return t;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet t(*this);
	t.DelElem(Elem);
	return t;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet t(BitField.operator&(s.BitField));
	return t;
}

TSet TSet::operator~(void) // дополнение
{
	//TSet t(~BitField);        ???
	TSet t(BitField.operator~);
	return t;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	//istr >> s.MaxPower;   ???
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
