#ifndef _FIXEDPTC_H_
#define _FIXEDPTC_H_

/*
 * fixedptc.h is a 32-bit or 64-bit fixed point numeric library.
 *
 * The symbol FIXEDPT_BITS, if defined before this library header file
 * is included, governs the number of bits in the data type (its "width").
 * The default width is 32-bit (FIXEDPT_BITS=32) and it can be used
 * on any recent C99 compiler. The 64-bit precision (FIXEDPT_BITS=64) is
 * available on compilers which implement 128-bit "long long" types. This
 * precision has been tested on GCC 4.2+.
 *
 * Since the precision in both cases is relatively low, many complex
 * functions (more complex than div & mul) take a large hit on the precision
 * of the end result because errors in precision accumulate.
 * This loss of precision can be lessened by increasing the number of
 * bits dedicated to the fraction part, but at the loss of range.
 *
 * Adventurous users might utilize this library to build two data types:
 * one which has the range, and one which has the precision, and carefully
 * convert between them (including adding two number of each type to produce
 * a simulated type with a larger range and precision).
 *
 * The ideas and algorithms have been cherry-picked from a large number
 * of previous implementations available on the Internet.
 * Tim Hartrick has contributed cleanup and 64-bit support patches.
 *
 * == Special notes for the 32-bit precision ==
 * Signed 32-bit fixed point numeric library for the 24.8 format.
 * The specific limits are -8388608.999... to 8388607.999... and the
 * most precise number is 0.00390625. In practice, you should not count
 * on working with numbers larger than a million or to the precision
 * of more than 2 decimal places. Make peace with the fact that PI
 * is 3.14 here. :)
 */

