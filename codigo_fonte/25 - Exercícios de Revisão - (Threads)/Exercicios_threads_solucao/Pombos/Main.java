public class Main {

	/*------------------------------------------------------*/
	public static Semaforo mutexcaixa = new Semaforo(1);
	public static Semaforo mutexpombos = new Semaforo(1);
	public static Semaforo sempombos = new Semaforo(0);
	public static Semaforo semtratador = new Semaforo(0);
	public static Semaforo semgaiola = new Semaforo(0);

    	public static Pessoa [] pessoas = new Pessoa[5];
	public static Pombo [] pombos = new Pombo[3];
	public static int numCartas = 0;
	public static int numPombos = 0;

	/*------------------------------------------------------*/
	public static void main (String [] args){

	   for(int i=0; i< 5;i++){
		pessoas[i] = new Pessoa(i);
		pessoas[i].start();
	   }	        

	   for(int i=0; i< 3;i++){
		pombos[i] = new Pombo(i);
		pombos[i].start();
	   }	   

	   Tratador tratador = new Tratador(0);
	   tratador.start();
	}
	/*------------------------------------------------------*/
}

