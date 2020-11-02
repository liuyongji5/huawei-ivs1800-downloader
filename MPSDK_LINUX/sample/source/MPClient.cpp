#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <unistd.h>
#include <string.h>
#include "curl/curl.h"
#include <json/json.h>
#include "MPSDKDef.h"
#include "MP.h"


using namespace std;
std::string  g_strSessionId;
std::string  g_strBaseURL;
int          g_isDownLoadStop = 0;

static int OnDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *)
{
	if (itype == CURLINFO_TEXT)
	{
		//printf("[TEXT]%s\n", pData);
	}
	else if (itype == CURLINFO_HEADER_IN)
	{
		printf("[HEADER_IN]%s\n", pData);
	}
	else if (itype == CURLINFO_HEADER_OUT)
	{
		printf("[HEADER_OUT]%s\n", pData);
	}
	else if (itype == CURLINFO_DATA_IN)
	{
		printf("[DATA_IN]%s\n", pData);
	}
	else if (itype == CURLINFO_DATA_OUT)
	{
		printf("[DATA_OUT]%s\n", pData);
	}
	return 0;
}


void print_cookies(CURL *curl)
{
	CURLcode res;
	struct curl_slist *cookies;
	struct curl_slist *nc;
	int i;

	printf("Cookies, curl knows:\n");
	res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
	if (res != CURLE_OK) {
		fprintf(stderr, "Curl curl_easy_getinfo failed: %s\n", curl_easy_strerror(res));
		//exit(1);
	}
	nc = cookies, i = 1;
	while (nc) {
		printf("[%d]: %s\n", i, nc->data);
		nc = nc->next;
		i++;
	}
	if (i == 1) {
		printf("(none)\n");
	}
	curl_slist_free_all(cookies);
}

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if (NULL == str || NULL == buffer)
	{
		return -1;
	}

	char* pData = (char*)buffer;
	str->append(pData, size * nmemb);
	return nmemb;
}

static size_t OnHeaderWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if (NULL == str || NULL == buffer)
	{
		return -1;
	}

	char* pData = (char*)buffer;
	str->append(pData, size * nmemb);
	return nmemb;
}

int HttpPosts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool isLoginIn)
{
	std::cout << "strPost is: " << strPost << std::endl;
	CURLcode res;

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Type:application/json");

	CURL* curl = curl_easy_init();
	if (NULL == curl)
	{
		return CURLE_FAILED_INIT;
	}
	if (0)
	{
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
	}
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
	//如果已登录则需要设置JSESSIONID
	if (isLoginIn) {
		std::cout << "g_strSessionId is: " << g_strSessionId << std::endl;
		curl_easy_setopt(curl, CURLOPT_COOKIE, g_strSessionId.c_str());
	}
	// curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	std::string  strHeader;
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, OnHeaderWriteData);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&strHeader);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);//设定为不验证证书和HOST  
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

	res = curl_easy_perform(curl);
	if (res != 0)
	{
		std::cout << "Curl Error is: " << res << std::endl;
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}

	std::cout << "strHeader is: " << strHeader << std::endl;
	//如果是登录场景，获取JSESSIONID
    if (!isLoginIn) {
		std::string  strCookie;
		if(string::npos == strHeader.find("Set-Cookie:"))
		{
			std::cout << "Login Failed without Set-Cookie \n";
			return -1;
		}
	    strCookie = strHeader.substr(strHeader.find("Set-Cookie:"));
	    g_strSessionId = strCookie.substr(12, strCookie.find(";") - 11);
		std::cout << "g_strSessionId is: " << g_strSessionId << std::endl;
	}

	//输出cookie信息
	//print_cookies(curl);
	curl_easy_cleanup(curl);
	return res;
}

