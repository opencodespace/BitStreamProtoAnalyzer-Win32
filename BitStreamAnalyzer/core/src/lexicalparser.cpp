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
#include "lexicalparser.h"
#include "string.h"

/*
 * element '0' - '9'; occurance *
 * element seperator '-'; occurance 1
 * pair seperator ';' occurance 1
 * Sequence ('0' - '9', *), ('-', 1), ('0' - '9', *), (';', 1)
 *
 */

int validateString(char* pszPairSeq, int bufLen)
{
	int nCompletness = 0;
	int nParseIndex = 0;

	if(bufLen == 0)
		return RET_FAIL;

	for(; nParseIndex < bufLen; )
	{
		// Initially set nCompletness to zero, is set to '1' only after all the steps in 'LEXICALANALYSISTEPS'
		// are completed
		nCompletness = 0;

		for(int nStepCounter = E_CHECK_FIRST_NUMERIC_SEQ; nStepCounter <= E_ANALYSIS_COMPLETE_STEP; nStepCounter++)
		{
			switch(nStepCounter)
			{
				case E_CHECK_FIRST_NUMERIC_SEQ:
				case E_CHECK_SECOND_NUMERIC_SEQ:
				{
					int count = 0;
					for(;(nParseIndex < bufLen) && (pszPairSeq[nParseIndex] >= '0' && pszPairSeq[nParseIndex] <= '9'); count++, nParseIndex++);

					if(count == 0)
					{
						// No digit found come out and return error
						nCompletness = 0;
						goto EXIT;
					}
				}
				break;
				case E_CHECK_ELEMENT_SEPERATOR:
				{
					if(pszPairSeq[nParseIndex] == LX_ELEMENT_SEPERATOR)
					{
						nParseIndex++;
					}
					else
					{
						nCompletness = 0;
						goto EXIT;
					}
				}
				break;
				case E_CHECK_PAIR_SEPERATOR:
				{
					if(pszPairSeq[nParseIndex] == LX_PAIR_SEPERATOR || nParseIndex >= bufLen)
					{
						nParseIndex++;
					}
					else
					{
						nCompletness = 0;
						goto EXIT;
					}
				}
				break;
				case E_ANALYSIS_COMPLETE_STEP:
				{
					nCompletness = 1;
				}
				break;
			}
		}
	}

EXIT:
	if(nCompletness == 1)
		return RET_SUCCESS;
	else
		return RET_FAIL;
}

int getNumberOfPairs(char* pszPairString, int bufLen)
{
	int nCount = 0;

	for(int i=0; i < bufLen; i++)
	{
		//if(pszPairString[i] == LX_PAIR_SEPERATOR)
		if (pszPairString[i] == LX_ELEMENT_SEPERATOR) // Dt: 08-May-2016
			nCount++;
	}

	return nCount;
}

void getElementsFromPairs(char* pszPairString, int bufLen, int** pPairValues, int* pNoOfPairs)
{
	int nPairCount	= 0;
	int* pValues	= NULL;
	int nParseIndex = 0;
	int nValueIndx	= 0;

	if(bufLen == 0)
		return;

	nPairCount = getNumberOfPairs(pszPairString, bufLen);

	pValues = (int*)malloc(2*nPairCount*sizeof(int));

	for(; nParseIndex < bufLen; )
	{
		// 1. Convert numerics to integer
		// 2. Skip emenent seperator
		// 3. Convert numerics to integer
		// 4. Skip pair seperator
		// 5. Repeat the process

		// Convert first element of the pair to integer
		pValues[nValueIndx] = atoi(&pszPairString[nParseIndex]);
		nValueIndx++;

		// Skip numeric characters
		for(int count = 0;(nParseIndex < bufLen) && (pszPairString[nParseIndex] >= '0' && pszPairString[nParseIndex] <= '9'); count++, nParseIndex++);

		// Skip element seperator
		nParseIndex++;

		// Convert second element of the pair to integer
		// donot worry!! even for the last pair, there shall be  pair seperator';'
		// succeeding the second element and atoi() shall work fine with out
		// loitering in to the invalid memory space
		pValues[nValueIndx] = atoi(&pszPairString[nParseIndex]);
		nValueIndx++;

		// Skip numeric characters
		for(int count = 0;(nParseIndex < bufLen) && (pszPairString[nParseIndex] >= '0' && pszPairString[nParseIndex] <= '9'); count++, nParseIndex++);

		// Skip pair seperator
		nParseIndex++;
	}

	*pNoOfPairs		= nPairCount;
	*pPairValues	= pValues;
}

void getElementsOfPairByPosition(char* pszPairString, int bufLen, int position, int** pPairValues)
{
	int nParseIndex = 0;
	int nPairCount	= 0;
	int nStartPos	= -1;
	int nEndPos		= -1;

	for(nParseIndex=0, nPairCount=0; nParseIndex < bufLen && nPairCount < (position -1); nParseIndex++)
	{
		if(pszPairString[nParseIndex] == LX_PAIR_SEPERATOR)
		{
			nPairCount++;
		}
	}

	if(nParseIndex < bufLen)
	{
		*pPairValues = (int*)malloc(2*nPairCount*sizeof(int));

		// Convert first element of the pair to integer
		nStartPos = atoi(&pszPairString[nParseIndex]);

		// Skip numeric characters
		for(int count = 0;(nParseIndex < bufLen) && (pszPairString[nParseIndex] >= '0' && pszPairString[nParseIndex] <= '9'); count++, nParseIndex++);

		// Skip element seperator
		nParseIndex++;

		//convert second element to integer
		nEndPos = atoi(&pszPairString[nParseIndex]);

		(*pPairValues)[0] = nStartPos;
		(*pPairValues)[1] = nEndPos;
	}
}

