#!/bin/sh

command="!reload"
command1="#close"

cd /usr/local/Ip2C/

./getIpDataBase.sh

HOST_IP="127.0.0.1 8033"

(
	sleep 1
	echo ${command}
	sleep 1
	echo ${command1}
) | telnet ${HOST_IP}

echo ""
echo "Ip2Country Service Reloaded."
echo ""
