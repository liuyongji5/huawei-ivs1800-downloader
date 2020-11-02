#!/bin/bash
export LD_LIBRARY_PATH=./../../libs:./../../libs/json_debian:./../../libs/ffmpeg:${LD_LIBRARY_PATH}

echo "$(date "+%Y-%m-%d %H:%M:%S") start downloading"
default_timeout=240s
host=$2
username=$4
password=$6
code=${8}
start=${10}
end=${12}
file_path=${14}

echo $host $username $password $code $start $end $file_path

#启动进程
./MPClient $host $username $password $code $start $end $file_path
result=$?
success=0

echo $?
if [[ $result == $success ]]
then
	chmod 644 $file_path*
    echo "downLoader success!"
    exit 0
else
    echo "downloader fail!"
    exit -1
fi
