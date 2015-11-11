public class Main {

	public static Semaforo mutex = new Semaforo(1);
	public static Semaforo db = new Semaforo(1);
	public static int leitores = 0;


	public static void main(String args[]) {
		Leitores t1 = new Leitores(1);
		Leitores t2 = new Leitores(2);
		Leitores t3 = new Leitores(3);

		Escritores e1 = new Escritores(1);
		Escritores e2 = new Escritores(2);

		t1.start();
		t2.start();
		t3.start();

		e1.start();
		e2.start();

		// try {
		// 	t1.join();
		// 	t2.join();
		// 	t3.join();
		// } catch (InterruptedException e) {
		// 	e.printStackTrace();
		// }
	}
}