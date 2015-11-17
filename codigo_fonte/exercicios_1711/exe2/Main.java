import java.util.Random;

public class Main {

	/*------------------------------------------------------------------*/
	
    static Semaforo mutex = new Semaforo(1);

	public static void main(String args [] ){
        Semaforo[] semaforos = new Semaforo[3];
		Fumante[] p = new Fumante[3];
        for (int i = 0; i < 3; i++) {
            semaforos[i] = new Semaforo(0);
            p[i] = new Fumante(Integer.toString(i), 1000, semaforos[i]);
            p[i].start();
        }

        Random gerador = new Random();
        while (true) {
            int vai_fumar = gerador.nextInt(3);
            System.out.println("Vai fumar " + Integer.toString(vai_fumar));
            p[vai_fumar].sem.V();
            mutex.P();
        }
    }
}