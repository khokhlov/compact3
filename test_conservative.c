// Author: Nikolay Khokhlov <k_h@inbox.ru>, <kolya.khokhlov@gmail.com>, (C) 2014

#include <stdio.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const double cfl = 0.4;
const double T = 100.0;
const int n0 = 200;


void single_test(const char *name, const char *name2, const int n, reconstruct r)
{
	printf("%s\n", name);
	FILE *f  = fopen(name, "w");
	data_t d;
	double dt = cfl * 2.0 / n;
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	create_simple_mesh(n, -1.0, 1.0, m);
	create_mesh_data(m, &d);
	initial_rect3(0.0, &d);
	int i;
	for (i = 0; i < T / dt; i++) {
		double t = sum(&d);
		if (i % 1000 == 0) fprintf(f, "%f %f\n", i * dt / 0.2, t / 20.0 * 100);
		step(1.0, dt, &d, r);
	}
	save_data(name2, &d);
	free_data(&d, 1);
	fclose(f);
}

int main(int argc, char *argv[])
{
	single_test("cons_none.txt", "cons_none_2.txt", n0, &none);
	single_test("cons_cir.txt",  "cons_cir_2.txt",  n0, &cir);
	single_test("cons_cip.txt",  "cons_cip_2.txt",  n0, &cip);
	single_test("cons_bis1.txt", "cons_bis1_2.txt", n0, &bis1);
	single_test("cons_bis2.txt", "cons_bis2_2.txt", n0, &bis2);
	return 0;
}
