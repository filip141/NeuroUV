package controlvehicle;

import java.net.*;

public class Socket implements Runnable {

	private String sentence;
	public boolean flag = true;
	
	public void Socket(){
		flag =true;
	}
	
	public void stopStream() {
		
		flag = false;
		System.out.println("Receiving UDP stopped.");
	}

	public void startStream() {
		flag = true;
		System.out.println("Receiving UDP started.");
		try {
			runStream();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public String getData() {
		return sentence;
	}

	public void runStream() throws Exception {
		

		@SuppressWarnings("resource")
		DatagramSocket serverSocket = new DatagramSocket(7000);
		byte[] receiveData = new byte[1024];

		while (true) {
			DatagramPacket receivePacket = new DatagramPacket(receiveData,
					receiveData.length);
			serverSocket.receive(receivePacket);
			sentence = new String(receivePacket.getData());
			if(!flag){
				serverSocket.close();
				break;
			}

		}
	}

	@Override
	public void run() {
		try {
			runStream();
		} catch (Exception e) {
			System.out.println("Can not connect to server.");
		}
	}
}