#include "crossover.hpp"

int* read(int &sum){//讀檔

    fstream file;
    int ind=0;
    file.open("readfile.txt",ios::in);
    int* temp=new int[510];
    while(file)
    {
        file>>temp[ind];
        ind++;
    }
    sum=ind-1;
    return temp;
}

void makearr(i2d &arr,int *input,int len)//將測資讀為整理好的陣列
{
    int chc=0;
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<dim;j++)
        {
            arr[i][j] = *(input+chc);
            //cout<<*((int*)arr +dim*i+j)<<' ';
            chc++;
        }
        //cout<<endl<<endl;
    }
}
double distance_calculate(int x1 ,int y1,int x2,int y2){//計算兩點的距離
    double dis;
    dis=pow(x2-x1,2)+pow(y2-y1,2);
    dis=sqrt(dis);
    return dis;
}
void distancecal(d2d &arr ,i2d city,int cityquan)
{
    for(int i=0;i<cityquan;i++)
    {
        for(int j=0;j<cityquan;j++)
        {
            if(i<=j)
                arr[i][j] = distance_calculate(city[i][1],city[i][2],city[j][1],city[j][2]);
                arr[j][i]=arr[i][j];
        }
    }
}



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
void create(i2d city,i2d &arr,int pop)//隨機產生TSP
{
    arr.assign(pop,i1d(city.size()+1,0));
    for(int i=0;i<pop;i++)
    {
        i1d choose_table;
        for(int i=0;i<city.size();i++)
        {
        choose_table.push_back(city[i][0]);
        }
        for(int j=0;j<city.size()+1;j++)
        {      
            if( j == city.size())
            {
                arr[i][j] = arr[i][0];
            }
            else{
                int index = rand()%choose_table.size();
                int a = choose_table[index];
                choose_table.erase(choose_table.begin()+index);
                arr[i][j] = a;
            }
            // cout<<arr[i][j]<<' ';            
        }
    
        // cout<<endl<<endl;
    }
}
void evaluate(i2d arr,d2d distance_table,d1d &Fitness,int &bestpop,int &bestvalue)//評估所有染色體的適應度（也就是1有幾個)
{
    bestvalue=1000000;
    for(int i=0;i<arr.size();i++)
    {
        double temp=0;
        for(int j=0;j<arr[i].size()-1;j++)
        {
           int Start = arr[i][j];
           int End = arr[i][j+1];
           temp += distance_table[Start-1][End-1];
        }
        // cout<<temp;
        Fitness[i]=temp;
        if(Fitness[i] < bestvalue)
            {
                bestpop=i;
                bestvalue = Fitness[i];
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

void ini(i2d &city,d2d &distancetable)
{
    int *a;
    int templen;
    a = read(templen); //讀檔用的pointer

    int len = templen / dim;
    d1d iteration_optimum(1001);
    int bestrunresult = 100000;
    city.assign(len, i1d(dim, 0));
    distancetable.assign(len,d1d(len,0));//儲存距離表
    makearr(city, a, len);
    distancecal(distancetable, city, len); //製作距離表
}
void GA(int iteration,i2d P,i1d value,int pop,i1d globalbest,int &globalbestvalue,int bestvalue,int bestpop,int r,i1d &result,char *function)
{
    int i=1;
    i1d bestrunpath;
    i2d city;
    d2d distancetable;
    d1d Fitness(pop);
    i2d temp;
    ini(city,distancetable);//做距離表和建立城市座標表
    bestrunpath.resize(city.size()+1);
    create(city,P,pop);
    temp.assign(P.size(),i1d(P[0].size(),0));
    evaluate(P,distancetable,Fitness,bestpop,bestvalue);//初始化完成
    for(int i=0;i<P.size();i++)
    {
        for(int j=0;j<P[i].size();j++)
        {
            cout<<P[i][j]<<' ';
        }
        cout<<"F"<<Fitness[i];
        cout<<endl<<endl;
    }
    tournament(P,temp,Fitness,pop);
    for(int i=0;i<temp.size();i++)
    {
        for(int j=0;j<temp[i].size();j++)
        {
            cout<<temp[i][j]<<' ';
        }
        cout<<endl<<endl;
    }
    // while(i<iteration)
    // {
    //     c2d temp;
    //     temp.assign(pop,c1d(len,0));
    //     if(function == std::string("t"))
    //         tournament(P,temp,value,pop,len);
    //     else
    //     {
    //      roulettechoose(P,temp,value,pop,len);
    //     }
        
    //     crossover(P,temp,pop,len);
    //     evaluate(P,pop,len,value,bestpop,bestvalue);
    //     // printonedim(value,pop);
    //     updateglobalbest(bestvalue,bestpop,globalbestvalue,globalbest,P,len);
    //     i++;
    //     if(globalbestvalue==len)
    //         break;
    // }
    // result[r]=globalbestvalue;
}
void RUN(int iteration,i2d P,i1d value,int pop,i1d globalbest,int &globalbestvalue,int bestvalue,int bestpop,int run,i1d &result,char *function)
{
     int r=0;
    while(r<run){
        GA(iteration,P,value,pop,globalbest,globalbestvalue,bestvalue,bestpop,r,result,function);
        r++;
    }
 
    
}