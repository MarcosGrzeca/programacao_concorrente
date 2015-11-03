import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

  
public class Linha{
	private String linha;
	private int x;
	private int y;
	private Image image;

 
	public Linha(int x, int y, String linha){
		ImageIcon icone = new ImageIcon(linha);
		image = icone.getImage();
		this.linha = linha;
		this.x = x;
		this.y = y;
	}

	 public void desenhar(Graphics g){
	    Graphics2D g2d = (Graphics2D)g;
	    g2d.drawImage(this.image, this.x, this.y, null);
	 }

}
