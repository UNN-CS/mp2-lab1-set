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
	TBitField tmp(this->BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return  MaxPower;
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
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return(*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int res = 0;
	if (BitField == s.BitField)
		res = 1;
	return res;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int res = 0;
	if (BitField != s.BitField)
		res = 1;
	return res;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet temp(MaxPower);
	temp = (*this);
	temp.InsElem(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet temp(MaxPower);
	temp = (*this);
	temp.DelElem(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(BitField & s.BitField);
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	return (~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int numb;
	for (int i = 0; i < s.MaxPower; i++)
	{
		istr >> numb;
		if ((numb >= 0) && (numb < s.MaxPower))
			s.InsElem(numb);
		else break;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i;
	ostr << "{ ";
	for (i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i))
			ostr << i << " ";
	}
	ostr << "}";
	return ostr;
}