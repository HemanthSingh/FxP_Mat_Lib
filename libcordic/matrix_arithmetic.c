/*
 * matrix_arithmetic.c
 *
 * Created: 10-2-2012 15:23:53
 *  Author: Leon
 */ 

#include <stdint.h>
#include <stdbool.h>
#include "fixedptc.h"
#include "matrix_arithmetic.h"



/*
 [1; 2; 3] -> [1 1 1; 2 2 2; 3 3 3]


[1 2; 3 4; 5 6] (3x2) -> [1 2 1 2; 3 4 3 4; 5 6 5 6] (3x4)

A.rows=3, A.cols=2, tile_cols=2;
i=2, l=1, idx_offset=(2*2+1)*2=10, j=1, A.comp[11] = A.comp[5]
i=2, l=1, idx_offset=(2*2+1)*2=10, j=0, A.comp[10] = A.comp[4]
i=2, l=0, idx_offset=(2*2+0)*2=8, j=1, A.comp[9] = A.comp[5]
i=2, l=0, idx_offset=(2*2+0)*2=8, j=0, A.comp[8] = A.comp[4]

i=1, l=1, idx_offset=(1*2+1)*2=6, j=1, A.comp[7] = A.comp[3]
i=1, l=1, idx_offset=(1*2+1)*2=6, j=0, A.comp[6] = A.comp[2]
i=1, l=0, idx_offset=(1*2+0)*2=4, j=1, A.comp[5] = A.comp[3]
i=1, l=0, idx_offset=(1*2+0)*2=4, j=0, A.comp[4] = A.comp[2]

i=0, l=1, idx_offset=(0*2+1)*2=2, j=1, A.comp[3] = A.comp[1]
i=0, l=1, idx_offset=(0*2+1)*2=2, j=0, A.comp[2] = A.comp[0]
i=0, l=0, idx_offset=(0*2+0)*2=0, j=1, A.comp[1] = A.comp[1]
i=0, l=0, idx_offset=(0*2+0)*2=0, j=0, A.comp[0] = A.comp[0]

*/
/*
void test_func(MAT9_UINT8_t A, uint8_t tile_cols)
{	
	do {
		uint8_t idx_offset;
		for(uint8_t i=(A.rows); i > 0 ; i--)
		{
			for(uint8_t l=(tile_cols); l > 0 ; l--)
			{
				idx_offset = ((i-1)*(tile_cols) + (l-1)) * A.cols;
				for(uint8_t j=A.cols; j > 0 ; j--)
				{
					A.comp[idx_offset + (j-1)] = A.comp[((i-1)*(A.cols))+(j-1)];
				}
			}
		}
		A.cols *= (tile_cols);
		A.elem = A.rows * A.cols;
	} while(0);

	uint8_t b = 0;
}
*/

// Original code: Adolfo
int __mat_locate_position(int ix, int jx)
{
	int position;
	position= ix*4+jx-5;
	return position;
}

