public class Semaforo {

	private int recursos;

	public Semaforo(int recursos) {
		this.recursos = recursos;
	}

	public synchronized void P() {
		System.out.println("teste");
		while (this.recursos == 0) {
			try {
				this.wait();
			} catch (InterruptedException e) {}
		}
		this.recursos--;
	}

	public synchronized void V() {
		this.recursos++;
		this.notifyAll();
	}
}