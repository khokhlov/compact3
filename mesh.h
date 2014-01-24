#ifndef MESH_H
#define MESH_H

#include <stdlib.h>
#include <math.h>

typedef struct {
	int size;
	double *x;
} mesh_t;

typedef double (*rfunc)(const int, const double, const int);
typedef void (*complex_mesh_func)(const int, const double, const double, const double, mesh_t *);

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

double r1(const int nx, const double alpha, const int i)
{
	int il = nx / 4;
	int nm = nx / 100;
	int ir = il + 20 * nm - 1;
	return (i >= il && i <= ir) ? alpha : 1.0;
}

double r2(const int nx, const double alpha, const int i)
{
	int il = nx / 4;
	int nm = nx / 100;
	int ir = il + 60 * nm - 1;
	return (i >= il && i <= ir) ? 1.0 + alpha * sin(2.0 * M_PI * (i - il) / (il - ir)) : 1.0;
}

void create_complex_mesh(const int size, const double x1, const double x2, const double alpha, rfunc rf, mesh_t *m)
{
	m->size = size;
	m->x = (double*)malloc(sizeof(double) * size);
	m->x[0] = x1;
	double r = 0.0;
	int i;
	for (i = 0; i < size; i++) {
		r += rf(size, alpha, i);
	}
	double h = (x2 - x1) / r;
	for (i = 0; i < size - 1; i++) {
		m->x[i + 1] = m->x[i] + h * rf(size, alpha, i);
	}
}

void create_mesh1(const int size, const double x1, const double x2, const double alpha, mesh_t *m)
{
	create_complex_mesh(size, x1, x2, alpha, &r1, m);
}

void create_mesh2(const int size, const double x1, const double x2, const double alpha, mesh_t *m)
{
	create_complex_mesh(size, x1, x2, alpha, &r2, m);
}

double rand1()
{
    return -1.0 + 2.0 * (double)rand() / (double)(RAND_MAX - 1);
}

void create_mesh3(const int size, const double x1, const double x2, const double alpha, mesh_t *m)
{
	m->size = size;
	m->x = (double*)malloc(sizeof(double) * size);
	m->x[0] = x1;
	double r = 0.0;
	double *ri = (double*)malloc(sizeof(double) * size);
	int i;
	for (i = 0; i < size; i++) {
		ri[i] = 1.0 + alpha * rand1();
		r += ri[i];
	}
	printf("%f\n", r);
	double h = (x2 - x1) / r;
	for (i = 0; i < size - 1; i++) {
		m->x[i + 1] = m->x[i] + h * ri[i];
	}
	free(ri);
}

void copy_mesh(const mesh_t *f, mesh_t *to)
{
	to->size = f->size;
	to->x = (double*)malloc(sizeof(double) * to->size);
	int i;
	for (i = 0; i < to->size; i++) {
		to->x[i] = f->x[i];
	}
}

void free_mesh(mesh_t *m)
{
	m->size = 0;
	free(m->x);
}

#endif // MESH_H
