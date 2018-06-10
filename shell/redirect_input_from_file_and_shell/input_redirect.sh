#! /bin/bash 

# 输入重定向是为了获取输入源; 从输入源中一行行获取数据,用于对每行数据处理或者行数的统计等
# 
# 1. 一般将stdin输入重定向为: 具体文件( 通过 重定向符号: <  ), 或者 一段数据(通过内联输入重定向符 << )
#

# 从文件中读取每行数据 并处理，将文件重定向为标准输入
while read name age
do 
    echo $name, $age
done <  data.txt

# 从数据段中读取数据，将数据段重定向为标准输入

while read name age
do
    echo $name, $age
done << EOF
tiehe 100
datang 3000
jinqiao  321
xiangshan 234
EOF
