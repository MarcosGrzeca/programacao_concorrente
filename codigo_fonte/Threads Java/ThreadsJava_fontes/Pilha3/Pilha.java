public class Pilha {                                                
	private int [] pilha;                                     
	private int indice;
	private int tam; 

	public Pilha(int tam) {                                            
		this.indice = 0;
		this.tam = tam;
		this.pilha = new int[tam];                                                             
	}         
                                                                    
	public void push(int num) throws Exception{ 	                                                                                                      	   
		
		Main.vazio.P();
		System.out.println("Produzindo: " + num );
		Main.mutex.P();
		pilha[indice] = num;                                                         
		indice++;
		Main.mutex.V();
		Main.cheio.V();

	}                                                                                 

	public synchronized void pop() throws Exception {                                        
		Main.cheio.P();
		Main.mutex.P();
		indice--;
		System.out.println("Consumindo: " + pilha[indice] );
		Main.mutex.V();
		Main.vazio.V();
	}                                                                                     

}      



 
