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
#include "parserintf.h"
#include "lexicalparser.h"
#include "bytetobitconversions.h"
#include "hextodecimal.h"

#define HEX_VALUE_SEPERATOR	"#"
#define MAX_HEX_VALUE_STRING_SIZE	1024*2


int getPositionValues(char* pzRuleStr, int bufLen, int** pPositionValues, int* noOfPairs)
{
	if(RET_FAIL == validateString(pzRuleStr, bufLen))
		return -1;

	getElementsFromPairs(pzRuleStr, bufLen, pPositionValues, noOfPairs);


	return 0;
}

void getHexValueStringFromBitStream(char* pszBitStream, 
									int bitStreamLen, 
									int* positionValues,
									int nNofPositions,
									char** pszValueStr)
{
	char szTempStr[MAX_HEX_VALUE_STRING_SIZE] = {0};
	int nValue;
	char* pszHexStr = NULL;

	for(int i=0; i < nNofPositions*2;)
	{
		if((positionValues[i] > bitStreamLen || positionValues[i+1] > bitStreamLen) ||
			(positionValues[i] > positionValues[i+1]))
		{
			sprintf_s(szTempStr, "%s%s#", szTempStr, HEX_VALUE_SEPERATOR);
		}
		else
		{
			nValue = 0;
			getIntValueFromBitStream(pszBitStream, positionValues[i], positionValues[i + 1], &nValue);

			pszHexStr = NULL;

			convertDecimalToHexStr(nValue, &pszHexStr);

			sprintf_s(szTempStr, "%s%s%s", szTempStr, pszHexStr, HEX_VALUE_SEPERATOR);

			if(pszHexStr)
				free(pszHexStr);
		}

		i = i + 2;
	}

	(*pszValueStr) = (char*)malloc(sizeof(char)*(strlen(szTempStr) + 1));

	memset(*pszValueStr, 0, (strlen(szTempStr) + 1));

	strcpy_s(*pszValueStr, strlen(szTempStr) + 1, szTempStr);
}