#include "varint.h"
#include <stdlib.h>

varint varint_encode(unsigned long long value){
    varint result;

    if (value <= 240){
        result = (varint)malloc(1);
        result[0] = (char)value;
    }
    else if (value <= 2287)
    {
        result = (varint)malloc(2);
        result[0] = (char)(((value - 240) >> 8) + 241);
        result[1] = (char)(value - 240);
    }
    else if (value <= 67823)
    {
        result = (varint)malloc(3);
        result[0] = 249;
        result[1] = (char)((value - 2288) >> 8);
        result[2] = (char)(value - 2288);
    }
    else
    {
        unsigned long long header = 255;
        unsigned long long match = 0x00FFFFFFFFFFFFFFUL;
        while (value <= match)
        {
            --header;
            match >>= 8;
        }
        int max = (int)(header - 247);

        result = (varint)malloc(max + 1);
        result[0] = (char) header;
        for (int i = 0; i < max; ++i)
                result[i+1] = (char)(value >> (i << 3));
    }
    return result;
}

unsigned long long varint_decode(varint varint){
    unsigned long long header = (unsigned char)varint[0];
    if(header <= 240){
            free(varint);
            return header;
    }
    if(header <= 248){
            free(varint);
            return 240UL + ((header - 241) << 8) + (unsigned char)varint[1];
    }
    if(header == 249){
            free(varint);
            return 2288UL + ((unsigned char)varint[1] << 8) + (unsigned char)varint[2];
    }
    unsigned long result = (unsigned char)varint[1] | ((unsigned char)varint[2] << 8) | ((unsigned char)varint[3]);
    int compare = 2;
    int head = (int)(header - 247);
    while(head > ++compare) result |= (unsigned char)varint[compare + 2] << (compare << 3);
    free(varint);
    return result;
}

unsigned long long zigzag_encode(signed long long value){
    union sig_ll convert = {value};
    return (convert.signature.value << 1) ^ (unsigned long long)convert.signature.sig;
}

signed long long zigzag_decode(unsigned long long value){
    union sig_ll convert = {value << 63};
    return (signed long long)((value >> 1) ^ (unsigned long long)convert.signature.sig);
}
