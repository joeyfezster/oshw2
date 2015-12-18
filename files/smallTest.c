#include "todo_api.h"
#include <stdio.h>

#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/list.h>  /* Needed by all modules */
#include <linux/types.h>  /* Needed for KERN_ALERT */
#include <linux/unistd.h>  /* Needed for KERN_ALERT */
#include <sys/types.h>
#include <sys/wait.h>

//C hello world example
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>     /* malloc, free, rand */


void checkResult( int returnValue , int expectedReturnValue, int expectedError, const char* testName ) {
	
	int errsv = errno;
	if (returnValue != expectedReturnValue) {
		printf("checkResult failed, wrong return value - %d, %s\n", returnValue, testName);
	}

	if (returnValue == expectedReturnValue && returnValue == -1) {
		if (errsv != expectedError) {
			printf("checkResult failed, wrong error value - %s\n", testName);
		}
	}

	
}

void testPrint(char* str){
	printf(str);
	fflush(stdout);
}

void checkStatus (int one, int two,const char* testName) {
	if (one != two) {
		printf("Check number %s failed, wrong returned status\n", testName);
	}
}

void checkDesc (char* one, char* two, const char* testName) {
	if (strcmp(one, two) != 0) {
		printf("checkDesc failed - %s\n", testName);
	}
}


