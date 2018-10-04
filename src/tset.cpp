//
// Created by rootreddragon on 9/29/2018.
//

#include "tset.h"






TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
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
	if (BitField.GetBit(Elem) == 1)
		return 1;
	else
		return 0;
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
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet b(1);
	b.BitField = BitField | s.BitField;
	b.MaxPower = b.BitField.GetLength();
	return b;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet b = *this;
	b.BitField.SetBit(Elem);
	return b;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet b = *this;
	b.BitField.ClrBit(Elem);
	return b;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet b(1);
	b.BitField = BitField & s.BitField;
	b.MaxPower = b.BitField.GetLength();
	return b;
}

TSet TSet::operator~(void) // дополнение
{
	TSet b = *this;
	b.BitField = ~BitField;
	return b;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	cout << "-1 = END" << endl;
	int a;
	istr >> a;
	while (a > 0)
	{
		s.InsElem(a);
		istr >> a;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "{";
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i) == 1)
			ostr << " " << i;
	}
	ostr << " }";
	return ostr;
}