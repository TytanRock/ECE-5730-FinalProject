/* 
 * "Small Hello World" example. 
 * 
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example 
 * designs. It requires a STDOUT  device in your system's hardware. 
 *
 * The purpose of this example is to demonstrate the smallest possible Hello 
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard 
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete 
 * description.
 * 
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION 
 *      This removes software exception handling, which means that you cannot 
 *      run code compiled for Nios II cpu with a hardware multiplier on a core 
 *      without a the multiply unit. Check the Nios II Software Developers 
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks  
 *      support for buffering, file IO, floating point and getch(), etc. 
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program 
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include "sys/alt_stdio.h"
#include "stdlib.h"

#define PIO_INPUT_ADDR (0x5000) // Change to match the input address of the PIO in the designer
#define PIO_NEXT_NUM_ADDR (0x5020)
#define READ_INPUT_FROM_PIO() (*(volatile int *)PIO_BASE_ADDR)
#define NEXT_NUM_FROM_PIO() (*(volatile int *)PIO_NEXT_NUM_ADDR) = 1

/**
 * @brief Adds to matrices together
 * 
 * @param a First matrix to add
 * @param b Second matrix to add
 * @param r1 Number of rows in a
 * @param c1 Number of columns in a
 * @param r2 Number of rows in b
 * @param c2 Number of columns in b
 */
void matrix_add(int** a, int** b, int r1, int c1, int r2, int c2)
{
	int i,j,k,l;
	int res[r1][c1];

	if (r1 != r2 || c1 != c2)
	{
		//display --> cannot be added
	}
	else
	{
		for (i=0;i<r1;i++)
		{
			for(j=0;j<c1;j++)
			{
				res[i][j]= a[i][j] + b[i][j];
			}
		}
	}

	for (i=0;i<r1;i++)
			{
				for(j=0;j<c1;j++)
				{
					//using lcd as output
				}
		//new line
	}

}

