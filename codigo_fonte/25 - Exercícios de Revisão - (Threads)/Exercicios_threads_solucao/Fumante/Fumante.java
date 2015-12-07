public class Fumante extends Thread {
   
    /*----------------------------------------------------*/	 
    private int id;
    
    /*----------------------------------------------------*/	
    public Fumante(int id) {
          this.id = id;
    }
   
    /*----------------------------------------------------*/	
    public void run(){
        
        while (true){
            System.out.println("Fumante " + this.id + " querendo fumar!!");
	    Main.fumantes[this.id].P();
            System.out.println("Fumante " + this.id + " fumando!!!");
	    try{
                   sleep(2000);
            }catch(InterruptedException e){}
            System.out.println("Fumante " + this.id + " terminando de fumar!!!");
	    Main.mutex.V();	
        }
    }

    /*----------------------------------------------------*/		
}
