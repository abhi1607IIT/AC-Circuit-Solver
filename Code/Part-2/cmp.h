#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<complex.h>
#include "SvgHelper.h"

double freq[10000] = {0};

typedef struct
{
	char type;
	char fname[6];
	int num;
	bool drawn;
 	int net1;
 	int net2;
 	double value;
 	double frequency;
	double offset;
	double delay;
	double dfactor;
	char name[50];
}element;


element components[50000];

typedef struct
{
	int num;
	int pos;
	int ingoing[100];
	int outgoing[100];
	int insize;
	int outsize;
	char fname[10];
} net;

net Net[10005],NetinC[10005];

int yc[10005];

double complex* solve_matrix(double complex* matrix1,double complex* matrix2,int rows,int columns);

void printmatrix(double complex* A,int rows,int columns);

void printsoln(FILE* o,double complex* A,element e[],int size);


int findfreq(double A[],int size,double frequency){
	for (int i = 0; i < size; i++)
	{
		if(A[i]==frequency)
			return i;
	}
	return -1;
}

void addfreq(double frequency,double A[],int* size){
	if(findfreq(A,*size,frequency)!=-1)
		return;
	A[*size]=frequency;
	*size=*size+1;
}


void seteq1(int m,double complex* A,int p,int q,double complex*  B,int x,int y)
{
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			A[(x+i)*m+(y+j)]=B[(i*q)+j];
		}
	}

}


void seteq2(int m,double complex* A,int p,int q,double complex*  B,int x,int y)
{
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < q; j++)
		{
			A[(x+j)*m+(y+i)]=-B[(i*q)+j];
		}
	}

}

void init_matrix(double complex* A,int r,int c){
	for (int i = 0; i < r*c; i++)
	{
		A[i]=0;
	}
}
double complex*  getsoln(net v[],element e[],int nb,int nv,double frequency){
	double complex* M = (double complex*)malloc(sizeof(double complex)*((2*nb+nv)*(2*nb+nv)));

	double complex* A = (double complex*)malloc(sizeof(double complex)*(nb*(nv)));
	//printf("Yeah\n");

	init_matrix(M,2*nb+nv,2*nb+nv);
	init_matrix(A,nv,nb);

	int j1=0,j2=0;
	for (int i = 0; i < nv; i++)
	{
		while(j1<v[i].insize){
			//printf("%s456\n",v[i].name);
			A[nb*i+v[i].ingoing[j1]]=1;
			j1++;
		}

		while(j2<v[i].outsize){
			A[nb*i+v[i].outgoing[j2]]=-1;
			j2++;
		}
		j1=0;
		j2=0;
			
	}

	double complex* Iden = (double complex*)malloc(sizeof(double complex)*(nb*(nb)));
	init_matrix(Iden,nb,nb);
	double complex* Y = (double complex*)malloc(sizeof(double complex)*(nb*(nb)));
	double complex* Z = (double complex*)malloc(sizeof(double complex)*(nb*(nb)));
	double complex* Var = (double complex*)malloc(sizeof(double complex)*(2*nb+nv));
	init_matrix(Y,nb,nb);
	init_matrix(Z,nb,nb);
	init_matrix(Var,2*nb+nv,1);
	


	seteq1(2*nb+nv,M,nv,nb,A,0,0);
	float pi=acos(-1);

	for (int i = 0; i < nb; i++)
	{
		Iden[i*nb+i]=1;
		if(e[i].type=='R'){
			Y[i*nb+i]=1;
			Z[i*nb+i]=e[i].value;		
		}

		if(e[i].type=='L'){
			Y[i*nb+i]=1;
			Z[i*nb+i]=2*pi*frequency*e[i].value*I;		
		}

		if(e[i].type=='C'){
			Z[i*nb+i]=1;
			Y[i*nb+i]=2*pi*frequency*e[i].value*I;		
		}

		if(e[i].type=='V'){
			Y[i*nb+i]=1;
			Z[i*nb+i]=0;

			Var[nb+nv+i]=0;
			
			if(frequency==0)
			Var[nb+nv+i]= e[i].offset;
			
			if(frequency==e[i].frequency)
			Var[nb+nv+i]= e[i].value*(cos(-2*pi*frequency*e[i].delay)+sin(-2*pi*frequency*e[i].delay)*I);


		}

		if(e[i].type=='I'){
			Z[i*nb+i]=1;
			Y[i*nb+i]=0;

			Var[nb+nv+i]=0;

			if(frequency==0)
			Var[nb+nv+i]= e[i].offset;
			
			if(frequency==e[i].frequency)
			Var[nb+nv+i]= e[i].value*(cos(-2*pi*frequency*e[i].delay)+sin(-2*pi*frequency*e[i].delay)*I);
		}
	}
	seteq1(2*nb+nv,M,nb,nb,Iden,nv,nb);
	seteq2(2*nb+nv,M,nv,nb,A,nv,2*nb);
	seteq1(2*nb+nv,M,nb,nb,Z,nb+nv,0);
	seteq1(2*nb+nv,M,nb,nb,Y,nb+nv,nb);
	return solve_matrix(M,Var,2*nb+nv,2*nb+nv+1);





}

