//===============================================================
//Date: 	February 8, 2020
//Author:	Cody Hawkins
//Class:	Operating Systems (CS4760)
//Project:	Assignment 1
//File:		bfs.h
//===============================================================


#ifndef BFS_H
#define BFS_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <utime.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

typedef struct node{
	char *dirname;
	struct node *nextNode;
}node;

typedef struct queue{
	int index;
	struct node *front;
	struct node *rear;
}queue;

int isEmpty(struct queue *);

struct queue *makeQ();

void enqueue(struct queue *, char *);

struct node *dequeue(struct queue *);

void breadthfirst(char *);

#endif
