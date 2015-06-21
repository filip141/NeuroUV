package controlvehicle;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.awt.image.BufferedImageOp;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import javax.imageio.ImageIO;
import javax.swing.JLabel;

public class JVideo extends JLabel implements Runnable{
	
	private BufferedImage img;
	private Dimension dimension;
	private String streamIP;
	int rotateLeft;
	int rotateRight;
	
	// Construct Thread
	public JVideo(String ip){
		this.streamIP = ip;
		Thread th = new Thread(this);
		th.start();
	}
	
	// Read mjpg image from server
	public void readImage() throws IOException{		
		URLConnection con = null;
		InputStream in = null;
	    try {
	    		
	    		System.out.println("http://" + streamIP + ":8090/?action=snapshot");
	            URL url = new URL("http://" + streamIP + ":8090/?action=snapshot");
	            con = url.openConnection();
	            con.setConnectTimeout(2200);
	            con.setReadTimeout(2200);
	            in = con.getInputStream();
	    		img = ImageIO.read(in);

	    }catch (IOException e){
	        System.out.println("Error");
	        img = ImageIO.read(new File("maxresdefault.jpg"));
	    }
	}
	
	public void changeIP(String newIP){
		streamIP = newIP;
	}
	
	// Check translation
	private AffineTransform findTranslation(AffineTransform at, BufferedImage bi) {
		   Point2D p2din, p2dout;
		 
		   p2din = new Point2D.Double(0.0, 0.0);
		   p2dout = at.transform(p2din, null);
		   double ytrans = p2dout.getY();
		 
		   p2din = new Point2D.Double(0, bi.getHeight());
		   p2dout = at.transform(p2din, null);
		   double xtrans = p2dout.getX();
		 
		   AffineTransform tat = new AffineTransform();
		   tat.translate(-xtrans, -ytrans);
		 
		   return tat;
	}
	
	//Rotate Video
	private void rotateVideo(int degrees){
		
		AffineTransform ax = new AffineTransform();
		ax.rotate(degrees * Math.PI / 180.0, img.getWidth() / 2.0, img.getHeight() / 2.0);
		
		AffineTransform translationTransform = findTranslation(ax, img);
		 
		ax.preConcatenate(translationTransform);
		
		BufferedImageOp op = new AffineTransformOp(ax, AffineTransformOp.TYPE_BILINEAR);
		img = op.filter(img, null);
	}
	
	// Increment left rotation acumulator
	public void rotateLeft(){
		rotateLeft = ( rotateLeft + 1 )% 4;
	}
	// Increment right rotation acumulator
	public void rotateRight(){
		rotateRight = rotateRight - 1 ;
		if (rotateRight < 0){
			rotateRight = 3;
		}
	}
	
	
    @Override
    public void paintComponent(Graphics g) {
    	super.paintComponent(g);
        Graphics2D g2d = (Graphics2D)g;
        g2d.drawImage(img, 20, 20, this.getWidth()-40, this.getHeight()-40,null);
    }
    

	@Override
	public void run() {
		int i;
		int j;
		while(true){
			try {
				readImage();
			} catch (IOException e) {
				System.out.println("error!");
				e.printStackTrace();
			}
			for(i = 0; i < rotateLeft; i++){
				rotateVideo(90);
			}
			for(j = 0; j < rotateRight; j++){
				rotateVideo(90);
			}
			repaint();
		}
	}
    
    
	
	

}