void swap(double complex*A,int i,int j,int rows,int columns){
	double complex temp=0;
	for (int z = 0; z < columns;z++)
	{
		temp=A[i*columns+z];
		A[i*columns+z]=A[j*columns+z];
		A[j*columns+z]=temp;

	}
}

double complex* solve_matrix(double complex* matrix1,double complex* matrix2,int rows,int columns){
	double complex* matrix = (double complex*)malloc(sizeof(double complex)*(rows*columns));

	for (int i = 0; i < rows;i++)
	{
		for (int j = 0; j < columns-1;j++)
		{
			matrix[i*columns + j] = matrix1[i*(columns-1) + j] ;
		}
	}
	for (int i = 0; i < columns; ++i)
	{
		matrix[(  (i)*columns) + columns-1] = matrix2[i]; 
			
	}

//	printmatrix(matrix,rows,columns);

	if(rows < columns-1) return NULL;
	int i,j,k;
	double complex factor,temp;

	int invalid = 0;
	for(i=0;i<rows;i++){	
		if(creal(matrix[i*columns + i]) == 0 && cimag(matrix[i*columns + i])==0){
			for (int zeta = i+1; zeta < rows; zeta++)
			{
				if((creal(matrix[zeta*columns + i]) != 0 || cimag(matrix[zeta*columns + i])!=0)){
					swap(matrix,i,zeta,rows,columns);
					//printf("%d\n",zeta );

					break;
				}


			}
		}
		double complex temp=matrix[i*columns+i];

		for (int mega = 0; mega < columns; mega++)
		{
			matrix[i*columns+mega]=matrix[i*columns+mega]/temp;
		}

		//printf("\n");
		//printmatrix(matrix,rows,columns);
		//printf("\n");
		for(k=0;k<rows;k++){
			if(k == i) continue;
			factor = (matrix[k*columns + i]);
			for(j=0;j<columns;j++){
				temp = (matrix[i*columns + j]*factor);
				matrix[k*columns + j] = (matrix[k*columns + j]-temp);
			}
		}
	}
	//printf("\n");
	//printmatrix(matrix,rows,columns);
	//printf("invalid=%d\n",invalid );
	double complex* solution = (double complex*)malloc(sizeof(double complex)*(rows-invalid));
	for(i=0;i<rows-invalid;i++){
		if(creal(matrix[i*columns + i]) == 0 && cimag(matrix[i*columns + i])==0) continue;
		solution[i] = (matrix[i*columns + (columns-1)]/matrix[i*columns + i]);
	}


	return solution;
}

void arraysort(double A[],int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if(A[i]>A[j]){
				double temp = A[i];
				A[i]=A[j];
				A[j]=temp;
			}
		}
	}
}

void printmatrix(double complex* A,int rows,int columns)
{
	for (int i = 0; i < rows;i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%.1lf,%.9lf ",creal(A[i*columns+j]),cimag(A[i*columns+j]) );
		}
		printf("\n");
	}
}

