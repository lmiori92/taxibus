# taxibus
A bare metal C interface exchange layer to transfer bytes in a transparent way on any defined medium. It is designed to be use in restricted-resources environments like a microcontroller.

# Preamble

This library wants to be a simple-yet-powerful portable layer written in standard C99 which handles interface protocol decoding to write device drivers that can communicate with peripherals in a transparent a dynamic way.
A very typical example: the HD44780 display. It communicates -data- (bytes), eventually commands and characters, over a parallel port. Lately, i2c port extenders and shift registers have been used to reduce the number of pin and this poses the problem of a generic driver.
By designing a crystal clear write() function it is possible to send commands and character to the target display without knowing a bit of the intermediate layers.
The initial implementation is focused on write-only operations which are mainly targetting display drivers.

# Library Name
A "taxi" is a transportation mean that carries people from one place to another and it is usually quite pricey, much higher than a public transportation mean, say a "bus".
With this library we want to perform a better integration of both worlds: a taxi is easy to get and on-demand, a bus might get tricky to catch. We want to integrate device drivers in a jiffy paying a somewhat higher cost, still trying to follow the bus lines...

# Requirements

- the user shall only define the behavior of the final destination. This can be defining and toggling pins on a specific architecture, opening a file for debugging the transmitted data and so on.
- a write() call is designed so that it is the only interface. By calling write with the desired data, it shall be possible to know how many bytes have been transferred via the unknown media "tunnel" and the state of the transfer.
- initialization is performed by the write() call, no other major interface is foreseen. 
- shall support arbitrary chaining of interfaces

# Chaining

A HD44780 write() could go through a i2c bitbang module which in turn goes through a write() of a port interface which in turns calls a user defined write() which eventually toggles port bits.
The original write() call ends up in something that hopefully the hardware understands and decodes.

# Timing

A major issue of building such a chaining is execution time and timing of bit / bytes toggling. A proposal to keep everything synchronized, is to "chain"/"define" a common routine, say, delay_us() which the implementer defines and will be used to halt the code execution for some time.

# Write Interface

A write() call is simply something that once returning "OK" it is assumed the data has been successfully sent. Nothing more than that. No status calls. The state is carried along this write call, the final state is a chain of intermediate states e.g. if an error has occured on port toggling (an advanced ECU / board could have a short protection that has triggered) the error is transported through all the intermediate steps until the device driver (originating write() call)
The write is defined as following:
```c
t_interface_err retval = write(t_interface *interface, uint8_t *data, uint8_t len);
```

# Read Interface

A read() call is simply something that once returning "OK" it is assumed that the data has been successfully received. Nothing more than that. No status calls. The state is carried along with this read call, and the final state is a chain of intermediate states e.g. if an error has occured on port reading, then the error is transported through all the intermediate steps until the device driver (originating read() call).
The read is defined as following:
```c
t_interface_err retval = read(t_interface *interface, uint8_t *data, uint8_t len);
```
# A working example
```c
#include "deasplay/taxibus/interface.h"
#include "deasplay/taxibus/i2c_linux.h"
#include "deasplay/taxibus/debugger.h"

t_interface display_entry_interface;
t_interface i2c_logger;

void init(void)
{
    /* initialize debugger interface, do not chain to anything else */
    debugger_init(&i2c_logger, NULL, NULL);
    /* initialize linux i2c interface and chain to the logger as well */
    i2c_linux_init(&display_entry_interface, &i2c_logger, 0x3CU);

    /* set the entry interface */
    DISPLAY_SET_INTERFACE(&display_entry_interface);
    /* initialize display (on the previously selected interface) */
    display_init();

    /* let's see what the display driver has sent on the bus */
    i2c_logger_dump();
}

```
# A complete concept C snippet
```c
t_interface i2c_bitbanged;
// . write = <implementation of i2c bitbang>
// . chain = shift_register interface;
t_interface shift_register;
// . write = <implementation of shift register>
// . chain = avr_port interface;
t_interface avr_port;
// . write = <implementation of user avr port definition>
// . chain = NULL (or debug over serial...);

// to initialize the interfaces with standard implementations
// xxx_init( <interface>, <binded to (chained to)> )
i2c_bitbanged_init(&i2c_bitbanged, &shift_register);
shift_register_init(&shift_register, &avr_port);
avr_port_init(&avr_port);

// what a driver would eventually perform...
display_attach(&i2c_bitbanged);

// draw something
display_write_string(...);
display_xxx(...);

// call the update function
display_periodic();
// --> that will simply:
    e_interface_err err = INTERFACE_UNKNOWN;
    t_interface_state state;
    uint8_t buffer[2] = { 0x01, 0x02 };

    // this do-while block is standardized
    // with a inline function:
    // err = interface_write(&attached, &state, buffer, sizeof(buffer));
    // so every driver will implement a blocking write in the same way
    do
    {
        err = attached.write(&state, buffer, sizeof(buffer));
        // --> this call performs some computation
        //     and calls .chain.write() with computed data
        //     --> in turn, .chain.write() will call
        //          --> .chain.chain.write() and so on and so forth...
        //  <-- the result will get back
    } while (err != INTERFACE_BUSY);
//  <-- Sent !
```
