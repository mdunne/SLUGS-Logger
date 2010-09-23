#ifndef LOGGER_DEFINITIONS_H


//#define TRUE 1
//#define FALSE 0

// SD Card port and SPI for GP710
// ========================
#ifdef PICGP710
#define SDWD _RF1
#define SDCD _RF0
#define SDCS _RB1
#define SD_SPIBUFFER SPI1BUF
#define SD_SPITRANSFER SPI1STATbits.SPIRBF 
#define SD_SPIEN SPI1STATbits.SPIEN
#define BUTTONONE !_RD6
#define BUTTONTWO !_RD7

#endif



//SD card commands
// ============================
#define RESET (0x40+0) //GO_IDLE
#define INIT (0x40+1) // SEND_OP_COND
#define SDINIT (0xC0+41) //sd card init
#define SEND_IF_COND (0x40+8)
//#define SET_BLOCKLEN (0x40+16)
//#define CRC_ON_OFF (0x40+59)
//#define STOP_TRANSMISSION	(0x40+12)	 
#define CMD55  (0x40+55) // pre for ACMD command
//#define READ_OCR (0x40+58)
#define READ_SINGLE (0x40+17) //read block of data
#define WRITE_SINGLE 24 //write a block of data
#define DATA_START 0xFE // start of a block of data
#define MEDIA_SECTOR_SIZE 		512

#define BSIZE 512
#define SECTORSIZE 512
#define DMABUFFERSIZE SECTORSIZE-2-2-1-2
#define OVERFLOWBUFFERDEPTH 12

#define HEADER_ONE '%'
#define HEADER_TWO '&'
#define FOOTER_ONE '^'
#define FOOTER_TWO '&'

#define MEM_LOCATION_ID 0
//#define CHEW_FAT_SIZE 2097152>>5
#define CHEW_FAT_SIZE 45056
#define CHEW_FAT_SIZE_IN_SECTORS 88
#define NINETY_PER_CHEW_FAT_SIZE_IN_SECTORS 79
//#define MILLISECDELAY      ((40000000/8/1000) - 5)
#endif
