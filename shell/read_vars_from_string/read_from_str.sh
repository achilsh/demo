#!/bin/bash
params_line="192.168.1.100 90"
read  ipaddr port <<< $(echo ${params_line})
echo $ipaddr, $port
