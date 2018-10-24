#include "tbitfield.h"
#include<iostream>
#include<string>
#include<algorithm>

TBitField::TBitField(int len)
{
	if (len <=0 ) throw  1;
	BitLen = len;
	MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen]{0};
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(int const n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int tmp = n % (sizeof(TELEM) * 8);
	TELEM mask = 1;
	mask = mask << tmp;
	return(mask);
	
}

// доступ к битам битового поля

int TBitField::GetLength(void) const  // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n<0 || n >= BitLen)
		throw  1;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n<0 || n >= BitLen)
		throw  1;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));

}


int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n<0 || n >= BitLen)
		throw  1;
	return ((pMem[GetMemIndex(n)] & GetMemMask(n))) >0;
	
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf == this)
		return *this;
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	
	if (this->BitLen != bf.BitLen)
		return false;
	for (int i = 0; i < MemLen - 1; ++i)
		if (this->pMem[i] != bf.pMem[i])
			return false;
	for (int i = ((this->BitLen - 1) / (sizeof(TELEM) * 8)) * sizeof(TELEM) * 8; i < this->BitLen; ++i)
		if (this->GetBit(i) != bf.GetBit(i))
			return false;
	return true;



}
int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !operator==(bf);
}
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	
	TBitField res(max(this->BitLen, bf.BitLen));
	for (int i = 0; i < min(this->BitLen, bf.BitLen); ++i)
		if (this->GetBit(i) || bf.GetBit(i))
			res.SetBit(i);
	if (bf.BitLen > min(this->BitLen, bf.BitLen))
		for (int i = min(this->BitLen, bf.BitLen); i < bf.BitLen; ++i)
			if (bf.GetBit(i))
				res.SetBit(i);
			else if (this->BitLen > min(this->BitLen, bf.BitLen))
				for (int i = min(this->BitLen, bf.BitLen); i < this->BitLen; ++i)
					if (this->GetBit(i))
						res.SetBit(i);
	return res;


}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	
	TBitField res(max(this->BitLen, bf.BitLen));
	for (int i = 0; i < min(this->BitLen, bf.BitLen); ++i)
		if (this->GetBit(i) && bf.GetBit(i))
			res.SetBit(i);
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for (int i = 0; i < MemLen - 1; ++i)
		res.pMem[i] = ~res.pMem[i];
	for (int i = ((res.BitLen - 1) / (sizeof(TELEM) * 8)) * (sizeof(TELEM) * 8); i < res.BitLen; ++i) {
		if (res.GetBit(i) > 0)
			res.ClrBit(i);
		else
			res.SetBit(i);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	
	string s;
	istr >> s;
	for (int i = 0; i < s.size(); ++i)
		((s[i] == '0') ? bf.ClrBit(i) : ((s[i] == '1') ? bf.SetBit(i) : throw - 1));
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	
	for (int i = 0; i < bf.BitLen; ++i)
		ostr << (bf.GetBit(i) ? 1 : 0);
	return ostr;
}