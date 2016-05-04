/*--Advanced Socket Programming--*/

import java.net.UnknownHostException;
import java.net.InetAddress;

public class ipaddress
{
	public static void main(String args[]) throws UnknownHostException
	{
		InetAddress alamat = InetAddress.getLocalHost();
		String alamatIP = alamat.getHostAddress();
		
		System.out.println("IP Address of localhost from Java Program: " + alamatIP);
		
		/*--Hostname--*/
		String hostname = alamat.getHostName();
		System.out.println("Name of hostname: " + hostname);
	}
}
