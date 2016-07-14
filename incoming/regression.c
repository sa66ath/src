#include <stdio.h>
#include <math.h>
#include <stdlib.h>

main()
{
	int	m;
	int	count;
	int	i, j, k;
	double	*a, *f, *x, *xt, *xx, *xf;

	printf("dimention = ");
	scanf("%d", &m);
	printf("data count = ");
	scanf("%d", &count);

	if(NULL == (a = (double *)malloc(count * sizeof(double)))) {
		printf("Memory Error!!!\n");
		exit(-1);
	}

	if(NULL == (f = (double *)malloc(count * sizeof(double)))) {
		printf("Memory Error!!!\n");
		exit(-1);
	}

	for(i = 0; i < count; i++) {
		printf("x,y = ");
		scanf("%lf%lf", a+i, f+i);
	}
	
	if(NULL == (xf = (double *)malloc((m+1) * sizeof(double)))) {
		printf("Memory Error\n");
		exit(-1);
	}

	regression(m, count, a, f, xf);
	putchar('\n');
	print_arry(xf, m+1, 1);
}

/*
	regression line determin
			m: dimention
			count: data count
			a[count], b[count]
			c[m-1][m-1]
*/
int	regression(m, count, a, b, c)
double	*a, *b, *c;
{
	double	*x, *xt, *xx;
	int	i, j, k;

	if(NULL == (x = (double *)malloc((m+1) * count * sizeof(double)))) {
		printf("Memory Error in regression()\n");
		exit(-1);
	}

	for(i = 0; i < count; i++) {
		*(x + i*(m+1) +m) = 1.0;
	}

	for(i = m-1; i >= 0; i--) {
		for(j = 0; j < count; j++) {
			*(x +j*(m+1) +i) = (*(x +j*(m+1) +(i+1)) * *(a+j)); 
		}
	}	
#ifdef	DEBUG
	printf("X \n");
	print_arry(x, count, m+1); 
	putchar('\n');
#endif

	if(NULL == (xt = (double *)malloc((m+1) * count * sizeof(double)))) {
		printf("Memory Error in regression()\n");
		exit(-1);
	}

	rotate_arry(x, count, m+1, xt); 
#ifdef	DEBUG
	printf("Xt\n");
	print_arry(xt, m+1, count);
	putchar('\n');
#endif

	if(NULL == (xx = (double *)malloc((m+1) * (m+1) * sizeof(double)))) {
		printf("Memory Error in regression()\n");
		exit(-1);
	}

	mul_arry(xt, m+1, count, x, count, m+1, xx);
#ifdef	DEBUG
	printf("XtX\n");
	print_arry(xx, m+1, m+1);
	putchar('\n');
#endif
	
	mul_arry(xt, m+1, count, b, count, 1, c);
#ifdef	DEBUG
	printf(" XtF \n");
	print_arry(c, m+1, 1);
	putchar('\n');
#endif
	LUdecomp(m+1, xx, c);
	free(x);
	free(xt);
	free(xx);
}

/*
	Gaussian Elimination
		prameter	dim: dimention (1 < dim)
					a:		pointer of arry[dim][dim+1]
*/
int gauss_elimi(dim, a)
double	*a;
{
	int	i, j, k;
	double	c;
	double	max;
	int		lmax;
	double	temp;

	for(i = 1; i < dim; i++) {		/* forword elimination */
		/* pivot exchange */
		max = fabs((double)*(a +(i-1)*(dim+1) + (i-1)));
		lmax = i - 1;
		for(j = i; j < dim; j++) {
			if(max < *(a +j*(dim+1) + (i-1))) {
				max = fabs((double)*(a + j*(dim+1) + (i-1)));
				lmax = j;
			}
		}
		if(lmax != (i-1)) {
			for(k = i - 1; k <= dim; k++) {
				temp = *(a +(i-1)*(dim+1) +k);
				*(a +(i-1)*(dim+1) +k) = *(a +lmax*(dim+1) +k);
				*(a +lmax*(dim+1) +k) = temp;
			}
		}
		c = 1.0/ *(a+(i-1)*(dim+1)+(i-1));
		for(j = i; j < dim; j++) {
			c *= *(a+j*(dim+1)+(i-1));
			for(k = i; k <= dim; k++) {
				*(a+j*(dim+1)+k) -= *(a+(i-1)*(dim+1)+k) * c;
			}
		}
	}
	/* backword substitution */
	for(i = dim - 1; i >= 0; i--) {	
		for(j = dim - 1; j > i; j--) {
			*(a +i*(dim+1) + dim) -=
				*(a +i*(dim+1) +j) * *(a +j*(dim+1) + dim);
		}
		*(a +i*(dim+1) + dim) /= *(a+ i*(dim+1) +i);
	}
}

int LUdecomp(dim, a, b)
double	*a, *b;
{
	int	i, j, k;
	double	w, max, nmax, temp;
	int	lmax;
	
	for(i = 0; i < dim-1; i++) {
		max = fabs(*(a+i*dim+i));
		lmax = i;
		for(j = i + 1; j < dim; j++) {
			if(max < (nmax = fabs(*(a +j*dim + i)))) {
				max = nmax;
				lmax = j;
			}
		}
		if(lmax != i) {
			for(k = 0; k < dim; k++) {
				temp = *(a +i*dim +k);
				*(a +i*dim +k) = *(a +lmax*dim +k);
				*(a +lmax*dim +k) = temp;
			}
			temp = *(b+i);
			*(b+i) = *(b+lmax);
			*(b+lmax) = temp;
		}
		w = 1.0/ *(a + i*dim + i);
		for(j = i+1; j < dim; j++) {
			*(a + j*dim + i) *= w;
			for(k = i+1; k < dim; k++) {
				*(a +j*dim + k) -= 
					((*(a +j*dim +i) * *(a +i*dim + k)));
			}
		}
	}
	for(i = 1; i < dim; i++) {		/* L*Y = B */
		for(j = 0; j < i; j++) {
			*(b+i) -=
				(*(a +i*dim +j) * *(b +j));
		}
	}
	for(i = dim-1; i >= 0; i--) {
		for(j = dim-1; j > i; j--) {
			*(b+i) -=
				(*(a +i*dim+j) * *(b+j));
		}
		*(b+i) /= *(a +i*dim + i);
	}
}

/*
	multiply arry
*/
int mul_arry(a, m, n, b, r, s, c)
double	*a, *b, *c;
{
	int	i, j, k;

	if(n != r)
		return -1;
	for(i = 0; i < m; i++) {
		for(j = 0; j < s; j++) {
			*(c +i*s +j) = 0.0;
			for(k = 0; k < n; k++) {
				*(c +i*s +j) += (*(a +i*n +k) * *(b +k*s +j));
			}
		}
	}
	return	0;
}	 			

/*
	rotate arry
*/
int	rotate_arry(a, m, n, b)
double	*a, *b;
{
	int	i, j;

	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			*(b +j*m + i) = *(a +i*n +j);
		}
	}
}

/*
	print arry
*/
int print_arry(arry, m, n)
double	*arry;
{
	int	i, j;

	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			printf("%lf ", *(arry +i*n + j));
		}
		putchar('\n');
	}
}
