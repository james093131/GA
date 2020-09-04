#define CR 0.95
#define MR 0.1
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include <string.h>
#include<time.h>
using namespace std;
void printonedim(int *,int );
void printtwodim(char *,int ,int );
void create(char *,int ,int );//隨機產生01
void evaluate(char *,int ,int ,int *,int &,int &);//評估所有染色體的適應度（也就是1有幾個)
void updateglobalbest(int ,int ,int &,char *,char *,int );
int avg(int *,int );
void finaloutput(int ,int ,int ,int ,double ,double ,char *);
void GA(int ,char *,int *,int ,int ,char *,int &,int ,int ,int ,int *,char *);
void RUN(int ,char *,int *,int ,int ,char *,int &,int ,int ,int ,int *,char *);