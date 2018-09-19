// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) //количество битов 
{
	BitLen = len;
	(len % 8 == 0) ? MemLen = len / 8 : MemLen = len / 8 + 1; //set MemLen
	pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (&bf != this)
		{
			delete[] pMem; //очистка исходного объекта
			pMem = NULL;
			BitLen = bf.BitLen; MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];// создать новый массив
			for (int i = 0; i < MemLen; i++)
			{
				pMem[i] = *(bf.pMem + i);//копируем
			}
		}
}

TBitField::~TBitField()
{
	delete[] pMem;// освобождаем память массива
	BitLen = MemLen = pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t = 1;
	return t << n % (sizeof(TELEM) * 8);// биты нумеруем с нуля
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int i = this->GetMemIndex(n);//index pMem
	if (this->GetMemMask * this->pMem[i] == 0) this->pMem[i] += this->GetMemMask; //а не включен ли уже бит?
}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
