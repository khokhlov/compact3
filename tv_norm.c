// Author: Nikolay Khokhlov <k_h@inbox.ru>, <kolya.khokhlov@gmail.com>, (C) 2014

#include <stdio.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const double cfl = 0.4;
const double T = 1.0;
const int n0 = 100;


void single_test(const char *name, const int n, reconstruct r)
{
	printf("%s\n", name);
	FILE *f  = fopen(name, "w");
	data_t d;
	double dt = cfl * 2.0 / n;
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	create_simple_mesh(n, -1.0, 1.0, m);
	create_mesh_data(m, &d);
	initial_rect(0.0, &d);
	int i;
	for (i = 0; i < T / dt; i++) {
		double t = TV(&d);
		fprintf(f, "%d %f\n", i, t);
		step(1.0, dt, &d, r);
	}
	free_data(&d, 1);
	fclose(f);
}

int main(int argc, char *argv[])
{
	single_test("tv_cir.txt",  n0, &cir);
	single_test("tv_cip.txt",  n0, &cip);
	single_test("tv_bis1.txt", n0, &bis1);
	single_test("tv_bis2.txt", n0, &bis2);
	return 0;
}
