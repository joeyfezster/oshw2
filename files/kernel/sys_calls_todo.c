/* Joey&Noy*/
#include <linux/sys_calls_todo.h>
#include <linux/string.h>
#include <linux/sched.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


//--------------------------Utility funcs -----------------------------------------------------

# define  PDEBUG(fmt, args...) do {} while (0)  // printk( KERN_DEBUG "HW2 %s, %s:%d: " fmt, __FILE__, __FUNCTION__, __LINE__, ## args); \
											 printk("\n")
#define ISNULL(x) ((x) == NULL) ? "yes" : "no"

int isDesendantOfCurrentProcess(pid_t maybe_baby){
	PDEBUG("child check for pid %d", maybe_baby);
	task_t* child = find_task_by_pid(maybe_baby);
	if(child == NULL || current == NULL) return FALSE; //no such pid

	pid_t currentPID = current->pid;
	PDEBUG("asking pid is %d, maybe_baby is %d", currentPID, maybe_baby);
	if(maybe_baby == currentPID) return TRUE;
	while(child != NULL  && child->pid !=1){
		if (child->pid == currentPID){
			return TRUE;
		}
		child = child->p_opptr;
	}
	return FALSE;
}

int legalAccessToProcess(pid_t pid){
	PDEBUG("legality check for pid %d", pid);
	if(isDesendantOfCurrentProcess(pid) == TRUE || ( current != NULL && pid == current->pid)) {
		PDEBUG("TRUE");
		return TRUE;
	}
	PDEBUG("FALSE");
	return FALSE;
}

TODO* getTODOByIndex(list_t* head, int index){
	PDEBUG("index=%d, head is null?: %s", index, ISNULL(head));
	if(head == NULL || index < 1 ) return NULL;
	
	list_t *it, *next;
	int counter =1;
	// if the list isn't empty, try find the requested index, return the TODO
	if (!list_empty(head)){
		list_for_each_safe(it, next, head){
			if(counter==index){
				TODO* todo_s = list_entry(it, TODO, link);
				PDEBUG("returning index %d, result is null?: %s", counter, ISNULL(todo_s));
				return todo_s;
			}
			
			counter++;
		}
	}
	return NULL;
}

/**
* returns null if:
*   1. head is null
*	 2. there's a null TODO in the list
*	 3. all TODO's in the list are later than deadline
*
**/
TODO* getTODOByNearestEarlyDeadline(list_t* head, time_t deadline){
	PDEBUG("deadline=%d, head is null?: %s", deadline, ISNULL(head));
	if(head == NULL ) return NULL;
	
	TODO* maxDeadlineBeforeGivenDeadline = getTODOByIndex(head,1);
	if(maxDeadlineBeforeGivenDeadline == NULL) return NULL;
	if(maxDeadlineBeforeGivenDeadline->deadline > deadline){
		PDEBUG("deadline is prior to all deadlines in the list");
		return NULL
	}
	
	list_t *it, *next;
	int counter =1;
	// go over all the todo's in the list, and find the one with the latest deadline that is before deadline
	
	if (!list_empty(head)){
		list_for_each_safe(it, next, head){
			TODO* todo_s = list_entry(it, TODO, link);
			PDEBUG("checking index %d, this TODO is null?: %s, this TODO's deadline is %d", counter, ISNULL(todo_s), todo_s->deadline);
			counter++;
			if(ISNULL(todo_s)){
				PDEBUG("bad shit happened! null TODO in list");
				return NULL;
			}
			if(todo_s->deadline > maxDeadlineBeforeGivenDeadline->deadline && todo_s->deadline < deadline){
				maxDeadlineBeforeGivenDeadline = todo_s;
			}
		}
	}
	return maxDeadlineBeforeGivenDeadline;

}

int removeFirstLatentTODO(list_t* head){
	if(head == NULL) return -1;

	list_t *it, *next;
	if(!list_empty(head)){
		list_for_each_safe(it, next, head){
			TODO* todo_s = list_entry(it, TODO, link);
			PDEBUG("checking todo with deadline %d at time %d", todo_s->deadline, now);
			if(todo_s->deadline < CURRENT_TIME && todo_s->status == 0){
					kfree(todo_s->desc);
					list_del(&todo_s->link);
					kfree(todo_s);
					return 0;
			}
		}
	}
	return -2;
}
//--------------------------End Utility funcs -----------------------------------------------------
//--------------------------Test function -----------------------------------------------------
int sys_sanity_test(){
	PDEBUG("sanity test");
	return 0;
}

//--------------------------End Test function -----------------------------------------------------

