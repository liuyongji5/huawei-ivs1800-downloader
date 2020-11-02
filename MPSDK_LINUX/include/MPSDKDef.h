/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 定义 DLL 应用程序的导出函数
 * Author: 周卫威
 * Create: 2020/05/05
 * Notes:
 */
#ifndef _MP_SDK_DEF_H_
#define _MP_SDK_DEF_H_

#ifndef MPSDK_LINUX
#include <Windows.h>
#endif 

#ifdef WIN32
#define __SDK_CALL __stdcall
#else
#define __SDK_CALL
#endif

typedef char IVS_INT8;
typedef unsigned char IVS_UINT8;

typedef short IVS_INT16;
typedef unsigned short IVS_UINT16;

typedef int IVS_INT32;
typedef unsigned int IVS_UINT32;

#ifdef _WIN64
typedef unsigned long long IVS_ULONG;
typedef long long IVS_LONG;
#else
typedef unsigned long IVS_ULONG;
typedef long IVS_LONG;
#endif

typedef long long IVS_LONGLONG;

#ifdef _MSC_VER
typedef __int64 IVS_INT64;
typedef unsigned __int64 IVS_UINT64;
#else
typedef long long IVS_INT64;
typedef unsigned long long IVS_UINT64;
#endif

typedef char IVS_CHAR;
typedef unsigned char IVS_UCHAR;

typedef float IVS_FLOAT;

typedef short IVS_SHORT;
typedef unsigned short IVS_USHORT;

// 类型定义
typedef int IVS_BOOL;
typedef void IVS_VOID;

// 通用常量定义
#define MP_BUFFER_SIZE 30 * 1024 * 1024              // 缓冲区大小
#define MP_URL_LEN 2048                             // URL路径，包含'\0'
#define MP_FILE_NAME_LEN 256                        // 文件名最大长度
#define MP_TIME_LEN 20                              // 时间长度
#define MP_IP_LEN 32                                // IP地址长度
#define IVS_TRUE 1                                  // 真
#define IVS_FALSE 0                                 // 假
#define MP_TRUE IVS_TRUE
#define MP_FALSE IVS_FALSE

// 本地录像
#define MP_ENCRY_KEY_LEN 90                         // 密钥最大字节数，不包含'\0'

// 消息定义
enum {
    MP_EVENT_DOWNLOAD_FAILED = 10005,               // 录像下载异常
    MP_EVENT_LOCAL_RECORD_SUCCESS = 10022,          // 本地录像成功事件
    MP_EVENT_LOCAL_RECORD_EGENERIC = 10023,         // 本地录像一般事件
    MP_EVENT_DOWNLOAD_SUCCESS = 10033,              // 录像下载成功事件
    MP_EVENT_PLAYER_WATER_MARK_EXCEPTION = 10037,   // 水印相关事件
    MP_EVENT_PLAYER_CREATE_DECODER_FAILED = 10312,  // 创建解码库失败
    MP_EVENT_PLAYBACK_SUCCESS = 10318,              // 回放播放成功事件
    MP_EVENT_CONNECT_TIMEOUT = 10319,               // 连接超时事件
    MP_EVENT_CONNECT_DISCONNECT = 10320,            // 连接失败事件
    MP_EVENT_RET_SYS = 10321,                       // 通用系统错误
    MP_EVENT_NORMAL_STOP = 10322,                   // 收流结束
    MP_EVENT_ABNORMAL_STOP = 10323,                 // 异常结束
    MP_EVENT_CONNECT_STAUTS_ABNORMAL = 10324        // 连接状态异常
};

// 视频解码类型
typedef enum {
    MP_VIDEO_DEC_UnKnow,
    MP_VIDEO_DEC_H264 = 0x0001,         // H264
    MP_VIDEO_DEC_H265 = 0x0006          // H265
} MP_VIDEO_DEC_TYPE;

// 音频解码类型
typedef enum {
    MP_AUDIO_DEC_UnKnow,
    MP_AUDIO_DEC_PCMA = 0x200,
    MP_AUDIO_DEC_PCMU,
} MP_AUDIO_DEC_TYPE;

// 文件类型;
typedef enum {
    MP_FILE_TYPE_MP4 = 0,               // Mp4文件  目前只支持MP4
} MP_FILE_TYPE;

// 解码缓存状态
typedef enum {
    MP_BUFFER_INCREASE = 0,             // 增长
    MP_BUFFER_DECREASE                  // 减少
} MP_DECBUFFER_STATUS;

