#ifndef MACRO_H_INCLUDED
#define MACRO_H_INCLUDED

/**********************************************************
* MACRO:
***********************************************************/
/**********************************************************
* NAME: sbiBF(byte,bit)
* DESCRIPTION: set bit in byte (set to 1)
* RETURN: none
***********************************************************/
#define sbiBF(byte,bit)         byte |= (1<<bit)

/**********************************************************
* NAME: cbiBF(byte,bit)
* DESCRIPTION: clear bit in byte (set to 0)
* RETURN: none
***********************************************************/
#define cbiBF(byte,bit)         byte &= ~(1<<bit)

/**********************************************************
* NAME: getLow(word)
* DESCRIPTION: get the low part of word
* RETURN: low part of word
***********************************************************/
#define getLow(word)            word&0b11111111

/**********************************************************
* NAME: getHigh(word)
* description: get the high part of word
* return: high part of word
***********************************************************/
#define getHigh(word)           (word>>8)&0b11111111



#endif // MACRO_H_INCLUDED
