/*=============================================================================
	lagrange.cpp: Lagrange Interporation 
	$Header: /home/boss/ikeda/source/RCS/lagrange.cpp,v 1.1 1999/11/26 07:49:43 ikeda Exp $
=============================================================================*/
#include <math.h>

#include "lagrange.h"

/*----------------------------------------------------------------------------
	prog  : ikeda@roland.co.jp
	func  : Lagrange Interporation
	date  : Fri Nov 26 16:44:19 JST 1999
	update: 
	entry : n=Data Pair Num,
		xdata=X Data array pointer
		ydata=Y Data array pointer
		x=x
	return: y
	remks :
----------------------------------------------------------------------------*/
double lagrange(int n, double* xdata, double* ydata, double x)
{
	double y = 0.0;
	for(int i = 0; i < n; i++) {
		double tmp = ydata[i];
		for(int j = 0; j < n; j++) {
			if(i != j) {
				tmp *= (x - xdata[j]);
				tmp /= (xdata[i] - xdata[j]);
			}
		}
		y += tmp;
	}

	return y;
}

/*--------------------------------------------------------------------------*/
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

	for(double x = min; x <= max; x += step) {
		cout << x << "\t" << lagrange(n, xdata, ydata, x) << endl;
	}
}
#endif /* M_DEBUG */
/*=============================================================================
	$Log: lagrange.cpp,v $
	Revision 1.1  1999/11/26 07:49:43  ikeda
	Initial revision

=============================================================================*/
