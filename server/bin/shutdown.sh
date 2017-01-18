#!/bin/sh

command="!shutdown"

HOST_IP="127.0.0.1 8033"

(
	sleep 1
	echo ${command}
) | telnet ${HOST_IP}

echo ""
echo "Ip2Country Service Stopped."
echo ""
