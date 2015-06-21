package controlvehicle;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

@SuppressWarnings("serial")
public class View extends JLabel {

	private GUIclass main;
	private JFileChooser chooser = new JFileChooser();
	private int mapH = 100;
	private int mapW = 100;
	private int[][] map;
	private int rectW = 5;
	private int rectH = 4;
	// private Dimension panelC;
	private Dimension window;

	public View(GUIclass m) {
		main = m;
		// panelC = main.getPanelCSize();
		window = main.getFrameSize();

		map = new int[mapW][mapH];
		preparingMap();

	}

	public void clear(){
		preparingMap();
	}
	
	public void save(){
		FileNameExtensionFilter filter = new FileNameExtensionFilter(
				".txt files", "txt");
		chooser.setFileFilter(filter);
		int returnVal = chooser.showSaveDialog(null);
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			try {

				PrintWriter zapis = new PrintWriter(new File(chooser
						.getSelectedFile().getAbsolutePath()));
				for(int b=0; b<100; b++){

				for(int a=0;a<100;a++){
						zapis.print(Integer.toString(map[a][b]));						
					}
				zapis.println("");
				
				}
				zapis.close();
			} catch (FileNotFoundException a) {
				System.out.println("nie dziala");
				JOptionPane.showMessageDialog(null, "can not save");
			}

		}
	}
	
	/**
	 * prepare map, setting empty zeros, and frame ones
	 */
	private void preparingMap() {

		// puste pole
		for (int a = 0; a < mapW; a++) {
			for (int b = 0; b < mapH; b++) {
				map[a][b] = 0;
			}
		}

		// robot
		for (int a = 47; a < 53; a++) {
			for (int b = 46; b < 54; b++) {
				map[a][b] = -99;
			}
		}
		// kola robota
		map[46][47] = -98;
		map[46][48] = -98;
	
		map[46][51] = -98;
		map[46][52] = -98;
		
		map[53][47] = -98;
		map[53][48] = -98;
		
		map[53][51] = -98;
		map[53][52] = -98;
	

	}

	public void setBarrier(int sonar, int val) {
	try{
		if (sonar == 1) {
			map[42][46 - val] += 1;
			map[43][46 - val] += 1;
			map[45][46 - val] += 1;
		}

		if (sonar == 2) {
			map[49][46 - val] += 1;
			map[50][46 - val] += 1;
			map[51][46 - val] += 1;
		}

		if (sonar == 3) {
			map[54][46 - val] += 1;
			map[55][46 - val] += 1;
			map[56][46 - val] += 1;
		}

		if (sonar == 4) {
			for (int a = 46; a < 54; a++) {
				map[a][54 + val] += 2;
			}
		}

		repaint();

		for (int a = 0; a < mapW; a++) {
			for (int b = 0; b < mapH; b++) {
				if (map[a][b] > 1000)
					map[a][b] = -10;

			}
		}
	}
	catch(ArrayIndexOutOfBoundsException e){
		System.out.println("Map out of bound");
	}
	}

	/**
	 * update current size of PanelC to set right dimension of table
	 */
	private void updateSize() {
		window = main.getFrameSize();

		rectW = (int) ((window.getWidth() - 156) / 100);
		rectH = (int) ((window.getHeight() - 94) / 100);
	}

	/**
	 * paint whole map
	 */
	@Override
	public void paint(Graphics g) {

		updateSize();

		for (int a = 0; a < 100; a++) {
			for (int b = 0; b < 100; b++) {

				if (map[a][b] > 0) {
					g.drawRect(rectW * a, rectH * b, rectW, rectH);
					g.setColor(Color.GREEN);
					g.fillRect(rectW * a, rectH * b, rectW, rectH);

				} else if (map[a][b] == -99) {
					g.drawRect(rectW * a, rectH * b, rectW, rectH);
					g.setColor(Color.BLUE);
					g.fillRect(rectW * a, rectH * b, rectW, rectH);
				} else if (map[a][b] == -10) {
					g.drawRect(rectW * a, rectH * b, rectW, rectH);
					g.setColor(Color.PINK);
					g.fillRect(rectW * a, rectH * b, rectW, rectH);

				}
				else if (map[a][b] == -98) {
					g.drawRect(rectW * a, rectH * b, rectW, rectH);
					g.setColor(Color.BLACK);
					g.fillRect(rectW * a, rectH * b, rectW, rectH);

				}
			}
		}

		Toolkit.getDefaultToolkit().sync();

	}

	/**
	 * size of frame
	 */
	@Override
	public Dimension getPreferredSize() {
		return new Dimension(500, 400);
	}

}