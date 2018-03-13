#include "rnd.h"
#include "windows.h" //use gettickcount
#include "time.h"

#include <iostream>
#include <iomanip>
using namespace std;


void printbigint(Bigint *l)
{
	int i=0;
	
		cout <<"0x";
		for( i=MAXSIZE-1 ; i >=0  ; i--)
			cout <<setw(8)<<hex<<setfill('0')<<l->num[i]<<" ";

		cout <<endl;
	
}

int compare(WORD32 * pa,WORD32* pb,int size)
{
	int i;

	for(i=size-1;i>=0;i--){
		if(pa[i] > pb[i]) return 1;
		else if(pa[i] < pb[i]) return -1;
	}

	return 0;

}
/*
*  return 0 if l==r,1 if l>r, 0 if l<r 
*/
int _compare(Bigint * l,Bigint *r){
	return compare(l->num,r->num,MAXSIZE);
}

//copy from source to dest
void _clone(Bigint * source,Bigint * dest)
{
	int i=0;
	for( i=0 ; i < MAXSIZE ; i++)
		dest->num[i]=source->num[i];
}

//return the biggest bit' position
int deg(Bigint * l)
{
	int i=MAXSIZE-1;
	int j=1;
	while(l->num[i]==0) i--;
	while((l->num[i]>>j)!=0 && j<32) j++;

	return (32*i+j);
}

//return 1 if l==0
int is_zero(Bigint * l)
{
	int i;
	for(i=0 ; i<MAXSIZE ; i++){
		if(l->num[i]) return 0;
	}

	return 1;
}

void rnd_bigint(Bigint * number,Bigint * limit)//generate random number: limit/2 <=number<limit 
{
	WORD32 kbox[256];
	int i =0,j=0;
	Bigint  rand_num;

	j=deg(limit);

	if(j==0) return;
	do{  
		unsigned long test=0;
		int sig=0;

		srand( (unsigned)time( NULL ) + rand() );
		test=GetTickCount();
		for(i=0;  i < 256; i++ ){

			if(test!=GetTickCount()&&sig==0) 
			{
				srand( (unsigned) ((GetTickCount())%32767) * rand() );
				sig=1;
			}

			kbox[i] = rand()+(rand()<<16);

			if(i==255&&test==GetTickCount()) 
			{
				i=rand()%256+1;
			} 
		} 

		for(i=0; i<j; i++){
			rand_num.num[i/32] += (kbox[rand()/256] & (1<<(i+rand())%32));	 
		}
		if((j%32!=0))
		{
			rand_num.num[j/32] += (kbox[rand()/256] & (1<<(j+rand())%32));
			rand_num.num[(j/32)] = rand_num.num[(j/32)]&(0xFFFFFFFF>>(32-(j%32)));
		}
		else 
		{
			rand_num.num[(j/32)-1] =(rand_num.num[(j/32)-1] | 0x80000000);   
		}

	}while(_compare(&rand_num,limit)>=0 || deg(&rand_num)!=j || is_zero(&rand_num) );
	_clone(&rand_num,number);
}

void rnd_bigint_freelen(Bigint * number,Bigint * limit)//generate random number: number<limit 
{

	WORD32 kbox[256];
	int i =0,j=0;
	Bigint  rand_num;

	j=deg(limit);

	if(j==0) return;
	do{  
		unsigned long test=0;
		int sig=0;

		srand( (unsigned)time( NULL ) + rand() );
		test=GetTickCount();
		for(i=0;  i < 256; i++ ){

			if(test!=GetTickCount()&&sig==0) 
			{
				srand( (unsigned) ((GetTickCount())%32767) * rand() );
				sig=1;
			}

			kbox[i] = rand()+(rand()<<16);

			if(i==255&&test==GetTickCount()) 
			{
				i=rand()%256+1;
			} 
		} 

		for(i=0; i<j; i++){
			rand_num.num[i/32] += (kbox[rand()/256] & (1<<((rand())%32)));

		}
		if((j%32!=0))
		{
			rand_num.num[j/32] += (kbox[rand()/256] & (1<<((rand())%32)));
			rand_num.num[(j/32)] = rand_num.num[(j/32)]&(0xFFFFFFFF>>(32-(j%32)));  
		}


	}while(_compare(&rand_num,limit)>=0 || is_zero(&rand_num) );
	_clone(&rand_num,number);
}


WORD32 countone(Bigint *l)
{
	int i=0,j=0;//sizeof(WORD32)*8
	WORD32 cone=0;
	for(i=0 ; i<MAXSIZE ; i++){
		WORD32 wone=0;
		for (j=0;j<32;j++)
		{
			wone=1<<j;
			if(l->num[i]&wone) cone++;
		}
	}
	return cone;
}


void count16(Bigint *l,WORD32 a[16])
{
	int i=0,j=0;
	
	for(i=0 ; i<MAXSIZE ; i++){
        WORD32 x=0xF;
		for (j=0;j<8;j++)
		{
			 x=0xF<<(4*j);
			 if(((l->num[i]&x)>>(4*j))<16){a[((l->num[i]&x)>>(4*j))]++;}else {cout<<"outofbound";return;}	
		}
	}

}

int getbit(WORD32 num[],WORD32 i)
{
	int remainder=(i-1)%32;
	int wor=(i-1)/32;
	if(num[wor]&(1<<remainder))
	    return 1;
	else
		return 0;
}

WORD32 countruns(WORD32 num[625],WORD32 a[6],WORD32 b[6])
{
	int i=0,j=0;//sizeof(WORD32)*8
	WORD32 k=1,r=0;
	WORD32 maxruns=0;
	for(i=1 ; i<=625*32; i++){
		if(getbit(num,i)==getbit(num,i+1)) {k++;}
		else
		{
			r+=1;
			if(getbit(num,i)==0)
			{if(k>=6)a[5]++;else a[k-1]++;}
			else
			{if(k>=6)b[5]++;else b[k-1]++;}
			if (k>maxruns)
			{
				maxruns=k;
			}
			k=1;
		}
	}
	cout<<"MAX Runs Length: "<<dec<<maxruns<<endl;
	return r+1;
}