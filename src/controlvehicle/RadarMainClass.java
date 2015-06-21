package controlvehicle;

 

import java.awt.Point;

import javax.swing.SwingUtilities;

public class RadarMainClass {

		private Point point;
		
	public void run(Point p){
		point = p;
		mapMain();
		
	}
	 
	private static Socket socket;
	
	/**
	 * Launch the application.
	 */
	public void mapMain() {

		 
		socket = new Socket();

		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				try {
					Thread t2 = new Thread(socket);
					t2.start();

					@SuppressWarnings("unused")
					GUIclass GUIobj = new GUIclass(socket,point);

				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

}