int sys_add_TODO(pid_t pid, const char *TODO_description, ssize_t description_size, time_t TODO_deadline){
	PDEBUG("reached add");
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_description == NULL || description_size < 1 || TODO_deadline < CURRENT_TIME) return -EINVAL;
	
	//check memory allocation success
	TODO* newTodo = kmalloc(sizeof(TODO), GFP_KERNEL);
	if(newTodo == NULL) return -ENOMEM;
	
	newTodo->desc = kmalloc(sizeof(char)*(description_size+1), GFP_KERNEL);
	if(newTodo->desc == NULL){
		kfree(newTodo);
		return -ENOMEM;
	}
	
	//check copy from user space success
	if(copy_from_user(newTodo->desc, TODO_description, description_size) !=0)
	{
		kfree(newTodo->desc);
		kfree(newTodo);
		return -EFAULT;
	}
	PDEBUG("finished sys_add_TODO validations");
	/********************************************************/
	
	newTodo->status = 0;
	newTodo->desc_size = description_size;
	newTodo->deadline = TODO_deadline;
	
	//add the new todo element to the list
	task_t* t = find_task_by_pid(pid);
	if(t == NULL) return -ESRCH;
	
	PDEBUG("Adding new todo to list");
	TODO* prior = getTODOByNearestEarlyDeadline(&t->todo_list, deadline);
	list_add(&newTodo->link, &prior->link);
	
	return 0;
}

ssize_t sys_read_TODO(pid_t pid, int TODO_index, char *TODO_description, time_t* TODO_deadline, int* status){
	PDEBUG("request read: pid = %d, index = %d, null buffer? %s, bufferSize =%d, status ptr is null ? %s", pid, TODO_index, ISNULL(TODO_description), description_size ,ISNULL(status));
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_index < 1 || TODO_description == NULL || status == NULL) return -EINVAL;
	
	//check index within range
	task_t* t = find_task_by_pid(pid);
	if(t == NULL) return -ESRCH;
	TODO* todo_s = getTODOByIndex(&t->todo_list, TODO_index);
	if(todo_s == NULL) return -EINVAL;
	
	//check buffer size < actual description size (buffer is big enough to hold the result)
	ssize_t actualSize = todo_s->desc_size;
	/**********************************************************/
	PDEBUG("this pid: %d, requested pid: %d, todo index %d, description: %s, descriptionSize: %d, status: %d", current->pid, pid, TODO_index, todo_s->desc, todo_s->desc_size, todo_s->status);
	if(copy_to_user(TODO_description, todo_s->desc, actualSize) != 0){ //only copy what we really need
		return -EFAULT;
	}
	*status = todo_s->status;
	*TODO_deadline = todo_s->deadline;
	return actualSize;
}

int sys_mark_TODO(pid_t pid, int TODO_index, int status){
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_index < 1) return -EINVAL;
	//check index within range
	task_t* t = find_task_by_pid(pid);
	if(t == NULL) return -ESRCH;
	TODO* todo_s = getTODOByIndex(&t->todo_list, TODO_index);
	if(todo_s == NULL) return -EINVAL;
	/**************************************************************/
	
	todo_s->status = status;
	return 0;
}

int sys_delete_TODO(pid_t pid, int TODO_index){
	PDEBUG("current pid %d asked to delete pid %d 's todo index %d", current->pid, pid, TODO_index);
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_index < 1) return -EINVAL;
	//check index within range
	task_t* t = find_task_by_pid(pid);
	if(t == NULL) return -ESRCH;
	TODO* todo_s = getTODOByIndex(&t->todo_list, TODO_index);
	if(todo_s == NULL) return -EINVAL;	
	
	PDEBUG("delete todo validations complete!");
	/***************************************************************/
	
	kfree(todo_s->desc);
	list_del(&todo_s->link);
	kfree(todo_s);
	return 0;
}

void punish(task_t* task){
	if(removeFirstLatentTODO(task->todo_list) == 0){
		//punish
		set_task_state(task, TASK_INTERRUPTIBLE);

		//init timer correctly to wake it up after 60 seconds (hardcoded)
		if(task->punish_timer_init == 0){
			task->punish_timer_init = 1;
		}
		else{
			del_timer(&task->punish_timer);
		}
		
		init_timer(&task-> punish_timer);
		task->punish_timer.expires = jiffies + 60*HZ;
		task->punish_timer.data = (unsigned long) task;
		task->punish_timer.function = process_timeout;

		add_timer(&task->punish_timer.function);
	}
}

int sys_the_punisher(){
	PDEBUG("we have reached the punisher!!");
	//foreach task in the system
	task_t* p;

	for_each_task(p) {
		punish(p);
	}
	return 0;
}