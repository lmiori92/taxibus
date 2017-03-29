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

/* Do not attempt to compile on Linux-unaware platforms :-) */
#ifdef __linux__

#include "i2c_master.h"

#include "i2c_linux.h"

#include "interface.h"

INTERFACE_INIT_FUNCTION(i2c_linux_init, uint8_t address)
{
    e_interface_err err = INTERFACE_UNKNOWN;

    i2c_slave_address = address;

    i2c_init();

    state->write = i2c_linux_write;
    state->chain = chained;

    return err;
}

INTERFACE_WRITE_FUNCTION(i2c_linux_write)
{
    e_interface_err err = INTERFACE_UNKNOWN;
    uint8_t i2cret;

    i2c_transfer_set_data(INTERFACEPTR_DATA_OUT(state), INTERFACEPTR_LEN_OUT(state));
    i2c_transfer_start();
    i2cret = i2c_transfer_successful();
    if (i2cret == 0U)
    {
        err = INTERFACE_OK;

        /* transfer successful, chain next step */
        if (state->chain != NULL)
        {
            INTERFACE_DATA(state->chain->state, INTERFACEPTR_DATA_OUT(state), INTERFACEPTR_LEN_OUT(state));
            INTERFACE_CHAIN_FUNCTION(state->chain);
        }

    }
    else
    {
        err = INTERFACE_ERROR;
    }

    return err;
}

#endif
