#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define N 3
#define K 3
#define D 2

int main(int argc, char *argv[])
{
  int proc_rank, proc_count, recv_number;
  int numbers[N], dims[D] = {N, K}, periods[D] = {1, 0}, subdims[D] = {0, 1};
  MPI_Comm dekart, row_comm;

  for (int i = 0; i < N; i++) {
      numbers[i] = i;
  }

  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

  MPI_Cart_create(MPI_COMM_WORLD, D, dims, periods, 1, &dekart);

  MPI_Cart_sub(dekart, subdims, &row_comm);
 
  MPI_Scatter(&numbers, 1, MPI_INT, &recv_number, 1, MPI_INT, 0, row_comm);
  printf("\n process with rank %d got message %d", proc_rank, recv_number);

  MPI_Finalize();
  return 0;
}