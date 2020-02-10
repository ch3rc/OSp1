//==========================================================
//Date:		February 8,2020
//Author:	Cody Hawkins
//Class:	Operating Systems (4760)
//Project:	Assignment 1
//File:		fileinfo.h
//=========================================================


#ifndef FILEINFO_H
#define FILEINFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "flags.h"

void help();

void fileInfoBuilder(const char *);

void show();

#endif