void printsoln(FILE* o,double complex* A,element e[],int size){
	float pi = acos(-1);
	//printf("pi=%f\n",pi);
	
	fprintf(o,"VOLTAGES\n");
	for (int i = size; i < 2*size; i++)
	{
		double amp = sqrt(creal(A[i])*creal(A[i])+cimag(A[i])*cimag(A[i]));
		
		double ang=0;
		
		 ang = 180*atan(cimag(A[i])/creal(A[i]))/pi;
		if(fabs(creal(A[i]))<=pow(10,-15))
			ang=90;

		if(fabs(cimag(A[i]))<=pow(10,-15))
			ang=0;



		fprintf(o,"%c%d %.3lf %.3lf \n",e[i-size].type,e[i-size].num,amp,ang);
		//printf("V=%.12lf,%.12lf\n ",creal(A[i]),cimag(A[i]) );

	}
	fprintf(o,"\n");
	fprintf(o,"CURRENTS\n");
	
	for (int i = 0; i < size; i++)
	{
		double amp = sqrt(creal(A[i])*creal(A[i])+cimag(A[i])*cimag(A[i]));
		double ang=0;
		
		 ang = 180*atan(cimag(A[i])/creal(A[i]))/pi;
		if(fabs(creal(A[i]))<=pow(10,-15))
			ang=90;

		if(fabs(cimag(A[i]))<=pow(10,-15))
			ang=0;

		fprintf(o,"%c%d %.3lf %.3lf \n",e[i].type,e[i].num,amp,ang);
		//printf("I=%.12lf,%.12lf\n ",creal(A[i]),cimag(A[i]) );
	}


	fprintf(o,"\n");
	fprintf(o,"\n");
}

int getNetValue(char *s)
{
	if(s[0]=='0') return -1;
	else
	{
		int ans = 0;
		for(int i=3;i<strlen(s);i++)
		{
			ans*=10;
			ans+=(s[i]-'0');
		}
		return ans;
	}
}

int getValue(char *s)
{
	int ans = 0;
	for(int i=1;i<strlen(s);i++)
	{
		ans*=10;
		ans+=(s[i]-'0');
	}
	return ans;
}

int Seperate()
{
	int xc = 1,j = 0;
	for(int i=1;i<10001;i++)
	{
		Net[i].num = i;
		if(Net[i].insize+Net[i].outsize>0)
		{
			Net[i].pos = xc;
			NetinC[j] = Net[i];
			j++;
			xc++;
		}
	}
	return j;
}
int min(int a,int b)
{
	if(a<b) return a;
	else return b;	
}
int max(int a,int b)
{
	if(a>b) return a;
	else return b;
}
int cmp(const void* x,const void* y)
{
	
	element *a = (element *)x;
	element *b = (element *)y;
	if(min(a->net1,a->net2)==min(b->net1,b->net2)) return max(a->net1,a->net2) - max(b->net1,b->net2);
	else return min(a->net1,a->net2) - min(b->net1,b->net2);
}
void sortelements(element e[],int n)
{
	qsort(e,n,sizeof(element),cmp);
}
void drawcircuit(FILE* fl, int size,int w)
{
	int y = 1,drawn = 0;
	for(int i=0;i<10005;i++)
	{
		yc[i] = -1;
	}
	start_svg(size+3,w+1,fl);
	sortelements(components,size);
	while(drawn!=size)
	{
		int i = 0,pnet = -1;
		while(i!=size)
		{
			if(components[i].drawn == false&&min(components[i].net1,components[i].net2)>=pnet )
			{
				if(components[i].net1<components[i].net2) make_element_horizontal(Net[components[i].net1+1].pos,y,Net[components[i].net2+1].pos,y,components[i].type,components[i].name,fl);
				else make_element_horizontal(Net[components[i].net2+1].pos,y,Net[components[i].net1+1].pos,y,components[i].type,components[i].name,fl);
				if(yc[components[i].net1+1]>0) draw_line(Net[components[i].net1+1].pos,yc[components[i].net1+1],Net[components[i].net1+1].pos,y,fl); 
				if(yc[components[i].net2+1]>0) draw_line(Net[components[i].net2+1].pos,yc[components[i].net2+1],Net[components[i].net2+1].pos,y,fl);
				yc[components[i].net1+1] = y;
				yc[components[i].net2+1] = y;
				pnet = max(components[i].net1,components[i].net2);
				components[i].drawn = true;
				drawn++;
			}
			i++;
		}
		y++;
	}
	strcpy(NetinC[0].fname,"0");
	//printf("%d\n",w+1);
	draw_ground(0,yc[0],fl);
	for(int i=0;i<w;i++)
	{
		draw_net_text_vertical(i+1,yc[NetinC[i].num],0,Net[NetinC[i].num].fname,fl);
	}
	end_svg(fl);
}