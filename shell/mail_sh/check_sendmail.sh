#! /bin/bash 
BinName=mediaTransferServer
str_sub_pre="[Srv mointor Alarm]"
file_msg="./mts_linux_log.txt"
dst_mail_addr="45152493@qq.com"

function  GetEnv
{
    env_str=""
    env_ip=$(hostname -I) 
    if [ $env_ip = "192.168.0.109"  ]
    then
        env_str="(Develop env)"
    elif [ $env_ip = "192.168.199.250" ]
    then 
        env_str="(Test_1 env)"
    else 
        env_str="(unknown env)"
    fi 
    echo $env_str
}

function GetProcessCmd
{
    local tpid=$(ps -ef|grep ${BinName}|grep -v  grep|grep -v kill|awk '{print $2}')
    echo ${tpid}
}

function GetProcessMsg
{
    cur_tm_str=$(date '+%Y-%m-%d %H:%M:%S')
    log_file="/data/logs/mediaTransfer.log"
    log_last2_item=$(tail -n 2 ${log_file})
    log_sys_last2_item=$(dmesg -T | tail -n 2)
    ip_addr_local=$(hostname -I) 

    str_mesg="Date: $cur_tm_str"
    echo $str_mesg >  ${file_msg}
    echo "" >> ${file_msg}
   
    str_mesg="MtsLogLast2Line:  $log_last2_item"
    echo $str_mesg >>  ${file_msg}
    echo "" >> ${file_msg}
    
    str_mesg="LinuxSysLog:  $log_sys_last2_item"
    echo $str_mesg >>  ${file_msg}
    echo "" >> ${file_msg}

    str_mesg="LocalIp: $ip_addr_local"
    echo $str_mesg >>  ${file_msg}
}


function SendMail
{
    local cmd_send_mail=sendemail
    local mail_domain_name=smtp.126.com
    local src_mail_addr=hwshtongxin@126.com
    str_env=$(GetEnv)
    sub_msg=${str_sub_pre}${str_env}
    local str_subject_mail="${sub_msg}:  \"$BinName\"  not run"
    local str_msg_mail=$(GetProcessMsg)
    
    local src_mail_name="hwshtongxin"
    local src_mail_pwd="hwshtongxin123"
    send_cmd_msg="${cmd_send_mail} -s ${mail_domain_name} -f ${src_mail_addr} -t ${dst_mail_addr}"
    send_cmd_msg="${send_cmd_msg} -u ${str_subject_mail} -m  -o message-file=${file_msg}  -xu ${src_mail_name} -xp ${src_mail_pwd} "
    ${send_cmd_msg}
    echo ${send_cmd_msg}
}

sleep_check_tm=1
sleep_send_mail_tm=60
function check_process_sendmail
{
    while [ 1 ]
    do
        local tpid=$(GetProcessCmd)
        if [ -z "$tpid"  ]
        then
            echo "$BinName not running, should send mail alarm" >> "./send_mail.log"
            ret_send_msg=$(SendMail)
            echo "${ret_send_msg}"
            sleep ${sleep_send_mail_tm}
        else
            echo "$tpid is runnging..." >> /dev/null
            sleep ${sleep_check_tm} 
        fi
    done
}

###run check sh
check_process_sendmail
