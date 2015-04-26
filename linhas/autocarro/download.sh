for i in 1 18 22 200 201 202 203 204 205 206 207 208 209 300 301 302 303 304 305 400 401 402 500 501 502 503 504 505 506 507 508 600 601 602 603 604 700 701 702 703 704 705 706 707 800 801 802 803 804 805 806 900 901 902 903 904 905 906 907 1M 3M 4M 5M 7M 8M 9M 10M 11M 12M 13M
do 
for j in 0 1
do
	if [ "$#" -ne 1 ]; then
    wget -O linha${i}sentido$j.dat "http://www.stcp.pt/pt/itinerarium/callservice.php?action=linedraw&lcode=$i&ldir=$((j++))"
else
	wget -P $1 -O linha${i}sentido$j.dat "http://www.stcp.pt/pt/itinerarium/callservice.php?action=linedraw&lcode=$i&ldir=$((j++))"
	fi
	
done
let "i++"
done