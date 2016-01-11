// config.h
#ifndef CONFIG_H
#define CONFIG_H
// configuration of this application
const char * P_OUT = "/media/xiang/DATA/Downloads/PR_DATA/AAI/OUT_DATA/";
const char * F_OFFSET = "offset.txt";
const char * F_INVERTED_LIST = "inverted_list.txt";
const char * F_OUTPUT = "output.txt";
const char * F_NAME_LIST = "name_list.txt";

// path of raw data
const char * P_RAW = "/media/xiang/DATA/Downloads/PR_DATA/AAI/RAW_DATA/";
const char * F_HUM = "HUM.fa";
const char * F_VIR = "VIR.fa";
const char * F_ALL = "ALL.fa";
const char * F_INF = "INF.fa";

const char * F_A1 = "A1.fq";
const char * F_A2 = "A2.fq";
const char * F_B1 = "B1.fq";
const char * F_B2 = "B2.fq";
const char * F_C = "C.fq";
const char * F_D = "D.fq";
const char * F_E = "E.fq";

#ifndef _DEBUG_
#define _DEBUG_
#endif

// indexing settings
const int CARD_SIZE = 10;
const char A = 'A';
const char C = 'C';
const char G = 'G';
const char T = 'T';
// end of chromsome
const int END = -1;
const int MIN_MATCH = 5;

// cache settings for inverted list
const int IL_CACHE_SIZE = 50000000;




#endif

