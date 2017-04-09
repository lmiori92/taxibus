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

/**< Enable 16 bit size variable */
#define HAS_16BIT_SIZE

#ifdef HAS_16BIT_SIZE
typedef uint16_t t_xfer_size;
#else
typedef uint8_t t_xfer_size;
#endif

typedef enum _e_interface_err
{
    INTERFACE_OK,
    INTERFACE_UNKNOWN,
    INTERFACE_TIMEOUT,
    INTERFACE_ERROR,
    INTERFACE_BUSY,
    INTERFACE_OVERFLOW
} e_interface_err;

typedef struct _t_inferface_state
{
    /*uint8_t flags;*/
    uint8_t *data;
    t_xfer_size len;
    void    *interface_internal;
} t_interface_state;

#define INTERFACE_INIT_FUNCTION(x, ...)     e_interface_err x(t_interface *state, t_interface *chained, __VA_ARGS__)

#define INTERFACE_WRITE_FUNCTION(x)     e_interface_err x(t_interface *state)

#define INTERFACE_CHAIN_FUNCTION(x)     /*if (x != NULL)*/  x->write(x);

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

#ifdef __cplusplus
}
#endif

#endif /* INTERFACE_H_ */
