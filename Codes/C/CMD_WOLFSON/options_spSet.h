#ifndef OPTIONS_SPSET_H_INCLUDED
#define OPTIONS_SPSET_H_INCLUDED

/**********************************************************
* ENUM OPTIONS:
***********************************************************/
/** DSP COMMUNICATION **/
enum OPTIONS_DSP_SETUP
{
    DSP = 1,
    I2S = 2,
    MSBLJ = 3,
    MSBRJ = 4
};

/** DATA BIT LENGTH **/
enum OPTIONS_DATA_BIT
{
    BIT16 = 1,
    BIT20 = 2,
    BIT24 = 3,
    BIT32 = 4
};

/** FREQUENCY SAMPLE **/
enum OPTIONS_FS
{
    FS8 = 1,
    FS32 = 2,
    FS441 = 3,
    FS48 = 4,
    FS882 = 5,
    FS96 = 6
};



#endif // OPTIONS_SPSET_H_INCLUDED
