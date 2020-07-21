#include <stdio.h>
#include "myMalloc.c"


int main(){
	char *addr1 = (char*)myMalloc(200);
	printf("Allocate 200 memeory:  %400 %p \n", addr1);
	char *addr2 = (char*)myMalloc(400);
	printf("Allocate 400 memeory:  %400 %p \n", addr2);
	char *addr3 = (char*)myMalloc(600);
	printf("Allocate 600 memeory:  %400 %p \n", addr3);
	char *addr4 = (char*)myMalloc(500);
	printf("Allocate 500 memeory:  %400 %p \n", addr4);
	
	printf("\n");
	printf("Free of 400 memeory:  %400 %p \n", addr2);
	
	printf("Free of 600 memeory:  %400 %p \n", addr3);
	char *addr5 = myMalloc(700);
	printf("\n");
	printf("Allocate 700 memeory:  %400 %p \n", addr5);
	
	return 0;
}
