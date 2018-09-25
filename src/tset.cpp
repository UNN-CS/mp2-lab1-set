// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "../include/tset.h"

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
	return TSet(BitField);
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
		BitField = s.BitField;
		MaxPower = s.MaxPower;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
		return 1;
	else
		return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
		return 0;
	else
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int length;
	if (MaxPower > s.MaxPower)
		length = MaxPower;
	else
		length = s.MaxPower;
	TSet temp(length);
	temp.BitField = BitField | s.BitField;
	return temp;

}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp(*this);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(*this);
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int length;
	if (MaxPower > s.MaxPower)
		length = MaxPower;
	else
		length = s.MaxPower;
	TSet temp(length);
	temp.BitField = BitField & s.BitField;
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(*this);
	tmp.BitField = ~tmp.BitField;
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int temp;
	char ch;
	do
	{
		istr >> ch;
	} while (ch != '{');
	do
	{
		istr >> temp;
		s.InsElem(temp);
		do
		{
			istr >> ch;
		} while ((ch != ',') && (ch != '}'));
	} while (ch != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i;
	ostr << "{ ";
	for (i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i))
			ostr << i << ' ';
	ostr << '}' << endl;
	return ostr;
}
