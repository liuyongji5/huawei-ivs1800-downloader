#!/bin/bash
export LD_LIBRARY_PATH=./../../libs:./../../libs/json_suse:./../../libs/ffmpeg:${LD_LIBRARY_PATH}


#启动进程
./MPClient_suse 
