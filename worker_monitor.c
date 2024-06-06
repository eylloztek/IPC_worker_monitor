#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void Start_Calculation(int num1, char operation, int num2, double result, char *mess)
{
    pthread_mutex_lock(&lock);
    printf("%s\n%d\n%c\n%d\n", mess, num1, operation, num2);
    printf("%lf\n", result);
    pthread_mutex_unlock(&lock);
}

void *Listen_Worker(void *pipe_name)
{
    const char *worker_pipe = (const char *)pipe_name;
    int pipe_fd = open(worker_pipe, O_RDONLY);

    if (pipe_fd == -1)
    {
        perror("Error opening the named pipe");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        //read data from the named pipe
        int num1, num2;
        double result;
        char operation;
        char mess[100];

        read(pipe_fd, mess, sizeof(mess));
        read(pipe_fd, &num1, sizeof(num1));
        read(pipe_fd, &num2, sizeof(num2));
        read(pipe_fd, &result, sizeof(result));
        read(pipe_fd, &operation, sizeof(char));

        //call Start_Calculation to display the operation
        Start_Calculation(num1, operation, num2, result, mess);

        sleep(1);
    }

    close(pipe_fd);

    return NULL;
}

int main()
{
    //create named pipes
    mkfifo("adder_pipe", 0666);
    mkfifo("subtractor_pipe", 0666);
    mkfifo("multiplier_pipe", 0666);
    mkfifo("divider_pipe", 0666);

    pthread_t adder_thread, subtractor_thread, multiplier_thread, divider_thread;

    //create threads for each worker
    pthread_create(&adder_thread, NULL, Listen_Worker, "adder_pipe");
    pthread_create(&subtractor_thread, NULL, Listen_Worker, "subtractor_pipe");
    pthread_create(&multiplier_thread, NULL, Listen_Worker, "multiplier_pipe");
    pthread_create(&divider_thread, NULL, Listen_Worker, "divider_pipe");

    //wait for threads to finish
    pthread_join(adder_thread, NULL);
    pthread_join(subtractor_thread, NULL);
    pthread_join(multiplier_thread, NULL);
    pthread_join(divider_thread, NULL);

    return 0;
}
