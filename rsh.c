#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	for(int i = 0; i < N; i++) {
		if(strcmp(cmd, allowed[i]) == 0) return 1;
	}
	return 0;
}

int main() {

    char line[256];

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';

	char *cmd = strtok(line, " ");
	if(cmd == NULL) continue;

	if(!isAllowed(cmd)) {
		printf("NOT ALLOWED!\n");
		continue;
	}

	if(strcmp(cmd, "exit") == 0) {
		return 0;
	} else if(strcmp(cmd, "help") == 0) {
		printf("The allowed commands are:\n");
		for(int i = 0; i < N; i++) {
			printf("%d: %s\n", i+1, allowed[i]);
		}
		continue;
	} else if(strcmp(cmd, "cd") == 0) {
		char *dir = strtok(NULL, " ");
		char *extra = strtok(NULL, " ");
		if(extra != NULL) {
			printf("-rsh: cd: too many arguments\n");
			continue;
		}
		if(dir == NULL) {
			dir = getenv("HOME");
			if(dir == NULL) {
				printf("cd: HOME not set\n");
				continue;
			}
		}
		if(chdir(dir) < 0) {
			printf("-rsh: cd: %s: No such file or directory\n", dir);
		}
		continue;
	} else {
		// spawn
		char *argv[22];
		argv[0] = cmd;
		int i = 1;
		char *token;
		while((token = strtok(NULL, " ")) != NULL && i < 21) {
			argv[i++] = token;
		}
		argv[i] = NULL;

		pid_t pid;
		int status;
		posix_spawnattr_t attr;
		if(posix_spawnattr_init(&attr) != 0) {
			perror("posix_spawnattr_init failed");
			continue;
		}
		if(posix_spawnp(&pid, cmd, NULL, &attr, argv, environ) != 0) {
			perror("spawn failed");
			posix_spawnattr_destroy(&attr);
			continue;
		}
		if(waitpid(pid, &status, 0) == -1) {
			perror("waitpid failed");
			posix_spawnattr_destroy(&attr);
			continue;
		}
		posix_spawnattr_destroy(&attr);
	}
    }
    return 0;
}
