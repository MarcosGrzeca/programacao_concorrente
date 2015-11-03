public class Main {

	public static void main ( String [] args ){
		Pilha pilha = new Pilha(40);
		Produtor produtor = new Produtor(pilha);
		Consumidor consumidor = new Consumidor(pilha);
		produtor.start();
		consumidor.start();
	}
}