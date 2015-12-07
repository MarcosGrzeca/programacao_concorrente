public class Agente extends Thread {
    
    /*-------------------------------------------------------------*/	
    public Agente() {
    }
   
    /*-------------------------------------------------------------*/	
    public void run(){
        
        while (true){

	    int vaifumar = (int) (Math.random() * 3);  
            System.out.println("Vou liberar o fumante " + vaifumar);
	    Main.fumantes[vaifumar].V();
	    Main.mutex.P();	
        }
    }
    /*-------------------------------------------------------------*/	
}


