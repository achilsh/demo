#! /bin/bash 
REPORT_FILE=./capstats.csv
TEMP_FILE=./capstats.html
#
DATE=`date +%m/%d/%Y`
#
MAIL=`which mutt`
MAIL_TO="user@email.com"
#
HOSTNAME=`hostname`
IP=`hostname -I`
##################################################
# Create Report Header
#
echo "<html><body><h3>Reported on $DATE</h3>" > $TEMP_FILE
echo "<h3>Hostname: $HOSTNAME</h3>" >> $TEMP_FILE
echo "<h3>Internal IP: $IP </h3>" >> $TEMP_FILE
echo "<table border=\"1\">" >> $TEMP_FILE
echo "<tr><td>Date</td><td>Time</td><td>Users</td>" >> $TEMP_FILE
echo "<td>Load Average</td><td>Free Memory</td><td>SWAP USED</td>" >> $TEMP_FILE
echo "<td>CPU Average</td><td>Root Disk Free</td></tr>" >> $TEMP_FILE
#
##################################################
# Place Performance Stats in Report
#
cat $REPORT_FILE | gawk -F, '{ 
printf "<tr><td>%s</td><td>%s</td><td>%s</td>", $1, $2, $3; 
printf "<td>%s</td><td>%s</td><td>%s</td>", $4, $5, $6; 
printf "<td>%s</td><td>%s</td>\n</tr>\n", $7, $8;
}' >> $TEMP_FILE
#
echo "</table></body></html>" >> $TEMP_FILE
