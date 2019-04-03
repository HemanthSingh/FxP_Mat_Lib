#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "mult64_with_32.h"
#include<math.h>
#include"fixedinclude.h"

/* This is a pure integer-only test program for fixedptc */

//#define FIXEDPT_WBITS 16
void test_sin();
void test_cos();
void test_atan2();
void test_acos();


void
fixedpt_print(fixedpt A)
{
	char num[40];

	fixedpt_str(A, num, -2);
	puts(num);
}

void test_sin(){
    fixedpt A, B, C;
    puts("");
    puts("sin(0)=");
    fixedpt_print(fixedpt_sin(0));
    A = fixedpt_mul(0,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = A<HALF ? (A + HALF) : (A - HALF);

    puts("A value (0)/2pi=");

    fixedpt_print(A);
    printf("math.h sin(0):%.32f",sin(0));
    printf("arm sin(0):%.32f\n",(float)(arm_sin_q31((A<<3))) / (1 << 31));

    puts("");
    puts("sin(pi/2)=");
    fixedpt_print(fixedpt_sin(FIXEDPT_HALF_PI));
    A = fixedpt_mul(FIXEDPT_HALF_PI,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = A<HALF ? (A + HALF) : (A - HALF);

    puts("A value (pi/2)/2pi=");

    fixedpt_print(A);
    printf("math.h sin(pi/2):%.32f",sin(PI/2.0));
    printf("arm sin(pi/2):%.32f\n",(float)(arm_sin_q31((A<<3))) / (1 << 31));

    puts("");
    puts("sin(pi)=");
    fixedpt_print(fixedpt_sin(FIXEDPT_PI));
    A = fixedpt_mul(FIXEDPT_PI,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = A<HALF ? (A + HALF) : (A - HALF);

    puts("A value pi/2pi=");

    fixedpt_print(A);
    printf("math.h sin(pi):%.32f",sin(PI));
    printf("arm sin(pi):%.32f\n",(float)(arm_sin_q31((A<<3))) / (1 << 31));

    puts("");
    puts("sin(2pi)=");
    fixedpt_print(fixedpt_sin(FIXEDPT_TWO_PI));
    A = fixedpt_mul(FIXEDPT_TWO_PI,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = A<HALF ? (A + HALF) : (A - HALF);
    puts("A value 2pi/2pi=");

    fixedpt_print(A);
    printf("math.h sin(2pi):%.32f",sin(2.0*PI));

    printf("arm sin(2pi):%.32f\n",(float)(arm_sin_q31((A<<3))) / (1 << 31));

    puts("");
    puts("sin(3pi/2)=");
    fixedpt_print(fixedpt_sin(FIXEDPT_3PI2));
    A = fixedpt_mul(FIXEDPT_3PI2,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = A<HALF ? (A + HALF) : (A - HALF);
    puts("A value 3pi/2/2pi=");

    fixedpt_print(A);
    printf("math.h sin(pi):%.32f",sin((3.0*PI)/2));

    printf("arm sin(3pi/2):%.32f\n",(float)(arm_sin_q31((A<<3))) / (1 << 31));
}
void test_cos(){
    fixedpt A, B, C;
    puts("");
    puts("sin(0)=");
    fixedpt_print(fixedpt_cos(0));
    A = fixedpt_mul(0,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = A<HALF ? (A + HALF) : (A - HALF);
    
    puts("A value (0)/2pi=");
    
    fixedpt_print(A);
    printf("math.h cos(0):%.32f",cos(0));
    printf("arm cos(0):%.32f\n",fixedpt_tofloat_F31(arm_cos_q31((A<<3))));
    
   
    puts("");
    puts("cos(0)=");
    fixedpt_print(fixedpt_cos(FIXEDPT_HALF_PI));
    A = fixedpt_mul(fixedpt_rconst(0),FIXEDPT_INV_2PI);//to get in range 0 to 1
    //A = A<HALF ? (A + HALF) : (A - HALF);
    
    puts("A value (pi/2)/2pi=");
    
    fixedpt_print(A);
    printf("math.h cos(pi/2):%.32f",cos(0));
    printf("arm cos(pi/2):%.32f\n",fixedpt_tofloat_F31(arm_cos_q31((A<<3))));
    

    
    puts("");
    puts("cos(pi/4)=");
    fixedpt_print(fixedpt_cos(0.7854));
    A = fixedpt_mul(fixedpt_rconst(0.7854),FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = (A>0 && A<HALF) ? (A + HALF) : (A);

    puts("A value (pi/2)/2pi=");
    
    fixedpt_print(A);
    printf("math.h cos(pi/4):%.32f",cos(PI/4.0));
    printf("arm cos(pi/4):%.32f\n",(float)(arm_cos_q31((A<<3))) / (1 << 31));
    
    
    puts("");
    puts("cos(pi/2)=");
    fixedpt_print(fixedpt_cos(FIXEDPT_HALF_PI));
    A = fixedpt_mul(FIXEDPT_HALF_PI,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = (A>0 && A<HALF) ? (A + HALF) : (A);

    puts("A value (pi/2)/2pi=");
    
    fixedpt_print(A);
    printf("math.h cos(pi/2):%.32f",cos(PI/2.0));
    printf("arm cos(pi/2):%.32f\n",(float)(arm_cos_q31((A<<3))) / (1 << 31));
    
    puts("");
    puts("cos(pi)=");
    fixedpt_print(fixedpt_cos(FIXEDPT_PI));
    A = fixedpt_mul(FIXEDPT_PI,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = (A>0 && A<HALF_1) ? (A + HALF) : (A);

    puts("A value pi/2pi=");
    
    fixedpt_print(A);
    printf("math.h cos(pi):%.32f",cos(PI));
    printf("arm cos(pi):%.32f\n",fixedpt_tofloat_F31(arm_cos_q31((A<<3))));
    
    puts("cos(3pi/2)=");
    fixedpt_print(fixedpt_cos(FIXEDPT_3PI2));
    A = fixedpt_mul(FIXEDPT_3PI2,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = (A>0 && A<HALF_1) ? (A + HALF) : (A);
    puts("A value 3pi/2/2pi=");
    
    fixedpt_print(A);
    printf("math.h cos(3pi/2):%.32f\n",cos((3.0*PI)/2));
    printf("arm cos(3pi/2):%.32f\n",(float)(arm_cos_q31((A<<3))) / (1 << 31));
    
    puts("cos(7pi/4)=");
    fixedpt_print(fixedpt_cos(FIXEDPT_3PI2));
    A = fixedpt_mul(fixedpt_rconst(5.4978),FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = (A>0 && A<HALF_1) ? (A + HALF) : (A);
    puts("A value 7pi/4/2pi=");
    
    fixedpt_print(A);
    printf("math.h cos(7pi/4):%.32f\n",cos((7.0*PI)/4));
    printf("arm cos(7pi/4):%.32f\n",(float)(arm_cos_q31((A<<3))) / (1 << 31));
    
    puts("");
    puts("cos(2pi)=");
    fixedpt_print(fixedpt_cos(FIXEDPT_TWO_PI));
    A = fixedpt_mul(FIXEDPT_TWO_PI,FIXEDPT_INV_2PI);//to get in range 0 to 1
    A = (A>0 && A<HALF_1) ? (A + HALF) : (A);
    puts("A value 2pi/2pi=");
    A= fixedpt_rconst(1);
    fixedpt_print(A);
    printf("math.h cos(2pi):%.32f",cos(2.0*PI));
    
    printf("arm cos(2pi):%.32f\n",(float)(arm_cos_q31((A<<3))) / (1 << 31));
    
    puts("");
   
}
void test_atan2(){
    int32_t x=FIXEDPT_ONE_HALF, y=-FIXEDPT_ONE, t;
    t = CordicAtan2(y, x); // atan2
    printf("math.h Atan2(-1.0,0.5):%.32f\n",atan2(-1,0.5));
    printf("CordicAtan2 Atan2(-1.0,0.5):%.32f\n",fixedpt_tofloat_F31(t));
}
void test_acos(){
    int32_t x, t=-FIXEDPT_ONE_HALF;
    CordicAcos(&x, t); // acos result in uint_32 x
    printf("math.h acos(-0.5):%.32f\n",acos(-0.5));
    printf("CordicAtan2 acos(-0.5):%.32f\n",fixedpt_tofloat_F31(x));
}

int main() {
    
    int64_t A, B, C;
    
    printf("fixedptc library version: %s\n", FIXEDPT_VCSID);
    printf("Using %d-bit precision, %d.%d format\n\n", FIXEDPT_BITS, FIXEDPT_WBITS, FIXEDPT_FBITS);
    
    printf("The most precise number: ");
    fixedpt_print(1);
    printf("The biggest number: ");
    fixedpt_print(0x7fffff00);
   printf("Here are some example numbers:\n");
    
    printf("Random number: ");
    fixedpt_print(fixedpt_rconst(143.125));
    printf("PI: ");
    fixedpt_print(FIXEDPT_PI);
    printf("e: ");
    fixedpt_print(FIXEDPT_E);
    puts("");
    
    A = fixedpt_rconst(2.333);
    B = fixedpt_rconst(-1.6);
    
    fixedpt_print(A);
    puts("+");
    fixedpt_print(B);
    C = fixedpt_add(A, B);
    puts("=");
    fixedpt_print(C);
    puts("");
    puts("-1");
   // C=MUL_NEG_ONE(A);
    fixedpt_print(C);
    fixedpt_print(A);
    puts("*");
    fixedpt_print(B);
    puts("=");
    C = fixedpt_mul(A, B);
    fixedpt_print(C);

    printf("A:%ld\n",(A));

    printf("B:%ld\n",(B));
    printf("B:%.32f\n",fixedpt_tofloat(B));
    printf("product_rnd:%.32f\n",fixedpt_tofloat(C));
    printf("B rep:%.32f\n",fixedpt_tofloat(-268569674));

    puts("");
    
  /*  A = fixedpt_rconst(1);
    B = fixedpt_rconst(4);
    C = fixedpt_div(A, B);
    
    fixedpt_print(A);
    puts("/");
    fixedpt_print(B);
    puts("=");
    fixedpt_print(C);
    
    printf("exp(1)=");
    fixedpt_print(fixedpt_exp(FIXEDPT_ONE));
    
    puts("");
    puts("sqrt(pi)=");
    fixedpt_print(fixedpt_sqrt(FIXEDPT_PI));
    
    puts("");
    puts("sqrt(25)=");
    printf("sqrt(25) as fixedpt:\t%s\n", fixedpt_cstr(fixedpt_sqrt(fixedpt_rconst(7.9)), -2));
    
    test_sin();
    test_cos();
    test_atan2();
    test_acos();*/
    // some matrix functions test
   /* fixedpt A;
    int64_t A_64,B_64,C_64,One_64=4.2950e+09;
    A_64= fixedpt_rconst_64(502.914194);  //8053063695000
    B_64= fixedpt_rconst_64(-16.4);//fixedpt_rconst(0.00005);//4550000
    C_64=fastrnd(B_64);
    //C_64 = mul_alg_F22(A_64,B_64);
    printf("mul_alg(A_64,B_64)%f\n",(((double)(C_64))/(1 << 22)));
    printf("(A_64,B_64)%lld\n",((A_64*B_64)));

    printf("fixedpt_rconst(2.0):%d\n",fixedpt_rconst(-2.005));
    MAT16_int64_t_t x,y,z;
    int i;
    MAT_PREP_DIAG(x, 4, 4,fixedpt_rconst_64(2));

    //MAT4_COLVEC_INIT(y,fixedpt_rconst(1), fixedpt_rconst(-1), fixedpt_rconst(3),fixedpt_rconst(1));
   // MAT_CROSS_PROD(x,y,z);
    for(i=0;i<16;i+=4)
        printf("x[%d]:%.4f\tx[%d]:%.4f\tx[%d]:%.4f\tx[%d]:%.4f\n",i,fixedpt_tofloat_F31(x.comp[i]),i+1,fixedpt_tofloat_F31(x.comp[i+1]),i+2,fixedpt_tofloat_F31(x.comp[i+2]),i+3,fixedpt_tofloat_F31(x.comp[i+3]));
    
    MAT_SCALE_64(x,fixedpt_rconst_64(2),z);
  //  mat16_inv(&x, &z);                                        // invS = S^-1
    //hypot(fixedpt_rconst(1.0),fixedpt_rconst(2.5),k);
    //printf("k:%f\n",fixedpt_tofloat_F31(k));
   
    
   MAT16_INIT(x, 4, 4,
               fixedpt_rconst(0.9990),  fixedpt_rconst( -0.0023), fixedpt_rconst(0.0442),   fixedpt_rconst(-0.0015),
               fixedpt_rconst(0.0023),  fixedpt_rconst(0.9990),   fixedpt_rconst(-0.0015),  fixedpt_rconst(-0.0442),
               fixedpt_rconst(-0.0442), fixedpt_rconst(0.0015),   fixedpt_rconst(0.9990),   fixedpt_rconst(-0.0023),
               fixedpt_rconst(0.0015),  fixedpt_rconst(0.0442),   fixedpt_rconst(0.0023),   fixedpt_rconst(0.9990));
    
    MAT16_EXP(x,16,z);           //#define MAT_SCALED_ADD(scalefacA, A, scalefacB, B, RES)
    //MAT_DIV_COMP(x,y,z);
    for(i=0;i<16;i+=4)
        printf("y[%d]:%.4f\ty[%d]:%.4f\ty[%d]:%.4f\ty[%d]:%.4f\n",i,fixedpt_tofloat_F31(z.comp[i]),i+1,fixedpt_tofloat_F31(z.comp[i+1]),i+2,fixedpt_tofloat_F31(z.comp[i+2]),i+3,fixedpt_tofloat_F31(z.comp[i+3]));*/
    return (0);
}
