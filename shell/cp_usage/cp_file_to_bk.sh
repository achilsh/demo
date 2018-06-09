#!/bin/bash
cur_dir=$(pwd)
echo $cur_dir
cur_file="cp_file_to_bk.sh"
#cp 命令给当前文件做备份
cp ${cur_dir}/${cur_file}{,.bk}