int HttpGet(const std::string & strUrl, std::string & strResponse)
{
	CURLcode res;

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Type:application/json");

	CURL* curl = curl_easy_init();
	if (NULL == curl)
	{
		return CURLE_FAILED_INIT;
	}
	if (0)
	{
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, OnDebug);
	}
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	//JSESSIONID
	std::cout << "g_strSessionId is: " << g_strSessionId << std::endl;
	curl_easy_setopt(curl, CURLOPT_COOKIE, g_strSessionId.c_str());
	// curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	std::string  strHeader;
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, OnHeaderWriteData);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&strHeader);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);//设定为不验证证书和HOST  
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

	res = curl_easy_perform(curl);
	if (res != 0)
	{
		std::cout << "Curl Error is: " << res << std::endl;
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}

	std::cout << "strHeader is: " << strHeader << std::endl;

	//输出cookie信息
	//print_cookies(curl);
	curl_easy_cleanup(curl);
	return res;
}

int login(std::string host, std::string userName, std::string password)
{
	std::cout << "Login Start."<< std::endl;
	//std::string jsonStrLogin;
	Json::Value login_data;
	// Json::StreamWriterBuilder writerBuilder;
	// ostringstream os;
	//读取配置文件
	// ifstream urlRightFile(configFilePath.c_str());
	// std::string line; // 配置文件中每一行字符串
 //    std::string::size_type pos;
	// std::cout << "get config begin"<< std::endl;
	// while (getline(urlRightFile, line)) {
	// 	std::cout << "line: "<< line << std::endl;
 //        pos = line.find("=");
	// 	std::cout << "pos: "<< pos << std::endl;
 //        if (pos != std::string::npos) {
	// 	    std::string key = line.substr(0, pos);
	// 		std::cout << "key: "<< key << std::endl;
	// 		if (key == "userName" || key == "password"){
	// 			std::cout << "value: "<< line.substr(pos + 1) << std::endl;
	// 			login_data[key.c_str()] = Json::Value(line.substr(pos + 1));
	// 		}
	// 		if (key == "url") {
	// 			g_strBaseURL = line.substr(pos + 1);
	// 		}
			
 //        } else {
 //            continue;
 //        }
 //    }
	g_strBaseURL = host;
	login_data["userName"] = userName.c_str();
	login_data["password"] = password.c_str();
	// std::cout << "---get config end---"<< std::endl;
	//unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
	//jsonWriter->write(login_data, &os);
	//jsonStrLogin = os.str();

	std::string login_url = g_strBaseURL + "/loginInfo/login/v1.0";
	std::string jsonOutStr;
	std::cout << "---login begin---"<< std::endl;
	//登录
	if (0 == HttpPosts(login_url, login_data.toStyledString(), jsonOutStr, false))
	{
		bool res;
		std::string errs;
		Json::Value result;
		Json::CharReaderBuilder readerBuilder;
		Json::Reader reader;

		//unique_ptr<Json::CharReader> jsonReader(readerBuilder.newCharReader());
		//res = jsonReader->parse(jsonOutStr.c_str(), jsonOutStr.c_str() + jsonOutStr.length(), &result, &errs);
		if (!reader.parse(jsonOutStr, result)) {
			std::cout << "parseJson err. " << errs << std::endl;
			return -1;
		}
     	std::cout << "login resultCode is: " << result["resultCode"] << std::endl;
		return result["resultCode"].asInt();
	}
	else
	{	
		std::cout << "---login failed---"<< std::endl;
		return -1;
	}
}