// 视频流是否加密
typedef enum {
    MP_UNENC_TYPE = 0,                  // 不加密
    MP_ENC_TYPE                         // 加密
} MP_ENCRYPTION_STATUS;

typedef enum {
    MP_PAY_LOAD_NO_TYPE = -1,
    MP_PAY_LOAD_TYPE_PCMU = 0,          // G711的u率
    MP_PAY_LOAD_TYPE_PCM = 1,           // 暂不支持
    MP_PAY_LOAD_TYPE_G723 = 4,          // 暂不支持
    MP_PAY_LOAD_TYPE_PCMA = 8,          // G711的a率
    MP_PAY_LOAD_TYPE_G722 = 9,          // 暂不支持
    MP_PAY_LOAD_TYPE_G726 = 16,         // 暂不支持
    MP_PAY_LOAD_TYPE_AAC = 17,          // AAC 暂不支持
    MP_PAY_LOAD_TYPE_MJPEG = 26,        // MJPEG 暂不支持
    MP_PAY_LOAD_TYPE_H264 = 99,         // H264
    MP_PAY_LOAD_TYPE_H265 = 108,        // H265
} MP_PAYLOAD_TYPE;

// 本地配置参数，用于全局配置
typedef struct {
    IVS_UINT32 uiDiskWarningValue = 1024;  // 本地录像，磁盘空间小于此值告警，单位M（进行“本地录像通用事件上报”2-本地录像告警）加入新的全局设置接口
    IVS_UINT32 uiStopRecordValue = 512;   // 本地录像，磁盘空间小于此值停止录像，单位M（进行“本地录像通用事件上报”3-本地录像磁盘满停止）加入新的全局设置接口
    IVS_UINT32 uiRecordTime = 0;        // 录像时长，单位秒，整数，300 ~ 43200（12小时）
} MP_LOCAL_CONFIG;

// 播放模式
typedef enum {
    MP_PLAY_FORWARD = 0,                // 正放
    MP_PLAY_BACKWARD                    // 倒放
} MP_PLAY_FB_MODE;

typedef enum {
    MP_REC_EGENERIC,                    // 失败错误
    MP_REC_ESTOP,                       // 结束
    MP_REC_EDISKWARN,                   // 磁盘报警
    MP_REC_EDISKFULL,                   // 磁盘空间不足
    MP_REC_EFILENOTEXIT                 // 文件不存在
} MP_EVENT_CODE;

typedef enum {
    MP_REC_RULE_NAME_NUM_TIME = 1,       // 文件名_序号_时间（开始时间-结束时间，YYYY-MM-DD-hh-mm-ss）
    MP_REC_RULE_NAME_TIME_NUM = 2,       // 文件名_时间（开始时间-结束时间，YYYY-MM-DD-hh-mm-ss）_序号
    MP_REC_RULE_TIME_NAME_NUM = 3,       // 时间（开始时间-结束时间，YYYY-MM-DD-hh-mm-ss）_文件名_序号
    MP_REC_RULE_DEFIND_BY_USER = 4       // 完全按照上层输入的cSavePath来做为文件名(cSavePath中需要包含后缀名)
} MP_RECORD_NAME_RULE;

// 视频相关参数
typedef struct {
    MP_VIDEO_DEC_TYPE codec_id;         // 编码类型，参照MP_VIDEO_DEC_TYPE
    IVS_UINT32 width;                   // 视频宽(预留，暂时不用)
    IVS_UINT32 height;                  // 视频高（预留，暂时不用）
} MP_VIDEO_STREAM_PARAM;

// 音频相关参数
typedef struct {
    MP_AUDIO_DEC_TYPE codec_id;         // 编码类型，参照MP_AUDIO_DEC_TYPE
    IVS_UINT32 sample_rate;             // 采样率， 如：8000
    IVS_UINT32 bits;                    // 采样位数 如：8
    IVS_UINT32 channels;                // 通道数， 如：1
} MP_AUDIO_STREAM_PARAM;

/* 媒体流播放参数 */
typedef struct {
    MP_VIDEO_STREAM_PARAM video;        // 视频相关参数
    MP_AUDIO_STREAM_PARAM audio;        // 音频相关参数

    IVS_UINT32 uiGPUUsed;               // 是否启用GPU解码加速,0-不使用 1-使用
} MP_STREAMPLAY_PARAM;

