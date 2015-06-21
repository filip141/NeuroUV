package controlvehicle;

import java.awt.EventQueue;
import java.awt.Image;

import javax.swing.JFrame;

import java.awt.BorderLayout;

import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.BoxLayout;
import javax.swing.SwingConstants;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.SocketException;
import java.net.URL;
import java.net.UnknownHostException;

import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;


// Windows Class
public class JControlWin implements Runnable{

	private JFrame frame;
	private JSocket sock;
	private JLabel videolabl;
	private JButton btnNewButton;
	private JButton btnNewButton_1;
	private JButton btnRight;
	private JButton btnLeft;
	private JPanel panel_1;
	private Thread stoppingThread; 
	private MainPref netPref =  new MainPref();
	private int sliderValue;
 
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					JControlWin window = new JControlWin();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 * 
	 * @throws IOException
	 * @throws MalformedURLException
	 */
	public JControlWin() throws MalformedURLException, IOException {
		sliderValue = 30;
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 * 
	 * @throws IOException
	 * @throws MalformedURLException
	 */
	private void initialize() throws MalformedURLException, IOException {
		
		// Create Frame
		frame = new JFrame("DesktopUV - Video Streaming");
		frame.setBounds(100, 100, 450, 500);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		
		// Build Video Stream with panel 
		videolabl = new JVideo(netPref.getIP());
		panel_1 = new JPanel();
		
		// Menu Bar
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		

		JMenu mnNewMenu = new JMenu("Preferences");
		menuBar.add(mnNewMenu);
		mnNewMenu.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
					

				
			}
		});
		
		
		// Menu Bar Network Preferences listener
		JMenu mnNewMenu2 = new JMenu("About");
		menuBar.add(mnNewMenu2);

		JMenuItem menuItem = new JMenuItem("Network");
		mnNewMenu.add(menuItem);
		menuItem.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
					
				netPref.setVisible(true);
				
				
			}
		});

		
		// Exit application
		JMenuItem menuItem4 = new JMenuItem("Exit");
		mnNewMenu.add(menuItem4);
		menuItem4.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				int result = JOptionPane.showConfirmDialog(null, "Are you sure?");
				if(result == JOptionPane.YES_OPTION)
						System.exit(0);	
			}
		});

		
		// Help acction listener
		JMenuItem menuItem3 = new JMenuItem("Help");
		mnNewMenu2.add(menuItem3);
		menuItem3.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				JOptionPane.showMessageDialog(null, "RobotCon Application to control NeuroUV");
			}
		});
		
	
		
		// Panel with buttons up,down ... 
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.SOUTH);
		panel.setLayout(new BorderLayout(0, 0));

		
		// Up Arrow listener
		ImageIcon upArrow = new ImageIcon("up.png");
		Image resizedUpArrow = upArrow.getImage();
		Image newResizedUpArrow = resizedUpArrow.getScaledInstance(30, 30,
				java.awt.Image.SCALE_SMOOTH);
		btnNewButton = new JButton(new ImageIcon(newResizedUpArrow));
		btnNewButton.addMouseListener(new MouseAdapter() {
			boolean mousePressed;
			public void mousePressed(MouseEvent e) {
				mousePressed = true;
				new Thread() {
					public void run() {
						while (mousePressed) {
							String command = Integer.toString(sliderValue) + " " + "0";
							try {
								sock.sendPacket(command);
							} catch (IOException e) {
								e.printStackTrace();
							}
						}
					}

				}.start();
			}

			public void mouseReleased(MouseEvent e) {
				mousePressed = false;
			}

		});
		panel.add(btnNewButton, BorderLayout.NORTH);

		
		// Down Arrow listener
		ImageIcon downArrow = new ImageIcon("down.png");
		Image resizedDownArrow = downArrow.getImage();
		Image newResizedDownArrow = resizedDownArrow.getScaledInstance(30, 30,
				java.awt.Image.SCALE_SMOOTH);
		btnNewButton_1 = new JButton(new ImageIcon(newResizedDownArrow));
		btnNewButton_1.addMouseListener(new MouseAdapter() {
			boolean mousePressed;

			public void mousePressed(MouseEvent e) {
				mousePressed = true;
				new Thread() {
					public void run() {
						while (mousePressed) {
							String command = Integer.toString(-sliderValue) + " " + "0";
							try {
								sock.sendPacket(command);
							} catch (IOException e) {
								e.printStackTrace();
							}
						}
					}

				}.start();
			}

			public void mouseReleased(MouseEvent e) {
				mousePressed = false;
			}

		});
		panel.add(btnNewButton_1, BorderLayout.SOUTH);

		// Right Arrow listener
		ImageIcon rightArrow = new ImageIcon("right.png");
		Image resizedRightArrow = rightArrow.getImage();
		Image newResizedRightArrow = resizedRightArrow.getScaledInstance(30,
				30, java.awt.Image.SCALE_SMOOTH);
		btnRight = new JButton(new ImageIcon(newResizedRightArrow));
		btnRight.addMouseListener(new MouseAdapter() {
			boolean mousePressed;

			public void mousePressed(MouseEvent e) {
				mousePressed = true;
				new Thread() {
					public void run() {
						while (mousePressed) {
							String command = "0" + " " + Integer.toString(sliderValue);
							try {
								sock.sendPacket(command);
							} catch (IOException e) {
								e.printStackTrace();
							}
						}
					}

				}.start();
			}

			public void mouseReleased(MouseEvent e) {
				mousePressed = false;
			}

		});
		panel.add(btnRight, BorderLayout.EAST);

		
		// Left arrow listener
		ImageIcon leftArrow = new ImageIcon("left.png");
		Image resizedLeftArrow = leftArrow.getImage();
		Image newResizedLeftArrow = resizedLeftArrow.getScaledInstance(30, 30,
				java.awt.Image.SCALE_SMOOTH);
		btnLeft = new JButton(new ImageIcon(newResizedLeftArrow));
		btnLeft.addMouseListener(new MouseAdapter() {
			boolean mousePressed;

			public void mousePressed(MouseEvent e) {
				mousePressed = true;
				new Thread() {
					public void run() {
						while (mousePressed) {
							String command = "0" + " " + Integer.toString(-sliderValue);
							try {
								sock.sendPacket(command);
							} catch (IOException e) {
								e.printStackTrace();
							}
						}
					}

				}.start();
			}

			public void mouseReleased(MouseEvent e) {
				mousePressed = false;
			}

		});
		panel.add(btnLeft, BorderLayout.WEST);

		// Start thread to monitor Ip changes
		Thread thr = new Thread(this);
		thr.start();
		
		
		// Control buttons label
		JLabel lblControlButtons = new JLabel("Control Buttons",
				SwingConstants.CENTER);
		panel.add(lblControlButtons, BorderLayout.CENTER);

		
		// Panel 1 with Video Stream
		frame.getContentPane().add(panel_1, BorderLayout.CENTER);
		panel_1.setLayout(new BorderLayout(0, 0));
		panel_1.add(videolabl);

		JPanel panel_2 = new JPanel();
		panel_1.add(panel_2, BorderLayout.NORTH);
		panel_2.setLayout(new BorderLayout(0, 0));

		
		// Arrow to rotate screen
		ImageIcon arrowLeft = new ImageIcon("arrow2.png");
		Image resizedIcon = arrowLeft.getImage();
		Image newimg = resizedIcon.getScaledInstance(30, 20,
				java.awt.Image.SCALE_SMOOTH);
		JButton btnNewButton_3 = new JButton(new ImageIcon(newimg));

		btnNewButton_3.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				((JVideo) videolabl).rotateRight();

			}
		});

		
		// Launch radar button 
		JButton radarBTN = new JButton("Launch radar");
		radarBTN.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				System.out.println(frame.getLocation());
				RadarMainClass radar = new RadarMainClass();
				radar.run(frame.getLocation());

			}
		});

		panel_2.add(btnNewButton_3, BorderLayout.EAST);
		panel_2.add(radarBTN, BorderLayout.CENTER);

		// Rotate arrow 
		arrowLeft = new ImageIcon("arrow3.png");
		resizedIcon = arrowLeft.getImage();
		newimg = resizedIcon.getScaledInstance(30, 20,
				java.awt.Image.SCALE_SMOOTH);
		JButton btnNewButton_4 = new JButton(new ImageIcon(newimg));
		btnNewButton_4.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				((JVideo) videolabl).rotateLeft();
			}
		});
		panel_2.add(btnNewButton_4, BorderLayout.WEST);
		
		//Java swing slider to control vehicle speed
		final JSlider slider = new JSlider();
		slider.setOrientation(SwingConstants.VERTICAL);
		panel_1.add(slider, BorderLayout.EAST);
		slider.addChangeListener(new ChangeListener() {
		
			@Override
			public void stateChanged(ChangeEvent arg0) {
				sliderValue = slider.getValue();
				System.out.println(sliderValue);
			}
		});

	}

	@Override
	public void run() {
		
		while(true){
			try {
				if (netPref.flag){
					sock =  netPref.returnSocket();
					System.out.println(netPref.getIP());
					((JVideo)videolabl).changeIP(netPref.getIP());
					// Thread to send stop commands
					if(stoppingThread != null){
						stoppingThread.join();
					}
					ZerosTh zth = new ZerosTh(sock, btnNewButton, btnNewButton_1, btnLeft,
							btnRight);
					Thread stoppingThread = new Thread(zth);
					stoppingThread.start();
					netPref.flag = false;
				}
			} catch (SocketException e) {
				e.printStackTrace();
			} catch (UnknownHostException e) {
				e.printStackTrace();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
		}
		
	}
}
