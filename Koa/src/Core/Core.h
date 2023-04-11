#pragma once
#ifdef DLL_BUILD
#define KOA_API  //__declspec(dllexport)
#else
#define KOA_API  //__declspec(dllimport)
#endif