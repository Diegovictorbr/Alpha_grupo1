package main;

import java.io.File;

public class RunForAll {
	
	//static ImageIcon imgObject = new ImageIcon(janela.getClass().getResource("AlphaLogo.bpm"));
	//static JLabel imgLabel = new JLabel("JAVA - Interface Grafica", imgObject, JLabel.RIGHT);
	
    public void cifrarAll(String senha, String confirmation, String inputFolderName, String outPutFolderName){
    	Alpha myAlpha = new Alpha();
        File folder = new File(inputFolderName);
        File [] inputFiles = folder.listFiles();

        for(int i = 0; i < inputFiles.length; i++){
        	myAlpha.cifrar(senha, confirmation, inputFolderName + inputFiles[i].getName(), outPutFolderName + "alpha_" + inputFiles[i].getName(), Alpha.DIREITA, Alpha._64bits);
        }
        
    }
    public void decifrarAll(String senha, String confirmation, String inputFolderName, String outPutFolderName){
    	Alpha myAlpha = new Alpha();
        File folder = new File(inputFolderName);
        File [] inputFiles = folder.listFiles();

        for(int i = 0; i < inputFiles.length; i++){
        	myAlpha.decifrar(senha, confirmation, inputFolderName + inputFiles[i].getName(), outPutFolderName + "decifrado_" + inputFiles[i].getName(), Alpha.DIREITA, Alpha._64bits);
        }
        
    }
    
    
	public static void main(String[] args) {
		RunForAll vairodar = new RunForAll();
		vairodar.cifrarAll("abcdefghijklmnop", "abcdefghijklmnop", "/Users/hallpaz/Workspace/General/NossoAlpha/inTestBase/", "/Users/hallpaz/Workspace/General/NossoAlpha/outTestBase_R64bits/");
		
		vairodar.decifrarAll("abcdefghijklmnop", "abcdefghijklmnop", "/Users/hallpaz/Workspace/General/NossoAlpha/outTestBase_R64bits/", "/Users/hallpaz/Workspace/General/NossoAlpha/decifrados_R64bits/");

		
	}

}
