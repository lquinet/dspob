
#include <avr/io.h>
#include <avr/interrupt.h>

#include "codec_analogue.h"
#include "codec_digital.h"
#include "codec_fileTest.h"
#include "init_port.h"

int main(void)
{
    /**********************************************************
    * FUNCTIONS TESTS:
    ***********************************************************/
    // initialisation port and interrupt
    port();
    interrupt();
    sei(); // open the global interruput mask

    sbiBF(PORTD,PD5); // activate the "STAND BY" diode LED
    codec_default(); // set codec parameters to default

    while(1)
    {

    }

    return 0;
}


/**********************************************************
* INTERRUPT VECTORS:
***********************************************************/


/** ANALOG PATH **/
ISR(INT0_vect)
{
    cli();
    // code:
    reset_LED();
    sbiBF(PORTD,PD6);

    /** CODEC FUNCTION **/
    codec_mic_ADC();

    sei();

}

/** DIGITAL PATH **/
ISR(INT1_vect)
{
    cli();
    // code:
    reset_LED();
    sbiBF(PORTD,PD7);

    /** CODEC FUNCTION **/
    codec_line_ADC();

    sei();

}

