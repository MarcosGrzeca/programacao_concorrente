public class Semaforo {
    
    /*---------------------------------------------------------*/	
    private int recursos;
    
    /*---------------------------------------------------------*/
    public Semaforo(int recursos) {
            this.recursos = recursos;
    }
    
    /*---------------------------------------------------------*/
    public synchronized void P( ){
        
        while (recursos==0){
            try{
                wait();
            }catch (InterruptedException e){
                System.out.println(e);
            }
        }
        recursos--;
    }
    
    /*---------------------------------------------------------*/    
    public synchronized void V(){
        recursos++;
        notify();
    }
    /*---------------------------------------------------------*/
    
}
