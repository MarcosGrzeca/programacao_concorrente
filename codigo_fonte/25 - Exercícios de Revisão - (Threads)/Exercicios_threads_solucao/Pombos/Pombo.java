public class Pombo extends Thread {

	/*------------------------------------------------------*/
	private int id;

	/*------------------------------------------------------*/
	public Pombo ( int id ){
		this.id = id;
	}

	/*------------------------------------------------------*/
	public void run(){
		while (true){
			try{
				sleep((long)(Math.random() * 10000));
			}catch(Exception e){}

			Main.mutexcaixa.P();
			while (Main.numCartas < 5 ) {
				System.out.println("Pombo " + this.id + " Cartas insuficientes " + Main.numCartas);
				Main.mutexcaixa.V();
				Main.sempombos.P();
	
			}
			Main.numCartas -= 5;
			System.out.println("Pombo " + this.id + " Pegando cartas " + Main.numCartas);
			Main.mutexcaixa.V();

			try{
				sleep((long)(Math.random() * 10000));
			}catch(Exception e){}

			Main.mutexpombos.P();
			Main.numPombos++;
			System.out.println("Pombo " + this.id + " Chegou no destino " + Main.numPombos);
			Main.semtratador.V();
			Main.mutexpombos.V();
			System.out.println("Pombo " + this.id + " bloqueou " + Main.numPombos);
			Main.semgaiola.P();
			System.out.println("Pombo " + this.id + " liberado " + Main.numPombos);

		}
	}
	/*------------------------------------------------------*/
	
}

