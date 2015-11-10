public class MinhaThread implements Runnable {
	
	/*------------------------------------------------------------------*/
	private int espera;

	/*------------------------------------------------------------------*/
	public MinhaThread(String nome, int espera) {
		Thread.currentThread().setName(nome);
		this.espera = espera;
	}

	/*------------------------------------------------------------------*/
	public void run(){
		try{
			Thread.currentThread().sleep(espera);
			System.out.println("Sou a thread " + Thread.currentThread().getName());
		}
		catch (InterruptedException e){};
	}

	/*------------------------------------------------------------------*/
	public static void main (String [] args){

		MinhaThread m1 = new MinhaThread("Thread 1",500);
		MinhaThread m2 = new MinhaThread("Thread 2",250);
		MinhaThread m3 = new MinhaThread("Thread 3",50);

		Thread t1 = new Thread(m1);
		Thread t2 = new Thread(m2);
		Thread t3 = new Thread(m2);


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