// 时间片段结构
typedef struct {
    IVS_CHAR cStart[MP_TIME_LEN];       // 格式参考YYYYMMDDThhmmssZ
    IVS_CHAR cEnd[MP_TIME_LEN];         // 格式参考YYYYMMDDThhmmssZ
} MP_TIME_SPAN;

// /*本地文件播放参数*/
typedef struct {
    MP_FILE_TYPE eFileType;             // 文件格式，目前支持MP4类型
    IVS_UINT32 uiGPUUsed;               // 是否启用GPU解码加速,0-不启用 1-启用
    IVS_UINT32 uiBeginTime;             // 播放开始时间(预留，暂时不用设置)
    IVS_UINT32 uiEndTime;               // 播放结束时间(预留，暂时不用设置)
} MP_FILEPLAY_PARAM;

typedef struct {
    IVS_UINT32 uiProtocolType = 1;      // 协议类型，1-UDP 2-TCP，默认为1
    IVS_CHAR cRtspURL[MP_URL_LEN + 1];  // RTSP URL地址
    IVS_UINT32 uiRtspType = 1;          // RTSP类型，1-RTSP 2-RTSP OVER TLS，默认为1
	IVS_INT32   rtspOverNorm;           // 是否使用标准rtsp流程:0-否；1-是
} MP_RTSP_URL;

/* 播放参数 用于实况播放，录像回放 */
typedef struct {
    IVS_BOOL bBlocked;                  // 同步/异步方式，预留暂不使用
    MP_RTSP_URL rtspUrl;                // RTSP URL
    MP_TIME_SPAN stTimeSpan;            // 录像启动、结束时间
    IVS_UINT32 uiMetaDataType;          // 元数据类型 0-不请求元数据 1-请求元数据 预留暂不使用
} MP_NET_PLAY_PARAM;

/*
 * 音视频帧信息
 */
//typedef struct {
//    unsigned int  uiStreamType;		  // 编码格式，参考：IVS_PAYLOAD_TYPE
//    unsigned int  uiTimeStamp;		  // RTP 时间戳
//    unsigned long long  ullTimeTick;  // 绝对时间戳
//    unsigned int  uiWaterMarkValue;	  // 水印数据，0表示无水印数据（视频数据有效）
//    unsigned int  uiGopSequence;	  // GOP序列
//    int           iNotFull;           // 是否完整
//    int           iKey;               // 是否是关键帧	
//    unsigned int  uiFrameType;		  // 帧数据类型，SPS、PPS、IDR、P（视频数据有效）
//    unsigned int  uiWidth;			  // 视屏宽度
//    unsigned int  uiHeight;			  // 视频高度
//} MP_FRAME_INFO;

typedef struct {
    IVS_UCHAR* pY;
    IVS_UCHAR* pU;
    IVS_UCHAR* pV;
    IVS_UINT32 uiPitch;                 // 平面的内存占用长度(也叫做跨度Stride)
    IVS_UINT32 uiWidth;                 // 画面宽
    IVS_UINT32 uiHeight;                // 画面高
    IVS_UINT32 uiPictureFormat;         // 画面格式,参考IVS_PICTURE_FORMAT
    IVS_UINT32 uiTimeStamp;             // RTP时间戳
    IVS_UINT64 ullTimeTick;             // 时标信息，单位毫秒
    IVS_UINT32 uiGopSequence;           // GOP序列
    IVS_CHAR cReserve[32];
    IVS_UINT32 uiFrameType;				// 帧类型(I P), 帧数据类型，SPS、PPS、IDR、P（视频数据有效）
} MP_VIDEO_FRAME;

typedef struct {
    IVS_UCHAR* pFrame;                  // 音频帧首地址
    IVS_UINT32 uiFrameSize;             // 音频帧长度
    IVS_UINT32 uiSampleRate;            // 采样率
    IVS_UINT32 uiChannels;              // 音频声道数
    IVS_UINT32 uiBits;                  // 样位率
    IVS_UINT32 uiTimeStamp;             // RTP时间戳
    IVS_UINT64 ullTimeTick;             // 时标信息，单位毫秒
    IVS_UINT32 uiAudioFormat;           // 音频格式，直接使用payload Type定义的值，参考 IVS_PAYLOAD_TYPE
    IVS_CHAR cReserve[32];              // 预留字段
} MP_AUDIO_FRAME;

