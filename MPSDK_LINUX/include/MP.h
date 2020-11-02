/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 定义 DLL 应用程序的导出函数
 * Author: 周卫威
 * Create: 2020/05/05
 * Notes:
 */

#ifndef MP_H
#define MP_H

#include "MPSDKDef.h"

#ifdef WIN32
#ifdef IVS_SDK_EXPORTS
#define MP_API __declspec(dllexport)
#else
#define MP_API __declspec(dllimport)
#endif
#else
#define MP_API __attribute__((visibility("default")))
#endif

#ifdef WIN32
#define __SDK_CALL __stdcall

#else
#define __SDK_CALL
#endif

#ifndef VOID
#define VOID void
#endif

#ifdef __cplusplus
extern "C" //lint !e10
{
#endif
/* *************************************************************************
函数名称:MP_Init
功能描述:初始化库
输入参数:日志路径
输出参数:NA
返 回 值:成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_Init(IVS_CHAR* pLogPath);

/* ****************************************************************************
函数名称：MP_SetBufferSize
功能描述：设置解码缓冲区大小（默认4*1024*1024）
输入参数：uiBufferSize      缓冲区大小
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_SetBufferSize(IVS_UINT32 uiBufferSize);

/* *************************************************************************
函数名称:MP_UnInit()
功能描述:释放SDK
输入参数:NA
输出参数:NA
返 回 值:成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_UnInit();

/* *************************************************************************
函数名称:MP_GetVersion()
功能描述:获取SDK版本号()
输入参数:NA
输出参数:NA
返 回 值:返回SDK版本号
************************************************************************* */
MP_API IVS_CHAR* __SDK_CALL MP_GetVersion();

/* *************************************************************************
函数名称:MP_SetLocalConfigParam()
功能描述:设置本地配置参数
输入参数:param    要设置的参数
输出参数:NA
返 回 值:成功返回IVS_SUCCEDD
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_SetLocalConfigParam(const MP_LOCAL_CONFIG* param);

/* *************************************************************************
函数名称:MP_GetLocalConfigParam()
功能描述:获取本地配置参数
输入参数:NA
输出参数:param     获取到的参数
返 回 值:成功返回IVS_SUCCEDD
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_GetLocalConfigParam(MP_LOCAL_CONFIG* param);

/* *************************************************************************
函数名称:MP_SetEventCallBack()
功能描述:设置事件回调
输入参数:fEventCallBack 事件回调函数
        pUserData      用户数据
返 回 值:成功返回IVS_SUCCEDD
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_SetEventCallBack(MP_EventCallBack fEventCallBack, IVS_VOID* pUserData);

/* *************************************************************************
* 函数名称: MP_NET_SetFirstFrameCallBack
* 功能描述: 设置解码第一帧回调
* 输入参数: callback            元数据回调函数指针
           pUserData           自定义用户数据
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetFirstFrameCallBack(MP_FIRSTFRAME_CALLBACK callback, IVS_VOID* pUserData);

/* *******************************************************01流媒体、本地文件播放**********************************************************
 */

#ifndef MPSDK_LINUX

/* *************************************************************************
函数名称: MP_StartStreamPlay
功能描述: 启动流媒体开始播放
输入参数: hWnd             播放窗体
         pRealplayPara    播放参数
输出参数: pHandle          播放句柄
返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_StartStreamPlay(HWND hWnd, MP_STREAMPLAY_PARAM* pPlayPara, IVS_ULONG* pHandle);

/* ****************************************************************************
函数名称：MP_StartFilePlay
功能描述：启动本地文件播放
输入参数：pFileName  本地文件
         hWnd       窗口句柄
         MP_FILEPLAY_PARAM  文件播放参数
输出参数：pHandle 播放句柄
返 回 值：成功:0;失败返回错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_StartFilePlay(HWND hWnd, MP_FILEPLAY_PARAM* pFilePlayParam, IVS_CHAR* pFileName,
    IVS_ULONG* pHandle);

#endif

/* ****************************************************************************
函数名称：MP_InputFrameData
功能描述：向播放库输入帧数据(音、视频);
输入参数：pHandle      播放句柄
         pFrameInfo   帧数据信息
         pFrame       帧数据
         uFrameSize   帧数据长度
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_InputFrameData(IVS_ULONG pHandle, MP_FRAME_INFO* pFrameInfo, IVS_CHAR* pFrame,
    IVS_UINT32 uFrameSize);

/* ****************************************************************************
函数名称：MP_StopPlay
功能描述：停止播放
输入参数：pHandle      播放句柄
输出参数：无
返 回 值：int
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_StopPlay(IVS_ULONG pHandle);

/* ****************************************************************************
函数名称：MP_PausePlay
功能描述：暂停播放
输入参数：pHandle 播放句柄
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_PausePlay(IVS_ULONG pHandle);

/* ****************************************************************************
函数名称：MP_ResumePlay
功能描述：恢复播放
输入参数：pHandle 播放句柄
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_ResumePlay(IVS_ULONG pHandle);

/* *****************************************************************
函数名称：MP_PlayFrameStepForward
功能描述：单帧播放前进
输入参数：pHandle          播放句柄
输出参数：NA
返 回 值：成功:0;失败:错误码
****************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_PlayFrameStepForward(IVS_ULONG pHandle);

/* *****************************************************************
函数名称：MP_PlayFrameStepBack
功能描述：单帧播放后退
输入参数：pHandle          播放句柄
输出参数：NA
返 回 值：成功:0;失败:错误码
****************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_PlayFrameStepBackward(IVS_ULONG pHandle);

/* *****************************************************************
函数名称：MP_SetPlaySpeed
功能描述：设置播放速度
输入参数：pHandle 播放句柄
         fSpeed  播放速度
输出参数：NA
返 回 值：成功:0;失败:错误码
****************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_SetPlaySpeed(IVS_ULONG pHandle, IVS_FLOAT fSpeed);

/* *****************************************************************
函数名称：MP_SetPlayDirect
功能描述：设置播放方向(仅本地文件播放支持)
输入参数：pHandle 播放句柄;
         direction 0-正放 1-倒放
输出参数：NA
返 回 值：成功:0;失败:错误码
****************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_SetPlayDirect(IVS_ULONG pHandle, MP_PLAY_FB_MODE direction);

/* ****************************************************************************
 函数名称：MP_SetPlayTime
 功能描述：设置播放时间(仅本地文件播放支持)
 输入参数：pHandle 播放句柄
          tm      播放时间
 输出参数：无
 返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_SetPlayTime(IVS_ULONG pHandle, IVS_ULONG tm);

/* ****************************************************************************
函数名称：MP_GetFileTime()
功能描述：获取文件播放总时长
输入参数：pHandle 播放句柄
输出参数：pTotalFileTime 总时长（ms）
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_GetFileTime(IVS_ULONG pHandle, IVS_ULONG* pTotalFileTime);

/* ****************************************************************************
函数名称：MP_GetPlayTime()
功能描述：获取当前播放时间
输入参数：pHandle 播放句柄
输出参数：puPlayTime 当前播放时间（单位ms）
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_GetPlayTime(IVS_ULONG pHandle, IVS_ULONG* puPlayTime);

/* *******************************************************02实况播放**********************************************************
 */

/* ****************************************************************************
函数名称：MP_Snapshot
功能描述：本地抓拍单张图片
输入参数：pHandle          播放句柄（实况、回放、本地、流媒体）
         pFileName        图片文件名称(如存在则覆盖)
         ulSnapshotFormat	图片保存类型  1-JPG 目前只支持JPG格式
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_Snapshot(IVS_ULONG pHandle, const IVS_CHAR* pFileName, IVS_ULONG ulSnapshotFormat);

/* ****************************************************************************
函数名称：MP_PlaySound
功能描述：打开随路音频
输入参数：pHandle     播放句柄（实况、回放、本地、流媒体）
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_PlaySound(IVS_ULONG pHandle);

/* ****************************************************************************
函数名称：MP_StopSound
功能描述：关闭随路音频（实况、回放、本地、流媒体）
输入参数：pHandle     播放句柄;
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_StopSound(IVS_ULONG pHandle);

/* ****************************************************************************
函数名称：MP_SetVolume
功能描述：设置音频播放音量
输入参数：pHandle 播放句柄
         uiVolumeValue 音量
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_SetVolume(IVS_ULONG pHandle, IVS_UINT32 uiVolumeValue);

/* ****************************************************************************
函数名称：MP_GetVolume
功能描述：获取音频播放音量
输入参数：pHandle 播放句柄
输出参数：uiVolumeValue 音量
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_GetVolume(IVS_ULONG pHandle, IVS_UINT32* puiVolumeValue);

/* ****************************************************************************
函数名称：MP_SetBufferStateCallback
功能描述：设置解码缓存状态回调函数
输入参数：ulChannel  通道号
         callback   回调函数指针
         pUser       用户数据
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_SetBufferStateCallback(IVS_ULONG pHandle, MP_BUFFER_STATE_CALLBACK callBack,
    IVS_VOID* pUser);

#ifndef MPSDK_LINUX

/* *************************************************************************
* 函数名称: MP_NET_StartPlay
* 功能描述: 启动实况开始播放接口
* 输入参数: hWnd             播放窗体
           pRealplayPara    播放参数
* 输出参数: pHandle          播放句柄
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_StartPlay(HWND hWnd, MP_NET_PLAY_PARAM* pRealPlayPara, IVS_ULONG* pHandle);

/* *************************************************************************
 * 函数名称: MP_NET_StopPlay
 * 功能描述: 停止实况播放接口
 * 输入参数: Handle            播放句柄
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
#endif
MP_API IVS_INT32 __SDK_CALL MP_NET_StopPlay(IVS_ULONG Handle);

#ifndef MPSDK_LINUX

/* *************************************************************************
* 函数名称: MP_UpdateWindowPartial
* 功能描述: 局部放大接口
* 输入参数: Handle             播放句柄（实况、回放）
           hWnd                窗口句柄
           pRealPlayPara       局部参数
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_UpdateWindowPartial(IVS_ULONG Handle, HWND hWnd, MP_LAYOUT_DRAW_PARTIAL* pRealPlayPara);

/* *************************************************************************
 * 函数名称: MP_DelPlayWnd
 * 功能描述: 删除播放窗口
 * 输入参数: ulPlayHandle   播放句柄
            hWnd       窗口句柄
 * 输出参数: NA
 * 返 回 值: 成功返回0，失败返回错误码
 ************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_DelPlayWnd(IVS_ULONG Handle, HWND hWnd);

/* *************************************************************************
 * 函数名称: IVS_SDK_AddPlayWindowPartial
 * 功能描述: 加入局部播放窗口
 * 输入参数: ulPlayHandle 播放句柄 （实况、回放）
            hWnd         窗口句柄
            pPartial     放大窗口的百分比
 * 输出参数: NA
 * 返 回 值: 成功返回0，失败返回错误码
 ************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_AddPlayWindowPartial(IVS_ULONG ulPlayHandle, HWND hWnd,
    MP_LAYOUT_DRAW_PARTIAL* pPartial);

#endif

/* *************************************************************************
* 函数名称: MP_NET_StartRecord
* 功能描述: 本地录像接口
* 输入参数: pHandle             播放句柄（实况、回放）
           pRecordParam        下载参数结构体
           bAssociatedAudio    是否下载音频
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_StartRecord(IVS_ULONG pHandle, const MP_RECORD_PARAM* pRecordParam,
    IVS_BOOL bAssociatedAudio);

/* *************************************************************************
 * 函数名称: MP_NET_StopRecord
 * 功能描述: 停止本地录像接口
 * 输入参数: pHandle             播放句柄（实况、回放）
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StopRecord(IVS_ULONG pHandle);

// 加密视频对外要提供两个接口  1.回调提示是否加密 2.设置密钥字符串
// 内部处理要做 两件事情  1.根据RTSP
// ANOUNCE解析出视频流是否是加密的，通过回调提示出去，如果是加密的，CU则要向Restful获取key，然后通过SDK设置Key
// 2.如果是加密流，MP要解析rtp流

/* *************************************************************************
* 函数名称: MP_NET_SetEncryptionStateCallBack
* 功能描述: 设置获取媒体播放是否加密回调
* 输入参数: callBack            回调函数指针
           pUser               用户数据
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetEncryptionStateCallBack(MP_ENCRY_STATE_CALLBACK callBack, IVS_VOID* pUser);

/* *************************************************************************
* 函数名称: MP_NET_SetKey
* 功能描述: 设置加密视频密钥
* 输入参数: pHandle             播放句柄（实况、回放）
           pszPlain            密钥正文
           ullLenPlain         密钥长度
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetScreKey(IVS_ULONG pHandle, IVS_UCHAR* pszPlain, IVS_UINT64 ullLenPlain);

/* *************************************************************************
* 函数名称: MP_NET_SetDisplayScale
* 功能描述: 设置播放显示比例
* 输入参数: pHandle             播放句柄（实况、回放）
           iDisplayScale       显示仪比例控制，1-原始比例显示 2-满屏显示
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetDisplayScale(IVS_ULONG pHandle, IVS_INT32 iDisplayScale);

#ifndef MPSDK_LINUX
/* *************************************************************************
* 函数名称: MP_NET_SetMetadataCallBack
* 功能描述: 设置元数据回调
* 输入参数: pHandle             播放句柄（实况、回放）
           callback            元数据回调函数指针
           pUserData           自定义用户数据
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetMetadataCallBack(IVS_ULONG pHandle, MP_METADATA_CALLBACK metaDataCallback, 
                                                       MP_VIDEODATA_CALLBACK videoDataCallback, IVS_VOID* pUserData);

/* *************************************************************************
 * 函数名称: MP_NET_EnableGPU
 * 功能描述: 开启/关闭 GPU加速
 * 输入参数: bEnable             硬解标志，0-不开启 1-开启
 * 输出参数: 无
 * 返 回 值: 成功返回IVS_SUCCEED，失败返回IVS_FAIL
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_EnableGPU(IVS_BOOL bEnable);
#endif

/* *************************************************************************
 * 函数名称: MP_NET_SetDecodeType
 * 功能描述: 设置编码类型
 * 输入参数: decodeType             编码类型, 0-海思 1-FFMPEG
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetDecodeType(IVS_INT32 decodeType);

/* *************************************************************************
* 函数名称: MP_NET_SetOnlyIDR
* 功能描述: 设置是否只解I帧
* 输入参数: pHandle             播放句柄（实况、回放）
           bOnlyIDR            是否只解I帧 0-不只解I帧 1-只解I帧
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetOnlyIDR(IVS_ULONG pHandle, IVS_BOOL bOnlyIDR);

/* *************************************************************************
* 函数名称: MP_NET_SetPlayQualityMode
* 功能描述: 码流质量切换
* 输入参数: pHandle             播放句柄（实况、回放）
           iPlayQualityMode    播放模式（1-流畅优先，2-画质优先）
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetPlayQualityMode(IVS_ULONG pHandle, IVS_INT32 iPlayQualityMode);

/* *************************************************************************
* 函数名称: MP_NET_EnableOptimization
* 功能描述: 丢包阈值策略
* 输入参数: iEnable             是否开启
           nLostValue          丢包率阈值
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_EnableOptimization(IVS_INT32 iEnable, IVS_INT32 nLostValue);

/* *************************************************************************
 * 函数名称: MP_NET_GetPlayInfo
 * 功能描述: 获取播放信息
 * 输入参数: pHandle             播放句柄（实况、回放、文件）
 * 输出参数: playInfo            播放信息
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_GetPlayInfo(IVS_ULONG pHandle, MP_PLAY_INFO* playInfo);

/* *******************************************************03语音对讲、广播**********************************************************
 */

/* *************************************************************************
 * 函数名称: MP_NET_StartVoiceTalkBack
 * 功能描述: 开启语音对讲
 * 输入参数: pTalkbackParam      语音对讲参数（注：目前只支持UDP方式）
 * 输出参数: pHandle         对讲句柄
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StartVoiceTalkBack(MP_VOICE_TALKBACK_PARAM* pTalkbackParam, IVS_ULONG* pHandle);

/* *************************************************************************
 * 函数名称: MP_NET_StopVoiceTalkBack
 * 功能描述: 关闭语音对讲
 * 输入参数: pTalkHandle             对讲句柄
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StopVoiceTalkBack(IVS_ULONG talkHandle);

/* *************************************************************************
* 函数名称: MP_NET_StartRealBroadcast
* 功能描述: 开始实时语音广播
* 输入参数: broadcast 广播地址数组
           count 地址数量
* 输出参数: pHandle 语音广播句柄
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_StartRealBroadcast(MP_VOICE_TALKBACK_PARAM broadcast[], int count,
    IVS_ULONG* pHandle);

/* *************************************************************************
 * 函数名称: MP_NET_StopRealBroadcast
 * 功能描述: 关闭实时语音广播
 * 输入参数: talkHandle 语音广播句柄
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StopRealBroadcast(IVS_ULONG talkHandle);

/* *************************************************************************
* 函数名称: MP_NET_StartFileBroadcast
* 功能描述: 开始文件语音广播
* 输入参数: broadcast 广播地址数组
           count 地址数量
           pFileName  音频文件名,
           bCycle     是否循环播放：0-不循环，1-循环
* 输出参数: pHandle 语音广播句柄
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_StartFileBroadcast(MP_VOICE_TALKBACK_PARAM broadcast[], int count,
    const IVS_CHAR* pFileName, IVS_BOOL bCycle, IVS_ULONG* pHandle);

/* *************************************************************************
 * 函数名称: MP_NET_StopFileBroadcast
 * 功能描述: 停止文件语音广播
 * 输入参数: 无
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StopFileBroadcast(IVS_ULONG talkHandle);

/* *******************************************************04实况裸码流转发**********************************************************
 */

/* *************************************************************************
* 函数名称: MP_StartPlayCallBackFrame
* 功能描述: 开启裸码流回调 (实况、回放）
* 输入参数: param               播放参数
           callback            实况裸码流回调函数
           pUserData           用户数据
* 输出参数: pHandle             播放句柄
* 返 回 值: 成功返回IVS_SUCCESS，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_StartPlayCallBackFrame(const MP_NET_PLAY_PARAM* param,
    MP_REALPLAY_CALLBACKFRAME callback, IVS_VOID* pUserData, IVS_ULONG* pHandle);

/* *******************************************************05回放播放**********************************************************
 */


#ifndef  MPSDK_LINUX

/* *************************************************************************
* 函数名称: MP_NET_StartPlayBack
* 功能描述: 启动录像回放开始播放接口
* 输入参数: hWnd             播放窗体
           pPlayBackPara    播放参数
* 输出参数: pHandle          播放句柄
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_StartPlayBack(HWND hWnd, MP_NET_PLAY_PARAM* pPlayBackPara, IVS_ULONG* pHandle);

#endif

/* *************************************************************************
 * 函数名称: MP_NET_StopPlayBack
 * 功能描述: 停止录像回放播放接口
 * 输入参数: pHandle            播放句柄
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StopPlayBack(IVS_ULONG pHandle);

/* *************************************************************************
* 函数名称: MP_NET_SetPlayBackSpeed
* 功能描述: 设置回放速度
* 输入参数: pHandle            播放句柄
           fSpeed             播放速度
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetPlayBackSpeed(IVS_ULONG pHandle, IVS_FLOAT fSpeed);

/* *************************************************************************
 * 函数名称: MP_NET_GetPlayBackSpeed
 * 功能描述: 获取回放速度
 * 输入参数: pHandle            播放句柄
 * 输出参数: pfSpeed            播放速度
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_GetPlayBackSpeed(IVS_ULONG pHandle, IVS_FLOAT* pfSpeed);

/* *****************************************************************
函数名称：MP_NET_SetPlayDirect
功能描述：设置播放方向
输入参数：pHandle        播放句柄(回放)
         direction      0-正放 1-倒放
输出参数：NA
返 回 值：成功:0;失败:错误码
****************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetPlayDirect(IVS_ULONG pHandle, MP_PLAY_FB_MODE direction);

/* ****************************************************************************
 函数名称：MP_NET_SetPlayTime
 功能描述：设置播放时间
 输入参数：pHandle     播放句柄(回放)
          tm      播放时间
 输出参数：无
 返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetPlayTime(IVS_ULONG pHandle, IVS_ULONG tm);

/* ****************************************************************************
函数名称：MP_NET_GetPlayTime
功能描述：获取当前播放时间
输入参数：pHandle     播放句柄（回放）
输出参数：puPlayTime  当前播放时间（单位ms）
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_NET_GetPlayTime(IVS_ULONG pHandle, IVS_ULONG* puPlayTime);

/* ****************************************************************************
函数名称：MP_NET_PausePlay
功能描述：暂停播放
输入参数：pHandle 播放句柄(实况、回放)
输出参数：NA
返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_NET_PausePlay(IVS_ULONG pHandle);

/* ****************************************************************************
 函数名称：MP_NET_ResumePlay
 功能描述：恢复播放
 输入参数：pHandle 播放句柄（实况、回放）
 输出参数：NA
 返 回 值：成功:0;失败:错误码
**************************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_NET_ResumePlay(IVS_ULONG pHandle);

/* *****************************************************************
 函数名称：MP_NET_PlayFrameStepForward
 功能描述：单帧播放前进
 输入参数：pHandle          播放句柄(回放)
 输出参数：NA
 返 回 值：成功:0;失败:错误码
****************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_NET_PlayFrameStepForward(IVS_ULONG pHandle);

/* *****************************************************************
 函数名称：MP_NET_PlayFrameStepBackward
 功能描述：单帧播放后退
 输入参数：pHandle          播放句柄(回放)
 输出参数：NA
 返 回 值：成功:0;失败:错误码
****************************************************************** */
MP_API IVS_INT32 __SDK_CALL MP_NET_PlayFrameStepBackward(IVS_ULONG pHandle);

/* *******************************************************06录像裸码流转发**********************************************************
 */

/* *************************************************************************
* 函数名称: MP_NET_SetPlayBackCallBackFrame
* 功能描述: 设置录像回放裸码流回调
* 输入参数: pHandle             播放句柄（回放）
           callback            录像裸码流回调函数
           pUserData           用户数据
* 输出参数: 无
* 返 回 值: 成功返回0，失败返回错误码
************************************************************************* */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetPlayBackCallBackFrame(const MP_NET_PLAY_PARAM* param,
    MP_PLAYBACK_CALLBACKFRAME callback, IVS_VOID* pUserData, IVS_ULONG* pHandle);

/* *******************************************************07录像下载**********************************************************
 */

/* *************************************************************************
 * 函数名称: MP_NET_StartDownload
 * 功能描述: 开始录像下载接口
 * 输入参数: pPlayBackPara       录像下载参数
 * 输出参数: pulHandle           录像下载句柄
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StartDownload(MP_RECORD_PARAM* pDownloadPara, IVS_ULONG* pulHandle);

/* *************************************************************************
 * 函数名称: MP_NET_StopDownload
 * 功能描述: 停止录像下载接口
 * 输入参数: pulHandle       录像下载句柄
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_StopDownload(IVS_ULONG pulHandle);

/* *************************************************************************
 * 函数名称: MP_NET_SetDownLoadSpeed
 * 功能描述: 设置录像下载速度接口
 * 输入参数: pulHandle       录像下载句柄
 * fSpeed          下载速度
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_SetDownLoadSpeed(IVS_ULONG pulHandle, float fSpeed);

/* *************************************************************************
 * 函数名称: MP_NET_PauseDownload
 * 功能描述: 暂停录像下载接口
 * 输入参数: pulHandle       录像下载句柄
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_PauseDownload(IVS_ULONG pulHandle);

/* *************************************************************************
 * 函数名称: MP_NET_ResumeDownload
 * 功能描述: 恢复录像下载接口
 * 输入参数: pulHandle       录像下载句柄
 * 输出参数: 无
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_ResumeDownload(IVS_ULONG pulHandle);

/* *************************************************************************
 * 函数名称: MP_NET_GetDownloadInfo
 * 功能描述: 恢复录像下载接口
 * 输入参数: pulHandle       录像下载句柄
 * 输出参数: pDownloadInfo   录像下载信息
 * 返 回 值: 成功返回0，失败返回错误码
 * ************************************************************************ */
MP_API IVS_INT32 __SDK_CALL MP_NET_GetDownloadInfo(IVS_ULONG pulHandle, MP_DOWNLOAD_INFO* pDownloadInfo);

#ifdef __cplusplus
}
#endif

#endif // MP_H