/*-
 * Copyright (c) 2010-2012 Ivan Voras <ivoras@freebsd.org>
 * Copyright (c) 2012 Tim Hartrick <tim@edgecast.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef FIXEDPT_BITS
#define FIXEDPT_BITS    32
#endif
#include"arm_math.h"

#if FIXEDPT_BITS == 32
typedef int32_t fixedpt;
typedef    int64_t    fixedptd;
typedef    uint32_t fixedptu;
typedef    uint64_t fixedptud;
#elif FIXEDPT_BITS == 64
typedef int64_t fixedpt;
typedef    __int128_t fixedptd;
typedef    uint64_t fixedptu;
typedef    __uint128_t fixedptud;
#else
#error "FIXEDPT_BITS must be equal to 32 or 64"
#endif

#ifndef FIXEDPT_WBITS
#define FIXEDPT_WBITS    4
#endif

#if FIXEDPT_WBITS >= FIXEDPT_BITS
#error "FIXEDPT_WBITS must be less than or equal to FIXEDPT_BITS"
#endif

#define FIXEDPT_VCSID "$Id: fixedptc.h,v 00c74d842389 2012/07/17 23:30:18 ivoras $"

#define FIXEDPT_FBITS               (FIXEDPT_BITS - FIXEDPT_WBITS)
#define FIXEDPT_FBITS_16            16
#define FIXEDPT_FBITS_06            6
#define FIXEDPT_FBITS_18            18
#define FIXEDPT_FBITS_22            22
#define FIXEDPT_FBITS_24            24
#define FIXEDPT_FBITS_34            34
#define FIXEDPT_FBITS_31            31
#define FIXEDPT_FMASK               (((fixedpt)1 << FIXEDPT_FBITS) - 1)

#define fixedpt_rconst(R)           ((fixedpt)((R) * (((fixedptd)1 << FIXEDPT_FBITS) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64(R)        ((fixedptd)((R) * (((fixedptd)1 << FIXEDPT_FBITS) \
+ ((R) >= 0 ? 0.5 : -0.5))))
#define fixedpt_rconst_64_F28(R)        ((fixedptd)((R) * (((fixedptd)1 << FIXEDPT_FBITS) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64_F22(R)    ((fixedptd)((R) * (((fixedptd)1 << FIXEDPT_FBITS_22) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64_F18(R)    ((fixedptd)((R) * (((fixedptd)1 << FIXEDPT_FBITS_18) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_32_F18(R)    ((fixedpt)((R) * (((fixedpt)1 << FIXEDPT_FBITS_18) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_32_F22(R)    ((fixedpt)((R) * (((fixedpt)1 << FIXEDPT_FBITS_22) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_32_F24(R)    ((fixedpt)((R) * (((fixedpt)1 << FIXEDPT_FBITS_24) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_32_F31(R)    ((fixedpt)((R) * (((fixedpt)1 << FIXEDPT_FBITS_31) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_32_F06(R)    ((fixedpt)((R) * (((fixedpt)1 << FIXEDPT_FBITS_06) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64_F34(R)    ((fixedptd)((R) * (((fixedptd)1 << FIXEDPT_FBITS_34) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64_F38(R)    ((fixedptd)((R) * (((fixedptd)1 << 38) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64_F31(R)    ((fixedptd)((R) * (((fixedptd)1 << FIXEDPT_FBITS_31) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_F31(R)    ((fixedpt)((R) * (((fixedptd)1 << FIXEDPT_FBITS_31) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64_F54(R)    ((fixedptd)((R) * (((fixedptd)1 << 54) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_rconst_64_F44(R)    ((fixedptd)((R) * (((fixedptd)1 << 44) \
+ ((R) >= 0 ? 0.5 : -0.5))))

#define fixedpt_cov_F28_to_F22(R)   ((R>>6))
#define fixedpt_cov_F22_to_F28(R)   ((R<<6))

#define fixedpt_cov_F28_to_F24(R)   ((R>>4))
#define fixedpt_cov_F24_to_F28(R)   ((R<<4))

#define fixedpt_cov_F28_to_F18(R)   ((R>>10))
#define fixedpt_cov_F28_to_F16(R)   ((R>>12))
#define fixedpt_cov_F28_to_F06(R)   ((R>>22))


#define fixedpt_cov_F28_to_F34(R)   ((R<<6))
#define fixedpt_cov_F34_to_F28(R)   ((R>>6))

#define fixedpt_cov_F28_to_F54(R) ((R<<26))
#define fixedpt_cov_F54_to_F28(R) ((R>>26))
#define fixedpt_cov_F54_to_F31(R) ((R>>23))

#define fixedpt_cov_F22_to_F44(R) ((R<<22))

#define fixedpt_cov_F28_to_F44(R) ((R<<16))
#define fixedpt_cov_F44_to_F28(R) ((R>>16))

#define fixedpt_cov_F44_to_F31(R) ((R>>13))

#define fixedpt_cov_F28_to_F38(R) ((R<<10))


#define fixedpt_cov_F28_to_F54(R) ((R<<26))
#define fixedpt_cov_F54_to_F28(R) ((R>>26))

#define fixedpt_cov_F28_to_F31(R)   ((R<<3))
#define fixedpt_cov_F31_to_F28(R)   ((R>>3))
#define fixedpt_cov_F31_to_F18(R)   ((R>>13))
#define fixedpt_cov_F31_to_F22(R)   ((R>>9))
#define fixedpt_cov_64_F31_to_F18(R)   ((((fixedptd)R)>>13))

#define fixedpt_cov_F22_to_F28(R)   ((R<<6))

#define fixedpt_fromint(I)          ((fixedptd)(I) << FIXEDPT_FBITS)
#define fixedpt_toint(F)            ((F) >> FIXEDPT_FBITS)
#define fixedpt_tofloat(F)          (((float)(F))/ (1 << FIXEDPT_FBITS))
#define fixedpt_tofloat_F22(F)      (((float)(F))/ (1 << FIXEDPT_FBITS_22))
#define fixedpt_tofloat_F24(F)      (((float)(F))/ (1 << FIXEDPT_FBITS_24))
#define fixedpt_tofloat_64_F22(F)      (((double)(F))/ (1 << FIXEDPT_FBITS_22))
#define fixedpt_tofloat_64_F18(F)      (((double)(F))/ (1 << FIXEDPT_FBITS_18))
#define fixedpt_tofloat_32_F18(F)      (((float)(F))/ (1 << FIXEDPT_FBITS_18))
#define fixedpt_tofloat_32_F16(F)      (((float)(F))/ (1 << FIXEDPT_FBITS_16))
#define fixedpt_tofloat_32_F06(F)      (((float)(F))/ (1 << FIXEDPT_FBITS_06))


#define fixedpt_tofloat_64(F)          (((double)(F))/ (1 << FIXEDPT_FBITS))
#define fixedpt_tofloat_F34(F)          (((double)(F))/ ((int64_t)1 << FIXEDPT_FBITS_34))
#define fixedpt_tofloat_F31(F)          (((double)(F))/ ((int64_t)1 << FIXEDPT_FBITS_31))
#define fixedpt_tofloat_F38(F)          (((double)(F))/ ((int64_t)1 << 38))
#define fixedpt_tofloat_F44(F)          (((double)(F))/ ((int64_t)1 << 44))
#define fixedpt_tofloat_F54(F)          (((double)(F))/ ((int64_t)1 << 54))

#define fixedpt_add(A,B)            ((A) + (B))
#define fixedpt_sub(A,B)            ((A) - (B))
#define fixedpt_xmul(A,B)                        \
((fixedpt)(((fixedptd)(A) * (fixedptd)(B)) >> FIXEDPT_FBITS))
#define fixedpt_xdiv(A,B)                        \
((fixedpt)(((fixedptd)(A) << FIXEDPT_FBITS) / (fixedptd)(B)))
#define fixedpt_fracpart(A) ((fixedpt)(A) & FIXEDPT_FMASK)

#define FIXEDPT_ONE                 ((fixedpt)((fixedpt)1 << FIXEDPT_FBITS))
#define FIXEDPT_ONE_64              ((fixedptd)((fixedptd)1 << FIXEDPT_FBITS))
#define FIXEDPT_ONE_64_F22          ((fixedptd)((fixedptd)1 << FIXEDPT_FBITS_22))

#define FIXEDPT_ONE_64_F18              ((fixedptd)((fixedptd)1 << FIXEDPT_FBITS_18))
#define FIXEDPT_ONE_32_F18              ((fixedpt)((fixedpt)1 << FIXEDPT_FBITS_18))
#define FIXEDPT_ONE_32_F16              ((fixedpt)((fixedpt)1 << FIXEDPT_FBITS_16))
#define FIXEDPT_ONE_32_F06              ((fixedpt)((fixedpt)1 << FIXEDPT_FBITS_06))
#define FIXEDPT_ONE_32_F24              ((fixedpt)((fixedpt)1 << FIXEDPT_FBITS_24))
#define FIXEDPT_ONE_32_F22              ((fixedpt)((fixedpt)1 << FIXEDPT_FBITS_22))
#define FIXEDPT_ONE_32_F31             ((fixedpt)((fixedpt)1 << FIXEDPT_FBITS_31))
#define NEG_FIXEDPT_ONE_32_F31          fixedpt_rconst_32_F31(-1)
#define NEG_FIXEDPT_ONE          fixedpt_rconst(-1)

#define FIXEDPT_ONE_HALF            (FIXEDPT_ONE >> 1)
#define FIXEDPT_ONE_HALF_64         (FIXEDPT_ONE_64 >> 1)
#define FIXEDPT_ONE_HALF_64_F22     (FIXEDPT_ONE_64_F22 >> 1)
#define FIXEDPT_ONE_HALF_32_F18     (FIXEDPT_ONE_32_F18 >> 1)

#define FIXEDPT_MAX                 fixedpt_rconst(7.99)
#define FIXEDPT_TWO                 (FIXEDPT_ONE + FIXEDPT_ONE)
#define FIXEDPT_TWO_64_F28          (FIXEDPT_ONE_64+FIXEDPT_ONE_64)
#define FIXEDPT_NEG_ONE             fixedpt_rconst_64(-1)
#define FIXEDPT_NEG_ONE_F22         fixedpt_rconst_64_F22(-1)
#define FIXEDPT_NEG_ONE_F18         fixedpt_rconst_32_F18(-1)

#define FIXEDPT_PI                  fixedpt_rconst(3.14159265358979323846)
#define FIXEDPT_PI_64_F34           fixedpt_rconst_64_F34(3.14159265358979323846)
#define FIXEDPT_TWO_PI              fixedpt_rconst(2. * 3.14159265358979323846)
#define FIXEDPT_TWO_PI_64           fixedpt_rconst_64(2. * 3.14159265358979323846)
#define FIXEDPT_TWO_PI_64_F34       fixedpt_rconst_64_F34(2 * 3.14159265358979323846)
#define FIXEDPT_INV_TWO_PI_F31      fixedpt_rconst_F31(1/(2 * 3.14159265358979323846))
#define FIXEDPT_HALF_PI             fixedpt_rconst(3.14159265358979323846 / 2)
#define FIXEDPT_E                   fixedpt_rconst(2.7182818284590452354)
#define FIXEDPT_INV_2PI             fixedpt_rconst(1/(2 * 3.14159265358979323846))
#define FIXEDPT_3PI2                fixedpt_rconst((3*3.14159265358979323846)/2)
#define HALF                        fixedpt_rconst(0.5)

#define I_HALF                      fixedpt_rconst(0.50021)
#define HALF_1                      fixedpt_rconst(0.49)
#define ZERO                        fixedpt_rconst(0.00005)
#define update_comp                 fixedpt_rconst(0.0001)
#define FOUR                        fixedpt_rconst(4)
#define giga_64                     fixedpt_rconst_64(1e6)
#define e_four_64                   fixedpt_rconst_64(1e4)
#define e_five_64                   fixedpt_rconst_64(1e5)
#define e_six_64                   fixedpt_rconst_64(1e6)
#define inv_e_three_32_F18          fixedpt_rconst_32_F18(1e-3)
#define e_three_32_F18              fixedpt_rconst_32_F18(1e3)
#define e_three_32_F31              fixedpt_rconst_F31(1e3)
#define inv_e_four_64               fixedpt_rconst_64(1e-4)
#define inv_giga_64                 fixedpt_rconst_64(1e-6)
#define rad2deg_conv_F18            (fixedpt)15019773 //180/pi
#define deg2rad_conv_F18            (fixedpt)4575      //pi/180
#define deg2rad_rnd_div            (fixedpt)15019773 //180/pi
#define deg2rad_rnd_mul           (fixedpt)4575 //180/pi
#define test        fixedpt_rconst(1.1141)

#define fixedpt_abs(A) ((A) < 0 ? -(A) : (A))

#define LOWER_RND                   0X00000001
static inline int32_t rnd(int64_t x)
{
    int32_t y;
    y=x>>1;
    if(x&LOWER_RND)
    {
        printf("result rounded!!\n\n\n");
        y=y+1;
    }
    
    return(y);
}
/* Multiplies two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_mul(fixedpt A, fixedpt B)
{
    int64_t product;
    product = (int64_t)A * B;
    
    return (fixedpt)(rnd(product >> (FIXEDPT_FBITS-1)));

}
/* Multiplies two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_mul_F24(fixedpt A, fixedpt B)
{
    int64_t product;
    product = (int64_t)A * B;
    
    return (fixedpt)(rnd(product >> (FIXEDPT_FBITS_24-1)));

}
/* Multiplies two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_mul_F31(fixedpt A, fixedpt B)
{
    int64_t product;
    product = (int64_t)A * B;
    
    return (fixedpt)(rnd(product >> (FIXEDPT_FBITS_31-1)));
}

/* Multiplies two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_mul_F18(fixedpt A, fixedpt B)
{
    int64_t product;
    product = (int64_t)A * B;
    
    return (fixedpt)(rnd(product >> (FIXEDPT_FBITS_18-1)));
}
/* Multiplies two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_mul_F16(fixedpt A, fixedpt B)
{
    int64_t product;
    product = (int64_t)A * B;
    
    return (fixedpt)(rnd(product >> (FIXEDPT_FBITS_16-1)));
}
/* Multiplies two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_mul_F06(fixedpt A, fixedpt B)
{
    int64_t product;
    product = (int64_t)A * B;
    
    return (fixedpt)(rnd(product >> (FIXEDPT_FBITS_06-1)));
}
/* Multiplies two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_mul_F22(fixedpt A, fixedpt B)
{
    int64_t product;
    product = (int64_t)A * B;
    
    return (fixedpt)(rnd(product >> (FIXEDPT_FBITS_22-1)));
}

/* Divides two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_div(fixedpt A, fixedpt B)
{
    if(B==0)
        return 0;
    else
        return (((fixedptd)A << FIXEDPT_FBITS) / (fixedptd)B);
}
/* Divides two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_div_F18(fixedpt A, fixedpt B)
{
    if(B==0)
        return 0;
    else
        return (((fixedptd)A << FIXEDPT_FBITS_18) / (fixedptd)B);
}
/* Divides two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_div_F16(fixedpt A, fixedpt B)
{
    if(B==0)
        return 0;
    else
        return (((fixedptd)A << FIXEDPT_FBITS_16) / (fixedptd)B);
}
/* Divides two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_div_F06(fixedpt A, fixedpt B)
{
    if(B==0)
        return 0;
    else
        return (((fixedptd)A << FIXEDPT_FBITS_06) / (fixedptd)B);
}
/* Divides two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_div_F22(fixedpt A, fixedpt B)
{
    if(B==0)
        return 0;
    else
        return (((fixedptd)A << FIXEDPT_FBITS_22) / (fixedptd)B);
}
/* Divides two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_div_F24(fixedpt A, fixedpt B)
{
    if(B==0)
        return 0;
    else
        return (((fixedptd)A << FIXEDPT_FBITS_24) / (fixedptd)B);
}
/* Divides two fixedpt numbers, returns the result. */
static inline fixedpt
fixedpt_div_F31(fixedpt A, fixedpt B)
{
    if(B==0)
        return 0;
    else
        return (((fixedptd)A << 31) / (fixedptd)B);
}
/*
 * Note: adding and substracting fixedpt numbers can be done by using
 * the regular integer operators + and -.
 */

