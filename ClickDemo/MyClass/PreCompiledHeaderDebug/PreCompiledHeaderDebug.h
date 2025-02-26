#pragma once

#ifdef _DEBUG
    #include <Windows.h>
    #define DEBUG_BREAK() do { if (IsDebuggerPresent()) { __debugbreak(); } } while(0)
#else
    #define DEBUG_BREAK() ((void)0)
#endif

#ifdef _DEBUG
#define DEBUG_EXECUTE(func) do { if (IsDebuggerPresent()) { func; } } while (0)
#else
    #define DEBUG_EXECUTE(func) ((void)0)
#endif

#define ife (errno = 0);    \
if

#define PRINT_MESSAGE(message) (std::cout << (message) << std::endl)

//NORMAL MESSAGE
#define MESSAGE_REQUEST_FILE_NAME "input file name"

//ERROR
#define ERROR_FILE_ACCESS "Error : File access"
#define ERROR_FILE_OPEN "Error : File open"
#define ERROR_END_OVERCOUNT "Error : There is more than one end"
#define ERROR_START_OVERCOUNT "Error : There is more than one start"
#define ERROR_MAPSIZE_OVERSIZE "Error : It's too big size map"
#define ERROR_MAPSIZE_SMALLSIZE "Error : It's too small size map"
#define ERROR_END_UNEXIST "Error : EndPoint does not exist"
#define ERROR_START_UNEXIST "Error : StartPoint does not exist"
#define ERROR_MAP_NOTVALID "Error : Map is not valid"
