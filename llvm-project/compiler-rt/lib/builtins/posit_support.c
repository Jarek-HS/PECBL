#include "../../../universal/include/universal/number/posit/posit_c_api.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//posit conversion
double posit32_to_posit64(uint32_t x);
float posit64_to_posit32(uint64_t x);


//double/float → posit
uint32_t float_to_posit32(float x);
uint64_t double_to_posit64(double x);
//posit → int/uint
int32_t posit32_to_int32(uint32_t x);
int32_t posit64_to_int32(uint64_t x);
uint32_t posit64_to_uint32(uint64_t x);
uint32_t posit32_to_uintt64(uint32_t x);
int64_t posit64_to_int64(uint64_t x);
int64_t posit32_to_int64(uint32_t x);
uint64_t posit64_to_uint64(uint64_t x);
uint64_t posit32_to_uint64(uint32_t x);
//int/uint → posit
uint32_t int32_to_posit32(int32_t x);
uint64_t int32_to_posit64(int32_t x);
uint32_t uint32_to_posit32(uint32_t x);
uint64_t uint32_to_posit64(uint32_t x);
uint32_t int64_to_posit32(int64_t x);
uint64_t int64_to_posit64(int64_t x);
uint32_t uint64_to_posit32(uint64_t x);
uint64_t uint64_to_posit64(uint64_t x);

//posit compare
bool posit_32_eq(uint32_t x, uint32_t y);
bool posit_32_ne(uint32_t x, uint32_t y);
bool posit_32_lt(uint32_t x, uint32_t y);
bool posit_32_le(uint32_t x, uint32_t y);
bool posit_32_gt(uint32_t x, uint32_t y);
bool posit_32_ge(uint32_t x, uint32_t y);
bool posit_64_eq(uint64_t x, uint64_t y);
bool posit_64_ne(uint64_t x, uint64_t y);
bool posit_64_lt(uint64_t x, uint64_t y);
bool posit_64_le(uint64_t x, uint64_t y);
bool posit_64_gt(uint64_t x, uint64_t y);
bool posit_64_ge(uint64_t x, uint64_t y);

//posit64 operation
uint64_t posit64_2_add(uint64_t x, uint64_t y);
uint64_t posit64_2_sub(uint64_t x, uint64_t y);
uint64_t posit64_2_mul(uint64_t x, uint64_t y);
uint64_t posit64_2_div(uint64_t x, uint64_t y);
//posit32 operation
uint32_t posit32_2_add(uint32_t x, uint32_t y);
uint32_t posit32_2_sub(uint32_t x, uint32_t y);
uint32_t posit32_2_mul(uint32_t x, uint32_t y);
uint32_t posit32_2_div(uint32_t x, uint32_t y);
void link_error(void) {

}
//double/float → posit
uint32_t float_to_posit32(float x) {
    posit32_t pa = posit32_fromf(x); 
    return pa.v;
}
uint64_t double_to_posit64(double x) {
    posit64_t pa = posit64_fromd(x);
    return pa.v;
}
//posit conversion

double posit32_to_posit64(uint32_t x) {
    posit32_t px = posit32_reinterpret(x);
    posit64_t pa = posit64_fromp32(px);
    double tmp;
    memcpy(&tmp, &pa.v, sizeof(double));  
    return tmp;
}
float posit64_to_posit32(uint64_t x) {
    posit64_t px = posit64_reinterpret(x);
    posit32_t pa = posit32_fromp64(px);
    float tmp;
    memcpy(&tmp, &pa.v, sizeof(float));  
    return tmp;
}

