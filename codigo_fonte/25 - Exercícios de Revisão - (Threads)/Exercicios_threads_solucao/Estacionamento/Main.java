public class Main {
	
	/*----------------------------------------------------------------*/
	public static final int maxCarros = 15;
	public static int  cont = 0;

	public static Semaforo [] sem = new Semaforo[3];
	public static Semaforo mutex = new Semaforo(1);
	public static int [] total  = new int[3];

	/*----------------------------------------------------------------*/
	public static void main (String [] args){

		Carros  [] c = new Carros[maxCarros]; 

		for(int i = 0; i < 3; i++){
			// posicao 0  semaforo dos professores
			// posicao 1  semaforo dos funcionarios
			// posicao 2  semaforo dos alunos
			sem[i] = new Semaforo(0);
			total[i] = 0;		
		}

		for(int i = 0; i< maxCarros; i++){
			// id 0 professor
			// id 1 funcionario
			// id 2 aluno
			c[i] = new Carros((int) (Math.random() * 3));
			c[i].start();
		}
	}
	/*----------------------------------------------------------------*/

}

