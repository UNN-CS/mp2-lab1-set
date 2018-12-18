<<<<<<< HEAD
п»ї// ГЌГЌД‚Г“, Г‚ДљД, ДГіД‘Е„ "ДљДєЕ€Г®Г¤Е± ДЏД‘Г®ДѓД‘Е•Д›Д›ДЌД‘Г®ГўЕ•Г­ДЌЛ™-2", Еѓ++, ГЋГЋДЋ
=======
<<<<<<< HEAD
// ГЌГЌД‚Г“, Г‚ДљД, ДГіД‘Е„ "ДљДєЕ€Г®Г¤Е± ДЏД‘Г®ДѓД‘Е•Д›Д›ДЌД‘Г®ГўЕ•Г­ДЌЛ™-2", Еѓ++, ГЋГЋДЋ
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
//
// tbitfield.cpp - Copyright (c) Д‚ДєД‘ДѓДєГ«Гј Г‚.ДЋ. 07.05.2001
//   ДЋДєД‘ДєД‘Е•ГЎГ®Е€Е•Г­Г® Г¤Г«Л™ Microsoft Visual Studio 2008 ЕѓЕ±Е„Г®ДєГўЕ±Д› Е”.Г‚. (19.04.2015)
//
// ГЃДЌЕ€Г®ГўГ®Дє ДЏГ®Г«Дє
<<<<<<< HEAD

=======
=======
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7

>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
#include <math.h>
#include "tbitfield.h"

TBitField::TBitField(int len)

{

	if (len < 0)
		throw "error";

<<<<<<< HEAD
	MemLen = ceil(static_cast<double>(len) / (sizeof(TELEM)* 8));
=======
<<<<<<< HEAD
	MemLen = ceil(static_cast<double>(len) / (sizeof(TELEM) * 8));
=======
	MemLen = ceil(static_cast<double>(len) / (sizeof(TELEM)* 8));
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
	BitLen = len;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

<<<<<<< HEAD
TBitField::TBitField(const TBitField &bf) // Д™Г®Г­Е„Е€Д‘ГіД™Е€Г®Д‘ Д™Г®ДЏДЌД‘Г®ГўЕ•Г­ДЌЛ™
=======
<<<<<<< HEAD
TBitField::TBitField(const TBitField &bf) // Д™Г®Г­Е„Е€Д‘ГіД™Е€Г®Д‘ Д™Г®ДЏДЌД‘Г®ГўЕ•Г­ДЌЛ™
=======
TBitField::TBitField(const TBitField &bf) // конструктор копирования
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
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
int TBitField::GetMemIndex(const int n) const // ДЌГ­Г¤ДєД™Е„ ДљДєД› Г¤Г«Л™ ГЎДЌЕ€Е• n
=======
<<<<<<< HEAD
int TBitField::GetMemIndex(const int n) const // ДЌГ­Г¤ДєД™Е„ ДљДєД› Г¤Г«Л™ ГЎДЌЕ€Е• n
=======
int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	if (n < 0 || n > BitLen)
		throw "error";
	else if (n != 0)
<<<<<<< HEAD
		return MemLen - ceil(static_cast<double>(n) / (sizeof(TELEM)* 8));
=======
<<<<<<< HEAD
		return MemLen - ceil(static_cast<double>(n) / (sizeof(TELEM) * 8));
=======
		return MemLen - ceil(static_cast<double>(n) / (sizeof(TELEM)* 8));
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
	else
		return MemLen - 1;
}

<<<<<<< HEAD
TELEM TBitField::GetMemMask(const int n) const // ГЎДЌЕ€Г®ГўЕ•Л™ Д›Е•Е„Д™Е• Г¤Г«Л™ ГЎДЌЕ€Е• n
=======
<<<<<<< HEAD
TELEM TBitField::GetMemMask(const int n) const // ГЎДЌЕ€Г®ГўЕ•Л™ Д›Е•Е„Д™Е• Г¤Г«Л™ ГЎДЌЕ€Е• n
=======
TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	if (n < 0 || n > BitLen)
		throw "error";
	else
		return 1 << n;
}

<<<<<<< HEAD
// Г¤Г®Е„Е€ГіДЏ Д™ ГЎДЌЕ€Е•Д› ГЎДЌЕ€Г®ГўГ®ДѓГ® ДЏГ®Г«Л™

int TBitField::GetLength(void) const // ДЏГ®Г«ГіГ·ДЌЕ€Гј Г¤Г«ДЌГ­Гі (Д™-ГўГ® ГЎДЌЕ€Г®Гў)
=======
<<<<<<< HEAD
// Г¤Г®Е„Е€ГіДЏ Д™ ГЎДЌЕ€Е•Д› ГЎДЌЕ€Г®ГўГ®ДѓГ® ДЏГ®Г«Л™

int TBitField::GetLength(void) const // ДЏГ®Г«ГіГ·ДЌЕ€Гј Г¤Г«ДЌГ­Гі (Д™-ГўГ® ГЎДЌЕ€Г®Гў)
=======
// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	return BitLen;
}

<<<<<<< HEAD
void TBitField::SetBit(const int n) // ГіЕ„Е€Е•Г­Г®ГўДЌЕ€Гј ГЎДЌЕ€
=======
<<<<<<< HEAD
void TBitField::SetBit(const int n) // ГіЕ„Е€Е•Г­Г®ГўДЌЕ€Гј ГЎДЌЕ€
=======
void TBitField::SetBit(const int n) // установить бит
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	if (n < 0 || n > BitLen)
		throw "error";
	else if (GetBit(n) != 1)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

