package main;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class MainPanel extends JPanel  implements ActionListener{

	static private JFrame janela;
	static private JPanel panel1 = new JPanel();
	static private JPanel panel2 = new JPanel();
	
	//Buttons
	static private JButton cifrarBtn = new JButton("Cifrar");
	static private JButton decifrarBtn = new JButton("Decifrar");
	
	public MainPanel(JFrame janela){
		
		this.janela = janela;
		setLayout(new GridLayout(2,1));
		
		panel1.add(cifrarBtn);
		panel1.add(decifrarBtn);
		
		cifrarBtn.addActionListener(this);
		decifrarBtn.addActionListener(this);
		add(panel1);
		add(panel2);
		
		//cifrarBtn.addActionListener(arg0)
	
	}
	
	public void actionPerformed(ActionEvent e){
		Object source = e.getSource();
		if(source.hashCode() == cifrarBtn.hashCode()){
			cifrarBtnClick();
		}else if(source.hashCode() == decifrarBtn.hashCode()){
			decifrarBtnClick();
		}
	}
	
	private void cifrarBtnClick(){
		janela.getContentPane().removeAll();
		
		janela.setContentPane(new CifrarPanel(janela));
		janela.revalidate();
		janela.repaint();
	}
	
	private void decifrarBtnClick(){
        janela.getContentPane().removeAll();
		
		janela.setContentPane(new DecifrarPanel(janela));
		janela.revalidate();
		janela.repaint();
	}
}
