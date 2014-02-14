// Author: Nikolay Khokhlov <k_h@inbox.ru>, <kolya.khokhlov@gmail.com>, (C) 2014

#include <stdio.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const int N = 200;
const double dt = 0.004;
int periods = 2;

void integrate(reconstruct r, data_t *d)
{
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	create_simple_mesh(N, -1.0, 1.0, m);
	create_mesh_data(m, d);
	initial_complex(0.0, d);
	steps(2.0 / dt * periods, 1.0, dt, d, r);
}

void test(const char *path, reconstruct r)
{
	data_t d, nd;
	integrate(r, &d);
	integrate(&none, &nd);
	printf("%s & %1.3f & %1.3f & %1.3f\\\\\n", path, L1(&d, &nd), L2(&d, &nd), Linf(&d, &nd));
	save_data(path, &d);
	free_data(&d, 1);
	free_data(&nd, 1);
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		periods = atoi(argv[1]);
	}
	test("none.txt", &none);
	printf("\\begin{tabular}{ c c c c c c c }\n");
	printf("& $L_1$ & $L_2$ & $L_{\\infty}$ \\\\\n");
	printf("\\hline\n");

	test("cir.txt", &cir);
	printf("\\hline\n");
	test("cip.txt", &cip);
	printf("\\hline\n");
	test("cip2l.txt", &cip2l);
	printf("\\hline\n");
	test("cip2r.txt", &cip2r);
	printf("\\hline\n");
	test("bis1.txt", &bis1);
	printf("\\hline\n");
	test("bis2.txt", &bis2);
	printf("\\hline\n");
	printf("\\end{tabular}\n");
	return 0;
}
