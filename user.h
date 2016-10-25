#define N 30

struct logindata{
	char userName[N];
	char password[N];
	int passwordLength;
	int key;
};

int structSize = sizeof(struct logindata);