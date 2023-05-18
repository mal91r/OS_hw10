#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int dec2bin(int num)
{
    int bin = 0, k = 1;

    while (num)
    {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }

    return bin;
}




int main()
{
    pid_t s_pid = getpid(); // Запонимаем пид родителя, то есть приёмника
    printf("Sender pid = %d\n", s_pid);
    printf("Input reciever PID: ");
    int x;
    scanf("%d", &x);
    pid_t r_pid = (pid_t)x;
    int number;
    printf("Input decimal integer number: ");
    scanf("%d", &number);   
    int rez = dec2bin(number);
    char str[100];
    sprintf(str, "%d", rez);
    int index = 0;
    while (str[index] == '0' || str[index] == '1') {
    	if(str[index] == '0') {
    	    kill(r_pid, SIGUSR1);
    	    printf("%c", '0');
    	    sleep(1);
    	} else {
    	    kill(r_pid, SIGUSR2);
    	    printf("%c", '1');
    	    sleep(1);
    	}
    	index++;
    }    
    kill(r_pid, SIGINT);
    sleep(1);
    printf("\nResult = %d\n", number);

    return 0;
}

