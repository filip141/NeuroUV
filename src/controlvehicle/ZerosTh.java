package controlvehicle;

import java.io.IOException;

import javax.swing.JButton;

public class ZerosTh implements Runnable {
	JSocket soc;
	JButton up;
	JButton down;
	JButton left;
	JButton right;
	
	public ZerosTh(JSocket soc, JButton up, JButton down, JButton left, JButton right){
		this.up = up;
		this.down = down;
		this.left = left;
		this.right = right;
		this.soc = soc;
	}
	
	@Override
	public void run() {
		while(true){
			if(!up.getModel().isPressed() && !down.getModel().isPressed() && !left.getModel().isPressed() && !right.getModel().isPressed()){
				String command = "0" + " " + "0";
				try {
					soc.sendPacket(command);
					Thread.sleep(25);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		
	}
	
	

}