// 音视频帧信息
typedef struct {
    MP_PAYLOAD_TYPE eStreamType;        // 编码格式
    IVS_UINT32 ullTimeTick;             // 视频帧时间戳
} MP_FRAME_INFO;

// 媒体流类型
typedef enum {
    MP_MEDIA_STREAM_VIDEO = 0,          // 视频
    MP_MEDIA_STREAM_AUDIO               // 音频
} MP_MEDIA_STREAM;

// 播放视频局部, 参数为百分比
typedef struct {
    IVS_UINT32 mp_left;
    IVS_UINT32 mp_top;
    IVS_UINT32 mp_right;
    IVS_UINT32 mp_bottom;
} MP_LAYOUT_DRAW_PARTIAL;

/* 录像参数,用于本地录像、录像下载功能 */
typedef struct {
    IVS_UINT32 uiRecordFormat; // 录像文件格式，目前支持mp4 1-mp4
    IVS_UINT32 uiSplitterType; // 录像分割方式，1-按时间分割,2-按容量分割
    IVS_UINT32 uiSplitterValue; // 录像分割值，文件分割方式是时间时，填入时间，对应单位为分钟，5-60分钟，同时满足文件大小不超过2048MB的限制，文件分割方式是容量时，填入容量，对应单位为M，1-2048MB

    IVS_UINT32 uiDownloadSpeed; // 录像下载速度：0-不限速（全速），1-1倍速
    MP_TIME_SPAN stTimeSpan; // 录像下载时间段
    
    IVS_UINT32 uiNameRule;                // 录像文件命名规则，参考 MP_RECORD_NAME_RULE
    IVS_CHAR cSavePath[MP_FILE_NAME_LEN]; // 本地录像存放路径，加上文件名长度不超过256字节
    MP_RTSP_URL rtspUrl; // RTSP URL
	IVS_UINT32  uiAudioFormat;   // 录像中音频格式， 0: MP3  1: AAC  默认为0(MP3格式)
    IVS_CHAR cReserve[64]; // 保留字段
} MP_RECORD_PARAM;

// 录像下载信息
typedef struct {
    IVS_UINT32 uiDownloadStatus;            // 下载状态，0-暂停 1-下载
    IVS_UINT32 uiDownloadSpeed;             // 下载速度，单位KB/S
    IVS_UINT64 uiDownloadSize;              // 已下载大小，单位KB
    IVS_UINT32 uiTimeLeft;                  // 剩余下载时间：单位秒
    IVS_UINT32 uiProgress;                  // 当前下载进度：0-100，表示百分比
} MP_DOWNLOAD_INFO;

// 录像成功上报信息
typedef struct {
    IVS_CHAR cFileName[MP_FILE_NAME_LEN];   // 文件名
    IVS_CHAR cFilePath[MP_FILE_NAME_LEN];   // 文件存放路径
    IVS_CHAR cOperationTime[MP_TIME_LEN];   // 操作时间
    MP_TIME_SPAN stRecordTime;              // 录像起始、结束时间
    IVS_UINT32 uiRecordType;                // 录像类型：0-本地录像，1-平台录像下载
    IVS_BOOL bIsEncrypt;                    // 录像是否加密：0-不加密，1-加密
} MP_RECORD_SUCCESS_INFO;

typedef struct {
    unsigned long ulExceptionCode;
    unsigned long long ullTimeStamp;
    unsigned long ulReseved1;
    unsigned long ulReseved2;
} MP_WATER_MARK_DATA;

// 语音对讲参数
typedef struct {
    MP_RTSP_URL rtspUrl;                    // RTSP URL
} MP_VOICE_TALKBACK_PARAM;

typedef struct {
    IVS_UINT32 uiAudioStatus;               // 声音状态
    IVS_UINT32 uiVideoFrameRate;            // 视频当前帧率，单位(fps)，范围1-60
    IVS_UINT32 uiVideoBitrate;              // 视频当前码率
    IVS_UINT32 uiVideoAverageBitrate;       // 视频平均码率
    IVS_UINT32 uiAudioBitRate;              // 音频当前码率，单位(kbps)
    IVS_UINT32 uiAudioAverageBitRate;       // 音频平均码率，单位(kbps)
    IVS_UINT32 uiVideoCodec;                // 视频编码格式：参考 MP_VIDEO_DEC_TYPE
    IVS_UINT32 uiVideoWidth;                // 视频画面宽
    IVS_UINT32 uiVideoHeight;               // 视频画面高
    IVS_FLOAT fLossTolerance;               // 丢包率
    IVS_CHAR cReserve[60];                  // 保留字段
} MP_PLAY_INFO;

