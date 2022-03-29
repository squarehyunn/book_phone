/*
 *
 *  Created on: 2022. 3. 11.
 *      Author: atec
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
	int num;
	char name[50];
	struct data *next;
}data;



data *g_head = NULL;
data *g_tail = NULL;

int insert(int num, char* name){
	data * node  = malloc(sizeof(data));
	node->num = num;
	node->next = NULL;
	if(name != NULL){
		strcpy(node->name,name);
	}else{
		return 1;
	}

	//g_tail->next = NULL;

	if(g_head == NULL){
		g_head = node;
		g_tail = node;
		return 1;
	}else{
		data *temp = g_head;
		while(temp->next){
			temp = temp->next;
		}
		temp-> next = node;
		g_tail = node;
		return 1;
	}




}

data * stack_pop(){
	//유의 해야 할 경우
	// 1. 아무것도 없는경우(g_head = NULL) || (g_tail = NULL)
	// 2. 하나만 남은 경우

	//1. 비어있는지 확인
	if(g_head == NULL || g_tail == NULL){ //g_tail == NULL이여도 상관없겠다.
		return NULL;
	}

	data *node = g_tail;

	data * temp  = g_head;
	data * before = NULL;

	//2. tail의 바로 전 노드를 찾고, 그 노드를 g_tail로 바꾸기
	while(temp->next){
		before = temp;
		temp=temp->next;
	}
	g_tail = before;

	//2-1 애초에 아무것도 없는 경우를 위한 예외처리
	if(before != NULL){
		before -> next = NULL;
	}else if(g_tail == NULL){
		g_head = NULL;
	}

	return node;

}

data * pop(){
	if(g_head == NULL){
		return NULL;
	}

	data * node = g_head;

	if(g_head->next != NULL){
		g_head = g_head->next;
	}else{
		g_head = NULL;
		g_tail = NULL;
	}
	return node;

}


void printAll(){
	data * temp = g_head;
	while(temp){//temp->next하면 출력이 안됨....NULL출력하려고 하면 세그먼트 오류
		printf("========s========\n");
		printf("num : %d\n",temp->num);
		printf("name : %s\n",temp->name);
		printf("========e========\n\n");
		temp = temp->next;
	}

}

data* find(int num){

	if(g_head == NULL){
		printf("no data...\n");
		return NULL ;
	}

	data * temp = g_head;

	while(temp){
		if(temp->num == num){
			return temp;
		}
		temp = temp -> next;
	}

}

data* find_before(int num){

	if(g_head == NULL){
		printf("no data...\n");
		return NULL ;
	}

	data * temp = g_head;
	data * before = NULL;

	while(temp){

		if(temp->num == num){
			return before;
		}
		before = temp;
		temp = temp -> next;
	}

}

int insertMid(int finNum,int num, char * name){

	data * node = malloc(sizeof(data));
	node->num = num;
	if(name != NULL){
		strcpy(node->name,name);
	}else{
		return 1;
	}
	//temp->next를 tem_nxt에 저장하고, temp->next를 node로 바꾸고, node의 next를 tem_nxt로 지정

	 data *temp = find(finNum);
	 data *tmp_nxt = temp->next;

	 if(tmp_nxt == NULL){//노드가 하나만 있는 경우
		 insert(num,name);
		 return 1;
	 }else{
		 temp->next = node;
		 node->next = tmp_nxt;
		 return 1;
	 }

}

int delMid(int finNum){

	printf("===== 삭제 번호 : %d =====\n",finNum);
	 data *temp = find(finNum);
	 data *before = find_before(finNum);
	 data *tmp_nxt = temp->next;

	 if(tmp_nxt == NULL){//노드가 하나만 있던 경우
		 free(temp);
		 g_head = NULL;
		 g_tail = NULL;
		 return 1;
	 }else{
			 free(temp);
		 if(before != NULL){
			 before->next = tmp_nxt;
		 }else{ //before가 NULL이라면, 맨 처음 값일 떄이고, 이값을 HEAD가 가리키고 있기 때문에
			 g_head  = tmp_nxt;
		 }
		 return 1;
	 }

}

int main(){

	char name[100] = "";

	for(int i = 0; i<5; i++){
		sprintf(name,"name[%d]",i);
		insert(i,name);
	}

	insertMid(1,11,"11name");
	insertMid(3,33,"33name");
	printAll();
	delMid(11);
	printAll();
	delMid(33);
	printAll();

	for(int i =0; i<5;i++){
		delMid(i);
		printAll();
	}
//	for(int i = 0 ; i<10; i++){
//		printf(" 찾을 데이터 입력 : ");
//		int i;
//		scanf("%d",&i);
//		data * finded = find(i);
//		printf("찾은 데이터 : num = %d / name = %s \n",finded->num, finded->name);
//	}

//	printAll();

//	for(int i = 0 ;i<10;i++){
//		data * node1 = pop();
//
//		printf("************************\n");
//		printf("pop num : %d\n",node1 -> num);
//		printf("pop name: %s\n",node1 -> name);
//		printf("************************\n");
//		free(node1);
//		printAll();
//	}




	return 1;
}
