public class Pessoa extends Thread {

	/*-------------------------------------------------------------------------*/
	private int id;

	/*-------------------------------------------------------------------------*/
	public Pessoa ( int id ){
		this.id = id;
	}

	/*-------------------------------------------------------------------------*/
	public void run(){

		while ( true ){
			try{
				sleep((long)(Math.random() * 50000));
			}catch(Exception e){}

			Main.mutexcaixa.P();
			System.out.println("Pessoa: " + this.id + " Cartas inicias: " + Main.numCartas);
			Main.numCartas += (int)(Math.random() * 10);
			System.out.println("Pessoa: " + this.id + " Cartas finais: " + Main.numCartas);
			Main.mutexcaixa.V();
			Main.sempombos.V();
		}
	}
	/*-------------------------------------------------------------------------*/

}

