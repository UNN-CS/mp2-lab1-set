// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	TBitField res(MaxPower);
	int MaxPow = res.GetLength();
	for (int i = 0; i < MaxPow; i++)
		if (BitField.GetBit(i)==1) res.SetBit(i);
	return res;
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
	if (this==&s) return *this;
	else 
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
		return *this;
	}
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (BitField==s.BitField) return true;
	else return false;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower!=s.MaxPower) return true;
	else {
		if (BitField!=s.BitField) return true;
		else return false;
	}
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet ts (BitField|s.BitField);
	return ts;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet ts (BitField&s.BitField);
	return ts;
}

TSet TSet::operator~(void) // дополнение
{
	TSet ts (~BitField);
	return ts;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int n=0;
	char ch;    
	do
	{
		istr.get(ch);
	} while (ch!='\n');
	while (1)
	{
		istr.get(ch);
		if (ch=='0')
		{
			s.DelElem(n++);
		}
		else
			if (ch=='1')
			{
				s.InsElem(n++);
			}
			else
				break;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int MaxPow = s.GetMaxPower();
	ostr<<"{ ";
	for (int i = 0; i < MaxPow; i++)
		if (s.IsMember(i)) ostr<<i<<"  ";
	ostr<<"}"<<endl;
	return ostr;
}
