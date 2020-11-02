# huawei-ivs1800-downloader

## 打包

### 打包生成 MPClient 文件
```bash
$ cd sample/source
$ g++ -c -std=c++11 MPClient.cpp -g -I../../include -DMPSDK_LINUX
$ g++ -std=c++11 -L../../libs -L../../libs/json_debian -lsecurec -lcurl -livs_security -ltinyxml2 -lssh2 -lcrypto -lssl -lACE -livs_base -lpcre -lhwmp -lBase -lLog -lKMC -lSDP -livs_compression -lIVS_Player -lIVS_NetSource -lRtsp_client -lmp4 -L../../libs/ffmpeg -lavutil -lavcodec -lavformat -lswresample -lBladeMP3EncDLL -ljsoncpp -o MPClient MPClient.o
```
构建完成后，将生成的sample/source目录下的MPClient 拷贝到sample/client

## 运行
```bash
./IVS1800-downloader.sh --host https://10.5.15.52:18531 --username suzhoudaxue --password admin@123 --code 06902080296401160101 --start 20201102010000 --end 20201102014000 --savepath /var/lib/hikvision-nvr-downloader/storage_device_06902080296401160101/20201102/010000-014000/video
```
