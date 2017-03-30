/*
 * shift_register.c
 *
 *  Created on: 30 mar 2017
 *      Author: lorenzo
 */

#include <stddef.h>

#include "interface.h"
#include "pin.h"
#include "shift_register.h"

typedef struct
{
    uint8_t clock;
    uint8_t latch;
    uint8_t data;
} t_shift_register_pins;

uint8_t devices = 0;

t_shift_register_pins shift_registers_registered[MAX_SHIFT_REGISTER_DEVICES];

INTERFACE_INIT_FUNCTION(shift_register_init, uint8_t clock, uint8_t latch, uint8_t data)
{
    e_interface_err err = INTERFACE_OVERFLOW;

    if (devices < sizeof(shift_registers_registered)/sizeof(shift_registers_registered[0]))
    {
        /* precalculate the shift to have it ready */
        shift_registers_registered[devices].clock = (uint8_t)(1 << clock);
        shift_registers_registered[devices].latch = (uint8_t)(1 << latch);
        shift_registers_registered[devices].data = (uint8_t)(1 << data);
        state->state.interface_internal = (void*)&shift_registers_registered[devices];
        state->state.flags = 0U;    /* support virtual port variable */
        state->chain = chained;
        state->write = shift_register_write;
        devices++;
        err = INTERFACE_OK;
    }
    else
    {
        state->chain = NULL;
        state->write = NULL;
    }

    return err;
}

INTERFACE_WRITE_FUNCTION(shift_register_write)
{
    e_interface_err err = INTERFACE_UNKNOWN;

    uint8_t i, byte;
    uint8_t port = state->state.flags;
    uint8_t *data_ptr = state->state.data;
    uint8_t clock = ((t_shift_register_pins*)state->state.interface_internal)->clock;
    uint8_t data = ((t_shift_register_pins*)state->state.interface_internal)->data;
    uint8_t latch = ((t_shift_register_pins*)state->state.interface_internal)->latch;
    /* Do not transfer the temporary register to the outputs */

    /* set the virtual port as output data */
    INTERFACE_DATA(state->chain->state, &port, 1U);

    for (byte = 0; byte < state->state.len; byte++)
    {

        for (i = 0; i < 8; i++)
        {
            /* Shift bits out */
            if ((*data_ptr >> i) & 0x01U)
            {
                PIN_SET(port, data);
            }
            else
            {
                PIN_UNSET(port, data);
            }

            INTERFACE_CHAIN_FUNCTION(state->chain);

            /* Clocks the bits */
            PIN_SET(port, clock);
            INTERFACE_CHAIN_FUNCTION(state->chain);
            PIN_UNSET(port, clock);
            INTERFACE_CHAIN_FUNCTION(state->chain);
        }
        /* Transfer the temporary register to the outputs */
        PIN_SET(port, latch);
        INTERFACE_CHAIN_FUNCTION(state->chain);
        PIN_UNSET(port, latch);
        INTERFACE_CHAIN_FUNCTION(state->chain);

        /* advance data pointer */
        data_ptr++;
    }

    return err;
}
