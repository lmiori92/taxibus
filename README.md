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
