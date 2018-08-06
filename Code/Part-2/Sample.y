%{
void yyerror (char *s);     /* C declarations used in actions */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
extern FILE *yyin;
#include "cmp.h"
int i = 0,fnum = 0;
bool ground = false;
bool R[10000],V[10000],Is[10000],L[10000],C[10000];
%}

%union {int num; char *s;}         /* Yacc definitions */
%token er EOL SIN LB RB
%token <s> CAPACITOR INDUCTOR RESISTOR NET RESISTANCE CAPACITANCE INDUCTANCE VOLTAGE CURRENT OFF DEL DAMP FREQUENCY AMP

%%
	line : 	LINE
			| LINE line	
			;

	LINE :	Expression
		| EOL
		;

	Expression : RESISTOR NET NET RESISTANCE EOL 
		{
			int rno = getValue($1);
			int net1 = getNetValue($2);
			int net2 = getNetValue($3);
			double rvalue = atof($4);
			int l = strlen($4);
			if($4[l-1]=='K') rvalue*=1000;
			else if($4[l-1]=='M') rvalue/=1000;
			else if($4[l-1]=='U') rvalue/=1000000;
			else if($4[l-1]=='N') rvalue/=1000000000;
			if(net1>9999||net2>9999)
			{
				printf("Net value must be between 0-9999\n");
				return 0;
			}
			if(rno>9999)
			{
				printf("Resistor Number must be between 0-9999\n");
				return 0;
			}
			if(net1==net2)
			{
				printf("Net values cannot be same %d\n",net1);
				return 0;
			}
			if(R[rno]==true)
			{
				printf("R%d being used more than once\n",rno);
				return 0;
			}
			R[rno] = true;
			if(net1!=-1)
			{
				Net[net1+1].ingoing[Net[net1+1].insize]=i;
				Net[net1+1].insize++;
			}
			else ground = true;
			if(net2!=-1)
			{
				Net[net2+1].outgoing[Net[net2+1].outsize]=i;
				Net[net2+1].outsize++;
			}
			else ground = true;
			strcpy(Net[net1+1].fname,$2);
			strcpy(Net[net2+1].fname,$3);
			components[i].type = 'R';
			components[i].num = rno;
			components[i].drawn = false;
			components[i].net1 = net1;
			components[i].net2 = net2;
			components[i].value = rvalue;
			
			strcat(components[i].name,$1);
			strcat(components[i].name," ");
			strcat(components[i].name,$4);
			i++;
		}
	|INDUCTOR NET NET INDUCTANCE EOL 
		{
			int lno = getValue($1);
			int net1 = getNetValue($2);
			int net2 = getNetValue($3);
			double lvalue = atof($4);
			int l = strlen($4);
			if($4[l-2]=='K') lvalue*=1000;
			else if($4[l-2]=='M') lvalue/=1000;
			else if($4[l-2]=='U') lvalue/=1000000;
			else if($4[l-2]=='N') lvalue/=1000000000;
			if(net1>9999||net2>9999)
			{
				printf("Net value must be between 0-9999\n");
				return 0;
			}
			if(lno>9999)
			{
				printf("Inductor Number must be between 0-9999\n");
				return 0;
			}
			if(net1==net2)
			{
				printf("Net values cannot be same %d\n",net1);
				return 0;
			}
			if(L[lno]==true)
			{
				printf("L%d being used more than once\n",lno);
				return 0;
			}
			L[lno] = true;
			if(net1!=-1)
			{
				Net[net1+1].ingoing[Net[net1+1].insize]=i;
				Net[net1+1].insize++;
			}
			else ground = true;
			if(net2!=-1)
			{
				Net[net2+1].outgoing[Net[net2+1].outsize]=i;
				Net[net2+1].outsize++;
			}
			else ground = true;
			strcpy(Net[net1+1].fname,$2);
			strcpy(Net[net2+1].fname,$3);
			components[i].type = 'L';
			components[i].num = lno;
			components[i].drawn = false;
			components[i].net1 = net1;
			components[i].net2 = net2;
			components[i].value = lvalue;
			
			strcat(components[i].name,$1);
			strcat(components[i].name," ");
			strcat(components[i].name,$4);
			i++;
		}
	
	|CAPACITOR NET NET CAPACITANCE EOL
		{
			int cno = getValue($1);
			int net1 = getNetValue($2);
			int net2 = getNetValue($3);
			double cvalue = atof($4);
			int l = strlen($4);
			if($4[l-2]=='K') cvalue*=1000;
			else if($4[l-2]=='M') cvalue/=1000;
			else if($4[l-2]=='U') cvalue/=1000000;
			else if($4[l-2]=='N') cvalue/=1000000000;
			if(net1>9999||net2>9999)
			{
				printf("Net value must be between 0-9999\n");
				return 0;
			}
			if(cno>9999)
			{
				printf("Inductor Number must be between 0-9999\n");
				return 0;
			}
			if(net1==net2)
			{
				printf("Net values cannot be same %d\n",net1);
				return 0;
			}
			if(C[cno]==true)
			{
				printf("L%d being used more than once\n",cno);
				return 0;
			}
			C[cno] = true;
			if(net1!=-1)
			{
				Net[net1+1].ingoing[Net[net1+1].insize]=i;
				Net[net1+1].insize++;
			}
			else ground = true;
			if(net2!=-1)
			{
				Net[net2+1].outgoing[Net[net2+1].outsize]=i;
				Net[net2+1].outsize++;
			}
			else ground = true;
			strcpy(Net[net1+1].fname,$2);
			strcpy(Net[net2+1].fname,$3);
			components[i].type = 'C';
			components[i].num = cno;
			components[i].drawn = false;
			components[i].net1 = net1;
			components[i].net2 = net2;
			components[i].value = cvalue;
			
			strcat(components[i].name,$1);
			strcat(components[i].name," ");
			strcat(components[i].name,$4);
			i++;
		}

	|VOLTAGE NET NET SIN LB OFF AMP FREQUENCY DEL DAMP RB EOL
		{
			int vno = getValue($1);
			int net1 = getNetValue($2);
			int net2 = getNetValue($3);
			double offset = atof($6);
			double amp = atof($7);
			double frequency = atof($8);
			if($8[strlen($8)-3]=='K') frequency*=1000;
			else if($8[strlen($8)-3]=='M') frequency/=1000;
			else if($8[strlen($8)-3]=='U') frequency/=1000000;
			else if($8[strlen($8)-3]=='N') frequency/=1000000000;
			double delay = atof($9);
			double damp = atof($10);
			if(net1>9999||net2>9999)
			{
				printf("Net value must be between 0-9999\n");
				return 0;
			}
			if(vno>9999)
			{
				printf("Voltage Source Number must be between 0-9999\n");
				return 0;
			}
			if(net1==net2)
			{
				printf("Net values cannot be same %d\n",net1);
				return 0;
			}
			if(V[vno]==true)
			{
				printf("V%d being used more than once\n",vno);
				return 0;
			}
			V[vno] = true;
			if(net1!=-1)
			{
				Net[net1+1].ingoing[Net[net1+1].insize]=i;
				Net[net1+1].insize++;
			}
			else ground = true;
			if(net2!=-1)
			{
				Net[net2+1].outgoing[Net[net2+1].outsize]=i;
				Net[net2+1].outsize++;
			}
			else ground = true;
			strcpy(Net[net1+1].fname,$2);
			strcpy(Net[net2+1].fname,$3);
			//printf("%lf\n",cvalue);
			components[i].type = 'V';
			components[i].num = vno;
			components[i].drawn = false;
			components[i].net1 = net1;
			
			components[i].net2 = net2;
			components[i].offset = offset;
			components[i].frequency = frequency;
			addfreq(frequency,freq,&fnum);
			if(offset>0) addfreq(0,freq,&fnum);
			components[i].value = amp;
			components[i].delay = delay;
			components[i].dfactor = damp;
			strcat(components[i].name,$1);
			strcat(components[i].name," ");
			strcat(components[i].name,"SINE ( ");
			strcat(components[i].name,$6);
			strcat(components[i].name," ");
			strcat(components[i].name,$7);
			strcat(components[i].name," ");
			strcat(components[i].name,$8);
			strcat(components[i].name," ");
			strcat(components[i].name,$9);
			strcat(components[i].name," ");
			strcat(components[i].name,$10);
			strcat(components[i].name," )");
			i++;
		}
		|VOLTAGE NET NET SIN LB OFF AMP FREQUENCY DEL RB EOL
		{
			int vno = getValue($1);
			int net1 = getNetValue($2);
			int net2 = getNetValue($3);
			double offset = atof($6);
			double amp = atof($7);
			double frequency = atof($8);
			if($8[strlen($8)-3]=='K') frequency*=1000;
			else if($8[strlen($8)-3]=='M') frequency/=1000;
			else if($8[strlen($8)-3]=='U') frequency/=1000000;
			else if($8[strlen($8)-3]=='N') frequency/=1000000000;
			double delay = atof($9);
			double damp = 0;
			if(net1>9999||net2>9999)
			{
				printf("Net value must be between 0-9999\n");
				return 0;
			}
			if(vno>9999)
			{
				printf("Voltage Source Number must be between 0-9999\n");
				return 0;
			}
			if(net1==net2)
			{
				printf("Net values cannot be same %d\n",net1);
				return 0;
			}
			if(V[vno]==true)
			{
				printf("V%d being used more than once\n",vno);
				return 0;
			}
			V[vno] = true;
			if(net1!=-1)
			{
				Net[net1+1].ingoing[Net[net1+1].insize]=i;
				Net[net1+1].insize++;
			}
			else ground = true;
			if(net2!=-1)
			{
				Net[net2+1].outgoing[Net[net2+1].outsize]=i;
				Net[net2+1].outsize++;
			}
			else ground = true;
			//printf("%lf\n",cvalue);
			strcpy(Net[net1+1].fname,$2);
			strcpy(Net[net2+1].fname,$3);
			components[i].type = 'V';
			components[i].num = vno;
			components[i].drawn = false;
			components[i].net1 = net1;
			components[i].net2 = net2;
			components[i].offset = offset;
			components[i].frequency = frequency;
			addfreq(frequency,freq,&fnum);
			if(offset>0) addfreq(0,freq,&fnum);
			components[i].value = amp;
			
			components[i].delay = delay;
			components[i].dfactor = damp;
			strcat(components[i].name,$1);
			strcat(components[i].name," ");
			strcat(components[i].name,"SINE ( ");
			strcat(components[i].name,$6);
			strcat(components[i].name," ");
			strcat(components[i].name,$7);
			strcat(components[i].name," ");
			strcat(components[i].name,$8);
			strcat(components[i].name," ");
			strcat(components[i].name,$9);
			strcat(components[i].name," )");
			i++;
		}
	|CURRENT NET NET SIN LB OFF AMP FREQUENCY DEL DAMP RB EOL
		{
			int vno = getValue($1);
			int net1 = getNetValue($2);
			int net2 = getNetValue($3);
			double offset = atof($6);
			double amp = atof($7);
			double frequency = atof($8);
			if($8[strlen($8)-3]=='K') frequency*=1000;
			else if($8[strlen($8)-3]=='M') frequency/=1000;
			else if($8[strlen($8)-3]=='U') frequency/=1000000;
			else if($8[strlen($8)-3]=='N') frequency/=1000000000;
			double delay = atof($9);
			double damp = atof($10);
			if(net1>9999||net2>9999)
			{
				printf("Net value must be between 0-9999\n");
				return 0;
			}
			if(vno>9999)
			{
				printf("Voltage Source Number must be between 0-9999\n");
				return 0;
			}
			if(net1==net2)
			{
				printf("Net values cannot be same %d\n",net1);
				return 0;
			}
			if(Is[vno]==true)
			{
				printf("Is%d being used more than once\n",vno);
				return 0;
			}
			Is[vno] = true;
			if(net1!=-1)
			{
				Net[net1+1].ingoing[Net[net1+1].insize]=i;
				Net[net1+1].insize++;
			}
			else ground = true;
			if(net2!=-1)
			{
				Net[net2+1].outgoing[Net[net2+1].outsize]=i;
				Net[net2+1].outsize++;
			}
			else ground = true;
			//printf("%lf\n",cvalue);
			strcpy(Net[net1+1].fname,$2);
			strcpy(Net[net2+1].fname,$3);
			components[i].type = 'I';
			components[i].num = vno;
			components[i].drawn = false;
			components[i].net1 = net1;
			components[i].net2 = net2;
			components[i].offset = offset;
			components[i].frequency = frequency;
			addfreq(frequency,freq,&fnum);
			if(offset>0) addfreq(0,freq,&fnum);
			components[i].value = amp;
			
			components[i].delay = delay;
			components[i].dfactor = damp;
			strcat(components[i].name,$1);
			strcat(components[i].name," ");
			strcat(components[i].name,"SINE ( ");
			strcat(components[i].name,$6);
			strcat(components[i].name," ");
			strcat(components[i].name,$7);
			strcat(components[i].name," ");
			strcat(components[i].name,$8);
			strcat(components[i].name," ");
			strcat(components[i].name,$9);
			strcat(components[i].name," ");
			strcat(components[i].name,$10);
			strcat(components[i].name," )");
			i++;
		}
		|CURRENT NET NET SIN LB OFF AMP FREQUENCY DEL RB EOL
		{
			int vno = getValue($1);
			int net1 = getNetValue($2);
			int net2 = getNetValue($3);
			double offset = atof($6);
			double amp = atof($7);
			double frequency = atof($8);
			if($8[strlen($8)-3]=='K') frequency*=1000;
			else if($8[strlen($8)-3]=='M') frequency/=1000;
			else if($8[strlen($8)-3]=='U') frequency/=1000000;
			else if($8[strlen($8)-3]=='N') frequency/=1000000000;
			double delay = atof($9);
			double damp = 0;
			if(net1>9999||net2>9999)
			{
				printf("Net value must be between 0-9999\n");
				return 0;
			}
			if(vno>9999)
			{
				printf("Voltage Source Number must be between 0-9999\n");
				return 0;
			}
			if(net1==net2)
			{
				printf("Net values cannot be same %d\n",net1);
				return 0;
			}
			if(Is[vno]==true)
			{
				printf("Is%d being used more than once\n",vno);
				return 0;
			}
			Is[vno] = true;
			if(net1!=-1)
			{
				Net[net1+1].ingoing[Net[net1+1].insize]=i;
				Net[net1+1].insize++;
			}
			else ground = true;
			if(net2!=-1)
			{
				Net[net2+1].outgoing[Net[net2+1].outsize]=i;
				Net[net2+1].outsize++;
			}
			else ground = true;
			strcpy(Net[net1+1].fname,$2);
			strcpy(Net[net2+1].fname,$3);
			//printf("%lf\n",cvalue);
			components[i].type = 'I';
			components[i].num = vno;
			components[i].drawn = false;
			components[i].net1 = net1;
			components[i].net2 = net2;
			components[i].offset = offset;
			components[i].frequency = frequency;
			addfreq(frequency,freq,&fnum);
			if(offset>0) addfreq(0,freq,&fnum);
			components[i].value = amp;
			components[i].delay = delay;

			components[i].dfactor = damp;
			strcat(components[i].name,$1);
			strcat(components[i].name," ");
			strcat(components[i].name,"SINE ( ");
			strcat(components[i].name,$6);
			strcat(components[i].name," ");
			strcat(components[i].name,$7);
			strcat(components[i].name," ");
			strcat(components[i].name,$8);
			strcat(components[i].name," ");
			strcat(components[i].name,$9);
			strcat(components[i].name," )");
			i++;
		}
	|er {printf("Error in syntax\n");return 0;}
	;

