
#ifndef __HEX_TO_DECIMAL__
#define __HEX_TO_DECIMAL__
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

/*
 *
 *	This file provides functionality for converting hex to decimal and viceversa
 *
 *
 *
 */

int convertHexStringToDecimalValue(char* szHex);

int convertDecimalToHexStr(int num, char** szHexStr);

#endif //__HEX_TO_DECIMAL__