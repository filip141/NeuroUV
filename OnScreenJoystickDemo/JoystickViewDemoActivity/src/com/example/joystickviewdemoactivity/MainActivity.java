package com.example.joystickviewdemoactivity;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Random;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.joystickviewdemoactivity.JoystickView.OnJoystickMoveListener;

public class MainActivity extends ActionBarActivity {

	public static final String EXTRA_MESSAGE = null;
	// private TextView angleTextView;
	// private TextView powerTextView;
	private TextView xJoy;
	private TextView yJoy;
//	private TextView directionTextView;
	private JoystickView joystick;

	private TextView maxSonarFL;
	private TextView maxSonarF;
	private TextView maxSonarFR;
	private TextView maxSonarBack;

//	private Intent intent;

	private String ipAddres;
	private String server_port;
	private Button refresh;
//	private TextView port;

	private Thread sensorInfo;
	private SensorsInfo sInfo;
//	private boolean thredRun = true;

	ImageView imageMap;
	WebView stream;

	StringBuffer readDAtaFromPage;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		initUi();
		loadAllItem();

		server_port = "9035";
		ipAddres = "90.156.88.134";

//		stream = (WebView) findViewById(R.id.webViewStream);
		stream.loadData(
				"<html><head><meta name='viewport' content='target-densitydpi=device-dpi,initial-scale=1,minimum-scale=1,user-scalable=yes'/></head><body><center><p>\n<img src=\"http://90.156.88.134:8090/?action=stream\" alt=\"Stream\" align=\"middle\"></p></center></body></html>",
				"text/html", null);
		stream.getSettings().setBuiltInZoomControls(true);

		// String streamAddress = "http://90.156.88.134:8080/?action=stream";
		// webView.loadUrl(streamAddress);

		// angleTextView = (TextView) findViewById(R.id.angleTextView);
		// powerTextView = (TextView) findViewById(R.id.powerTextView);

//		maxSonarFL = (TextView) findViewById(R.id.maxSonarFL);
//		maxSonarF = (TextView) findViewById(R.id.maxSonarF);
//		maxSonarFR = (TextView) findViewById(R.id.maxSonarFR);
//		maxSonarBack = (TextView) findViewById(R.id.maxSonarBack);

//		xJoy = (TextView) findViewById(R.id.xJoy);
//		yJoy = (TextView) findViewById(R.id.yJoy);
		xJoy.setText("x= 0");
		yJoy.setText("y= 0");

		// directionTextView = (TextView) findViewById(R.id.directionTextView);
		// Referencing also other views
//		joystick = (JoystickView) findViewById(R.id.joystickView);
//
//		imageMap = (ImageView) findViewById(R.id.imageView1);
//		stream = (WebView) findViewById(R.id.webViewStream);

		sInfo = new SensorsInfo(new Handler());

		sensorInfo = new Thread(sInfo);
		sensorInfo.start();

//		refresh = (Button) findViewById(R.id.button1);

		refresh.setOnTouchListener(new View.OnTouchListener() {

			@Override
			public boolean onTouch(View v, MotionEvent event) {
				stream.reload();
				return false;
			}
		});

