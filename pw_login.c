#include <stdio.h>
#include "libtxt.h"
#include "user.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>

int random(int num);
void scramble(char pw[], int len, int key);


int main(){
	srand(time(NULL));
	system("cls");
	char userInput[N], pwInput[N], c;
	memset(userInput, '\0', N);
	//memset(pwInput, '\0', N);
	FILE *f = fopen("user.dat", "rb");
	fseek(f, 0, SEEK_END);
	int n = ftell(f) / structSize;
	rewind(f);
	//printf("Hittade %d användare i filen!", n);
	struct logindata users[n];
	fread(&users, structSize, n, f);
	fclose(f);
/* 	for(int i=0; i<n;i++){
		printf("Användare: %s\n", users[i].userName);
		printf("Scramblat lösenord: %s\n", users[i].password);
		printf("Nyckel: %d\n", users[i].key);
		printf("Lösen Längd: %d\n\n", users[i].passwordLength);
	} */
	printf(FORM_CYAN"LOGGA IN!" FORM_END "\nAnvändarnamn: ");
	radInput(userInput, N);
	//leta index:
	int index = -1;
	for(int i=0; i<n;i++){
		if(!strcoll(userInput, users[i].userName)){
			index = i;
			//printf("Hittade användare på index %d", index);
			break;
		}
	}
	if(index<0){
		printf(FORM_RED "Hittade inte användare!");
		return 0;
	}
	printf("Ange ditt lösenord: ");
	//Masked input from http://codingstreet.com/c-code-to-hide-input-password/ (needs <conio.h> in windows)
	int i =0;
	while(i<=N){
		pwInput[i]=getch();
		c=pwInput[i];
		if(c==13) break; //return
		else printf("*");
		i++;
	}
	pwInput[i]='\0';
	//printf("Du skrev lösenord: %s\n", pwInput);

	scramble(pwInput,  users[index].passwordLength, users[index].key);
	if(!strcoll(pwInput, users[index].password)){
		printf("\n\n" FORM_GREEN "Korrekt lösenord! Du vann!");
	}
	else{
		printf("\n\n" FORM_RED "Fel lösenord!!!!!");
		return 0;
	}
	return 0;
}

int random(int num){
	return rand() % num;
}

void scramble(char pw[], int len, int key){
	while(len){
		pw[len-1] = pw[len-1] + key;
		len--;
	}
}
