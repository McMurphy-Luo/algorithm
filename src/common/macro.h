#ifndef ALGORITHM_CONFIG_H
#define ALGORITHM_CONFIG_H

#ifdef WIN32
#define ALGORITHM_WINDOWS
#endif

#ifdef ALGORITHM_WINDOWS
// leak_detection feature use crt debug provided by visual studio crt.
// so this function is only supported on windows platform with visual studio

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#endif // ALGORITHM_WINDOWS

#endif // ALGORITHM_CONFIG_H