uint32_t int32_to_posit32(int32_t x) {
    posit32_t pa = posit32_fromsi(x); 
    return pa.v;
}
uint64_t int32_to_posit64(int32_t x) {
    posit64_t pa = posit64_fromsi(x); 
    return pa.v;
}
uint32_t uint32_to_posit32(uint32_t x) {
    posit32_t pa = posit32_fromui(x); 
    return pa.v;
}
uint64_t uint32_to_posit64(uint32_t x) {
    posit64_t pa = posit64_fromui(x); 
    return pa.v;
}
uint32_t int64_to_posit32(int64_t x) {
    posit32_t pa = posit32_fromsl(x);
    return pa.v;
}
uint64_t int64_to_posit64(int64_t x) {
    posit64_t pa = posit64_fromsl(x);
    return pa.v;
}
uint32_t uint64_to_posit32(uint64_t x) {
    posit64_t pa = posit64_fromul(x); 
    posit32_t pb = posit32_fromp64(pa);
    return pb.v;
}
uint64_t uint64_to_posit64(uint64_t x) {
    posit64_t pa = posit64_fromul(x);  
    return pa.v;
}
int32_t posit32_to_int32(uint32_t x) {
    posit32_t px = posit32_reinterpret(x);
    int32_t tmp = posit32_tosi(px);
    return tmp;
}

int32_t posit64_to_int32(uint64_t x) {
    posit64_t px = posit64_reinterpret(x);
    int32_t tmp = posit64_tosi(px);
    return tmp;
}
uint32_t posit32_to_uint32(uint32_t x) {
    posit32_t px = posit32_reinterpret(x);
    uint32_t tmp = posit32_toui(px);
    return tmp;
}
uint32_t posit64_to_uint32(uint64_t x) {
    posit64_t px = posit64_reinterpret(x);
    uint32_t tmp = posit64_toui(px);
    return tmp;
}
int64_t posit32_to_int64(uint32_t x) {
    posit32_t px = posit32_reinterpret(x);
    int64_t tmp = posit32_tosi(px);
    return tmp;
}
int64_t posit64_to_int64(uint64_t x) {
    posit64_t px = posit64_reinterpret(x);
    int64_t tmp = posit64_tosi(px);
    return tmp;
}
uint64_t posit32_to_uint64(uint32_t x) {
    posit32_t px = posit32_reinterpret(x);
    uint64_t tmp = posit32_toui(px);
    return tmp;
}
uint64_t posit64_to_uint64(uint64_t x) {
    posit64_t px = posit64_reinterpret(x);
    uint64_t tmp = posit64_toui(px);
    return tmp;
}
double posit32_to_double(uint64_t x) {
    posit32_t px = posit32_reinterpret(x);
    double tmp = posit32_tod(px);
    return tmp;
}
float double_to_posit32(double x) {
    posit32_t pa = posit32_fromd(x);
    float tmp;
    memcpy(&tmp, &pa.v, sizeof(float));  
    return tmp;
}
//posit compare
bool posit_32_eq(uint32_t x, uint32_t y) {
    posit32_t px = posit32_reinterpret(x);
    posit32_t py = posit32_reinterpret(y);
    int result = posit32_p32cmp(px, py);
    if(result == 0) {
        return true;
    }
    return false;
}
bool posit_32_ne(uint32_t x, uint32_t y) {
    posit32_t px = posit32_reinterpret(x);
    posit32_t py = posit32_reinterpret(y);
    int result = posit32_p32cmp(px, py);
    if(result != 0) {
        return true;
    }
    return false;
}
bool posit_32_lt(uint32_t x, uint32_t y) {
    posit32_t px = posit32_reinterpret(x);
    posit32_t py = posit32_reinterpret(y);
    int result = posit32_p32cmp(px, py);
    if(result < 0) {
        return true;
    }
    return false;
}
bool posit_32_le(uint32_t x, uint32_t y) {
    posit32_t px = posit32_reinterpret(x);
    posit32_t py = posit32_reinterpret(y);
    int result = posit32_p32cmp(px, py);
    if(result <= 0) {
        return true;
    }
    return false;
}
bool posit_32_gt(uint32_t x, uint32_t y) {
    posit32_t px = posit32_reinterpret(x);
    posit32_t py = posit32_reinterpret(y);
    int result = posit32_p32cmp(px, py);
    if(result > 0) {
        return true;
    }
    return false;
}
bool posit_32_ge(uint32_t x, uint32_t y) {
    posit32_t px = posit32_reinterpret(x);
    posit32_t py = posit32_reinterpret(y);
    int result = posit32_p32cmp(px, py);
    if(result >= 0) {
        return true;
    }
    return false;
}
bool posit_64_eq(uint64_t x, uint64_t y) {
    posit64_t px = posit64_reinterpret(x);
    posit64_t py = posit64_reinterpret(y);
    int result = posit64_p64cmp(px, py);
    if(result == 0) {
        return true;
    }
    return false;
}
bool posit_64_ne(uint64_t x, uint64_t y) {
    posit64_t px = posit64_reinterpret(x);
    posit64_t py = posit64_reinterpret(y);
    int result = posit64_p64cmp(px, py);
    if(result != 0) {
        return true;
    }
    return false;
}
bool posit_64_lt(uint64_t x, uint64_t y) {
    posit64_t px = posit64_reinterpret(x);
    posit64_t py = posit64_reinterpret(y);
    int result = posit64_p64cmp(px, py);
    if(result < 0) {
        return true;
    }
    return false;
}
bool posit_64_le(uint64_t x, uint64_t y) {
    posit64_t px = posit64_reinterpret(x);
    posit64_t py = posit64_reinterpret(y);
    int result = posit64_p64cmp(px, py);
    if(result <= 0) {
        return true;
    }
    return false;
}
bool posit_64_gt(uint64_t x, uint64_t y) {
    posit64_t px = posit64_reinterpret(x);
    posit64_t py = posit64_reinterpret(y);
    int result = posit64_p64cmp(px, py);
    if(result > 0) {
        return true;
    }
    return false;
}
bool posit_64_ge(uint64_t x, uint64_t y) {
    posit64_t px = posit64_reinterpret(x);
    posit64_t py = posit64_reinterpret(y);
    int result = posit64_p64cmp(px, py);
    if(result >= 0) {
        return true;
    }
    return false;
}

