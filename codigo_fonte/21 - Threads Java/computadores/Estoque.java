public class Estoque {

	private int quantidade;

	public Estoque(int quantidade) {
		this.quantidade = quantidade;
	}
	
	public void inserirEstoque(int quantidade) {
		this.quantidade += quantidade;
	}

	public void removerEstoque(int quantidade) {
		this.quantidade += quantidade;
	}
}