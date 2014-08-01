/****************************************************************
* Sieve Sift                                                                                  
*  Author: Michael Carpenter
*  Date: October 12, 2012
*
* 
******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>


int prime_test(unsigned long number) {
  unsigned long upper_bound = 0, remainder = 0, divisor = 3;

  if ((number % 2) == 0)
    return(0);

  upper_bound = (unsigned long)sqrt((double)number);

  while (divisor <= upper_bound) {
    remainder = number % divisor;

    if (remainder == 0)
      return(0);

    divisor += 2;
  }
  return(1);
}

void partition(unsigned int rank, unsigned long world_size, unsigned long problem_head, unsigned long problem_length) {
  unsigned long partition_size    = 0;
  unsigned long partition_head    = 0;
  unsigned long partition_length  = 0; 
  
  partition_size = floor (((problem_length - problem_head) + 1) / world_size);
  partition_head = rank * partition_size;
  partition_length = partition_head + partition_size;
 
  problem_head = partition_head;
  problem_length = partition_length; 
}

int main(int argc, char *argv[]) {
  //Initialize a bunch of relavent variables. They will be set later, but for now 0 is fine.
	unsigned int rank                     = 0;
  unsigned int world_size               = 0;
  const int SERVER                      = 0;
  
  //Initializing the variables keeping track of the problem size.
  unsigned long problem_size            = 0;
  unsigned long problem_head            = 3; //problem_head is the starting point of the local list. 
  unsigned long problem_length          = 0; //problem_length is the length of the local list of ints. 
  unsigned long x                       = 0; //counter will be our current place in the local list. 
  
  //We want the number of primes, not the primes themselves. A global and local prime counter will be used.
  unsigned long global_primes           = 2; //Global for the head node. 
  unsigned long local_primes            = 0; //Local for the child nodes.
  
  //We will be taking the wall time in seconds and milliseconds. Doubles will do.
  double start_time                     = 0.0;
  double end_time                       = 0.0;
  double start_work                     = 0.0;
  double end_work                       = 0.0;
  double total_work                     = 0.0;
  double work                           = 0.0;
  double start_waste                    = 0.0;
  double end_waste                      = 0.0;
  double waste                          = 0.0;
  double total_waste                    = 0.0;

  //Start up MPI :)
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //Destroy sense of community - establish the patriarchy, create the hierarchy, and assign every node a rank.
	MPI_Comm_size(MPI_COMM_WORLD, &world_size); //Lets see what we're workin' with - how many nodes are there.
 
  problem_size    = 50000000;
  problem_length  = 50000000; //Hard-coded problem set for now.
  
  if (rank == SERVER)
    start_time = MPI_Wtime();
  
  partition(rank, world_size, problem_head, problem_length);
 
  //There should be a second partition in order to perform load balancing without the overhead.

  fprintf(stderr, "Between %lu and %lu\n",
      problem_head, problem_length);

  start_work = MPI_Wtime();
  for (x = problem_head; x < problem_length; x++)
   local_primes += prime_test(x);
  end_work = MPI_Wtime();
  total_work = end_work - start_work; 
   
  start_waste = MPI_Wtime();
  MPI_Reduce(&local_primes, &global_primes, 1, MPI_UNSIGNED_LONG,
      MPI_SUM, SERVER, MPI_COMM_WORLD);
  end_waste = MPI_Wtime();

  MPI_Reduce(&total_waste, &waste, 1, MPI_DOUBLE,
     MPI_SUM, SERVER, MPI_COMM_WORLD);

  MPI_Reduce(&total_work, &work, 1, MPI_DOUBLE,
      MPI_SUM, SERVER, MPI_COMM_WORLD);
  
  if (rank == SERVER) {
    end_time = MPI_Wtime();
    total_waste = (waste / world_size);
    total_work = (work / world_size);
    fprintf(stderr, "%lu primes between 1 and %lu, average work time %.2f, average time wasted %.2f, wall time = %.2f seconds\n",
        global_primes, problem_size, total_work, total_waste, end_time - start_time);
  }

  MPI_Finalize();
  return(EXIT_SUCCESS);
}
