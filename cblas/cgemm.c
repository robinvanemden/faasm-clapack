
/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "cblas.h"

void cblas_cgemm(const enum CBLAS_ORDER Order, const enum CBLAS_TRANSPOSE TransA,
                 const enum CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const void *alpha, const void *A,
                 const int lda, const void *B, const int ldb,
                 const void *beta, void *C, const int ldc) {

    inner_cgemm(TO_CHAR_TRANSPOSE(TransA), TO_CHAR_TRANSPOSE(TransB),
            &M, &N, &K, alpha, A, &lda, B, &ldb, beta, C, &ldc);
}

/* Subroutine */ int inner_cgemm(char *transa, char *transb, integer *m, integer *
	n, integer *k, complex *alpha, complex *a, integer *lda, complex *b, 
	integer *ldb, complex *beta, complex *c, integer *ldc)
{


    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, i__1, i__2, 
	    i__3, i__4, i__5, i__6;
    complex q__1, q__2, q__3, q__4;

    /* Builtin functions */
    void r_cnjg(complex *, complex *);

    /* Local variables */
    static integer info;
    static logical nota, notb;
    static complex temp;
    static integer i, j, l;
    static logical conja, conjb;
    static integer ncola;
    extern logical lsame_(char *, char *);
    static integer nrowa, nrowb;
    extern /* Subroutine */ int xerbla_(char *, integer *);


/*  Purpose   
    =======   

    CGEMM  performs one of the matrix-matrix operations   

       C := alpha*op( A )*op( B ) + beta*C,   

    where  op( X ) is one of   

       op( X ) = X   or   op( X ) = X'   or   op( X ) = conjg( X' ),   

    alpha and beta are scalars, and A, B and C are matrices, with op( A ) 
  
    an m by k matrix,  op( B )  a  k by n matrix and  C an m by n matrix. 
  

    Parameters   
    ==========   

    TRANSA - CHARACTER*1.   
             On entry, TRANSA specifies the form of op( A ) to be used in 
  
             the matrix multiplication as follows:   

                TRANSA = 'N' or 'n',  op( A ) = A.   

                TRANSA = 'T' or 't',  op( A ) = A'.   

                TRANSA = 'C' or 'c',  op( A ) = conjg( A' ).   

             Unchanged on exit.   

    TRANSB - CHARACTER*1.   
             On entry, TRANSB specifies the form of op( B ) to be used in 
  
             the matrix multiplication as follows:   

                TRANSB = 'N' or 'n',  op( B ) = B.   

                TRANSB = 'T' or 't',  op( B ) = B'.   

                TRANSB = 'C' or 'c',  op( B ) = conjg( B' ).   

             Unchanged on exit.   

    M      - INTEGER.   
             On entry,  M  specifies  the number  of rows  of the  matrix 
  
             op( A )  and of the  matrix  C.  M  must  be at least  zero. 
  
             Unchanged on exit.   

    N      - INTEGER.   
             On entry,  N  specifies the number  of columns of the matrix 
  
             op( B ) and the number of columns of the matrix C. N must be 
  
             at least zero.   
             Unchanged on exit.   

    K      - INTEGER.   
             On entry,  K  specifies  the number of columns of the matrix 
  
             op( A ) and the number of rows of the matrix op( B ). K must 
  
             be at least  zero.   
             Unchanged on exit.   

    ALPHA  - COMPLEX         .   
             On entry, ALPHA specifies the scalar alpha.   
             Unchanged on exit.   

    A      - COMPLEX          array of DIMENSION ( LDA, ka ), where ka is 
  
             k  when  TRANSA = 'N' or 'n',  and is  m  otherwise.   
             Before entry with  TRANSA = 'N' or 'n',  the leading  m by k 
  
             part of the array  A  must contain the matrix  A,  otherwise 
  
             the leading  k by m  part of the array  A  must contain  the 
  
             matrix A.   
             Unchanged on exit.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in the calling (sub) program. When  TRANSA = 'N' or 'n' then 
  
             LDA must be at least  max( 1, m ), otherwise  LDA must be at 
  
             least  max( 1, k ).   
             Unchanged on exit.   

    B      - COMPLEX          array of DIMENSION ( LDB, kb ), where kb is 
  
             n  when  TRANSB = 'N' or 'n',  and is  k  otherwise.   
             Before entry with  TRANSB = 'N' or 'n',  the leading  k by n 
  
             part of the array  B  must contain the matrix  B,  otherwise 
  
             the leading  n by k  part of the array  B  must contain  the 
  
             matrix B.   
             Unchanged on exit.   

    LDB    - INTEGER.   
             On entry, LDB specifies the first dimension of B as declared 
  
             in the calling (sub) program. When  TRANSB = 'N' or 'n' then 
  
             LDB must be at least  max( 1, k ), otherwise  LDB must be at 
  
             least  max( 1, n ).   
             Unchanged on exit.   

    BETA   - COMPLEX         .   
             On entry,  BETA  specifies the scalar  beta.  When  BETA  is 
  
             supplied as zero then C need not be set on input.   
             Unchanged on exit.   

    C      - COMPLEX          array of DIMENSION ( LDC, n ).   
             Before entry, the leading  m by n  part of the array  C must 
  
             contain the matrix  C,  except when  beta  is zero, in which 
  
             case C need not be set on entry.   
             On exit, the array  C  is overwritten by the  m by n  matrix 
  
             ( alpha*op( A )*op( B ) + beta*C ).   

    LDC    - INTEGER.   
             On entry, LDC specifies the first dimension of C as declared 
  
             in  the  calling  (sub)  program.   LDC  must  be  at  least 
  
             max( 1, m ).   
             Unchanged on exit.   


    Level 3 Blas routine.   

    -- Written on 8-February-1989.   
       Jack Dongarra, Argonne National Laboratory.   
       Iain Duff, AERE Harwell.   
       Jeremy Du Croz, Numerical Algorithms Group Ltd.   
       Sven Hammarling, Numerical Algorithms Group Ltd.   



       Set  NOTA  and  NOTB  as  true if  A  and  B  respectively are not 
  
       conjugated or transposed, set  CONJA and CONJB  as true if  A  and 
  
       B  respectively are to be  transposed but  not conjugated  and set 
  
       NROWA, NCOLA and  NROWB  as the number of rows and  columns  of  A 
  
       and the number of rows of  B  respectively.   

    
   Parameter adjustments   
       Function Body */

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define B(I,J) b[(I)-1 + ((J)-1)* ( *ldb)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    nota = lsame_(transa, "N");
    notb = lsame_(transb, "N");
    conja = lsame_(transa, "C");
    conjb = lsame_(transb, "C");
    if (nota) {
	nrowa = *m;
	ncola = *k;
    } else {
	nrowa = *k;
	ncola = *m;
    }
    if (notb) {
	nrowb = *k;
    } else {
	nrowb = *n;
    }

/*     Test the input parameters. */

    info = 0;
    if (! nota && ! conja && ! lsame_(transa, "T")) {
	info = 1;
    } else if (! notb && ! conjb && ! lsame_(transb, "T")) {
	info = 2;
    } else if (*m < 0) {
	info = 3;
    } else if (*n < 0) {
	info = 4;
    } else if (*k < 0) {
	info = 5;
    } else if (*lda < max(1,nrowa)) {
	info = 8;
    } else if (*ldb < max(1,nrowb)) {
	info = 10;
    } else if (*ldc < max(1,*m)) {
	info = 13;
    }
    if (info != 0) {
	xerbla_("CGEMM ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || (alpha->r == 0.f && alpha->i == 0.f || *k == 0) 
	    && (beta->r == 1.f && beta->i == 0.f)) {
	return 0;
    }

/*     And when  alpha.eq.zero. */

    if (alpha->r == 0.f && alpha->i == 0.f) {
	if (beta->r == 0.f && beta->i == 0.f) {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    i__3 = i + j * c_dim1;
		    C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L10: */
		}
/* L20: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    i__3 = i + j * c_dim1;
		    i__4 = i + j * c_dim1;
		    q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
			    q__1.i = beta->r * C(i,j).i + beta->i * C(i,j)
			    .r;
		    C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L30: */
		}
/* L40: */
	    }
	}
	return 0;
    }

