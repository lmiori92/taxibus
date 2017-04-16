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

    Lorenzo Miori (C) 2016 [ 3M4|L: memoryS60<at>gmail.com ]

    Version History
        * 1.0 initial

*/

#ifndef TAXIBUS_SPI_AVR_H_
#define TAXIBUS_SPI_AVR_H_

#include "interface.h"
#include "peripheral.h"

/* Let this library to be also compilable in C++ projects */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Initialize the SPI subsystem on the AVR platform.
 * An additional parameter allows to specify or
 * override any internal bits of the SPCR register to
 * allow maximum flexibility on configuration.
 * @param spi_reg_flags the additional register flags
 */
INTERFACE_INIT_FUNCTION(spi_avr_init, e_divider divider, e_bit_order bit, uint8_t spi_reg_flags);

/**
 * The AVR SPI write function. The user should not usually
 * call it directly, but a taxibus-compatible module.
 * @return  e_interface_err error code
 */
INTERFACE_WRITE_FUNCTION(spi_avr_write);

#ifdef __cplusplus
}
#endif

#endif /* TAXIBUS_SPI_AVR_H_ */
