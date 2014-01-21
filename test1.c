#include <stdio.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const int N = 200;
const double dt = 0.004;
const int periods = 2;

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
	printf("%s %f %f %f\n", path, L1(&d, &nd), L2(&d, &nd), Linf(&d, &nd));
	save_data(path, &d);
	free_data(&d, 1);
	free_data(&nd, 1);
}

int main(int argc, char *argv[])
{
	printf("path L1 L2 Linf\n");
	test("none.txt", &none);
	test("cir.txt", &cir);
	test("cip.txt", &cip);
	test("cip2l.txt", &cip2l);
	test("cip2r.txt", &cip2r);
	test("bis1.txt", &bis1);
	test("bis2.txt", &bis2);
	return 0;
}
