#ifndef RANDOMC_H
#define RANDOMC_H

#include <math.h>
#include <assert.h>
#include <stdio.h>

// Define 32 bit signed and unsigned integers.
// Change these definitions, if necessary, on 64 bit computers
typedef   signed long int32;
typedef unsigned long uint32;

class TRandomMersenne                  // encapsulate random number generator
{
#if 0
    // define constants for MT11213A:
    // (32 bit constants cannot be defined as enum in 16-bit compilers)
#define MERS_N   351
#define MERS_M   175
#define MERS_R   19
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   17
#define MERS_A   0xE4BD75F5
#define MERS_B   0x655E5280
#define MERS_C   0xFFD58000
#else
    // or constants for MT19937:
#define MERS_N   624
#define MERS_M   397
#define MERS_R   31
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   18
#define MERS_A   0x9908B0DF
#define MERS_B   0x9D2C5680
#define MERS_C   0xEFC60000
#endif
public:
    TRandomMersenne( uint32 seed )       // constructor
    {
        RandomInit( seed );
    }
    void RandomInit( uint32 seed );      // re-seed
    void RandomInitByArray( uint32 seeds[], int length ); // seed by more than 32 bits
    int IRandom( int min, int max );     // output random integer
    double Random();                     // output random float
    uint32 BRandom();                    // output random bits
private:
    uint32 mt[MERS_N];                   // state vector
    int mti;                             // index into mt
    enum TArch {LITTLE_ENDIAN1, BIG_ENDIAN1, NONIEEE};
    TArch Architecture;                  // conversion to float depends on computer architecture
};

class TRanrotBGenerator                // encapsulate random number generator
{
    enum constants                       // define parameters
    {
        KK = 17, JJ = 10, R1 = 13, R2 =  9
    };
public:
    void RandomInit( uint32 seed );      // initialization
    int IRandom( int min, int max );     // get integer random number in desired interval
    double Random();                     // get floating point random number
    TRanrotBGenerator( uint32 seed );    // constructor
protected:
    int p1, p2;                          // indexes into buffer
    uint32 randbuffer[KK];               // history buffer
    uint32 randbufcopy[KK * 2];          // used for self-test
    enum TArch {LITTLE_ENDIAN1, BIG_ENDIAN1, NONIEEE};
    TArch Architecture;                  // conversion to float depends on computer architecture
};


class TRanrotWGenerator                // encapsulate random number generator
{
    enum constants                       // define parameters
    {
        KK = 17, JJ = 10, R1 = 19, R2 =  27
    };
public:
    void RandomInit( uint32 seed );      // initialization
    int IRandom( int min, int max );     // get integer random number in desired interval
    long double Random();                // get floating point random number
    uint32 BRandom();                    // output random bits
    TRanrotWGenerator( uint32 seed );    // constructor
protected:
    int p1, p2;                          // indexes into buffer
    union                                // used for conversion to float
    {
        long double randp1;
        uint32 randbits[3];
    };
    uint32 randbuffer[KK][2];            // history buffer
    uint32 randbufcopy[KK * 2][2];       // used for self-test
    enum TArch {LITTLE_ENDIAN1, BIG_ENDIAN1, NONIEEE, EXTENDEDPRECISIONLITTLEENDIAN};
    TArch Architecture;                  // conversion to float depends on computer architecture
};

class TRandomMotherOfAll               // encapsulate random number generator
{
public:
    void RandomInit( uint32 seed );      // initialization
    int IRandom( int min, int max );     // get integer random number in desired interval
    double Random();                     // get floating point random number
    TRandomMotherOfAll( uint32 seed );   // constructor
protected:
    double x[5];                         // history buffer
};

#endif

