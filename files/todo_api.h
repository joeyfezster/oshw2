/*
 * todo_api.h
 */
#include <errno.h>
#include <sys/types.h>

int add_TODO(pid_t pid, const char *TODO_description, ssize_t description_size)
 {
	 int res;
	 __asm__
		(
		 "pushl %%eax;"
		 "pushl %%ebx;"
		 "pushl %%ecx;"
		 "pushl %%edx;"
		 "movl $243, %%eax;"
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
		 : "m" (pid) ,"m" (TODO_description) ,"m"(description_size)
		 );
	 if (res >= (unsigned long)(-125))
	 {
		 errno = -res;
		 res = -1;
	 }
	 return (int) res;
 }
 
 ssize_t read_TODO(pid_t pid, int TODO_index, char *TODO_description, ssize_t description_size, int* status)
 {
	 int res;
	 __asm__
		(
		 "pushl %%eax;"
		 "pushl %%ebx;"
		 "pushl %%ecx;"
		 "pushl %%edx;"
		 "pushl %%esi;"
		 "pushl %%edi;"
		 "movl $244, %%eax;"
		 "movl %1, %%ebx;"
		 "movl %2, %%ecx;"
		 "movl %3, %%edx;"
		 "movl %4, %%esi;"
		 "movl %5, %%edi;"
		 "int $0x80;"
		 "movl %%eax,%0;"
		 "popl %%edi;"
		 "popl %%esi;"
		 "popl %%edx;"
		 "popl %%ecx;"
		 "popl %%ebx;"
		 "popl %%eax;"
		 : "=m" (res)
		 : "m" (pid) ,"m" (TODO_index) ,"m"(TODO_description) ,"m"(description_size) ,"m"(status)
		 );
	 if (res >= (unsigned long)(-125))
	 {
		 errno = -res;
		 res = -1;
	 }
	 return (int) res;
 }
 
 int mark_TODO(pid_t pid, int TODO_index, int status)
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
		 : "m" (pid) ,"m" (TODO_index) ,"m"(status)
		 );
	 if (res >= (unsigned long)(-125))
	 {
		 errno = -res;
		 res = -1;
	 }
	 return (int) res;
 }
 
int delete_TODO(pid_t pid, int TODO_index)
 {
	 int res;
	 __asm__
		(
		 "pushl %%eax;"
		 "pushl %%ecx;"
		 "pushl %%edx;"
		 "movl $246, %%eax;"
		 "int $0x80;"
		 "movl %%eax,%0;"
		 "popl %%ecx;"
		 "popl %%ebx;"
		 "popl %%eax;"		 
		 : "=m" (res)
		 : "m"(pid) ,"m"(TODO_index)
		 );
	 if (res >= (unsigned long)(-125))
	 {
		 errno = -res;
		 res = -1;
	 }
	 return (int) res;
 }
 
int sanity_test(void)
 {
	 int res;
	 __asm__
		(
		 "pushl %%eax;"
		 "movl $247, %%eax;"
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

