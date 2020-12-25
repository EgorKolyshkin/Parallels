#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define K 5

int main(int argc, char *argv[])
{
  int proc_rank, proc_count;
  MPI_Status status;
  MPI_Group world_group, even_group;
  MPI_Comm even_comm;
  int even_ranks[K];
  int recv_number;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

  if (proc_count / 2 + (proc_count % 2) != K) {
      printf("\n Incorrect count of processes");
      return 1;
  }
  for (int i = 0; i < K; ++i) {
      even_ranks[i] = 2 * i;
  }
      
  MPI_Comm_group (MPI_COMM_WORLD, &world_group);
  MPI_Group_incl(world_group, K, even_ranks, &even_group);
  MPI_Comm_create(MPI_COMM_WORLD, even_group, &even_comm);
  if (proc_rank % 2 == 0) {
      MPI_Scatter(&even_ranks, 1, MPI_INT, &recv_number, 1, MPI_INT, 0, even_comm);
      printf("\n process with rank %d got message %d", proc_rank, recv_number);
  }
  MPI_Finalize();
  return 0;
}