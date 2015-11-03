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
