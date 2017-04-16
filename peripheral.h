/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Lorenzo Miori (C) 2017 [ 3M4|L: memoryS60<at>gmail.com ]

*/

#ifndef TAXIBUS_PERIPHERAL_H_
#define TAXIBUS_PERIPHERAL_H_

/**
 * Divider settings
 */
typedef enum _e_divider
{
    DIV_BY_2, //!< DIV_BY_2
    DIV_BY_4, //!< DIV_BY_4
    DIV_BY_8, //!< DIV_BY_8
    DIV_BY_16,//!< DIV_BY_16
    DIV_BY_32,//!< DIV_BY_32
    DIV_BY_64,//!< DIV_BY_64
    DIV_BY_128//!< DIV_BY_128
} e_divider;

typedef enum _e_bit_order
{
    BIT_ORDER_MSB,
    BIT_ORDER_LSB
} e_bit_order;

#endif /* TAXIBUS_PERIPHERAL_H_ */
