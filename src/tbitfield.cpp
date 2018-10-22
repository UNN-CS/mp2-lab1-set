// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    BitLen = len;
    
    if (BitLen < 1)
    {
		throw(-1);
    }
		
    
    if ((len % sizeof(TELEM)) == 0)
    {
        MemLen = len / sizeof(TELEM);
    }
    else
    {
        MemLen = len / sizeof(TELEM) + 1;
    }
    
    pMem = new TELEM[MemLen];
	for (int i = 0; i<MemLen; i++)
		pMem[i] = 0;
    
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    if (&bf != this)
    
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    
    pMem = new TELEM[MemLen];
    for (int i =0; i<MemLen; i++)
    {
        pMem[i]=bf.pMem[i];
    }
    
}

TBitField::~TBitField()
{
	
	//delete[]pMem;
    BitLen = NULL;
    MemLen = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int m = n % sizeof(TELEM);
    TELEM mask = 1<<m;
    return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw(-1);
    TELEM tempMask=GetMemMask(n);
    if ((pMem[GetMemIndex(n)] & tempMask) == 0)
    {
        pMem[GetMemIndex(n)]+=tempMask;
    }
    
    
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw(-1);
    TELEM tempMask=GetMemMask(n);
    if ((pMem[GetMemIndex(n)] & tempMask) != 0)
    {
        pMem[GetMemIndex(n)]-=tempMask;
    }
}


int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw(-1);
  if ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0)
  {
      return 1;
  }
  else
  {
      return 0;
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf != this)
    {
        
        this->BitLen = bf.BitLen;
        this->MemLen = bf.MemLen;
        for (int i=0; i<MemLen; i++)
        {
            this->pMem[i]=bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if(this->BitLen != bf.BitLen)
    {
        return 0;
    }
    else
    {
        for (int i=0; i<MemLen-1; i++)
        {
            if (this->pMem[i]!=bf.pMem[i])
            {
                return 0;
            }
        }
        
        for (int j = (bf.MemLen-1)*sizeof(TELEM); j<bf.BitLen-1; j++)
        {
            if (this->GetBit(j)!=bf.GetBit(j)) 
            {
                return 0;
            }
        }
    return 1;
    }
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (*this==bf)
  {
      return 0;
  }
  else
  {
      return 1;
  }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    
    if (this->BitLen == bf.BitLen)
    {
        TBitField temp(bf.BitLen);
        for (int i=0; i<bf.BitLen; i++)
        {
            if((this->GetBit(i)) | (bf.GetBit(i)))
            {
                temp.SetBit(i);
            }
        }
        return temp;
    }
    else
    {
        if (this->BitLen < bf.BitLen)
        {
            TBitField temp(bf);
            for (int i=0; i<this->BitLen; i++)
            {
                if (this->GetBit(i)==1)
                {
                    temp.SetBit(i);
                }
            }
			return temp;
        }
        else
        { 
            TBitField temp(*this);
            for (int i=0; i<bf.BitLen; i++)
            {
                if (bf.GetBit(i)==1)
                {
                    temp.SetBit(i);
                }
            }
            return temp;
        }
        
    }
    
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int max, min;
	if (this->BitLen < bf.BitLen)
	{
		max = bf.BitLen;
		min = this->BitLen;
	}
	else
	{
		max = this->BitLen;
		min = bf.BitLen;
	}

	TBitField temp(max);

	for (int i = 0; i<min; i++)
	{
		if ((this->GetBit(i)) & (bf.GetBit(i)))
		{
			temp.SetBit(i);
		}
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(*this);
    for (int i=0; i<temp.BitLen; i++)
    {
        if(temp.GetBit(i)==0)
        {
            temp.SetBit(i);
        }
        else
        {
            temp.ClrBit(i);
        }
    }
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    cin>>bf.BitLen;
    int t;
    for (int i=0; i<bf.BitLen; i++)
    {
        cin>>t;
        switch(t)
        {
            case 1: bf.SetBit(i); break;
            case 0: bf.ClrBit(i); break;
            default: cout<<"Wrong input"<<endl; i--; break;
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i=0; i<bf.BitLen; i++)
    {
        ostr<<bf.GetBit(i)<<" ";
    }
    return ostr;
}