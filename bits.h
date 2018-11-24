#ifndef BITS_H
#define BITS_H

#if defined(TYPES_64) || defined(TYPES_32) || !defined(TYPES_CUSTOM)
#define SIZE_LL 64
#define SIZE_L  64
#define SIZE_I  32
#endif


union sig_ll {
    signed long long value : SIZE_LL;
    struct {
        unsigned long long value : SIZE_LL - 1;
        unsigned char sig : 1;
    } signature;
};


union sig_l {
    signed long value : SIZE_L;
    struct {
        unsigned long value : SIZE_L - 1;
        unsigned char sig : 1;
    } signature;
};

union sig_i {
    signed int value : SIZE_I;
    struct {
        unsigned int value : SIZE_I - 1;
        unsigned char sig : 1;
    } signature;
};

#endif
