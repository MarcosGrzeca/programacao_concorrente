public class Pilha {                                                
	private int [] pilha;                                     
	private int indice;
	private int tam; 

	public Pilha(int tam) {                                            
		this.indice = 0;
		this.tam = tam;
		this.pilha = new int[tam];                                                             
	}         
                                                                    
	public synchronized void push(int num) throws Exception {                                                                                                         
		if ( indice == tam-1) throw new Exception("Fila cheia!");                         
		System.out.println("Produzindo: " + num );
		pilha[indice] = num;                                                         
		indice++;
	}                                                                                 

	public synchronized void pop() throws Exception {                                        
		if (indice == 0 ) throw new Exception("Fila vazia!");                        
		indice--;
		System.out.println("Consumindo: " + pilha[indice] );
	}                                                                                     

}      



 
