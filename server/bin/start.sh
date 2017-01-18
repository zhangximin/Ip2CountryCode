#!/bin/sh

cd /usr/local/Ip2C
nohup ./Ip2CService 8033 >/dev/null 2>&1 &
echo $! > ip2c.pid

echo ""
echo "IP2Country Service Started."
echo ""


