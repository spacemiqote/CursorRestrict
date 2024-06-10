#define VERSION_YEAR        2024
#define VERSION_MONTH       06
#define VERSION_DAY         10
#define VERSION_UNSAFE      0

#define VER_COPYRIGHT_STR       "Open Source Software"
#define VER_FILEDESCRIPTION_STR "A program to restrict your cursor from moving out of the game window.(Shift+F11 toggle,Shift+F12 exit)"
#define VER_INTERNALNAME_STR    "Open Source Software"
#define VER_PRODUCTNAME_STR    "Open Source Software"
#define VER_LEGALCOPYRIGHT_STR  "Open Source Software"
#define VER_LEGALTRADEMARKS1_STR    ""
#define VER_LEGALTRADEMARKS2_STR    ""
#define VER_ORIGINALFILENAME_STR    "CursorRestrict.exe"
#define VER_COMPANY_STR     "spacemiqote(author)"

#define STRINGIZE2(s)               #s
#define STRINGIZE(s)                STRINGIZE2(s)
#if (VERSION_UNSAFE == 1)
    #define MY_VERSION_NUM          STRINGIZE(VERSION_YEAR) STRINGIZE(VERSION_MONTH) "." STRINGIZE(VERSION_DAY) STRINGIZE(VERSION_UNSAFE)
#else
    #define MY_VERSION_NUM          STRINGIZE(VERSION_YEAR) STRINGIZE(VERSION_MONTH) "." STRINGIZE(VERSION_DAY)
#endif
#define VER_FILE_VERSION            VERSION_YEAR, VERSION_MONTH, VERSION_DAY, VERSION_UNSAFE
#define VER_FILE_VERSION_STR        STRINGIZE(VERSION_YEAR) "." STRINGIZE(VERSION_MONTH) "." STRINGIZE(VERSION_DAY) "." STRINGIZE(VERSION_UNSAFE)
#define VER_PRODUCT_VERSION         VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR     VER_FILE_VERSION_STR
#ifdef _DEBUG
    #define VER_VER_DEBUG           VS_FF_DEBUG
#else
    #define VER_VER_DEBUG           0
#endif
#define VER_FILEOS                  0x00L
#define VER_FILEFLAGS               VER_VER_DEBUG
#define VER_FILETYPE                0x01L
