/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: ���� DLL Ӧ�ó���ĵ�������
 * Author: ������
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

// ���Ͷ���
typedef int IVS_BOOL;
typedef void IVS_VOID;

// ͨ�ó�������
#define MP_BUFFER_SIZE 30 * 1024 * 1024              // ��������С
#define MP_URL_LEN 2048                             // URL·��������'\0'
#define MP_FILE_NAME_LEN 256                        // �ļ�����󳤶�
#define MP_TIME_LEN 20                              // ʱ�䳤��
#define MP_IP_LEN 32                                // IP��ַ����
#define IVS_TRUE 1                                  // ��
#define IVS_FALSE 0                                 // ��
#define MP_TRUE IVS_TRUE
#define MP_FALSE IVS_FALSE

// ����¼��
#define MP_ENCRY_KEY_LEN 90                         // ��Կ����ֽ�����������'\0'

// ��Ϣ����
enum {
    MP_EVENT_DOWNLOAD_FAILED = 10005,               // ¼�������쳣
    MP_EVENT_LOCAL_RECORD_SUCCESS = 10022,          // ����¼��ɹ��¼�
    MP_EVENT_LOCAL_RECORD_EGENERIC = 10023,         // ����¼��һ���¼�
    MP_EVENT_DOWNLOAD_SUCCESS = 10033,              // ¼�����سɹ��¼�
    MP_EVENT_PLAYER_WATER_MARK_EXCEPTION = 10037,   // ˮӡ����¼�
    MP_EVENT_PLAYER_CREATE_DECODER_FAILED = 10312,  // ���������ʧ��
    MP_EVENT_PLAYBACK_SUCCESS = 10318,              // �طŲ��ųɹ��¼�
    MP_EVENT_CONNECT_TIMEOUT = 10319,               // ���ӳ�ʱ�¼�
    MP_EVENT_CONNECT_DISCONNECT = 10320,            // ����ʧ���¼�
    MP_EVENT_RET_SYS = 10321,                       // ͨ��ϵͳ����
    MP_EVENT_NORMAL_STOP = 10322,                   // ��������
    MP_EVENT_ABNORMAL_STOP = 10323,                 // �쳣����
    MP_EVENT_CONNECT_STAUTS_ABNORMAL = 10324        // ����״̬�쳣
};

// ��Ƶ��������
typedef enum {
    MP_VIDEO_DEC_UnKnow,
    MP_VIDEO_DEC_H264 = 0x0001,         // H264
    MP_VIDEO_DEC_H265 = 0x0006          // H265
} MP_VIDEO_DEC_TYPE;

// ��Ƶ��������
typedef enum {
    MP_AUDIO_DEC_UnKnow,
    MP_AUDIO_DEC_PCMA = 0x200,
    MP_AUDIO_DEC_PCMU,
} MP_AUDIO_DEC_TYPE;

// �ļ�����;
typedef enum {
    MP_FILE_TYPE_MP4 = 0,               // Mp4�ļ�  Ŀǰֻ֧��MP4
} MP_FILE_TYPE;

// ���뻺��״̬
typedef enum {
    MP_BUFFER_INCREASE = 0,             // ����
    MP_BUFFER_DECREASE                  // ����
} MP_DECBUFFER_STATUS;

// ��Ƶ���Ƿ����
typedef enum {
    MP_UNENC_TYPE = 0,                  // ������
    MP_ENC_TYPE                         // ����
} MP_ENCRYPTION_STATUS;

typedef enum {
    MP_PAY_LOAD_NO_TYPE = -1,
    MP_PAY_LOAD_TYPE_PCMU = 0,          // G711��u��
    MP_PAY_LOAD_TYPE_PCM = 1,           // �ݲ�֧��
    MP_PAY_LOAD_TYPE_G723 = 4,          // �ݲ�֧��
    MP_PAY_LOAD_TYPE_PCMA = 8,          // G711��a��
    MP_PAY_LOAD_TYPE_G722 = 9,          // �ݲ�֧��
    MP_PAY_LOAD_TYPE_G726 = 16,         // �ݲ�֧��
    MP_PAY_LOAD_TYPE_AAC = 17,          // AAC �ݲ�֧��
    MP_PAY_LOAD_TYPE_MJPEG = 26,        // MJPEG �ݲ�֧��
    MP_PAY_LOAD_TYPE_H264 = 99,         // H264
    MP_PAY_LOAD_TYPE_H265 = 108,        // H265
} MP_PAYLOAD_TYPE;

