// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if( (len % sizeof(TELEM)) == 0)
        MemLen = len / sizeof(TELEM);
    else
        MemLen = len / sizeof(TELEM) + 1;
    
    BitLen = len;
    
    pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    if (this != &bf) // &bf возвращает адрес объекта
    {
        BitLen = bf.BitLen;
        
        MemLen = bf.MemLen;
        
        pMem = new TELEM[MemLen];
        
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    BitLen = NULL;
    MemLen = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ( (n >= this->BitLen) || (n < 0) )
        throw (-1); // Ошибка, если бита с таким номером нет в массиве или он неположительный
    return (n/sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    // m - позиция бита внутри его Мема
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
	if ((n < 0) || (n >= BitLen))
		throw (-1);

    TELEM tMask = GetMemMask(n);
    
    if ( (pMem[GetMemIndex(n)] & tMask) == 0 )
        pMem[GetMemIndex(n)] += tMask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
		throw (-1);

    TELEM tMask = GetMemMask(n);
    
    if ( (pMem[GetMemIndex(n)] & tMask) != 0 ) // бит == 1
        pMem[GetMemIndex(n)] -= tMask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ( (n < 0) || (n >= BitLen) )
		throw (-1);

    if( (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ) // бит == 1
        return 1;
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) // &bf возвращает адрес объекта
    {
		BitLen = bf.BitLen;

		if (MemLen != bf.MemLen)
		{
			delete[] pMem;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}

        /* for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i]; */

		copy(bf.pMem, bf.pMem + MemLen, pMem);
    }
    
    return(*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen)
    {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
        
        int Attit = BitLen % sizeof(TELEM);
        
        for (int j = 0; j < Attit; j++)
            if ( GetBit(BitLen - Attit + j) != bf.GetBit(BitLen - Attit + j) )
                return 0;
                
        return 1;
    }
    return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int Maxlen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField Temp(Maxlen);
    for (int i = 0; i < ( (BitLen > bf.BitLen) ? bf.BitLen : BitLen ); i++)
        if (GetBit(i) || bf.GetBit(i))
            Temp.SetBit(i);
        else
            Temp.ClrBit(i);
            
    if (BitLen > bf.BitLen)
        for (int j = bf.BitLen - 1; j < BitLen; j++)
            if(GetBit(j))
                Temp.SetBit(j);
            else
                Temp.ClrBit(j);
    if (BitLen < bf.BitLen)
        for (int k = BitLen - 1; k < bf.BitLen; k++)
            if(bf.GetBit(k))
                Temp.SetBit(k);
            else
                Temp.ClrBit(k);
                
    return Temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int Maxlen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField Temp(Maxlen);
    for (int i = 0; i < ( (BitLen > bf.BitLen) ? bf.BitLen : BitLen ); i++)
        if (GetBit(i) && bf.GetBit(i))
            Temp.SetBit(i);
        else
            Temp.ClrBit(i);
            
    if (BitLen > bf.BitLen)
        for (int j = bf.BitLen - 1; j < BitLen; j++)
            if(GetBit(j))
                Temp.SetBit(j);
            else
                Temp.ClrBit(j);
    if (BitLen < bf.BitLen)
        for (int k = BitLen - 1; k < bf.BitLen; k++)
            if(bf.GetBit(k))
                Temp.SetBit(k);
            else
                Temp.ClrBit(k);
                
    return Temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField Temp(BitLen);
    
    for (int i = 0; i < BitLen; i++)
        if(GetBit(i))
            Temp.ClrBit(i);
        else
            Temp.SetBit(i);
            
    return Temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int bit;
    for (int i = 0; i < bf.GetLength(); i++)
    {
        istr >> bit;
        switch(bit)
        {
            case 1: bf.SetBit(i); break;
            case 0: bf.ClrBit(i); break;
            default: cout << "WRONG" << endl; i = 0; break;
        }
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++)
        ostr << bf.GetBit(i) << " ";
    
    ostr << endl;
    return ostr;
}