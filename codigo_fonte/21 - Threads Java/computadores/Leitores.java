public class Leitores extends Thread{

	private int id;

	public Leitores(int id) {
		this.id = id;
	}

	public void run() {
		while(true) {
			Main.mutex.P();
			Main.leitores++;
			if (Main.leitores == 1) {
				Main.db.P();
			}
			Main.mutex.V();
			System.out.println("Leitor " + this.id + " acessando a base");
			try {
				this.sleep(1000);
			} catch (InterruptedException e) {}
			Main.mutex.P();
			Main.leitores--;
			if (Main.leitores == 0) {
				Main.db.V();
			}
			Main.mutex.V();
			try {
				this.sleep(1);
			} catch (InterruptedException e) {}
		}
	}
}