// �������ò���������ȫ������
typedef struct {
    IVS_UINT32 uiDiskWarningValue = 1024;  // ����¼�񣬴��̿ռ�С�ڴ�ֵ�澯����λM�����С�����¼��ͨ���¼��ϱ���2-����¼��澯�������µ�ȫ�����ýӿ�
    IVS_UINT32 uiStopRecordValue = 512;   // ����¼�񣬴��̿ռ�С�ڴ�ֵֹͣ¼�񣬵�λM�����С�����¼��ͨ���¼��ϱ���3-����¼�������ֹͣ�������µ�ȫ�����ýӿ�
    IVS_UINT32 uiRecordTime = 0;        // ¼��ʱ������λ�룬������300 ~ 43200��12Сʱ��
} MP_LOCAL_CONFIG;

// ����ģʽ
typedef enum {
    MP_PLAY_FORWARD = 0,                // ����
    MP_PLAY_BACKWARD                    // ����
} MP_PLAY_FB_MODE;

typedef enum {
    MP_REC_EGENERIC,                    // ʧ�ܴ���
    MP_REC_ESTOP,                       // ����
    MP_REC_EDISKWARN,                   // ���̱���
    MP_REC_EDISKFULL,                   // ���̿ռ䲻��
    MP_REC_EFILENOTEXIT                 // �ļ�������
} MP_EVENT_CODE;

typedef enum {
    MP_REC_RULE_NAME_NUM_TIME = 1,       // �ļ���_���_ʱ�䣨��ʼʱ��-����ʱ�䣬YYYY-MM-DD-hh-mm-ss��
    MP_REC_RULE_NAME_TIME_NUM = 2,       // �ļ���_ʱ�䣨��ʼʱ��-����ʱ�䣬YYYY-MM-DD-hh-mm-ss��_���
    MP_REC_RULE_TIME_NAME_NUM = 3,       // ʱ�䣨��ʼʱ��-����ʱ�䣬YYYY-MM-DD-hh-mm-ss��_�ļ���_���
    MP_REC_RULE_DEFIND_BY_USER = 4       // ��ȫ�����ϲ������cSavePath����Ϊ�ļ���(cSavePath����Ҫ������׺��)
} MP_RECORD_NAME_RULE;

// ��Ƶ��ز���
typedef struct {
    MP_VIDEO_DEC_TYPE codec_id;         // �������ͣ�����MP_VIDEO_DEC_TYPE
    IVS_UINT32 width;                   // ��Ƶ��(Ԥ������ʱ����)
    IVS_UINT32 height;                  // ��Ƶ�ߣ�Ԥ������ʱ���ã�
} MP_VIDEO_STREAM_PARAM;

// ��Ƶ��ز���
typedef struct {
    MP_AUDIO_DEC_TYPE codec_id;         // �������ͣ�����MP_AUDIO_DEC_TYPE
    IVS_UINT32 sample_rate;             // �����ʣ� �磺8000
    IVS_UINT32 bits;                    // ����λ�� �磺8
    IVS_UINT32 channels;                // ͨ������ �磺1
} MP_AUDIO_STREAM_PARAM;

/* ý�������Ų��� */
typedef struct {
    MP_VIDEO_STREAM_PARAM video;        // ��Ƶ��ز���
    MP_AUDIO_STREAM_PARAM audio;        // ��Ƶ��ز���

    IVS_UINT32 uiGPUUsed;               // �Ƿ�����GPU�������,0-��ʹ�� 1-ʹ��
} MP_STREAMPLAY_PARAM;

// ʱ��Ƭ�νṹ
typedef struct {
    IVS_CHAR cStart[MP_TIME_LEN];       // ��ʽ�ο�YYYYMMDDThhmmssZ
    IVS_CHAR cEnd[MP_TIME_LEN];         // ��ʽ�ο�YYYYMMDDThhmmssZ
} MP_TIME_SPAN;

// /*�����ļ����Ų���*/
typedef struct {
    MP_FILE_TYPE eFileType;             // �ļ���ʽ��Ŀǰ֧��MP4����
    IVS_UINT32 uiGPUUsed;               // �Ƿ�����GPU�������,0-������ 1-����
    IVS_UINT32 uiBeginTime;             // ���ſ�ʼʱ��(Ԥ������ʱ��������)
    IVS_UINT32 uiEndTime;               // ���Ž���ʱ��(Ԥ������ʱ��������)
} MP_FILEPLAY_PARAM;

