// Author: Nikolay Khokhlov <k_h@inbox.ru>, <kolya.khokhlov@gmail.com>, (C) 2014

#ifndef NORM_H
#define NORM_H

#include <math.h>

#include "compact3.h"

double L1(data_t *d1, data_t *d2)
{
	// WARNING: no size check
	int i, N = d1->m->size;
	double n = 0.0;
	double ne = 0.0;
	for (i = 0; i < N; i++) {
		int i1 = ((i + N)-1) % N;
		double h = d1->m->x[i] - d1->m->x[i1];
		if (i == 0) {
			h = d1->m->x[1] - d1->m->x[0];
		}
		//printf("%f\n", dx);
		n += ABS(d1->u[i] - d2->u[i]) * h;
		ne += d2->u[i];
	}
	return n;
}

double L2(data_t *d1, data_t *d2)
{
	// WARNING: no size check
	int i, N = d1->m->size;
	double n = 0.0;
	double ne = 0.0;
	for (i = 0; i < N; i++) {
		int i1 = ((i + N)-1) % N;
		int i2 = ((i + N)+1) % N;
		double dx = (d1->m->x[i2] - d1->m->x[i1]) / 2.0;
		double du = d1->u[i] - d2->u[i];
		n += du * du;
		ne += d2->u[i];
	}
	return sqrt(n);
}

double Linf(data_t *d1, data_t *d2)
{
	// WARNING: no size check
	int i, N = d1->m->size;
	double n = 0.0;
	for (i = 0; i < N; i++) {
		double du = d1->u[i] - d2->u[i];
		double v = ABS(du);
		if (n < v) n = v;
	}
	return n;
}

double TV(data_t *d)
{
	int i, N = d->m->size;
	double tv = 0.0;
	for (i = 0; i < N; i++) {
		double du = d->u[(i + 1) % N] - d->u[i];
		tv += ABS(du);
	}
	return tv;
}

double sum(data_t *d)
{
	int i, N = d->m->size;
	double s = 0.0;
	for (i = 0; i < N; i++) {
		s += d->u[i];
	}
	return s;
}

#endif // NORM_H