		joystick.setOnJoystickMoveListener(new OnJoystickMoveListener() {

			@Override
			public void onValueChanged(int angle, int power, int direction) {
				// angleTextView.setText("x= " + String.valueOf(angle));
				// powerTextView.setText("y= " + String.valueOf(power));
				yJoy.setText("y= " + String.valueOf(angle));
				xJoy.setText("x= " + String.valueOf(power));

				Thread t;

				switch (direction) {
				default:
					// directionTextView.setText(R.string.center_lab);

					t = new Thread(new Client(ipAddres, Integer
							.parseInt(server_port), new Point(angle, power)));
					t.start();
				}
			}
		}, JoystickView.DEFAULT_LOOP_INTERVAL);
	}

	private void initUi() {
		switch (getResources().getConfiguration().orientation) {
		case android.content.res.Configuration.ORIENTATION_LANDSCAPE:
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
			setContentView(R.layout.activity_main_land);
			break;
		case android.content.res.Configuration.ORIENTATION_PORTRAIT:
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
			setContentView(R.layout.activity_main_port);
			break;
		default:
			setContentView(R.layout.activity_main);
			break;
		}
	}
	
	private void loadAllItem(){
		maxSonarFL = (TextView) findViewById(R.id.maxSonarFL);
		maxSonarF = (TextView) findViewById(R.id.maxSonarF);
		maxSonarFR = (TextView) findViewById(R.id.maxSonarFR);
		maxSonarBack = (TextView) findViewById(R.id.maxSonarBack);
		xJoy = (TextView) findViewById(R.id.xJoy);
		yJoy = (TextView) findViewById(R.id.yJoy);
		
		joystick = (JoystickView) findViewById(R.id.joystickView);

		imageMap = (ImageView) findViewById(R.id.imageView1);
		stream = (WebView) findViewById(R.id.webViewStream);
		
		refresh = (Button) findViewById(R.id.button1);

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.action_settings:
			dialogMenu();
			break;
		case R.id.stream_map:

			// sensorInfo.interrupt();
			// try {
			// sInfo.stopThread();
			// sensorInfo.join();
			//
			// } catch (InterruptedException e) {
			// // TODO Auto-generated catch block
			// e.printStackTrace();
			// }
			// if (sensorInfo.interrupted()) {
			// int cos = 0;
			// }

			if (!imageMap.isShown()) {
				imageMap.setVisibility(View.VISIBLE);
				stream.setVisibility(View.INVISIBLE);
				refresh.setVisibility(View.INVISIBLE);

				Bitmap bmp = Bitmap.createBitmap(100, 100,
						Bitmap.Config.ARGB_8888);
				for (int x = 0; x < bmp.getWidth(); x++) {
					for (int y = 0; y < bmp.getHeight(); y++) {
						Random r = new Random();
						bmp.setPixel(
								x,
								y,
								new Color().argb(255, r.nextInt(255),
										r.nextInt(255), r.nextInt(255)));
					}
				}
				imageMap.setImageBitmap(bmp);
			} else {
				imageMap.setVisibility(View.INVISIBLE);
				stream.setVisibility(View.VISIBLE);
				refresh.setVisibility(View.VISIBLE);

			}
			// intent = new Intent(getApplicationContext(), Addr.class);
			// startActivityForResult(intent, 1);

			break;

		default:
			break;
		}

		return super.onOptionsItemSelected(item);
	}

	@Override
	protected void onActivityResult(int arg0, int arg1, Intent data) {
		if (arg1 == RESULT_OK && arg0 == 1) {
			if (data.hasExtra("ipAddress")) {
				Bundle bundle = data.getExtras();
				this.ipAddres = bundle.get("ipAddress").toString();
				this.server_port = bundle.get("port").toString();

				Toast.makeText(this, this.ipAddres + ":" + this.server_port,
						Toast.LENGTH_SHORT).show();
			}
		}
		super.onActivityResult(arg0, arg1, data);
	}

	void dialogMenu() {
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		LayoutInflater inflater = this.getLayoutInflater();
		View v = inflater.inflate(R.layout.settings_main, null);
		final TextView editIP = (TextView) v.findViewById(R.id.editIpAddress);
		final TextView serwerPort = (TextView) v
				.findViewById(R.id.editPortNumber);

		final Context context = this;

		builder.setView(v).setPositiveButton(R.string.ok,
				new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int id) {
						ipAddres = editIP.getText().toString();
						server_port = serwerPort.getText().toString();

						Toast.makeText(context, ipAddres + ":" + server_port,
								Toast.LENGTH_SHORT).show();
					}
				});
		// .setNegativeButton(R.string.cancel,
		// new DialogInterface.OnClickListener() {
		// public void onClick(DialogInterface dialog, int id) {
		//
		// }
		// });
		// Create the AlertDialog object and return it
		AlertDialog alertD = builder.create();
		alertD.show();
	}

	class SensorsInfo implements Runnable {

		private Handler handler;
		private boolean threadRun;
		final String text2[] = new String[5];


		public SensorsInfo(Handler h) {
			handler = h;
			threadRun = true;
		}

		public void stopThread() {
			threadRun = false;
		}

		@Override
		public void run() {

			
//			String server_port = "9035";
//			String ipAddres = "192.168.1.34";
//
//			DatagramSocket socketSend = null;
//			DatagramSocket socketReceive = null;

			while (threadRun) {

//				try {
//					socketSend = new DatagramSocket(
//							Integer.parseInt(server_port));
//				} catch (SocketException e3) {
//					// TODO Auto-generated catch block
//					e3.printStackTrace();
//				}
//				InetAddress address = null;
//
//				try {
//					address = InetAddress.getByName(ipAddres);
//				} catch (UnknownHostException e2) {
//					// TODO Auto-generated catch block
//					e2.printStackTrace();
//				}
//
//				byte[] buf = new byte[256];
//				String s = "t";
//				buf = s.getBytes();
//				DatagramPacket packet = new DatagramPacket(buf, buf.length,
//						address, Integer.parseInt(server_port));
//				try {
//					socketSend.send(packet);
//				} catch (IOException e1) {
//					// TODO Auto-generated catch block
//					e1.printStackTrace();
//				}
//				socketSend.close();
//
//				byte[] lMsg = new byte[4096];
//				DatagramPacket dp = new DatagramPacket(lMsg, lMsg.length);

				StringBuffer total2 = new StringBuffer();

				try {

					BufferedReader r = new BufferedReader(
							new InputStreamReader(
									(InputStream) new URL(
											"http://90.156.88.134/sonar.dat")
											.getContent()));
//					StringBuilder total = new StringBuilder();
					int idx=0;
					String line;
					while ((line = r.readLine()) != null) {
						if(!line.isEmpty()){
						text2[idx++] = line;
						total2.append(line);}
					}
				} catch (Exception e) {
				}
				
				try {
					Thread.sleep(10);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}

				
//					socketReceive = new DatagramSocket(
//							Integer.parseInt(server_port));
//
//					// while (Server_aktiv) {
//					socketReceive.receive(dp);
//					String recive = new String(lMsg, 0, dp.getLength());
//					final String[] text = recive.split(" ");
				
					final String text[] = new String[5];
					char[] tempText = new char[5];
int idx = 0;
					String temp = total2.toString();
					for (int i = 0; i<total2.length();++i){
						char c = temp.charAt(i);
						tempText = new char[5];
						if (c == ':'){
							temp.getChars(i+1, i+4, tempText, 0);
							text[idx++] = new String(tempText);
							}else{
							}
					}

					handler.post(new Runnable() {
						@Override
						public void run() {

							maxSonarFL.setText(text2[0]);
							maxSonarF.setText(text2[1]);
							maxSonarFR.setText(text2[2]);
							maxSonarBack.setText(text2[3]);
						}
					});


					// }
	
				
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e4) {
					// TODO Auto-generated catch block
					e4.printStackTrace();
				}

			}

		}

	}

}
