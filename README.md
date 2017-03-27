# taxibus
A bare metal C interface exchange layer to transfer bytes in a transparent way on any defined medium

# Preamble

This library wants to be a simple-yet-powerful portable layer written in standard C99 which handles interface protocol decoding to write device drivers that can communicate with peripherals in a transparent a dynamic way.
A very typical example: the HD44780 display. It communicates -data- (bytes), eventually commands and characters, over a parallel port. Lately, i2c port extenders and shift registers have been used to reduce the number of pin and this poses the problem of a generic driver.
By designing a crystal clear write() function it is possible to send commands and character to the target display without knowing a bit of the intermediate layers.
The initial implementation is focused on write-only operations which are mainly targetting display drivers.
A read() call is foreseen and is exactly the reverse of a write(), no major issues are found.

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
