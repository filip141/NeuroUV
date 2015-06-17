package com.example.joystickviewdemoactivity;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

public class Dialogsss extends DialogFragment {

	String ipAddres;
	int server_port;

	public Dialogsss() {
		this.ipAddres = "192.168.1.1";
		this.server_port = 9877;
	}

	public Dialogsss(String ipAddres, int server_port) {
		this.ipAddres = ipAddres;
		this.server_port = server_port;
	}

	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
		LayoutInflater inflater = getActivity().getLayoutInflater();
		View v = inflater.inflate(R.layout.settings_main, null);
		final TextView t  = (TextView) v.findViewById(R.id.editIpAddress);
		
		builder.setView(v)
				.setPositiveButton(R.string.ok,
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int id) {
								
								
							}
						});
//				.setNegativeButton(R.string.cancel,
//						new DialogInterface.OnClickListener() {
//							public void onClick(DialogInterface dialog, int id) {
//
//							}
//						});
		// Create the AlertDialog object and return it
		return builder.create();
	}
}
