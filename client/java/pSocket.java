package com.up3d.services.ip2country;

import java.io.BufferedReader;
import java.io.DataInputStream;  
import java.io.DataOutputStream;  
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

import com.sun.xml.internal.ws.Closeable;

public class pSocket {
	public final String IP_ADDR = "192.168.1.33";   
	public final int PORT = 8033;
	public final int BufferSize = 32;

	Socket socket = null;
	BufferedReader input = null;
	DataOutputStream out = null;
	
	public void open() {
		try {
			socket = new Socket(IP_ADDR, PORT);
			socket.setSendBufferSize(32);
			socket.setReceiveBufferSize(32);
			input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			out = new DataOutputStream(socket.getOutputStream());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public String getCountry(String ip){
		String reValue = "NOTFOUND";
		
		try {
			
			out.write(ip.getBytes());
			out.flush();
			String ret = input.readLine();
			if(ret!=null)
				reValue = ret;
		} catch (Exception e) {  
            e.printStackTrace();
		} 
		return reValue;
	}
	
	public void close(){
		try {
			out.close();
			input.close();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (socket != null) {  
                try {  
                    socket.close();  
                } catch (IOException e) {  
                    socket = null;   
                }  
            }
		}
	}
}
