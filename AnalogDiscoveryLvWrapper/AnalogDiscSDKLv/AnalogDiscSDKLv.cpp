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
//	char DevName[512];
//	char SerialNum[512];
//	char userName[512];
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

int GetInfo_Trigger(HDWF hdwf, int* pfstrigsrc){
	return FDwfDeviceTriggerInfo(hdwf, pfstrigsrc);
}
int Set_Trigger(HDWF hdwf, int idxPin,TRIGSRC trigsrc = trigsrcExternal1){
	return FDwfDeviceTriggerSet(hdwf, idxPin, trigsrc);
}



//AnalogIn 
extern "C" __declspec(dllexport) int GetStatus_AnalogIn(HDWF hdwf, int fReadData, STS *psts){
	return FDwfAnalogInStatus(hdwf, true, psts);
	// STS: Byte 
}

extern "C" __declspec(dllexport) int GetData_AnalogIn(HDWF hdwf, int idxChannel, double rgdSamples[], int BufferSize){
	return FDwfAnalogInStatusData (hdwf, idxChannel, rgdSamples, BufferSize);
}

extern "C" __declspec(dllexport) int Config_AnalogIn(HDWF hdwf,	int fReconfigure, int fStart){
	return FDwfAnalogInConfigure(hdwf, fReconfigure, fStart);
}

// Channel independent configure
extern "C" __declspec(dllexport) int SetAcquisitionConfig_AnalogIn(HDWF hdwf, double hzFrquency, int nSize, ACQMODE  AcqMode = acqmodeSingle /*, double RecordLength */){
	int error = false;

	error = FDwfAnalogInFrequencySet(hdwf, hzFrquency);
	error = error || FDwfAnalogInBufferSizeSet(hdwf, nSize);
	error = error || FDwfAnalogInAcquisitionModeSet(hdwf, AcqMode);

	return error;
}
extern "C" __declspec(dllexport) int GetAcquisitionsConfig_AnalogIn(HDWF hdwf){
	return 0;
}


// Channel dependent configure
extern "C" __declspec(dllexport) int SetChannelsConfig_AnalogIn(HDWF hdwf, int idxChannel, int fEnable,	double voltsRange, FILTER Filter, double voltOffset){
	int error = 0;

	error = FDwfAnalogInChannelEnableSet(hdwf, idxChannel, fEnable);
	error = error || FDwfAnalogInChannelFilterSet(hdwf, idxChannel, Filter);
	error = error || FDwfAnalogInChannelRangeSet(hdwf, idxChannel, voltsRange);
	error = error || FDwfAnalogInChannelOffsetSet(hdwf, idxChannel, voltOffset); // voltOffset consistent with official manual

	return error;
}

extern "C" __declspec(dllexport) int GetChannelsConfig_AnalogIn(HDWF hdwf){
	return 0;
}
