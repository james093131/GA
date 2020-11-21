#include "GAfunction.hpp"
int main(int argc, char *argv[])
{
    double START,END;
    srand(time(NULL));
    int len = atoi(argv[1]);
    int pop = atoi(argv[2]);
	int iteration = atoi(argv[3]);
    int run = atoi(argv[4]);
    char * functionchoice=argv[5];
    c2d P;
    P.assign(pop, c1d(len, 0));
    i1d value(pop,0);//儲存目前最佳的染色體
    c1d globalbest;
    globalbest.resize(len);
    int globalbestvalue=0;;
    int bestpop=0;//儲存最佳的解的位置
    int bestvalue=0;//儲存最佳的解多少bit
    //printonedim(value,pop);
    i1d result(run,0);
    
    // START=clock();
    RUN(iteration,P,value,pop,len,globalbest,globalbestvalue,bestvalue,bestpop,run,result,functionchoice);
    // // END=clock();
    // // int avg_bestvalue=avg(result,run);
    // // finaloutput(len,pop,avg_bestvalue,run,START,END,functionchoice);
    // // fstream file;//寫檔
    // // if(functionchoice == std::string("t"))
	// //     file.open("GA_Tournament.txt",ios::app);
    // // else
    // //     file.open("GA_Roulettechoose.txt",ios::app);
	// // file<<iteration<<' '<<avg_bestvalue<<endl;
}