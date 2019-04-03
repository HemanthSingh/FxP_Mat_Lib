/*
 * matrix_arithmetic.h
 *
 * Created: 10-2-2012 15:24:10
 *  Author: Leon
 */ 


#ifndef MATRIX_ARITHMETIC_H_
#define MATRIX_ARITHMETIC_H_
#include "fixedptc.h"

static int32_t k[17]={FIXEDPT_ONE,FIXEDPT_ONE,fixedpt_rconst(1.0/2),
    fixedpt_rconst(1.0/6),fixedpt_rconst(1.0/24),
    fixedpt_rconst(1.0/120),fixedpt_rconst(1.0/720),
    fixedpt_rconst(1.0/5040),fixedpt_rconst(1.0/40320),
    fixedpt_rconst(1.0/362880),fixedpt_rconst(1.0/3628800),
    fixedpt_rconst(1.0/39916800), fixedpt_rconst(1.0/479001600),
    fixedpt_rconst(1.0/1932053504), fixedpt_rconst(1.0/1278945280),
    fixedpt_rconst(1.0/2004310016), fixedpt_rconst(1.0/2004189184)
};

////
//// uint8_t
////
typedef struct MAT3_UINT8_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint8_t comp[3];
} MAT3_UINT8_t;

typedef struct MAT4_UINT8_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint8_t comp[4];
} MAT4_UINT8_t;

typedef struct MAT9_UINT8_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint8_t comp[9];
} MAT9_UINT8_t;

typedef struct MAT16_UINT8_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint8_t comp[16];
} MAT16_UINT8_t;

typedef struct MAT25_UINT8_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint8_t comp[25];
} MAT25_UINT8_t;

typedef struct MAT36_UINT8_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint8_t comp[36];
} MAT36_UINT8_t;

typedef struct MAT49_UINT8_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint8_t comp[49];
} MAT49_UINT8_t;


////
//// int16_t
////
typedef struct MAT3_INT16_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int16_t comp[3];
} MAT3_INT16_t;

typedef struct MAT9_INT16_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int16_t comp[9];
} MAT9_INT16_t;


////
//// uint16_t
////
typedef struct MAT3_UINT16_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint16_t comp[3];
} MAT3_UINT16_t;

typedef struct MAT4_UINT16_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint16_t comp[4];
} MAT4_UINT16_t;

typedef struct MAT25_UINT16_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	uint16_t comp[25];
} MAT25_UINT16_t;


////
//// int32_t
////
typedef struct MAT3_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[3];
} MAT3_int32_t_t;

typedef struct MAT4_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[4];
} MAT4_int32_t_t;
//newly added for B_ref
typedef struct MAT2_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[2];
} MAT2_int32_t_t;

typedef struct MAT6_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[6];
} MAT6_int32_t_t;

typedef struct MAT9_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[9];
} MAT9_int32_t_t;

typedef struct MAT16_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[16];
} MAT16_int32_t_t;
typedef struct MAT16_int64_t_struct
{
    uint8_t rows;
    uint8_t cols;
    uint8_t elem;
    int64_t comp[16];
} MAT16_int64_t_t;

typedef struct MAT25_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[25];
} MAT25_int32_t_t;

typedef struct MAT36_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[36];
} MAT36_int32_t_t;

typedef struct MAT49_int32_t_struct
{
	uint8_t rows;
	uint8_t cols;
	uint8_t elem;
	int32_t comp[49];
} MAT49_int32_t_t;


/*
	####### Matrix initializer macro's #######
*/

// Resetting the memory space of a matrix
// totally resetting everything to 0
#define MAT_RESET(A) do { \
	memset(&(A), 0, sizeof(A)); \
} while(0)


// Clear a MAT structure by zero-ing its data fields
// while retaining its rows/cols/elem values
#define MAT_CLEAR(A) do { \
uint8_t i;\
	for(i=0; i < (sizeof((A).comp)/sizeof((A).comp[0])); i++) \
	{ \
		(A).comp[i] = 0; \
	} \
} while(0)

// Prepare a matrix
// Clear it and set the rows/cols
#define MAT_PREP(A, init_rows, init_cols) do { \
	memset(&(A), 0, sizeof(A)); \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
} while(0)

// initialize B using rows and columns and copying appropriate values
// from A; different sized MAT structures can be used together
#define MAT_INIT_FROM(A, B) do { \
	(B).rows = (A).rows; \
	(B).cols = (A).cols; \
	(B).elem = (A).elem; \
	uint8_t i;\
	for(i=0; i < (B).elem; i++) \
	{ \
		(B).comp[i] = (A).comp[i]; \
	} \
} while(0)

// set the diagional entries of a matrix to the value of diag_val
#define MAT_DIAG(A, diag_val) do { \
	uint8_t i;\
	for(i=0; i < (A).rows; i++) \
	{ \
		(A).comp[(i*(A).cols) + i] = (diag_val); \
	} \
} while(0)

