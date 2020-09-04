#include "GAfunction.hpp"
void tournament(char *arr,char *temp,int *value,int pop,int len){
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
        *((char*)temp +len*i+k)=*((char*)arr +len*chc+k);
        }
        i++;
    }
}
void mutation(char *arr,int ind,int len)//隨機選取一點做調換
{
    int c=rand()%len;
    if( *((char*)arr +len*ind+c)=='1')
        *((char*)arr +len*ind+c)='0';
    else
        *((char*)arr +len*ind+c)='1';
    
}
void crossover(char *arr,char *temp,int pop,int len){//隨機生成一個切割點，將兩個染色體做交配
    int i=0;
    while(i<pop){
        int c1=rand()%len;
        int c2=rand()%len;
        float t1 = (float) rand() / (RAND_MAX + 1.0);
        for(int k=0;k<len;k++)
        {
            if(t1<CR){
                if(k>c1)
                {
                    *((char*)arr +len*i+k)=*((char*)temp +len*(i+1)+k);
                    *((char*)arr +len*(i+1)+k)=*((char*)temp +len*(i)+k);
                }
                else{
                    *((char*)arr +len*i+k)=*((char*)temp +len*(i)+k);
                    *((char*)arr +len*(i+1)+k)=*((char*)temp +len*(i+1)+k);
                }
            }
            else{
                *((char*)arr +len*i+k)=*((char*)temp +len*(i)+k);
                *((char*)arr +len*(i+1)+k)=*((char*)temp +len*(i+1)+k);
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
void sum(int *arr,int len,int &s)
{
    for(int i=0;i<len;i++)
    {
            s+=arr[i];
    }
}
void cut(int *value,double *split,int sum,int pop)
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
void roulettechoose(char *arr,char *temp,int *value,int pop,int len)
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
            *((char*)temp +len*i+k)=*((char*)arr +len*chc+k);
        }
        i++;
    }
}