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

/* not enough memory on AVR to perform debugging */
#ifndef __AVR

#include "interface.h"
#include "debugger.h"
#include "pin.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static uint8_t i2cbuffer[1024] = { 0 };
static uint16_t buf_id = 0;

INTERFACE_INIT_FUNCTION(debugger_init, void* voidparam)
{
    state->write = debugger_write;
    state->chain = chained;
    return INTERFACE_OK;
}

INTERFACE_WRITE_FUNCTION(debugger_write)
{
    if (buf_id < sizeof(i2cbuffer))
    {
        memcpy(&i2cbuffer[buf_id], state->state.data, state->state.len);
        buf_id += state->state.len;
    }

    /* transfer successful, chain next step */
    if (state->chain != NULL)
    {
        INTERFACE_DATA(state->chain->state, INTERFACEPTR_DATA_OUT(state), INTERFACEPTR_LEN_OUT(state));
        INTERFACE_CHAIN_FUNCTION(state->chain);
    }

    return INTERFACE_OK;
}

void debugger_dump()
{
    uint8_t line = 0;
    for (uint16_t i = 0; i < buf_id; i++)
    {
        printf("0x%02x ", i2cbuffer[i]);
        line++;
        if (line >= 16)
        {
            line = 0;
            printf("\n");
        }

    }
    printf("\n");
}

void debugger_byte_bits()
{
    for (uint16_t i = 0; i < buf_id; i++)
    {
        printf("0x%02x\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",
                i2cbuffer[i],
                i2cbuffer[i],
                GET_BIT(i2cbuffer[i], 0),
                GET_BIT(i2cbuffer[i], 1),
                GET_BIT(i2cbuffer[i], 2),
                GET_BIT(i2cbuffer[i], 3),
                GET_BIT(i2cbuffer[i], 4),
                GET_BIT(i2cbuffer[i], 5),
                GET_BIT(i2cbuffer[i], 6),
                GET_BIT(i2cbuffer[i], 7)
                );
    }
    printf("\n");
}

#endif
