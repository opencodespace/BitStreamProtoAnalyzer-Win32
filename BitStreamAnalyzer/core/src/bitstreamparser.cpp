
 /*
  *    GENERAL PUBLIC LICENSE
  *    Version 3
  *
  *    Copyright(C) 2016 Guru Shanker S
  *    E - mail: shanker_gs@yahoo.com
  *    Dt: July 2016
  *
  *    This program is free software : you can redistribute it and / or modify
  *    it under the terms of the GNU General Public License as published by
  *    the Free Software Foundation, either version 3 of the License, or
  *    (at your option) any later version.
  *
  *    This program is distributed in the hope that it will be useful,
  *    but WITHOUT ANY WARRANTY; without even the implied warranty of
  *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
  *    GNU General Public License for more details.
  *
  *    You should have received a copy of the GNU General Public License
  *    along with this program.If not, see <http://www.gnu.org/licenses/>.
  */

/*
 *
 * Change History: 
 *					
 *	Dt: 26-Feb-2013
 *	Change: Modification done to function SetBitsInAByte(); bug fixed.
 *
 */


#include "stdafx.h"
#include "bitstreamparser.h"

#if 0
// This is sample code for testing
#include<stdio.h>
/* 
 * The Main function is -> SetValue(char* buf, int startBit, int endBit, int value);
 * Functions SetBitsInAByte ->  SetBitsInAByteMethod2 are same
 *  
 */

void SetValue(char* buf, int startBit, int endBit, int value);
void SetBitsInAByte(char* buf, int start, int end, int val);
void SetBitsInAByteMethod2(char* buf, int start, int end, int val);
void PrintBitStream(char* byte1, int length);
char GetByteVal(int startValBitPos, int extractBitLen, int bitLenOfValue, int val);
void ClearBits(char* buf, int startPos, int endPos);

char buf[25] = {0};


int main()
{
	printf("Hellow world\n");

	PrintBitStream(buf, 4);
	printf("\n");

	SetBitsInAByte(buf, 2, 4, 7);

	PrintBitStream(buf, 4);


	printf("\n==============>");
	SetValue(buf, 6, 10, 23);

	PrintBitStream(buf, 25);

	printf("\n==============>");

	SetValue(buf, 9, 10, 0);

	PrintBitStream(buf, 25);

	getchar();

	return 0;
}

#endif



void SetBitsInAByte(char* buf, int start, int end, int val);
void SetBitsInAByteMethod2(char* buf, int start, int end, int val);

char GetByteVal(int startValBitPos, int extractBitLen, int bitLenOfValue, int val);
void ClearBits(char* buf, int startPos, int endPos);

// Bits between start and end positions have to be cleared before calling
// this function
void SetBitsInAByte(char* buf, int start, int end, int val)
{
	/*
	// Old code as on 26-Feb-2015
	int binLen = end - start + 1;
	int nCtr = 0;
	char* buf1 = (char*)&val;

	for(nCtr = 0; nCtr < binLen; nCtr++)
	{
		if(buf1[0] &(1<<(binLen-nCtr-1)))
		{
			buf[0] = buf[0] | (1<<((8-start) - nCtr));
		}
		else
		{
			buf[0] &= ~((1<<((8-start) - nCtr)));
		}
	}
	*/

	// Modified on 26-Feb-2013

	int nNoOfBitsToModify = end - start + 1;
	int nBitMap = 0;

	// BitMap makes sure that only bits set in the BitMap are 
	// altered in the destination; its like a gaurd not to
	// modify unwanted left are right bits (beyond start to end).
	nBitMap = (0xFF>>(start-1)) & (0xFF<<(8-end));

	// Shitf the value to set to the correct location
	// any leading values beyond start position (left to start position)
	// will be lost
	nBitMap = nBitMap & (val<<(8-end));

	buf[0] = buf[0] | nBitMap;
}

void SetBitsInAByteMethod2(char* buf, int start, int end, int val)
{
	int noOfBitsToModify = end - start +1;
	char bitMaskForTargetBits;
	char* buf1 = (char*)&val;

	// Clear all the bits except only the required bits
	// ie. the required number of bits from left to right -> noOfBitsToModify
	buf1[0] = buf1[0] & (0xFF >> (8-noOfBitsToModify));

	// move the bits except only hte required bits
	buf1[0] = buf1[0] << (8-end);

	// Clear the target bit positions in the dest type
	bitMaskForTargetBits = (0xFF << (8-end)) & (0xFF >> (start - 1));

	buf1[0] = buf1[0] & bitMaskForTargetBits;

	// Set the required bits in the destination byte
	buf[0] = buf[0] | buf1[0];
}

