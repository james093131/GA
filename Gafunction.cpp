#include "GAfunction.hpp"  
#include "crossover.hpp"
void printonedim(int *arr,int len)
{
    for(int i=0;i<len;i++)
    {
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}
void printtwodim(char *arr,int pop,int len)
{
    for(int i=0;i<pop;i++)
    {
        for(int j=0;j<len;j++)
        {           
            cout<<*((char*)arr +len*i+j)<<' ';
        }
        cout<<endl<<endl;
    }
}
void create(char *arr,int pop,int len)//隨機產生01
{
    for(int i=0;i<pop;i++)
    {
        for(int j=0;j<len;j++)
        {           
            int a=rand()%2;
            char c =a+'0';
            *((char*)arr +len*i+j)=c;
            //cout<<*((char*)arr +len*i+j)<<' ';
        }
        //cout<<endl<<endl;
    }
}
void evaluate(char *arr,int pop,int len,int *value,int &bestpop,int &bestvalue)//評估所有染色體的適應度（也就是1有幾個)
{
    bestvalue=0;
    for(int i=0;i<pop;i++)
    {
        int temp=0;
        for(int j=0;j<len;j++)
        {
           if(*((char*)arr +len*i+j)=='1')
           {
            temp++;
           }
        }
        value[i]=temp;
        if(value[i]>bestvalue)
            {
                bestpop=i;
                bestvalue=value[i];
            }
    }

}
void updateglobalbest(int bestvalue,int bestpop,int &globalbestvalue,char *globalbest,char *arr,int len)
{
     if(bestvalue>globalbestvalue)
        {
            globalbestvalue=bestvalue;
            for(int i=0;i<len;i++)
            {
                globalbest[i]= *((char*)arr +bestpop*len+i);
            }
        }
}
int avg(int *arr,int len)
{
	int sum=0;
	for(int i=0;i<len;i++)
	{
		sum+=arr[i];
		//cout<<"iteration"<<i+1<<':'<<arr[i]<<endl;
	}
	int avg=sum/len;
	return avg;
}
void finaloutput(int len,int pop,int avgbestvalue,int run,double START,double END,char * function)
{   
    cout<<"length : "<<len<<endl;
    cout<<"Population : "<<pop<<endl;
    cout<<"Run :"<<run<<endl;
    cout<<"Average Optimum : "<<avgbestvalue<<endl;
    if(function == std::string("t"))
        cout<<"Select Function : Tournament"<<endl;
    else
        cout<<"Select Function : Roulettechoose"<<endl;
    cout<<"Execution Time :"<<(END - START) / CLOCKS_PER_SEC<<"(s)"<<endl;
}
void GA(int iteration,char *P,int *value,int pop,int len,char *globalbest,int &globalbestvalue,int bestvalue,int bestpop,int r,int *result,char *function)
{
    int i=1;
    while(i<iteration)
    {
        char temp[pop][len];
        if(function == std::string("t"))
            tournament((char*)P,(char*)temp,value,pop,len);
        else
        {
         roulettechoose((char*)P,(char*)temp,value,pop,len);
        }
        
        crossover((char*)P,(char*)temp,pop,len);
        evaluate((char*)P,pop,len,value,bestpop,bestvalue);
        //printonedim(value,pop);
        updateglobalbest(bestvalue,bestpop,globalbestvalue,globalbest,(char*)P,len);
        i++;
        if(globalbestvalue==len)
            break;
    }
    result[r]=globalbestvalue;
}
void RUN(int iteration,char *P,int *value,int pop,int len,char *globalbest,int &globalbestvalue,int bestvalue,int bestpop,int run,int *result,char *function)
{
     int r=0;
    while(r<run){
        create((char*)P,pop,len);//隨機生成陣列
        evaluate((char*)P,pop,len,value,bestpop,bestvalue);
        GA(iteration,(char*)P,value,pop,len,globalbest,globalbestvalue,bestvalue,bestpop,r,result,function);
        r++;
    }
 
    
}