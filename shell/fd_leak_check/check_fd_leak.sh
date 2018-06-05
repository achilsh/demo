#! /bin/bash 

NameProc="test"
function GetOpenFdNums {
    pid=$(ps -ef|grep ${NameProc} |grep -v grep|awk '{print $2}')
    if [  -z "$pid" ]
    then 
        echo "test proce not exist"
        exit 1
    fi

    cmd_str="ls /proc/$pid/fd "
    fd_nums_proc=`${cmd_str} |  wc -l` 
    echo ${fd_nums_proc}
}

cur_fd_nums_pre=0
while [ 1  ]
do
    if read  -t 2 -n1 -p "[Y/y]?"  flag
    then
        echo  
        #echo "\ninput flag: $flag" 
    else
        flag=N
    fi
    echo 
    case $flag in
        Y|y) echo "stop stats"
            break;;
    esac
    echo "input flag: $flag"
    
    cur_fd_nums=$(GetOpenFdNums)
    echo "cur open fs num: $cur_fd_nums"
    fd_nums_diff=$[ $cur_fd_nums - $cur_fd_nums_pre ]
    if [ $cur_fd_nums_pre -ne 0 ] 
    then
        echo "increase opened fd num: $fd_nums_diff"
    fi 

    if [ $fd_nums_diff -gt 0  ]
    then
        echo "used fd increase, fd pre nums: $cur_fd_nums_pre, cur nums: $cur_fd_nums"
    fi
    cur_fd_nums_pre=$cur_fd_nums 
done
