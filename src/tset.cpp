// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField()
{
    TBitField newBitField(BitField);

    return newBitField;
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
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (MaxPower == s.MaxPower && BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet newSet(BitField | s.BitField);

    newSet.MaxPower = max(BitField.GetLength(), s.BitField.GetLength());

    return newSet;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet newSet(*this);

    newSet.InsElem(Elem);

    return newSet;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet newSet(*this);

    newSet.DelElem(Elem);

    return newSet;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet newSet(BitField & s.BitField);

    newSet.MaxPower = max(BitField.GetLength(), s.BitField.GetLength());
    
    return newSet;
}

TSet TSet::operator~(void) // дополнение
{
    TSet newSet(~BitField);

    return newSet;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    char tmp;
    string strTmp = "";

    istr >> tmp;
    if (tmp != '{') throw runtime_error("Wrong input format");

    while (istr >> tmp) {
        if (tmp == '}') break;
        if (tmp == ',') {
            istr >> tmp;

            if (tmp == ' ') {
                s.InsElem(stoi(strTmp));
                strTmp = "";
            }
            else throw runtime_error("Wrong input format");
        }
        else if (tmp >= '0' || tmp <= '9') {
            strTmp += tmp;
        }
        else throw runtime_error("Wrong input format");
    }

    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << "{";

    bool firstValue = true;
    for (int i = 0; i < s.MaxPower-1; i++) {
        if (s.IsMember(i)) {
            if (!firstValue) {
                ostr << ", ";
            }
            else firstValue = false;
            
            ostr << i;
        }
    }

    ostr << "}";

    return ostr;
}
