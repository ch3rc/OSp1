#ifndef FLAGS_H
#define FLAGS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


extern int h_helpMessage;
extern int L_symbolic;
extern int t_fileType;
extern int p_permissions;
extern int i_links;
extern int u_uid;
extern int g_gid;
extern int s_filesize;
extern int d_lastmod;
extern int l_allflags;

extern char *dirname;

void initOptions();

void setOptions(int argc, char *argv[]);

void allTpuigs();

void print();

#endif
