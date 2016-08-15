#ifndef __BIT_SEQ_PARSER__
#define __BIT_SEQ_PARSER__

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
 * This method sets the decimal (param4) value in to the bit sequence
 * buffer (param1) in to the position indicated by param2 and param3
 * The method sets the bit sequence indicated by param2 and param3 with the 
 * decimal value aligning towards the left.
 */
void SetValue(char* buf, int startBit, int endBit, int value);

/*
 * Prints the bit sequence of array of bytes, number
 * of bytes are indicated by param2.
 */

void PrintBitStream(char* byte1, int length);



#endif //__BIT_SEQ_PARSER__