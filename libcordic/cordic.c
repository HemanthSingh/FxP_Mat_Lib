/* Copyright (C) 1981-1999 Ken Turkowski.
 *
 * All rights reserved.
 *
 * Warranty Information
 *  Even though I have reviewed this software, I make no warranty
 *  or representation, either express or implied, with respect to this
 *  software, its quality, accuracy, merchantability, or fitness for a
 *  particular purpose.  As a result, this software is provided "as is,"
 *  and you, its user, are assuming the entire risk as to its quality
 *  and accuracy.
 *
 * This code may be used and freely distributed as int32_t as it includes
 * this copyright notice and the above warranty information.
 *
 *
 * 2008-05-18 changed: Daniel Prokesch, adapted for fvs needs:
 *
 *    To calculate atan2, use CordicAtan2.
 *    Arguments have to be Q16.16 (default) or Q4.28 (use define Q28)
 *    fixed-point format.
 *    The result returned also as Q16.16 resp. Q4.28.
 *
 *    To calculate acos of the same angle, use CordicAcos.
 *    This function was newly added by ustilizing atan2 function which
 *    was openly availabe, it uses tricnometric equality between acos and
 *    atan. Look at Wiki link for more formula:https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
 *    Arguments have to be Q16.16 (default) or Q4.28 (use define Q28)
 *    fixed-point format.
 *    The result of static PseudoRotate is returned as fractional value
 *    (Q.30), which is defined solely through the COSCALE constant,
 *    but the CordicUnitVec performs a shift before returning the values so
 *    that they are returned as Q16.16 (SCALE_Q16)
 *
 *    Q.16 has max. precision of 0.0000152587890625
 */

#define Q28
//#define SCALE_Q16
#include <stdio.h>
#include <stdlib.h>
#include "fixedptc.h"
#include "cordic.h"
// precision of COSCALE determines the precision the results are returned for sin/cos (unit vector)
#define COSCALE 0x26DD3B6A // 652032874 = 0.6072529350088813 * 2^30, valid for j>13
//#define COSCALE 0x9B74EDA // 163008218 = 0,6072529350088813 * 2^28, valid for j>13
// MAXITER: the resolution of the arctan table, precision of QUARTER and TAB
// QUARTER: precision of QUARTER and the TAB are for fixed point input and result for atan2
#ifdef Q28
    #define MAXITER 28
    #define QUARTER ((int32_t)(3.141592654 / 2.0 * (1L << 28)))
#else
    #define MAXITER 16
    #define QUARTER ((int32_t)(3.141592654 / 2.0 * (1L << 16)))
#endif


static int32_t arctantab[MAXITER] = {
#ifdef Q28
    // 2^28
    210828714, 124459457, 65760959, 33381290, 16755422, 8385879, 4193963, 2097109, 1048571, 524287, // 10
    262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, // 20
    256, 128, 64, 32, 16, 8, 4, 2
#else
    // 2^16
    51472, 30386, 16055, 8150, 4091, 2047, 1024, 512, 256, 128, // 10
    64, 32, 16, 8, 4, 2
#endif
};


static void PseudoPolarize(int32_t *argx, int32_t *argy);

/* Return a unit vector corresponding to theta.
 * sin and cos are fixed-point fractions.
 */
void CordicAcos(int32_t *cos, int32_t theta)
{
    //*cos = COSCALE;
    int32_t x=FIXEDPT_ONE, y;
   
    y = fixedpt_div( fixedpt_sqrt(FIXEDPT_ONE-fixedpt_mul(theta,theta)), (FIXEDPT_ONE+theta));
    *cos = CordicAtan2(y,x) << 1;
#ifdef SCALE_Q16
    *cos >>= (30-16);
    *sin >>= (30-16);
#endif
}


int32_t CordicAtan2(int32_t y, int32_t x)
{
    if ((x == 0) && (y == 0))
        return(0);

    PseudoPolarize(&x, &y);	/* Convert to polar coordinates */
    return(y);
}


static void
PseudoPolarize(int32_t *argx, int32_t *argy)
{
    register int32_t theta;
    register int32_t yi, i;
    register int32_t x, y;
    register int32_t *arctanptr;

    x = *argx;
    y = *argy;

    /* Get the vector into the right half plane */
    theta = 0;
    if (x < 0) {
        x = -x;
        y = -y;
        theta = 2 * QUARTER;
    }

    if (y > 0)
        theta = - theta;
    
    arctanptr = arctantab;
    for (i = 0; i < MAXITER; i++) {
        if (y < 0) {	/* Rotate positive */
            yi = y + (x >> i);
            x  = x - (y >> i);
            y  = yi;
            theta -= *(arctanptr++);
        }
        else {		/* Rotate negative */
            yi = y - (x >> i);
            x  = x + (y >> i);
            y  = yi;
            theta += *(arctanptr++);
        }
    }

    *argx = x;
    *argy = theta;
}
