#include "GAfunction.hpp"
int main(int argc, char *argv[])
{
    double START,END;
    srand(time(NULL));
    int pop = atoi(argv[1]);
	int iteration = atoi(argv[2]);
    int run = atoi(argv[3]);    

    // START=clock();
    RUN(iteration,pop,run);
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