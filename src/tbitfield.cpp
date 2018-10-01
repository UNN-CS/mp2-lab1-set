// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if(len<=0) throw -2;
     BitLen = len;
      
	MemLen = (BitLen/(sizeof(TELEM)*8))+1;
    pMem = new TELEM[MemLen];
    for(int i = 0;i<MemLen;i++)
     pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for(int i = 0;i<MemLen;i++)
     pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if(n<0 || n>=BitLen) throw -1;
    return (n/(sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if(n<0 || n>=BitLen) throw -1;
        TELEM m = 1;
    m <<= (n-(GetMemIndex(n)*sizeof(TELEM)*8));
    return m;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
   return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if(n<0 || n>=BitLen) throw -1;
     pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if(n<0 || n>=BitLen) throw -1;
     pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if(n<0 || n>=BitLen) throw -1;
     if(((pMem[GetMemIndex(n)])&(GetMemMask(n))) == 0)
      return 0;
     else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if(this != &bf)
    {
        if(BitLen == bf.BitLen)
        {
            for(int i = 0;i<BitLen;i++)
            {
                if(bf.GetBit(i) == 0) ClrBit(i);
                else SetBit(i);
            }
        }
        else
        {
            BitLen = bf.BitLen;
            MemLen = bf.MemLen;
            pMem = new TELEM[MemLen];
            for(int i = 0;i<MemLen;i++)
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if(BitLen == bf.BitLen)
    {
        if((BitLen/32)!=((BitLen+1)/32))
        {
            for(int i = 0;i<MemLen;i++)
             if(pMem[i]!=bf.pMem[i]) return 0;
            return 1;
        }
          else
          {
            for(int i = 0;i<(MemLen-1);i++)
             if(pMem[i]!=bf.pMem[i]) return 0;
            int p = (MemLen-1)*sizeof(TELEM)*8;
            for(int l = p;l<BitLen;l++)
            {
                if(GetBit(l)!=bf.GetBit(l)) return 0;
            }
            return 1;
          }
    }
    else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if(*this == bf) return 0;
   else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if(BitLen!=bf.BitLen)
    {
        if(BitLen < bf.BitLen)
        {
            TBitField tmp(bf.BitLen);
            TBitField t1(bf.BitLen);
            for(int i = 0;i<BitLen;i++)
             if(GetBit(i) == 1) t1.SetBit(i);

            for(int i = 0;i<t1.BitLen;i++)
            {
                if((t1.GetBit(i) == 0)&&(bf.GetBit(i) == 0))
                tmp.ClrBit(i);
                else tmp.SetBit(i);
            }
            return tmp;
        }
       if(BitLen > bf.BitLen)
        {
            TBitField tmp(BitLen);
            TBitField t2(BitLen);
            for(int i = 0;i<bf.BitLen;i++)
             if(bf.GetBit(i) == 1) t2.SetBit(i);

            for(int i = 0;i<BitLen;i++)
            {
                if((GetBit(i) == 0)&&(t2.GetBit(i) == 0))
                tmp.ClrBit(i);
                else tmp.SetBit(i);
            }
            return tmp;
        }
    }
    TBitField tmp(BitLen);
    for(int i = 0;i<BitLen;i++)
    {
        if((GetBit(i) == 0)&&(bf.GetBit(i) == 0))
         tmp.ClrBit(i);
        else tmp.SetBit(i);
    }
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if(BitLen!=bf.BitLen)
    {
        if(BitLen < bf.BitLen)
        {
            TBitField tmp(bf.BitLen);
            TBitField t1(bf.BitLen);
            for(int i = 0;i<BitLen;i++)
             if(GetBit(i) == 1) t1.SetBit(i);

            for(int i = 0;i<t1.BitLen;i++)
            {
                if((t1.GetBit(i) == 1)&&(bf.GetBit(i) == 1))
                tmp.SetBit(i);
                else tmp.ClrBit(i);
            }
            return tmp;
        }

        if(BitLen > bf.BitLen)
        {
            TBitField tmp(BitLen);
            TBitField t2(BitLen);
            for(int i = 0;i<bf.BitLen;i++)
             if(bf.GetBit(i) == 1) t2.SetBit(i);

            for(int i = 0;i<BitLen;i++)
            {
                if((GetBit(i) == 1)&&(t2.GetBit(i) == 1))
                tmp.SetBit(i);
                else tmp.ClrBit(i);
            }
            return tmp;
        }
    }
    TBitField tmp(BitLen);
    for(int i = 0;i<BitLen;i++)
    {
        if((GetBit(i) == 1)&&(bf.GetBit(i) == 1)) tmp.SetBit(i);
        else tmp.ClrBit(i);
    }
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(*this);
    for(int i = 0;i<BitLen;i++)
    {
        if(GetBit(i) == 1) tmp.ClrBit(i);
        else tmp.SetBit(i);
    }
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int t;
    for(int i = 0;i<bf.BitLen;i++)
    {
        cout<<"Enter bit number("<<i<<"): ";
        istr>>t;
        if(t!=1 && t!=0)
        {
            cout<<"Wrong value. You should to enter 0 or 1"<<endl;
            i--;
        }
        if(t == 1) bf.SetBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for(int i = bf.BitLen - 1;i>=0;i--)
    {
        ostr<<bf.GetBit(i);
    }
    ostr << endl;
    return ostr;
}