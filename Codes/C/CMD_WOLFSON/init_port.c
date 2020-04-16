/**********************************************************
* NAME OF FILE: init_port.c
* HEADER FILES: -) main: init_port.h

* AUTHORS: SUPER_MICHOU
* COPYLEFT: MUDADATISM_PROD
* HOW DOES IT WORK ?:

***********************************************************/

/**********************************************************
* INCLUDED HEADERS:
***********************************************************/
#include "init_port.h"
#include "macro.h"

/**********************************************************
* FUNCTIONS:
***********************************************************/
/**********************************************************
* NAME: port()
* DESCRIPTION: initialize ports
* RETURN: none
***********************************************************/
void port()
{
     /* PULL UP CONFIGURATION FOR INPUT */
    sbiBF(PORTD,PD2); // PUSH BUTTON 1
    sbiBF(PORTD,PD3); // PUSH BUTTON 2

    // outputs:
    sbiBF(DDRD,DDD5);
    sbiBF(DDRD,DDD6);
    sbiBF(DDRD,DDD7);


}

/**********************************************************
* NAME: interrupt()
* DESCRIPTION: initialize interruptions
* RETURN: none
***********************************************************/
void interrupt()
{
    // interruption on falling edge:
    // EICRA:
    sbiBF(EICRA,ISC11);
    sbiBF(EICRA,ISC01);

    // EIMSK:
    sbiBF(EIMSK,INT1);
    sbiBF(EIMSK,INT0);

}

/**********************************************************
* NAME: reset_LED()
* DESCRIPTION: reset all led states
* RETURN: none
***********************************************************/
void reset_LED()
{
    cbiBF(PORTD,PD5);
    cbiBF(PORTD,PD6);
    cbiBF(PORTD,PD7);

}