/**
 * Convert the given fixedpt number to a decimal string.
 * The max_dec argument specifies how many decimal digits to the right
 * of the decimal point to generate. If set to -1, the "default" number
 * of decimal digits will be used (2 for 32-bit fixedpt width, 10 for
 * 64-bit fixedpt width); If set to -2, "all" of the digits will
 * be returned, meaning there will be invalid, bogus digits outside the
 * specified precisions.
 */
static inline void
fixedpt_str(fixedpt A, char *str, int max_dec)
{
    int ndec = 0, slen = 0;
    char tmp[12] = {0};
    fixedptud fr, ip;
    const fixedptud one = (fixedptud)1 << FIXEDPT_BITS;
    const fixedptud mask = one - 1;
    
    if (max_dec == -1)
#if FIXEDPT_BITS == 32
        max_dec = 2;
#elif FIXEDPT_BITS == 64
    max_dec = 10;
#else
#error Invalid width
#endif
    else if (max_dec == -2)
        max_dec = (FIXEDPT_BITS - FIXEDPT_WBITS);
    
    if (A < 0) {
        str[slen++] = '-';
        A *= -1;
    }
    
    ip = fixedpt_toint(A);
    do {
        tmp[ndec++] = '0' + ip % 10;
        ip /= 10;
    } while (ip != 0);
    
    while (ndec > 0)
        str[slen++] = tmp[--ndec];
    str[slen++] = '.';
    
    fr = (fixedpt_fracpart(A) << FIXEDPT_WBITS) & mask;
    do {
        fr = (fr & mask) * 10;
        
        str[slen++] = '0' + (fr >> FIXEDPT_BITS) % 10;
        ndec++;
    } while (fr != 0 && ndec < max_dec);
    
    if (ndec > 1 && str[slen-1] == '0')
        str[slen-1] = '\0'; /* cut off trailing 0 */
    else
        str[slen] = '\0';
}

