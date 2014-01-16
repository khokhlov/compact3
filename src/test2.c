#include <stdio.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const double cfl = 0.2;
const double T = 2.0;
const int periods = 1;
const int n0 = 10;
const int S = 10;
const int nsteps = 20000;

typedef struct {
	double l1, l2, linf;
} err_t;

void integrate(const int n, reconstruct r, data_t *d)
{
	double dt = cfl * 2.0 / n;
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	create_simple_mesh(n, -1.0, 1.0, m);
	create_mesh_data(m, d);
	initial_sin(0.0, d);
	steps(T / dt, 1.0, dt, d, r);
}

void save_theoretical(const char *name, const int n)
{
	data_t nd;
	integrate(n, &none, &nd);
	initial_sin(T, &nd);
	save_data(name, &nd);
	free_data(&nd, 1);
}

void single_test(const char *name, const int n, reconstruct r, err_t *err)
{
	data_t d, nd;
	integrate(n, r, &d);
	integrate(n, &none, &nd);
	initial_sin(T, &nd);
	err->l1 = L1(&d, &nd) * 2.0 / n;
	err->l2 = L2(&d, &nd) * 2.0 / n;
	err->linf = Linf(&d, &nd);
	save_data(name, &d);
	free_data(&d, 1);
	free_data(&nd, 1);
}

void test(const char *name, reconstruct r)
{
	int i, n = n0;
	err_t *err = (err_t*)malloc(sizeof(err_t) * S);
	for (i = 0; i < S; i++) {
		single_test(name, n, r, &err[i]);
		save_theoretical("none.txt", n);
		n *= 2;
	}
	printf("%s\n", name);
	n = n0;
	double t = (log(1.0 / n / 2.0) - log(1.0 / n));
	for (i = 0; i < S; i++) {
		if (i > 0) printf("%d\t%1.16f\t%f\n", n, err[i].l1, (log(err[i].l1) - log(err[i-1].l1)) / t);
		else       printf("%d\t%1.16f\t-\n", n, err[i].l1);
		n *= 2;
	}
	printf("\n");
	free(err);
}

int main(int argc, char *argv[])
{
	//test("none.txt", &none);
	test("cir.txt", &cir);
	test("cip.txt", &cip);
	test("cip2l.txt", &cip2l);
	test("cip2r.txt", &cip2r);
	test("bis1.txt", &bis1);
	test("bis2.txt", &bis2);
	return 0;
}