int main()
{
	int sizeOfReadBuffer = 80;
	int descLength = 13;
	printf("\n---STARTED RUNNING TESTS---\n");
	pid_t myPid = getpid();
	printf("1,");
	int* pStatus = (int*) malloc (sizeof(int));
	testPrint("2,");
	char* pDesc = (char*) malloc (sizeof(char)*sizeOfReadBuffer);	
	printf("3,");
	char str1[40] = "Description_1";
	printf("4,");
	char str2[40] = "Description_2";
	printf("5,");
	char str3[40] = "Description_3";
	printf("6,");
	char str4[40] = "Description_4";

	// CHECK ALL FUNCTIONALITY, SINGLE PROCESS
	printf("7!\n");
	fflush(stdout);
	//if (1 == 1) {

	printf("\n-Running single process checks-\n");

	//Basic test, noy joey
	// checkResult(add_TODO(myPid, str1, descLength) , 0 , 0, "add1");
	// checkResult(read_TODO(myPid, 1, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 1st element");
	
	/**
	 READ THE NEWLY CREATED TODOQUEUE, MAKE SURE IT IS EMPTY
	**/	
	
	// testPrint("2.1,");
	// checkResult(read_TODO(myPid, 1, pDesc, sizeOfReadBuffer, pStatus) , -1 , EINVAL, "read 1st element of empty queue, invalid index");	

	
	// /**
	 // ADDING CHECKS, SINGLE PROCESS
	// **/

	
	// // adding 3 todos - should work
	// testPrint("2.2,");
	// checkResult(add_TODO(myPid, str1, descLength) , 0 , 0, "add1");
	
	// testPrint("2.3,");
	// checkResult(add_TODO(myPid, str2, descLength) , 0 , 0, "add2");	

	// testPrint("2.4,");
	// checkResult(add_TODO(myPid, str3, descLength) , 0 , 0, "add3");		

	// // adding to a non-valid pid
	// testPrint("2.5,");
	// checkResult(add_TODO(myPid*2, str4, descLength) , -1 , ESRCH, "add non valid pid");	
	
	// // adding a huge desc, expecting mem allocation failing
	// testPrint("2.6,");
	// checkResult(add_TODO(myPid, str4, 10000000) , -1 , ENOMEM, "add way too long desc");	
	
	// // adding null desc
	// testPrint("2.7,");
	// checkResult(add_TODO(myPid, NULL, descLength) , -1 , EINVAL, "add NULL description");	
	// //checkResult(add_TODO(myPid, NULL, descLength) , -1 , EFAULT, "add NULL description2");	

	// // adding short sized desc
	// testPrint("2.8,");
	// checkResult(add_TODO(myPid, str3, 0) , -1 , EINVAL, "add 0 length description");	
	// testPrint("2.9,");
	// checkResult(add_TODO(myPid, str3, -1) , -1 , EINVAL, "add -1 length description");	

	

	
	/**
	 READING CHECKS, SINGLE PROCESS
	**/

	
	// reading the second todo, checking status & desc
	// testPrint("2.10!\n");
	// checkResult(read_TODO(myPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 2nd element");	
	// checkResult(read_TODO(myPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 2nd element");	
	// testPrint("2.11,");
	// checkStatus (*pStatus, 0, "read 2nd element");
	// testPrint("2.12,");
	// checkDesc (pDesc, str2, "read 2nd element");

	// // reading the second todo, wrong pid
	// testPrint("2.13,");
	// checkResult(read_TODO(myPid*3, 2, pDesc, sizeOfReadBuffer, pStatus) , -1 , ESRCH, "read 2nd element, wrong pid");	

	// // reading the second todo, short buffer
	// testPrint("2.14,");
	// checkResult(read_TODO(myPid, 2, pDesc, descLength - 3, pStatus) , -1 , EINVAL, "read 2nd element, short buff");	
	
	
	
	// // reading the second todo, invalid index
	// testPrint("2.15,");
	// checkResult(read_TODO(myPid, -5, pDesc, sizeOfReadBuffer, pStatus) , -1 , EINVAL, "read -5th element, invalid index");	
	// // reading the second todo, null pDesc
	// testPrint("2.16,");
	// checkResult(read_TODO(myPid, 2, NULL, sizeOfReadBuffer, pStatus) , -1 , EINVAL, "read 2nd element, NULL pDesc");	


	// /**
	 // MARKING CHECKS, SINGLE PROCESS
	// **/
	
	// // marking the second todo, then reading ,checking status & desc
	// testPrint("2.17,");
	// checkResult(mark_TODO(myPid, 2, 5) , 0 , 0, "mark 2nd element as 5");	
	
	// testPrint("2.18,");
	// checkResult(read_TODO(myPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read after mark 2nd element");	
	// testPrint("2.19,");
	// checkStatus (*pStatus, 5, "read after mark 2nd element");
	// testPrint("2.20!\n");
	// checkDesc (pDesc, str2, "read after mark 2nd element");

	// testPrint("2.21,");
	// checkResult(mark_TODO(myPid, 3, 9) , 0 , 0, "mark 3rd element as 9");	
	
	// testPrint("2.22,");
	// checkResult(read_TODO(myPid, 3, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read after mark 3rd element");	
	// testPrint("2.23,");
	// checkStatus (*pStatus, 9, "read after mark 3rd element");
	// testPrint("2.24,");
	// checkDesc (pDesc, str3, "read after mark 3rd element");


	// checkResult(read_TODO(myPid, 1, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read after mark 3rd element");	
	// testPrint("2.25,");
	// checkStatus (*pStatus, 0, "read after mark 3rd element");
	// testPrint("2.26,");
	// checkDesc (pDesc, str1, "read after mark 3rd element");
	
	
	// // marking out of bounds index
	// testPrint("2.27,");
	// checkResult(mark_TODO(myPid, 0, 1) , -1 , EINVAL, "mark 0 element as 5");	
	
	// // marking out of bounds index
	// testPrint("2.28,");
	// checkResult(mark_TODO(myPid*4, 2, 1) , -1 , ESRCH, "mark illegal pid");	

	// // check all 3 todo are still valid
	// testPrint("2.29,");
	// checkResult(read_TODO(myPid, 1, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 1 after end marking");	
	// testPrint("2.30!\n");
	// checkStatus (*pStatus, 0, "read after mark 3rd element");
	// testPrint("2.31,");
	// checkDesc (pDesc, str1, "read after mark 3rd element");
	// testPrint("2.32,");
	// checkResult(read_TODO(myPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 2 after end marking");	
	// testPrint("2.33,");
	// checkStatus (*pStatus, 5, "read after mark 2nd element");
	// testPrint("2.34,");
	// checkDesc (pDesc, str2, "read after mark 2nd element");
	// testPrint("2.35,");
	// checkResult(read_TODO(myPid, 3, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 3 after end marking");	
	// testPrint("2.36,");
	// checkStatus (*pStatus, 9, "read after mark 3rd element");
	// testPrint("2.37,");
	// checkDesc (pDesc, str3, "read after mark 3rd element");

	
	// /**
	 // DELETE CHECKS, SINGLE PROCESS
	// **/	
	
	// // delete 2nd todo item
	// testPrint("2.38,");
	// checkResult(delete_TODO(myPid, 2) , 0 , 0, "delete 2nd item");	

	// // check 1 is the same, 3->2 and 3 doesnt exist
	// testPrint("2.39,");
	// testPrint("2.40!\n");
	// checkResult(read_TODO(myPid, 1, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 1 after delete");	
	// testPrint("2.41,");
	// checkStatus (*pStatus, 0, "read after mark 3rd element");
	// testPrint("2.42,");
	// checkDesc (pDesc, str1, "read after mark 3rd element");

	// testPrint("2.43,");
	// checkResult(read_TODO(myPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 2 after delete");	
	// testPrint("2.44,");
	// checkStatus (*pStatus, 9, "read after mark 3rd element");
	// testPrint("2.45,");
	// checkDesc (pDesc, str3, "read after mark 3rd element");
	
	// testPrint("2.46,");
	// checkResult(read_TODO(myPid, 3, pDesc, sizeOfReadBuffer, pStatus) , -1 , EINVAL, "read 3 after delete");	

	// // error deletes
	// testPrint("2.47,");
	// checkResult(delete_TODO(myPid-1, 2) , -1 , ESRCH, "delete wrong pid");	
	// testPrint("2.48,");
	// checkResult(delete_TODO(myPid, 5) , -1 , EINVAL, "delete wrong index 5");	
	// testPrint("2.49,");
	// checkResult(delete_TODO(myPid, 3) , -1 , EINVAL, "delete wrong index 3");	
	// testPrint("2.50!/n");
	// checkResult(delete_TODO(myPid, 0) , -1 , EINVAL, "delete wrong index 0");	
	// checkResult(delete_TODO(myPid, -1) , -1 , EINVAL, "delete wrong index -1");	

	// // check 1 is the same, 3->2 and 3 doesnt exist
	// checkResult(read_TODO(myPid, 1, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 1 after delete 2");	
	// checkStatus (*pStatus, 0, "read after mark 3rd element");
	// checkDesc (pDesc, str1, "read after mark 3rd element");

	// checkResult(read_TODO(myPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "read 2 after delete 2");	
	// checkStatus (*pStatus, 9, "read after mark 3rd element");
	// checkDesc (pDesc, str3, "read after mark 3rd element");
	
	// checkResult(read_TODO(myPid, 3, pDesc, sizeOfReadBuffer, pStatus) , -1 , EINVAL, "read 3 after delete 2");	

	// printf("-Finished running single process checks-\n");

	// }

	// // CHECK FATHER CAN CHANGE CHILD AND CHILD'S CHILD
	
	// if (1==1){
		// printf("\n-Running Father->Son checks-\n");

		
		// //int n = something();
		// int n= 0;

		
		// int     fd[2];
		// pipe(fd);
		
		// //pid_t parentPid = myPid;
		// int statusForWaitpid;
		
		// //char c[1000];
		// //FILE *fptr;
		// //unlink ("itaytempfile.txt");
		// // printf("forking!!!\n");

		// int sonPid;
		// sonPid = fork();

		// if(sonPid == 0){               /*child*/
			// // printf("\n\nsonPid == 0!!!\n");

			// int son2Pid;
			// son2Pid = fork();
			// if(son2Pid == 0){    
							// // printf("GRANDSON - SLEEPING!!!\n");
					// //printf("\ngrandson pid is %d\n", getpid());

				// sleep(5);
				// close(fd[0]);							// printf("GRANDSON - EXITNG!!!\n");
				// close(fd[1]);	
				// exit(1);
			// }
			// else if (son2Pid > 0){
				// close(fd[0]);
				// //write(pipe_w, &n, sizeof(n));
				// //printf("\nson pid is %d\n", getpid());
				// n = son2Pid;
				// //printf("\nson writing grandson pid %d\n", son2Pid);
				// //printf("\nson content of n is: %d\n", *(&n));

                // /* Send "string" through the output side of pipe */
                // write(fd[1], &n, sizeof(n));
			    // close(fd[1]);
				// // fptr=fopen("itaytempfile.txt","w");

				// // printf("writing to file\n");
				// // fprintf(fptr,"%d",son2Pid);
				// // fclose(fptr);

				// // printf("SON - WAITING FOR GRANDSON, GRANDSON PID IS %d!!!\n",son2Pid);
				// // printf("SON - GRANDSON PID IS %d!!!\n",son2Pid);
				// // printf("SON - POINTER IS IS %p!!!\n",pGrandsonPID);
				// waitpid(son2Pid, &statusForWaitpid, 0);
				// // printf("SON - GOT GRANDSON!!!\n");
				// exit(1);
			// }
		// } else if(sonPid > 0){  /*parent*/
			// // sleep(5);
			// // printf("STARTING CHECKS - FATHER!!!\n");
			// // printf("STARTING CHECKS - GRANDSON PID IS %d!!!\n",*pGrandsonPID);
			// // printf("STARTING CHECKS - POINTER IS IS %p!!!\n",pGrandsonPID);

			// // if ((fptr=fopen("itaytempfile.txt","r"))==NULL){
				// // printf("Error! opening file");
			// // exit(1);         /* Program exits if file pointer returns NULL. */
			// // }
			// // fscanf(fptr,"%[^\n]",c);
			// // fclose(fptr);
			// // int grandsonPid = atoi(c);

			// close(fd[1]);
            // read(fd[0], &n, sizeof(n));
			// int grandsonPid = n;
			// //printf ("father - son pid is %d grandson pid is %d \n", sonPid, n);
			// close(fd[0]);
			
			
			
			
			
			
			
			// checkResult(read_TODO(sonPid, 1, pDesc, sizeOfReadBuffer, pStatus) , -1 , EINVAL, "grandson - read 1st element of empty queue, invalid index");	
			// checkResult(add_TODO(sonPid, str1, descLength) , 0 , 0, "grandson - add1");			
			// checkResult(add_TODO(sonPid, str2, descLength) , 0 , 0, "grandson - add2");
			// checkResult(add_TODO(sonPid, str3, descLength) , 0 , 0, "grandson - add3");
			
			// checkResult(mark_TODO(sonPid, 2, 5) , 0 , 0, "grandson - mark 2nd element as 5");	
			
			// checkResult(read_TODO(sonPid, 1, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 1 after add");	
			// checkStatus (*pStatus, 0, "grandson - read 1 after add");
			// checkDesc (pDesc, str1, "grandson - read 1 after add");
			// checkResult(read_TODO(sonPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 2 after add");	
			// checkStatus (*pStatus, 5, "grandson - read 2 after add");
			// checkDesc (pDesc, str2, "grandson - read 2 after add");
			// checkResult(read_TODO(sonPid, 3, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 3 after add");	
			// checkStatus (*pStatus, 0, "grandson - read 3 after add");
			// checkDesc (pDesc, str3, "grandson - read 3 after add");
			
			// checkResult(read_TODO(sonPid, 3, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 3 after add");	
			// checkStatus (*pStatus, 0, "grandson - read 3 after add");
			// checkDesc (pDesc, str3, "grandson - read 3 after add");			

			// checkResult(read_TODO(grandsonPid, 1, pDesc, sizeOfReadBuffer, pStatus) , -1 , EINVAL, "grandson - read 1st element of empty queue, invalid index");	
			// checkResult(add_TODO(grandsonPid, str1, descLength) , 0 , 0, "grandson - add1");			
			// checkResult(add_TODO(grandsonPid, str2, descLength) , 0 , 0, "grandson - add2");
			// checkResult(add_TODO(grandsonPid, str3, descLength) , 0 , 0, "grandson - add3");
			
			// checkResult(mark_TODO(grandsonPid, 2, 5) , 0 , 0, "grandson - mark 2nd element as 5");	
			
			// checkResult(read_TODO(grandsonPid, 1, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 1 after add");	
			// checkStatus (*pStatus, 0, "grandson - read 1 after add");
			// checkDesc (pDesc, str1, "grandson - read 1 after add");
			// checkResult(read_TODO(grandsonPid, 2, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 2 after add");	
			// checkStatus (*pStatus, 5, "grandson - read 2 after add");
			// checkDesc (pDesc, str2, "grandson - read 2 after add");
			// checkResult(read_TODO(grandsonPid, 3, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 3 after add");	
			// checkStatus (*pStatus, 0, "grandson - read 3 after add");
			// checkDesc (pDesc, str3, "grandson - read 3 after add");
			
			// checkResult(read_TODO(grandsonPid, 3, pDesc, sizeOfReadBuffer, pStatus) , descLength , 0, "grandson - read 3 after add");	
			// checkStatus (*pStatus, 0, "grandson - read 3 after add");
			// checkDesc (pDesc, str3, "grandson - read 3 after add");		

			
			// waitpid(sonPid, &statusForWaitpid, 0);
			// // printf("END CHECKS - FATHER!!!\n");
			// //unlink ("itaytempfile.txt");
			// printf("-Finished running Father->Son checks-\n");

			
		//}
		
	//}
	
	// // CHECK THAT CHILD CAN'T WRITE TO FATHER
// if (1==1){
				// pid_t parentPid = myPid;

		// printf("\n-Running Son->Father checks-\n");
		// int statusForWaitpid2;


		// int sonPid;
		// sonPid = fork();

		// if(sonPid == 0){               /*child*/
			// //printf("son, parentPid is %d\n",parentPid);
			// //printf("son, getpid is %d\n",getpid());
			
			// //read_TODO(myPid, 1, pDesc, sizeOfReadBuffer, pStatus);	
			
			
			// //checkResult(read_TODO(parentPid, 1, pDesc, sizeOfReadBuffer, pStatus) , -1 , ESRCH, "child - reading father not allowed");	
			// checkResult(read_TODO(parentPid, 1, pDesc, sizeOfReadBuffer, pStatus) , -1 , ESRCH, "child - reading father not allowed");	
			// checkResult(read_TODO(parentPid, 1, pDesc, sizeOfReadBuffer, pStatus) , -1 , ESRCH, "child - reading father not allowed");	
			// checkResult(mark_TODO(parentPid, 1, 5) , -1 , ESRCH, "child - marking father not allowed");	
			// checkResult(add_TODO(parentPid, str1, descLength) , -1 , ESRCH, "child - adding to father not allowed");
			// checkResult(read_TODO(parentPid, 1, pDesc, sizeOfReadBuffer, pStatus) , -1 , ESRCH, "child - reading father not allowed");	
			// checkResult(delete_TODO(parentPid, 3) , -1 , ESRCH, "child - delete from father not allowed");	
			
			
			// exit(1);
		// } else if(sonPid > 0){  /*parent*/
			
			// //printf("Father, son pid is %d. not waiting\n",sonPid);

			// waitpid(sonPid, &statusForWaitpid2, 0);
			// //printf("Father, son pid is %d. done waiting\n",sonPid);

			// // int i;
     		// // for (i = 0; i < 10; i++)
     		// // {
          		// // printf ("iteration %d\n",i);
         		// // sleep(1);
     		// // }
		// }
		// printf("-Finished running Son->Father checks-\n");
	// }

	
	free(pStatus);
	free(pDesc);

	printf("\n---FINISHED RUNNING TESTS---\n");
    return 0;
  
}