/*     Start the operations. */

    if (notb) {
	if (nota) {

/*           Form  C := alpha*A*B + beta*C. */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		if (beta->r == 0.f && beta->i == 0.f) {
		    i__2 = *m;
		    for (i = 1; i <= *m; ++i) {
			i__3 = i + j * c_dim1;
			C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L50: */
		    }
		} else if (beta->r != 1.f || beta->i != 0.f) {
		    i__2 = *m;
		    for (i = 1; i <= *m; ++i) {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__1.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L60: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= *k; ++l) {
		    i__3 = l + j * b_dim1;
		    if (B(l,j).r != 0.f || B(l,j).i != 0.f) {
			i__3 = l + j * b_dim1;
			q__1.r = alpha->r * B(l,j).r - alpha->i * B(l,j).i, 
				q__1.i = alpha->r * B(l,j).i + alpha->i * B(l,j).r;
			temp.r = q__1.r, temp.i = q__1.i;
			i__3 = *m;
			for (i = 1; i <= *m; ++i) {
			    i__4 = i + j * c_dim1;
			    i__5 = i + j * c_dim1;
			    i__6 = i + l * a_dim1;
			    q__2.r = temp.r * A(i,l).r - temp.i * A(i,l).i, 
				    q__2.i = temp.r * A(i,l).i + temp.i * A(i,l).r;
			    q__1.r = C(i,j).r + q__2.r, q__1.i = C(i,j).i + 
				    q__2.i;
			    C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L70: */
			}
		    }
/* L80: */
		}
/* L90: */
	    }
	} else if (conja) {

/*           Form  C := alpha*conjg( A' )*B + beta*C. */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    temp.r = 0.f, temp.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			r_cnjg(&q__3, &A(l,i));
			i__4 = l + j * b_dim1;
			q__2.r = q__3.r * B(l,j).r - q__3.i * B(l,j).i, 
				q__2.i = q__3.r * B(l,j).i + q__3.i * B(l,j)
				.r;
			q__1.r = temp.r + q__2.r, q__1.i = temp.i + q__2.i;
			temp.r = q__1.r, temp.i = q__1.i;
/* L100: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__1.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__1.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__2.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L110: */
		}
/* L120: */
	    }
	} else {

/*           Form  C := alpha*A'*B + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    temp.r = 0.f, temp.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			i__4 = l + i * a_dim1;
			i__5 = l + j * b_dim1;
			q__2.r = A(l,i).r * B(l,j).r - A(l,i).i * B(l,j)
				.i, q__2.i = A(l,i).r * B(l,j).i + A(l,i)
				.i * B(l,j).r;
			q__1.r = temp.r + q__2.r, q__1.i = temp.i + q__2.i;
			temp.r = q__1.r, temp.i = q__1.i;
/* L130: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__1.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__1.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__2.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L140: */
		}
