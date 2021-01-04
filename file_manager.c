#include "types.h"
#include "user.h"
#include "fcntl.h"

char* tempPath = "/temp.txt";


int callCD(char* path) {
	char *argv[] = { "cd", path };

	int pid = fork();

	if (pid == -1) {
		printf(1, "CD call error, pid: ", pid);
		return -1;
	}
	else if (pid == 0){
		exec("cd", argv);
		printf(1, "init: exec cd failed\n");
		exit();
	}
	else {
		int status;
		wait();
	}

	return 0;
}


int callLS(char* path) {
	char *argv[] = { "ls", path };

	int pid = fork();

	if (pid == -1) {
		printf(1, "LS call error, pid: ", pid);
		return -1;
	}
	else if (pid == 0) {
		close(1);
		int tempfd = open(tempPath, O_CREATE|O_RDWR);

		exec("ls", argv);
		printf(1, "init: exec ls failed\n");
		exit();
	}
	else {
		int status;
		wait();
	}

	return 0;
}


int callRM(char* path) {
	char *argv[] = { "rm", path };

	int pid = fork();

	if (pid == -1) {
		printf(1, "RM call error, pid: ", pid);
		return -1;
	}
	else if (pid == 0){
		exec("rm", argv);
		printf(1, "init: exec rm failed\n");
		exit();
	}
	else {
		int status;
		wait();
	}

	return 0;
}


int callCP(char* from, char* to) {
	char *argv[] = { "cp", from, to };

	int pid = fork();

	if (pid == -1) {
		printf("1, CP call error, pid: ", pid);
		return -1;
	}
	else if (pid == 0){
		exec("cp", argv);
		printf(1, "init: exec cd failed\n");
		exit();
	}
	else {
		int status;
		wait();
	}

	return 0;
}


int callMV(char* from, char* to) {
	char *argv[] = { "mv", from, to };

	int pid = fork();

	if (pid == -1) {
		printf(1, "MV call error, pid: ", pid);
		return -1;
	}
	else if (pid == 0){
		exec("mv", argv);
		printf(1, "init: exec mv failed\n");
		exit();
	}
	else {
		int status;
		wait();
	}

	return 0;
}

int main(void) {
	callCP("g.txt", "folder/g.txt");
	callLS("/");
	callMV("f.txt", "folder/f.txt");
	callCD("folder/");
	callRM("f.txt");

	exit();
}