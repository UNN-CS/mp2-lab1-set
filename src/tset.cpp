// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp <= 0)
		throw("creating set with 0 or less length");

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
}

TSet::operator TBitField()
{
	return TBitField(-1);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return 0;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	return TSet(-1);
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return TSet(-1);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	return TSet(-1);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	return TSet(-1);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(-1);
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(-1);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}
