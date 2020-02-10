//==================================================================
//Date:		February 8,2020
//Author:	Cody Hawkins
//Class:	Operating Systems (CS4760)
//Project:	Assignment 1
//File:		main.c
//==================================================================


#include "flags.h"
#include "bfs.h"
#include "fileinfo.h"
int main(int argc, char *argv[])
{
	
	initOptions();

	setOptions(argc, argv);
	
	if(h_helpmessage)
	{
		help();
		return 0;
	}

	breadthfirst(dirname);


	return 0;

}	
