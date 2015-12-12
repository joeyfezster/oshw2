/* ronen and arthur*/
#include <linux/sys_calls_todo.h>
#include <linux/string.h>

/*list for ranks*/
list_t ranks;



int sys_register_mpi(void){
	rankS *newRank = kmalloc(sizeof(rankS),GFP_KERNEL);
	/* check allocation */
    if (newRank == NULL){
        return -ENOMEM;
    }
	newRank->taskPtr = current;
	/* register a process to mpi */
    if (!(list_empty(&ranks)))  
	{
        /* if its not the first process in the MPI */
		int myPid = current->pid;
        int max_rank = 0;
		list_t *itr,*next;
        list_t *rankItr,*rankNext;
		rankS *tempRank,*maxRankTemp;
		/* check if the process is already registered */ 
        list_for_each_safe(itr, next, &ranks){
			tempRank = list_entry(itr, rankS, listPtr);
			if (tempRank->taskPtr->pid == myPid){
                kfree(newRank); // no new item was inserted
				return tempRank->rank;
			}
		}
        /*else find the highest rank so far */ 
        list_for_each_safe(rankItr, rankNext, &ranks){
            maxRankTemp = list_entry(rankItr, rankS, listPtr);
            if (maxRankTemp->rank > max_rank){
                max_rank = maxRankTemp->rank;
            }
        }
        /* add the new process to the rank list */ 
        newRank->rank = max_rank+1;
		list_add(&newRank->listPtr, &ranks);
		return newRank->rank;
	}
	else
	{
        /* first registered process => rank =0 */ 
		newRank->rank = 0;
		list_add(&newRank->listPtr, &ranks);
		return 0;
	}
    
}
int sys_send_mpi_message(int rank, const char *message, int message_size){
	int myPid = current->pid;
	int myRank = -1;
	list_t *itr,*next;
	rankS *tempRank;
	if (message == NULL || message_size<1){
		return -EINVAL;

	}
	if (list_empty(&ranks)){
      return -ESRCH;

    }
	/* check if the sending process is registered in the MPI*/
	list_for_each_safe(itr, next, &ranks){
		tempRank = list_entry(itr, rankS, listPtr);
		if (tempRank->taskPtr->pid == myPid){
			myRank = tempRank->rank;
			break;
		}
	}
	if (myRank <0){
		return -ESRCH;

	}
	/**********************************************/
	
	list_for_each_safe(itr, next, &ranks){
		tempRank = list_entry(itr, rankS, listPtr);
		
		if (tempRank->rank == rank){
			//allocate new struct for new msg
			MSG *new_msg = (MSG*)kmalloc(sizeof(MSG),GFP_KERNEL);
			if (new_msg == NULL){
                return -ENOMEM;

            }
			// allocate new message
			new_msg->msg = kmalloc(sizeof(char)*(message_size+1),GFP_KERNEL);
			if (new_msg->msg == NULL){
                return -ENOMEM;
    
            }
			/* copy from user to kernel */ 
			if( copy_from_user(new_msg->msg, message, message_size) != 0 ){
				return -EFAULT;

			}
			new_msg->msg[message_size] = '\0';
			new_msg->fromRank = myRank;
			// add message to end of list (FIFO)
			list_add_tail(&new_msg->ptr, &tempRank->taskPtr->msg_queue);
			return 0;	
		}
	}
    /* return this value if rank was not found - or not registered */ 
	return -ESRCH;
}
int sys_receive_mpi_message(int rank, char *message, int message_size){
	list_t *itr,*next;
	MSG *tempMsg;
	rankS *tempRank;
	int myPid = current->pid;
	int foundRank = 0;
	int copy_size = message_size;
	
    /* check ivalid args */ 
    if (message_size<1 || message==NULL){
        return -EINVAL;
    }
    if (list_empty(&ranks)){
        return -ESRCH;
    }
    /* check if the receiving process is registered in the MPI*/
	list_for_each_safe(itr, next, &ranks){
		tempRank = list_entry(itr, rankS, listPtr);
		if (tempRank->taskPtr->pid == myPid){
			foundRank=1;
			break;
		}
	}
	if (!foundRank){
		return -ESRCH;
	}
    
    /********************************************************/
    
	if (!(list_empty(&current->msg_queue))){
		list_for_each_safe(itr, next, &current->msg_queue){
			tempMsg = list_entry(itr, MSG, ptr);
			if (tempMsg->fromRank == rank){
				if (message_size > strlen(tempMsg->msg))
					copy_size = strlen(tempMsg->msg);
				if (!copy_to_user(message, tempMsg->msg, copy_size)){
					//message[copy_size] = '\0';
					kfree(tempMsg->msg);
					list_del(&tempMsg->ptr);
					kfree(tempMsg);
					return copy_size;
					break;
				}
				else 
				{
                    return -EFAULT;

				}
			}
		}
        
	}
	return -EFAULT;

}