<<<<<<< HEAD
void TBitField::ClrBit(const int n) // Г®Г·ДЌЕ„Е€ДЌЕ€Гј ГЎДЌЕ€
=======
<<<<<<< HEAD
void TBitField::ClrBit(const int n) // Г®Г·ДЌЕ„Е€ДЌЕ€Гј ГЎДЌЕ€
=======
void TBitField::ClrBit(const int n) // очистить бит
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	if (n < 0 || n > BitLen)
		throw "error";
	else if (GetBit(n) != 0)
		pMem[GetMemIndex(n)] ^= GetMemMask(n);
}

<<<<<<< HEAD
int TBitField::GetBit(const int n) const // ДЏГ®Г«ГіГ·ДЌЕ€Гј Г§Г­Е•Г·ДєГ­ДЌДє ГЎДЌЕ€Е•
=======
<<<<<<< HEAD
int TBitField::GetBit(const int n) const // ДЏГ®Г«ГіГ·ДЌЕ€Гј Г§Г­Е•Г·ДєГ­ДЌДє ГЎДЌЕ€Е•
=======
int TBitField::GetBit(const int n) const // получить значение бита
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	if (n < 0 || n > BitLen)
		throw "Unexpected bit index";
	else
		return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ? 1 : 0;
}

<<<<<<< HEAD
// ГЎДЌЕ€Г®ГўЕ±Дє Г®ДЏДєД‘Е•Г¶ДЌДЌ

TBitField& TBitField::operator = (const TBitField &bf) // ДЏД‘ДЌЕ„ГўЕ•ДЌГўЕ•Г­ДЌДє
=======
<<<<<<< HEAD
// ГЎДЌЕ€Г®ГўЕ±Дє Г®ДЏДєД‘Е•Г¶ДЌДЌ

TBitField& TBitField::operator = (const TBitField &bf) // ДЏД‘ДЌЕ„ГўЕ•ДЌГўЕ•Г­ДЌДє
=======
// битовые операции

TBitField& TBitField::operator = (const TBitField &bf) // присваивание
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
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
int TBitField::operator == (const TBitField &bf) const // Е„Д‘Е•ГўГ­ДєГ­ДЌДє
=======
<<<<<<< HEAD
int TBitField::operator == (const TBitField &bf) const // Е„Д‘Е•ГўГ­ДєГ­ДЌДє
=======
int TBitField::operator == (const TBitField &bf) const // сравнение
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
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
int TBitField::operator != (const TBitField &bf) const // Е„Д‘Е•ГўГ­ДєГ­ДЌДє
=======
<<<<<<< HEAD
int TBitField::operator != (const TBitField &bf) const // Е„Д‘Е•ГўГ­ДєГ­ДЌДє
=======
int TBitField::operator != (const TBitField &bf) const // сравнение
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	return !(operator==(bf));
}

<<<<<<< HEAD
TBitField TBitField::operator|(const TBitField &bf) // Г®ДЏДєД‘Е•Г¶ДЌЛ™ "ДЌГ«ДЌ"
=======
<<<<<<< HEAD
TBitField TBitField::operator|(const TBitField &bf) // Г®ДЏДєД‘Е•Г¶ДЌЛ™ "ДЌГ«ДЌ"
=======
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
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
TBitField TBitField::operator & (const TBitField &bf) // Г®ДЏДєД‘Е•Г¶ДЌЛ™ "ДЌ"
=======
<<<<<<< HEAD
TBitField TBitField::operator & (const TBitField &bf) // Г®ДЏДєД‘Е•Г¶ДЌЛ™ "ДЌ"
=======
TBitField TBitField::operator & (const TBitField &bf) // операция "и"
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
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
TBitField TBitField::operator~ (void) // Г®Е€Д‘ДЌГ¶Е•Г­ДЌДє
=======
<<<<<<< HEAD
TBitField TBitField::operator~ (void) // Г®Е€Д‘ДЌГ¶Е•Г­ДЌДє
=======
TBitField TBitField::operator~ (void) // отрицание
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
{
	TBitField tmp(BitLen);
	TELEM mask = 0;

<<<<<<< HEAD
	for (int i = (MemLen - 1) * sizeof(TELEM)* 8; i < BitLen; i++)
=======
<<<<<<< HEAD
	for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
=======
	for (int i = (MemLen - 1) * sizeof(TELEM)* 8; i < BitLen; i++)
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
		mask += GetMemMask(i);
	tmp.pMem[0] = pMem[0] ^ mask;

	for (int i = MemLen - 1; i > 0; i--)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

<<<<<<< HEAD
// ГўГўГ®Г¤/ГўЕ±ГўГ®Г¤

istream &operator>>(istream &istr, TBitField &bf) // ГўГўГ®Г¤
=======
<<<<<<< HEAD
// ГўГўГ®Г¤/ГўЕ±ГўГ®Г¤

istream &operator>>(istream &istr, TBitField &bf) // ГўГўГ®Г¤
=======
// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
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
ostream &operator<<(ostream &ostr, const TBitField &bf) // ГўЕ±ГўГ®Г¤
{
	for (int i = 0; i < bf.GetLength(); i++)
	if (bf.GetBit(i)) ostr << '1';
	else ostr << '0';
=======
<<<<<<< HEAD
ostream &operator<<(ostream &ostr, const TBitField &bf) // ГўЕ±ГўГ®Г¤
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
=======
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
	if (bf.GetBit(i)) ostr << '1';
	else ostr << '0';
>>>>>>> fd8649f96a184ed262dd1aab6e5f32eddf50e9c7
>>>>>>> d2aeda11f914a428afdea9384c5ffdaebe877fe5
	return ostr;
}