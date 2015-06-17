package com.example.joystickviewdemoactivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.TextView;

public class Addr extends MainActivity {
	Intent intent;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.settings_main);
		intent = getIntent();

		EditText ipAddres = (EditText) findViewById(R.id.editIpAddress);
		ipAddres.addTextChangedListener(new TextWatcher() {

			@Override
			public void onTextChanged(CharSequence s, int start, int before,
					int count) {
				intent.putExtra("ipAddress", s);

				// String result = new String();
				// Bundle bundle = getIntent().getExtras();
				// result = bundle.get("ipAddress").toString();

			}

			@Override
			public void beforeTextChanged(CharSequence s, int start, int count,
					int after) {
				// TODO Auto-generated method stub

			}

			@Override
			public void afterTextChanged(Editable s) {
				intent.putExtra("ipAddress", s);
			}
		});

		TextView port = (TextView) findViewById(R.id.editPortNumber);
		port.addTextChangedListener(new TextWatcher() {

			@Override
			public void onTextChanged(CharSequence s, int start, int before,
					int count) {
				intent.putExtra("port", s);

			}

			@Override
			public void beforeTextChanged(CharSequence s, int start, int count,
					int after) {
				// TODO Auto-generated method stub

			}

			@Override
			public void afterTextChanged(Editable s) {
				intent.putExtra("port", s);

			}
		});
	}

	@Override
	public void finish() {
		if (!intent.hasExtra("ipAddress")) {
			intent.putExtra("ipAddress", "90.156.88.134");
		}
		if (!intent.hasExtra("port")) {
			intent.putExtra("port", "9035");
		}

		setResult(RESULT_OK, intent);
		super.finish();
	}

}
