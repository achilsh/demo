#! /bin/bash 
# 统计tcp连接中各个状态及其数目
# 可以采用两种方式来实现, 1: netstat; 2: ss
# 该方法可对udp的协议进行统计,包括对udp established的记录数统计

echo -e "方式1:"
#netstat -ant |awk '{if ($1 ~ /^tcp/) { ++stat[$6] }} END{for (type in stat) {printf("%-5d %s\n", stat[type], type)}}'|sort -nr
x=`netstat -ant |awk '{if ($1 ~ /^tcp/) { ++stat[$6] }} END{for (type in stat) {printf("%-5d %s\n", stat[type], type)}}'|sort -nr`
IFS_OLD=$IFS
IFS='$\n'
echo $x
IFS=$IFS_OLD

echo -e "方式2:"
#方式2:
x=`ss -ant|grep -Ev "^State" |awk '{++stat[$1]} END{ for(type in stat) { printf("%-5d %s\n", stat[type], type) } }' |sort -nr`
IFS_OLD=$IFS
IFS='$\n'
echo $x
IFS=$IFS_OLD


