package main;

import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.JRadioButton;

public class CifrarPanel extends JPanel implements ActionListener {
	
	JFrame janela;
	JFileChooser chooser1 = new JFileChooser();
	JFileChooser chooser2 = new JFileChooser();
	JLabel label1 = new JLabel("Escolha o arquivo que deseja cifrar:");
	JLabel label2 = new JLabel("Escolha o diretorio para salvar o arquivo cifrado:");
	JLabel label3 = new JLabel("Digite a senha (16 caracteres):");
	JLabel label4 = new JLabel("Confirme a senha:");
	JLabel label5 = new JLabel("Mostrar senha");
	JTextField cifrarPath = new JTextField(40);
	JTextField cifradoPath = new JTextField(40);
	JPasswordField password = new JPasswordField(25);
	JPasswordField confPassword = new JPasswordField(25);
	JButton escolher1 = new JButton("Escolher...");
	JButton escolher2 = new JButton("Escolher...");
	JButton cifrarBtn = new JButton("Cifrar");
	JButton cancelarBtn = new JButton("Cancelar");
	JCheckBox checkbox = new JCheckBox();
	JRadioButton rb1 = new JRadioButton("8bits");
	JRadioButton rb2 = new JRadioButton("64bits Esquerda");
	JRadioButton rb3 = new JRadioButton("64bits Direita");
	private JPanel panel1 = new JPanel(new FlowLayout(FlowLayout.LEFT));
	private JPanel panel2 = new JPanel(new FlowLayout(FlowLayout.LEFT));
	private JPanel panel3 = new JPanel(new FlowLayout(FlowLayout.LEFT));
	private JPanel panel4 = new JPanel(new FlowLayout(FlowLayout.LEFT));
	private JPanel panel5 = new JPanel(new FlowLayout(FlowLayout.CENTER));
	private JPanel panel6 = new JPanel(new FlowLayout(FlowLayout.CENTER));
	
	
	public CifrarPanel(JFrame janela){
		
		this.janela = janela;
		setLayout(new GridLayout(10,1));
		
		chooser1.setFileSelectionMode(JFileChooser.FILES_ONLY);
		chooser2.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		escolher1.addActionListener(this);
		escolher2.addActionListener(this);
		cifrarBtn.addActionListener(this);
		cancelarBtn.addActionListener(this);
		checkbox.addActionListener(this);
		panel1.add(cifrarPath);
		panel1.add(escolher1);
		panel2.add(cifradoPath);
		panel2.add(escolher2);
		panel3.add(password);
		panel3.add(checkbox);
		panel3.add(label5);
		panel4.add(confPassword);		
		panel6.add(rb1);
		panel6.add(rb2);
		panel6.add(rb3);
		panel5.add(cifrarBtn);
		panel5.add(cancelarBtn);
		add(label1);
		add(panel1);
		add(label2);
		add(panel2);
		add(label3);
		add(panel3);
		add(label4);
		add(panel4);
		add(panel6);
		add(panel5);
	}


	
	public void actionPerformed(ActionEvent e){
		Object source = e.getSource();
		if (!checkbox.isSelected()) {
			password.setEchoChar('*');
    	} else {
    		password.setEchoChar((char) 0);
    	}
		if(source.hashCode() == escolher1.hashCode()){
			int returnVal = chooser1.showOpenDialog(this);
			if(returnVal == JFileChooser.APPROVE_OPTION){
				File file = chooser1.getSelectedFile();
				cifrarPath.setText(file.getPath());
			}
		}else if(source.hashCode() == escolher2.hashCode()){
			int returnVal = chooser2.showOpenDialog(this);
			if(returnVal == JFileChooser.APPROVE_OPTION){
				File file = chooser2.getSelectedFile();
				cifradoPath.setText(file.getPath());
			}
		}else if(source.hashCode() == cifrarBtn.hashCode()){
			Alpha alpha = new Alpha();
			System.out.println(String.valueOf(password.getPassword()));
			System.out.println(String.valueOf(confPassword.getPassword()));
			System.out.println(cifrarPath.getText());
			System.out.println(cifradoPath.getText());
			int mode;
			int size;
			if(rb1.isSelected()) {
				size = Alpha._8bits;
				mode = 1;
				}
			else { size = Alpha._64bits;
				if(rb2.isSelected()) mode = Alpha.ESQUERDA;
				else mode = Alpha.DIREITA;
			}
			
			System.out.println("mode " + mode + " size " +size);
			alpha.cifrar(String.valueOf(password.getPassword()),String.valueOf(confPassword.getPassword()),cifrarPath.getText(),cifradoPath.getText(), mode, size);
		}else if(source.hashCode() == cancelarBtn.hashCode()){
			
			janela.getContentPane().removeAll();
			janela.setContentPane(new MainPanel(janela));
			janela.revalidate();
			janela.repaint();
		}
	}
	
}
