#include <stdio.h>
#include "mpi.h"
int main(int argc, char* argv[]){
int proc_count, proc_rank, recv_rank;
MPI_Status Status;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
if ( proc_rank == 0 ) {

for ( int i=1; i<proc_count; i++ ) {
 
	MPI_Send(&proc_rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

	printf("\n process %d send %d", recv_rank, proc_rank); 

	} 

	for ( int i=1; i<proc_count; i++ ) {
 
	MPI_Recv(&recv_rank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

	printf("\n process %d got %d", proc_rank, recv_rank); 

	} 
	
}
else {

	MPI_Recv(&recv_rank, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

	MPI_Send(&proc_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
	MPI_Finalize();
	return 0;
}