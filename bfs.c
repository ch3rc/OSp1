//===================================================================
//Date:		February 8,2020
//Author:	Cody Hawkins
//Class:	Operating Systems (CS4760)
//Project:	Assignment 1
//File:		bfs.c
//===================================================================

#include "bfs.h"
#include "fileinfo.h"

//check if q is empty
int isEmpty(struct queue *q)
{
	return !(q->index);
}

//create a queue node
struct queue *makeQ()
{
	struct queue *q = (struct queue *)malloc(sizeof(struct queue));
	q->index = 0;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

//intialize node if new, if already created add adjacent paths
void enqueue(struct queue *q, char *path)
{
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	newNode->dirname = path;
	newNode->nextNode = NULL;
	if(!isEmpty(q))
	{
		q->rear->nextNode = newNode;
		q->rear = newNode;
	}else{
		q->front = q->rear = newNode;
	}
	q->index++;
}

//pop of traversed path and move to next
struct node *dequeue(struct queue *q)
{
	struct node *temp;
	temp = q->front;
	q->front = q->front->nextNode;
	q->index--;
	return temp;
}

//concat prevoius path and newpath
static char *concatPath(long parent, long child, char *start, const char *next)
{
	char *temp = (char *)malloc(sizeof(parent + child + 2));
	strcpy(temp, start);
	strcat(temp, "/");
	strcat(temp, next);
	return temp;
}


void breadthfirst(char *path)
{
	DIR *dp, *dir;
	struct dirent *entry;
	struct stat fileStat;
	struct queue *q;
	char *name;
	long len_parent, len_child;
	
	//create queue and intialize
	q = makeQ();
	enqueue(q, path);
	
	//get first path information
	dir = opendir(path);
	fileInfoBuilder(path);
	show();
	closedir(dir);

	while(!isEmpty(q))
	{
		struct node *next = dequeue(q);
		dp = opendir(next->dirname);
		
		len_parent = strlen(next->dirname);
		while((entry = readdir(dp)) != NULL)
		{
			//ignore current, parent and git repository
			if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0) && (strcmp(entry->d_name, ".git") != 0))
			{
				len_child = strlen(entry->d_name);
				name = (char *)malloc(sizeof(len_parent + len_child + 2));
				name = concatPath(len_parent, len_child, next->dirname, entry->d_name);
				if(stat(name, &fileStat) < 0)
				{
					printf("ERROR: %s: %s\n", name, strerror(errno));
					free(name);
				}
				else
				{
					if(S_ISDIR(fileStat.st_mode))
					{
						//add next path to queue and show info if directory
						enqueue(q, name);	
						fileInfoBuilder(name);
						show();
					}
					else
					{
						//if file show information	
						fileInfoBuilder(name);
						show();
						free(name);
					}
				}
			}
		}
		closedir(dp);
	}
} 
