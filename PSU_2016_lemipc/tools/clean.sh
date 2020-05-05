for x in $(ipcs | grep -v "0x00000000" | cut -d ' ' -f2); do
	if echo $x | egrep -q '^[0-9]+$'; then
	    ipcrm -s $x &> /dev/null
    	ipcrm -m $x &> /dev/null
    	ipcrm -q $x &> /dev/null
    fi
done