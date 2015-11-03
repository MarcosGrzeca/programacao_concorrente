public class MinhaThread extends Thread{

	static Semaforo sem = new Semaforo(2);
   
	private int espera;
    
	public MinhaThread(String nome, int espera){
		this.setName(nome);
		this.espera = espera;
	}
    
	public void run(){
		sem.P();
		System.out.println("Sou a thread " + this.getName());
		try{
		    this.sleep(espera);
		}catch(Exception e){}
        	sem.V();
	} 
        
	public static void main(String args [] ){
		MinhaThread t1 = new MinhaThread("Thread 1",5000);
		MinhaThread t2 = new MinhaThread("Thread 2",2500);
		MinhaThread t3 = new MinhaThread("Thread 3",0);

		t1.start();
		t2.start();
		t3.start();
        }
}