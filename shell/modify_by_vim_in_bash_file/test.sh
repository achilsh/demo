#! /bin/bash 
data_file="data.txt"

#now we modify data file by vim in bash shell file
#  first check vim wheth install 
#  add # on line head on third line
#  789 replace to 10000 in forth line
# :n,ms/ / / 从第n 到第 m层 字符串替换

vim  ${data_file} << VIM  > /dev/null 2>&1
:3,3s/^/#/
:4,4s/789/10000/
:wq
VIM

# :s/ / / 模式是替换当前行的第一个字符串
# :s/ / /g 模式是替换当前行的所有字符串

# :%s/ / / 模式是替换每一行的第一个字符串, :g/ / /
# :%s/ / /g 模式是替换每一行的所有字符串, :g/ / /g


#or patten-match work
#   %s/ / /
#   %sOther  Other Other, because of / is included in contain,but / is default delimiter
vim ${data_file} << VIM > /dev/null 2>&1
:%s/ff/gg/
:%s:/dev/info:xxxxx:
:wq
VIM

# 当然也可以用 sed -i 's/ / /' file 来实现对文件中字符串的替换
# or sed -i '/pattern/s/ / /' file
