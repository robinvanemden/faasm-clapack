
/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "cblas.h"

void cblas_ssyrk(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE Trans, const int N, const int K,
                 const float alpha, const float *A, const int lda,
                 const float beta, float *C, const int ldc) {
    inner_ssyrk(TO_CHAR_UPLO(Uplo), TO_CHAR_TRANSPOSE(Trans),
            &N, &K, &alpha, A, &lda, &beta, C, &ldc);
}

/* Subroutine */ int inner_ssyrk(char *uplo, char *trans, integer *n, integer *k,
	real *alpha, real *a, integer *lda, real *beta, real *c, integer *ldc)
{


    /* System generated locals */
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2, i__3;

    /* Local variables */
    static integer info;
    static real temp;
    static integer i, j, l;
    extern logical lsame_(char *, char *);
    static integer nrowa;
    static logical upper;
    extern /* Subroutine */ int xerbla_(char *, integer *);


/*  Purpose   
    =======   

    SSYRK  performs one of the symmetric rank k operations   

       C := alpha*A*A' + beta*C,   

    or   

       C := alpha*A'*A + beta*C,   

    where  alpha and beta  are scalars, C is an  n by n  symmetric matrix 
  
    and  A  is an  n by k  matrix in the first case and a  k by n  matrix 
  
    in the second case.   

    Parameters   
    ==========   

    UPLO   - CHARACTER*1.   
             On  entry,   UPLO  specifies  whether  the  upper  or  lower 
  
             triangular  part  of the  array  C  is to be  referenced  as 
  
             follows:   

                UPLO = 'U' or 'u'   Only the  upper triangular part of  C 
  
                                    is to be referenced.   

                UPLO = 'L' or 'l'   Only the  lower triangular part of  C 
  
                                    is to be referenced.   

             Unchanged on exit.   

    TRANS  - CHARACTER*1.   
             On entry,  TRANS  specifies the operation to be performed as 
  
             follows:   

                TRANS = 'N' or 'n'   C := alpha*A*A' + beta*C.   

                TRANS = 'T' or 't'   C := alpha*A'*A + beta*C.   

                TRANS = 'C' or 'c'   C := alpha*A'*A + beta*C.   

             Unchanged on exit.   

    N      - INTEGER.   
             On entry,  N specifies the order of the matrix C.  N must be 
  
             at least zero.   
             Unchanged on exit.   

    K      - INTEGER.   
             On entry with  TRANS = 'N' or 'n',  K  specifies  the number 
  
             of  columns   of  the   matrix   A,   and  on   entry   with 
  
             TRANS = 'T' or 't' or 'C' or 'c',  K  specifies  the  number 
  
             of rows of the matrix  A.  K must be at least zero.   
             Unchanged on exit.   

    ALPHA  - REAL            .   
             On entry, ALPHA specifies the scalar alpha.   
             Unchanged on exit.   

    A      - REAL             array of DIMENSION ( LDA, ka ), where ka is 
  
             k  when  TRANS = 'N' or 'n',  and is  n  otherwise.   
             Before entry with  TRANS = 'N' or 'n',  the  leading  n by k 
  
             part of the array  A  must contain the matrix  A,  otherwise 
  
             the leading  k by n  part of the array  A  must contain  the 
  
             matrix A.   
             Unchanged on exit.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in  the  calling  (sub)  program.   When  TRANS = 'N' or 'n' 
  
             then  LDA must be at least  max( 1, n ), otherwise  LDA must 
  
             be at least  max( 1, k ).   
             Unchanged on exit.   

    BETA   - REAL            .   
             On entry, BETA specifies the scalar beta.   
             Unchanged on exit.   

    C      - REAL             array of DIMENSION ( LDC, n ).   
             Before entry  with  UPLO = 'U' or 'u',  the leading  n by n 
  
             upper triangular part of the array C must contain the upper 
  
             triangular part  of the  symmetric matrix  and the strictly 
  
             lower triangular part of C is not referenced.  On exit, the 
  
             upper triangular part of the array  C is overwritten by the 
  
             upper triangular part of the updated matrix.   
             Before entry  with  UPLO = 'L' or 'l',  the leading  n by n 
  
             lower triangular part of the array C must contain the lower 
  
             triangular part  of the  symmetric matrix  and the strictly 
  
             upper triangular part of C is not referenced.  On exit, the 
  
             lower triangular part of the array  C is overwritten by the 
  
             lower triangular part of the updated matrix.   

    LDC    - INTEGER.   
             On entry, LDC specifies the first dimension of C as declared 
  
             in  the  calling  (sub)  program.   LDC  must  be  at  least 
  
             max( 1, n ).   
             Unchanged on exit.   


    Level 3 Blas routine.   

    -- Written on 8-February-1989.   
       Jack Dongarra, Argonne National Laboratory.   
       Iain Duff, AERE Harwell.   
       Jeremy Du Croz, Numerical Algorithms Group Ltd.   
       Sven Hammarling, Numerical Algorithms Group Ltd.   



       Test the input parameters.   

    
   Parameter adjustments   
       Function Body */

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    if (lsame_(trans, "N")) {
	nrowa = *n;
    } else {
	nrowa = *k;
    }
    upper = lsame_(uplo, "U");

    info = 0;
    if (! upper && ! lsame_(uplo, "L")) {
	info = 1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans, "T") &&
	     ! lsame_(trans, "C")) {
	info = 2;
    } else if (*n < 0) {
	info = 3;
    } else if (*k < 0) {
	info = 4;
    } else if (*lda < max(1,nrowa)) {
	info = 7;
    } else if (*ldc < max(1,*n)) {
	info = 10;
    }
    if (info != 0) {
	xerbla_("SSYRK ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0 || (*alpha == 0.f || *k == 0) && *beta == 1.f) {
	return 0;
    }

/*     And when  alpha.eq.zero. */

    if (*alpha == 0.f) {
	if (upper) {
	    if (*beta == 0.f) {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			C(i,j) = 0.f;
/* L10: */
		    }
/* L20: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			C(i,j) = *beta * C(i,j);
/* L30: */
		    }
/* L40: */
		}
	    }
	} else {
	    if (*beta == 0.f) {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			C(i,j) = 0.f;
/* L50: */
		    }
/* L60: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			C(i,j) = *beta * C(i,j);
/* L70: */
		    }
