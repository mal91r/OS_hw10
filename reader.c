#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

char b_number[100];
int index = 0;


 int bin2dec(char *s)
{
	short i;
	int res = 0;

	for (i = 0; i < sizeof(long) * 8 && s[i]; ++i)
	{
		res <<= 1;
		res |= (s[i] - '0');
	}
	return res;
}

void handler(int nsig) {
    switch(nsig) {
    case SIGUSR1: // Сигнал процесса SIGUSR1
	zero(nsig);
	break;
    case SIGUSR2: // Сигнал процесса SIGUSR2
        one(nsig);
        break;
    default: // Этот пример не поддерживает
        printf("Should not be here\n");
        break;
    }
}

void end(int nsig){
    int rez = bin2dec(b_number);
    printf("\nResult = %d\n", rez);
    exit(0);
}

void zero(int nsig){
    printf("%c", '0');
    b_number[index++] = '0';
}

void one(int nsig) {
    printf("%c", '1');
    b_number[index++] = '1';
}


int main()
{
    (void) signal(SIGUSR1, handler);
    (void) signal(SIGUSR2, handler);   
    (void) signal(SIGINT, end);
    pid_t r_pid = getpid(); 
    printf("Reciever pid = %d\n", r_pid);
    printf("Input sender PID: ");
    int x;
    scanf("%d", &x);
    pid_t s_pid = (pid_t)x;
    while(1);
    //b_number = "1111";
    return 0;
}

