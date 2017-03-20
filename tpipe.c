#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
        int     fd[2], nbytes,a=0;
        pid_t   childpid;
        char    string[] = "Data: 9d234fffccc44 \n";
	char    string1[] = "09876gh \n";
    
      char    readbuffer[80];

        pipe(fd);
	a=(strlen(string)+1);
		printf("/n%d ",a);
       
        childpid = fork();
        if(childpid == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                printf("                   Child Process: %s \n",string);
                write(fd[1], string1, (strlen(string)+1));
		
                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		a=(sizeof(readbuffer));
		printf("/n%d ",a);
                printf("Parent Process: Received string: %s", readbuffer);
        }
        
        return(0);
}
