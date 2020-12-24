
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define N 10

void init_matrix(int m[N][N])
{
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      m[i][j] = rand() % 10000;
    }
  }
}

void print_matrix(int m[N][N])
{
  for (int i = 0; i < N; i++) {
    printf("\n");
    for (int j = 0; j < N; j++) {
      printf("%2d ", m[i][j]);
    }
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  int proc_rank, proc_count, i, size, A[N][N], B[N][N], C[N][N];
  size = N*N;
  MPI_Status status;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

  if (proc_rank==0) {
    init_matrix(A);
    init_matrix(B);
  }

  MPI_Bcast (B, size, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast (A, size, MPI_INT, 0, MPI_COMM_WORLD);

  for (i = 0; i<N; i++) {
    C[proc_rank][i] = A[proc_rank][i] + B[proc_rank][i];
  }

  MPI_Gather (C[proc_rank], size/proc_count, MPI_INT, C, size/proc_count, MPI_INT, 0, MPI_COMM_WORLD);

  if (proc_rank==0) {
    print_matrix(A);
    print_matrix(B);
    print_matrix(C);
  }

  MPI_Finalize();
  return 0;
}