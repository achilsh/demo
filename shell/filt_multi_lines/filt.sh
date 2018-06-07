#! /bin/bash 
sed -n '{/shen.*zhen/p; /bei.*jing/p}' ./data.txt 
