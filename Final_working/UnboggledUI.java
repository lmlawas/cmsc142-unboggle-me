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

public class UnboggledUI {

	private JFrame frame;
	private JPanel panel;
	private JTextArea list;
	private JScrollPane scroll;
	LinkedList<String> words;

	public UnboggledUI(Tray t){
		frame = new JFrame("Answer Key");
		frame.setResizable(false);
		frame.setBounds(750, 100, 350, 600);
		//frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		
		panel = new JPanel();
		list = new JTextArea(30, 30);
		list.setFont(new Font("Arial", Font.PLAIN, 15));
		words = t.valid_words;
		showAnswers(words);

		list.setEditable(false);
		JScrollPane scroll = new JScrollPane (list);
	 	scroll.setVerticalScrollBarPolicy ( ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS );
	 	panel.add(scroll);

	 	frame.add(panel);
	 	frame.pack();
	 	frame.setVisible(true);

	}

	private void showAnswers(LinkedList<String> w){
		if(w.size() == 0){
			list.setText("There is NO SOLUTION for this tray :(");
		}
		else if(w.size() == 1)
			list.setText("There is "+w.size()+" word valid\n");
		else{
			list.setText("There are "+w.size()+" words valid\n");
			for(int i = 0; i < w.size(); i++){
				list.append(""+(i+1)+".) "+w.get(i)+"\n");
			}
		}
	}
}