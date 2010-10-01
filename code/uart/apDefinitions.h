	/* ==================================================
This is the definition file for the the UCSC AP code
it creates all the common defines, unions, enumerations
and data types.

 Code by: Mariano I. Lizarraga
 First Revision: Aug 18 2008 @ 17:42
 ====================================================*/
#ifndef _APDEFINITIONS_H_
#define _APDEFINITIONS_H_

#ifdef __cplusplus
       extern "C"{
#endif

#define DATA_LOGGER

// =========== Global Definitions ==========

// Circular Buffer Size
// ===================
#ifdef __cplusplus
       #define BSIZE			1024
#else
       #define BSIZE			512
#endif

// GPS Checksum Messages
// =====================
#define GGACS			86
#define RMCCS			75

// GPS Header IDs
// ==============
#define GGAID			1
#define RMCID			2
#define UNKID			254

// GPS Circular Buffers
// ====================
#define MSIZE			150
#define CSIZE			26 //[newBytes payload remaingBytes]  (comms buffer out of readGPS)

// Data Logger Values
// ================
#define LOGSEND					8
#define MAXSEND					103
#define MAXLOGSEND				56

#ifdef __cplusplus
       #define MAXLOGLEN		500
#else
       #define MAXLOGLEN		99
#endif

// Define log raw data at 100 hz. Comment out to have
// XYZ data come at 100 Hz instead. COMMENT not Change to 0 (using #ifdef)
//#define LOGRAW100	1



// Message Protocol Lengths and IDs
// ================================

// SENSOR MCU
// ==========
#define GPS_START 		0
#define GPSMSG_ID		1
#define GPSMSG_LEN		27 

#define LOAD_START		27
#define LOADMSG_ID		2
#define LOADMSG_LEN		4

#define RAW_START 		31
#define RAWMSG_ID		3
#define RAWMSG_LEN		26

#define ATT_START		49
#define ATTMSG_ID		4
#define ATTMSG_LEN		26

#define XYZ_START		75
#define XYZMSG_ID		11
#define XYZMSG_LEN		24

#define DYN_START		99
#define DYNMSG_ID		5
#define DYNMSG_LEN		10

#define BIA_START		109
#define BIAMSG_ID		6
#define BIAMSG_LEN		24

#define DIA_START		133
#define DIAMSG_ID		7
#define DIAMSG_LEN		18

#define HIL_START		151

#define PIL_START		152
#define PILMSG_ID		9
#define PILMSG_LEN		10



// CONTROL MCU
// ===========
#define AKNMSG_ID		105
#define AKNMSG_LEN		6

#define PWMMSG_ID		100
#define PWMMSG_LEN		20 

#define CALMSG_ID		102
#define CALMSG_LEN		17

#define APSMSG_ID		101
#define APSMSG_LEN		20


// GROUND STATION
// ==============
// NOTE: for HIL simulator the GS uses the same IDs for the 
// simulated sensor readings, i.e. GPS, Raw, Air Data, etc. Than
// for the actual readings.

#define FILMSG_ID		205
#define FILMSG_LEN		1

#define PIDMSG_ID		202
#define PIDMSG_LEN		13

#define QUEMSG_ID		204
#define QUEMSG_LEN		10

#define WPSMSG_ID		201
#define WPSMSG_LEN		16

#define COMMSG_ID		206
#define COMMSG_LEN		10

#define CHSMSG_ID		207
#define CHSMSG_LEN		9


// Identifier values for messages that have a type ID
// ==================================================

// Calibration and Query type IDs
#define PIDTYPE_ID		1
#define WPSTYPE_ID		2
#define PASTYPE_ID		3
#define COMTYPE_ID		4

// Control Types
#define CTRL_TYPE_MANUAL	1		// Pilot in full control of aircraft
#define CTRL_TYPE_AP_COMM	2		// Low level commands: airspeed, height and turnrate
#define CTRL_TYPE_AP_WP		3		// Waypoint following
#define CTRL_TYPE_PASS		4		// Passthrough the commands from the pilot console
#define CTRL_TYPE_SEL_PIL	5		// Pass some from the pilot and some from the AP
#define CTRL_TYPE_SEL_AP	6

#define PIL_FAILSAFE		6000	// IC direct reading from the pilot console when failsafe is
									// is turned ON i.e. the pilot is in control. 

// Commands to AP ids
#define COMM_TYPE_HEIGHT	1
#define	COMM_TYPE_TURNRATE	2
#define	COMM_TYPE_AIRSPEED	3
#define COMM_TYPE_GOTO_WP	4



// ERROR MESSAGES
// ==============

// PID EEPROM Error Messages
#define PIDEEP_WRITE_FAIL	11
#define PIDEEP_PAGE_EXP		12
#define PIDEEP_MEMORY_CORR	13

// WP EEPROM Error Messages
#define WPSEEP_WRITE_FAIL	21
#define WPSEEP_PAGE_EXP		22
#define WPSEEP_MEMORY_CORR	23

// EEPROM Emulation Address Offsets
// ================================
#define PID_OFFSET		0
#define WPS_OFFSET		60

// Communication Protocol Merging Offsets
// ======================================
#define GSMSG_IDX		99
#define AKMSG_IDX		202


// Standard characters used in the parsing of messages
// ===================================================
#define DOLLAR			36
#define STAR			42
#define CR				13
#define LF				10
#define AT				64

// Interprocessor Communication
// ============================
#define BEGINSPI		0xFFFF
#define ENDSPI			0xBEEF
#define SPIBUFSIZE		46

// Standard Units
// ==============
#define KTS2MPS 		0.514444444
#define PI              3.141592653589793
#define DEG2RAD			0.017453292519943
#define RAD2DEG			57.29577951308232

// Periphereal Configurations
// ==========================
#define APFCY			40000000

	
#define GPSBAUDF		19200
#define GPSBAUDI		4800
#define UCSCAP_UBRGF 	129
#define UCSCAP_UBRGI 	520

#define LOGBAUD			115200
#define LOG_UBRG		21

#define LOGMAT_BAUD		57600
#define LOGOMAT_UBRG	42


// ifdef switches for debugging and conditional inclusion
// ======================================================
#define __IN_DSPIC__ 	1 // switch for use in PC

#if __IN_DSPIC__
	#ifdef DEBUG
		#undef DEBUG
	#endif	
#else
	#define DEBUG 1
#endif

// Uncomment if there is no magentometers
//#define NO_MAGNETO 

// Uncomment to allow full gyro calibration
#define DO_FULL_CALL


// ============= Unions Used for Data Transmission ====
//Type definitions for standard unions used in sending
// and receiving data



#ifdef __cplusplus
      }
#endif

#endif /* _APDEFINITIONS_H_ */
