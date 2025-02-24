#pragma once

#ifdef _DEBUG
    #include <Windows.h>
    #define DEBUG_BREAK() do { if (IsDebuggerPresent()) { __debugbreak(); } } while(0)
#else
    #define DEBUG_BREAK() ((void)0)
#endif

#ifdef _DEBUG
    #define DEBUG_EXECUTE(func) (func)
#else
    #define DEBUG_EXECUTE(func) ((void)0)
#endif

#define PRINT_MESSAGE(message) (std::cout << (message) << std::endl)

//NORMAL MESSAGE
#define MESSAGE_REQUEST_FILE_NAME "input file name"

//ERROR
#define ERROR_FILE_ACCESS "Error : File access"
#define ERROR_FILE_OPEN "Error : File open"