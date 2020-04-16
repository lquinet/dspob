#ifndef INIT_PORT_H_INCLUDED
/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

#define INIT_PORT_H_INCLUDED
/**********************************************************
* FUNCTION PROTOTYPES:
***********************************************************/
void port();
void interrupt();
void reset_LED();

#endif // INIT_PORT_H_INCLUDED
