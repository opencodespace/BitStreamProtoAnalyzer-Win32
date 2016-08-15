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

#include "stdafx.h"
#include "math.h"
#include "bytetobitconversions.h"

// The below macro sets the value '0' or '1' provided by the param 'VALUE' in to the destination byte
// param 'DESTBYTE' at a location given by param 'POSITION'
// Param1 DESTBYTE is a variable of type byte/char
// Param2 POSITION is the location of the bit whose values will be updated; Range 1 to 8
// Param3 VALUE is the value to be set to the bit; Value range '0' or '1'
#define SET_VALUE_TO_BIT_IN_BYTE(DESTBYTE, POSITION, VALUE)	\
						(DESTBYTE = ( (DESTBYTE & (~(1<<(POSITION-1)))) | (VALUE<<(POSITION-1)) ))
#define GET_VALUE_OF_BIT_IN_BYTE(SRCBYTE, POSITION) \
						((SRCBYTE & (1 <<(POSITION -1))) ? 1 : 0)

inline void setValueToBitInByte(char* destByte, int position, char value)
{
	destByte[0] = (destByte[0] & (~(1<<(position-1)))) | (value<<(position-1));
}

inline char getValueOfBitInByte(char srcByte, int position)
{
	char ch;

	ch = (srcByte & (1 <<(8- position))) ? '1' : '0';

	return ch;
}

char* convertByteRepToBitRep(char* pszBuff, int len)
{
	int i;
	int bytesLeft;
	int dstByteIndx = 0;
	char* pBitSeq = NULL;
	int nNoOfBytes = len/8;

	if((len%8) > 0)
		nNoOfBytes++;

	pBitSeq = (char*)malloc(nNoOfBytes*sizeof(char));

	memset(pBitSeq, 0, nNoOfBytes);

	for(i=0; i < len;)
	{
		bytesLeft = len - i;

		if(bytesLeft > 8)
			bytesLeft = 8;

		switch(bytesLeft)
		{ // Bit positions from '1' to '8' not from '0' to '7'
			case 8:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 8, pszBuff[i*8 + 7]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 1, (pszBuff[i + 7] == '1')?1:0);
			case 7:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 7, pszBuff[i*8 + 6]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 2, (pszBuff[i + 6] == '1')?1:0);
			case 6:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 6, pszBuff[i*8 + 5]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 3, (pszBuff[i + 5] == '1')?1:0);
			case 5:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 5, pszBuff[i*8 + 4]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 4, (pszBuff[i + 4] == '1')?1:0);
			case 4:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 4, pszBuff[i*8 + 3]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 5, (pszBuff[i + 3] == '1')?1:0);
			case 3:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 3, pszBuff[i*8 + 2]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 6, (pszBuff[i + 2] == '1')?1:0);
			case 2:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 2, pszBuff[i*8 + 1]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 7, (pszBuff[i + 1] == '1')?1:0);
			case 1:
				//SET_VALUE_TO_BIT_IN_BYTE(pBitSeq[dstByteIndx], 1, pszBuff[i*8]);
				setValueToBitInByte(&pBitSeq[dstByteIndx], 8, (pszBuff[i] == '1')?1:0);
		}

		dstByteIndx++;
		i = i + 8;

	}

	return pBitSeq;
}

char* convertBitRepToByteRep(char* pszBuff, int nNoOfBits)
{
	char* nByteRepSeq = NULL;
	int nNoOfBytesToParse = nNoOfBits/8;
	int bitsLeft;
	int srcByteIndx = 0;

	if((nNoOfBits%8) > 0)
		nNoOfBytesToParse++;

	// nNoOfBits + 1 ==> ' + 1' for space for NULL character in the string
	nByteRepSeq = (char*)malloc((nNoOfBits + 1)*sizeof(char));

	// Initialize bytes with ASCII value of ZERO and not 0; bcos it terminates string
	memset(nByteRepSeq, 0, (nNoOfBits + 1)*sizeof(char));

	for(int i = 0; i < nNoOfBytesToParse; i++)
	{
		bitsLeft = nNoOfBits - i*8;

		if(bitsLeft > 8)
			bitsLeft = 8;

		switch(bitsLeft)
		{ // Bit positions from '1' to '8' not from '0' to '7'
			case 8:
				//nByteRepSeq[i*8 + 7] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 8)? '1' : '0';
				nByteRepSeq[i*8 + 7] = getValueOfBitInByte(pszBuff[srcByteIndx], 8);
			case 7:
				//nByteRepSeq[i*8 + 6] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 7)? '1' : '0';
				nByteRepSeq[i*8 + 6] = getValueOfBitInByte(pszBuff[srcByteIndx], 7);
			case 6:
				//nByteRepSeq[i*8 + 5] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 6)? '1' : '0';
				nByteRepSeq[i*8 + 5] = getValueOfBitInByte(pszBuff[srcByteIndx], 6);
			case 5:
				//nByteRepSeq[i*8 + 3] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 5)? '1' : '0';
				nByteRepSeq[i*8 + 4] = getValueOfBitInByte(pszBuff[srcByteIndx], 5);
			case 4:
				//nByteRepSeq[i*8 + 4] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 4)? '1' : '0';
				nByteRepSeq[i*8 + 3] = getValueOfBitInByte(pszBuff[srcByteIndx], 4);
			case 3:
				//nByteRepSeq[i*8 + 5] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 3)? '1' : '0';
				nByteRepSeq[i*8 + 2] = getValueOfBitInByte(pszBuff[srcByteIndx], 3);
			case 2:
				//nByteRepSeq[i*8 + 6] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 2)? '1' : '0';
				nByteRepSeq[i*8 + 1] = getValueOfBitInByte(pszBuff[srcByteIndx], 2);
			case 1:
				//nByteRepSeq[i*8 + 7] = GET_VALUE_OF_BIT_IN_BYTE(pszBuff[srcByteIndx], 1)? '1' : '0';
				nByteRepSeq[i*8] = getValueOfBitInByte(pszBuff[srcByteIndx], 1);
		}

		srcByteIndx++;
	}

	return nByteRepSeq;
}


void getIntValueFromBitStream(char* pszBitStream, int nStartPos, int nEndPos, int* resVal)
{
	int val = 0;

	for(int i=nStartPos-1; i < nEndPos; i++)
	{
		val = val<<1;

		if(pszBitStream[i] == '1')
		{
			val = val + 1;
		}
	}

	*resVal = val;
}
