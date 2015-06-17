package com.example.joystickviewdemoactivity;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import android.graphics.Point;

public class Client implements Runnable {
	String ipAddres;
	int server_port;
	Point xy;

	public Client() {
		ipAddres = "90.156.88.134";
		server_port = 9035;
		run();
	}

	public Client(String ipAddres, int server_port, Point xy) {
//		this.ipAddres = "192.168.43.186";
//		this.ipAddres = "90.156.88.134";
//		this.server_port = 9035;
		
		this.ipAddres = ipAddres;
		this.server_port = server_port;
		this.xy = xy;
		run();
	}

	public void run() {

		try {
			final DatagramSocket socket = new DatagramSocket(this.server_port);

			byte[] buf = new byte[256];
			if (xy.x > 100){xy.x = 100;}
			if (xy.y > 100){xy.y = 100;}
			if (xy.x < -100){xy.x = -100;}
			if (xy.y < -100){xy.y = -100;}

			String s = xy.x + " " + xy.y;
			buf = s.getBytes();
			// InetAddress address = InetAddress.getByName ("192.168.43.181");
			InetAddress address = InetAddress.getByName(ipAddres);

			final DatagramPacket packet = new DatagramPacket(buf, buf.length,
					address, server_port);

			new Thread() {
				public void run() {
					try {
						socket.send(packet);
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					socket.close();
				}
			}.start();
		} catch (SocketException e1) {
		} catch (UnknownHostException e2) {
		}
	};
}
