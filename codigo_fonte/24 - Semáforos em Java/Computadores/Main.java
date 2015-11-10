public class Main {
    
    /*---------------------------------------------------------*/	
    public static Semaforo mutex = new Semaforo(1);
    public static Semaforo exclusao = new Semaforo(1);
    
    /*---------------------------------------------------------*/
    public static int CONSULTA = 0;
    public static int VENDE = 1;
    public static int COMPRA = 2;
    
    /*---------------------------------------------------------*/	
    public static int leitores = 0;
    public static int quantidade = 100;
  
    /*---------------------------------------------------------*/
    public static void main(String [] args){
      
        Computadores thr1 = new Computadores(1,COMPRA, 50);
        Computadores thr2 = new Computadores(2,CONSULTA, 50);
        Computadores thr3 = new Computadores(3,CONSULTA, 50);
        Computadores thr4 = new Computadores(4,VENDE, 10);
        Computadores thr5 = new Computadores(5,CONSULTA, 50);
        Computadores thr6 = new Computadores(6,VENDE, 20);
        
        thr1.start();
        thr2.start();
        thr3.start();
        thr4.start();
        thr5.start();
        thr6.start();
    }
    /*---------------------------------------------------------*/
}
