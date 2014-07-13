#include "dwf.h"
#define DEVICE_INFO_STRING_LENGTH 32	// string length of device info calling return
#define MAX_DEVICE_NUMBER 4				//increase this number to support more than 4 device, Do not if 4 devices actually work though. 

// Device Enumeration
extern "C" __declspec(dllexport) int Enum_DevLv(ENUMFILTER enumfilter, 
	int * pnDevice,								// number of device
	char DevName[MAX_DEVICE_NUMBER][DEVICE_INFO_STRING_LENGTH],		// array of devices namess
	char SN[MAX_DEVICE_NUMBER][DEVICE_INFO_STRING_LENGTH],			// array of devices SNs
	char UserName[MAX_DEVICE_NUMBER][DEVICE_INFO_STRING_LENGTH],		// array of devices UserNames
	int isBusy[MAX_DEVICE_NUMBER],				// array of devices busy condition
	DEVID DeviceID[MAX_DEVICE_NUMBER],			// array of devices IDs
	DEVVER DeviceVersion[MAX_DEVICE_NUMBER]		// array of devices versions
);


// Device Initial/Open/Close/Reset
extern "C" __declspec(dllexport) int Open_DevLv(int idxDev, HDWF *hdwf);
extern "C" __declspec(dllexport) int Close_DevLv(HDWF hdwf);
extern "C" __declspec(dllexport) int Reset_DevLv(HDWF hdwf);
extern "C" __declspec(dllexport) int SetAutoConfig_DevLv(HDWF hdwf, int fAutoConfig);

// Trigger functions

extern "C" __declspec(dllexport) int GetInfo_AnalogIn_Trigger(HDWF hdwf, TRIGSRC * ptrigsrc);
extern "C" __declspec(dllexport) int Set_AnalogIn_Trigger(HDWF hdwf, TRIGSRC AItrigsrc, double timeout, double secPosition, double secHoldOff);

// Analog Trigger functins
extern "C" __declspec(dllexport) int Set_AnalogIn_TriggerDetector(HDWF hdwf, 
	int idxChannel,				// channel index
	TRIGCOND trigcond,			// rising or falling 
	TRIGTYPE trigtype,			// edge, pulse, transition triger
	double voltsLevel,			// trigger level
	FILTER filter,				// decimate, average
	double HystersisvoltsLEvel	// hysterisis level
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
	// int timeout,		// timeout should be handled by caller, not SDK for more flexible operation.
	int idxChannel,		// index of Channel
	double rgdSamples[],	// Array pointer to Sample buffer, must be pre-allocated
	int BufferSize		// sample record legngth
	);
extern "C" __declspec(dllexport) int Config_AnalogIn(HDWF hdwf,	//rearm
	int fReconfigure,
	int fStart
	);
// Channel independent configure
extern "C" __declspec(dllexport) int SetAcquisitionConfig_AnalogIn(HDWF hdwf,
	double hzFrquency,	// sampling rate
	int nSize,			// buffer size
	ACQMODE AcqMode,	// acqmodeSingle: single acq
						// acqmodeRecord: acquisition for length of time
	double sLength		// record length in second, for RecordLength Mode
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
extern "C" __declspec(dllexport) int GetChannelCount_AnalogOut(
	HDWF hdwf,
	int *pcChannel
	);
extern "C" __declspec(dllexport) int SetMasterNode_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	int idxMaster
	);
extern "C" __declspec(dllexport) int fStart_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	int fStart
	);
extern "C" __declspec(dllexport) int SetConfig_AnalogOut(
	HDWF hdwf, 
	int idxChannel,
	AnalogOutNode node,
	double hzFrequency, 
	double vAmplitude, 
	double vOffset,
	double degPhase,
	FUNC func
	);
extern "C" __declspec(dllexport) int SetChannelEnable_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	AnalogOutNode node,
	int fEnable
	);
extern "C" __declspec(dllexport) int SetFunctionData_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	AnalogOutNode node,
	double rgdData[16384], // range +/-1 normalized
	int cdData
	);
extern "C" __declspec(dllexport) int SetSymmetry_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	AnalogOutNode node,
	double percentageSymmetry	//duty cycle
	);
extern "C" __declspec(dllexport) int SetTriggerSource_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	TRIGSRC trigsrc
	);
extern "C" __declspec(dllexport) int SetStates_AnalogOut(
	HDWF hdwf,
	int idxChannel,
	double secWait,
	double secRun,	// default 0, => infinite run
	int cRepeat
	);
