#include "crossover.hpp"

void printonedim(int *arr,int len)
{
    for(int i=0;i<len;i++)
    {
        cout<<arr[i]<<' ';
    }
    cout<<endl;
}
void printtwodim(c2d arr,int pop,int len)
{
    for(int i=0;i<pop;i++)
    {
        for(int j=0;j<len;j++)
        {           
            cout<<arr[i][j]<<' ';
        }
        cout<<endl<<endl;
    }
}
void create(c2d &arr,int pop,int len)//隨機產生01
{
    for(int i=0;i<pop;i++)
    {
        for(int j=0;j<len;j++)
        {           
            int a=rand()%2;
            char c =a+'0';
            arr[i][j]=c;
            //cout<<arr[i][j]<<' ';
        }
        //cout<<endl<<endl;
    }
}
void evaluate(c2d arr,int pop,int len,i1d &value,int &bestpop,int &bestvalue)//評估所有染色體的適應度（也就是1有幾個)
{
    bestvalue=0;
    for(int i=0;i<pop;i++)
    {
        int temp=0;
        for(int j=0;j<len;j++)
        {
           if(arr[i][j] == '1')
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
void updateglobalbest(int bestvalue,int bestpop,int &globalbestvalue,c1d globalbest,c2d arr,int len)//更新最佳解
{
     if(bestvalue>globalbestvalue)
        {
            globalbestvalue=bestvalue;
            for(int i=0;i<len;i++)
            {
                globalbest[i]=  arr[bestpop][i];
            }
        }
}
int avg(i1d arr,int len)
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
void GA(int iteration,c2d P,i1d value,int pop,int len,c1d globalbest,int &globalbestvalue,int bestvalue,int bestpop,int r,i1d &result,char *function)
{
    int i=1;
    while(i<iteration)
    {
        c2d temp;
        temp.assign(pop,c1d(len,0));
        if(function == std::string("t"))
            tournament(P,temp,value,pop,len);
        else
        {
         roulettechoose(P,temp,value,pop,len);
        }
        
        crossover(P,temp,pop,len);
        evaluate(P,pop,len,value,bestpop,bestvalue);
        // printonedim(value,pop);
        updateglobalbest(bestvalue,bestpop,globalbestvalue,globalbest,P,len);
        i++;
        if(globalbestvalue==len)
            break;
    }
    result[r]=globalbestvalue;
}
void RUN(int iteration,c2d P,i1d value,int pop,int len,c1d globalbest,int &globalbestvalue,int bestvalue,int bestpop,int run,i1d &result,char *function)
{
     int r=0;
    while(r<run){
        create(P,pop,len);//隨機生成陣列
        evaluate(P,pop,len,value,bestpop,bestvalue);
        GA(iteration,P,value,pop,len,globalbest,globalbestvalue,bestvalue,bestpop,r,result,function);
        r++;
    }
 
    
}