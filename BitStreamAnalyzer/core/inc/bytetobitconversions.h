#ifndef __UTILITY_FUNCTIONS__
#define __UTILITY_FUNCTIONS__
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

char* convertByteRepToBitRep(char* pszBuff, int len);

char* convertBitRepToByteRep(char* pszBuff, int nNoOfBits);

void getIntValueFromBitStream(char* pszBitStream, int nStartPos, int nEndPos, int* resVal);

#endif //__UTILITY_FUNCTIONS__