int getUrl(std::string cameraCode, std::string startTime, std::string endTime, std::string &downloadUrl)
{
	std::string jsonStr;
	Json::Value getUrl_data;
	Json::Value mediaURLParam;
	Json::Value timeSpan;
	Json::StreamWriterBuilder writerBuilder;
	//ostringstream os;
	std::cout << "---getUrl begin---"<< std::endl;
	std::string jsonOutStr;

	//获取RTSP URL
	std::string download_url = g_strBaseURL + "/video/rtspurl/v1.0";
	timeSpan["startTime"] = startTime;
	timeSpan["endTime"] = endTime;
	mediaURLParam["timeSpan"] = timeSpan;
	mediaURLParam["serviceType"] = 3;          //录像下载
	mediaURLParam["packProtocolType"] = 1;     //ES流
	mediaURLParam["streamType"] = 1;           //主码流
	mediaURLParam["protocolType"] = 2;         //1.UDP 2.TCP
	mediaURLParam["transMode"] = 0;  
	mediaURLParam["broadCastType"] = 0;
	mediaURLParam["clientType"] = 0;           //下载采用MP媒体库
	//mediaURLParam["supportTLS"] = 1;           //下载采用MP媒体库
	getUrl_data["cameraCode"] = cameraCode;
	getUrl_data["mediaURLParam"] = mediaURLParam;

	//unique_ptr<Json::StreamWriter> jsonWriterUrl(writerBuilder.newStreamWriter());
	//ostringstream osUrl;
	//jsonWriterUrl->write(getUrl_data, &osUrl);
	//jsonStr = osUrl.str();
	//获取url
	if (0 == HttpPosts(download_url, getUrl_data.toStyledString(), jsonOutStr, true))
	{
		bool res;
		std::string errs;
		Json::Value result;
		//Json::CharReaderBuilder readerBuilder;
		//unique_ptr<Json::CharReader> jsonReaderUrl(readerBuilder.newCharReader());
		//res = jsonReaderUrl->parse(jsonOutStr.c_str(), jsonOutStr.c_str() + jsonOutStr.length(), &result, &errs);
		Json::Reader reader;

		if (!reader.parse(jsonOutStr, result)) {
			std::cout << "getUrl parseJson err. " << errs << std::endl;
			return -1;
		}
		std::cout << "getUrl jsonOutStr is: " << jsonOutStr << std::endl;
		std::cout << "getUrl result is: " << result << std::endl;
		downloadUrl = result["rtspURL"].asString();
		return 0;
	}

}


void logout()
{
	std::string jsonOutStr;
	//登出
	std::string logout_url = g_strBaseURL + "/users/logout";
	if (0 == HttpGet(logout_url, jsonOutStr)) {
		bool res;
		std::string errs;
		Json::Value result;
		Json::CharReaderBuilder readerBuilder;

		unique_ptr<Json::CharReader> jsonReaderLogout(readerBuilder.newCharReader());
		res = jsonReaderLogout->parse(jsonOutStr.c_str(), jsonOutStr.c_str() + jsonOutStr.length(), &result, &errs);
		if (!res || !errs.empty()) {
			std::cout << "logout parseJson err. " << errs << std::endl;
		}
		std::cout << "logout jsonOutStr is: " << jsonOutStr << std::endl;
		std::cout << "logout result is: " << result << std::endl;
	}
}



void __SDK_CALL sdkEventCallBack(IVS_INT32 iEventType, IVS_VOID* pEventBuf, IVS_UINT32 uiBufSize, IVS_VOID* pUserData)
{
	switch (iEventType)
	{
	case MP_EVENT_DOWNLOAD_SUCCESS:
	{
		std::cout << "MP_EVENT_DOWNLOAD_SUCCESS" << std::endl;
		MP_EVENT_INFO *pEventInfo = static_cast<MP_EVENT_INFO *>(pEventBuf);
		std::cout <<"cFileName is:"<< pEventInfo->recordInfo.cFileName << std::endl;
		std::cout <<"cFilePath is:" << pEventInfo->recordInfo.cFilePath << std::endl;
		std::cout <<"cOperationTime is:" << pEventInfo->recordInfo.cOperationTime << std::endl;
	}
	break;
	case MP_EVENT_NORMAL_STOP:
	{
		std::cout << "MP_EVENT_NORMAL_STOP"<<std::endl;
		MP_EVENT_INFO *pEventInfo = static_cast<MP_EVENT_INFO *>(pEventBuf);

		MP_DOWNLOAD_INFO info;
		MP_NET_GetDownloadInfo(pEventInfo->ulHandle, &info);

		std::cout << "uiDownloadSize is:" << info.uiDownloadSize << std::endl;
		std::cout << "uiDownloadSpeed is:" << info.uiDownloadSpeed << std::endl;
		std::cout << "uiDownloadStatus is:" << info.uiDownloadStatus << std::endl;
		std::cout << "uiProgress is:" << info.uiProgress << std::endl;

		MP_NET_StopDownload(pEventInfo->ulHandle);
		g_isDownLoadStop = 1;
	}
	break;
	case MP_EVENT_ABNORMAL_STOP:
	{
		std::cout << "MP_EVENT_ABNORMAL_STOP";
		g_isDownLoadStop = 1;
	}
	break;
	case MP_EVENT_CONNECT_DISCONNECT:
	{
		std::cout << "MP_EVENT_CONNECT_DISCONNECT";
		g_isDownLoadStop = 1;
	}
	break;
	default:
		g_isDownLoadStop = 1;
		break;
	}
}