// Prepare and set diagonal entries of a matrix
#define MAT_PREP_DIAG(A, init_rows, init_cols, diag_val) do { \
	memset(&(A), 0, sizeof(A)); \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
	uint8_t i;\
	for(i=0; i < (A).rows; i++) \
	{ \
		(A).comp[(i*(A).cols) + i] = (diag_val); \
	} \
} while(0)

// refurbished code originating from Adolfo
// returns a rotation matrix for rotation around X by angle
#define MAT_PREP_ROTX(A, angle) do { \
	int32_t cos_angle = fixedpt_cos(angle); \
	int32_t sin_angle = fixedpt_sin(angle); \
	(A).cols = 3; \
	(A).rows = 3; \
	(A).elem = 9; \
	(A).comp[0] = FIXEDPT_ONE; \
	(A).comp[1] = 0; \
	(A).comp[2] = 0; \
	(A).comp[3] = 0; \
	(A).comp[4] = cos_angle; \
	(A).comp[5] = sin_angle; \
	(A).comp[6] = 0; \
	(A).comp[7] = -sin_angle; \
	(A).comp[8] = cos_angle; \
} while(0)

// refurbished code originating from Adolfo
// returns a rotation matrix for rotation around Y by angle
#define MAT_PREP_ROTY(A, angle) do { \
	int32_t cos_angle = fixedpt_cos(angle); \
	int32_t sin_angle = fixedpt_sin(angle); \
	(A).cols=3; \
	(A).rows=3; \
	(A).elem=9; \
	(A).comp[0] = cos_angle; \
	(A).comp[1] = 0; \
	(A).comp[2] = -sin_angle; \
	(A).comp[3] = 0; \
	(A).comp[4] = FIXEDPT_ONE; \
	(A).comp[5] = 0; \
	(A).comp[6] = sin_angle; \
	(A).comp[7] = 0; \
	(A).comp[8] = cos_angle; \
} while(0)

// refurbished code originating from Adolfo
// returns a rotation matrix for rotation around Z by angle
#define MAT_PREP_ROTZ(A, angle) do { \
	int32_t cos_angle = fixedpt_cos(angle); \
	int32_t sin_angle = fixedpt_sin(angle); \
	(A).cols=3; \
	(A).rows=3; \
	(A).elem=9; \
	(A).comp[0] = cos_angle; \
	(A).comp[1] = sin_angle; \
	(A).comp[2] = 0; \
	(A).comp[3] = -sin_angle; \
	(A).comp[4] = cos_angle; \
	(A).comp[5] = 0; \
	(A).comp[6] = 0; \
	(A).comp[7] = 0; \
	(A).comp[8] = FIXEDPT_ONE; \
} while(0)

// set a subrange of the matrix diagonal to the value of diag_val
// starting at row_start (first row = 0) and filling row_count rows
#define MAT_DIAG_SUB(A, diag_val, row_start, row_count) do { \
	uint8_t i;\
	for( i=(row_start); i < ((row_start) + (row_count)); i++) \
	{ \
		(A).comp[(i*(A).cols) + i] = (diag_val); \
	} \
} while(0)

/* Initialize a MAT3 structure as a (1 x 3) row vector
A = [comp0 comp1 comp2]*/
#define MAT3_ROWVEC_INIT(A, comp0, comp1, comp2) do { \
    memset(&A, 0, sizeof(A));\
	(A).rows = 1; \
	(A).cols = 3; \
	(A).elem = 3; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2);	\
} while(0)

/* Initialize a MAT3 structure as a (3 x 1) column vector
 A = [comp0; comp1; comp2]*/
#define MAT3_COLVEC_INIT(A, comp0, comp1, comp2) do { \
    memset(&A, 0, sizeof(A));\
	(A).rows = 3; \
	(A).cols = 1; \
	(A).elem = 3; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2);	\
} while(0)

// Initialize a MAT3 structure of any type
#define MAT3_INIT(A, init_rows, init_cols, comp0, comp1, comp2) do { \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2);	\
} while(0)


/* Initialize a MAT4 structure as a (1 x 4) row vector
 A = [comp0 comp1 comp2 comp3]*/
#define MAT4_ROWVEC_INIT(A, comp0, comp1, comp2, comp3) do { \
    memset(&A, 0, sizeof(A));\
	(A).rows = 1; \
	(A).cols = 4; \
	(A).elem = 4; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3);	\
} while(0)

/*
 Initialize a MAT4 structure as a (4 x 1) column vector
 A = [comp0; comp1; comp2; comp3]
*/
#define MAT4_COLVEC_INIT(A, comp0, comp1, comp2, comp3) do { \
    memset(&A, 0, sizeof(A));\
	(A).rows = 4; \
	(A).cols = 1; \
	(A).elem = 4; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3);	\
} while(0)

