public class Tratador extends Thread {

	/*------------------------------------------------------*/
	private int id;

	/*------------------------------------------------------*/
	public Tratador ( int id ){
		this.id = id;
	}

	/*------------------------------------------------------*/
	public void run(){

		while (true ){

			Main.semtratador.P();
			Main.mutexpombos.P();
			if ( Main.numPombos >= 2 ){	
				while (Main.numPombos > 0){
					Main.numPombos--;
					Main.semgaiola.V();
				}
				System.out.println("Tratador liberando os pombos");	
			}
			Main.mutexpombos.V();
		}				
		
	}
	/*------------------------------------------------------*/	

}