typedef struct {
    IVS_UINT32 uiProtocolType = 1;      // Э�����ͣ�1-UDP 2-TCP��Ĭ��Ϊ1
    IVS_CHAR cRtspURL[MP_URL_LEN + 1];  // RTSP URL��ַ
    IVS_UINT32 uiRtspType = 1;          // RTSP���ͣ�1-RTSP 2-RTSP OVER TLS��Ĭ��Ϊ1
	IVS_INT32   rtspOverNorm;           // �Ƿ�ʹ�ñ�׼rtsp����:0-��1-��
} MP_RTSP_URL;

/* ���Ų��� ����ʵ�����ţ�¼��ط� */
typedef struct {
    IVS_BOOL bBlocked;                  // ͬ��/�첽��ʽ��Ԥ���ݲ�ʹ��
    MP_RTSP_URL rtspUrl;                // RTSP URL
    MP_TIME_SPAN stTimeSpan;            // ¼������������ʱ��
    IVS_UINT32 uiMetaDataType;          // Ԫ�������� 0-������Ԫ���� 1-����Ԫ���� Ԥ���ݲ�ʹ��
} MP_NET_PLAY_PARAM;

/*
 * ����Ƶ֡��Ϣ
 */
//typedef struct {
//    unsigned int  uiStreamType;		  // �����ʽ���ο���IVS_PAYLOAD_TYPE
//    unsigned int  uiTimeStamp;		  // RTP ʱ���
//    unsigned long long  ullTimeTick;  // ����ʱ���
//    unsigned int  uiWaterMarkValue;	  // ˮӡ���ݣ�0��ʾ��ˮӡ���ݣ���Ƶ������Ч��
//    unsigned int  uiGopSequence;	  // GOP����
//    int           iNotFull;           // �Ƿ�����
//    int           iKey;               // �Ƿ��ǹؼ�֡	
//    unsigned int  uiFrameType;		  // ֡�������ͣ�SPS��PPS��IDR��P����Ƶ������Ч��
//    unsigned int  uiWidth;			  // �������
//    unsigned int  uiHeight;			  // ��Ƶ�߶�
//} MP_FRAME_INFO;

typedef struct {
    IVS_UCHAR* pY;
    IVS_UCHAR* pU;
    IVS_UCHAR* pV;
    IVS_UINT32 uiPitch;                 // ƽ����ڴ�ռ�ó���(Ҳ�������Stride)
    IVS_UINT32 uiWidth;                 // �����
    IVS_UINT32 uiHeight;                // �����
    IVS_UINT32 uiPictureFormat;         // �����ʽ,�ο�IVS_PICTURE_FORMAT
    IVS_UINT32 uiTimeStamp;             // RTPʱ���
    IVS_UINT64 ullTimeTick;             // ʱ����Ϣ����λ����
    IVS_UINT32 uiGopSequence;           // GOP����
    IVS_CHAR cReserve[32];
    IVS_UINT32 uiFrameType;				// ֡����(I P), ֡�������ͣ�SPS��PPS��IDR��P����Ƶ������Ч��
} MP_VIDEO_FRAME;

typedef struct {
    IVS_UCHAR* pFrame;                  // ��Ƶ֡�׵�ַ
    IVS_UINT32 uiFrameSize;             // ��Ƶ֡����
    IVS_UINT32 uiSampleRate;            // ������
    IVS_UINT32 uiChannels;              // ��Ƶ������
    IVS_UINT32 uiBits;                  // ��λ��
    IVS_UINT32 uiTimeStamp;             // RTPʱ���
    IVS_UINT64 ullTimeTick;             // ʱ����Ϣ����λ����
    IVS_UINT32 uiAudioFormat;           // ��Ƶ��ʽ��ֱ��ʹ��payload Type�����ֵ���ο� IVS_PAYLOAD_TYPE
    IVS_CHAR cReserve[32];              // Ԥ���ֶ�
} MP_AUDIO_FRAME;

// ����Ƶ֡��Ϣ
typedef struct {
    MP_PAYLOAD_TYPE eStreamType;        // �����ʽ
    IVS_UINT32 ullTimeTick;             // ��Ƶ֡ʱ���
} MP_FRAME_INFO;

// ý��������
typedef enum {
    MP_MEDIA_STREAM_VIDEO = 0,          // ��Ƶ
    MP_MEDIA_STREAM_AUDIO               // ��Ƶ
} MP_MEDIA_STREAM;

// ������Ƶ�ֲ�, ����Ϊ�ٷֱ�
typedef struct {
    IVS_UINT32 mp_left;
    IVS_UINT32 mp_top;
    IVS_UINT32 mp_right;
    IVS_UINT32 mp_bottom;
} MP_LAYOUT_DRAW_PARTIAL;

