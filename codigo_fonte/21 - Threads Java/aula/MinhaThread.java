public class MinhaThread extends Thread {

	private int tempo;
	private Semaforo semaforo;


	public MinhaThread(String nome, int tempo, Semaforo semaforo) {
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
		
		MinhaThread t1 = new MinhaThread("T1", 3000, semaforo);
		MinhaThread t2 = new MinhaThread("T2", 1500, semaforo);
		MinhaThread t3 = new MinhaThread("T3", 500, semaforo);

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