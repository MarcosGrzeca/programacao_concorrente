public class Consumidor extends Thread {

	Pilha pilha; 
	
	public Consumidor(Pilha pilha){
		this.pilha = pilha;
	}

	public void run(){ 
		while ( true ){
			try { 
				this.sleep((long)(Math.random() * 5000)); 
				pilha.pop();	

			} catch (Exception e) {
				System.out.println(e);
			}
		} 
	}
}
