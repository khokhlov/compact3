#include <stdio.h>

#include "compact3.h"
#include "initial.h"

int main(int argc, char *argv[])
{
	mesh_t m;
	data_t d;
	create_simple_mesh(201, -1.0, 1.0, &m);
	create_mesh_data(&m, &d);
	initial_complex(0.0, &d);
	steps(222, 1.0, 0.009, &d, &bis2);
	save_data("1.txt", &d);
	free_data(&d, 1);
	return 0;
}