/* Converts the given fixedpt number into a string, using a static
 * (non-threadsafe) string buffer */
static inline char*
fixedpt_cstr(const fixedpt A, const int max_dec)
{
    static char str[25];
    
    fixedpt_str(A, str, max_dec);
    return (str);
}


/* Returns the square root of the given number, or -1 in case of error */
static inline fixedpt
fixedpt_sqrt(fixedpt A)
{
    int invert = 0;
    int iter = FIXEDPT_FBITS;
    int l, i;
    
    if (A < 0)
        return (-1);
    if (A == 0 || A == FIXEDPT_ONE)
        return (A);
    if (A < FIXEDPT_ONE && A > 6) {
        invert = 1;
        A = fixedpt_div(FIXEDPT_ONE, A);
    }
    if (A > FIXEDPT_ONE) {
        int s = A;
        
        iter = 0;
        while (s > 0) {
            s >>= 2;
            iter++;
        }
    }
    
    /* Newton's iterations */
    l = (A >> 1) + 1;
    for (i = 0; i < iter; i++)
        l = (l + fixedpt_div(A, l)) >> 1;
    if (invert)
        return (fixedpt_div(FIXEDPT_ONE, l));
    return (l);
}

/* Returns the square root of the given number, or -1 in case of error */
static inline fixedpt
fixedpt_sqrt_F18(fixedpt A)
{
    int invert = 0;
    int iter = FIXEDPT_FBITS_18;
    int l, i;
    
    if (A < 0)
        return (-1);
    if (A == 0 || A == FIXEDPT_ONE_32_F18)
        return (A);
    if (A < FIXEDPT_ONE_32_F18 && A > 6) {
        invert = 1;
        A = fixedpt_div_F18(FIXEDPT_ONE_32_F18, A);
    }
    if (A > FIXEDPT_ONE_32_F18) {
        int s = A;
        
        iter = 0;
        while (s > 0) {
            s >>= 2;
            iter++;
        }
    }
    
    /* Newton's iterations */
    l = (A >> 1) + 1;
    for (i = 0; i < iter; i++)
        l = (l + fixedpt_div_F18(A, l)) >> 1;
    if (invert)
        return (fixedpt_div_F18(FIXEDPT_ONE_32_F18, l));
    return (l);
}