//newly added for B_ref
#define MAT2_INIT(A, comp0, comp1) do { \
	(A).rows = 2; \
	(A).cols = 1; \
	(A).elem = 2; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1);	\
} while(0)
// Initialize a MAT6 structure of any type
#define MAT6_INIT(A,comp0, comp1, comp2, comp3, comp4, comp5) do { \
	(A).rows = 3; \
	(A).cols = 2; \
	(A).elem = 6; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3), (A).comp[4] = (comp4), (A).comp[5] = (comp5); \
} while(0)


// Initialize a MAT4 structure of any type
#define MAT4_INIT(A, init_rows, init_cols, comp0, comp1, comp2, comp3) do { \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3);	\
} while(0)

// Initialize a MAT9 structure of any type
#define MAT9_INIT(A, init_rows, init_cols, comp0, comp1, comp2, comp3, comp4, comp5, comp6, comp7, comp8) do { \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3), (A).comp[4] = (comp4), (A).comp[5] = (comp5), \
	(A).comp[6] = (comp6), (A).comp[7] = (comp7), (A).comp[8] = (comp8); \
} while(0)

// Initialize a MAT16 structure of any type
#define MAT16_INIT(A, init_rows, init_cols, comp0, comp1, comp2, comp3, comp4, comp5, comp6, comp7, comp8, comp9, comp10, comp11, comp12, comp13, comp14, comp15) do { \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3), (A).comp[4] = (comp4), (A).comp[5] = (comp5), \
	(A).comp[6] = (comp6), (A).comp[7] = (comp7), (A).comp[8] = (comp8), (A).comp[9] = (comp9), (A).comp[10] = (comp10), (A).comp[11] = (comp11), \
	(A).comp[12] = (comp12), (A).comp[13] = (comp13), (A).comp[14] = (comp14), (A).comp[15] = (comp15); \
} while(0)

// Initialize a MAT25 structure of any type
#define MAT25_INIT(A, init_rows, init_cols, comp0, comp1, comp2, comp3, comp4, comp5, comp6, comp7, comp8, comp9, comp10, comp11, comp12, comp13, comp14, comp15, comp16, comp17, comp18, comp19, comp20, comp21, comp22, comp23, comp24) do { \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3), (A).comp[4] = (comp4), (A).comp[5] = (comp5), \
	(A).comp[6] = (comp6), (A).comp[7] = (comp7), (A).comp[8] = (comp8), (A).comp[9] = (comp9), (A).comp[10] = (comp10), (A).comp[11] = (comp11), \
	(A).comp[12] = (comp12), (A).comp[13] = (comp13), (A).comp[14] = (comp14), (A).comp[15] = (comp15), (A).comp[16] = (comp16), (A).comp[17] = (comp17), \
	(A).comp[18] = (comp18), (A).comp[19] = (comp19), (A).comp[20] = (comp20), (A).comp[21] = (comp21), (A).comp[22] = (comp22), (A).comp[23] = (comp23), \
	(A).comp[24] = (comp24); \
} while(0)

#define MAT49_INIT(A, init_rows, init_cols, comp0, comp1, comp2, comp3, comp4, comp5, comp6, comp7, comp8, comp9, comp10, comp11, comp12, comp13, comp14, comp15, comp16, comp17, comp18, comp19, comp20, comp21, comp22, comp23, comp24, comp25, comp26, comp27, comp28, comp29, comp30, comp31, comp32, comp33, comp34, comp35, comp36, comp37, comp38, comp39, comp40, comp41, comp42, comp43, comp44, comp45, comp46, comp47, comp48) do { \
	(A).rows = (init_rows); \
	(A).cols = (init_cols); \
	(A).elem = (A).rows * (A).cols; \
	(A).comp[0] = (comp0), (A).comp[1] = (comp1), (A).comp[2] = (comp2), (A).comp[3] = (comp3), (A).comp[4] = (comp4), (A).comp[5] = (comp5), \
	(A).comp[6] = (comp6), (A).comp[7] = (comp7), (A).comp[8] = (comp8), (A).comp[9] = (comp9), (A).comp[10] = (comp10), (A).comp[11] = (comp11), \
	(A).comp[12] = (comp12), (A).comp[13] = (comp13), (A).comp[14] = (comp14), (A).comp[15] = (comp15), (A).comp[16] = (comp16), (A).comp[17] = (comp17), \
	(A).comp[18] = (comp18), (A).comp[19] = (comp19), (A).comp[20] = (comp20), (A).comp[21] = (comp21), (A).comp[22] = (comp22), (A).comp[23] = (comp23), \
	(A).comp[24] = (comp24), (A).comp[25] = (comp25), (A).comp[26] = (comp26), (A).comp[27] = (comp27), (A).comp[28] = (comp28), (A).comp[29] = (comp29), \
	(A).comp[30] = (comp30), (A).comp[31] = (comp31), (A).comp[32] = (comp32), (A).comp[33] = (comp33), (A).comp[34] = (comp34), (A).comp[35] = (comp35), \
	(A).comp[36] = (comp36), (A).comp[37] = (comp37), (A).comp[38] = (comp38), (A).comp[39] = (comp39), (A).comp[40] = (comp40), (A).comp[41] = (comp41), \
	(A).comp[42] = (comp42), (A).comp[43] = (comp43), (A).comp[44] = (comp44), (A).comp[45] = (comp45), (A).comp[46] = (comp46), (A).comp[47] = (comp47), \
	(A).comp[48] = (comp48); \
} while(0)

