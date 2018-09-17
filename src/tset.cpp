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
	for (int i = 0; i < MaxPower; ++i)
	{
		BitField.ClrBit(i);
	}
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
	return TBitField(BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0 || Elem >= MaxPower)
		return 0;
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower)
		throw range_error("out of universe");
	else
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if(Elem >= 0 && Elem < MaxPower)
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
	if (MaxPower != s.MaxPower)
	{
		return 0;
	}
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return (*this == s) ? 0 : 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet t(BitField | s.BitField);
	return t;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= MaxPower) {
		throw range_error("out of universe");
	}
	TSet t(*this);
	t.InsElem(Elem);
	return t;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet t(*this);
	if(Elem >= 0 && Elem < MaxPower)
		t.DelElem(Elem);
	return t;
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

istream &operator>>(istream &istr, TSet &s) // ввод
{
	char input[1024];
	char tmp[16] = { 0 };
	char i = 0;
	char *p = input;
	cin.getline(input, 1024);

	while (*p != 0)
	{
		while (isdigit(*p) || *p == '-')
		{
			tmp[i++] = *p;
			++p;
		}
		if (tmp[0] != 0) {
			int el = atoi(tmp);
			if (el < 0 || el >= s.GetMaxPower()) {
				throw range_error("bad input");
			}
			s.InsElem(el);
		}
		for (int j = 0; j < 16; ++j)
			tmp[j] = 0;
		i = 0;
		++p;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << "{";
	int i = 0;
	for (; i < s.MaxPower; ++i)
	{
		if (s.IsMember(i))
		{
			cout << i;
			++i;
			break;
		}
	}
	for (; i < s.MaxPower; ++i)
	{
		if (s.IsMember(i))
		{
			cout << ", " << i;
		}
	}
	cout << "}";
	return ostr;
}
