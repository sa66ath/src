/*=============================================================================
	spline.cpp: Spline (4 Point Lagrange Interporation) 
	$Header: /home/boss/ikeda/source/RCS/spline.cpp,v 1.2 1999/11/26 07:59:12 ikeda Exp $
=============================================================================*/
#include <math.h>

#include "spline.h"
#include "lagrange.h"

/*----------------------------------------------------------------------------
	prog  : ikeda@roland.co.jp
	func  : Spline (4 Point Lagrrange) Interporation
	date  : Fri Nov 26 16:44:19 JST 1999
	update: 
	entry : n=Data Pair Num,
		xdata=X Data array pointer
		ydata=Y Data array pointer
		x=x
	return: y
	remks :
----------------------------------------------------------------------------*/
double spline(int n, double* xdata, double* ydata, double x)
{

	if(n <= 4)	return lagrange(n, xdata, ydata, x);

	int min = 0;
	int max = n - 1;

	if(xdata[max] <= x) {
		min = n - 1;
	} else {
		while((min+1) < max) {
			int p = (min+max)>>1;
			if(x < xdata[p])	max = p;
			else			min = p;
		}
	}

	if(min == 0) {
		return lagrange(4, &xdata[0], &ydata[0], x);
	} else {
		if(min == (n-1)) {
			return lagrange(4, &xdata[n-4], &ydata[n-4], x);
		} else {
			return lagrange(4, &xdata[min-1], &ydata[min-1], x);
		}
	}
}


#ifdef M_DEBUG
#include <iostream.h>

int main()
{
	int n;
	double min, max, step;

	cerr << "min=";
	cin >> min;
	cerr << "max=";
	cin >> max;
	cerr << "step=";
	cin >> step;

	cout << "min=" << min << ", max=" << max << ", step=" << step << endl;

	double* xdata;
	double* ydata;

	for(n = 1; ; ) {
		double x, y;
		double* xtmp, * ytmp;
		cerr << "(x y)=";
		cin >> x >> y;
		if(!cin) break;
		xtmp = new double[n];
		ytmp = new double[n];
		for(int i = 0; i < n - 1; i++) {
			xtmp[i] = xdata[i];
			ytmp[i] = ydata[i];
		}
		xtmp[n-1] = x;
		ytmp[n-1] = y;
		if(n > 1) {
			delete[] xdata;
			delete[] ydata;
		}
		xdata = xtmp;
		ydata = ytmp;
		n++;
	}
	n--;

	for(double x = min; x <= max; x += step) {
		cout << x << "\t" << spline(n, xdata, ydata, x) << endl;
	}
}
#endif /* M_DEBUG */
/*=============================================================================
	$Log: spline.cpp,v $
	Revision 1.2  1999/11/26 07:59:12  ikeda
	*** empty log message ***

	Revision 1.1  1999/11/26 07:48:55  ikeda
	Initial revision

=============================================================================*/
