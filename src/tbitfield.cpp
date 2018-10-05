// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
		BitLen = len;
	else throw -1;
	MemLen = (len + sizeof(int)*8 - 1)/(sizeof(int)*8);
	pMem = new TELEM [MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM [bf.MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n>=0)&&(n<BitLen))
		return n/(sizeof(int)*8);
	else throw -1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n>=0)&&(n<BitLen))
		return 1<<(n&31);
	else throw -1;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n>=0)&&(n<BitLen))
		pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]|GetMemMask(n);
	else throw -1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n>=0)&&(n<BitLen))
		pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]&~GetMemMask(n);
	else throw -1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n>=0)&&(n<BitLen))
	  return pMem[GetMemIndex(n)]&GetMemMask(n);
  else throw -1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this==&bf)
		return *this;
	else 
	{
		if (pMem != NULL)
			delete[]pMem;
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		pMem = new TELEM [MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
		return *this;
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  bool flag = true;
	int minlen = MemLen<bf.MemLen ? MemLen:bf.MemLen;
	for (int i=0; i<minlen; ++i)
			if (pMem[i]!=bf.pMem[i]) 
				{
					flag = false;
					break;
				}
	if (MemLen>bf.MemLen) 
			for (int i=bf.MemLen; i<MemLen; ++i) if (pMem[i]!=0) 
				{
					flag = false;
					break;
				}
	if (MemLen<bf.MemLen) 
			for (int i=MemLen; i<bf.MemLen; ++i) if (bf.pMem[i]!=0) 
				{
					flag = false;
					break;
				}
  return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (*this==bf) return false;
	else return true;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int minlen = MemLen < bf.MemLen ? MemLen : bf.MemLen;
	TBitField tmp (len);
	for (int i = 0; i<tmp.MemLen; ++i)
			tmp.pMem[i]=bf.pMem[i];
	for (int i = 0; i<minlen; ++i)
		tmp.pMem[i]=tmp.pMem[i]|pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen > bf.BitLen ? BitLen : bf.BitLen;
	int minlen = MemLen < bf.MemLen ? MemLen : bf.MemLen;
	TBitField tmp (len);
	for (int i = 0; i < minlen; i++)
		tmp.pMem[i] = pMem[i]&bf.pMem[i];
	for (int i = minlen; i < tmp.MemLen; i++)
		tmp.pMem[i] = 0;
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField bf(len);
	for (int i = 0; i < BitLen; ++i)
		if (GetBit(i)) bf.ClrBit(i);
		else bf.SetBit(i);
	return bf;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int n = 0; 
	char c;    
	do
	{
		istr.get(c);
	} while (c!='\n');
	while (1)
	{
		istr.get(c);
		if (c=='0')
		{
			bf.ClrBit(n++);
		}
		else
			if (c=='1')
			{
				bf.SetBit(n++);
			}
			else
				break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0; i<bf.BitLen; ++i)
		{
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
		return ostr;
}
