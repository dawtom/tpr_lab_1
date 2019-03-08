#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    double t1, t2;
    // We are assuming at least 2 processes for this task
    if (world_size < 2) {
        fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    char * text = malloc(1000000 * sizeof(char));
//  SENDER
    if (world_rank == 0) {
        int i;
	for (i = 0; i < 10000; i++) {
            strcat(text, "Miala baba koguta, wsadzila go do butaMiala baba koguta, wsadzila go do butaMiala baba koguta");
        }
        t1 = MPI_Wtime();
        MPI_Ssend(text, 1000000, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_BARRIER(MPI_COMM_WORLD);
        t2 = MPI_Wtime();
        printf("Time: %1.2f\n", t2-t1);
    } else
//    RECEIVER
    if (world_rank == 1) {
        MPI_Recv(text, 1000000, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_BARRIER(MPI_COMM_WORLD);
        printf("Process 1 received text from process 0\n");
    }
    MPI_Finalize();
    return 0;

}
