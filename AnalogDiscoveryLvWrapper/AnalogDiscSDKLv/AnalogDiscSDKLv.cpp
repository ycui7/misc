// AnalogDiscSDKLv.cpp : LabVIEW C calling wrapper dll.
// Copyright (C) 2014 Yang Cui
// vmbncy@gmail.com
// Licensed under GPLv3 

// Most nomenclature made consistent with WaveForm's SDK manual
// This is only a partial SDK wrapper, to get the work done quick. 
// If you like more features to be added, please donate to 
// BTC: 1ARLZ8rDFSwqRQqYSE8AA2JuH7ZUFwfNTw 
// 



#include "stdafx.h"
#include "AnalogDiscSDKLv.h"




/********************************************************
 *  Wrapper start here                                  *
 ********************************************************/
int debugLevel = 0;

bool FApi(const char * szApi, BOOL fResult){
//    if(debugLevel>=2) printf(">>%s\n", szApi);
    if(fResult == 0){
        char szError[512];
        FDwfGetLastErrorMsg(szError);
        // printf("FAILED: %s\n%s\n", szApi, szError);
        return false;
    }
 //   if(debugLevel>=3) PrintDateTime(false);
    return true;
}


//typedef struct{
//	int DevId;
//	char DevName[32];
//	char SerialNum[32];
//	char userName[32];
//	int isBusy;
//}DeviceInfo;




int Enum_DevLv(ENUMFILTER enumfilter, int * pnDevice, char DevName[MAX_DEVICE_NUMBER][DEVICE_INFO_STRING_LENGTH], char SN[MAX_DEVICE_NUMBER][DEVICE_INFO_STRING_LENGTH], char UserName[MAX_DEVICE_NUMBER][DEVICE_INFO_STRING_LENGTH], int isBusy[MAX_DEVICE_NUMBER], DEVID DeviceID[MAX_DEVICE_NUMBER], DEVVER DeviceVersion[MAX_DEVICE_NUMBER]){
    int devcount = 0;
	char sz[512];
    BOOL fBusy;
    DEVID devid;
    DEVVER devver;
    HDWF h = hdwfNone;

    if(!FApi("FDwfEnum", FDwfEnum(enumfilterAll, &devcount))) return false;

	*pnDevice = devcount;

    for(int i = 0; i < devcount; i++){

        if(!FApi("FDwfEnumDeviceName", FDwfEnumDeviceName(i, sz))) continue;
        strcpy(DevName[i], sz);

        if(!FApi("FDwfEnumSN", FDwfEnumSN(i, sz))) continue;
		strcpy(SN[i], sz);

        if(!FApi("FDwfEnumUserName", FDwfEnumUserName(i, sz))) continue;
		strcpy(UserName[i], sz);
        
        if(!FApi("FDwfEnumDeviceType", FDwfEnumDeviceType(i, &devid, &devver))) continue;
		DeviceID[i] = devid;
		DeviceVersion[i] = devver;

        if(!FApi("FDwfEnumDeviceIsOpened", FDwfEnumDeviceIsOpened(i, &fBusy))) continue;
        isBusy[i] = fBusy;
    }
	return true;	// 1 : normal, 0 : error 
}

// Device Initial/Open/Close/Reset
int Open_DevLv(int idxDev, HDWF *phdwf){
	return FDwfDeviceOpen(idxDev, phdwf);
}
int Close_DevLv(HDWF hdwf){
	return FDwfDeviceClose(hdwf);
}

int Reset_DevLv(HDWF hdwf){
	return FDwfDeviceReset(hdwf);
}
int SetAutoConfig_DevLv(HDWF hdwf, int fAutoConfig){
	return FDwfDeviceAutoConfigureSet(hdwf,fAutoConfig);
}

// Trigger functions

int GetInfo_AnalogIn_Trigger(HDWF hdwf, TRIGSRC * ptrigsrc){
	return FDwfAnalogInTriggerSourceGet(hdwf, ptrigsrc);
}
int Set_AnalogIn_Trigger(HDWF hdwf, TRIGSRC AItrigsrc, double timeout){
	int noerror = false;

	if(FDwfAnalogInTriggerAutoTimeoutSet(hdwf, timeout))
		noerror = true;
	if(FDwfAnalogInTriggerSourceSet(hdwf, AItrigsrc))
		noerror = true;
	return noerror;
}



//AnalogIn 
int GetStatus_AnalogIn(HDWF hdwf, int fReadData, STS *psts){
	return FDwfAnalogInStatus(hdwf, true, psts);
	// STS: Byte 
}

int GetData_AnalogIn(HDWF hdwf, int idxChannel, double rgdSamples[], int BufferSize){
	return FDwfAnalogInStatusData (hdwf, idxChannel, rgdSamples, BufferSize);
}

int Config_AnalogIn(HDWF hdwf,	int fReconfigure, int fStart){
	return FDwfAnalogInConfigure(hdwf, fReconfigure, fStart);
}

// Channel independent configure
int SetAcquisitionConfig_AnalogIn(HDWF hdwf, double hzFrquency, int nSize, ACQMODE  AcqMode = acqmodeSingle /*, double RecordLength */){
	int noerror = false;

	if(FDwfAnalogInFrequencySet(hdwf, hzFrquency))
		noerror = true;
	if(FDwfAnalogInBufferSizeSet(hdwf, nSize))
		noerror = true;
	if(FDwfAnalogInAcquisitionModeSet(hdwf, AcqMode))
		noerror = true;
	return noerror;
}
int GetAcquisitionsConfig_AnalogIn(HDWF hdwf){
	return 0;
}


// Channel dependent configure
int SetChannelsConfig_AnalogIn(HDWF hdwf, int idxChannel, int fEnable,	double voltsRange, FILTER Filter, double voltOffset){
	int noerror = 0;

	if(FDwfAnalogInChannelEnableSet(hdwf, idxChannel, fEnable))
		noerror = true;
	if(FDwfAnalogInChannelFilterSet(hdwf, idxChannel, Filter))
		noerror = true;
	if(FDwfAnalogInChannelRangeSet(hdwf, idxChannel, voltsRange))
		noerror = true;
	if(FDwfAnalogInChannelOffsetSet(hdwf, idxChannel, voltOffset))
		noerror = true; 	// voltOffset consistent with official manual

	return noerror;
}

int GetChannelsConfig_AnalogIn(HDWF hdwf){
	return 0;
}
