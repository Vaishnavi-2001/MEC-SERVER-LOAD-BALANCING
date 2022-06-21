#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iterator>
#include <random>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <time.h>
#define e  2.71828

using namespace std;

void ant_colony(float arr[100][100],vector<float> process,vector<int> j,vector<int> m)
{


   int alpha=2,beta=1;
   float sum=0.0;
   cout<<endl;
   float prob[100][100],num,den;
   vector <float>  s;
   for(int i=0; i<j.size();i++)
   {
       for(int j=0;j<process.size(); j++)
       {
           sum=sum+(pow(arr[i][j],alpha)*pow(process[j],beta));
       }
       s.push_back(sum);
       sum=0.0;
   }
   float sum1=0.0;

   float a=0.0;
   for(int i=0; i<j.size(); i++)
   {
       for(int j=0; j<process.size(); j++)
       {
           a=(pow(arr[i][j],alpha)*pow(process[j],beta));
           prob[i][j]=a/s[i];
           a=0.0;
       }
   }
  cout<<" PROBABILITY TABLE "<<endl;
   for(int i=0; i<j.size(); i++)
   {
       for(int j=0; j<m.size(); j++)
       {
           cout<<prob[i][j]<<" ";
       }
       cout<<endl;
   }
   cout<<endl;

   cout<<endl;


}

vector<int> poission_dis2(vector<int> v)
{
  vector<int> v4;
  cout<<" BASED ON POISSION DISTRIBUTION " <<endl;
  cout<<endl;
  for (int i=0; i<v.size(); ++i)
  {
    std::default_random_engine generator(time(0));
    std::mt19937 mrand(std::time(0));
    cout<<"AT "<<generator<<" : PROCESSING RATE OF : "<<i+1<<" MEC SEVER IS : ";
    std::poisson_distribution<int> distribution(v[i]);
    int number = distribution(generator);
    cout<<number<<" "<<endl;
    v4.push_back(number);
  }
  cout<<endl;
  return v4;
}
vector<int> poission_dis(vector<int> v2)
{
  vector<int> v3;
  cout<<" BASED ON POISSION DISTRIBUTION " <<endl;
  cout<<endl;
  for (int i=0; i<v2.size(); ++i)
  {
    std::default_random_engine generator(time(0));
    std::mt19937 mrand(std::time(0));
    cout<<"AT "<<generator<<" : PACKETS ARRIVING IN : "<<i+1<<" MEC SEVER : ";
    std::poisson_distribution<int> distribution(v2[i]);
    int number = distribution(generator);
    cout<<number<<" "<<endl;
    v3.push_back(number);
  }
  cout<<endl;
  return v3;
}

int main()
{
   vector<int> mec_mean_arrival;
   vector<int> mec_processing;
   vector<int> instance;
   vector<int> instance2;
   vector<int> job;
   vector<int> machine;
   vector<float> ppp;
   float  cal[100][100];
   float cal1[100][100];
   float sumofpro;

   mec_mean_arrival.push_back(900);
   mec_mean_arrival.push_back(500);
   mec_mean_arrival.push_back(1000);
   mec_mean_arrival.push_back(850);
   mec_mean_arrival.push_back(700);


   mec_processing.push_back(550);
   mec_processing.push_back(800);
   mec_processing.push_back(980);
   mec_processing.push_back(640);
   mec_processing.push_back(1500);

instance=poission_dis(mec_mean_arrival);
instance2=poission_dis2(mec_processing);
cout<<"MAIN"<<endl;
cout<<endl;
for(int i=0;i<instance.size();i++)
{
    cout<<"MEC SERVER : "<<i+1<<" PACKETS ARRIVED : "<< instance[i]<<" PROCESSING POWER : "<<instance2[i]<<endl;
}
cout<<endl;
for(int i=0;i<instance2.size();i++)
{
    if(instance2[i]-instance[i]<0)
    {
        int z=instance2[i]-instance[i];
        job.push_back((-1)*z);
    }
    else
    {
        machine.push_back(instance2[i]-instance[i]);
    }
}

cout<<"JOB     : ";
for(int i=0;i<job.size();i++)
{
    cout<<job[i]<<" ";
}
cout<<endl;
cout<<"MACHINE : ";
for(int i=0;i<machine.size();i++)
{
    cout<<machine[i]<<" ";
}
cout<<endl;
for(int i=0;i<job.size();i++)
{
    for(int j=0;j<machine.size();j++)
    {
        if(job[i]>machine[j])
            cal[i][j]=0;
        else
        {
         float g = job[i];
         float s=  machine[j];
         cal[i][j]=g/s;
        }
    }
}
cout<<endl;
cout<<" 1st pheremone table " <<endl;
int n=sizeof(cal);
for(int i = 0; i <job.size(); i++)
    {
        cout<<"JOB "<<i+1<<" :: ";
        for(int j = 0; j < machine.size(); j++)
        {
            cout << cal[i][j] << " ";
        }
        cout << endl;
    }

 for(int j = 0; j < machine.size(); j++)
        {
            float kk;
            kk=machine[j];
            ppp.push_back(1/kk);
        }
       cout<<endl;
        cout<<" 1/process rate table "<<endl;
        for(int i=0;i<ppp.size();i++)
        {
            cout<<" MACHINE "<<i<<" : "<<ppp[i]<<" ";
        }
  cout<<endl;
ant_colony(cal,ppp,job,machine);

 for(int i=0; i<ppp.size(); i++)
  {
      sumofpro=sumofpro+ppp[i];
  }
for(int i=0;i<100;i++){
   cout<<" PHEREMONE UPDATED TABLE "<<endl;
    for(int i=0; i<job.size(); i++)
   {
       for(int j=0; j<ppp.size(); j++)
       {
           if(cal[i][j]!=0)
           {
           cal[i][j]=(0.5*cal[i][j]+sumofpro);
           }
       }
   }
   for(int i=0; i<job.size(); i++)
   {
       for(int j=0; j<machine.size(); j++)
       {
           cout<<cal[i][j]<<" ";
       }
       cout<<endl;
   }
  ant_colony(cal,ppp,job,machine);
}
double r = ((double) rand() / (RAND_MAX));
cout<<" RANDOM INSTANCE  "<<r<<endl;

for(int i=0;i<job.size();i++)
{

    for(int j=0;j<machine.size();j++)
    {

        if(cal[i][j]>r)
        {
            cout<<" JOB "<<i+1<<" chooses machine "<<j+1<<" at instance "<<r<<endl;
            break;
        }
    }
}