/* ¼�����,���ڱ���¼��¼�����ع��� */
typedef struct {
    IVS_UINT32 uiRecordFormat; // ¼���ļ���ʽ��Ŀǰ֧��mp4 1-mp4
    IVS_UINT32 uiSplitterType; // ¼��ָʽ��1-��ʱ��ָ�,2-�������ָ�
    IVS_UINT32 uiSplitterValue; // ¼��ָ�ֵ���ļ��ָʽ��ʱ��ʱ������ʱ�䣬��Ӧ��λΪ���ӣ�5-60���ӣ�ͬʱ�����ļ���С������2048MB�����ƣ��ļ��ָʽ������ʱ��������������Ӧ��λΪM��1-2048MB

    IVS_UINT32 uiDownloadSpeed; // ¼�������ٶȣ�0-�����٣�ȫ�٣���1-1����
    MP_TIME_SPAN stTimeSpan; // ¼������ʱ���
    
    IVS_UINT32 uiNameRule;                // ¼���ļ��������򣬲ο� MP_RECORD_NAME_RULE
    IVS_CHAR cSavePath[MP_FILE_NAME_LEN]; // ����¼����·���������ļ������Ȳ�����256�ֽ�
    MP_RTSP_URL rtspUrl; // RTSP URL
	IVS_UINT32  uiAudioFormat;   // ¼������Ƶ��ʽ�� 0: MP3  1: AAC  Ĭ��Ϊ0(MP3��ʽ)
    IVS_CHAR cReserve[64]; // �����ֶ�
} MP_RECORD_PARAM;

// ¼��������Ϣ
typedef struct {
    IVS_UINT32 uiDownloadStatus;            // ����״̬��0-��ͣ 1-����
    IVS_UINT32 uiDownloadSpeed;             // �����ٶȣ���λKB/S
    IVS_UINT64 uiDownloadSize;              // �����ش�С����λKB
    IVS_UINT32 uiTimeLeft;                  // ʣ������ʱ�䣺��λ��
    IVS_UINT32 uiProgress;                  // ��ǰ���ؽ��ȣ�0-100����ʾ�ٷֱ�
} MP_DOWNLOAD_INFO;

// ¼��ɹ��ϱ���Ϣ
typedef struct {
    IVS_CHAR cFileName[MP_FILE_NAME_LEN];   // �ļ���
    IVS_CHAR cFilePath[MP_FILE_NAME_LEN];   // �ļ����·��
    IVS_CHAR cOperationTime[MP_TIME_LEN];   // ����ʱ��
    MP_TIME_SPAN stRecordTime;              // ¼����ʼ������ʱ��
    IVS_UINT32 uiRecordType;                // ¼�����ͣ�0-����¼��1-ƽ̨¼������
    IVS_BOOL bIsEncrypt;                    // ¼���Ƿ���ܣ�0-�����ܣ�1-����
} MP_RECORD_SUCCESS_INFO;

typedef struct {
    unsigned long ulExceptionCode;
    unsigned long long ullTimeStamp;
    unsigned long ulReseved1;
    unsigned long ulReseved2;
} MP_WATER_MARK_DATA;

// �����Խ�����
typedef struct {
    MP_RTSP_URL rtspUrl;                    // RTSP URL
} MP_VOICE_TALKBACK_PARAM;

typedef struct {
    IVS_UINT32 uiAudioStatus;               // ����״̬
    IVS_UINT32 uiVideoFrameRate;            // ��Ƶ��ǰ֡�ʣ���λ(fps)����Χ1-60
    IVS_UINT32 uiVideoBitrate;              // ��Ƶ��ǰ����
    IVS_UINT32 uiVideoAverageBitrate;       // ��Ƶƽ������
    IVS_UINT32 uiAudioBitRate;              // ��Ƶ��ǰ���ʣ���λ(kbps)
    IVS_UINT32 uiAudioAverageBitRate;       // ��Ƶƽ�����ʣ���λ(kbps)
    IVS_UINT32 uiVideoCodec;                // ��Ƶ�����ʽ���ο� MP_VIDEO_DEC_TYPE
    IVS_UINT32 uiVideoWidth;                // ��Ƶ�����
    IVS_UINT32 uiVideoHeight;               // ��Ƶ�����
    IVS_FLOAT fLossTolerance;               // ������
    IVS_CHAR cReserve[60];                  // �����ֶ�
} MP_PLAY_INFO;

