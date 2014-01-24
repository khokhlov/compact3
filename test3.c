#include <stdio.h>
#include <time.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const double cfl = 0.2;
const double T = 2.0;
const int periods = 1;
const int n0 = 100;
const int S = 5;
const int nsteps = 20000;

typedef struct {
	double l1, l2, linf;
} err_t;

void integrate(const int n, const double alpha, reconstruct r, complex_mesh_func cmf, data_t *d)
{
	double dt = cfl * 2.0 / n;
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	cmf(n, -1.0, 1.0, alpha, m);
	create_mesh_data(m, d);
	initial_sin4(0.0, d);
	steps(T / dt, 1.0, dt, d, r);
}

void single_test(const int n, const double alpha, reconstruct r, complex_mesh_func cmf, err_t *err)
{
	data_t d, nd;
	integrate(n, alpha, r, cmf, &d);
	save_data("bis2.txt", &d);
	copy_data(&d, &nd);
	initial_sin4(T, &nd);
	save_data("none.txt", &d);
	err->l1 = L1(&d, &nd);
	err->l2 = L2(&d, &nd);
	err->linf = Linf(&d, &nd);
	free_data(&d, 1);
	free_data(&nd, 1);
}

void test(const char *name, const double alpha, reconstruct r, complex_mesh_func cmf)
{
	int i, n = n0;
	err_t *err = (err_t*)malloc(sizeof(err_t) * S);
	for (i = 0; i < S; i++) {
		single_test(n, alpha, r, cmf, &err[i]);
		n *= 2;
	}
	printf("%s\n", name);
	FILE *f = fopen(name, "w");
	n = n0;
	double t = (log(1.0 / 2.0) - log(1.0));
	for (i = 0; i < S; i++) {
		if (i > 0) {
			printf("%d\t%1.16f\t%f\t%1.16f\t%f\n", n, err[i].l1, (log(err[i].l1) - log(err[i-1].l1)) / t, err[i].linf, (log(err[i].linf) - log(err[i-1].linf)) / t);
			fprintf(f, "%d\t%1.16f\t%f\t%1.16f\t%f\n", n, err[i].l1, (log(err[i].l1) - log(err[i-1].l1)) / t, err[i].linf, (log(err[i].linf) - log(err[i-1].linf)) / t);
		}
		else {
			printf("%d\t%1.16f\t-\t\t%1.16f\t-\n", n, err[i].l1, err[i].linf);
			fprintf(f, "%d\t%1.16f\t-\t\t%1.16f\t-\n", n, err[i].l1, err[i].linf);
		}
		n *= 2;
	}
	printf("\n");
	fclose(f);
	free(err);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int i;
	char buf[100];
	double a1[6] = {0.5, 1.0, 1.01, 1.05, 1.2, 1.5};
	double a2[5] = {0.0, 0.05, 0.2, 0.35, 0.5};
	double a3[4] = {0.01, 0.05, 0.1, 0.5};
	for (i = 0; i < 6; i++) {
		sprintf(buf, "case1_%f.txt", a1[i]);
		test(buf, a1[i], &bis2, &create_mesh1);
	}
	for (i = 0; i < 5; i++) {
		sprintf(buf, "case2_%f.txt", a2[i]);
		test(buf, a2[i], &bis2, &create_mesh2);
	}
	for (i = 0; i < 4; i++) {
		sprintf(buf, "case3_%f.txt", a3[i]);
		//test(buf, a3[i], &bis2, &create_mesh3);
	}
	return 0;
}
