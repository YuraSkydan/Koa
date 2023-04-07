#pragma once
#ifdef DLL_BUILD
#define KOA  //__declspec(dllexport)
#else
#define KOA  //__declspec(dllimport)
#endif