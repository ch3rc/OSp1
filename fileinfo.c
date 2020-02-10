//======================================================
//Date:		February 8,2020
//Author:	Cody Hawkins
//Class:	Operating Systems (CS4760)
//Project:	Assignment 1
//File:		fileinfo.c
//======================================================


#include "fileinfo.h"
#include "flags.h"

#define MAX 1024
#define CTIME 26

char fileinfo[MAX] = "";

static void catString(const char *s)
{
	strcat(fileinfo, s);
}

void help()
{
	printf("----HELP------\n");
	printf("\n");
	printf("-h: print a help message\n");
	printf("-L: print symbolic links\n");
	printf("-t: print file type information\n");
	printf("-p: print permission bits as rwxrwxrwx\n");
	printf("-i: print number of links to file in inode table\n");
	printf("-u: print the user id associated with the file\n");
	printf("-g: print the group id associated with the file\n");
	printf("-s: print the file size\n");
	printf("-d: print date of last modification\n");
	printf("-l: Print info on file as if all tpiugs are initialized\n");
}


static char *bytes(const int filesize)
{
	char *size = (char *)malloc(500);
	
	//Gigabyte
	if((filesize / 1073741824) > 0)
	{
		sprintf(size, "%dG", (filesize / 1073741824));
		return size;
	}
	//Megabyte
	else if((filesize / 1048576) > 0)
	{
		sprintf(size, "%dM", (filesize / 1048576));
		return size;
	}
	//Kilobyte
	else if((filesize / 1024) > 0)
	{
		sprintf(size, "%dK", (filesize / 1024));
		return size;
	}
	//Smaller than Kb
	else
	{
		sprintf(size, "%d", filesize);
		return size;
	}
}


void fileInfoBuilder(const char *path)
{
	//get file status
	struct stat statbuf;
	if(lstat(path, &statbuf) == -1)
	{
		perror("Failed to get file status");
		exit(EXIT_FAILURE);
	}

	//check for symbolic links. TODO: create symbolic links to check
	if(L_symbolic)
	{	
		
		if((statbuf.st_mode & S_IFMT) == S_IFLNK)
		{
			char buf[300];

			int link;
			if(link = readlink(path, buf, sizeof(buf))== -1)
			{
				perror("readlink() error");
			}
			else
			{
				catString("symL:");
				catString(buf);
			}
		}	
	
	}
	
	//file type info
	if(t_fileType)
	{
		if(S_ISBLK(statbuf.st_mode))
		{
			catString("BLOCK");
		}
		else if(S_ISCHR(statbuf.st_mode))
		{
			catString("CHARACTER");
		}
		else if(S_ISDIR(statbuf.st_mode))
		{
			catString("DIRECTORY");
		}
		else if(S_ISFIFO(statbuf.st_mode))
		{
			catString("FIFO/PIPE");
		}
		else if(S_ISLNK(statbuf.st_mode))
		{
			catString("SYMLINK");
		}
		else if(S_ISREG(statbuf.st_mode))
		{
			catString("FILE");
		}
		else if(S_ISSOCK(statbuf.st_mode))
		{
			catString("SOCKET");
		}
		
		catString("  ");
	}

	//file permissions
	if(p_permissions)
	{
		S_ISDIR(statbuf.st_mode) ? catString("d") : catString("-");
		statbuf.st_mode & S_IRUSR ? catString("r") : catString("-");
		statbuf.st_mode & S_IWUSR ? catString("w") : catString("-");
		statbuf.st_mode & S_IXUSR ? catString("x") : catString("-");
		statbuf.st_mode & S_IRGRP ? catString("r") : catString("-");
		statbuf.st_mode & S_IWGRP ? catString("w") : catString("-");
		statbuf.st_mode & S_IXGRP ? catString("x") : catString("-");
		statbuf.st_mode & S_IROTH ? catString("r") : catString("-");
		statbuf.st_mode & S_IWOTH ? catString("w") : catString("-");
		statbuf.st_mode & S_IXOTH ? catString("x") : catString("-");
		catString("  ");
	}
	
	//number of links
	if(i_links)
	{
		char temp[300];
		sprintf(temp, "%d", statbuf.st_nlink);
		catString(temp);
		catString("  ");
	
	}

	//user id of file
	if(u_uid)
	{
		struct passwd *pwd;
		pwd = getpwuid(statbuf.st_uid);
		if(pwd == NULL)
		{
			perror("getpwuid");
			exit(EXIT_FAILURE);
		}
		catString(pwd->pw_name);
		catString("  ");
	}
	
	//group id of file
	if(g_gid)
	{
		struct group *grp;
		grp = getgrgid(statbuf.st_gid);
		if(grp == NULL)
		{
			perror("getgrgid");
			exit(EXIT_FAILURE);
		}
		catString(grp->gr_name);
		catString("  ");
	}
	
	//check filesizes
	if(s_filesize)
	{
		catString(bytes(statbuf.st_size));
		catString("\t");
	}
	

	//date of last modification
	if(d_lastmod)
	{
		char mtime[CTIME];
		strncpy(mtime, ctime(&statbuf.st_mtime), CTIME - 1);
		mtime[CTIME - 2] = 0;
		catString(mtime);
		catString("  ");
	}
	
	//append file path to the end of the string
	//remove ../ or ./at beginning of path	
	if(strstr(path, "../"))
	{	
		path += 3;
		catString(path);
	}
	else if(strstr(path, "./"))
	{
		path += 2;
		catString(path);
	}
}

//print full string and then remove info
void show()
{
	printf("%s\n", fileinfo);

	int i;
	
	for(i = 0; i < MAX; i++)
	{
		fileinfo[i] = '\0';
	}

}
