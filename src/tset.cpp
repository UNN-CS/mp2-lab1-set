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

// Конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// Конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return TBitField(MaxPower);
}

int TSet::GetMaxPower(void) const // получить максимального количества элементов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // Проверка на элемент множества
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // Вставка элемента в множество
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // Удаление элемента из множества
{
	BitField.ClrBit(Elem);
}

// Операции с множествами

TSet& TSet::operator=(const TSet &s) // Присваивавание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // Сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // Сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // Объединение
{
	return BitField | s.BitField;
}

TSet TSet::operator+(const int Elem) // Объединение с элементом
{
	TSet temp(*this);
	temp.BitField.SetBit(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) // Разность с элементом
{
	TSet temp(*this);
	temp.BitField.ClrBit(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // Пересечение
{
	return BitField & s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// Перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // Ввод
{
	char ch;
	int i;
	while (1)
	{
		istr >> ch;
		istr >> i;
		s.InsElem(i);
		istr >> ch;
		if (ch == ';') break;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // Вывод
{
	ostr << "{ ";
	for (int i = 0; i < s.GetMaxPower(); i++)
		if (s.IsMember(i))
			ostr << 'A' << i << ' ';
	ostr << "}";
	return ostr;
}