/* Returns the square root of the given number, or -1 in case of error */
static inline fixedpt
fixedpt_sqrt_F24(fixedpt A)
{
    int invert = 0;
    int iter = FIXEDPT_FBITS_24;
    int l, i;
    
    if (A < 0)
        return (-1);
    if (A == 0 || A == FIXEDPT_ONE_32_F24)
        return (A);
    if (A < FIXEDPT_ONE_32_F24 && A > 6) {
        invert = 1;
        A = fixedpt_div_F24(FIXEDPT_ONE_32_F24, A);
    }
    if (A > FIXEDPT_ONE_32_F24) {
        int s = A;
        
        iter = 0;
        while (s > 0) {
            s >>= 2;
            iter++;
        }
    }
    
    /* Newton's iterations */
    l = (A >> 1) + 1;
    for (i = 0; i < iter; i++)
        l = (l + fixedpt_div_F24(A, l)) >> 1;
    if (invert)
        return (fixedpt_div_F24(FIXEDPT_ONE_32_F24, l));
    return (l);
}


/* Returns the sine of the given fixedpt number.
 * Note: the loss of precision is extraordinary! */
static inline fixedpt
fixedpt_sin(fixedpt fp)
{
    int sign = 1;
    fixedpt sqr, result;
    const fixedpt SK[2] = {
        fixedpt_rconst(7.61e-03),
        fixedpt_rconst(1.6605e-01)
    };
    
    fp %= 2 * FIXEDPT_PI;
    if (fp < 0)
        fp = FIXEDPT_PI * 2 + fp;
    if ((fp > FIXEDPT_HALF_PI) && (fp <= FIXEDPT_PI))
        fp = FIXEDPT_PI - fp;
    else if ((fp > FIXEDPT_PI) && (fp <= (FIXEDPT_PI + FIXEDPT_HALF_PI))) {
        fp = fp - FIXEDPT_PI;
        sign = -1;
    } else if (fp > (FIXEDPT_PI + FIXEDPT_HALF_PI)) {
        fp = (FIXEDPT_PI << 1) - fp;
        sign = -1;
    }
    sqr = fixedpt_mul(fp, fp);
    result = SK[0];
    result = fixedpt_mul(result, sqr);
    result -= SK[1];
    result = fixedpt_mul(result, sqr);
    result += FIXEDPT_ONE;
    result = fixedpt_mul(result, fp);
    return sign * result;
}


