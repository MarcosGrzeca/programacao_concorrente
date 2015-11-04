public class MinhaThread implements Runnable {
	private String nome;
	private Classe objeto;
	public MinhaThread(String nome, Classe objeto) {
		this.nome = nome;
		this.objeto = objeto;
	}

	public void run(){
		System.out.println(this.nome);

	}

	public static void main(String args[]) {
		Classe objeto = new Classe();

		MinhaThread n1 = new MinhaThread("T1", objeto);
		Thread t1 = new Thread(n1);
		MinhaThread n2 = new MinhaThread("T2", objeto);
		Thread t2 = new Thread(n2);
		MinhaThread n3 = new MinhaThread("T3", objeto);
		Thread t3 = new Thread(n3);
		MinhaThread n4 = new MinhaThread("T4", objeto);
		Thread t4 = new Thread(n4);
		MinhaThread n5 = new MinhaThread("T5", objeto);
		Thread t5 = new Thread(n5);

		t1.start();
		t2.start();
		t3.start();
		t4.start();
		t5.start();

		try {
			t1.join();
			t2.join();
			t3.join();
			t4.join();
			t5.join();
		} catch (Exception e) {

		}
	}
}