/*
	####### Matrix arithmetic #######
*/

/*
	Add matrix components

	RES = A + B
 / Overflow can only happen if sign of a == sign of b, and then
 // it causes sign of sum != sign of a.
 for(ll=0; ll < (RES).elem; ll++) {\
 if (!(((A).comp[ll] ^ (B).comp[ll]) & 0x80000000) && (((A).comp[ll] ^ (RES).comp[ll]) & 0x80000000)){\
 printf("W! OVERFLOW MAT_ADD\n");\
 exit(-1);\
 }\
 }\

*/
#define MAT_ADD(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t j;\
	for(j=0; j < (RES).elem; j++) \
	{ \
		(RES).comp[j] = (A).comp[j] + (B).comp[j]; \
	} \
} while(0)

/*
	Subtract matrix components

	RES = A - B
 // Overflow can only happen if sign of a != sign of b, and then
 // it causes sign of diff != sign of a.
 for(ll=0; ll < (RES).elem; ll++) {\
 if ((((A).comp[ll] ^ (B).comp[ll]) & 0x80000000) && (((A).comp[ll] ^ (RES).comp[ll]) & 0x80000000)){\
 printf("W! OVERFLOW MAT_SUB\n");\
 exit(-1);\
 }\
 }\
*/
#define MAT_SUB(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t j;\
	for(j=0; j < (RES).elem; j++) \
	{ \
		(RES).comp[j] = (A).comp[j] - (B).comp[j]; \
	} \
} while(0)

/*
	Add matrix components with scaling

	RES = scalefacA * A + scalefacB * B
*/
#define MAT_SCALED_ADD(scalefacA, A, scalefacB, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t j;\
	for(j=0; j < (RES).elem; j++) \
	{ \
		(RES).comp[j] = fixedpt_mul((scalefacA), (A).comp[j]) + fixedpt_mul((scalefacB) , (B).comp[j]); \
	} \
} while(0)

/*
	Subtract matrix components with scaling

	RES = scalefacA * A + scalefacB * B
*/
#define MAT_SCALED_SUB(scalefacA, A, scalefacB, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t j;\
	for(j=0; j < (RES).elem; j++) \
	{ \
		(RES).comp[j] = fixedpt_mul((scalefacA) , (A).comp[j]) - fixedpt_mul((scalefacB) , (B).comp[j]); \
	} \
} while(0)

/*
	Multiply matrices using standard matrix multiplication
	
	RES_ij = sum_k_1_to_Acols(A_ik * B_kj)
	
	Example:
	A = [A1 A2; A3 A4]; B = [B1 B2; B3 B4]
	MAT_MUL(A, B, RES)
	RES = [(A1*B1+A2*B3) (A1*B2+A2*B4); (A3*B1+A4*B3) (A3*B2+A4*B4)]

	WARNING: A or B cannot be RES e.g. MAT_MUL(A, B, A) will fail!
*/
#define MAT_MUL(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (B).cols; \
	(RES).elem = (RES).rows * (RES).cols; \
	uint8_t i;\
	for(i = 0; i < (RES).rows; i++) \
	{ \
		uint8_t j;\
		for(j = 0; j < (RES).cols; j++) \
		{ \
			(RES).comp[(i*((RES).cols))+j] = 0; \
			uint8_t k;\
			for(k = 0; k < (A).cols; k++) \
			{ \
				(RES).comp[(i*((RES).cols))+j] += fixedpt_mul((A).comp[(i*((A).cols))+k] , (B).comp[(k*((B).cols))+j]); \
			} \
		} \
	} \
} while(0)

/*
	Multiply matrices using standard matrix multiplication
	while first transposing the A matrix
	
	RES_ij = sum_k_1_to_Arows(A_ki * B_kj)

	WARNING: A or B cannot be RES e.g. MAT_MUL(A, B, A) will fail!
*/
#define MAT_MUL_LTP(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (B).rows; \
	(RES).elem = (RES).rows * (RES).cols; \
	uint8_t i;\
	for(i = 0; i < (RES).rows; i++) \
	{ \
		uint8_t j;\
		for(j = 0; j < (RES).cols; j++) \
		{ \
			(RES).comp[(i*((RES).cols))+j] = 0; \
			uint8_t k;\
			for(k = 0; k < (A).rows; k++) \
			{ \
				(RES).comp[(i*((RES).cols))+j] += fixedpt_mul((A).comp[(i*((A).cols))+k] , (B).comp[(j*((B).cols))+k]); \
			} \
		} \
	} \
} while(0)

