public class Main {
     
    /*-------------------------------------------------------*/
    public static Semaforo [] fumantes = new Semaforo[3];
    public static Semaforo mutex =  new Semaforo(0);
    
    /*-------------------------------------------------------*/
    public static void main(String [] args){

	Fumante [] fumador = new Fumante[3];
	Agente age = new Agente();
	age.start();

        for(int i=0; i< 3;i++){
           fumador[i] = new Fumante(i);
           fumantes[i] = new Semaforo(0);
           fumador[i].start();
        }
    }
  
    /*-------------------------------------------------------*/
}
