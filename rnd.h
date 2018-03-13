#ifndef RND_H
#define RND_H

#define MAXSIZE 25

typedef unsigned long WORD32;
struct Bigint  
{
 WORD32 num[MAXSIZE];//bigindia  
};

 void printbigint(Bigint *l);
 int is_zero();
 int deg();
 int _compare(Bigint *pa,Bigint *pb);
 void _clone(Bigint * source,Bigint * dest);
 void rnd_bigint(Bigint * number,Bigint * limit);//limit/2 <= rnd <limit
 void rnd_bigint_freelen(Bigint * number,Bigint * limit);
 WORD32 countone(Bigint *l);
 void count16(Bigint *l,WORD32 a[16]);
 int getbit(WORD32 num[],WORD32 i);//return the i th bit of l
WORD32 countruns(WORD32 num[625],WORD32 a[6],WORD32 b[6]);
#endif

