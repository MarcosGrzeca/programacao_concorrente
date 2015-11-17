public class MinhaThread extends Thread{

	/*------------------------------------------------------------------*/
	private int espera;

	/*------------------------------------------------------------------*/    
	public MinhaThread(String nome, int espera){
		this.setName(nome);
		this.espera = espera;
	}
    
	/*------------------------------------------------------------------*/
	public void run(){
		System.out.println("Inicio " + this.getName());
		Main.mutex.P();
		Main.cont++;
		if (Main.cont < Main.maxThreads) {
			try{
			    this.sleep(espera);
			}catch(Exception e){}
			Main.mutex.V();
			Main.barreira.P();
		} else {
		}
		
		Main.cont--;
		Main.barreira.V();
		Main.mutex.V();
		System.out.println("FIM " + this.getName());
	}
}