int initHWMPSDK(const char * logPath)
{
	int iRet = MP_Init((char *)logPath);     //初始化MP接口
	if (iRet != 0)
	{
		std::cout << "MP_Init Failed!\n";
		return iRet;
	}
	else
	{
		std::cout << "MP_Init succeed!\n";
	}

	iRet = MP_SetEventCallBack(sdkEventCallBack, (void *)"test");
	if (iRet != 0)
	{
		std::cout << "MP_SetEventCallBack Failed :" << iRet << std::endl;
		return iRet;
	}
	else
	{
		std::cout << "MP_SetEventCallBack succeed!\n";
	}
	return 0;
}

typedef struct 
{
	char * filePath;
	char * rtspUrl;
	char * starttime;
	char * endtime;
} DownLoadPara;

int HWMPDownLoadRecord(DownLoadPara * downLoadPara, unsigned long * handle)
{

	MP_RECORD_PARAM recordParam;
	int iRet = 0;
	recordParam.uiRecordFormat = 1;    //mp4文件格式
	recordParam.uiSplitterType = 2;    //按照容量分割
	recordParam.uiSplitterValue = 2047;  //最大为2G
	recordParam.uiDownloadSpeed = 0;     //全速下载

    std::string time;
	std::string recordStarttime; 
	std::string recordEndtime;

	time = downLoadPara->starttime;
	recordStarttime = time.substr(0,8) + "T";
	recordStarttime += time.substr(8,6);
	recordStarttime += "Z";

	time = downLoadPara->endtime;
	recordEndtime = time.substr(0,8) + "T";
	recordEndtime += time.substr(8,6);
	recordEndtime += "Z";

	strncpy(recordParam.stTimeSpan.cStart, recordStarttime.c_str(), 20);    //开始时间
	strncpy(recordParam.stTimeSpan.cEnd, recordEndtime.c_str(), 20);      //结束时间
	strncpy(recordParam.cSavePath,  downLoadPara->filePath, MP_FILE_NAME_LEN);  //保存路径
	strncpy(recordParam.rtspUrl.cRtspURL, downLoadPara->rtspUrl, MP_URL_LEN);  //rtsp url地址
	recordParam.rtspUrl.uiProtocolType = 2;                                    //rtsp 传输类型
	recordParam.rtspUrl.uiRtspType = 1;                                        //rtsp是否加密
	//recordParam.rtspUrl.uiRtspType = 2;
	recordParam.rtspUrl.rtspOverNorm = 0;               //精简RTSP协议 
	recordParam.uiRecordFormat = 1;                     //mp4文件格式
	recordParam.uiSplitterType = 2;                     //按照容量分割
	recordParam.uiSplitterValue = 8192;                 //最大为2G
	recordParam.uiDownloadSpeed = 8;                    //支持设置为0, 1, 2, 4, 8 (分别为不限速，1倍，2倍，4倍，8倍速)
	recordParam.uiAudioFormat = 1;                      //AAC音频格式
	recordParam.uiNameRule = MP_REC_RULE_DEFIND_BY_USER;//自定义保存路径

	iRet = MP_NET_StartDownload(&recordParam, (IVS_ULONG* )handle);
	if (iRet != 0)
	{
		std::cout << "MP_NET_StartDownload():Failed. result:" << iRet << "\n";
		iRet = MP_NET_StopDownload(*handle);
		if (iRet != 0)
		{
			std::cout << "MP_NET_StopDownload():Failed\n";
			return iRet;
		}
		else
		{
			std::cout << "MP_NET_StopDownload():Success!\n";
			return 0;
		}
	}
	else
	{
		std::cout << "MP_NET_StartDownload():Success!\n";
	}
	return 0;
}