void ClearBits(char* buf, int startPos, int endPos)
{
	char ch;
	int lExBits = startPos - 1;
	int rExBits = 8 - endPos;

	ch = ~((0xFF>>lExBits) & (0xFF<<rExBits));

	*buf &= ch;
}

char GetByteVal(int startValBitPos, int extractBitLen, int bitLenOfValue, int val)
{
	int lExBits = 0;
	int rExBits = 0;
	int bitMap = 0;
	int result = 0;
	char ch = 0;

	lExBits = 32 - bitLenOfValue;
	lExBits = lExBits + startValBitPos - 2;
	rExBits = bitLenOfValue - extractBitLen - startValBitPos + 2;

	//bitMap = (0xFFFFFFFF<<rExBits) & (0xFFFFFFFF<<lExBits);
	bitMap = (0xFFFFFFFF<<rExBits) & (0xFFFFFFFF>>lExBits);
	result = (val & bitMap);
	result = result>>rExBits;

	ch = result;

	return ch;
}

void SetValue(char* buf, int startBit, int endBit, int value)
{
	int nCtr;
	char* byte;
	int leadingBitLen	= 0;
	int leadingBitsEndByte = 0;
	int endBitLen		= 0;
	int trailingBitsStartByte = 0;
	int startByteIndex = startBit/8;
	int noOfBytes = endBit/8 - startBit/8; 

	// Incase if the bit is the last in byte
	if(startBit%8 == 0)
		startByteIndex--;

	if(startBit%8 == 0)
		noOfBytes++;

	if(endBit%8 != 0)
		noOfBytes++;

	trailingBitsStartByte = ((startByteIndex + 1)*8 - startBit) + 1;
	leadingBitsEndByte		= endBit % 8;

	if(leadingBitsEndByte == 0)
		leadingBitsEndByte = 8;

	byte = (char*)&value;

	if(noOfBytes == 1)
	{
		int noOfBytes = 0;
		int bitMap = 0xFF;
		
		startBit = startBit % 8;
		endBit = endBit % 8;

		if(startBit == 0)
			startBit = 8;

		if(endBit == 0)
			endBit = 8;


		ClearBits(&buf[startByteIndex], startBit, endBit);
		SetBitsInAByte(&buf[startByteIndex], startBit, endBit, value);
	}
	else
	{
		char ch;

		int firstBitInStartByte = 8 - trailingBitsStartByte + 1;

		for(nCtr = 0; nCtr < noOfBytes; nCtr++)
		{
			if(nCtr == 0)
			{
				ClearBits(&buf[startByteIndex + nCtr], firstBitInStartByte, 8);

				ch = GetByteVal(1, trailingBitsStartByte, endBit - startBit, value);

				SetBitsInAByte(&buf[startByteIndex +  nCtr], firstBitInStartByte, 8, ch);
			}
			else if(nCtr == noOfBytes - 1)
			{
				int endByteLen;
				endByteLen = endBit - startBit - (nCtr -1)*8 - trailingBitsStartByte + 1;

				ClearBits(&buf[startByteIndex + nCtr], 1, leadingBitsEndByte);

				ch = GetByteVal(1 + trailingBitsStartByte + (nCtr - 1)*8, endByteLen, endBit - startBit, value);

				SetBitsInAByte(&buf[startByteIndex + nCtr], 1, endByteLen, ch);
			}
			else
			{
				ClearBits(&buf[startByteIndex + nCtr], 1, 8);

				ch = GetByteVal(1 + trailingBitsStartByte + (nCtr -1)*8, 8, endBit - startBit, value);

				SetBitsInAByte(&buf[startByteIndex + nCtr], 1, 8, ch);
			}
		}
	}
	

}

void PrintBitStream(char* byte1, int length)
{
	int cnt, cnt1=0;

	for(cnt=0; cnt < length; cnt++)
	{
		cnt1=7;
		while(cnt1>=0)
		{
			if((*byte1)&(1<<cnt1))
				printf("1");
			else
				printf("0");

			cnt1--;
		}
		printf(" ");
		byte1++;

	}
}