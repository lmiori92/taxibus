/*
 * interface.c
 *
 *  Created on: 29 mar 2017
 *      Author: lorenzo
 */

#ifndef DEASPLAY_TAXIBUS_INTERFACE_C_
#define DEASPLAY_TAXIBUS_INTERFACE_C_

#include "interface.h"

e_interface_err interface_write(t_interface *interface)
{
    e_interface_err retval = INTERFACE_UNKNOWN;

    /* call the write function of the interface */
    retval = interface->write(interface);

    /* and then call the chained one */
    if (retval == INTERFACE_OK)
    {

    }

    return retval;
}

#endif /* DEASPLAY_TAXIBUS_INTERFACE_C_ */