/*
	Multiply matrices using standard matrix multiplication
	while first transposing the B matrix
	
	RES_ij = sum_k_1_to_Acols(A_ik * B_jk)

	WARNING: A or B cannot be RES e.g. MAT_MUL(A, B, A) will fail!
*/
#define MAT_MUL_RTP(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (B).rows; \
	(RES).elem = (RES).rows * (RES).cols; \
	uint8_t i;\
	for(i = 0; i < (RES).rows; i++) \
	{ \
		uint8_t j;\
		for( j = 0; j < (RES).cols; j++) \
		{ \
			(RES).comp[(i*((RES).cols))+j] = 0; \
			uint8_t k;\
			for( k = 0; k < (A).cols; k++) \
			{ \
				(RES).comp[(i*((RES).cols))+j] += fixedpt_mul((A).comp[(i*((A).cols))+k] , (B).comp[(j*((B).cols))+k]); \
			} \
		} \
	} \
} while(0)

// Matrix exponential of a square matrix up to 4x4 in size
// using 'terms' amount of terms
// original math: Taylor expansion
// RES = inf_sum( (1/(k!)) * A^k )
// zeroth term = I; first term = A, sec_term = (1/2) * A^2
//for(j=0;j<16;j+=4)
//printf("y[%d]:%.4f\ty[%d]:%.4f\ty[%d]:%.4f\ty[%d]:%.4f\n",j,fixedpt_tofloat(RES.comp[j]),j+1,fixedpt_tofloat(RES.comp[j+1]),j+2,fixedpt_tofloat(RES.comp[j+2]),j+3,fixedpt_tofloat(RES.comp[j+3]));
#define MAT16_EXP(A, terms, RES) do { \
	MAT16_int32_t_t temp1, temp2; \
	MAT_PREP_DIAG((RES), (A).rows, (A).cols, FIXEDPT_ONE); \
	MAT_PREP_DIAG(temp1, (A).rows, (A).cols, FIXEDPT_ONE); \
	uint8_t i,j;\
	for (i=1; i <= (terms); i++){	\
		MAT_MUL((A), temp1, temp2); \
		temp1 = temp2; \
		MAT_SCALE(temp2, (int32_t)k[i], temp2); \
        MAT_ADD((RES), temp2, (RES)); \
	}	\
} while(0)

// Matrix exponential of a square matrix up to 7x7 in size
// using 'terms' amount of terms
// original math: Taylor expansion
// RES = inf_sum( (1/(k!)) * A^k )
// zeroth term = I; first term = A, sec_term = (1/2) * A^2
#define MAT49_EXP(A, terms, RES) do { \
    MAT49_int32_t_t temp1, temp2, temp3; \
	MAT_PREP_DIAG((RES), (A).rows, (A).cols, FIXEDPT_ONE); \
	MAT_PREP_DIAG(temp1, (A).rows, (A).cols, FIXEDPT_ONE); \
	uint8_t i;\
	for (i=1; i <= (terms); i++){	\
		MAT_MUL((A), temp1, temp2); \
		temp1 = temp2; \
        MAT_SCALE(temp2, (int32_t)k[i], temp2); \
		MAT_ADD((RES), temp2, (RES)); \
	}	\
} while(0)

/*
	Multiply matrices using per component multiplication
	
	RES_ij = A_ij * B_ij
	
	Example:
	A = [A1 A2; A3 A4]; B = [B1 B2; B3 B4]
	MAT_MUL_COMP(A, B, RES)
	RES = [(A1*B1) (A2*B2); (A3*B3) (A4*B4)]
*/
#define MAT_MUL_COMP(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t i;\
	for(i=0; i < (RES).elem; i++) \
	{ \
		(RES).comp[i] = fixedpt_mul((A).comp[i] , (B).comp[i]); \
	} \
} while(0)

/*
	Divide matrices using per component division
	
	RES_ij = A_ij * B_ij
	
	Example:
	A = [A1 A2; A3 A4]; B = [B1 B2; B3 B4]
	MAT_MUL_COMP(A, B, RES)
	RES = [(A1/B1) (A2/B2); (A3/B3) (A4/B4)]
*/
#define MAT_DIV_COMP(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t i;\
	for(i=0; i < (RES).elem; i++) \
	{ \
		(RES).comp[i] = fixedpt_div((A).comp[i] , (B).comp[i]); \
	} \
} while(0)

// Create a unit vector from vector A
#define MAT_VECTOR_NORMALIZE(A, RES) do { \
	int32_t len; \
	MAT_VECTOR_LENGTH(A, len); \
	MAT_SCALE_INV(A, len, RES); \
} while(0)

/*C = hypot(A,B) returns the result of the following equation, computed to avoid underflow and overflow:

C = fixedpt_sqrt(abs(A).^2 + abs(B).^2)
*/
// Create a unit vector from vector A
#define hypot(A,B, RES) do { \
	(RES) = fixedpt_sqrt( fixedpt_mul((abs(A)) , (abs(A))) + fixedpt_mul((abs(B)) , (abs(B))) );\
} while(0)

