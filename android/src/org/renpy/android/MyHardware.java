package org.renpy.android;
import android.content.*;
import android.net.*;
import java.io.*;
import org.tukaani.xz.*;

public class MyHardware {
	public static Object open_intent(String type, String url) {
		Intent myIntent = new Intent(type, Uri.parse(url));

		Hardware.context.startActivity(myIntent);
		return null;
	}
	
	public static byte[] encode_or_decode_xz(byte[] src, boolean decode) {
		try {
			LZMA2Options options = new LZMA2Options();
			options.setDictSize(1024 * 1024); // 1MB
			ByteArrayOutputStream outbytes = new ByteArrayOutputStream();
			ByteArrayInputStream inbytes = new ByteArrayInputStream(src);
			if(decode) {
				XZInputStream inp = new XZInputStream(inbytes);
				byte[] buff = new byte[8096];
				int size;
				while ((size = inp.read(buff)) != -1)
				    outbytes.write(buff, 0, size);
			} else {
				XZOutputStream out = new XZOutputStream(outbytes, options);
				byte[] buf = new byte[8192];
				int size;
				while ((size = inbytes.read(buf)) != -1)
				    out.write(buf, 0, size);
				out.close();
			}
			return outbytes.toByteArray();
		} catch(IOException ex) {
			ex.printStackTrace();
			return null;
		}
	}
}