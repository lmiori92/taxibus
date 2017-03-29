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

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <stdint.h>

/* Let this library to be also compilable in C++ projects */
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum _e_interface_err
{
    INTERFACE_OK,
    INTERFACE_UNKNOWN,
    INTERFACE_TIMEOUT,
    INTERFACE_ERROR,
    INTERFACE_BUSY
} e_interface_err;

typedef struct _t_inferface_state
{
    uint8_t flags;
    uint8_t *data;
    uint8_t len;
    void    *interface_internal;
} t_interface_state;

#define INTERFACE_INIT_FUNCTION(x, interface_params)     e_interface_err x(t_interface *state, t_interface *chained, interface_params)

#define INTERFACE_WRITE_FUNCTION(x)     e_interface_err x(t_interface *state)

#define INTERFACE_CHAIN_FUNCTION(x)     if (x != NULL)  x->write(x);

typedef struct _t_inferface
{
    e_interface_err (*write)(struct _t_inferface *state);
    t_interface_state   state;

    struct _t_inferface *chain;
} t_interface;

#define INTERFACE_FLAGS(state, flags)   ((state).flags = flags)
#define INTERFACE_DATA(state, data_val, len_val)    { \
                                              state.data = data_val;  \
                                              state.len = len_val;    \
                                            }

#define INTERFACEPTR_DATA(state, data_val, len_val)    { \
                                              state->data = data_val;  \
                                              state->len = len_val;    \
                                            }

#define INTERFACE_DATA_OUT(state)       (state.data)
#define INTERFACE_LEN_OUT(state)       (state.len)

#define INTERFACEPTR_DATA_OUT(intf)       (intf->state.data)
#define INTERFACEPTR_LEN_OUT(intf)       (intf->state.len)

#define INTERFACEPTR_DATA_IN(state)       (state->data)
#define INTERFACEPTR_LEN_IN(state)       (state->len)

/**
 * Write the data all in a go, until data transfer is complete
 * or error occurred.
 * @param state
 * @return
 */
e_interface_err interface_write(t_interface *interface);

//t_interface i2c_bitbanged;
//// . write = <implementation of i2c bitbang>
//// . chain = shift_register interface;
//t_interface shift_register;
//// . write = <implementation of shift register>
//// . chain = avr_port interface;
//t_interface avr_port;
//// . write = <implementation of user avr port definition>
//// . chain = NULL (or debug over serial...);
//
//// to initialize the interfaces with standard implementations
//// xxx_init( <interface>, <binded to (chained to)> )
//i2c_bitbanged_init(&i2c_bitbanged, &shift_register);
//shift_register_init(&shift_register, &avr_port);
//avr_port_init(&avr_port);
//
//// what a driver would eventually perform...
//display_attach(&i2c_bitbanged);
//
//// draw something
//display_write_string(...);
//display_xxx(...);
//
//// call the update function
//display_periodic();
//// --> that will simply:
//    e_interface_err err = INTERFACE_UNKNOWN;
//    t_interface_state state;
//    uint8_t buffer[2] = { 0x01, 0x02 };
//
//    // this do-while block is standardized
//    // with a inline function:
//    // err = interface_write(&attached, &state, buffer, sizeof(buffer));
//    // so every driver will implement a blocking write in the same way
//    do
//    {
//        err = attached.write(&state, buffer, sizeof(buffer));
//        // --> this call performs some computation
//        //     and calls .chain.write() with computed data
//        //     --> in turn, .chain.write() will call
//        //          --> .chain.chain.write() and so on and so forth...
//        //  <-- the result will get back
//    } while (err != INTERFACE_BUSY);
////  <-- Sent !

#ifdef __cplusplus
}
#endif

#endif /* INTERFACE_H_ */