//posit64 operation
uint64_t posit64_2_add(uint64_t x, uint64_t y) {
    posit64_t pa = posit64_ㄉ(x);
    posit64_t pb = posit64_reinterpret(y);
    posit64_t sum = posit64_add(pa, pb); 
    return sum.v;
}
uint64_t posit64_2_sub(uint64_t x, uint64_t y) {
    posit64_t pa = posit64_reinterpret(x);
    posit64_t pb = posit64_reinterpret(y);
    posit64_t sum = posit64_sub(pa, pb);
    return sum.v;
}
uint64_t posit64_2_mul(uint64_t x, uint64_t y) {
    posit64_t pa = posit64_reinterpret(x);
    posit64_t pb = posit64_reinterpret(y);
    posit64_t sum = posit64_mul(pa, pb);
    return sum.v;
}
uint64_t posit64_2_div(uint64_t x, uint64_t y) {
    posit64_t pa = posit64_reinterpret(x);
    posit64_t pb = posit64_reinterpret(y);
    posit64_t sum = posit64_div(pa, pb);
    return sum.v;
}
uint32_t posit32_2_add(uint32_t x, uint32_t y) {
    posit32_t pa = posit32_reinterpret(x);
    posit32_t pb = posit32_reinterpret(y);
    posit32_t sum = posit32_add(pa, pb);
    return sum.v;
}
uint32_t posit32_2_sub(uint32_t x, uint32_t y) {
    posit32_t pa = posit32_reinterpret(x);
    posit32_t pb = posit32_reinterpret(y);
    posit32_t sum = posit32_sub(pa, pb);
    return sum.v;
}
uint32_t posit32_2_mul(uint32_t x, uint32_t y) {
    posit32_t pa = posit32_reinterpret(x);
    posit32_t pb = posit32_reinterpret(y);
    posit32_t sum = posit32_mul(pa, pb);
    return sum.v;
}
uint32_t posit32_2_div(uint32_t x, uint32_t y) {
    posit32_t pa = posit32_reinterpret(x);
    posit32_t pb = posit32_reinterpret(y);
    posit32_t sum = posit32_div(pa, pb);
    return sum.v;
}
