#ifndef INITIAL_H
#define INITIAL_H

#include <math.h>

#include "compact3.h"

void initial_rect(const double st, data_t *d)
{
	int i;
	for (i = 0; i < d->m->size; i++) {
		double x = d->m->x[i] - st;
		if (x > -0.9 && x < -0.8) {
			d->u[i] = 1.0;
		} else {
			d->u[i] = 0.0;
		}
		d->v[i] = 0.0;
	}
}

void initial_complex(const double st, data_t *d)
{
	int i;
	for (i = 0; i < d->m->size; i++) {
		double x = d->m->x[i] - st;
		double u = 0.0, v = 0.0;
		if (x >= -0.8 && x <= -0.6) {
			double sq = x + 0.7;
			u = exp(-log(2.0) * sq * sq / 0.0009);
			v = -1540.33 * exp(-770.164 * sq * sq) * sq;
		} else if (x >= -0.4 && x <= -0.2) {
			u = 1.0;
		} else if (x >= 0 && x <= 0.2) {
			u = 1.0 - ABS(10.0 * (x - 0.1));
			v = (x >= 0.1 ? 10.0 : -10.0);
		} else if (x >= 0.4 && x <= 0.6) {
			double sq = x - 0.5;
			u = sqrt(1.0 - 100 * sq * sq);
			v = -(100.0 * sq / sqrt(1.0 - 100.0 * sq * sq));
			if (v < -100.0) v = -100.0;
			if (v > 100.0) v = 100.0;
		}
		d->u[i] = u;
		d->v[i] = v;
	}
}

#endif // INITIAL_H
