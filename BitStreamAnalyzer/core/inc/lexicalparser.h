#ifndef __LEXICAL_PARSER__
#define __LEXICAL_PARSER__

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

// A pair represents start and end position of a bit stream and each of these are called elements
// Exampe of pair is 2-5;. Sequence of pairs shall be seperated by ';'
// Example of sequence of pairs ==> 2-5;8-12;6-9;
// Each pair is essentially terminated/succeeded by ';'

#define LX_PAIR_SEPERATOR		';'
#define LX_ELEMENT_SEPERATOR	'-'


typedef enum {
		RET_SUCCESS,
		RET_FAIL
} RESULT;

typedef enum {
	E_CHECK_FIRST_NUMERIC_SEQ,		//First position value
	E_CHECK_ELEMENT_SEPERATOR,
	E_CHECK_SECOND_NUMERIC_SEQ,		// Second position value
	E_CHECK_PAIR_SEPERATOR,
	E_ANALYSIS_COMPLETE_STEP
} LEXICALANALYSISTEPS;

int validateString(char* pszPairSeq, int bufLen);

int getNumberOfPairs(char* pszPairString, int bufLen);

void getElementsFromPairs(char* pszPairString, int bufLen, int** pPairValues, int* pNoOfPairs);

void getElementsOfPairByPosition(char* pszPairString, int bufLen, int position, int** pPairValues);

#endif //__LEXICAL_PARSER__