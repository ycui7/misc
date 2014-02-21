// AnalogDiscSDKLv.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dwf.h"
// #include <stdio.h>


// Device Enumeration
extern "C" __declspec(dllexport) int Enum_DevLv(ENUMFILTER enumfilter, int * pnDevice);

// Device Initial/Open/Close/Reset
extern "C" __declspec(dllexport) int Open_DevLv(int idxDev, HDWF *hdwf);
extern "C" __declspec(dllexport) int Close_DevLv(HDWF hdwf);
extern "C" __declspec(dllexport) int Reset_DevLv(HDWF hdwf);
extern "C" __declspec(dllexport) int SetAutoConfig_DevLv(HDWF hdwf, int fAutoConfig);

// Trigger functions

extern "C" __declspec(dllexport) int GetInfo_Trigger(HDWF hdwf, int* pfstrigsrc);
extern "C" __declspec(dllexport) int Set_Trigger(HDWF hdwf, int idxPin, TRIGSRC trigsrc);

// Analog Trigger functins
extern "C" __declspec(dllexport) int Set_Analog_Trigger(HDWF hdwf, 
	int idxchannel,				// channel index
	double position,			// trigger delay
	double timeout,
	double holdoff,				// trigger holdoff
	TRIGTYPE type,				// edge, pulse, transition triger
	FILTER filter,				// decimate, average
	double voltsLevel,			// trigger level
	double HystersisvoltsLEvel,	// hysterisis level
	TRIGCOND trigcond			// rising or falling 
	);
extern "C" __declspec(dllexport) int GetConfig_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int GetStatus_Trigger(HDWF hdwf);

/*
extern "C" __declspec(dllexport) int GetSource_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int SetSource_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int GetPosition_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int SetPosition_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int SetTimeout_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int GetTimeout_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int SetHoldOff_Trigger(HDWF hdwf);
extern "C" __declspec(dllexport) int GetHoldOff_Trigger(HDWF hdwf);
*/


// AnalogIn functions
//Status
extern "C" __declspec(dllexport) int GetStatus_AnalogIn(HDWF hdwf,
	int fReadData,
	STS* psts
	);
extern "C" __declspec(dllexport) int GetData_AnalogIn(HDWF hdwf, 
	//int timeout,		// timeout 
	int idxChannel,		// index of Channel
	double rgdSamples[],	// Array pointer to Sample buffer, must be pre-allocated
	int BufferSize	// sample record legngth
	);
extern "C" __declspec(dllexport) int Config_AnalogIn(HDWF hdwf,	//rearm
	int fReconfigure,
	int fStart
	);
// Channel independent configure
extern "C" __declspec(dllexport) int SetAcquisitionConfig_AnalogIn(HDWF hdwf,
	double hzFrquency,	// sampling rate
	int nSize,			// buffer size
	ACQMODE AcqMode		// acqmodeSingle: single acq
						// acqmodeRecord: acquisition for length of time
//	double RecordLength	// dupliate of buffersize, commmented.	
	);
extern "C" __declspec(dllexport) int GetAcquisitionsConfig_AnalogIn(HDWF hdwf);

// Channel dependent configure
extern "C" __declspec(dllexport) int SetChannelsConfig_AnalogIn(HDWF hdwf, 
	int indexCh,	// channel info
	int Enable,		// enable Channel
	double voltsRange,		// DAQ Range
	FILTER Filter,	// filter: decimate, average, minmax
	double voltOffset	//Offset, aka, vertical position
	);
extern "C" __declspec(dllexport) int GetChannelsConfig_AnalogIn(HDWF hdwf);
/*
extern "C" __declspec(dllexport) int SetChannelEnable_AnalogIn(HDWF hdwf, int indexCh, int fEnable);
extern "C" __declspec(dllexport) int SetFilter_AnalogIn(HDWF hdwf, int indexCh, FILTER filter);
extern "C" __declspec(dllexport) int SetRange_AnalogIn(HDWF hdwf, int indexCh, double voltsRange);
*/


// AnalogOut functions
extern "C" __declspec(dllexport) int SetDataAnalogOut(HDWF hdwf);


/********************************************************
 *  Wrapper start here                                  *
 ********************************************************/

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
	FDwfAnalogInStatus(hdwf, true, psts);
	// STS: Byte 
}

extern "C" __declspec(dllexport) int GetData_AnalogIn(HDWF hdwf, /*int timeout,*/int idxChannel, double rgdSamples[], int BufferSize){
	return FDwfAnalogInStatusData (hdwf, idxChannel, rgdSamples, BufferSize);
}

extern "C" __declspec(dllexport) int Config_AnalogIn(HDWF hdwf,	//rearm
	int fReconfigure,
	int fStart
	);
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
extern "C" __declspec(dllexport) int SetChannelsConfig_AnalogIn(HDWF hdwf, 
	int indexCh,	// channel info
	int Enable,		// enable Channel
	double voltsRange,		// DAQ Range
	FILTER Filter,	// filter: decimate, average, minmax
	double voltOffset	//Offset, aka, vertical position
	);
extern "C" __declspec(dllexport) int GetChannelsConfig_AnalogIn(HDWF hdwf);