/* Returns the cosine of the given fixedpt number */
static inline fixedpt
fixedpt_cos(fixedpt A)
{
    return (fixedpt_sin(FIXEDPT_HALF_PI - A));
}


/* Returns the tangens of the given fixedpt number */
static inline fixedpt
fixedpt_tan(fixedpt A)
{
    return (fixedpt_sin(A), fixedpt_cos(A));
}


/* Returns the value exp(x), i.e. e^x of the given fixedpt number. */
static inline fixedpt
fixedpt_exp(fixedpt fp)
{
    fixedpt xabs, k, z, R, xp;
    const fixedpt LN2 = fixedpt_rconst(0.69314718055994530942);
    const fixedpt LN2_INV = fixedpt_rconst(1.4426950408889634074);
    const fixedpt EXP_P[5] = {
        fixedpt_rconst(1.66666666666666019037e-01),
        fixedpt_rconst(-2.77777777770155933842e-03),
        fixedpt_rconst(6.61375632143793436117e-05),
        fixedpt_rconst(-1.65339022054652515390e-06),
        fixedpt_rconst(4.13813679705723846039e-08),
    };
    
    if (fp == 0)
        return (FIXEDPT_ONE);
    xabs = fixedpt_abs(fp);
    k = fixedpt_mul(xabs, LN2_INV);
    k += FIXEDPT_ONE_HALF;
    k &= ~FIXEDPT_FMASK;
    if (fp < 0)
        k = -k;
    fp -= fixedpt_mul(k, LN2);
    z = fixedpt_mul(fp, fp);
    /* Taylor */
    R = FIXEDPT_TWO +
    fixedpt_mul(z, EXP_P[0] + fixedpt_mul(z, EXP_P[1] +
                                          fixedpt_mul(z, EXP_P[2] + fixedpt_mul(z, EXP_P[3] +
                                                                                fixedpt_mul(z, EXP_P[4])))));
    xp = FIXEDPT_ONE + fixedpt_div(fixedpt_mul(fp, FIXEDPT_TWO), R - fp);
    if (k < 0)
        k = FIXEDPT_ONE >> (-k >> FIXEDPT_FBITS);
    else
        k = FIXEDPT_ONE << (k >> FIXEDPT_FBITS);
    return (fixedpt_mul(k, xp));
}