%%                     /* C code */

int main (int argc,char *argv[]) 
{
	if(argc !=4 )
    {
        fprintf(stderr, "3 args required! Now %d arguments\n",argc);
        return 0;
    }
    bool brk = false;
    printf("%s\n",argv[1]);
    yyin = fopen(argv[1],"r");
    FILE *results = fopen(argv[3],"w");
    FILE *draw = fopen(argv[2],"w");
    do
    {	
    	yyparse ( );
    }while(!feof(yyin));

	if(!ground)
	{
		printf("Error! Ground Net not included in the circuit\n");
		return 0;
	}
	for(int i=1;i<10005;i++)
	{
		if(Net[i].insize+Net[i].outsize==1)
		{
			printf("Error in file. Net %d is connected to just one component\n",i-1);
			brk = true;
			break;
		}
	}
	if(brk) return 0;
	int size = Seperate();//Assigns x co-ordinates to the Nets based on whether they are present in the circuit or not. Also, it is for seperating present nets in the circuit from 1-9999
	drawcircuit(draw,i,size);//Renders the SVG Based on pre obtained data
	int k = i;
	for(int i=0;i<fnum;i++){
    fprintf(results,"FREQ=%.3lfKhz\n",freq[i]/1000);
    printsoln(results,getsoln(NetinC,components,k,size,freq[i]),components,k);
  }  
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);} 