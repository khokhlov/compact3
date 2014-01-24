// Author: Nikolay Khokhlov <k_h@inbox.ru>, <kolya.khokhlov@gmail.com>, (C) 2014

#ifndef COMPACT3_H
#define COMPACT3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schema.h"
#include "mesh.h"

typedef struct {
	double *u;
	double *v;
	mesh_t *m;
} data_t;

void create_mesh_data(mesh_t *m, data_t *d)
{
	d->m = m;
	d->u = (double*)calloc(m->size, sizeof(double));
	d->v = (double*)calloc(m->size, sizeof(double));
}

void copy_data(const data_t *f, data_t *t)
{
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	copy_mesh(f->m, m);
	t->m = m;
	t->u = (double*)calloc(m->size, sizeof(double));
	t->v = (double*)calloc(m->size, sizeof(double));
	memcpy(t->u, f->u, m->size * sizeof(double));
	memcpy(t->v, f->v, m->size * sizeof(double));
}


void free_data(data_t *d, int free_mesh_flag)
{
	free(d->u);
	free(d->v);
	if (free_mesh_flag) {
		free_mesh(d->m);
	}
}

void save_data(const char *path, data_t *d)
{
	FILE *f;
	int i;
	f = fopen(path, "w");
	for (i = 0; i < d->m->size; i++) {
		fprintf(f, "%f\t%f\t%f\n", d->m->x[i], d->u[i], d->v[i]);
	}
	fclose(f);
}

/**
 * Do single time step.
 */
void step(const double la, const double dt, data_t *d, reconstruct r)
{
	int i;
	int N = d->m->size;
	double u0, u1 = d->u[N - 1], v0, v1 = d->v[N - 1], t;
	double *x = d->m->x;
	for (i = 0; i < N; i++) {
		int i1 = ((i + N)-1) % N;
		double h = x[i] - x[i1];
		if (i == 0) {
			h = x[1] - x[0];
		}
		u0 = d->u[i];
		v0 = d->v[i];
		r(la, h, dt, u1, u0, v1, v0, d->u + i, d->v + i);
		v1 = v0;
		u1 = u0;
	}
}

void steps(const int N, const double la, const double dt, data_t *d, reconstruct r)
{
	int i;
	for (i = 0; i < N; i++) {
		step(la, dt, d, r);
	}
}

#endif // COMPACT3_H
