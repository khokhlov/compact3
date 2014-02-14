// Author: Nikolay Khokhlov <k_h@inbox.ru>, <kolya.khokhlov@gmail.com>, (C) 2014

#include <stdio.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const double cfl = 0.2;
const double T = 2.0;
const int periods = 1;
const int n0 = 16;
const int S = 9;
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

void single_test(const int n, reconstruct r, err_t *err)
{
	data_t d, nd;
	integrate(n, r, &d);
	integrate(n, &none, &nd);
	initial_sin(T, &nd);
	err->l1 = L1(&d, &nd);
	err->l2 = L2(&d, &nd);
	err->linf = Linf(&d, &nd);
	free_data(&d, 1);
	free_data(&nd, 1);
}

void test(const char *name, reconstruct r)
{
	int i, n = n0;
	err_t *err = (err_t*)malloc(sizeof(err_t) * S);
	for (i = 0; i < S; i++) {
		single_test(n, r, &err[i]);
		n *= 2;
	}
	printf("%s\n", name);
	char latex[1000];
	sprintf(latex, "latex_%s", name);
	FILE *f  = fopen(name, "w");
	FILE *fl = fopen(latex, "w");
	n = n0;
	double t = (log(1.0 / 2.0) - log(1.0));
	for (i = 0; i < S; i++) {
		if (i > 0) {
			printf("%d\t%1.16f\t%f\t%1.16f\t%f\n", n, err[i].l1, (log(err[i].l1) - log(err[i-1].l1)) / t, err[i].linf, (log(err[i].linf) - log(err[i-1].linf)) / t);
			fprintf(f, "%d\t%1.16f\t%f\t%1.16f\t%f\n", n, err[i].l1, (log(err[i].l1) - log(err[i-1].l1)) / t, err[i].linf, (log(err[i].linf) - log(err[i-1].linf)) / t);
			fprintf(fl, "& %d & $\\num{%1.2e}$ & %1.2f & $\\num{%1.2e}$ & %1.2f\\\\\n", n, err[i].l1, (log(err[i].l1) - log(err[i-1].l1)) / t, err[i].linf, (log(err[i].linf) - log(err[i-1].linf)) / t);
		}
		else {
			printf("%d\t%1.16f\t-\t\t%1.16f\t-\n", n, err[i].l1, err[i].linf);
			fprintf(f, "%d\t%1.16f\t-\t\t%1.16f\t-\n", n, err[i].l1, err[i].linf);
			fprintf(fl, "& %d & $\\num{%1.2e}$ & - & $\\num{%1.2e}$ & -\\\\\n", n, err[i].l1, err[i].linf);
		}
		n *= 2;
	}
	printf("\n");
	fclose(f);
	fclose(fl);
	free(err);
}

int main(int argc, char *argv[])
{
	test("cir.txt", &cir);
	test("cip.txt", &cip);
	test("cip2l.txt", &cip2l);
	test("cip2r.txt", &cip2r);
	test("bis1.txt", &bis1);
	test("bis2.txt", &bis2);
	return 0;
}
