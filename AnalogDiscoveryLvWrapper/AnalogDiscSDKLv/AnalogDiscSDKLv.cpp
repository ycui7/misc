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
int Set_AnalogIn_Trigger(HDWF hdwf, TRIGSRC AItrigsrc, double timeout, double secPosition, double secHoldOff){
	int noerror = false;

	if(FDwfAnalogInTriggerAutoTimeoutSet(hdwf, timeout))
		noerror = true;
	if(FDwfAnalogInTriggerSourceSet(hdwf, AItrigsrc))
		noerror = noerror && true;
	if(FDwfAnalogInTriggerPositionSet(hdwf, secPosition))
		noerror = noerror && true;
	if(FDwfAnalogInTriggerHoldOffSet(hdwf, secHoldOff))
		noerror = noerror && true;
	return noerror;
}

int Set_AnalogIn_TriggerDetector(HDWF hdwf, int idxChannel, TRIGCOND trigcond, TRIGTYPE trigtype, double voltsLevel, FILTER filter, double HystersisvoltsLEvel){
	int noerror = false;

	if(FDwfAnalogInTriggerChannelSet(hdwf, idxChannel))
		noerror = true;
	if(FDwfAnalogInTriggerConditionSet(hdwf, trigcond))
		noerror = noerror && true;
	if(FDwfAnalogInTriggerTypeSet(hdwf, trigtype))
		noerror = noerror && true;
	if(FDwfAnalogInTriggerLevelSet(hdwf, voltsLevel))
		noerror = noerror && true;
	if(FDwfAnalogInTriggerFilterSet(hdwf, filter))
		noerror = noerror && true;
	if(FDwfAnalogInTriggerHysteresisSet(hdwf, voltsLevel))
		noerror = noerror && true;

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
int SetAcquisitionConfig_AnalogIn(HDWF hdwf, double hzFrquency, int nSize, ACQMODE  AcqMode, double sLength){
	int noerror = false;

	if(FDwfAnalogInFrequencySet(hdwf, hzFrquency))
		noerror = true;
	if(FDwfAnalogInBufferSizeSet(hdwf, nSize))
		noerror = noerror && true;
	if(FDwfAnalogInAcquisitionModeSet(hdwf, AcqMode))
		noerror = noerror && true;
	if(FDwfAnalogInRecordLengthSet(hdwf, sLength))
		noerror = noerror && true;
	return noerror;
}
int GetAcquisitionsConfig_AnalogIn(HDWF hdwf){
	return 0;
}


// Channel dependent configure
int SetChannelsConfig_AnalogIn(HDWF hdwf, int idxChannel, int fEnable,	double voltsRange, FILTER Filter, double voltOffset){
	int noerror = false;

	if(FDwfAnalogInChannelEnableSet(hdwf, idxChannel, fEnable))
		noerror = true;
	if(FDwfAnalogInChannelFilterSet(hdwf, idxChannel, Filter))
		noerror = noerror && true;
	if(FDwfAnalogInChannelRangeSet(hdwf, idxChannel, voltsRange))
		noerror = noerror && true;
	if(FDwfAnalogInChannelOffsetSet(hdwf, idxChannel, voltOffset))
		noerror = noerror && true; 	// voltOffset consistent with official manual

	return noerror;
}

int GetChannelsConfig_AnalogIn(HDWF hdwf){
	return 0;
}


//AnalogOut sections:

// AnalogOut functions
extern "C" __declspec(dllexport) int GetChannelCount_AnalogOut(
	HDWF hdwf,
	int *pcChannel
	){
	int noerror = false;

	if(FDwfAnalogOutCount(hdwf, pcChannel))
		noerror = true;

	return noerror;
};
extern "C" __declspec(dllexport) int SetMasterNode_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	int idxMaster
	){
	return FDwfAnalogOutMasterSet(hdwf, idxChannel, idxMaster);
};
extern "C" __declspec(dllexport) int fStart_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	int fStart
	){
	return FDwfAnalogOutConfigure(hdwf, idxChannel, fStart);
};
extern "C" __declspec(dllexport) int SetConfig_AnalogOut(
	HDWF hdwf, 
	int idxChannel,
	AnalogOutNode node,
	double hzFrequency, 
	double vAmplitude, 
	double vOffset,
	double degPhase,
	FUNC func
	){
	int noerror = false;
	
	if(FDwfAnalogOutNodeFunctionSet(hdwf, idxChannel, node, func))
		noerror = true;
	if(FDwfAnalogOutNodeFrequencySet(hdwf, idxChannel, node, hzFrequency))
		noerror =  noerror && true;
	if(FDwfAnalogOutNodeAmplitudeSet(hdwf, idxChannel, node, vAmplitude))
		noerror =  noerror && true;
	if(FDwfAnalogOutNodeOffsetSet(hdwf, idxChannel, node, vOffset))
		noerror =  noerror && true;
	if(FDwfAnalogOutNodePhaseSet(hdwf, idxChannel, node, degPhase))
		noerror =  noerror && true;

	return noerror;	
};
extern "C" __declspec(dllexport) int SetChannelEnable_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	AnalogOutNode node,
	int fEnable
	){
	return FDwfAnalogOutNodeEnableSet(hdwf, idxChannel, node, fEnable);
};
extern "C" __declspec(dllexport) int SetFunctionData_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	AnalogOutNode node,
	double * rgdData, // range +/-1 normalized
	int cdData
	){
	return FDwfAnalogOutNodeDataSet(hdwf, idxChannel, node, rgdData, cdData);
};
extern "C" __declspec(dllexport) int SetSymmetry_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	AnalogOutNode node,
	double percentageSymmetry	//duty cycle
	){
	return FDwfAnalogOutNodeSymmetrySet(hdwf, idxChannel, node, percentageSymmetry);
};
extern "C" __declspec(dllexport) int SetTriggerSource_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	TRIGSRC trigsrc
	){
	return FDwfAnalogOutTriggerSourceSet(hdwf, idxChannel, trigsrc);
};
extern "C" __declspec(dllexport) int SetStates_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	double secWait,
	double secRun,	// default 0, => infinite run
	int cRepeat
	){
	int noerror = false;
	
	if(FDwfAnalogOutRunSet(hdwf, idxChannel, secRun))
		noerror = true;
	if(FDwfAnalogOutWaitSet(hdwf, idxChannel, secWait))
		noerror = noerror && true;
	if(FDwfAnalogOutRepeatSet(hdwf, idxChannel, cRepeat))
		noerror = noerror && true;

	return noerror;
};
