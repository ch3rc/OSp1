//================================================================
//Date:		February 8,2020
//Author:	Cody Hawkins
//Class:	Operating Systems (CS4760)
//Project:	Assignment 1
//File:		flags.c
//================================================================


#include "flags.h"

int h_helpmessage;
int L_symbolic;
int t_fileType;
int p_permissions;
int i_links;
int u_uid;
int g_gid;
int s_filesize;
int d_lastmod;
int l_allflags;

char *dirname;

void initOptions()
{
	h_helpmessage = 0;
	L_symbolic = 0;
	t_fileType = 0;
	p_permissions = 0;
	i_links = 0;
	u_uid = 0;
	g_gid = 0;
	s_filesize = 0;
	d_lastmod = 0;
	l_allflags = 0;
	dirname = NULL;
}

void allTpuigs()
{
	p_permissions = 1;
	i_links = 1;
	u_uid = 1;
	g_gid = 1;
	s_filesize = 1;
	d_lastmod = 1;
}

void setOptions(int argc, char *argv[])
{
	int i;
	int c;

	while((c = getopt(argc, argv, "hLtpiugsdl")) != -1)
	{
		
		switch(c)
			{
			
			case 'h':
			 	h_helpmessage = 1;
				break;

			case 'L':
				L_symbolic = 1;
				break;
				
			case 't':
				t_fileType = 1;
				break;

			case 'p':
				p_permissions = 1;
				break;

			case 'i':
				i_links = 1;
			
			case 'u':
				u_uid = 1;
				break;

			case 'g':
				g_gid = 1;
				break;

			case 's':
				s_filesize = 1;
				break;

			case 'd':
				d_lastmod = 1;
				break;

			case 'l':
				l_allflags = 1;
				allTpuigs();
				break;

			case '?':
				printf("unknown option %s\n", optarg);
				exit(0);
				break;
			}

	}
	
	//if file name is given save as dirname else default to current working directory
	if(optind < argc)
	{
		dirname = argv[optind];
	}

	if(dirname == NULL)
	{
		dirname = ".";
	}

}



