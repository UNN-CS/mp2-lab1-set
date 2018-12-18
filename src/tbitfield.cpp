<<<<<<< HEAD
// ÃÃÄ‚Ã“, Ã‚ÄšÄ˜, Ä˜Ã³Ä‘Å„ "ÄšÄºÅˆÃ®Ã¤Å± ÄÄ‘Ã®ÄƒÄ‘Å•Ä›Ä›ÄÄ‘Ã®Ã¢Å•Ã­ÄË™-2", Åƒ++, ÃŽÃŽÄŽ
//
// tbitfield.cpp - Copyright (c) Ä‚ÄºÄ‘ÄƒÄºÃ«Ã¼ Ã‚.ÄŽ. 07.05.2001
//   ÄŽÄºÄ‘ÄºÄ‘Å•Ã¡Ã®ÅˆÅ•Ã­Ã® Ã¤Ã«Ë™ Microsoft Visual Studio 2008 ÅƒÅ±Å„Ã®ÄºÃ¢Å±Ä› Å”.Ã‚. (19.04.2015)
//
// ÃÄÅˆÃ®Ã¢Ã®Äº ÄÃ®Ã«Äº
=======
// ÍÍÃÓ, ÂÌÊ, Êóðñ "Ìåòîäû ïðîãðàììèðîâàíèÿ-2", Ñ++, ÎÎÏ
//
// tbitfield.cpp - Copyright (c) Ãåðãåëü Â.Ï. 07.05.2001
//   Ïåðåðàáîòàíî äëÿ Microsoft Visual Studio 2008 Ñûñîåâûì À.Â. (19.04.2015)
//
// Áèòîâîå ïîëå

>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7

#include <math.h>
#include "tbitfield.h"

TBitField::TBitField(int len)

{

	if (len < 0)
		throw "error";

<<<<<<< HEAD
	MemLen = ceil(static_cast<double>(len) / (sizeof(TELEM) * 8));
=======
	MemLen = ceil(static_cast<double>(len) / (sizeof(TELEM)* 8));
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
	BitLen = len;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

<<<<<<< HEAD
TBitField::TBitField(const TBitField &bf) // Ä™Ã®Ã­Å„ÅˆÄ‘Ã³Ä™ÅˆÃ®Ä‘ Ä™Ã®ÄÄÄ‘Ã®Ã¢Å•Ã­ÄË™
=======
TBitField::TBitField(const TBitField &bf) // êîíñòðóêòîð êîïèðîâàíèÿ
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];

	for (int i = MemLen - 1; i >= 0; i--)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

<<<<<<< HEAD
int TBitField::GetMemIndex(const int n) const // ÄÃ­Ã¤ÄºÄ™Å„ ÄšÄºÄ› Ã¤Ã«Ë™ Ã¡ÄÅˆÅ• n
=======
int TBitField::GetMemIndex(const int n) const // èíäåêñ Ìåì äëÿ áèòà n
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	if (n < 0 || n > BitLen)
		throw "error";
	else if (n != 0)
<<<<<<< HEAD
		return MemLen - ceil(static_cast<double>(n) / (sizeof(TELEM) * 8));
=======
		return MemLen - ceil(static_cast<double>(n) / (sizeof(TELEM)* 8));
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
	else
		return MemLen - 1;
}

<<<<<<< HEAD
TELEM TBitField::GetMemMask(const int n) const // Ã¡ÄÅˆÃ®Ã¢Å•Ë™ Ä›Å•Å„Ä™Å• Ã¤Ã«Ë™ Ã¡ÄÅˆÅ• n
=======
TELEM TBitField::GetMemMask(const int n) const // áèòîâàÿ ìàñêà äëÿ áèòà n
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	if (n < 0 || n > BitLen)
		throw "error";
	else
		return 1 << n;
}

<<<<<<< HEAD
// Ã¤Ã®Å„ÅˆÃ³Ä Ä™ Ã¡ÄÅˆÅ•Ä› Ã¡ÄÅˆÃ®Ã¢Ã®ÄƒÃ® ÄÃ®Ã«Ë™

int TBitField::GetLength(void) const // ÄÃ®Ã«Ã³Ã·ÄÅˆÃ¼ Ã¤Ã«ÄÃ­Ã³ (Ä™-Ã¢Ã® Ã¡ÄÅˆÃ®Ã¢)
=======
// äîñòóï ê áèòàì áèòîâîãî ïîëÿ

int TBitField::GetLength(void) const // ïîëó÷èòü äëèíó (ê-âî áèòîâ)
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	return BitLen;
}

<<<<<<< HEAD
void TBitField::SetBit(const int n) // Ã³Å„ÅˆÅ•Ã­Ã®Ã¢ÄÅˆÃ¼ Ã¡ÄÅˆ
=======
void TBitField::SetBit(const int n) // óñòàíîâèòü áèò
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	if (n < 0 || n > BitLen)
		throw "error";
	else if (GetBit(n) != 1)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

