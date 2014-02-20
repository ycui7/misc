/************************************************************************/
/*                                                                      */
/*    dwf.h  --    Public Interface Declarations for DWF.DLL	        */
/*                                                                      */
/************************************************************************/
/*    Author: Laszlo Attila Kovacs										*/
/*    Copyright 2013 Digilent Inc.                                      */
/************************************************************************/
/*  File Description:                                                   */
/*                                                                      */
/*    This header file contains the public interface declarations for	*/
/*    the DWF.DLL.  This interface constists of  hardware device		*/
/*	  enumeration, connection (open/close), and hardware instrument		*/
/*	  control.  This spans all 4 main instruments  supported by the		*/
/*    WaveForms system:													*/
/*			Analog In, Analog Out, Analog I/O, and Digital I/O			*/
/*																		*/
/*	  For details on using this interface, refer to:					*/
/*	  The WaveForms SDK User's Manual (available in the WaveForms SDK)	*/
/*                                                                      */
/************************************************************************/
/*  Revision History:                                                   */
/*                                                                      */
/*  08/1/2013(JPederson):  Edited for initial public release (WF 2.5)   */
/*  06/6/2009(KovacsLA) : Created                                       */
/*                                                                      */
/************************************************************************/


#pragma once

#ifndef DWFINC 
#define DWFINC TRUE

#ifndef DWFAPI

    #if defined(WIN32)
        #if defined(__cplusplus)
            #define    DWFAPI extern "C" __declspec(dllimport)
        #else
            #define    DWFAPI __declspec(dllimport)
        #endif
    #else        
        #if defined(__cplusplus)
            #define DWFAPI extern "C"
        #else
            #define DWFAPI
        #endif
    #endif
#endif

//WaveForms hardware device handle
typedef int HDWF;
const HDWF hdwfNone = 0;

// Hardware device enumeration filters
typedef int ENUMFILTER;
const ENUMFILTER enumfilterAll      = 0;
const ENUMFILTER enumfilterEExplorer= 1;
const ENUMFILTER enumfilterDiscovery= 2;

// Hardware device ID
typedef int DEVID;
const DEVID devidEExplorer  = 1;
const DEVID devidDiscovery  = 2;

// Hardware device version
typedef int DEVVER;
const DEVVER devverEExplorerC   = 2;
const DEVVER devverEExplorerE   = 4;
const DEVVER devverEExplorerF   = 5;
const DEVVER devverDiscoveryA   = 1;
const DEVVER devverDiscoveryB   = 2;
const DEVVER devverDiscoveryC   = 3;

// Trigger source:
typedef BYTE TRIGSRC;
const TRIGSRC trigsrcNone				= 0;
const TRIGSRC trigsrcPC					= 1;
const TRIGSRC trigsrcDetectorAnalogIn   = 2;
const TRIGSRC trigsrcDetectorDigitalIn  = 3;
const TRIGSRC trigsrcAnalogIn			= 4;
const TRIGSRC trigsrcDigitalIn			= 5;
const TRIGSRC trigsrcDigitalOut			= 6;
const TRIGSRC trigsrcAnalogOut1			= 7;
const TRIGSRC trigsrcAnalogOut2			= 8;
const TRIGSRC trigsrcAnalogOut3			= 9;
const TRIGSRC trigsrcAnalogOut4			= 10;
const TRIGSRC trigsrcExternal1			= 11;
const TRIGSRC trigsrcExternal2			= 12;
const TRIGSRC trigsrcExternal3			= 13;
const TRIGSRC trigsrcExternal4			= 14;

// Instrument status:
typedef BYTE STS;
const STS stsRdy		= 0;
const STS stsArm		= 1;
const STS stsDone		= 2;
const STS stsTrig		= 3;
const STS stsCfg		= 4;
const STS stsPrefill	= 5;
const STS stsNotDone	= 6;
const STS stsTrigDly	= 7;
const STS stsError		= 8;
const STS stsBusy		= 9;
const STS stsStop		= 10;

