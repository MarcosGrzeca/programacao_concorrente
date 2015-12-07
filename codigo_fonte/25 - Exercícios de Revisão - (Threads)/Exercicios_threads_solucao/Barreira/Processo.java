public class Processo extends Thread{

	/*----------------------------------------------------------------*/
	private int id;

	/*----------------------------------------------------------------*/
	public Processo (int id){
		this.id = id;
	}

	/*----------------------------------------------------------------*/
	public void run(){
		try{
			this.sleep(id*10000);
		}catch(Exception e){
			e.printStackTrace();
		}
			
		System.out.println("Thread " + this.id + " chegando na barreira");

		Main.mutex.P();
		Main.cont++;
		if (Main.cont < Main.maxThreads){
			Main.mutex.V();
			Main.barr.P();
		}
		Main.cont--;

		Main.barr.V();
		Main.mutex.V();

		System.out.println("Thread " + this.id + " saiu da barreira");
	}
	/*----------------------------------------------------------------*/
}
