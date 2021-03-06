#include"GF_2sup8.h"
static int move_left_by(const int s,const int b)
{
	if(s>b || s<=0)
		return -1; 
	int i,si=-1,bi=-1;
	for(i=0;i<16;i++)
	{   
		if(s&bit_vector[i] && si==-1)
			si=i;
		if(b&bit_vector[i] && bi==-1)
			bi=i;
		if(si>0&&bi>0)
			break;
	}   
	int m_n=si-bi;
	return m_n;
}

/*axb*/
int GF2sup8_mul8(const int a,const int b)
{
	if(!a || !b) return 0;
	int BX[8];
	BX[0]=a;
	int i;
	for(i=1;i<8;i++){
		if(BX[i-1] & 0x80){
			BX[i]=BX[i-1]<<1;
			BX[i]^=IRR_POLY8;
		}else
			BX[i]=BX[i-1]<<1;
	}
	i=0;
	int n=1;
	int ret=0;
	while(n){
		if(n&b) ret^=BX[i];
		i++;
		n<<=1;
	}

	return ret;
}

int GF2sup8_mul16(const int a,const int b)
{
	int i=0;
	int n=1;
	if(!a || !b) return 0;
	int ret=0;
	while(n){
		if(n&b) ret^=(a<<i);
		i++;
		n<<=1;
	}

	return ret;
}

/* a/b ,Return divide number;[a]:dividend,[b]:divisor,[mod]:remainder */
int GF2sup8_divid(const int a,const int b,int * mod)
{
	int ret = 0;
	int c=0;
	int A=a;
	while(A>b){
		c=move_left_by(b,A);
		if(c<0) break;
		setbit(&ret,c);
		//SET_BIT(&ret,c);
		A=(b<<c)^A;
	}
	if(mod)
		*mod=A;
	return ret;
}

/* a%b,Return remainder;[a]:dividend,[b]:divisor */
int GF2sup8_mod(const int a,const int b)
{
	int c=0;
	int A=a;
	while(A>b)
	{
		c=move_left_by(b,A);
		if(c<0) break;
		A=(b<<c)^A;
	}
	return A;
}
