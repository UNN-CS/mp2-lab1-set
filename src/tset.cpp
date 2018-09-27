// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp)
{
	MaxPower = mp;
	BitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) 
{
	MaxPower = s.MaxPower;
	BitField = TBitField(s.BitField);
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) 
{
	MaxPower = bf.GetLength();
	BitField = TBitField(bf); // копируем битовое поле
}

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
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int max;
	if (MaxPower >= s.MaxPower)     // ищем наибольшую длину
		max = MaxPower;
	else
		max = s.MaxPower;

	TSet tmp(BitField | s.BitField);
	tmp.MaxPower = max;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower) throw "out_of_range";
	this->InsElem(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	this->DelElem(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int max;
	if (MaxPower >= s.MaxPower)     // ищем наибольшую длину
		max = MaxPower;
	else
		max = s.MaxPower;

	TSet tmp(BitField & s.BitField);
	tmp.MaxPower = max;
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	cin >> s.BitField;

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << s.BitField;

	return ostr;
}
