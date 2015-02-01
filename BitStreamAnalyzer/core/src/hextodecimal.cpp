/*
 *   Author: sealights@gmx.com
 *
 *   This file is licensed under the terms of the GNU General Public License version 3.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "stdafx.h"
#include "hextodecimal.h"

int convertHexStringToDecimalValue(char* szHex)
{
	int nDecimalVal		= 0;
	int nHexStrLen		= -1;
	int nCharHexVal;
	int nHexDigitLocationValue;

	if(szHex == NULL)
		return -1;

	nHexStrLen = (int)strlen(szHex);

	if(nHexStrLen == 0)
		return -1;

	for(int i = nHexStrLen - 1; i >= 0; i--)
	{
		switch(szHex[i])
		{
		case '0':
			nCharHexVal = 0;
			break;
		case '1':
			nCharHexVal = 1;
			break;
		case '2':
			nCharHexVal = 2;
			break;
		case '3':
			nCharHexVal = 3;
			break;
		case '4':
			nCharHexVal = 4;
			break;
		case '5':
			nCharHexVal = 5;
			break;
		case '6':
			nCharHexVal = 6;
			break;
		case '7':
			nCharHexVal = 7;
			break;
		case '8':
			nCharHexVal = 8;
			break;
		case '9':
			nCharHexVal = 9;
			break;
		case 'A':
		case 'a':
			nCharHexVal = 10;
			break;
		case 'B':
		case 'b':
			nCharHexVal = 11;
			break;
		case 'C':
		case 'c':
			nCharHexVal = 12;
			break;
		case 'D':
		case 'd':
			nCharHexVal = 13;
			break;
		case 'E':
		case 'e':
			nCharHexVal = 14;
			break;
		case 'F':
		case 'f':
			nCharHexVal = 15;
			break;
		default:
			return -1;
		}


		nHexDigitLocationValue = 1;
		for(int j = 0; j < nHexStrLen - i -1; j++)
			nHexDigitLocationValue = 16*nHexDigitLocationValue;

		nDecimalVal = nDecimalVal + (nCharHexVal*nHexDigitLocationValue);
	}

	return nDecimalVal;
}


int convertDecimalToHexStr(int num, char** szHexStr)
{
	int rem[50],i=0,length=0;
	int nHexCharPos;

	while(num>0)
	{
	  rem[i]=num%16;
	  num=num/16;
	  i++;
	  length++;
	}

	(*szHexStr) = (char*)malloc(sizeof(char)*(length+1));
	memset((*szHexStr), 0, sizeof(char)*(length+1));

	printf("Hexadecimal number : ");
	for(nHexCharPos =0, i=length-1;i>=0;i--, nHexCharPos++)
	{
		switch(rem[i])
		{
		  case 0:
			  (*szHexStr)[nHexCharPos] = '0';
			  break;
		  case 1:
			  (*szHexStr)[nHexCharPos] = '1';
			  break;
		  case 2:
			  (*szHexStr)[nHexCharPos] = '2';
			  break;
		  case 3:
			  (*szHexStr)[nHexCharPos] = '3';
			  break;
		  case 4:
			  (*szHexStr)[nHexCharPos] = '4';
			  break;
		  case 5:
			  (*szHexStr)[nHexCharPos] = '5';
			  break;
		  case 6:
			  (*szHexStr)[nHexCharPos] = '6';
			  break;
		  case 7:
			  (*szHexStr)[nHexCharPos] = '7';
			  break;
		  case 8:
			  (*szHexStr)[nHexCharPos] = '8';
			  break;
		  case 9:
			  (*szHexStr)[nHexCharPos] = '9';
			  break;
		  case 10:
			  //printf("A");
			  (*szHexStr)[nHexCharPos] = 'A';
			  break;
		  case 11:
			  //printf("B");
			  (*szHexStr)[nHexCharPos] = 'B';
			  break;
		  case 12:
			  //printf("C");
			  (*szHexStr)[nHexCharPos] = 'C';
			  break;
		  case 13:
			  //printf("D");
			  (*szHexStr)[nHexCharPos] = 'D';
			  break;
		  case 14:
			  //printf("E");
			  (*szHexStr)[nHexCharPos] = 'E';
			  break;
		  case 15:
			  //printf("F");
			  (*szHexStr)[nHexCharPos] = 'F';
			  break;
		  default :
			 //printf("%ld",rem[i]);
			  (*szHexStr)[nHexCharPos] = rem[i];
		}
	}

	return 0;
}