// Scope acquisition mode:
typedef int ACQMODE;
const ACQMODE acqmodeSingle		= 0;
const ACQMODE acqmodeScanShift  = 1;
const ACQMODE acqmodeScanScreen = 2;
const ACQMODE acqmodeRecord		= 3;

// Scope acquisition filter:
typedef int FILTER;
const FILTER filterDecimate = 0;
const FILTER filterAverage  = 1;
const FILTER filterMinMax   = 2;

// Scope trigger type:
typedef int TRIGTYPE;
const TRIGTYPE trigtypeEdge         = 0;
const TRIGTYPE trigtypePulse        = 1;
const TRIGTYPE trigtypeTransition   = 2;

// Scope trigger type:
typedef int TRIGCOND;
const TRIGCOND trigcondRisingPositive   = 0;
const TRIGCOND trigcondFallingNegative  = 1;

// Scope trigger type:
typedef int TRIGLEN;
const TRIGLEN triglenLess       = 0;
const TRIGLEN triglenTimeout    = 1;
const TRIGLEN triglenMore       = 2;

// Error Codes for DWF Public API:
typedef int DWFERC;                           
const   DWFERC dwfercNoErc                  = 0;		//  No error occurred
const   DWFERC dwfercUnknownError           = 1;		//  API waiting on pending API timed out
const   DWFERC dwfercApiLockTimeout         = 2;		//  API waiting on pending API timed out
const   DWFERC dwfercAlreadyOpened          = 3;		//  Device already opened
const   DWFERC dwfercNotSupported           = 4;		//  Device not supported
const   DWFERC dwfercInvalidParameter0      = 0x10;		//  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter1      = 0x11;		//  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter2      = 0x12;		//  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter3      = 0x13;		//  Invalid parameter sent in API call

// Generated signal function type:
typedef BYTE FUNC;
const FUNC funcDC       = 0;
const FUNC funcSine     = 1;
const FUNC funcSquare   = 2;
const FUNC funcTriangle = 3;
const FUNC funcRampUp   = 4;
const FUNC funcRampDown = 5;
const FUNC funcNoise    = 6;
const FUNC funcCustom   = 30;
const FUNC funcPlay     = 31;

// Analog IO channel node type:
typedef BYTE ANALOGIO;
const ANALOGIO analogioEnable		= 1;
const ANALOGIO analogioVoltage		= 2;
const ANALOGIO analogioCurrent		= 3;
const ANALOGIO analogioPower		= 4;
const ANALOGIO analogioTemperature	= 5;

// Macro used to verify if bit is 1 or 0 in given bit field
#define IsBitSet(fs, bit) ((fs & (1<<bit)) != 0)

// Error and version APIs:
DWFAPI BOOL FDwfGetLastError(DWFERC * pdwferc);
DWFAPI BOOL FDwfGetLastErrorMsg(char szError[512]);
DWFAPI BOOL FDwfGetVersion(char szVersion[32]);  // Returns DLL version, for instance: "2.4.3"


// DEVICE MANAGMENT FUNCTIONS
// Enumeration:
DWFAPI BOOL FDwfEnum(ENUMFILTER enumfilter, int * pcDeviceFound);
DWFAPI BOOL FDwfEnumDeviceType(int idxDevice, DEVID* pDeviceId, DEVVER* pDeviceRevision);
DWFAPI BOOL FDwfEnumDeviceIsOpened(int idxDevice, BOOL* pfIsUsed);
DWFAPI BOOL FDwfEnumUserName(int idxDevice, char szUserName[32]);
DWFAPI BOOL FDwfEnumDeviceName(int idxDevice, char szDeviceName[32]);
DWFAPI BOOL FDwfEnumSN(int idxDevice, char szSN[32]);

