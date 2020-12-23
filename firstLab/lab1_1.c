#include <stdio.h>
#include "mpi.h"
#include "time.h"

int main(int argc, char* argv[]){
	int proc_num, proc_rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	int ITERATIONS = atoi(argv[1]);
	int COUNT = atoi(argv[2]);
	int data[COUNT];
	int recv_data[COUNT];
	int is_last_rank = proc_rank == (proc_num - 1);
	int is_first_rank = proc_rank == 0;
	clock_t before = clock();
	for (int i = 0; i < ITERATIONS; ++i) {
		int is_last_iteration = i == (ITERATIONS - 1);
		if (is_last_iteration && is_last_rank) {
			break;
		}
		int target_ix = (proc_rank + 1) % proc_num;
		MPI_Send(&data, COUNT, MPI_INT, target_ix, 0, MPI_COMM_WORLD);
		printf("\n %3d sent data to %3d", proc_rank, target_ix);
		if (is_last_iteration && is_first_rank) {
			break;
		}
		MPI_Recv(&recv_data, COUNT, MPI_INT, MPI_ANY_SOURCE,
			MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("\n %3d received data", proc_rank);
	}
	MPI_Finalize();
	return 0;
}
