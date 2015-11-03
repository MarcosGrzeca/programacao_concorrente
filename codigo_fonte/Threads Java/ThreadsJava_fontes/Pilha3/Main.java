public class Main {
	
	static Semaforo mutex = new Semaforo(1);
	static Semaforo cheio = new Semaforo(0);
	static Semaforo vazio = new Semaforo(40);

	public static void main ( String [] args ){
		Pilha pilha = new Pilha(40);
		Produtor produtor = new Produtor(pilha);
		Consumidor consumidor = new Consumidor(pilha);
		produtor.start();
		consumidor.start();
	}
}
