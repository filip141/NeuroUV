package controlvehicle;

import java.io.*;
import java.net.*;


public class JSocket{
		BufferedReader inFromUser;
		DatagramSocket clientSocket;
		InetAddress IPAddress;
		int port;
		
	    public JSocket(int port, String IP) throws SocketException, UnknownHostException{
	    	inFromUser = new BufferedReader(new InputStreamReader(System.in));
	    	clientSocket = new DatagramSocket();
	    	IPAddress = InetAddress.getByName(IP);
	    	this.port = port;
	    }
	    
	    public void sendPacket(String data) throws IOException{
	    	byte[] sendData = new byte[1024];
	    	String sentence = data;
	    	sendData = sentence.getBytes();
	    	DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
		    clientSocket.send(sendPacket);
	    }
	    public void closeSocket(){
	    	clientSocket.close();
	    }


}
