package controlvehicle;

import javax.swing.SwingUtilities;

public class Controller extends Thread {

	private View mapa;
	private GUIclass main;
	private Socket socket;
	private String[] lines;

	Controller(View k, GUIclass m, Socket s) {
		mapa = k;
		main = m;
		socket = s;
		lines  = new String[5];

	}

	private void updateMap() {
		//jesli sie poruszył zeruj
		if(Integer.parseInt(lines[4])!=1)
			mapa.clear();
			
		
		// algorytm liczenia odleglosci tu winien być
		int dist1 = (int) Math.ceil((Float.parseFloat(lines[0]) / 5));
		int dist2 = (int) Math.ceil((Float.parseFloat(lines[1]) / 5));
		int dist3 = (int) Math.ceil((Float.parseFloat(lines[2]) / 5));
		int dist4 = (int) Math.ceil((Float.parseFloat(lines[3]) / 5));

		mapa.setBarrier(1, dist1);
		mapa.setBarrier(2, dist2);
		mapa.setBarrier(3, dist3);
		mapa.setBarrier(4, dist4);

	}

	@Override
	public void run() {

		while (true) {

			SwingUtilities.invokeLater(new Runnable() {

				@Override
				public void run() {
					try{
					String text = socket.getData();
					lines = text.split("\\s*\\r?\\n\\s*");
					main.setSonarLabel(lines[0], lines[1], lines[2], lines[3]);
					
					updateMap();
					mapa.repaint();
					}
					catch( java.lang.NullPointerException e)
					{
						System.out.println("No connection");
						
						main.setSonarLabel("00.000", "00.000", "00.000", "00.000");
						
					}
					}

			});

			try {
				sleep(10);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}