/* L80: */
		}
	    }
	}
	return 0;
    }

/*     Start the operations. */

    if (lsame_(trans, "N")) {

/*        Form  C := alpha*A*A' + beta*C. */

	if (upper) {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		if (*beta == 0.f) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			C(i,j) = 0.f;
/* L90: */
		    }
		} else if (*beta != 1.f) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			C(i,j) = *beta * C(i,j);
/* L100: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= *k; ++l) {
		    if (A(j,l) != 0.f) {
			temp = *alpha * A(j,l);
			i__3 = j;
			for (i = 1; i <= j; ++i) {
			    C(i,j) += temp * A(i,l);
/* L110: */
			}
		    }
/* L120: */
		}
/* L130: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		if (*beta == 0.f) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			C(i,j) = 0.f;
/* L140: */
		    }
		} else if (*beta != 1.f) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			C(i,j) = *beta * C(i,j);
/* L150: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= *k; ++l) {
		    if (A(j,l) != 0.f) {
			temp = *alpha * A(j,l);
			i__3 = *n;
			for (i = j; i <= *n; ++i) {
			    C(i,j) += temp * A(i,l);
/* L160: */
			}
		    }
/* L170: */
		}
/* L180: */
	    }
	}
    } else {

/*        Form  C := alpha*A'*A + beta*C. */

	if (upper) {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = j;
		for (i = 1; i <= j; ++i) {
		    temp = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			temp += A(l,i) * A(l,j);
/* L190: */
		    }
		    if (*beta == 0.f) {
			C(i,j) = *alpha * temp;
		    } else {
			C(i,j) = *alpha * temp + *beta * C(i,j);
		    }
/* L200: */
		}
/* L210: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *n;
		for (i = j; i <= *n; ++i) {
		    temp = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			temp += A(l,i) * A(l,j);
/* L220: */
		    }
		    if (*beta == 0.f) {
			C(i,j) = *alpha * temp;
		    } else {
			C(i,j) = *alpha * temp + *beta * C(i,j);
		    }
/* L230: */
		}
/* L240: */
	    }
	}
    }

    return 0;

/*     End of SSYRK . */

} /* ssyrk_ */