/* L150: */
	    }
	}
    } else if (nota) {
	if (conjb) {

/*           Form  C := alpha*A*conjg( B' ) + beta*C. */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		if (beta->r == 0.f && beta->i == 0.f) {
		    i__2 = *m;
		    for (i = 1; i <= *m; ++i) {
			i__3 = i + j * c_dim1;
			C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L160: */
		    }
		} else if (beta->r != 1.f || beta->i != 0.f) {
		    i__2 = *m;
		    for (i = 1; i <= *m; ++i) {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__1.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L170: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= *k; ++l) {
		    i__3 = j + l * b_dim1;
		    if (B(j,l).r != 0.f || B(j,l).i != 0.f) {
			r_cnjg(&q__2, &B(j,l));
			q__1.r = alpha->r * q__2.r - alpha->i * q__2.i, 
				q__1.i = alpha->r * q__2.i + alpha->i * 
				q__2.r;
			temp.r = q__1.r, temp.i = q__1.i;
			i__3 = *m;
			for (i = 1; i <= *m; ++i) {
			    i__4 = i + j * c_dim1;
			    i__5 = i + j * c_dim1;
			    i__6 = i + l * a_dim1;
			    q__2.r = temp.r * A(i,l).r - temp.i * A(i,l).i, 
				    q__2.i = temp.r * A(i,l).i + temp.i * A(i,l).r;
			    q__1.r = C(i,j).r + q__2.r, q__1.i = C(i,j).i + 
				    q__2.i;
			    C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L180: */
			}
		    }
/* L190: */
		}
/* L200: */
	    }
	} else {

/*           Form  C := alpha*A*B'          + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		if (beta->r == 0.f && beta->i == 0.f) {
		    i__2 = *m;
		    for (i = 1; i <= *m; ++i) {
			i__3 = i + j * c_dim1;
			C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L210: */
		    }
		} else if (beta->r != 1.f || beta->i != 0.f) {
		    i__2 = *m;
		    for (i = 1; i <= *m; ++i) {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__1.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L220: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= *k; ++l) {
		    i__3 = j + l * b_dim1;
		    if (B(j,l).r != 0.f || B(j,l).i != 0.f) {
			i__3 = j + l * b_dim1;
			q__1.r = alpha->r * B(j,l).r - alpha->i * B(j,l).i, 
				q__1.i = alpha->r * B(j,l).i + alpha->i * B(j,l).r;
			temp.r = q__1.r, temp.i = q__1.i;
			i__3 = *m;
			for (i = 1; i <= *m; ++i) {
			    i__4 = i + j * c_dim1;
			    i__5 = i + j * c_dim1;
			    i__6 = i + l * a_dim1;
			    q__2.r = temp.r * A(i,l).r - temp.i * A(i,l).i, 
				    q__2.i = temp.r * A(i,l).i + temp.i * A(i,l).r;
			    q__1.r = C(i,j).r + q__2.r, q__1.i = C(i,j).i + 
				    q__2.i;
			    C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L230: */
			}
		    }
/* L240: */
		}
/* L250: */
	    }
	}
    } else if (conja) {
	if (conjb) {

/*           Form  C := alpha*conjg( A' )*conjg( B' ) + beta*C. */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    temp.r = 0.f, temp.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			r_cnjg(&q__3, &A(l,i));
			r_cnjg(&q__4, &B(j,l));
			q__2.r = q__3.r * q__4.r - q__3.i * q__4.i, q__2.i = 
				q__3.r * q__4.i + q__3.i * q__4.r;
			q__1.r = temp.r + q__2.r, q__1.i = temp.i + q__2.i;
			temp.r = q__1.r, temp.i = q__1.i;
/* L260: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__1.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__1.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__2.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L270: */
		}
/* L280: */
	    }
	} else {

/*           Form  C := alpha*conjg( A' )*B' + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    temp.r = 0.f, temp.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			r_cnjg(&q__3, &A(l,i));
			i__4 = j + l * b_dim1;
			q__2.r = q__3.r * B(j,l).r - q__3.i * B(j,l).i, 
				q__2.i = q__3.r * B(j,l).i + q__3.i * B(j,l)
				.r;
			q__1.r = temp.r + q__2.r, q__1.i = temp.i + q__2.i;
			temp.r = q__1.r, temp.i = q__1.i;
/* L290: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__1.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__1.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__2.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L300: */
		}
