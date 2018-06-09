#!/bin/bash
data_file=data.txt

#write some one things to file
#write some two things to file
cat >> ${data_file}  << EOF
this is one line
this is second line
EOF
