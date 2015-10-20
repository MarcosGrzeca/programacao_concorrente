import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

  
public class Carro extends Thread {
	private String carro;
	private int x;
	private int y;
	private int dx;
	private int dy;
	private Image imagem;

	private static boolean parar = false;

  
	public Carro(int x, int y, String carro){

		ImageIcon icone = new ImageIcon(carro);
		imagem = icone.getImage();
		this.dx = imagem.getWidth(null);
		this.dy = imagem.getHeight(null);   

		this.carro = carro;
		this.x = x;
		this.y = y;
	}


	public void run(){

		Random random = new Random();
		while ( this.x + this.dx < 800 && Carro.parar != true ){

			try{
				Thread.sleep(random.nextInt(500));
			}
			catch(InterruptedException e){}
			
			this.mover();

		}
		
		Carro.parar = true;
	}


	public void mover(){
		this.x += 10;
	}


	 public void desenhar(Graphics g){
	    Graphics2D g2d = (Graphics2D)g;
	    g2d.drawImage(this.imagem, this.x, this.y, null);
	 }

}
