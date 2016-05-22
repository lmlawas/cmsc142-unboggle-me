import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.nio.file.*;
import java.io.IOException;
import javax.swing.JScrollPane;
import java.io.*;
import java.util.*;
import javax.imageio.*;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;

public class UnboggleUI extends JFrame{
	
	private JFrame frame;
	private JPanel unbogglePanel;
	private JPanel optionsPanel;
	private JPanel gridPanel;
	private JButton btnStart;
	private JButton btnNext;
	private JButton btnAns;
	private GridBagConstraints g;
	private int size = 1;
	private int trayCount = 0;
	private int initial = 1;
	private JButton[][] board;// = new JButton[initial][initial];

	LinkedList<Tray> trays = new LinkedList<Tray>();
	Trie dictionary = new Trie();
	boolean success_reading =false;

	UnboggledUI answer;

	/****************************************
		Launch application
	****************************************/
	public static void main(String[] args){
		EventQueue.invokeLater(new Runnable (){
			public void run() {
				try	{
					UnboggleUI ui = new UnboggleUI();
					ui.frame.setVisible(true);
				} catch (Exception e){
					e.printStackTrace();
				}
			}
		});
	}

	public UnboggleUI(){
		initialize();
	}

	private void initialize(){
		frame = new JFrame ("Unboggle Me");
		frame.setResizable(false);
		frame.setBounds(100,100, 650, 700);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BorderLayout(0,0));
		
		optionsPanel = new JPanel();

		btnStart = new JButton("LOAD TRAYS");		//starts setting up the board with all trays	
		btnStart.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				start(e);
			}
		});

		btnNext = new JButton("NEXT TRAY");		//get next tray
		btnNext.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				next(e);
			}
		});
		btnNext.setEnabled(false);

		btnAns = new JButton("SHOW VALID WORDS");
		btnAns.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				show_answer(e);
			}
		});
		btnAns.setEnabled(false);

		optionsPanel.add(btnStart);
		optionsPanel.add(btnNext);
		optionsPanel.add(btnAns);

		gridPanel = new JPanel(new GridBagLayout());
		g = new GridBagConstraints();
		g.gridx = 0;
		g.gridy = 0;
		g.weightx = 1;
		g.weighty = 1;
		gridPanel.setBackground(Color.WHITE);

		frame.getContentPane().add(optionsPanel, BorderLayout.SOUTH);
		frame.getContentPane().add(gridPanel, BorderLayout.CENTER);

		//Loading of pre-set trays (TRY MAKE READ FILE WORK)
		success_reading = readDictionary (dictionary);
		if(success_reading){
			success_reading = readTrays("input.txt", trays, dictionary );
		}
		if(!success_reading){
			btnStart.setEnabled(false);			
		}
	}

	private void start(ActionEvent e){		
	/***************************************************************************
			Action button for loading up all trays
    ***************************************************************************/
		loadTray(trays.get(trayCount));
		gridPanel.revalidate();
		gridPanel.repaint();
		btnNext.setEnabled(true);
		btnAns.setEnabled(true);
	}

	private void next(ActionEvent e){	
	/***************************************************************************
			Action button for loading the next tray
    ***************************************************************************/	
		if(trays.size() == 0){
			btnNext.setEnabled(false);
		}
		trayCount = (trayCount + 1) % trays.size(); //if trayCount reaches max, it will go back to the first tray
		gridPanel.removeAll();
		gridPanel.updateUI();
		loadTray(trays.get(trayCount));
		gridPanel.revalidate();
		gridPanel.repaint();

	}

	private void loadTray(Tray t){
	/***************************************************************************
			Makes the board for the selected tray
    ***************************************************************************/
		int s = t.size;

		board = new JButton[s][s];
		for(int i = 0; i < s; i++){
			 	g.gridy = i;
			 	for(int j = 0; j < s; j++){
			 		g.gridx = j;
			 		g.fill = GridBagConstraints.BOTH;
					board[i][j] = new JButton(""+t.values[i][j].c);
					board[i][j].setBackground(new Color(232,175,167));
					board[i][j].setFont(new Font("Arial", Font.BOLD, 50));
						//add action listener
					gridPanel.add(board[i][j]);
					gridPanel.add(board[i][j],g);
			}
		}	
		gridPanel.revalidate();
		gridPanel.repaint();
	}

	private void show_answer(ActionEvent e){		
		//answer = new UnboggledUI();
		answer = new UnboggledUI(trays.get(trayCount));
	}

	private static boolean readDictionary(Trie root){
    /***************************************************************************
        This method reads dictionary.txt and adds them to the Trie.
    ***************************************************************************/

        try{
            FileReader fr = new FileReader("dictionary.txt");
            BufferedReader br = new BufferedReader( fr );
            String word = null;
            while( (word = br.readLine()) != null ) {
                if( word.length() < 3 ) continue;
                root.addWord(word);
            }
            
            fr.close();	// stop reading
            
            return true; // if reading dictionary is successful
        }catch( IOException e ){
			System.out.println("No dictionary.txt file found.");
		}
		return false; // if reading dictionary is not successful
    }// end of readDictionary()

	private static boolean readTrays(String filename, LinkedList<Tray> trays, Trie dictionary){
	/***************************************************************************
		This method reads input.txt to get the values of the trays,
		as well as the list of valid words generated from the tray
		by searching the dictionary.
	***************************************************************************/
		try{
			FileReader fr = new FileReader(filename);
			BufferedReader br = new BufferedReader( fr );

			// get number of trays
			int noOfTrays = Integer.parseInt( br.readLine() );

			for( int i = 0; i < noOfTrays; i++ ){
				
				int size = Integer.parseInt( br.readLine() );
				char[][] values = new char[size][size];

				for( int j = 0; j < size; j++ ){
					String row = br.readLine();
					char[] arr = row.toCharArray();
					int n = 0;

					// update values attribute of the tray
					for( int k = 0; k < row.length(); k++ ){
						if( arr[k] != ' '){
							values[j][n] = arr[k];
							n++;
						}
					}

				}
				Tray tray = new Tray( values, size, dictionary );
				// add the tray instance
				trays.add( tray );
			}
			fr.close();	// stop reading
            return true; // if reading dictionary is successful
		}catch( IOException e ){
			System.out.println("No input.txt file found.");
		}
		return false; // if reading dictionary is not successful
	}// end of readTrays()


	//board button actions
	private void disable(int i, int j){
		board[i][j].setText("x");
		board[i][j].setEnabled(false);
	}

	private void enable(int i, int j){
		board[i][j].setText("x");
		board[i][j].setEnabled(true);
	}

}