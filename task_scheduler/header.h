#ifndef HEADER_H
#define HEADER_H
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
// Define ANSI escape codes for colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"
enum status{FALSE,TRUE};
enum Size{Task1,Task2,Task3,TotalSize};
typedef  void (*fnctptr)(void);
typedef struct {
fnctptr functionAddr;
int interval;
int timerCounter;
}TskSchedulerStruct;
#endif