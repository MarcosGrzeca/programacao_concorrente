public class MinhaThread extends Thread {
	
	/*------------------------------------------------------------------*/
	private int espera;

	/*------------------------------------------------------------------*/
	public MinhaThread(String nome, int espera) {
		this.setName(nome);
		this.espera = espera;
	}

	/*------------------------------------------------------------------*/
	public void run(){
		try{
			sleep(espera);
			System.out.println("Sou a thread " + this.getName());
		}
		catch (InterruptedException e){};
	}

	/*------------------------------------------------------------------*/
	public static void main (String [] args){

		MinhaThread t1 = new MinhaThread("Thread 1",500);
		MinhaThread t2 = new MinhaThread("Thread 2",250);
		MinhaThread t3 = new MinhaThread("Thread 3",50);

		t1.start();
		t2.start();
		t3.start();

		try{
			t1.join();
			t2.join();
			t3.join();
		}
		catch(InterruptedException e){}	
	}
	/*------------------------------------------------------------------*/
}


