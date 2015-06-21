package controlvehicle;

import java.awt.EventQueue;

import javax.swing.JFrame;

import java.awt.BorderLayout;

import javax.swing.BoxLayout;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JButton;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.SocketException;
import java.net.UnknownHostException;

public class MainPref {

	private JFrame frame;

	private JTextField textField_1;
	private JTextField textField_2;

	private String ipStr = "90.156.88.134";
	private int portInt = 9035;

	private JSocket socket;
	public boolean flag = true;

	public JSocket returnSocket() throws SocketException, UnknownHostException {

		return socket;

	}

	public void setVisible(boolean a) {
		frame.setVisible(a);
	}

	public String getIP() {
		return ipStr;
	}

	public int getPort() {
		return portInt;
	}

	/**
	 * Launch the application.
	 */
	public void mainPref() {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {

					frame.setVisible(false);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 * 
	 * @throws UnknownHostException
	 * @throws SocketException
	 */
	public MainPref() throws SocketException, UnknownHostException {

		socket = new JSocket(portInt, ipStr);

		initialize();

		mainPref();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame("Network preferences");
		frame.setBounds(100, 100, 250, 150);
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		frame.setResizable(false);

		JPanel panelC = new JPanel();
		frame.getContentPane().add(panelC, BorderLayout.WEST);
		panelC.setLayout(new BoxLayout(panelC, BoxLayout.Y_AXIS));

		JPanel panelS = new JPanel();
		frame.getContentPane().add(panelS, BorderLayout.SOUTH);

		JPanel panel = new JPanel();
		panelC.add(panel);

		JLabel lblNewLabel = new JLabel("Server");
		panel.add(lblNewLabel);

		textField_1 = new JTextField();
		panel.add(textField_1);
		textField_1.setColumns(10);

		JPanel panel_1 = new JPanel();
		panelC.add(panel_1);

		JLabel lblNewLabel_1 = new JLabel("     Port");
		panel_1.add(lblNewLabel_1);

		textField_2 = new JTextField();
		panel_1.add(textField_2);

		textField_2.setColumns(10);

		JButton btnNewButton = new JButton("Accept");
		panelS.add(btnNewButton);

		btnNewButton.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				flag = true;
				ipStr = textField_1.getText();
				portInt = Integer.parseInt(textField_2.getText());
				try {
					socket = new JSocket(portInt, ipStr);
				} catch (SocketException e1) {

					e1.printStackTrace();
				} catch (UnknownHostException e1) {

					e1.printStackTrace();
				}
				frame.setVisible(false);

			}
		});

		JButton btnNewButton2 = new JButton("Cancel");
		panelS.add(btnNewButton2);

		btnNewButton2.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {

				frame.setVisible(false);

			}
		});

	}

}