<<<<<<< HEAD
void TBitField::ClrBit(const int n) // Ã®Ã·ÄÅ„ÅˆÄÅˆÃ¼ Ã¡ÄÅˆ
=======
void TBitField::ClrBit(const int n) // î÷èñòèòü áèò
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	if (n < 0 || n > BitLen)
		throw "error";
	else if (GetBit(n) != 0)
		pMem[GetMemIndex(n)] ^= GetMemMask(n);
}

<<<<<<< HEAD
int TBitField::GetBit(const int n) const // ÄÃ®Ã«Ã³Ã·ÄÅˆÃ¼ Ã§Ã­Å•Ã·ÄºÃ­ÄÄº Ã¡ÄÅˆÅ•
=======
int TBitField::GetBit(const int n) const // ïîëó÷èòü çíà÷åíèå áèòà
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	if (n < 0 || n > BitLen)
		throw "Unexpected bit index";
	else
		return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ? 1 : 0;
}

<<<<<<< HEAD
// Ã¡ÄÅˆÃ®Ã¢Å±Äº Ã®ÄÄºÄ‘Å•Ã¶ÄÄ

TBitField& TBitField::operator = (const TBitField &bf) // ÄÄ‘ÄÅ„Ã¢Å•ÄÃ¢Å•Ã­ÄÄº
=======
// áèòîâûå îïåðàöèè

TBitField& TBitField::operator = (const TBitField &bf) // ïðèñâàèâàíèå
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	if (bf.MemLen == 0)
		throw "error";
	else
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];

		for (int i = MemLen - 1; i >= 0; i--)
		{
			pMem[i] = bf.pMem[i];
		}

		return *this;
	}
}

<<<<<<< HEAD
int TBitField::operator == (const TBitField &bf) const // Å„Ä‘Å•Ã¢Ã­ÄºÃ­ÄÄº
=======
int TBitField::operator == (const TBitField &bf) const // ñðàâíåíèå
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	if (bf.MemLen == 0)
		throw "error";
	else
	{
		bool check = 1;
		int length;

		if (BitLen >= bf.BitLen)
		{
			length = bf.MemLen - 1;
			for (int i = MemLen - 1; i >= bf.MemLen - 1; i--, length--)
			{
				check &= pMem[i] == bf.pMem[length];
			}
		}
		else
		{
			length = MemLen - 1;
			for (int i = bf.MemLen - 1; i >= MemLen - 1; i--, length--)
			{
				check &= pMem[length] == bf.pMem[i];
			}
		}

		return check;
	}
}

<<<<<<< HEAD
int TBitField::operator != (const TBitField &bf) const // Å„Ä‘Å•Ã¢Ã­ÄºÃ­ÄÄº
=======
int TBitField::operator != (const TBitField &bf) const // ñðàâíåíèå
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	return !(operator==(bf));
}

<<<<<<< HEAD
TBitField TBitField::operator|(const TBitField &bf) // Ã®ÄÄºÄ‘Å•Ã¶ÄË™ "ÄÃ«Ä"
=======
TBitField TBitField::operator|(const TBitField &bf) // îïåðàöèÿ "èëè"
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	int len = BitLen;

	if (BitLen < bf.BitLen)
		len = bf.BitLen;

	TBitField tmp(len);

	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];

	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];

	return tmp;
}

<<<<<<< HEAD
TBitField TBitField::operator & (const TBitField &bf) // Ã®ÄÄºÄ‘Å•Ã¶ÄË™ "Ä"
=======
TBitField TBitField::operator & (const TBitField &bf) // îïåðàöèÿ "è"
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	int len = BitLen;

	if (bf.BitLen > len)
		len = bf.BitLen;

	TBitField temp(len);

	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];

	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];

	return temp;
}

<<<<<<< HEAD
TBitField TBitField::operator~ (void) // Ã®ÅˆÄ‘ÄÃ¶Å•Ã­ÄÄº
=======
TBitField TBitField::operator~ (void) // îòðèöàíèå
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	TBitField tmp(BitLen);
	TELEM mask = 0;

<<<<<<< HEAD
	for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
=======
	for (int i = (MemLen - 1) * sizeof(TELEM)* 8; i < BitLen; i++)
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
		mask += GetMemMask(i);
	tmp.pMem[0] = pMem[0] ^ mask;

	for (int i = MemLen - 1; i > 0; i--)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

<<<<<<< HEAD
// Ã¢Ã¢Ã®Ã¤/Ã¢Å±Ã¢Ã®Ã¤

istream &operator>>(istream &istr, TBitField &bf) // Ã¢Ã¢Ã®Ã¤
=======
// ââîä/âûâîä

istream &operator>>(istream &istr, TBitField &bf) // ââîä
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
{
	int i = 0;
	char ch;
	do { istr >> ch; } while (ch != ' ');
	while (1)
	{
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else if (ch == '1')
			bf.SetBit(i++);
		else break;
	}
	return istr;
}

<<<<<<< HEAD
ostream &operator<<(ostream &ostr, const TBitField &bf) // Ã¢Å±Ã¢Ã®Ã¤
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
=======
ostream &operator<<(ostream &ostr, const TBitField &bf) // âûâîä
{
	for (int i = 0; i < bf.GetLength(); i++)
	if (bf.GetBit(i)) ostr << '1';
	else ostr << '0';
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
	return ostr;
}