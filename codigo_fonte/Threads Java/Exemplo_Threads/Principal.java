import javax.swing.JFrame;
import java.awt.event.*;
  
public class Principal extends JFrame{
  
	 public static void main(String[] args){
		JFrame frame = new JFrame();
		frame.getContentPane().add(new Cenario());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(840, 360);
		frame.setLocationRelativeTo(null);
		frame.setTitle("Exemplo - Threads");
		frame.setResizable(false);
		frame.setVisible(true);
	 }

}