/*
	Determine vector length
	
	scalar = fixedpt_sqrt((A1*A1) + (A2*A2) + (A3*A3) + (A4*A4))
		   = fixedpt_sqrt(A dot A)
*/
#define MAT_VECTOR_LENGTH(A, scalar) do { \
	MAT_DOT_PROD((A), (A), (scalar)); \
	(scalar) = fixedpt_sqrt(scalar); \
} while(0)

// Immediate variant of the VECTOR_LENGTH macro
// returning the result as return value instead of output parameter
#define MATI_VECTOR_LENGTH(A)	fixedpt_sqrt(MATI_DOT_PROD((A), (A)))

/*
	Dot (or scalar) product of matrices
	
	scalar = sum(A_ij * B_ij)
	
	Example:
	A = [A1 A2; A3 A4]; B = [B1 B2; B3 B4]
	MAT_MUL(A, B, scalar)
	scalar = (A1*B1) + (A2*B2) + (A3*B3) + (A4*B4)
*/
#define MAT_DOT_PROD(A, B, scalar) do {	\
	(scalar) = 0; \
	uint8_t i;\
	for(i = 0; i < (A).elem; i++) \
	{ \
		(scalar) += fixedpt_mul( ((A).comp[i]) , ((B).comp[i]) ); \
	} \
} while(0)

// Immediate variant of the DOT_PROD macro
// returning the result as return value instead of output parameter
#define MATI_DOT_PROD(A, B)			\
({									\
	int32_t __result;				\
	MAT_DOT_PROD(A, B, __result);	\
	__result;						\
})

/*
	Cross (or vector) product of two row or two column vectors
	
	Example:
	A = [A1 A2 A3 A4]; B = [B1 B2 B3 B4]
	MAT_CROSS_PROD(A, B, RES)
	RES = [(A2*B3-B2*A3)  (A3*B4-A4*B3) (A4*B1-A1*B4) (A1*B2-A2*B1)]
*/
#define MAT_CROSS_PROD(A, B, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t i;\
	for(i = 0; i < ((RES).elem - 2); i++) \
	{ \
		(RES).comp[i] = fixedpt_mul(((A).comp[i+1]) , ((B).comp[i+2])) - fixedpt_mul(((A).comp[i+2]) , ((B).comp[i+1])); \
	} \
	(RES).comp[(RES).elem-2] = fixedpt_mul(((A).comp[(RES).elem-1]) , ((B).comp[0])) - fixedpt_mul(((A).comp[0]) , ((B).comp[(RES).elem - 1])); \
	(RES).comp[(RES).elem-1] = fixedpt_mul(((A).comp[0]) , ((B).comp[1])) - fixedpt_mul(((A).comp[1]) , ((B).comp[0])); \
} while(0)

/*
	Transpose matrix
	
	RES_ji = A_ij
	
	WARNING: A cannot be RES. e.g. MAT_TRANSP(A, A) will fail!
*/
#define MAT_TRANSP(A, RES) do {	\
    MAT_RESET(RES);\
	(RES).cols = (A).rows; \
	(RES).rows = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t i;\
	for(i=0; i < (A).rows; i++) \
	{ \
		uint8_t j;\
		for(j=0; j < (A).cols; j++) \
		{ \
			(RES).comp[j*(RES).cols+i] = (A).comp[(i*((A).cols))+j]; \
		} \
	} \
} while(0)

/*
	Inverse matrix components
	
	RES_ij = inv_val / A_ij

	usually inv_val = 1
*/
#define MAT_INV_COMP(A, inv_val, RES) do {	\
    MAT_RESET(RES);\
	(RES).cols = (A).rows; \
	(RES).rows = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t l;\
	for(l=0; l < (A).elem; l++) \
	{ \
		(RES).comp[l] = fixedpt_div((inv_val) , ((A).comp[l])); \
	} \
} while(0)

/*
	Scale matrix components using scale_fac
	
	RES_ij = A_ij * scale_fac
*/
#define MAT_SCALE(A, scale_fac, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t ll;\
	for(ll=0; ll < (A).elem; ll++) \
	{ \
		(RES).comp[ll] = fixedpt_mul(((A).comp[ll]) , (scale_fac)); \
	} \
} while(0)
/*
 64 bit Scale matrix components using scale_fac
 
 RES_ij = A_ij * scale_fac
 */
#define MAT_SCALE_64(A, scale_fac, RES) do {    \
MAT_RESET(RES);\
(RES).rows = (A).rows; \
(RES).cols = (A).cols; \
(RES).elem = (A).elem; \
uint8_t ll;\
for(ll=0; ll < (A).elem; ll++) \
{ \
(RES).comp[ll] = mul_alg(((A).comp[ll]) , (scale_fac)); \
} \
} while(0)

