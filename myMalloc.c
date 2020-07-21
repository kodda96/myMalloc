#include <stdio.h>
#include "myMalloc.h"

Block *root = (Block*)memory;

 static void initialize(){
	root->free = 1;
	root->size = MAX - sizeof(Block);
	root->next = NULL;
	root->prev = NULL;
	root->address = memory + sizeof(Block);
}

static void merge(Block *ptr){
	ptr->size = (ptr->size) + (ptr->next->size) + sizeof(Block);
	if(ptr->next->next){
		ptr->next = ptr->next->next;
		ptr->next->prev->next = NULL;
		ptr->next->prev->prev = NULL;
		ptr->next->prev = ptr;
	}else{
		ptr->next->prev = NULL;
		ptr->next = NULL;
	}
}

static void split(Block *ptr, unsigned int size){
	Block *temp = ((void*)(ptr+1) + size);
	temp->size = ptr->size - size - sizeof(Block);
	temp->free = 1;
	temp->address = (void*)(temp+1);
	ptr->size = size;
	if(ptr->next){
		temp->next = ptr->next;
		ptr->next->prev = temp;
	}else{
		ptr->next = temp;
	}
	temp->prev = ptr;
	ptr->next = temp;	
}

void *myMalloc(unsigned int size){
	if(!root->size) initialize();
	Block *ptr = root;
	while(ptr){
		if(ptr->free == 1 && ptr->size >= size){
			if(ptr->size == size){
				ptr->address = (void*)(ptr+1);
			}else if(ptr->size > size + sizeof(Block)){
				split(ptr, size);
			}
			ptr->free = 0;
			return ptr->address;
		}
		ptr = ptr->next;
	}	
	return NULL;
}

void myFree(void *loc){
	Block *ptr = root;
	while(ptr){
		if(ptr->address == loc){
			ptr->free = 1;
			if(ptr->next && ptr->next->free) merge(ptr);
			if(ptr->prev && ptr->prev->free) merge(ptr->prev);
			return;
		}
		ptr = ptr->next;
	}
}

