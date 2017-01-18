package com.up3d.services.ip2country;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		// System.out.println(IpUtils.ipToLong("24.156.192.0"));
		// System.out.println(IpUtils.longToIp(412925952+16384));
		long begintime = System.nanoTime();
		pSocket p = new pSocket();
		p.open();
		for (int i = 0; i < 1000; i++) {
//			System.out.println("www.up3d.com:" + p.getCountry("52.31.255.124"));
//			System.out.println("www.163.com:" + p.getCountry("180.97.180.16"));
//			System.out.println("www.uk.com:" + p.getCountry("212.18.250.171"));
//			System.out.println("www.sina.com:" + p.getCountry("218.30.108.185"));
//			System.out.println("www.sohu.com:" + p.getCountry("220.181.90.13"));
//			System.out.println("www.whitehouse.gov:" + p.getCountry("184.27.16.110"));
			p.getCountry("52.31.255.124");
			p.getCountry("180.97.180.16");
			p.getCountry("212.18.250.171");
			p.getCountry("218.30.108.185");
			p.getCountry("220.181.90.13");
			p.getCountry("184.27.16.110");

		}
		p.close();
		long endtime = System.nanoTime();
		System.out.println("Total used time(μs):"+ (endtime - begintime)/1000 + " ");
	}

}
