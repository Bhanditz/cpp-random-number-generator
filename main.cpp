#include "rnd.h"
#include <iostream>
using namespace std;

int main()
{
	int i=0,j=0;
	Bigint num;
	Bigint limit;
	
	for (i=0; i<MAXSIZE;i++)
	{
		limit.num[i]=0xFFFFFFFF;
	}
	
	
	WORD32 s2=0,runs=0,sumofpoker=0;
	WORD32 poker[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	WORD32 a[6]={0,0,0,0,0,0};
	WORD32 b[6]={0,0,0,0,0,0};
	WORD32 number[625]={0};
	WORD32 onecount=0;
	for (i=0;i<MAXSIZE;i++)
	{
		rnd_bigint(&num,&limit);
		onecount+=countone(&num);
		count16(&num,poker);       
		 
		for (j=0;j<MAXSIZE;j++)
		{
			number[MAXSIZE*i+j]=num.num[j];
		}
	}
	cout<<"Monobit TEST (Should Between 9654 and 10346): "<<dec<<onecount<<endl;
	cout<<"***********************************************************"<<endl;
	for (i=0; i<16;i++)
	{
		cout<<" "<<i<<" Times: "<<poker[i]<<endl;
	    s2+=(poker[i]*poker[i]);
		sumofpoker+=poker[i];
	}
    s2=s2*16/5000-5000;
    cout<<"SUM of poker (Should be 5000): "<<sumofpoker<<endl;
	cout<<"Poker TEST (Should Between 1.03 and 57.4): "<<dec<<s2<<endl;
	cout<<"***********************************************************"<<endl;
	cout<<"Long Run TEST (MAX Runs Length Should  < 34 ): ";
	runs=countruns(number,a,b);
	cout<<"***********************************************************"<<endl;
	cout<<"Runs TEST: "<<endl;
	
    cout<<"Runs length: 1"<<" Runs Times (Should Between 2,267 and 2,733) "<<endl<<"Zero Runs Times: "<<dec<<a[0]<<","<<" One Runs Times: "<<dec<<b[0]<<endl;
	cout<<"Runs length: 2"<<" Runs Times (Should Between 1,079 and 1,421) "<<endl<<"Zero Runs Times: "<<dec<<a[1]<<","<<" One Runs Times: "<<dec<<b[1]<<endl;
	cout<<"Runs length: 3"<<" Runs Times (Should Between 502 and 748) "<<endl<<"Zero Runs Times: "<<dec<<a[2]<<","<<" One Runs Times: "<<dec<<b[2]<<endl;
	cout<<"Runs length: 4"<<" Runs Times (Should Between 223 and 402) "<<endl<<"Zero Runs Times: "<<dec<<a[3]<<","<<" One Runs Times: "<<dec<<b[3]<<endl;
	cout<<"Runs length: 5"<<" Runs Times (Should Between 90 and 223) "<<endl<<"Zero Runs Times: "<<dec<<a[4]<<","<<" One Runs Times: "<<dec<<b[4]<<endl;
	cout<<"Runs length: >=6"<<" Runs Times (Should Between 90 and 223) "<<endl<<"Zero Runs Times: "<<dec<<a[5]<<","<<" One Runs Times: "<<dec<<b[5]<<endl;
	

    cout<<"Sum of Runs "<<runs<<endl;
	cout<<"***********************************************************"<<endl;
    

	for (j=625-1;j>=0;j--)
	{
		cout<<hex<<number[j]<<" ";
	}
    cout<<endl<<"***********************************************************"<<endl;
	system("pause");
	return 0;
}