int main(int argc, char *argv[])
{
	//入参
	if (argc != 8) {
	 	std::cout << "Usage: "<<argv[0] << ": host "<< ": userName "<< ": password "<<": cameraCode "<<"startTime(yyyyMMddHHmmss) "<<"endTime(yyyyMMddHHmmss)"  << std::endl;
		return 0;
	}
	// std::string configFilePath("./loginConf.properties");
	// std::cout << "program is: " << configFilePath << std::endl;
	std::string host(argv[1]);
	std::string userName(argv[2]);
	std::string password(argv[3]);
	std::string cameraCode(argv[4]);
	std::string startTime(argv[5]);
	std::string endTime(argv[6]);
	std::string filePath(argv[7]);
	//std::string cameraCode("07617067202601980101");
	//std::string startTime("20200902094330");
	//std::string endTime("20200902094430");
	std::string downloadUrl;
	//ToDo 初始化MP库
	if(0 == initHWMPSDK("./"))
	{
	 	std::cout << "initHWMPSDK  succeed!\n";
	}
	else
	{
		std::cout << "initHWMPSDK  failed!\n";
	 	return -1;
	} 

    if(login(host, userName, password)==0)
	{
		std::cout << "login  succeed!\n";
	}
	else
	{
		std::cout << "login  failed!\n";
		return -1;
	}

	if(getUrl(cameraCode, startTime, endTime, downloadUrl)==0)
	{
		std::cout << "getUrl  succeed!\n";
	}
	else
	{
		std::cout << "getUrl  failed!\n";
		return -1;
	}
  
	//修改url, 新版本微云URL无需修改
	//downloadUrl = downloadUrl.replace(downloadUrl.find("ClientType="), 12, "ClientType=0");
	//std::cout << "rtspURL is: " << downloadUrl << std::endl;
	//downloadUrl = downloadUrl.substr(0, downloadUrl.find("Token="));
	//std::cout << "rtspURL is: " << downloadUrl << std::endl;

	//调用MP库，下载录像
	DownLoadPara downloadPara = { 0 };
	downloadPara.rtspUrl = (char *)downloadUrl.c_str();
	downloadPara.filePath = (char *)filePath.c_str();
	downloadPara.starttime = (char *)startTime.c_str();
	downloadPara.endtime = (char *)endTime.c_str();
	unsigned long handle; 
	if (0 == HWMPDownLoadRecord(&downloadPara, &handle))
	{
	    std::cout << "DownLoadRecord  succeed!\n";
	}
	else
	{
		std::cout << "DownLoadRecord  failed!\n";
	 	return -1;
	}

	while (g_isDownLoadStop == 0)
	{
	 	MP_DOWNLOAD_INFO info;
	 	MP_NET_GetDownloadInfo(handle, &info);

	 	std::cout << "uiDownloadSize is:" << info.uiDownloadSize << std::endl;
	 	std::cout << "uiProgress is:" << info.uiProgress << std::endl;
	 	sleep(1);
	}
    
	logout();

    //等待3S
	sleep(3);
	std::cout << "Download Task Finished!\n";
}


