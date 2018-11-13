// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower),  BitField(s.BitField)
{
	
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
	TBitField temp(this->BitField);
	return temp;
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
	BitField = s.BitField;
	MaxPower = s.GetMaxPower();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet temp(BitField | s.BitField);
		return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TBitField temp = BitField;
	temp.SetBit(Elem);
	return TSet(temp);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TBitField temp=BitField;
	temp.ClrBit(Elem);
    return TSet(temp);
	
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp(BitField & s.BitField);
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(~BitField);
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    char ch;
	do{ istr >> ch; } while (ch != '{');
	do{ istr >> ch; } while( ((ch != ',')) && (ch != '}'));
	while (ch != ')');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i, n; char ch = ' ';
	ostr << "{";
		n = s.GetMaxPower();
		for (i = 0; i < n; i++){
			if (s.IsMember(i)) {
				ostr << ch << ' ' << i; ch = ',';
			}
		}
		ostr << " } ";
		return ostr;
}