/* L310: */
	    }
	}
    } else {
	if (conjb) {

/*           Form  C := alpha*A'*conjg( B' ) + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    temp.r = 0.f, temp.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			i__4 = l + i * a_dim1;
			r_cnjg(&q__3, &B(j,l));
			q__2.r = A(l,i).r * q__3.r - A(l,i).i * q__3.i, 
				q__2.i = A(l,i).r * q__3.i + A(l,i).i * 
				q__3.r;
			q__1.r = temp.r + q__2.r, q__1.i = temp.i + q__2.i;
			temp.r = q__1.r, temp.i = q__1.i;
/* L320: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__1.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__1.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__2.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L330: */
		}
/* L340: */
	    }
	} else {

/*           Form  C := alpha*A'*B' + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *m;
		for (i = 1; i <= *m; ++i) {
		    temp.r = 0.f, temp.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			i__4 = l + i * a_dim1;
			i__5 = j + l * b_dim1;
			q__2.r = A(l,i).r * B(j,l).r - A(l,i).i * B(j,l)
				.i, q__2.i = A(l,i).r * B(j,l).i + A(l,i)
				.i * B(j,l).r;
			q__1.r = temp.r + q__2.r, q__1.i = temp.i + q__2.i;
			temp.r = q__1.r, temp.i = q__1.i;
/* L350: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__1.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__1.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp.r - alpha->i * temp.i, 
				q__2.i = alpha->r * temp.i + alpha->i * 
				temp.r;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L360: */
		}
/* L370: */
	    }
	}
    }

    return 0;

/*     End of CGEMM . */

} /* cgemm_ */