// Open/Close:
DWFAPI BOOL FDwfDeviceOpen(int idxDevice, HDWF *phdwf);
DWFAPI BOOL FDwfDeviceClose(HDWF hdwf);
DWFAPI BOOL FDwfDeviceCloseAll();
DWFAPI BOOL FDwfDeviceAutoConfigureSet(HDWF hdwf, BOOL fConfigureWhenSet);
DWFAPI BOOL FDwfDeviceAutoConfigureGet(HDWF hdwf, BOOL* pfConfigureWhenSet);
DWFAPI BOOL FDwfDeviceReset(HDWF hdwf);
DWFAPI BOOL FDwfDeviceTriggerInfo(HDWF hdwf, int* pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfDeviceTriggerSet(HDWF hdwf, int idxPin, TRIGSRC trigsrc);
DWFAPI BOOL FDwfDeviceTriggerGet(HDWF hdwf, int idxPin, TRIGSRC* ptrigsrc);
DWFAPI BOOL FDwfDeviceTriggerPC(HDWF hdwf);



// ANALOG IN INSTRUMENT FUNCTIONS
// Control and status: 
DWFAPI BOOL FDwfAnalogInReset(HDWF hdwf);
DWFAPI BOOL FDwfAnalogInConfigure(HDWF hdwf, BOOL fReconfigure, BOOL fStart);
DWFAPI BOOL FDwfAnalogInStatus(HDWF hdwf, BOOL fReadData, STS* psts);
DWFAPI BOOL FDwfAnalogInStatusSamplesLeft(HDWF hdwf, int* pcSamplesLeft);
DWFAPI BOOL FDwfAnalogInStatusSamplesValid(HDWF hdwf, int* pcSamplesValid);
DWFAPI BOOL FDwfAnalogInStatusIndexWrite(HDWF hdwf, int* pidxWrite);
DWFAPI BOOL FDwfAnalogInStatusAutoTriggered(HDWF hdwf, BOOL* pfAuto);
DWFAPI BOOL FDwfAnalogInStatusData(HDWF hdwf, int idxChannel, double* rgdVoltData, int cdData);
DWFAPI BOOL FDwfAnalogInStatusSample(HDWF hdwf, int idxChannel, double* pdVoltSample);

DWFAPI BOOL FDwfAnalogInStatusRecord(HDWF hdwf, int* pcdDataAvailable, int* pcdDataLost, int* pcdDataCorrupt);
DWFAPI BOOL FDwfAnalogInRecordLengthSet(HDWF hdwf, double sLegth);
DWFAPI BOOL FDwfAnalogInRecordLengthGet(HDWF hdwf, double* psLegth);

// Acquistion configuration:
DWFAPI BOOL FDwfAnalogInFrequencyInfo(HDWF hdwf, double* phzMin, double* phzMax);
DWFAPI BOOL FDwfAnalogInFrequencySet(HDWF hdwf, double hzFrequency);
DWFAPI BOOL FDwfAnalogInFrequencyGet(HDWF hdwf, double* phzFrequency);

DWFAPI BOOL FDwfAnalogInBitsInfo(HDWF hdwf, int* pnBits); // Returns the number of ADC bits 

DWFAPI BOOL FDwfAnalogInBufferSizeInfo(HDWF hdwf, int* pnSizeMin, int* pnSizeMax);
DWFAPI BOOL FDwfAnalogInBufferSizeSet(HDWF hdwf, int nSize);
DWFAPI BOOL FDwfAnalogInBufferSizeGet(HDWF hdwf, int* pnSize);

DWFAPI BOOL FDwfAnalogInAcquisitionModeInfo(HDWF hdwf, int* pfsacqmode); // use IsBitSet
DWFAPI BOOL FDwfAnalogInAcquisitionModeSet(HDWF hdwf, ACQMODE acqmode);
DWFAPI BOOL FDwfAnalogInAcquisitionModeGet(HDWF hdwf, ACQMODE* pacqmode);

// Channel configuration:
DWFAPI BOOL FDwfAnalogInChannelCount(HDWF hdwf, int* pcChannel);
DWFAPI BOOL FDwfAnalogInChannelEnableSet(HDWF hdwf, int idxChannel, BOOL fEnable);
DWFAPI BOOL FDwfAnalogInChannelEnableGet(HDWF hdwf, int idxChannel, BOOL *pfEnable);
DWFAPI BOOL FDwfAnalogInChannelFilterInfo(HDWF hdwf, int* pfsfilter); // use IsBitSet
DWFAPI BOOL FDwfAnalogInChannelFilterSet(HDWF hdwf, int idxChannel, FILTER filter);
DWFAPI BOOL FDwfAnalogInChannelFilterGet(HDWF hdwf, int idxChannel, FILTER* pfilter);
DWFAPI BOOL FDwfAnalogInChannelRangeInfo(HDWF hdwf, double* pvoltsMin, double* pvoltsMax, double* pnSteps);
DWFAPI BOOL FDwfAnalogInChannelRangeSteps(HDWF hdwf, double rgVoltsStep[32], int* pnSteps);
DWFAPI BOOL FDwfAnalogInChannelRangeSet(HDWF hdwf, int idxChannel, double voltsRange);
DWFAPI BOOL FDwfAnalogInChannelRangeGet(HDWF hdwf, int idxChannel, double* pvoltsRange);
DWFAPI BOOL FDwfAnalogInChannelOffsetInfo(HDWF hdwf, double* pvoltsMin, double* pvoltsMax, double* pnSteps);
DWFAPI BOOL FDwfAnalogInChannelOffsetSet(HDWF hdwf, int idxChannel, double voltOffset);
DWFAPI BOOL FDwfAnalogInChannelOffsetGet(HDWF hdwf, int idxChannel, double* pvoltOffset);

// Trigger configuration:
DWFAPI BOOL FDwfAnalogInTriggerSourceInfo(HDWF hdwf, int* pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI BOOL FDwfAnalogInTriggerSourceGet(HDWF hdwf, TRIGSRC* ptrigsrc);

DWFAPI BOOL FDwfAnalogInTriggerPositionInfo(HDWF hdwf, double* psecMin, double* psecMax, double* pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerPositionSet(HDWF hdwf, double secPosition);
DWFAPI BOOL FDwfAnalogInTriggerPositionGet(HDWF hdwf, double* psecPosition);

DWFAPI BOOL FDwfAnalogInTriggerAutoTimeoutInfo(HDWF hdwf, double* psecMin, double* psecMax, double* pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerAutoTimeoutSet(HDWF hdwf, double secTimeout);
DWFAPI BOOL FDwfAnalogInTriggerAutoTimeoutGet(HDWF hdwf, double* psecTimeout);

DWFAPI BOOL FDwfAnalogInTriggerHoldOffInfo(HDWF hdwf, double* psecMin, double* psecMax, double* pnStep);
DWFAPI BOOL FDwfAnalogInTriggerHoldOffSet(HDWF hdwf, double secHoldOff);
DWFAPI BOOL FDwfAnalogInTriggerHoldOffGet(HDWF hdwf, double* psecHoldOff);

DWFAPI BOOL FDwfAnalogInTriggerTypeInfo(HDWF hdwf, int* pfstrigtype); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerTypeSet(HDWF hdwf, TRIGTYPE trigtype);
DWFAPI BOOL FDwfAnalogInTriggerTypeGet(HDWF hdwf, TRIGTYPE* ptrigtype);

DWFAPI BOOL FDwfAnalogInTriggerChannelInfo(HDWF hdwf, int* pidxMin, int* pidxMax);
DWFAPI BOOL FDwfAnalogInTriggerChannelSet(HDWF hdwf, int idxChannel);
DWFAPI BOOL FDwfAnalogInTriggerChannelGet(HDWF hdwf, int* pidxChannel);

DWFAPI BOOL FDwfAnalogInTriggerFilterInfo(HDWF hdwf, int* pfsfilter); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerFilterSet(HDWF hdwf, FILTER filter);
DWFAPI BOOL FDwfAnalogInTriggerFilterGet(HDWF hdwf, FILTER* pfilter);

DWFAPI BOOL FDwfAnalogInTriggerLevelInfo(HDWF hdwf, double* pvoltsMin, double* pvoltsMax, double* pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerLevelSet(HDWF hdwf, double voltsLevel);
DWFAPI BOOL FDwfAnalogInTriggerLevelGet(HDWF hdwf, double* pvoltsLevel);

DWFAPI BOOL FDwfAnalogInTriggerHysteresisInfo(HDWF hdwf, double* pvoltsMin, double* pvoltsMax, double* pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerHysteresisSet(HDWF hdwf, double voltsLevel);
DWFAPI BOOL FDwfAnalogInTriggerHysteresisGet(HDWF hdwf, double* pvoltsHysteresis);

DWFAPI BOOL FDwfAnalogInTriggerConditionInfo(HDWF hdwf, int* pfstrigcond); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerConditionSet(HDWF hdwf, TRIGCOND trigcond);
DWFAPI BOOL FDwfAnalogInTriggerConditionGet(HDWF hdwf, TRIGCOND* ptrigcond);

DWFAPI BOOL FDwfAnalogInTriggerLengthInfo(HDWF hdwf, double* psecMin, double* psecMax, double* pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerLengthSet(HDWF hdwf, double secLength);
DWFAPI BOOL FDwfAnalogInTriggerLengthGet(HDWF hdwf, double* psecLength);

DWFAPI BOOL FDwfAnalogInTriggerLengthConditionInfo(HDWF hdwf, int* pfstriglen); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerLengthConditionSet(HDWF hdwf, TRIGLEN triglen);
DWFAPI BOOL FDwfAnalogInTriggerLengthConditionGet(HDWF hdwf, TRIGLEN* ptriglen);



// ANALOG OUT INSTRUMENT FUNCTIONS
// Control:
DWFAPI BOOL FDwfAnalogOutReset(HDWF hdwf, int idxChannel);
DWFAPI BOOL FDwfAnalogOutConfigure(HDWF hdwf, int idxChannel, BOOL fStart);
DWFAPI BOOL FDwfAnalogOutStatus(HDWF hdwf, int idxChannel, STS* psts);
DWFAPI BOOL FDwfAnalogOutPlayStatus(HDWF hdwf, int idxChannel, int* cdDataFree, int *cdDataLost, int *cdDataCorrupted);
DWFAPI BOOL FDwfAnalogOutPlayData(HDWF hdwf, int idxChannel, double* rgdData, int cdData);

// Configuration:
DWFAPI BOOL FDwfAnalogOutCount(HDWF hdwf, int* pcChannel);
DWFAPI BOOL FDwfAnalogOutEnableSet(HDWF hdwf, int idxChannel, BOOL fEnable);
DWFAPI BOOL FDwfAnalogOutEnableGet(HDWF hdwf, int idxChannel, BOOL* pfEnable);

DWFAPI BOOL FDwfAnalogOutTriggerSourceInfo(HDWF hdwf, int idxChannel, int* pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfAnalogOutTriggerSourceSet(HDWF hdwf, int idxChannel, TRIGSRC trigsrc);
DWFAPI BOOL FDwfAnalogOutTriggerSourceGet(HDWF hdwf, int idxChannel, TRIGSRC* ptrigsrc);

DWFAPI BOOL FDwfAnalogOutRunInfo(HDWF hdwf, int idxChannel, double* psecMin, double* psecMax);
DWFAPI BOOL FDwfAnalogOutRunSet(HDWF hdwf, int idxChannel, double secRun);
DWFAPI BOOL FDwfAnalogOutRunGet(HDWF hdwf, int idxChannel, double* psecRun);
DWFAPI BOOL FDwfAnalogOutRunStatus(HDWF hdwf, int idxChannel, double* psecRun);

DWFAPI BOOL FDwfAnalogOutWaitInfo(HDWF hdwf, int idxChannel, double* psecMin, double* psecMax);
DWFAPI BOOL FDwfAnalogOutWaitSet(HDWF hdwf, int idxChannel, double secWait);
DWFAPI BOOL FDwfAnalogOutWaitGet(HDWF hdwf, int idxChannel, double* psecWait);

DWFAPI BOOL FDwfAnalogOutRepeatInfo(HDWF hdwf, int idxChannel, int* pnMin, int* pnMax);
DWFAPI BOOL FDwfAnalogOutRepeatSet(HDWF hdwf, int idxChannel, int cRepeat);
DWFAPI BOOL FDwfAnalogOutRepeatGet(HDWF hdwf, int idxChannel, int* pcRepeat);
DWFAPI BOOL FDwfAnalogOutRepeatStatus(HDWF hdwf, int idxChannel, int* pcRepeat);

DWFAPI BOOL FDwfAnalogOutRepeatTriggerSet(HDWF hdwf, int idxChannel, BOOL fRepeatTrigger);
DWFAPI BOOL FDwfAnalogOutRepeatTriggerGet(HDWF hdwf, int idxChannel, BOOL* pfRepeatTrigger);

DWFAPI BOOL FDwfAnalogOutFunctionInfo(HDWF hdwf, int idxChannel, int* pfsfunc); // use IsBitSet
DWFAPI BOOL FDwfAnalogOutFunctionSet(HDWF hdwf, int idxChannel, FUNC func);
DWFAPI BOOL FDwfAnalogOutFunctionGet(HDWF hdwf, int idxChannel, FUNC* pfunc);

DWFAPI BOOL FDwfAnalogOutFrequencyInfo(HDWF hdwf, int idxChannel, double* phzMin, double* phzMax);
DWFAPI BOOL FDwfAnalogOutFrequencySet(HDWF hdwf, int idxChannel, double hzFrequency);
DWFAPI BOOL FDwfAnalogOutFrequencyGet(HDWF hdwf, int idxChannel, double* phzFrequency);

DWFAPI BOOL FDwfAnalogOutAmplitudeInfo(HDWF hdwf, int idxChannel, double* pvoltsMin, double* pvoltsMax);
DWFAPI BOOL FDwfAnalogOutAmplitudeSet(HDWF hdwf, int idxChannel, double voltsAmplitude);
DWFAPI BOOL FDwfAnalogOutAmplitudeGet(HDWF hdwf, int idxChannel, double* pvoltsAmplitude);

DWFAPI BOOL FDwfAnalogOutOffsetInfo(HDWF hdwf, int idxChannel, double* pvoltsMin, double* pvoltsMax);
DWFAPI BOOL FDwfAnalogOutOffsetSet(HDWF hdwf, int idxChannel, double voltsOffset);
DWFAPI BOOL FDwfAnalogOutOffsetGet(HDWF hdwf, int idxChannel, double* pvoltsOffset);

DWFAPI BOOL FDwfAnalogOutSymmetryInfo(HDWF hdwf, int idxChannel, double* ppercentageMin, double* ppercentageMax);
DWFAPI BOOL FDwfAnalogOutSymmetrySet(HDWF hdwf, int idxChannel, double percentageSymmetry);
DWFAPI BOOL FDwfAnalogOutSymmetryGet(HDWF hdwf, int idxChannel, double* ppercentageSymmetry);

DWFAPI BOOL FDwfAnalogOutPhaseInfo(HDWF hdwf, int idxChannel, double* pdegreeMin, double* pdegreeMax);
DWFAPI BOOL FDwfAnalogOutPhaseSet(HDWF hdwf, int idxChannel, double degreePhase);
DWFAPI BOOL FDwfAnalogOutPhaseGet(HDWF hdwf, int idxChannel, double* pdegreePhase);

DWFAPI BOOL FDwfAnalogOutDataInfo(HDWF hdwf, int idxChannel, int* pnSamplesMin, int* pnSamplesMax);
DWFAPI BOOL FDwfAnalogOutDataSet(HDWF hdwf, int idxChannel, double* rgdData, int cdData);



// ANALOG IO INSTRUMENT FUNCTIONS
// Control:
DWFAPI BOOL FDwfAnalogIOReset(HDWF hdwf);
DWFAPI BOOL FDwfAnalogIOConfigure(HDWF hdwf);
DWFAPI BOOL FDwfAnalogIOStatus(HDWF hdwf);

// Configure:
DWFAPI BOOL FDwfAnalogIOEnableInfo(HDWF hdwf, BOOL* pfSet, BOOL* pfStatus);
DWFAPI BOOL FDwfAnalogIOEnableSet(HDWF hdwf, BOOL fMasterEnable);
DWFAPI BOOL FDwfAnalogIOEnableGet(HDWF hdwf, BOOL* pfMasterEnable);
DWFAPI BOOL FDwfAnalogIOEnableStatus(HDWF hdwf, BOOL* pfMasterEnable);
DWFAPI BOOL FDwfAnalogIOChannelCount(HDWF hdwf, int* pnChannel);
DWFAPI BOOL FDwfAnalogIOChannelName(HDWF hdwf, int idxChannel, char szName[32], char szLabel[16]);
DWFAPI BOOL FDwfAnalogIOChannelInfo(HDWF hdwf, int idxChannel, int *pnNodes);
DWFAPI BOOL FDwfAnalogIOChannelNodeName(HDWF hdwf, int idxChannel, int idxNode, char szNodeName[32], char szNodeUnits[16]);
DWFAPI BOOL FDwfAnalogIOChannelNodeInfo(HDWF hdwf, int idxChannel, int idxNode, ANALOGIO* panalogio);
DWFAPI BOOL FDwfAnalogIOChannelNodeSetInfo(HDWF hdwf, int idxChannel, int idxNode, double* pmin, double* pmax, int* pnSteps);
DWFAPI BOOL FDwfAnalogIOChannelNodeSet(HDWF hdwf, int idxChannel, int idxNode, double value);
DWFAPI BOOL FDwfAnalogIOChannelNodeGet(HDWF hdwf, int idxChannel, int idxNode, double* pvalue);
DWFAPI BOOL FDwfAnalogIOChannelNodeStatusInfo(HDWF hdwf, int idxChannel, int idxNode, double* pmin, double* pmax, int* pnSteps);
DWFAPI BOOL FDwfAnalogIOChannelNodeStatus(HDWF hdwf, int idxChannel, int idxNode, double* pvalue);



// DIGITAL IO INSTRUMENT FUNCTIONS
// Control:
DWFAPI BOOL FDwfDigitalIOReset(HDWF hdwf);
DWFAPI BOOL FDwfDigitalIOConfigure(HDWF hdwf);
DWFAPI BOOL FDwfDigitalIOStatus(HDWF hdwf);

// Configure:
DWFAPI BOOL FDwfDigitalIOOutputEnableInfo(HDWF hdwf, unsigned int* pfsOutputEnableMask);
DWFAPI BOOL FDwfDigitalIOOutputEnableSet(HDWF hdwf, unsigned int fsOutputEnable);
DWFAPI BOOL FDwfDigitalIOOutputEnableGet(HDWF hdwf, unsigned int* pfsOutputEnable);
DWFAPI BOOL FDwfDigitalIOOutputInfo(HDWF hdwf, unsigned int* pfsOutputMask);
DWFAPI BOOL FDwfDigitalIOOutputSet(HDWF hdwf, unsigned int fsOutput);
DWFAPI BOOL FDwfDigitalIOOutputGet(HDWF hdwf, unsigned int* pfsOutput);
DWFAPI BOOL FDwfDigitalIOInputInfo(HDWF hdwf, unsigned int* pfsInputMask);
DWFAPI BOOL FDwfDigitalIOInputStatus(HDWF hdwf, unsigned int* pfsInput);

// OBSOLATE, do not use them:
DWFAPI BOOL FDwfEnumAnalogInChannels(int idxDevice, int* pnChannels);
DWFAPI BOOL FDwfEnumAnalogInBufferSize(int idxDevice, int* pnBufferSize);
DWFAPI BOOL FDwfEnumAnalogInBits(int idxDevice, int* pnBits);
DWFAPI BOOL FDwfEnumAnalogInFrequency(int idxDevice, double* phzFrequency);

#endif
