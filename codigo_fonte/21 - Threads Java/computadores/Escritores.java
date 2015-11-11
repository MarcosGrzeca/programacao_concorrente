public class Escritores extends Thread{

	private int id;

	public Escritores(int id) {
		this.id = id;
	}

	public void run() {
		while(true) {
			Main.db.P();
			System.out.println("Escritor " + this.id + " acessando a base");
			try {
				this.sleep(2000);
			} catch (InterruptedException e) {}
			Main.db.V();
			try {
				this.sleep(1);
			} catch (InterruptedException e) {}
		}
	}
}