typedef struct {
    IVS_ULONG ulHandle;                     // ���
    MP_EVENT_CODE code;                     // �����¼��� �ο�MP_EVENT_CODE
    MP_RECORD_SUCCESS_INFO recordInfo;      // ¼���ϱ���Ϣ
    MP_WATER_MARK_DATA waterMarkInfo;       // ˮӡ��Ϣ
} MP_EVENT_INFO;

typedef struct {
    IVS_INT32 iVideoKeyType;                // 0:SIMPLE(����������ͷ) 1:SIMPLE_HEADER(����������ͷ) 2:AES256(����ͷ) 3:AES256_PARTIAL(AES-256���ּ���)
    IVS_CHAR szSessionID[64];               // �ỰID
} MP_MEDIA_KEY_INFO;

/* *****************************************************************
function   : MP_BUFFER_STATE_CALLBACK
description: ��ý�岥�Ž��뻺��ص�
input      : NA
output     : ����״̬���ο�MP_DECBUFFER_STATUS
             pUser  �û�����;
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_BUFFER_STATE_CALLBACK)(int uiBufferStatus, IVS_VOID* pUser);

/* *****************************************************************
function   : MP_ENCRY_STATE_CALLBACK
description: �ж����Ƿ���ܻص�
input      : NA
output     : ulHandle ���ž��
             uiEncryption �Ƿ���ܣ��ο�MP_ENCRYPTION_STATUS
             pUser  �û�����
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_ENCRY_STATE_CALLBACK)(IVS_ULONG ulHandle, IVS_VOID* pData, IVS_UINT32 uiLen, IVS_VOID* pUser);

/* *****************************************************************
function   : MP_METADATA_CALLBACK
description: Ԫ���ݻص�����
input      : NA
output     : uiType     Ԫ��������
             pData      Ԫ�������ݣ���ͬ���Ͷ�Ӧ��ͬԪ���ݽṹ
             uiLen      Ԫ���ݳ���
             pUser      �û�����
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_METADATA_CALLBACK)(IVS_UINT32 timestamp, IVS_VOID* pData, IVS_UINT32 uiLen, IVS_VOID* pUser);

typedef void(__SDK_CALL* MP_VIDEODATA_CALLBACK)(IVS_UINT32 timestamp, IVS_VOID* pUser);

/* *****************************************************************
function   : MP_REALPLAY_CALLBACKFRAME
description: ��ȡ����������ص�������ʵ����
input      : NA
output     : ulHandle      ���ž��
             uiStreamType  ֡����(��Ƶ����Ƶ���ο�MP_MEDIA_STREAM)
             pFrameInfo    ֡���Ͳ���(��Ƶ���Ͳο�MP_VIDEO_FRAME����Ƶ���Ͳο�MP_AUDIO_FRAME)
             pUserData     �û�����
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_REALPLAY_CALLBACKFRAME)(IVS_ULONG ulHandle, IVS_UINT32 uiStreamType, IVS_VOID* pFrameInfo,
    IVS_VOID* pUserData);

/* *****************************************************************
function   : MP_PLAYBACK_CALLBACKFRAME
description: ��ȡ����������ص��������طţ�
input      : NA
output     : ulHandle      ���ž��
             uiStreamType  ֡����(��Ƶ����Ƶ���ο�MP_MEDIA_STREAM);
             pFrameInfo    ֡���Ͳ���(��Ƶ���Ͳο�MP_VIDEO_FRAME����Ƶ���Ͳο�MP_AUDIO_FRAME);
             pUserData     �û�����
return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_PLAYBACK_CALLBACKFRAME)(IVS_ULONG ulHandle, IVS_UINT32 uiStreamType, IVS_VOID* pFrameInfo,
    IVS_VOID* pUserData);

/* *****************************************************************
 function   : MP_EventCallBack
 description: �¼��ص�����(�¼�֪ͨ���쳣�ص���)
 input      : NA
 output     : iEventType    �¼�����
              pEventBuf     �¼�����; �ο�MP_EVENT_INFO
              uiBufSize     buf����
              pUserData     �û�����
 return     : void
****************************************************************** */
typedef void(__SDK_CALL* MP_EventCallBack)(IVS_INT32 iEventType, IVS_VOID* pEventBuf, IVS_UINT32 uiBufSize,
    IVS_VOID* pUserData);

/* *****************************************************************
 function   : MP_FirstframeCallback
 description: �����һ֡�ص�
 input      : NA
 output     : pUserData     �û�����
 return     : void
****************************************************************** */
typedef void(__SDK_CALL * MP_FIRSTFRAME_CALLBACK)(IVS_ULONG ulHandle, IVS_VOID* pUserData);
#endif // _MP_SDK_DEF_H_