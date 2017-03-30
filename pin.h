/*
 * pin.h
 *
 *  Created on: 30 mar 2017
 *      Author: lorenzo
 */

#ifndef TAXIBUS_PIN_H_
#define TAXIBUS_PIN_H_

/* 8-bit bank */

#define PIN_0   0U
#define PIN_1   1U
#define PIN_2   2U
#define PIN_3   3U
#define PIN_4   4U
#define PIN_5   5U
#define PIN_6   6U
#define PIN_7   7U

/* 16-bit bank */

#define PIN_8   8U
#define PIN_9   9U
#define PIN_10  10U
#define PIN_11  11U
#define PIN_12  12U
#define PIN_13  13U
#define PIN_14  14U
#define PIN_15  15U

#define PIN_LOW(port, pin)      port &= ~(1 << pin);  /**< Set PIN LOW in a n-byte port */
#define PIN_HIGH(port, pin)     port |=  (1 << pin);  /**< Set PIN HIGH in a n-byte port */
#define PIN_SET(port, pin_shift)    port |= pin_shift;
#define PIN_UNSET(port, pin_shift)    port &= ~pin_shift;

#define GET_BIT(x, pos)     (((x >> pos) & 0x01U))

#endif /* TAXIBUS_PIN_H_ */
