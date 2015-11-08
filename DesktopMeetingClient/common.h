#ifndef SETTINGS_H
#define SETTINGS_H
#define MAX_SEND_SIZE  32768        // 每次通过Socket发送的最大字节数
#define START_CODE  "START"
#define START_CODE_LENGTH 5
#define END_CODE   "END"
#define END_CODE_LENGTH 3
static const char* MULTICASTADDRESS[]=
{
    "224.100.1.100",
    "224.100.2.100",
    "224.100.3.100",
    "224.100.4.100",
    "224.100.5.100",
    "224.100.6.100",
    "224.100.7.100",
    "224.100.8.100",
    "224.100.9.100",
};
#endif // SETTINGS_H
