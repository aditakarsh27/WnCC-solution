#include <bits/stdc++.h>
#include <string>
using namespace std;
float stof(string num) //Function to convert (a.bcd)string to float
{
    float n0=num[0]-'0';
    float n2=num[2]-'0';
    float n3=num[3]-'0';
    float n4=num[4]-'0';
    return n0+n2/10+n3/100+n4/1000;
}
int main()
{
    ifstream fin;
    string c;
    int i=0,realnum=0,usernum=0,sysnum=0;
    float realsum=0,usersum=0,syssum=0,realsq=0,usersq=0,syssq=0,realst,userst,sysst, realavg,useravg,sysavg;
    float R[100],U[100],S[100];
    float min;
    fin.open("timestat.txt");
    while(fin>>c)  //While file is open
    {
        if(c[1]=='m')
        {
            i++;
           if(i%3==1) //To detect whether it is real
            {
                min=c[0]-'0'; //converting from string to float
                R[i/3]=min*60+stof(c.substr(2,5)); //Storing time value in seconds in an array
                realsum=realsum+R[i/3]; //Storing sum of times
                realsq=realsq+R[i/3]*R[i/3]; //Storing sum of squares of times
            }
            else if(i%3==2) //To detect whether it is user
            {
                min=c[0]-'0';
                U[i/3]=min*60+stof(c.substr(2,5));
                usersum=usersum+min*60+U[i/3];
                usersq=usersq+U[i/3]*U[i/3];
            }
           else  //To detect whether it is sys
            {
                min=c[0]-'0';
                S[i/3-1]=min*60+stof(c.substr(2,5));
                syssum=syssum+S[i/3-1];
                syssq=syssq+S[i/3-1]*S[i/3-1];
            }
        }
    }
    int n=i/3; //Number of runs

    realavg=realsum/n;
    useravg=usersum/n;
    sysavg=syssum/n;

    realst=sqrt((realsq/n)-(realavg*realavg)); //Standard deviation
    userst=sqrt((usersq/n)-(useravg*useravg));
    sysst=sqrt((syssq/n)-(sysavg*sysavg));

    for(int j=0;j<100;j++) //To find number of times within standard deviation
    {
        if(abs(R[j]-realavg)<realst)
            realnum++;
        if(abs(U[j]-useravg)<userst)
            usernum++;
        if(abs(S[j]-sysavg)<sysst)
            sysnum++;
    }

    cout<<"Number of runs : "<<n
        <<"\nAverage Time statistics\n"
        <<"real "<<realavg<<" user "<<useravg<<" sys "<<sysavg
        <<"\nStandard deviation of Time statistics\n"
        <<"real "<<realst<<" user "<<userst<<" sys "<<sysst
        <<"\nNumber of runs within (average - standard deviation) to (average + standard deviation)\n"
        <<"real "<<realnum<<" user "<<usernum<<" sys "<<sysnum;

    return 0;
}
