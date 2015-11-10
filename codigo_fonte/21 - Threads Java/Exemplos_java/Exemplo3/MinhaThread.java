public class MinhaThread extends Thread {

	/*------------------------------------------------------------------*/
	public MinhaThread(String nome) {
		this.setName(nome);
	}

	/*------------------------------------------------------------------*/
	public static synchronized void escreveNome(){
		for (int i=0; i<5; i++){
			try{
				sleep(1000);		
			}catch (InterruptedException e){}
			System.out.println("Sou a thread " + Thread.currentThread().getName());
		}
	}

	/*------------------------------------------------------------------*/
	public void run(){
		MinhaThread.escreveNome();
	}

	/*------------------------------------------------------------------*/
	public static void main (String [] args){

		MinhaThread t1 = new MinhaThread("Thread 1");
		MinhaThread t2 = new MinhaThread("Thread 2");
		MinhaThread t3 = new MinhaThread("Thread 3");

		t1.start();
		t2.start();
		t3.start();

		try{
			t1.join();
			t2.join();
			t3.join();
		}catch(InterruptedException e){}	
	}
	/*------------------------------------------------------------------*/
}


