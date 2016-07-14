#include <iostream.h>

#include "s2z.h"
#include "z2s.h"

double	SrcFs = 32000.0, DestFs = 44100.0;

double	a[3], b[3], c[3], d[3];

main()
{
	for(int i = 0; i <= 2; i++) {
		cout << "a" << i << "= ";
		cin >> a[i];
	}
	for(int i = 0; i <= 2; i++) {
		cout << "b" << i << "= ";
		cin >> b[i];
	}

	z2s(a, b, c, d, 2, 1.0/SrcFs);
	s2z(c, d, a, b, 2, 1.0/DestFs);

	for(int i = 0; i <= 2; i++) {
		cout << a[i] << endl;
	}
	for(int i = 0; i <= 2; i++) {
		cout << b[i] << endl;
	}
}
