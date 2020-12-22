#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]){
	int proc_num, proc_rank, recv_rank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

	if (proc_rank == 0) {
		MPI_Send(&proc_rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}

	while(1) {
		MPI_Recv(&recv_rank, 1, MPI_INT, MPI_ANY_SOURCE,
			MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("%3d throwed snowball to %3d\n", recv_rank, proc_rank);
		MPI_Send(&proc_rank, 1, MPI_INT, (proc_rank + 1) % proc_num, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