void matrix_sub(int** a, int** b, int r1, int c1, int r2, int c2)
{
	int i,j,k,l;
	int res[r1][c1];

	if (r1 != r2 || c1 != c2)
	{
		//display --->  cannot be subtracted
	}
	else
	{
		for (i=0;i<r1;i++)
		{
			for(j=0;j<c1;j++)
			{
				res[i][j]= a[i][j] - b[i][j];
			}
		}
	}

	for (i=0;i<r1;i++)
			{
				for(j=0;j<c1;j++)
				{
					//using lcd as output
				}

}

void scalar_matrix_mul (int **a, int r1, int c1)
{
	int i,j;
	int k;  // declare as float if needed 
	int res[r1][c1];
	
	for (i=0; i<r1; i++)
	{
		for (j=0;j<c1;j++)
		{
			res[i][j]=k*a[i][j];
		}
	}
	for (i=0;i<r1;i++)
		{
			for(j=0;j<c1;j++)
				{
					//using lcd as output
				}
		}
	
void matrix_mul(int** a, int** b, int r1, int c1, int r2, int c2)

{
	int i,j,k,l,m;
	int res[r1][c2];
	if(r1 != c2)
	{
		//display---> not possible
	}
	else
	{
		for (i=0;i<r1;i++)
		{
			for(j=0;j<c2;j++)
			{
				res[i][j]=0;
				for(m=0;m<c1;m++)
				{
					res[i][j]=res[i][j]+ (a[i][m] * b[m][j]);
				}
			}

		}
	}
	for (i=0;i<r1;i++)
	{
		for(j=0;j<c1;j++)
			{
			//using lcd as output
			}
	}
}
	
void matrix_transpose(int **a, int r1, int c1);
	{
		int i,j;
		int res[r1][c1];
		
		for (i=0; i<c1;i++)
		{
			for (j=0;j<r1;j++)
			{ 
				res[i][j]= a[j][i];
			}
		}
		for (i=0;i<c1;i++)
		{
			for(j=0;j<r1;j++)
				{
					//using lcd as output
				}
		}
	}

void matrix_det(int** a, int r2, int c2)
{
    int D = 0; // Initialize result
 int n;
    //  Base case : if matrix contains single element
    if(r1!=c1)
    {
     //not possible to find determinant
    }
    else
    {
    	n=r1;
    	if (n == 1)
    	        return a[0][0];

    	    int temp[n][n]; // To store cofactors

    	    int sign = 1; // To store sign multiplier

    	    // Iterate for each element of first row
    	    for (int f = 0; f < n; f++)
    	    {
    	        // Getting Cofactor of mat[0][f]
    	        getCofactor(a, temp, 0, f, n);
    	        D += sign * a[0][f]
    	             * matrix_det(temp, n - 1);

    	        // terms are to be added with alternate sign
    	        sign = -sign;
    	    }

    	    //display  D;
    }

}

void getCofactor(int mat[N][N], int temp[N][N], int p,
                 int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void *DISP_VAL;// variable to store value to be displayed on lcd
int *RD_VAL;
#define N=100;
int main()
{ 
  int ROW1, ROW2, COL1, COL2;
  int **A;
  int **B ;

  char OP_SEL; //can be converted to integer


  int i,j,k;
  while(1)
  {
	  //reading row and column size for matrix A and B
	  // Read the row, column size of matrix 1 and matrix 2 from the FPGA PIO layer.
      RD_VAL = READ_INPUT_FROM_PIO();
      ROW1=*RD_VAL;
	  NEXT_NUM_FROM_PIO();
      RD_VAL=READ_INPUT_FROM_PIO();
      COL1=*RD_VAL;
	  NEXT_NUM_FROM_PIO();
      RD_VAL=READ_INPUT_FROM_PIO();
      ROW2=*RD_VAL;
	  NEXT_NUM_FROM_PIO();
      RD_VAL=READ_INPUT_FROM_PIO();
      COL2=*RD_VAL;

      //reading values into matrix A and B
      //allocating memory
      A= malloc(ROW1*sizeof*A);
      for (i=0; i< ROWS1; i++)
      {
    	  A[i]= malloc(COL1*sizeof*A[i]);
      }

      B= malloc(ROW2*sizeof*B);
            for (i=0; i< ROWS2; i++)
            {
          	  B[i]= malloc(COL2*sizeof*B[i]);
            }

      for (i=0;i<ROW1; i++)
      {
    	  for(j=0;j<COL1;j++)
    	  {
    		  RD_VAL=READ_INPUT_FROM_PIO(); //is this going to work?
    		  NEXT_NUM_FROM_PIO();
    		  A[i][j]=*RD_VAL;
    	  }
      }
      for (i=0;i<ROW2; i++)
            {
         	  for(j=0;j<COL2;j++)
         	  {
         		  RD_VAL=READ_INPUT_FROM_PIO();
         		  NEXT_NUM_FROM_PIO();
         		  B[i][j]=*RD_VAL;
         	  }
           }
       //selecting operator
      RD_VAL=(char *)0x00011010;
      OP_SEL=*RD_VAL;

    switch (OP_SEL){
    case '+':
    	matrix_add(A,B,ROW1,COL1, ROW2,COL2);
    	break;
    case '-':
    	matrix_sub(A,B,ROW1,COL1, ROW2,COL2);
    	break;
    case 's'
	scalar_matrix_mul(A,ROW1,COL1);
	break;
    case '*':
    	matrix_mul(A,B,ROW1,COL1, ROW2,COL2);
    	break;
    case 't':
	martix_tanspose(A,ROW1,COL1);
	break;		    
    case 'd':
    	matrix_det(A,ROW1,COL1);
    	matrix_det(B,ROW1,COL1);
    	break;
    default:
    	break;

  }
  }

  free(A);
  free(B);
   return 0;
}
