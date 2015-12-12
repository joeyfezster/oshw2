/*
 * todo_api.h
 */
#include <linux/errno.h>

int send_mpi_message(int rank, const char *message, ssize_t message_size)
 {
	 int res;
	 __asm__
		(
		 "pushl %%eax;"
		 "pushl %%ebx;"
		 "pushl %%ecx;"
		 "pushl %%edx;"
		 "movl $244, %%eax;"
		 "movl %1, %%ebx;"
		 "movl %2, %%ecx;"
		 "movl %3, %%edx;"
		 "int $0x80;"
		 "movl %%eax,%0;"
		 "popl %%edx;"
		 "popl %%ecx;"
		 "popl %%ebx;"
		 "popl %%eax;"
		 : "=m" (res)
		 : "m" (rank) ,"m" (message) ,"m"(message_size)
		 );
	 if (res >= (unsigned long)(-125))
	 {
		 errno = -res;
		 res = -1;
	 }
	 return (int) res;
 }
 
 int receive_mpi_message(int rank, char *message, ssize_t message_size)
 {
	 int res;
	 __asm__
		(
		 "pushl %%eax;"
		 "pushl %%ebx;"
		 "pushl %%ecx;"
		 "pushl %%edx;"
		 "movl $245, %%eax;"
		 "movl %1, %%ebx;"
		 "movl %2, %%ecx;"
		 "movl %3, %%edx;"
		 "int $0x80;"
		 "movl %%eax,%0;"
		 "popl %%edx;"
		 "popl %%ecx;"
		 "popl %%ebx;"
		 "popl %%eax;"
		 : "=m" (res)
		 : "m" (rank) ,"m" (message) ,"m"(message_size)
		 );
	 if (res >= (unsigned long)(-125))
	 {
		 errno = -res;
		 res = -1;
	 }
	 return (int) res;
 }
 
int register_mpi(void)
 {
	 int res;
	 __asm__
		(
		 "pushl %%eax;"
		 "movl $243, %%eax;"
		 "int $0x80;"
		 "movl %%eax,%0;"
		 : "=m" (res)
		 );
	 if (res >= (unsigned long)(-125))
	 {
		 errno = -res;
		 res = -1;
	 }
	 return (int) res;
 }
