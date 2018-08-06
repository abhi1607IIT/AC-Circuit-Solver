%{
#include "Sample.tab.h"
%}

number [0-9]+
value [0-9]*("."{number})?
unit [UNMK]
resistance {value}({unit})?
capacitance {value}{unit}?[Ff]
inductance {value}{unit}?[hH]
name [a-zA-Z][a-zA-Z0-9]*
suffix [a-zA-Z0-9_]+

%s NET1
%s NET2
%s CVALUE
%s END
%s OFFSET
%s AMPLITUDE
%s FREQ
%s DELAY
%s DAMPF
%s LEFT
%s RIGHT


%%

[ ]+ { }
<INITIAL>[V]{number} {yylval.s = strdup(yytext);BEGIN NET1;return VOLTAGE;}
<INITIAL>[I]{number} {yylval.s = strdup(yytext);BEGIN NET1;return CURRENT;}
<INITIAL>[R]{number} {yylval.s = strdup(yytext);BEGIN NET1;return RESISTOR;}
<INITIAL>[L]{number} {yylval.s = strdup(yytext);BEGIN NET1;return INDUCTOR;}
<INITIAL>[C]{number} {yylval.s = strdup(yytext);BEGIN NET1;return CAPACITOR;}
<NET1>[0]|([Nn][eE][tT]){number} {yylval.s = strdup(yytext);BEGIN NET2;return NET;}
<NET2>[0]|([Nn][eE][tT]){number} {yylval.s = strdup(yytext);BEGIN CVALUE;return NET;}
<CVALUE>[S][I][N][E] {BEGIN LEFT;return SIN;}
<CVALUE>{resistance} {yylval.s = strdup(yytext);BEGIN END;return RESISTANCE;}
<CVALUE>{inductance} {yylval.s = strdup(yytext);BEGIN END;return INDUCTANCE;}
<CVALUE>{capacitance} {yylval.s = strdup(yytext);BEGIN END;return CAPACITANCE;}
<LEFT>[/(] {BEGIN OFFSET;return LB;}
<OFFSET>{value}	{yylval.s = strdup(yytext);BEGIN AMPLITUDE;return OFF;}
<AMPLITUDE>{value}	{yylval.s = strdup(yytext);BEGIN FREQ;return AMP;}
<FREQ>{value}{unit}?[hH][zZ] {yylval.s = strdup(yytext);BEGIN DELAY;return FREQUENCY;}
<DELAY>{value}[sS] {yylval.s = strdup(yytext);BEGIN DAMPF;return DEL;}
<DAMPF>{value} {yylval.s = strdup(yytext);BEGIN RIGHT;return DAMP;}
<DAMPF>[/)] {BEGIN END;return RB;}
<RIGHT>[/)] {BEGIN END;return RB;}
<END>[\n] {BEGIN INITIAL;return EOL;}
. {yyerror("Error in Syntax\n");return er;}
	
%%
int yywrap (void) {return 1;}