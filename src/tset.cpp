// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
	return TBitField(this->BitField);
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
    if (&s == this)
        return *this;
	this->BitField = s.BitField;
	this->MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (this->MaxPower != s.MaxPower)
		return false;
	return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !operator==(s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return TSet(this->BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res = TSet(this->BitField);
	res.BitField.SetBit(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res = TSet(this->BitField);
	res.BitField.ClrBit(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(this->BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(~this->BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return operator>>(istr, s.BitField);
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return operator<<(ostr, s.BitField);
}