typedef struct {
    IVS_ULONG ulHandle;                     // 句柄
    MP_EVENT_CODE code;                     // 错误事件码 参考MP_EVENT_CODE
    MP_RECORD_SUCCESS_INFO recordInfo;      // 录像上报信息
    MP_WATER_MARK_DATA waterMarkInfo;       // 水印信息
} MP_EVENT_INFO;

typedef struct {
    IVS_INT32 iVideoKeyType;                // 0:SIMPLE(扰码流密文头) 1:SIMPLE_HEADER(扰码流明文头) 2:AES256(明文头) 3:AES256_PARTIAL(AES-256部分加密)
    IVS_CHAR szSessionID[64];               // 会话ID
} MP_MEDIA_KEY_INFO;

/* *****************************************************************
function   : MP_BUFFER_STATE_CALLBACK
description: 流媒体播放解码缓存回调
input      : NA
output     : 缓存状态，参考MP_DECBUFFER_STATUS
             pUser  用户数据;
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_BUFFER_STATE_CALLBACK)(int uiBufferStatus, IVS_VOID* pUser);

/* *****************************************************************
function   : MP_ENCRY_STATE_CALLBACK
description: 判断流是否加密回调
input      : NA
output     : ulHandle 播放句柄
             uiEncryption 是否加密，参考MP_ENCRYPTION_STATUS
             pUser  用户数据
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_ENCRY_STATE_CALLBACK)(IVS_ULONG ulHandle, IVS_VOID* pData, IVS_UINT32 uiLen, IVS_VOID* pUser);

/* *****************************************************************
function   : MP_METADATA_CALLBACK
description: 元数据回调函数
input      : NA
output     : uiType     元数据类型
             pData      元数据内容，不同类型对应不同元数据结构
             uiLen      元数据长度
             pUser      用户数据
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_METADATA_CALLBACK)(IVS_UINT32 timestamp, IVS_VOID* pData, IVS_UINT32 uiLen, IVS_VOID* pUser);

typedef void(__SDK_CALL* MP_VIDEODATA_CALLBACK)(IVS_UINT32 timestamp, IVS_VOID* pUser);

/* *****************************************************************
function   : MP_REALPLAY_CALLBACKFRAME
description: 获取解码后码流回调函数（实况）
input      : NA
output     : ulHandle      播放句柄
             uiStreamType  帧类型(音频或视频，参考MP_MEDIA_STREAM)
             pFrameInfo    帧类型参数(视频类型参考MP_VIDEO_FRAME，音频类型参考MP_AUDIO_FRAME)
             pUserData     用户数据
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_REALPLAY_CALLBACKFRAME)(IVS_ULONG ulHandle, IVS_UINT32 uiStreamType, IVS_VOID* pFrameInfo,
    IVS_VOID* pUserData);

/* *****************************************************************
function   : MP_PLAYBACK_CALLBACKFRAME
description: 获取解码后码流回调函数（回放）
input      : NA
output     : ulHandle      播放句柄
             uiStreamType  帧类型(音频或视频，参考MP_MEDIA_STREAM);
             pFrameInfo    帧类型参数(视频类型参考MP_VIDEO_FRAME，音频类型参考MP_AUDIO_FRAME);
             pUserData     用户数据
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_PLAYBACK_CALLBACKFRAME)(IVS_ULONG ulHandle, IVS_UINT32 uiStreamType, IVS_VOID* pFrameInfo,
    IVS_VOID* pUserData);

/* *****************************************************************
 function   : MP_EventCallBack
 description: 事件回调函数(事件通知，异常回调等)
 input      : NA
 output     : iEventType    事件类型
              pEventBuf     事件数据; 参考MP_EVENT_INFO
              uiBufSize     buf长度
              pUserData     用户数据
 return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_EventCallBack)(IVS_INT32 iEventType, IVS_VOID* pEventBuf, IVS_UINT32 uiBufSize,
    IVS_VOID* pUserData);

/* *****************************************************************
 function   : MP_FirstframeCallback
 description: 解码第一帧回调
 input      : NA
 output     : pUserData     用户数据
 return     : void
****************************************************************** */
typedef void(__SDK_CALL * MP_FIRSTFRAME_CALLBACK)(IVS_ULONG ulHandle, IVS_VOID* pUserData);
#endif // _MP_SDK_DEF_H_