/*
	Scale matrix components using inverse of scale_fac_to_inv
	
	RES_ij = A_ij / scale_fac_to_inv
 printf("scale_fac_to_inv %f \n",fixedpt_tofloat(scale_fac_to_inv));\
*/
#define MAT_SCALE_INV(A, scale_fac_to_inv, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t ll;\
    int32_t scale_fac_inv = fixedpt_div(FIXEDPT_ONE, scale_fac_to_inv);\
	for(ll=0; ll < (A).elem; ll++) \
	{ \
    (RES).comp[ll] = fixedpt_mul( ((A).comp[ll]), (scale_fac_inv)); \
	} \
} while(0)


/*
	Take absolute of components
	
	RES_ij = abs(A_ij)
*/
#define MAT_ABS(A, RES) do {	\
    MAT_RESET(RES);\
	(RES).rows = (A).rows; \
	(RES).cols = (A).cols; \
	(RES).elem = (A).elem; \
	uint8_t i;\
	for(i=0; i < (A).elem; i++) \
	{ \
		(RES).comp[i] = abs((A).comp[i]); \
	} \
} while(0)

/*
	Check if value is between (inclusive) boundary values

	only if all B_MIN_ij <= A_ij <= B_MIN_ij then bool_is_between = true
*/
#define MAT_BETWEEN(A, B_MIN, B_MAX, bool_is_between) do {	\
	(bool_is_between) = true; \
	uint8_t i;\
	for(i=0; i < (A).elem; i++) \
	{ \
		if( ((A).comp[i] < (B_MIN).comp[i]) || ((A).comp[i] > (B_MAX).comp[i]) ) { \
			(bool_is_between) = false; \
			break; \
		} \
	} \
} while(0)


/*
	Replicate matrix by tiling TEMP tile_rows x tile_cols into RES
	
	TEMPL = [1 2; 3 4]; tile_rows = 3; tile_cols = 3;
	RES = [1 2 1 2 1 2; 3 4 3 4 3 4; 1 2 1 2 1 2; 3 4 3 4 3 4; 1 2 1 2 1 2; 3 4 3 4 3 4]; (6x6)
	

#define MAT_REPLI(TEMPL, tile_rows, tile_cols, RES) do {	\
	RES.rows = TEMPL.rows * (tile_rows); \
	RES.cols = TEMPL.cols * (tile_cols); \
	RES.elem = RES.rows * RES.cols; \
	for(uint8_t k=0; k < (tile_rows); k++) \
	{ \
		for(uint8_t l=0; l < (tile_cols); l++) \
		{ \
			for(uint8_t i=0; i < A.rows; i++) \
			{ \
				for(uint8_t j=0; j < A.cols; j++) \
				{ \
					RES.comp[]
				} \			
			} \

		} \			
	} \
} while(0)
*/
	
// [1 2 3] -> [1 2 3; 1 2 3; 1 2 3]
#define MAT_EXPAND_ROW(A, tile_rows) do {	\
	uint8_t idx_offset; \
	uint8_t k;\
	for(k=1; k < (tile_rows); k++) \
	{ \
		idx_offset = k * (A).elem; \
		uint8_t i;\
		for(i=0; i < (A).elem; i++) \
		{ \
			(A).comp[idx_offset + i] = (A).comp[i]; \
		} \
	} \
	(A).rows = (A).rows * (tile_rows); \
	(A).elem = (A).rows * (A).cols; \
} while(0)

#define MAT_EXPAND_COL(A, tile_cols) do {	\
	uint8_t idx_offset; \
	uint8_t i;\
	for(i=(A).rows; i > 0 ; i--) \
	{ \
		uint8_t l;\
		for(l=(tile_cols); l > 0 ; l--) \
		{ \
			idx_offset = ((i-1)*(tile_cols) + (l-1)) * (A).cols; \
			uint8_t j;\
			for(j=(A).cols; j > 0 ; j--) \
			{ \
				(A).comp[idx_offset + (j-1)] = (A).comp[((i-1)*((A).cols))+(j-1)]; \
			} \
		} \
	} \
	(A).cols *= (tile_cols); \
	(A).elem = (A).rows * (A).cols; \
} while(0)



