// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
//final

#include "tbitfield.h"
#include <cmath>
#include <string>

#define TELEMsz (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	try
	{
		if (len < 0) throw "inaccessible len";
	}
	catch (string s)
	{
		cout << "Ex: " << s << endl;
	}

	BitLen = len;

	MemLen = ceil(float(len) / TELEMsz);
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];

	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0 && n < GetLength())
		return n / TELEMsz;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n вида 2^k
{
	if (n >= 0 && n < GetLength())
		return 1 << TELEMsz - 2 - (n % TELEMsz);

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	try
	{
		if (n >= 0 && n < GetLength())
		{
			pMem[GetMemIndex(n)] |= GetMemMask(n);
		}
		else
		{
			throw "inaccessible bit";
		}
	}
	catch (string s)
	{
		cout << "Ex: " << s << endl;
	}

	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	try
	{
		if (n >= 0 && n < GetLength())
		{
			pMem[GetMemIndex(n)] &= ~GetMemMask(n);
		}
		else
		{
			throw "inaccessible bit";
		}
	}
	catch (string s)
	{
		cout << "Ex: " << s << endl;
	}

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	try
	{
		if (n >= 0 && n < GetLength())
		{
			return (pMem[GetMemIndex(n)] & GetMemMask(n)) > 0;
		}
		else
		{
			throw "inaccessible bit";
		}
	}
	catch (string s)
	{
		cout << "Ex: " << s << endl;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf == this) return *this;

	BitLen = bf.BitLen;

	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL) delete[] pMem;
		pMem = new TELEM[MemLen];
	}

	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение 
{
	if (this->GetLength() != bf.GetLength()) return 0;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i]) return 0;
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (this->GetLength() != bf.GetLength()) return 1;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i]) return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int minL = this->MemLen < bf.MemLen ? this->MemLen : bf.MemLen;

	TBitField temp = this->MemLen > bf.MemLen ? *this : bf;

	for (int i = 0; i < minL; i++)
	{
		temp.pMem[i] = pMem[i] | bf.pMem[i];
	}

	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;

	TBitField temp(len);

	for (int i = 0; i < MemLen; i++)
	{
		temp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] &= bf.pMem[i];
	}

	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp = *this;

	for (int i = 0; i < MemLen - 1; i++)
	{
		temp.pMem[i] = ~temp.pMem[i];
	}

	for (int i = (MemLen - 1)*TELEMsz; i < BitLen; i++) //цикл, чтобы лишние биты в Телеме остались нулями 
	{
		if (GetBit(i))									//и не приходилось с ними работать в других операциях
		{
			temp.ClrBit(i); // 1 чистим
		}
		else
		{
			temp.SetBit(i); //0 в 1
		}
	}



	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string s;
	cin >> s;

	int slen = s.length();
	bf = TBitField(slen); //перевыделить память

	for (int i = 0; i < slen; i++)
	{
		bf.SetBit(i);

	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	string s = "";

	for (int i = 0; i < bf.BitLen; i++)
	{
		s += bf.GetBit(i) + '0';
	}

	cout << s << endl;

	return ostr;

}
