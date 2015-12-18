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

int isDesendantOfCurrentProcess(pid_t maybe_baby){
	task_t* child = find_task_by_pid(maybe_baby);
	if(child == NULL) return FALSE; //no such pid
	
	pid_t currentPID = current->pid;
	while(child->pid !=  1){
		if (child->p_pptr->pid == currentPID) return TRUE;
		child = child->p_pptr;
	}
	return FALSE;
}

int legalAccessToProcess(pid_t pid){
	if(isDesendantOfCurrentProcess(pid) == TRUE || pid == current->pid) return TRUE;
	return FALSE;
}

TODO* getTODOByIndex(list_t* head, int index){
	if(head == NULL || index < 1) return NULL;
	
	list_t *it, *next;
	int counter =1;
	// delete the list if it isn't empty 
	if (!list_empty(head)){
		list_for_each_safe(it, next, &current->todo_list){
			if(counter==index) return list_entry(it, TODO, link);
			
			counter++;
		}
	}
	return NULL;

	
}
//--------------------------End Utility funcs -----------------------------------------------------

int sys_add_TODO(pid_t pid, const char *TODO_description, ssize_t description_size){
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_description == NULL || description_size <1) return -EINVAL;
	
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
	
	/********************************************************/
	
	newTodo->status = 0;
	newTodo->desc_size = description_size;
	
	//add the new todo element to the list
	task_t* t = find_task_by_pid(pid);
	list_t todoList = t->todo_list;
	list_add_tail(&newTodo->link, &todoList);
	
	return 0;
}

ssize_t sys_read_TODO(pid_t pid, int TODO_index, char *TODO_description, ssize_t description_size, int* status){
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_index < 1 || TODO_description == NULL || description_size <1) return -EINVAL;
	
	//check index within range
	struct task_struct *tsk = current;
	TODO* todo_s = getTODOByIndex(&current->todo_list, TODO_index);
	if(todo_s == NULL) return -EINVAL;
	
	//check buffer size < actual description size (buffer is big enough to hold the result)
	ssize_t actualSize = todo_s->desc_size;
	if(description_size < actualSize) return -EINVAL;
	/**********************************************************/
	
	if(copy_to_user(TODO_description, todo_s->desc, actualSize) != 0){ //only copy what we really need
		return -EFAULT;
	}
	return actualSize;
}

int sys_mark_TODO(pid_t pid, int TODO_index, int status){
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_index < 1) return -EINVAL;
	//check index within range
	struct task_struct *tsk = current;
	TODO* todo_s = getTODOByIndex(&current->todo_list, TODO_index);
	if(todo_s == NULL) return -EINVAL;
	/**************************************************************/
	
	todo_s->status = status;
	return 0;
}

int sys_delete_TODO(pid_t pid, int TODO_index){
	//check legal access
	if(legalAccessToProcess(pid) != TRUE) return -ESRCH;
	//check legal parameters
	if(TODO_index < 1) return -EINVAL;
	//check index within range
	struct task_struct *tsk = current;
	TODO* todo_s = getTODOByIndex(&current->todo_list, TODO_index);
	if(todo_s == NULL) return -EINVAL;	
	/***************************************************************/
	
	list_t *it, *next;
	// delete the particular entry
	int counter =1;
	if (!list_empty(&current->todo_list)){
		TODO *todo_s;
		list_for_each_safe(it, next, &current->todo_list){
			if(counter == TODO_index){
				todo_s = list_entry(it, TODO, link);
				kfree(todo_s->desc);
				list_del(&todo_s->link);
				kfree(todo_s);
			}
			counter++;
		}
	}
}