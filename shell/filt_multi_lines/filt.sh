#! /bin/bash 
exec 2>&1 1> test.data.$(date '+%m%d%y')
#-n 只打印匹配的结果。
sed -n '{/shen.*zhen/p; /bei.*jing/p}' ./data.txt  
