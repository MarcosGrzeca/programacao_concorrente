public class Fumante extends Thread{

	/*------------------------------------------------------------------*/
	private int espera;
	protected Semaforo sem;

	/*------------------------------------------------------------------*/    
	public Fumante(String nome, int espera, Semaforo sem){
		this.setName(nome);
		this.espera = espera;
		this.sem = sem;
	}
    
	/*------------------------------------------------------------------*/
	public void run(){
		while (true) {
			this.sem.P();
	        System.out.println("Fuma " + this.getName());
			Main.mutex.V();
			try {
	            sleep(1000);
	        } catch (Exception e) {

	        }
		}
	}
}