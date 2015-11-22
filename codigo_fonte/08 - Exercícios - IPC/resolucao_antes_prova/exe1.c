
##ifndef SYMBOL
#define KEY 10
#endif

#define N 1000
#define w 1.0/N

double pi(int x) {

}

void main(int argc, char const *argv[])
{
	/* code */
	
	double pi= 0.0, x;

	pid_t pid;
	double *memoria = NULL;



	int shmid = shmget(KEY, 3 * sizeof(double), IPC_CREAT | 0600);
	if (shmid < 0) {
		printf("ERRO\n");
	}

	memoria = shmat(shmid, 0, 0);

		printf("Digite o numero de retangulos: ");
	scanf("%lf", &n);


	pid = fork();
	if (pid > 0) {
		pid = fork();
		if (pid > 0) {
			pid = fork();
			if (pid > 0) {
				wait(NULL);
				wait(NULL);
				wait(NULL);

				shmctl(shmid, IPC_RMID, NULL);
			} else {

				shmdt(memoria);
			}
		} else {
				shmdt(memoria);
		}
	} else {
		memoria[0]  = pi
			shmdt(memoria);
	}

}