/* Returns the natural logarithm of the given fixedpt number. */
static inline fixedpt
fixedpt_ln(fixedpt x)
{
    fixedpt log2, xi;
    fixedpt f, s, z, w, R;
    const fixedpt LN2 = fixedpt_rconst(0.69314718055994530942);
    const fixedpt LG[7] = {
        fixedpt_rconst(6.666666666666735130e-01),
        fixedpt_rconst(3.999999999940941908e-01),
        fixedpt_rconst(2.857142874366239149e-01),
        fixedpt_rconst(2.222219843214978396e-01),
        fixedpt_rconst(1.818357216161805012e-01),
        fixedpt_rconst(1.531383769920937332e-01),
        fixedpt_rconst(1.479819860511658591e-01)
    };
    
    if (x < 0)
        return (0);
    if (x == 0)
        return 0xffffffff;
    
    log2 = 0;
    xi = x;
    while (xi > FIXEDPT_TWO) {
        xi >>= 1;
        log2++;
    }
    f = xi - FIXEDPT_ONE;
    s = fixedpt_div(f, FIXEDPT_TWO + f);
    z = fixedpt_mul(s, s);
    w = fixedpt_mul(z, z);
    R = fixedpt_mul(w, LG[1] + fixedpt_mul(w, LG[3]
                                           + fixedpt_mul(w, LG[5]))) + fixedpt_mul(z, LG[0]
                                                                                   + fixedpt_mul(w, LG[2] + fixedpt_mul(w, LG[4]
                                                                                                                        + fixedpt_mul(w, LG[6]))));
    return (fixedpt_mul(LN2, (log2 << FIXEDPT_FBITS)) + f
            - fixedpt_mul(s, f - R));
}


