#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{

int arr[argc];
int length = 0;

for (int k = 1; k < argc; k++)
{
   arr[k-1] = atoi(*(argv+k));
   length++;
}

    int fd[2];
    if(pipe(fd) == -1){
        perror(" error");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    int end, start;
    if (-1 == pid){
        perror("Fork error");
        return EXIT_FAILURE;
    } else if (0 == pid){
        close(fd[0]);
        start = 0;
        end = length / 2;
        int sum = 0;
        for (int i = start; i < end; i++){
            sum += arr[i];
        }
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    } else {
        close(fd[1]);
        
        start = length / 2;
        end = length;
        int sum = 0;
        for (int i = start; i < end; i++){
            sum += arr[i];
        }
        int sumChild;
        read(fd[0], &sumChild, sizeof(sumChild));
        close(fd[0]);
        printf("Sum of parent = %d\n", sum);
        printf("Sum  child = %d\n", sumChild);
        printf("Final = %d\n", sum + sumChild);
        wait(NULL);
    }    
    return EXIT_SUCCESS;
}