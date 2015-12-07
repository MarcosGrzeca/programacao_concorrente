public class Main {
	
	/*----------------------------------------------------------------*/
	public static final int maxThreads = 5;
	public static int  cont = 0;
	public static Semaforo mutex = new Semaforo(1); 
	public static Semaforo barr = new Semaforo(0); 

	/*----------------------------------------------------------------*/
	public static void main (String [] args){

		Processo  [] p = new Processo[maxThreads]; 
		
		for(int i = 0; i< maxThreads; i++){
			p[i] = new Processo(i);
			p[i].start();
		}


		for(int i = 0; i < maxThreads; i++){
			try{
			   p[i].join();
			}catch(Exception e){System.out.println(e);}
		}
	}
	/*----------------------------------------------------------------*/
}