/* Returns the logarithm of the given base of the given fixedpt number */
static inline fixedpt
fixedpt_log(fixedpt x, fixedpt base)
{
    return (fixedpt_div(fixedpt_ln(x), fixedpt_ln(base)));
}


/* Return the power value (n^exp) of the given fixedpt numbers */
static inline fixedpt
fixedpt_pow(fixedpt n, fixedpt exp)
{
    if (exp == 0)
        return (FIXEDPT_ONE);
    if (n < 0)
        return 0;
    return (fixedpt_exp(fixedpt_mul(fixedpt_ln(n), exp)));
}
static inline int64_t fastrnd(int64_t x)
{
    x=x+FIXEDPT_ONE_HALF_64;

    return  (x & FIXEDPT_NEG_ONE);
}
static inline int64_t fastrnd_F22(int64_t x)
{
    x=x+FIXEDPT_ONE_HALF_64_F22;
    
    return  (x & FIXEDPT_NEG_ONE_F22);
}
static inline int32_t fastrnd_F18(int32_t x)
{
    x=x+FIXEDPT_ONE_HALF_32_F18;
    return  (x & FIXEDPT_NEG_ONE_F18);
}


static inline fixedpt
sin_F31(fixedpt x)
{
    fixedpt tempsin;
    tempsin = fixedpt_mul(x,FIXEDPT_INV_2PI);//to get in range 0 to 1
    
    return (arm_sin_q31(tempsin<<3));
}

static inline fixedpt
cos_F31(fixedpt y)
{
    int32_t tempcos;
    tempcos = fixedpt_mul(y,FIXEDPT_INV_2PI);//to get in range 0 to 1
    return (arm_cos_q31(tempcos<<3));

}

static inline fixedpt
tan_F31(fixedpt y)
{
    return (fixedpt_div_F31(sin_F31(y),cos_F31(y)));
}
static inline fixedpt
inv_tan_F28(fixedpt y)
{
    return (fixedpt_div((cos_F31(y)>>3),(sin_F31(y)>>3)));
}

#endif


