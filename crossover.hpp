#define CR 0.95
#define MR 0.1
#define dim 3//幾維
#include<stdio.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include <string.h>
#include<time.h>
#include<vector>
#include<math.h>
using namespace std;

typedef vector<char> c1d;
typedef vector<c1d> c2d;
typedef vector<c2d> c3d;
typedef vector<c3d> c4d;
typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<i2d> i3d;
typedef vector<i3d> i4d;
typedef vector<double>d1d;
typedef vector<d1d> d2d;
typedef vector<d2d> d3d;
typedef vector<d3d> d4d;

void tournament(c2d arr,c2d &temp,i1d value,int pop,int len){
    int i=0;
    while(i<pop){
        int c1=rand()%(pop);
        int c2=rand()%(pop);
        int chc;
        if(value[c1]>value[c2]){
            chc=c1;
        }
        else{
            chc=c2;
        }
        for(int k=0;k<len;k++)
        {
        temp[i][k]=arr[chc][k];
        }
        i++;
    }
}
void mutation(c2d &arr,int ind,int len)//隨機選取一點做調換
{
    int c=rand()%len;
    if( arr[ind][c] == '1')
        arr[ind][c]='0';
    else
        arr[ind][c]='1';
    
}
void crossover(c2d &arr,c2d temp,int pop,int len){//隨機生成一個切割點，將兩個染色體做交配
    int i=0;
    while(i<pop){
        int c1=rand()%len;
        // int c2=rand()%len;
        float t1 = (float) rand() / (RAND_MAX + 1.0);
        for(int k=0;k<len;k++)
        {
            if(t1<CR){
                if(k>c1)
                {
                    arr [i][k]=temp[i+1][k];
                    arr [i+1][k]=temp[i][k];
                }
                else{
                    arr [i][k]=temp[i][k];
                    arr [i+1][k]=temp[i+1][k];
                }
            }
            else{
                arr[i][k]=temp[i][k];
                arr[i+1][k]=temp[i+1][k];
            }
        }
        float x = (float) rand() / (RAND_MAX + 1.0);
        float y = (float) rand() / (RAND_MAX + 1.0);
        if(x<MR)
        {
        mutation(arr,i,len);
        }
        if(y<MR)
        {
        mutation(arr,i+1,len); 
        }
        i+=2;
    }
}
void sum(i1d arr,int len,int &s)
{
    for(int i=0;i<len;i++)
    {
            s+=arr[i];
    }
}
void cut(i1d value,double *split,int sum,int pop)
{
    split[0]=0;split[pop]=1;
    double temp=0;
    for(int i=1;i<pop;i++)//設定區間用
    {
        temp+=value[i];
        split[i]=temp/sum;
    }
}
void tran(int &chc,double x,double *split,int len){
    for(int i=1;i<len;i++)
    {
        if(x>split[i-1]&&x<split[i])
        {

            chc=i-1;
            break;
        }
    }
}
void roulettechoose(c2d arr,c2d &temp,i1d value,int pop,int len)
{
    int i=0;
    int s=0;
    int chc;
    double split[pop+1];
    sum(value,len,s);
    cut(value,split,s,pop);
    while(i<pop){
        double x = (double) rand() / (RAND_MAX + 1.0);
        tran(chc,x,split,pop+1);
        for(int k=0;k<len;k++)
        {
           temp[i][k]=arr[chc][k];
        }
        i++;
    }
}