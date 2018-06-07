#! /bin/bash 
exec 2>&1 1> test.data.$(date '+%m%d%y')
sed -n '{/shen.*zhen/p; /bei.*jing/p}' ./data.txt  
