#include <stdio.h>
#include "libtxt.h"
#include "user.h"

#include <stdlib.h>
#include <time.h>

int random(int num);
void scramble(char pw[], int len, int key);



int main(){
	srand(time(NULL));
	system("cls");
	char userInput[N], pwInput[N];
	struct logindata user;
	memset(user.userName, '\0', N);
	memset(user.password, '\0', N);
	FILE *f = fopen("user.dat", "ab");
	printf(FORM_RED"LÄGG TILL NY ANVÄNDARE!" FORM_END "\nNytt användarnamn: ");
	radInput(userInput, N);
	strcpy(user.userName, userInput);
	printf("Lösenord för %s: ", user.userName);
	radInput(pwInput, N);
	int pwLength = strlen(pwInput);
	user.passwordLength = pwLength;
	int seed = random(pwLength) * random(pwLength) + random(pwLength);
	user.key = seed;
	//printf("\nLösenord innan scramble: %s", pwInput);
	scramble(pwInput, pwLength, user.key);
	//printf("\nLösenord efter scramble: %s", pwInput);
	strcpy(user.password, pwInput);
	fwrite(&user, structSize, 1, f);
	fclose(f);
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