// Original code: Adolfo
void __mat16_lu_decomp(MAT16_int32_t_t *matrix, MAT16_int32_t_t *L, MAT16_int32_t_t *U )
{
	int ix=1; 
	int jx=1; 
	int n=4;
	int k=1;
	int component;
	int aux;
	int aux2;
	int aux3; 
	int aux4; 
	
	/* By default, all ellements will start as zero */
	MAT16_INIT((*L), 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	MAT16_INIT((*U), 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	for (ix=1; ix <=4; ix++) 
		{
		component=5*ix-5;
		(*L).comp[component]=FIXEDPT_ONE;
		}		
	
	
	while (jx<=n)
		{
		ix=1;
	
	
		while (ix<=jx)
			{
			component=__mat_locate_position(ix,jx);
			(*U).comp[component]=(*matrix).comp[component];
		
			if (ix!=1) 
				{
				for (k=1; k<ix; k++)
					{
					aux=__mat_locate_position(ix,k);
					aux2=__mat_locate_position(k,jx);
					(*U).comp[component]=(*U).comp[component]-(*L).comp[aux]*(*U).comp[aux2];
					}				
			
				}	
			ix=ix+1;
			}		
		while (ix<=n)
			{
			aux=__mat_locate_position(ix,jx);
			aux2=__mat_locate_position(jx,jx);
			(*L).comp[aux]=fixedpt_div(FIXEDPT_ONE,(*U).comp[aux2] * (*matrix).comp[aux]);
			
			if (jx!=1)
				{
				
				for (k=1; k<jx; k++)
					{
					aux=__mat_locate_position(ix,jx);
					aux2=__mat_locate_position(jx,jx);
					aux3=__mat_locate_position(ix,k);
					aux4=__mat_locate_position(k,jx);
					(*L).comp[aux] =	(*L).comp[aux] - (fixedpt_mul(fixedpt_mul(fixedpt_div(FIXEDPT_ONE , (*U).comp[aux2]) , 	(*L).comp[aux3]) , (*U).comp[aux4]));
					}
				
				}
			
			
			ix=ix+1;
			}			
		jx=jx+1;
		}		
}

// assuming the L and U matrices of an LU decomposition are given, this subprogram solves
// the equation LUX=B, with both X and B matrices of the same dimension of L and U
// Original code: Adolfo
void __mat16_solve(MAT16_int32_t_t *L, MAT16_int32_t_t *U, MAT16_int32_t_t *B, MAT16_int32_t_t *X )
{
	MAT16_int32_t_t Y;
	(*X).cols=(*B).cols;
	(*X).rows=(*B).rows;
	(*X).elem=(*B).elem;
	int ix; 
	int jx; 
	int k; 
	int n=4; 
	int position1;
	int position2; 
	int position3; 
	int position4; 
	
	/* forward substitution */ 
	for (jx=1; jx<=n; jx++) /* for each column */ 
		{
		for (ix=1; ix<=n; ix++) /* for each row */ 
			{
			position1=__mat_locate_position(ix,jx);
			position2=__mat_locate_position(ix,ix);
			Y.comp[position1]=fixedpt_div((*B).comp[position1] , (*L).comp[position2]);
				
			if (ix!=1)
				{
				for (k=1; k<ix; k++)
					{
					position3=__mat_locate_position(ix,k);
					position4=__mat_locate_position(k,jx);
					Y.comp[position1]=Y.comp[position1]-(fixedpt_div(fixedpt_mul((*L).comp[position3] , Y.comp[position4]) , (*L).comp[position2]));
					}
				}
			}
		
		}
	/* backsubstition */ 
	for (jx=n; jx>=1; jx--)
		{
		for (ix=n; ix>=1; ix--)
			{	
			position1=__mat_locate_position(ix,jx);
			position2=__mat_locate_position(ix,ix);
			(*X).comp[position1]=fixedpt_div((Y).comp[position1] , (*U).comp[position2]);
			/*if (ix!=1)	
				{*/
				for (k=ix+1; k<=n;k++)
					{
					position3=__mat_locate_position(ix,k);
					position4=__mat_locate_position(k,jx);
					(*X).comp[position1]=(*X).comp[position1]-(fixedpt_div(fixedpt_mul((*U).comp[position3], (*X).comp[position4]) , (*U).comp[position2]));
					}
				}
			/*}*/			
		}
}

// Original code: Adolfo
void mat16_inv(MAT16_int32_t_t *Matrix, MAT16_int32_t_t *Inverse)
{
    MAT_RESET(*Inverse);
	MAT16_int32_t_t L;
	MAT16_int32_t_t U;
	MAT16_int32_t_t identity;
    MAT_PREP_DIAG(identity, 4, 4,FIXEDPT_ONE);

	//MAT16_INIT(identity,4,4,FIXEDPT_ONE,0,0,0,0,FIXEDPT_ONE,0,0,0,0,FIXEDPT_ONE,0,0,0,0,FIXEDPT_ONE);
	
	__mat16_lu_decomp(Matrix,&L,&U);
	__mat16_solve(&L,&U,&identity,Inverse);
}

#if DEBUG_UNIT_TEST

inline bool mat_unit_test(void)
{
	MAT4_UINT8_t A4, B4, C4;				// declare matrix variables
	MAT9_UINT8_t A9, B9, C9;
//	MAT16_UINT8_t A16, B16, C16;
//	MAT25_int32_t_t A, B, C;
//	MAT36_int32_t_t A, B, C;
//	MAT49_int32_t_t A, B, C;

	// *** test init function
	
											// Use MAT4_INIT(mat_var, rows, cols, c0, c1, c2, c3) to initialize the matrix 'mat_var'
	MAT4_INIT(A4, 2, 2, 1, 2, 3, 4);		// 2x2 matrix with [1 2; 3 4]
	
	if(A4.elem != 4) return false;		// check if all elements are correct
	if(A4.rows != 2) return false;
	if(A4.cols != 2) return false;
		
	for(uint8_t i=0; i < A4.elem; i++)
	{
		if(A4.comp[i] != i+1) return false;
	}


	// *** test multiply function
	MAT4_INIT(B4, 2, 1, 1, 2, 0, 0);		// 2x1 vector with [1 2]
	
	MAT_MUL(A4, B4, C4);					// multiply A with B putting result in C

	if(A4.elem != 4) return false;		// check if all elements are correct
	if(A4.rows != 2) return false;
	if(A4.cols != 2) return false;
	
	for(uint8_t i=0; i < A4.elem; i++)
	{
		if(A4.comp[i] != i+1) return false;
	}

	if(B4.elem != 2) return false;		// check if all elements are correct
	if(B4.rows != 2) return false;
	if(B4.cols != 1) return false;

	for(uint8_t i=0; i < B4.elem; i++)
	{
		if(B4.comp[i] != (i+1)) return false;
	}

	//check multiplication result
	if(C4.elem != 2) return false;		// check if all elements are correct
	if(C4.rows != 2) return false;
	if(C4.cols != 1) return false;

	if(C4.comp[0] != 5) return false;
	if(C4.comp[1] != 11) return false;
	
	// *** test component multiply function
	MAT4_INIT(B4, 2, 2, 1, 2, 3, 4);
	
	MAT_MUL_COMP(A4, B4, C4);
		
	if(A4.elem != 4) return false;		// check if all elements are correct
	if(A4.rows != 2) return false;
	if(A4.cols != 2) return false;
	
	for(uint8_t i=0; i < A4.elem; i++)
	{
		if(A4.comp[i] != (i+1)) return false;
	}

	if(B4.elem != 4) return false;		// check if all elements are correct
	if(B4.rows != 2) return false;
	if(B4.cols != 2) return false;

	for(uint8_t i=0; i < B4.elem; i++)
	{
		if(B4.comp[i] != (i+1)) return false;
	}

	//check component multiplication result
	if(C4.elem != 4) return false;		// check if all elements are correct
	if(C4.rows != 2) return false;
	if(C4.cols != 2) return false;

	if(C4.comp[0] != 1) return false;
	if(C4.comp[1] != 4) return false;
	if(C4.comp[2] != 9) return false;
	if(C4.comp[3] != 16) return false;


	// *** test addition function
	MAT9_INIT(A9, 3, 2, 1, 2, 3, 4, 5, 6, 0, 0, 0);		// 3x2 matrix with [1 2; 3 4; 5 6]

	MAT9_INIT(B9, 3, 2, 1, 2, 3, 4, 5, 6, 0, 0, 0);		// 3x2 matrix with [1 2; 3 4; 5 6]

	MAT_ADD(A9, B9, C9);
	
	if(A9.elem != 6) return false;		// check if all elements are correct
	if(A9.rows != 3) return false;
	if(A9.cols != 2) return false;
	
	for(uint8_t i=0; i < A9.elem; i++)
	{
		if(A9.comp[i] != i+1) return false;
	}

	if(B9.elem != 6) return false;		// check if all elements are correct
	if(B9.rows != 3) return false;
	if(B9.cols != 2) return false;

	for(uint8_t i=0; i < B9.elem; i++)
	{
		if(B9.comp[i] != i+1) return false;
	}
	
	//check addition result
	if(C9.elem != 6) return false;		// check if all elements are correct
	if(C9.rows != 3) return false;
	if(C9.cols != 2) return false;

	if(C9.comp[0] != 2) return false;
	if(C9.comp[1] != 4) return false;
	if(C9.comp[2] != 6) return false;
	if(C9.comp[3] != 8) return false;
	if(C9.comp[4] != 10) return false;
	if(C9.comp[5] != 12) return false;
	
	// *** test subtraction function
	MAT_SUB(A9, B9, C9);
	
	if(A9.elem != 6) return false;		// check if all elements are correct
	if(A9.rows != 3) return false;
	if(A9.cols != 2) return false;
	
	for(uint8_t i=0; i < A9.elem; i++)
	{
		if( A9.comp[i] != (i+1) ) return false;
	}

	if(B9.elem != 6) return false;		// check if all elements are correct
	if(B9.rows != 3) return false;
	if(B9.cols != 2) return false;

	for(uint8_t i=0; i < B9.elem; i++)
	{
		if( B9.comp[i] != (i+1) ) return false;
	}
	
	//check subtraction result
	if(C9.elem != 6) return false;		// check if all elements are correct
	if(C9.rows != 3) return false;
	if(C9.cols != 2) return false;

	for(uint8_t i=0; i < C9.elem; i++)
	{
		if(C9.comp[i] != 0) return false;
	}
	
	// *** test transpose function
	MAT9_INIT(A9, 3, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	MAT_CLEAR(C9);
	
	MAT_TRANSP(A9, C9);					// result: [1 4 7; 2 5 8; 3 6 9]
	
	if(A9.elem != 9) return false;		// check if all elements are correct
	if(A9.rows != 3) return false;
	if(A9.cols != 3) return false;
	
	for(uint8_t i=0; i < A9.elem; i++)
	{
		if( A9.comp[i] != (i+1) ) return false;
	}

	if(C9.comp[0] != 1) return false;
	if(C9.comp[1] != 4) return false;
	if(C9.comp[2] != 7) return false;
	if(C9.comp[3] != 2) return false;
	if(C9.comp[4] != 5) return false;
	if(C9.comp[5] != 8) return false;
	if(C9.comp[6] != 3) return false;
	if(C9.comp[7] != 6) return false;
	if(C9.comp[8] != 9) return false;

	// again with non square matrix
	MAT9_INIT(A9, 3, 2, 1, 2, 3, 4, 5, 6, 0, 0, 0);		// 3x2, [1 2; 3 4; 5 6]
	MAT_CLEAR(C9);
	
	MAT_TRANSP(A9, C9);					// result: [1 3 5; 2 4 6]
	
	if(A9.elem != 6) return false;		// check if all elements are correct
	if(A9.rows != 3) return false;
	if(A9.cols != 2) return false;
	
	for(uint8_t i=0; i < A9.elem; i++)
	{
		if( A9.comp[i] != (i+1) ) return false;
	}

	if(C9.comp[0] != 1) return false;
	if(C9.comp[1] != 3) return false;
	if(C9.comp[2] != 5) return false;
	if(C9.comp[3] != 2) return false;
	if(C9.comp[4] != 4) return false;
	if(C9.comp[5] != 6) return false;
	
	// *** test expansion functions
	MAT9_INIT(A9, 1, 3, 1, 2, 3, 0, 0, 0, 0, 0, 0);
	MAT_CLEAR(B9);
	MAT_TRANSP(A9, B9);
	
	MAT_EXPAND_ROW(A9, 3);
	MAT_EXPAND_COL(B9, 3);

	//test_func(B9, 3);

	//check	result
	if(A9.comp[0] != 1) return false;	//row expanded [1 2 3]
	if(A9.comp[1] != 2) return false;
	if(A9.comp[2] != 3) return false;
	if(A9.comp[3] != 1) return false;
	if(A9.comp[4] != 2) return false;
	if(A9.comp[5] != 3) return false;
	if(A9.comp[6] != 1) return false;
	if(A9.comp[7] != 2) return false;
	if(A9.comp[8] != 3) return false;
	
	if(B9.comp[0] != 1) return false;	//column expanded [1; 2; 3]
	if(B9.comp[1] != 1) return false;
	if(B9.comp[2] != 1) return false;
	if(B9.comp[3] != 2) return false;
	if(B9.comp[4] != 2) return false;
	if(B9.comp[5] != 2) return false;
	if(B9.comp[6] != 3) return false;
	if(B9.comp[7] != 3) return false;
	if(B9.comp[8] != 3) return false;

	// *** test cross product
	MAT4_ROWVEC_INIT(A4, 5, 7, 9, 11);
	MAT4_ROWVEC_INIT(B4, 1, 3, 5, 7);
	MAT_CLEAR(C4);
	
	MAT_CROSS_PROD(A4, B4, C4);

	if(C4.comp[0] != ((uint8_t) (35-27))) return false;
	if(C4.comp[1] != ((uint8_t) (63-55))) return false;
	if(C4.comp[2] != ((uint8_t) (11-35))) return false;
	if(C4.comp[3] != ((uint8_t) (15-7))) return false;
	
	return true;
}

#endif // DEBUG_UNIT_TEST


