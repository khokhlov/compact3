#ifndef MESH_H
#define MESH_H

#include <stdlib.h>

typedef struct {
	int size;
	double *x;
} mesh_t;

void create_simple_mesh(const int size, const double x1, const double x2, mesh_t *m)
{
	m->size = size;
	m->x = (double*)malloc(sizeof(double) * size);
	m->x[0] = x1;
	double h = (x2 - x1) / (size);
	int i;
	for (i = 0; i < size - 1; i++) {
		m->x[i + 1] = m->x[i] + h;
	}
}

void free_mesh(mesh_t *m)
{
	m->size = 0;
	free(m->x);
}

#endif // MESH_H
