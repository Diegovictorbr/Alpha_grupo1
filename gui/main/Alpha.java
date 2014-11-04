package main;

import java.awt.FlowLayout;
import java.awt.GridLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Alpha {
	 static {
      System.loadLibrary("alpha"); // Load native library at runtime
                                   // hello.dll (Windows) or libhello.so (Unixes)
   }

	public static final int _8bits = 0;
	public static final int _64bits = 1;
	public static final int DIREITA = 0;
	public static final int ESQUERDA = 1;
	
	public native void decifrar(String senha, String confirmation, String inFileName, String outFileName, int mode, int size);
	
	public native void cifrar(String senha, String confirmation, String inFileName, String outFileName, int mode, int size);
	
	static JFrame janela = new JFrame("Alpha");

	

	
	//static ImageIcon imgObject = new ImageIcon(janela.getClass().getResource("AlphaLogo.bpm"));
	//static JLabel imgLabel = new JLabel("JAVA - Interface Grafica", imgObject, JLabel.RIGHT);
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		
		janela.setContentPane(new MainPanel(janela));
		
		configPanels();
		
		janela.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		janela.setSize(600,400);//define o tamanho da janela
		janela.setVisible(true);//exibe a janela
		janela.setResizable(false);
	}
	public static void configPanels(){
		

		//panel2.add(imgLabel);

		
		

	}

}
