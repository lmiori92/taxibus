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

#ifndef TAXIBUS_SHIFT_REGISTER_H_
#define TAXIBUS_SHIFT_REGISTER_H_

#include "interface.h"

/* Let this library to be also compilable in C++ projects */
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef MAX_SHIFT_REGISTER_DEVICES
#define MAX_SHIFT_REGISTER_DEVICES    1
#endif

INTERFACE_INIT_FUNCTION(shift_register_init, uint8_t clock, uint8_t latch, uint8_t data);

INTERFACE_WRITE_FUNCTION(shift_register_write);

#ifdef __cplusplus
}
#endif

#endif /* TAXIBUS_SHIFT_REGISTER_H_ */
