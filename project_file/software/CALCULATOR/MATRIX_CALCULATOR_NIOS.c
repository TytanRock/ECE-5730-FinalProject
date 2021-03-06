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
#include "stdio.h"
#include "math.h"
#include "stdint.h"
#include "io.h"
#include "altera_avalon_pio_regs.h"


void next_write()
{
	uint8_t *next;

	next = (uint8_t *)0x00021000;
//next = IORD_ALTERA_AVALON_PIO_DATA(0x00021020);
	*next = 0;

	for(volatile uint32_t i=0; i<500000;i++);
	*next = 1;
	for(volatile uint32_t i=0; i<500000;i++);
}

void writeByte(char c)
{
	char *toSend;
	toSend = (char *)0x00021010;
	*toSend = c;
}

void writeString(char* str, int len)
{
	for(int i = 0; i < len; ++i) {
		writeByte(str[i]);
		next_write();
	}
}


void next_from_pio()
{
	uint8_t *next;

	next = (uint8_t *)0x00021020;
//next = IORD_ALTERA_AVALON_PIO_DATA(0x00021020);
	*next = 0;

	for(volatile uint32_t i=0; i<500000;i++);
	*next = 1;
	for(volatile uint32_t i=0; i<500000;i++);
}


int decode_ascii() {

	int retval = 0;


	while(1) {
		char value = IORD_ALTERA_AVALON_PIO_DATA(0x00021030);
		printf("%c\n", value);
		if(value == ',') break;
		if(value >= '0' && value <= '9')
		{
			retval *= 10;
			retval += value-'0';
		}
		next_from_pio();

	}
	next_from_pio();

	return retval;
}


int main()
{ 

  int ROW1, ROW2, COL1, COL2;
  int **A;
  int **B ;
  int Determinant_A,Determinant_B;

  int OP_SEL;
  char str[100];

  int i,j,k;

 printf("entered main\n");
 writeString("Writing Uart", 13);

      ROW1= decode_ascii();
      COL1=decode_ascii();

//      ROW2=decode_ascii();
//      COL2=decode_ascii();

      printf("ROW1=%d\n",ROW1);
      printf("COL1=%d\n",COL1);
//      printf("ROW2=%d\n",ROW2);
//      printf("COL2=%d\n",COL2);



      OP_SEL=decode_ascii();
      switch(OP_SEL){
      case 1:
    	  sprintf(str,"\n sum is : %d",(ROW1+COL1));
    	  printf("%s",str);
    	  writeString(str,sizeof(str));
    	  break;
      case 2:
    	  sprintf(str,"difference is : %d",(ROW1-COL1));
    	  writeString(str,sizeof(str));
    	  break;
      case 3:
    	  sprintf(str,"product is : %d",(ROW1*COL1));
    	  writeString(str,sizeof(str));
    	   break;
      default:
    	  break;

      }



  free(A);
  free(B);
   return 0;
}
