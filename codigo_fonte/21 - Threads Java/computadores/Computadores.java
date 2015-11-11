public class Computadores extends Thread {

	private int tempo;
	private Semaforo semaforo;


	public Computadores(String nome, int tempo, Semaforo semaforo) {
		this.setName(nome);
		this.tempo = tempo;
		this.semaforo = semaforo;
	}

	public void run() {
		this.semaforo.P();
		System.out.println(Thread.currentThread().getName());
		try {
			Thread.currentThread().sleep(this.tempo);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		this.semaforo.V();
	}

	public static void main(String args[]) {

		Semaforo semaforo = new Semaforo(1);
		
		Computadores t1 = new Computadores("T1", 3000, semaforo);
		Computadores t2 = new Computadores("T2", 1500, semaforo);
		Computadores t3 = new Computadores("T3", 500, semaforo);

		t1.start();
		t2.start();
		t3.start();

		try {
			t1.join();
			t2.join();
			t3.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}