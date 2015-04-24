#ifndef __PLATFORM_SETTINGS_HPP
#define __PLATFORM_SETTINGS_HPP

#include <bits/stdc++.h>
#include <unistd.h>

#if (defined(__WIN32__) || defined(_WIN32) || defined(__WIN64__) || defined(__WIN64))
#	include <windows.h>
#	include <direct.h>
#	define SLEEP(MICROSECONDS) Sleep(int(MICROSECONDS))
#	define CLS  system("cls")
#	define MKDIR(DIRNAME) _mkdir(DIRNAME)
#else
#	include <sys/stat.h>
#	include <sys/types.h>
#	define SLEEP(MICROSECONDS) usleep(int(1000*(MICROSECONDS)))
#	define CLS  system("clear")
#	define MKDIR(DIRNAME) mkdir(DIRNAME,0777)
#endif

#endif
