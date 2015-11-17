public class Semaforo {

	/*------------------------------------------------------------------*/   
	private int recursos;
    	
	/*------------------------------------------------------------------*/
	public Semaforo(int recursos) {
      		this.recursos = recursos;
	}
    
	/*------------------------------------------------------------------*/
	public synchronized void P( ){
      		while (recursos==0){
            		try{
                  		this.wait();
            		}catch (InterruptedException e){}
      		}
      		recursos--;
	}
	
	/*------------------------------------------------------------------*/    
  	public synchronized void V(){
  		recursos++;
  		this.notifyAll();
	}
	/*------------------------------------------------------------------*/
}
