// Author: Nikolay Khokhlov <k_h@inbox.ru>, <kolya.khokhlov@gmail.com>, (C) 2014

#include <stdio.h>

#include "compact3.h"
#include "initial.h"
#include "norm.h"

const int N = 20;
const double dt = 0.5;

void integrate(reconstruct r, data_t *d)
{
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	create_simple_mesh(N, -10.0, 10.0, m);
	create_mesh_data(m, d);
	initial_godunovs_parabola(0.0, d);
	steps(1, 1.0, dt, d, r);
}

void test(const char *path, reconstruct r)
{
	data_t d;
	integrate(r, &d);
	save_data(path, &d);
	free_data(&d, 1);
}

int main(int argc, char *argv[])
{
	data_t d;
	mesh_t *m = (mesh_t*)malloc(sizeof(mesh_t));
	create_simple_mesh(N, -10.0, 10.0, m);
	create_mesh_data(m, &d);
	initial_godunovs_parabola(0.5, &d);
	save_data("godunov_theor.txt", &d);
	
	
	test("godunov_none.txt", &none);
	test("godunov_cir.txt", &cir);
	test("godunov_cip.txt", &cip);
	test("godunov_cip2l.txt", &cip2l);
	test("godunov_cip2r.txt", &cip2r);
	test("godunov_bis1.txt", &bis1);
	test("godunov_bis2.txt", &bis2);
	return 0;
}
