/* File:     mpi_trap1.c
 * Purpose:  Use MPI to implement a parallel version of the trapezoidal 
 *           rule.  In this version the endpoints of the interval and
 *           the number of trapezoids are hardwired.
 *
 * Input:    None.
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -g -Wall -o mpi_trap1 mpi_trap1.c
 * Run:      mpiexec -n <number of processes> ./mpi_trap1
 *
 * Algorithm:
 *    1.  Each process calculates "its" interval of
 *        integration.
 *    2.  Each process estimates the integral of f(x)
 *        over its interval using the trapezoidal rule.
 *    3a. Each process != 0 sends its integral to 0.
 *    3b. Process 0 sums the calculations received from
 *        the individual processes and prints the result.
 *
 * Note:  f(x), a, b, and n are all hardwired.
 *
 * IPP:   Section 3.2.2 (pp. 96 and ff.)
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>

void Build_mpi_type(double* a_p, double* b_p, int* n_p, MPI_Datatype* input_mpi_t_p);

/* Calculate local integral  */
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len);    

/* Function we're integrating */
double f(double x); 

void Get_input_pack(int my_rank, int comm_sz, double* a_p, double* b_p, int* n_p);

int main(void) {
   int my_rank, comm_sz, n, local_n;   
   double a, b, h, local_a, local_b;
   double local_int, total_int;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   Get_input_pack(my_rank, comm_sz, &a, &b, &n);

   h = (b-a)/n;          /* h is the same for all processes */
   local_n = n/comm_sz;  /* So is the number of trapezoids  */

   /* Length of each process' interval of
    * integration = local_n*h.  So my interval
    * starts at: */
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;
   local_int = Trap(local_a, local_b, local_n, h);

   /* Add up the integrals calculated by each process */
   MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,
         MPI_COMM_WORLD);

   /* Print the result */
   if (my_rank == 0) {
      printf("With n = %d trapezoids, our estimate\n", n);
      printf("of the integral from %f to %f = %.15e\n",
          a, b, total_int);
   }

   /* Shut down MPI */
   MPI_Finalize();

   return 0;
} /*  main  */

void Build_mpi_type(
      double*        a_p            /* in  */, 
      double*        b_p            /* in  */, 
      int*           n_p            /* in  */,
      MPI_Datatype*  input_mpi_t_p  /* out */) {

   int array_of_blocklengths[3] = {1, 1, 1};
   MPI_Datatype array_of_types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};
   MPI_Aint a_addr, b_addr, n_addr;
   MPI_Aint array_of_displacements[3] = {0};

   MPI_Get_address(a_p, &a_addr);
   MPI_Get_address(b_p, &b_addr);
   MPI_Get_address(n_p, &n_addr);
   array_of_displacements[1] = b_addr-a_addr; 
   array_of_displacements[2] = n_addr-a_addr; 
   MPI_Type_create_struct(3, array_of_blocklengths, 
         array_of_displacements, array_of_types,
         input_mpi_t_p);
   MPI_Type_commit(input_mpi_t_p);
} 

void Get_input_pack(int my_rank, int comm_sz, double* a_p, double* b_p, int* n_p) {
    char pack_buf[1000];
    if (my_rank == 0) {
        int position = 0;
        printf("Enter a, b, and n\n");
        scanf("%lf %lf %d", a_p, b_p, n_p);
        MPI_Pack(a_p, 1, MPI_DOUBLE, pack_buf, 1000, &position, MPI_COMM_WORLD);
        MPI_Pack(b_p, 1, MPI_DOUBLE, pack_buf, 1000, &position, MPI_COMM_WORLD);
        MPI_Pack(n_p, 1, MPI_INT, pack_buf, 1000, &position, MPI_COMM_WORLD);
    }
    int positionUnpack = 0;
    MPI_Bcast(pack_buf, 1000, MPI_PACKED, 0, MPI_COMM_WORLD);
    MPI_Unpack(pack_buf, 1000, &positionUnpack, a_p, 1, MPI_DOUBLE, MPI_COMM_WORLD);
    MPI_Unpack(pack_buf, 1000, &positionUnpack, b_p, 1, MPI_DOUBLE, MPI_COMM_WORLD);
    MPI_Unpack(pack_buf, 1000, &positionUnpack, n_p, 1, MPI_INT, MPI_COMM_WORLD);
} 
/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral 
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count 
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double Trap(double left_endpt  /* in */, double right_endpt /* in */, int trap_count  /* in */, double base_len    /* in */) 
{
	double estimate, x; 
	int i;

	estimate = (f(left_endpt) + f(right_endpt))/2.0;
	for (i = 1; i <= trap_count-1; i++) 
	{
	   x = left_endpt + i*base_len;
	   estimate += f(x);
	}
	estimate = estimate*base_len;

	return estimate;
} /*  Trap  */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) 
{
	return x*x;
} /* f */
