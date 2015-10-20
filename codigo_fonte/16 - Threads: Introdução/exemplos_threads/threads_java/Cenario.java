import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
  
public class Cenario extends JPanel {

	private Carro carro1, carro2, carro3, carro4;
	private Linha linha;

  
	 public Cenario(){
  		setFocusable(true);
		setBackground(Color.WHITE);
 		setDoubleBuffered(true);

		carro1 = new Carro(40,20,"carro1.png");
		carro2 = new Carro(40,100,"carro2.png");
		carro3 = new Carro(40,180,"carro3.png");
		carro4 = new Carro(40,260,"carro4.png");
		linha = new Linha(800,0,"linha.png");

		carro1.start();
		carro2.start();
		carro3.start();
		carro4.start();

	 }
   
	 public void paint(Graphics g) {
  
		 super.paint(g);
		 Graphics2D g2d = (Graphics2D)g;
 		
		 carro1.desenhar(g);
		 carro2.desenhar(g);
		 carro3.desenhar(g);
		 carro4.desenhar(g);
		 linha.desenhar(g);
		 repaint();
		 g.dispose();
	 }

}

