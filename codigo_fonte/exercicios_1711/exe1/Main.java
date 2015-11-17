public class Main {

	/*------------------------------------------------------------------*/
	public static final int maxThreads = 5;
	public static int cont = 0;

	static Semaforo mutex = new Semaforo(1);
	static Semaforo barreira = new Semaforo(0);

	public static void main(String args [] ){
		
		MinhaThread[] p = new MinhaThread[Main.maxThreads];
        for (int i = 0; i < Main.maxThreads; i++) {
            p[i] = new MinhaThread(Integer.toString(i), 1000);
            p[i].start();
        }
        
        for (int i = 0; i < Main.maxThreads; i++) {
            try {
                p[i].join();
            } catch (Exception e) {}
        }
    }
}