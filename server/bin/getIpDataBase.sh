#!/bin/sh

cd /usr/local/Ip2C
rm delegated-*

echo "Getting asia and pacific ip address ..."
wget ftp://ftp.apnic.net/pub/apnic/stats/apnic/delegated-apnic-extended-latest

echo "Getting north american ip address ..."
wget ftp://ftp.arin.net/pub/stats/arin/delegated-arin-extended-latest

echo "Getting african ip address ..."
wget ftp://ftp.afrinic.net/pub/stats/afrinic/delegated-afrinic-extended-latest

echo "Getting latin america and some caribbean islands ip address ..."
wget ftp://ftp.lacnic.net/pub/stats/lacnic/delegated-lacnic-extended-latest

echo "Getting europe middle east and parts of central asia ip address ..."
wget ftp://ftp.ripe.net/pub/stats/ripencc/delegated-ripencc-extended-latest

echo "Done."
