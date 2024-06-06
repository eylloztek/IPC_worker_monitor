#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    const char *pipe_name = "divider_pipe";

    while (1)
    {
        //open the named pipe for writing
        int pipe_fd = open(pipe_name, O_WRONLY);

        if (pipe_fd == -1)
        {
            perror("Error opening the named pipe");
            exit(EXIT_FAILURE);
        }

        //write the name of the operation performed for ease of understanding in worker_monitor terminal
        char *mess = "Divider";
        write(pipe_fd, mess, strlen(mess) + 1);

        //read two numbers from the user
        int num1, num2;
        printf("Enter two numbers: ");
        while (scanf("%d %d", &num1, &num2) != 2) {
            printf("Invalid input. Please enter two numbers.\n");

            //clear the input buffer
            while (getchar() != '\n');
            printf("Enter two numbers: ");
        }

        //perform division (checking for division by zero)
        double result = (num2 != 0) ? ((double)num1 / num2) : 0.0;

        //write the operation details to the named pipe
        write(pipe_fd, &num1, sizeof(num1));
        write(pipe_fd, &num2, sizeof(num2));
        write(pipe_fd, &result, sizeof(result));
        write(pipe_fd, "/", sizeof(char));

        close(pipe_fd);

        sleep(1); //sleep for a short time to allow the monitor to read

    }

    return 0;
}
