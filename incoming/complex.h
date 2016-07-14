/*==========================================================================
	complex.h: 
	$Author$
	$Revision$
	$Date$
==========================================================================*/


/*****  Includes **********************************************************/

/*****  Definitions  ******************************************************/

/*****  Enums *************************************************************/

/*****  Typedefs  *********************************************************/

/*****  External Variables  ***********************************************/

/*****  Global Variables  *************************************************/

/*****  Static Variables  *************************************************/

class complex {
	double	re, im;
public:
	complex(double r, double i = 0)	{ re = r; im = i; }
	friend complex operator+(complex a, complex b);
	friend complex operator-(complex a, complex b);
	friend complex operator*(complex a, complex b);
	friend complex operator/(complex a, complex b);
	complex& operator+=(complex c);
	complex& operator-=(complex c);
	complex& operator*=(complex c);
	complex& operator*=(double c);
	complex& operator/=(complex c);
	complex& operator/=(double c);
};


inline complex operator+(complex a, complex b)
{
	return complex(a.re+b.re, a.im+b.im);
}


inline complex operator-(complex a, complex b)
{
	return complex(a.re-b.re, a.im-b.im);
}


inline complex operator*(complex a, complex b)
{
	return complex(a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re);
}

inline complex operator/(complex a, complex b)
{
	return complex((a.re*b.re + a.im*b.im)/(b.re*b.re - b.im*b.im),
			(a.im*b.re - a.re*b.im)/(b.re*b.re - b.im*b.im));
}

inline complex& operator+=(complex c)
{
	re += c.re;
	im += c.im;
	return *this;
}

inline complex& operator-=(complex c)
{
	re -= c.re;
	im -= c.im;
	return *this;
}

inline complex& operator*=(complex c)
{
	re *= c.re;
	re -= im*c.im;
	im *= c.re;
	im += re*c.im;
	return *this;
}


inline complex& operator*=(double c)
{
	re *= c;
	im *= c;
	return *this;
}


inline complex& operator/=(complex c)
{
	double mother = c.re*c.re - c.im*c.im;
	
	re *= c.re;
	re += im*c.im;
	re /= mother;

	im *= c.re;
	im -= re*c.im;
	im /= mother;

	return *this;
}


inline complex& operator/=(double c)
{
	re /= c;
	im /= c;
	return *this;
}

/*==========================================================================
	$Log$
==========================================================================*/
