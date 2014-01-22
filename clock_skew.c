#include<stdio.h>
//reference Estimation and removal of clock skew from network delay measurements
//by SB Moon, P Skelly, D Towsley
/*
procedure: IN(di,ti,N), out(alpha, beta)
n1=1, n2=2, k=2
for i=3 to N
	for j=k downto 2
	    if intersection_x(ti, -di, t_nj, -d_nj)>intersection_x(t_nj,-d_nj,t_nj-1, -d_nj-1
		greak;
	    endif
	endfor
        k=j+1,nk=i
endfor
opt=sum_i ti/N
FOR i=1 to k 
     IF tni<opt and opt<tni+1
	alpha-1=intersection_x(tni,-dni,tni+1,-dni+1)
	beta=intersection_y(tni,-dni,tni+1,-dni+1)
     ENDIF
ENDFOR
ENDPROCEDURE
*/
double  alpha, beta;
double intersection_x(double a1, double b1, double a2, double b2)
{
	if(a1==a2)
	return 0;
	else
	return (b1-b2)/(a2-a1);
}
double intersection_y(double a1, double b1, double a2, double b2)
{
	if(a1==a2)
	return 0;
	else
	return a1*(b1-b2)/(a2-a1)+b1;
}

#define MAXMEASURE 1000
int linearP(double delay[], double time[],int N)
{
//double alpha, beta;
int n[MAXMEASURE], k;
int i,j,start=0;
n[1]=1;
n[2]=2;
k=2;
double sum=time[1]+time[2];
//for(i=1;i<N;i++)
//  printf("%f,%f\n",delay[i],time[i]);
for (i=3;i<=N;i++)
{
	for(j=k;j>=2;j--)
	{
		if (j==1||intersection_x(time[i],-delay[i],time[n[j]],-delay[n[j]])
		>intersection_x(time[n[j]],-delay[n[j]],time[n[j-1]],-delay[n[j-1]]))
		break;
	}
	k=j+1;
	n[k]=i;
	sum+=time[i];
}
double opt=sum/N;
for (i=1 ;i<k;i++)
{
	printf("n%d=%d\n",i,n[i]);
	if(time[n[i]]<opt  &&  opt<time[n[i+1]])
	{
		alpha=intersection_x(time[n[i]],-delay[n[i]],time[n[i+1]],-delay[n[i+1]]);
		beta=intersection_y(time[n[i]],-delay[n[i]],time[n[i+1]],-delay[n[i+1]]);
		break;
	}
}
printf("alpha=%f,beta=%f\n",alpha,beta);
for(i=1;i<N;i++)
  if(delay[i]-(alpha-1)*time[i]+beta<0)
  {
    printf("error %d\n",i);
  }
return 0;
}
int main()
{
double  a[]={1,2,3,4,5,6};
double  b[]={100.1,102.1, 103.2, 104.4, 105.41, 106.52};
linearP(a,b,5);
printf("%lf, %lf\n",alpha, beta);
return 0;
}
