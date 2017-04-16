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

#ifndef DEASPLAY_TAXIBUS_PORT_H_
#define DEASPLAY_TAXIBUS_PORT_H_

typedef struct
{
    /** The physical memory address of the port */
    uint8_t *io_address;
    /** The remapping array */
    uint8_t remapping[8U];
    /** The bits that will be read or written from/to the port */
    uint8_t mask;
} t_port_descriptor;

typedef enum _e_port_direction
{
    PORT_READ,
    PORT_WRITE,
    PORT_TRISTATE
} e_port_direction;

#define PORT_REMAP_PIN(port, pin_in, pin_out)   ( port = ( (((port) >> (pin_in)) & 0x01U) << (pin_out) ) )

//inline void port_remap_and_set(t_port_descriptor* port, uint8_t value)
//{
//    /* null pointer check consumes some cycles, avoid it here */
//    uint8_t*rem = port->remapping;
//
//    /* apply pin remapping */
//    PORT_REMAP_PIN(value, 0U, *rem);
//    rem++;
//    PORT_REMAP_PIN(value, 1U, *rem);
//    rem++;
//    PORT_REMAP_PIN(value, 2U, *rem);
//    rem++;
//    PORT_REMAP_PIN(value, 3U, *rem);
//    rem++;
//    PORT_REMAP_PIN(value, 4U, *rem);
//    rem++;
//    PORT_REMAP_PIN(value, 5U, *rem);
//    rem++;
//    PORT_REMAP_PIN(value, 6U, *rem);
//    rem++;
//    PORT_REMAP_PIN(value, 7U, *rem);
//    rem++;
//
//    /* set the computed value */
//    /* null pointer check consumes some cycles, avoid it here */
//    *(port->io_address) = value;
//}

#endif /* DEASPLAY_TAXIBUS_PORT_H_ */