/* ADOLFOS FUNCTIONS */
/*
#define VECTOR_INIT_0(A) do {\
	A.rows=3;\
	A.cols=1; \
	A.elem=3;\
	A.comp[0]=0; \
	A.comp[1]=0; \
	A.comp[2]=0; \
} while(0)

#define VECTOR_INIT(A, comp0, comp1, comp2) do { \
	A.rows = 3; \
	A.cols = 1; \
	A.elem = 3; \
	A.comp[0] = (comp0), A.comp[1] = (comp1), A.comp[2] = (comp2);	\
} while(0)

// Obtains the [Ax] matrix from A, useful for cross product
#define CROSS_MATRIX(A,Ax) do {\
	Ax.rows = 3; \
	Ax.cols = 3; \
	Ax.elem=9;\
	Ax.comp[0]=0;\
	Ax.comp[4]=0;\
	Ax.comp[8]=0; \
	Ax.comp[1]=-A.comp[2];\
	Ax.comp[2]=A.comp[1];\
	Ax.comp[3]=A.comp[2];\
	Ax.comp[5]=-A.comp[0];\
	Ax.comp[6]=-A.comp[1];\
	Ax.comp[7]=A.comp[0];\
} while(0)

#define CROSS(A,B,cx) do {\
	MAT9_int32_t_t Ax;\
	CROSS_MATRIX(A,Ax);\
	MAT_MUL(Ax,B,cx);\
} while(0)


// still problems with fixedpt_sqrt
#define ABS_VEC( A , res) do {\
	int ix;\
	for (ix=0; ix<A.elem ; ix++) \
		{\
		res=res+A.comp[ix]*A.comp[ix];\
		}\
} while(0)


// square of the absolute value of a vector
#define ABS_VECSQ( A , res) do {\
	int ix;\
	for (ix=0; ix<A.elem ; ix++) \
		{\
		res=res+A.comp[ix]*A.comp[ix];\
		}\
} while(0)

#define VEC_MAX( A , max) do {\
	if ( absd(A.comp[0]) > absd(A.comp[1]) ) \
		{\
		if ( absd(A.comp[0]) > absd(A.comp[2]) ) \
			max=(A.comp[0]);\
		else\
			max=(A.comp[2]);\
		}\
	else\
		{\
		if ( absd(A.comp[1]) > absd(A.comp[2]) )\
			max=(A.comp[1]);\
		else \
			max=(A.comp[2]);\
		}\
} while(0)

#define VEC_MIN( A , min) do {\
	if ( absd(A.comp[0]) < absd(A.comp[1]) ) \
		{\
		if ( absd(A.comp[0]) < absd(A.comp[2]) ) \
			min=(A.comp[0]);\
		else\
			min=(A.comp[2]);\
		}\
	else\
		{\
		if ( absd(A.comp[1]) < absd(A.comp[2]) )\
			min=(A.comp[1]);\
		else \
			min=(A.comp[2]);\
		}\
} while(0)



// Determines the position of the hightest, middle and lower value. Higher is written in position 1

#define VEC_POSITIONS( A , positions) do {\
	int evaluator=0;\
	if ( absd(A.comp[0]) > absd(A.comp[1]) ) \
		{\
		evaluator=evaluator+4;\
		}\
	if ( absd(A.comp[0]) > absd(A.comp[2]) ) \
		{\
		evaluator=evaluator+2;\
		}\
	if ( absd(A.comp[1]) > absd(A.comp[2]) ) \
		{\
		evaluator=evaluator+1;\
		}\
	switch (evaluator)\
	{\
		case 0:\
		{\
			positions[0]=2;\
			positions[1]=1;\
			positions[2]=0;\
			break;\
		}\
		case 1:\
		{\
			positions[0]=1;\
			positions[1]=2;\
			positions[2]=0;\
			break;\
		}\
		case 3:\
		{\
			positions[0]=1;\
			positions[1]=0;\
			positions[2]=2;\
			break;\
		}\
		case 4:\
		{\
			positions[0]=2;\
			positions[1]=0;\
			positions[2]=1;\
			break;\
		}\
		case 6:\
		{\
			positions[0]=0;\
			positions[1]=2;\
			positions[2]=1;\
			break;\
		}\
		case 7:\
		{\
			positions[0]=0;\
			positions[1]=1;\
			positions[2]=2;\
			break;\
		}\
	}\
} while(0)

#define CREATE_MAVL( m_avl ) do {\
	int ix;\
	m_avl.cols=8;\
	m_avl.rows=3;\
	m_avl.elem=24;\
	for (ix=0;ix<23;ix++)\
		m_avl.comp[ix]=m_max;\
	m_avl.comp[4]=-m_max;\
	m_avl.comp[5]=-m_max;\
	m_avl.comp[6]=-m_max;\
	m_avl.comp[7]=-m_max;\
	m_avl.comp[10]=-m_max;\
	m_avl.comp[11]=-m_max;\
	m_avl.comp[14]=-m_max;\
	m_avl.comp[15]=-m_max;\
	m_avl.comp[17]=-m_max;\
	m_avl.comp[19]=-m_max;\
	m_avl.comp[21]=-m_max;\
	m_avl.comp[23]=-m_max;\
	} while(0)
*/

/*
	####### function declarations #######
*/

// take the matrix inverse of a 16 element matrix
// using LU factorization
void mat16_inv(MAT16_int32_t_t *Matrix, MAT16_int32_t_t *Inverse);

#if DEBUG_UNIT_TEST

bool mat_unit_test(void);

#endif // DEBUG_UNIT_TEST

#endif /* MATRIX_ARITHMETIC_H_ */
