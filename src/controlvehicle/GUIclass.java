package controlvehicle;

import javax.imageio.ImageIO;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Point;

import javax.swing.JLabel;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.swing.JOptionPane;
import javax.swing.SwingConstants;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JButton;
import javax.swing.JTextField;

import java.awt.Font;

public class GUIclass {

	private JFrame frame;
	private JLabel l1;
	private JLabel l2;
	private JLabel l3;
	private JLabel l4;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	private JTextField textField_3;
	private JLabel startStop;
	private JPanel panelC;
	private JPanel panelN;
	private JPanel panelE;
	private Controller controller;
	private Socket socket;
	private View vievOBJ;
	private JFrame videoFrame;
	private Point point;
	/**
	 * Create the application.
	 */
	public GUIclass(Socket s, Point p) {
		socket = s;
		initialize();
		frame.setVisible(true);
		point = p;
	 
	}

	/**
	 * 
	 * return the size of main window
	 */
	public Dimension getFrameSize() {
		return frame.getSize();
	}

	/**
	 * return the size of center panel
	 * 
	 */
	public Dimension getPanelCSize() {
		return panelC.getSize();

	}

	/**
	 * set value of distance in labels on screen
	 * 
	 * @param a
	 *            - 1st sonar
	 * @param b
	 * @param c
	 * @param d
	 *            4th sonar
	 */
	public void setSonarLabel(String a, String b, String c, String d) {

		int n = 5;
		String nA = a.substring(0, Math.min(a.length(), n));
		String nB = b.substring(0, Math.min(b.length(), n));
		String nC = c.substring(0, Math.min(c.length(), n));
		String nD = d.substring(0, Math.min(d.length(), n));

		textField.setText(nA);
		textField_1.setText(nB);
		textField_2.setText(nC);
		textField_3.setText(nD);

	}

	/**
	 * INITIALIZE START/STOP ICON
	 */
	private void iconInit() {

		BufferedImage StartIcon = null;
		BufferedImage StopIcon = null;

		try {
			StartIcon = ImageIO.read(new File("power_on.png"));
			StopIcon = ImageIO.read(new File("power_off.png"));
		} catch (IOException e) {
			System.out.println("Nie mozna zaladowac ikon");
			e.printStackTrace();
		}

		final ImageIcon imgStart = new ImageIcon(StartIcon);
		final ImageIcon imgStop = new ImageIcon(StopIcon);

		startStop = new JLabel("", imgStart, JLabel.CENTER);
		panelN.add(startStop);

		JButton btnStart_1 = new JButton("Start");
		panelN.add(btnStart_1);

		JButton btnStop = new JButton("Stop");
		panelN.add(btnStop);

		btnStart_1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				//new MainClass();

				startStop.setIcon(imgStart);

				Thread t2 = new Thread(socket);
				socket.flag=true;
				t2.start();
			}
		});

		btnStop.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				startStop.setIcon(imgStop);
				socket.stopStream();
			}
		});

	}

	/**
	 * INITIALIZE textFields
	 */
	private void textFieldsInit() {
		textField = new JTextField();
		textField.setFont(new Font("Dialog", Font.PLAIN, 30));
		textField.setEditable(false);
		textField.setText("");
		textField.setColumns(1);
		panelE.add(textField);

		panelE.add(l2);

		textField_1 = new JTextField();
		textField_1.setColumns(1);
		textField_1.setFont(new Font("Dialog", Font.PLAIN, 30));
		textField_1.setEditable(false);
		textField_1.setText("");
		panelE.add(textField_1);

		panelE.add(l3);

		textField_2 = new JTextField();
		textField_2.setColumns(1);
		textField_2.setFont(new Font("Dialog", Font.PLAIN, 30));
		textField_2.setEditable(false);
		textField_2.setText("");
		panelE.add(textField_2);
		panelE.add(l4);

		panelC.setBackground(new Color(14, 124, 18));
		panelC.add(vievOBJ);

		l2.setHorizontalAlignment(SwingConstants.CENTER);

		textField_3 = new JTextField();
		textField_3.setColumns(1);
		textField_3.setFont(new Font("Dialog", Font.PLAIN, 30));
		textField_3.setEditable(false);
		textField_3.setText("");

		panelE.add(textField_3);

	}

	/**
	 * INITIALIZE JMenu
	 */
	private void jmenuInit() {
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);

		JMenu mnNewMenu = new JMenu("File");
		menuBar.add(mnNewMenu);

		JMenuItem menuItem = new JMenuItem("New map");
		mnNewMenu.add(menuItem);
		menuItem.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				
				vievOBJ.clear();
			}
		});
		
		
		
		JMenuItem mntmM = new JMenuItem("Start");
		mnNewMenu.add(mntmM);
		mntmM.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				Thread t2 = new Thread(socket);
				socket.flag=true;
				t2.start();


			}
		});
		

		JMenuItem mntmM_1 = new JMenuItem("Stop");
		mnNewMenu.add(mntmM_1);
		mntmM_1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				socket.stopStream();

			}
		});

		JMenuItem mntmM_2 = new JMenuItem("Save map");
		mnNewMenu.add(mntmM_2);
		mntmM_2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				
				vievOBJ.save();

			}
		});

		
		JMenuItem mntmM_3 = new JMenuItem("Exit");
		mnNewMenu.add(mntmM_3);
		mntmM_3.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				int result = JOptionPane.showConfirmDialog(null, "Are you sure?");
				if(result == JOptionPane.YES_OPTION)
						System.exit(0);	
			}
		});
		JMenu mnEdit = new JMenu("Edit");
//		menuBar.add(mnEdit);

		JMenuItem mntmE = new JMenuItem("e1");
		//mnEdit.add(mntmE);

		JMenuItem mntmE_1 = new JMenuItem("e2");
	//	mnEdit.add(mntmE_1);

		JMenu mnWindow = new JMenu("Window");
//		menuBar.add(mnWindow);

		JMenu mnHelp = new JMenu("Help");
		menuBar.add(mnHelp);

		JMenuItem mntmAbout = new JMenuItem("About");
		mnHelp.add(mntmAbout);
		mntmAbout.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				JOptionPane.showMessageDialog(null, "Jakub Brzoza - Radar NeuroUV 2015");
				
			}
		});

	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {

		
		//int x = (int)point.getX();
		//int y = (int)point.getY();
		 
		frame = new JFrame("Radar - NeuroUV");
		frame.setLocation(550,100);
		//frame.setLocation(point);
		//frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		panelC = new JPanel();
		panelE = new JPanel();
		panelN = new JPanel();
		
		vievOBJ = new View(this);
		controller = new Controller(vievOBJ, this, socket);
		controller.start();
		
		//////
		//GUI
		//////
		
		// labels
		l1 = new JLabel("Front-left sonar");
		l2 = new JLabel("Front-center sonar");
		l3 = new JLabel("Front-right sonar");
		l4 = new JLabel("Back sonar");

		
		// init BorderLayout
		frame.getContentPane().add(panelC, BorderLayout.CENTER);
		frame.getContentPane().add(panelN, BorderLayout.NORTH);
		frame.getContentPane().add(panelE, BorderLayout.EAST);
		
		panelE.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		panelE.setLayout(new BoxLayout(panelE, BoxLayout.Y_AXIS));
		panelE.add(l1);

		
		iconInit();

		textFieldsInit();

		jmenuInit();
		
		frame.pack();

	}

}
