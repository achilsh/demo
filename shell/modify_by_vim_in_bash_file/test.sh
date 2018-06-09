#! /bin/bash 
data_file="data.txt"

#now we modify data file by vim in bash shell file
#first check vim wheth install 
#add # on line head on third line
#789 replace to 10000 in forth line
vim  ${data_file} << VIM  > /dev/null 2>&1
:3,3s/^/#/
:4,4s/789/10000/
:wq
VIM

#or patten-match work
# %s/ / /
# %sOther  Other Other, because of / is included in contain,but / is default delimiter
vim ${data_file} << VIM > /dev/null 2>&1
:%s/ff/gg/
:%s:/dev/info:xxxxx:
:wq
VIM
