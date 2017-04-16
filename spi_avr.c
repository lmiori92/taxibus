/*
 * spi_avr.c
 *
 *  Created on: 16 apr 2017
 *      Author: lorenzo
 */

#ifdef __AVR

#include <avr/io.h>
#include "spi_avr.h"
#include "taxibus/pin.h"

INTERFACE_INIT_FUNCTION(spi_avr_init, e_divider divider, e_bit_order bit, uint8_t spi_reg_flags)
{
    e_interface_err err = INTERFACE_OK;

    /* AVR SPI init */

    /* MOSI, CLOCK and SS(to prevent hangup while transferring) */
    DDRB |= (1 << PIN3) | (1 << PIN5) | (1 << PIN2);
    SPCR = (1 << SPE) | (1 << MSTR);

    SPCR &= ~((1 << SPR1) | (1 << SPR0));
    SPSR &= ~(1 << SPI2X);

    switch(divider)
    {
    case DIV_BY_2:
        SPSR |= (1 << SPI2X);
        break;
    case DIV_BY_4:
        break;
    case DIV_BY_8:
        SPCR |= ((0 << SPR1) | (1 << SPR0));
        SPSR |= (1 << SPI2X);
        break;
    case DIV_BY_16:
        SPCR |= ((0 << SPR1) | (1 << SPR0));
        break;
    case DIV_BY_32:
        SPCR |= ((1 << SPR1) | (0 << SPR0));
        SPSR |= (1 << SPI2X);
        break;
    case DIV_BY_64:
        SPCR |= ((1 << SPR1) | (1 << SPR0));
        SPSR |= (1 << SPI2X);
        break;
    case DIV_BY_128:
        SPCR |= ((1 << SPR1) | (1 << SPR0));
        break;
    default:
        break;
    }

    switch(bit)
    {
    case BIT_ORDER_LSB:
        SPCR |= (1 << DORD);
        break;
    case BIT_ORDER_MSB:
        SPCR &= ~(1 << DORD);
        break;
    default:
        break;
    }

    SPCR |= spi_reg_flags;

    /* Set SS to HIGH (not asserted) */
    PIN_SET(PORTB, (1 << PIN2));

    /* set interface entry points */
    state->write = spi_avr_write;
    state->chain = chained;

    return err;
}

INTERFACE_WRITE_FUNCTION(spi_avr_write)
{
    uint8_t *data_ptr = state->state.data;
    uint8_t *data_end = state->state.data + state->state.len;

    /* Set SS to LOW (asserted) */
    PIN_UNSET(PORTB, (1 << PIN2));

    do
    {
        /* set the data byte */
        SPDR = *(data_ptr);
        /* wait until transmission is complete */
        while (!(SPSR & (1 << SPIF)));
        /* advance data pointer */
        data_ptr++;

    } while (data_ptr < data_end);

    /* Set SS to HIGH (not asserted) */
    PIN_SET(PORTB, (1 << PIN2));

    return INTERFACE_OK;
}

#endif
