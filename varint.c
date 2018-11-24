#include "varint.h"


varint varint_encode(unsigned long long value){
    
}

unsigned long long varint_decode(varint varint){

}

unsigned long long zigzag_encode(signed long long value){
    return ((unsigned long long)value << 1) ^ (value >> 63);
}

signed long long zigzag_decode(unsigned long long value){

}
