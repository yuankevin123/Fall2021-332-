// Worked on by Kevin Yuan

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

void sh_list(char **args) {
    system("clear"); //Clear Screen();

    int file_desc = open("t1.txt", O_WRONLY | O_CREAT, 0666);
    int pid_ls = fork(); // Fork a process to run ls -l

    if (pid_ls < 0){
        fprintf(stderr, "parent: Could not fork process to run ls\n");
        exit(0);
    } 
    else if (pid_ls == 0){// Child
        dup2(file_desc, 1);
        char *new_argv[] = {"ls", "-l", 0}; // Setup the arguments/environment to call
        execvp(new_argv[0], new_argv); // Call execvp() which will replace the executable image of this process
        fprintf(stderr, "child ls -l failed!\n");
        exit(0);
    } else {
        close(file_desc);
        wait(NULL); // Wait for children to finish
        FILE *file = fopen("t1.txt", "r");// open file and print to stdout
        if (file == NULL) {
            printf("File t1.txt not found.\n");
            exit(0);
        }
        char c;
        c = fgetc(file);
        while (c != EOF) {
            printf("%c", c);
            c = fgetc(file);
        }
        fclose(file);
        rename("t1.txt", "tree.txt"); // rename file
    }
}


