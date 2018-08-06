#include <stdio.h>
#include <assert.h>

float LINE_WIDTH=0.03;
float CIRCLE_WIDTH=0.05;
float WIDTH = 1500;
float HEIGHT = 900;
char* arr[20005];

enum component_type { resistor, inductor, capacitor, voltage, current };

void start_svg(int rows, int cols, FILE* ptr);
void draw_line(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_circle(int x,int y, FILE* ptr);
void end_svg(FILE* ptr);
void place_resistor_vertical(int x, int y, FILE* ptr);
void place_resistor_horizontal(int x, int y, FILE* ptr);
void place_capacitor_vertical(int x, int y, FILE* ptr);
void place_capacitor_horizontal(int x, int y, FILE* ptr);
void place_inductor_vertical(int x, int y, FILE* ptr);
void place_inductor_horizontal(int x, int y, FILE* ptr);
void place_ac_vertical(int x,int y, FILE* ptr);
void place_ac_horizontal(int x,int y, FILE* ptr);
void place_current_vertical(int x,int y, FILE* ptr);
void place_current_horizontal(int x,int y, FILE* ptr);
void draw_resistor_vertical(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_resistor_horizontal(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_capacitor_vertical(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_capacitor_horizontal(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_inductor_vertical(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_inductor_horizontal(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_ac_vertical(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_ac_horizontal(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_current_vertical(int x1,int y1, int x2, int y2,FILE* ptr);
void draw_current_horizontal(int x1,int y1, int x2, int y2,FILE* ptr);
void make_element_vertical(int x1,int y1,int x2,int y2,enum component_type type,char* name, FILE* ptr);
void make_element_horizontal(int x1,int y1,int x2,int y2,enum component_type type,char* name, FILE* ptr);
void place_text_vertical(int x,int y, float off_x,char* text, char* color, FILE* ptr);
void place_text_horizontal(int x,int y, float off_x,char* text, char* color, FILE* ptr);
void draw_text_vertical(int x, int y, char* text, enum component_type type, FILE* ptr);
void draw_text_horizontal(int x, int y, char* text, enum component_type type, FILE* ptr);
void draw_net_text_vertical(int x, int y, int is_up,char* text, FILE* ptr);
void draw_net_text_horizontal(int x, int y, int is_up,char* text, FILE* ptr);
void draw_ground_vertical(int x,int y, FILE* ptr);


void start_svg(int rows, int cols, FILE* ptr)
{
	fprintf(ptr, "<svg width=\"%f\" height=\"%f\" viewBox=\"-1.25 -1.25 %d %d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" onload=\"init(evt)\">\n",WIDTH,HEIGHT,(cols+1),(rows+1));
}

void draw_line(int x1,int y1, int x2, int y2,FILE* ptr)
{
	if(x1==x2 && y1==y2) { return ; }
	fprintf(ptr, "<line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke-width=\"%f\" stroke=\"black\"/>\n",x1,x2,y1,y2,LINE_WIDTH);
}
void draw_circle(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<circle cx=\"%d\" cy=\"%d\" r=\"%f\"/>\n",x,y,CIRCLE_WIDTH);
}

void end_svg(FILE* ptr)
{
	fprintf(ptr, "</svg>\n");
}

void draw_resistor_vertical(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text_vertical(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_vertical(x2,y2,0,arr[y2],ptr);
	place_resistor_vertical(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_capacitor_vertical(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text_vertical(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_vertical(x2,y2,0,arr[y2],ptr);
	place_capacitor_vertical(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_inductor_vertical(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text_vertical(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_vertical(x2,y2,0,arr[y2],ptr);
	place_inductor_vertical(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_ac_vertical(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text_vertical(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_vertical(x2,y2,0,arr[y2],ptr);
	place_ac_vertical(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_current_vertical(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(x1==x2);
	assert(y1<y2);
	draw_circle(x1,y1,ptr);
	draw_net_text_vertical(x1,y1,1,arr[y1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_vertical(x2,y2,0,arr[y2],ptr);
	place_current_vertical(x1,y1,ptr);
	draw_line(x1,y1+1,x2,y2,ptr);
}

void draw_ground(int x,int y, FILE* ptr)
{
	fprintf(ptr, " <g transform=\"translate(%d,%d)\"> <g transform=\"matrix(0.01259861,0,0,0.01413041,-0.15527664,-0.06236267)\"> <path d=\"m 0.5,24.5 24,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 4.5,27.5 16,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 16.5,30.5 -8,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 12.5,24.5 0,-20\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> </g> </g> \n",x,y,(60*LINE_WIDTH),(60*LINE_WIDTH),(60*LINE_WIDTH),(60*LINE_WIDTH));
}

void draw_text_vertical(int x, int y, char* text, enum component_type type, FILE* ptr)
{
	switch(type)
	{
		case resistor:
			place_text_vertical(x,y,0.2,text,"red",ptr);
			break;
		case inductor:
			place_text_vertical(x,y,0.2,text,"green",ptr);
			break;
		case capacitor:
			place_text_vertical(x,y,0.33,text,"blue",ptr);
			break;
		case voltage:
			place_text_vertical(x,y,0.4,text,"brown",ptr);
			break;
		case current:
			place_text_vertical(x,y,0.4,text,"purple",ptr);
			break;
	}
}

void draw_net_text_vertical(int x, int y, int is_up,char* text, FILE* ptr)
{
	float off_y;
	if(is_up)
	{
		off_y = -1.5*CIRCLE_WIDTH;
	}
	else
	{
		off_y = 3.0*CIRCLE_WIDTH;
	}
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" fill=\"black\">%s</text>\n",x-0.15,y+off_y,LINE_WIDTH*4,text);	
}

void place_text_vertical(int x,int y, float off_x,char* text, char* color, FILE* ptr)
{
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" style=\"writing-mode: tb;\" fill=\"%s\">%s</text>\n",x+off_x,y+0.2,LINE_WIDTH*4,color,text);
}

void place_resistor_vertical(int x, int y, FILE* ptr)
{
	fprintf(ptr,"<path d=\" M 0 0 l 0.25 0 l 0.04166666667 -0.08333333334 l 0.08333333334 0.166666666667 l 0.08333333334 -0.166666666667 l 0.08333333334 0.166666666667 l 0.08333333334 -0.166666666667 l 0.08333333334 0.166666666667 l 0.04166666667 -0.08333333334 l 0.25 0 \" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"  transform=\"translate(%d %d) rotate(90)\"/>\n",LINE_WIDTH,x,y);
}

void place_capacitor_vertical(int x, int y, FILE* ptr)
{
	fprintf(ptr," \
	<g transform = \"translate(%d,%d)\"> \
		<path d=\" \
			M 0 0 \
			l 0 0.4 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M -0.25 0.4 \
			l 0.5 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M -0.25 0.6 \
			l 0.5 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M 0 0.6 \
			l 0 0.4 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
 	</g> \
 	",x,y,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH);
}

void place_inductor_vertical(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<path \
		d=\" \
			M 0,0 \
			L 5.5,0 \
			C 5.5,0 5.5,-4 9.5,-4 \
			C 13.5,-4 13.5,0 13.5,0 \
			C 13.5,0 13.5,-4 17.5,-4 \
			C 21.5,-4 21.5,0 21.5,0 \
			C 21.5,0 21.5,-4 25.5,-4 \
			C 29.5,-4 29.5,0 29.5,0 \
			C 29.5,0 29.5,-4 33.5,-4 \
			C 37.5,-4 37.5,0 37.5,0 \
			L 43,0 \
		\" \
		stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"miter\" fill=\"none\" fill-rule=\"evenodd\" fill-opacity=\"0.75\" stroke-linecap=\"butt\" stroke-opacity=\"1\" transform=\"translate(%d,%d) scale(0.02325581395) rotate(90) \" />\n ",(43*LINE_WIDTH),x,y);
}

void place_ac_vertical(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.02125,0.022727272727272728)\"> <g transform=\"translate(-25.08161,-2.992383)\"> <path d=\"m 40,25 c 0,8.284271 -6.715729,15 -15,15 -8.284271,0 -15,-6.715729 -15,-15 0,-8.284271 6.715729,-15 15,-15 8.284271,0 15,6.715729 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\"/> <path d=\"M 25,10 25,3\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25,40 0,7\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 16,25.000005 c 0,0 1.5,-5.000001 4.5,-5.000001 3,0 6,10.000002 9,10.000002 3,0 4.5,-5.000001 4.5,-5.000001\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

void place_current_vertical(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.02125,0.022727272727272728)\"> <g transform=\"translate(-25.08161,-2.992383)\"> <path d=\"m 40,25 c 0,8.284271 -6.715729,15 -15,15 -8.284271,0 -15,-6.715729 -15,-15 0,-8.284271 6.715729,-15 15,-15 8.284271,0 15,6.715729 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\" /> <path d=\"M 25,10 25,3\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25,40 0,7\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 25.136017,23.540261 0,11.951034\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path style=\"fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1\" d=\"m 25.136017,18.552775 -3.210011,4.951033 6.63765,0.05441 z\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

void make_element_vertical(int x1,int y1,int x2,int y2,enum component_type type,char* name,FILE* ptr)
{
	draw_text_vertical(x1,y1,name,type,ptr);
	switch(type)
	{
		case resistor:
			draw_resistor_vertical(x1,y1,x2,y2,ptr);
			break;
		case inductor:
			draw_inductor_vertical(x1,y1,x2,y2,ptr);
			break;
		case capacitor:
			draw_capacitor_vertical(x1,y1,x2,y2,ptr);
			break;
		case voltage:
			draw_ac_vertical(x1,y1,x2,y2,ptr);
			break;
		case current:
			draw_current_vertical(x1,y1,x2,y2,ptr);
			break;
	}
}


void draw_resistor_horizontal(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(y1==y2);
	assert(x1<x2);
	draw_circle(x1,y1,ptr);
	draw_net_text_horizontal(x1,y1,1,arr[x1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_horizontal(x2,y2,0,arr[x2],ptr);
	place_resistor_horizontal(x1,y1,ptr);
	draw_line(x1+1,y1,x2,y2,ptr);
}

void draw_capacitor_horizontal(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(y1==y2);
	assert(x1<x2);
	draw_circle(x1,y1,ptr);
	draw_net_text_horizontal(x1,y1,1,arr[x1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_horizontal(x2,y2,0,arr[x2],ptr);
	place_capacitor_horizontal(x1,y1,ptr);
	draw_line(x1+1,y1,x2,y2,ptr);
}

void draw_inductor_horizontal(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(y1==y2);
	assert(x1<x2);
	draw_circle(x1,y1,ptr);
	draw_net_text_horizontal(x1,y1,1,arr[x1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_horizontal(x2,y2,0,arr[x2],ptr);
	place_inductor_horizontal(x1,y1,ptr);
	draw_line(x1+1,y1,x2,y2,ptr);
}

void draw_ac_horizontal(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(y1==y2);
	assert(x1<x2);
	draw_circle(x1,y1,ptr);
	draw_net_text_horizontal(x1,y1,1,arr[x1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_horizontal(x2,y2,0,arr[x2],ptr);
	place_ac_horizontal(x1,y1,ptr);
	draw_line(x1+1,y1,x2,y2,ptr);
}

void draw_current_horizontal(int x1,int y1, int x2, int y2,FILE* ptr)
{
	assert(y1==y2);
	assert(x1<x2);
	draw_circle(x1,y1,ptr);
	draw_net_text_horizontal(x1,y1,1,arr[x1],ptr);
	draw_circle(x2,y2,ptr);
	draw_net_text_horizontal(x2,y2,0,arr[x2],ptr);
	place_current_horizontal(x1,y1,ptr);
	draw_line(x1+1,y1,x2,y2,ptr);
}


void draw_text_horizontal(int x, int y, char* text, enum component_type type, FILE* ptr)
{
	switch(type)
	{
		case resistor:
			place_text_horizontal(x,y,0.2,text,"red",ptr);
			break;
		case inductor:
			place_text_horizontal(x,y,0.2,text,"green",ptr);
			break;
		case capacitor:
			place_text_horizontal(x,y,0.33,text,"blue",ptr);
			break;
		case voltage:
			place_text_horizontal(x,y,0.4,text,"brown",ptr);
			break;
		case current:
			place_text_horizontal(x,y,0.4,text,"purple",ptr);
			break;
	}
}

void draw_net_text_horizontal(int x, int y, int is_left,char* text, FILE* ptr)
{
	float off_x;
	if(is_left)
	{
		off_x = -1.5*CIRCLE_WIDTH;
	}
	else
	{
		off_x = 3.0*CIRCLE_WIDTH;
	}
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" fill=\"black\">%s</text>\n",x+off_x,y-0.15,LINE_WIDTH*4,text);	
}

void place_text_horizontal(int x,int y, float off_y,char* text, char* color, FILE* ptr)
{
	fprintf(ptr, "<text x = \"%f\" y=\"%f\" font-size=\"%f\" style=\"writing-mode: tb;\" fill=\"%s\">%s</text>\n",x+0.2,y+off_y,LINE_WIDTH*4,color,text);
}

void place_resistor_horizontal(int x, int y, FILE* ptr)
{
	fprintf(ptr,"<path d=\" M 0 0 l 0 -0.25 l -0.08333333334 -0.04166666667 l 0.166666666667 -0.08333333334 l -0.166666666667 -0.08333333334 l 0.166666666667 -0.08333333334 l -0.166666666667 -0.08333333334 l 0.166666666667 -0.08333333334 l -0.08333333334 -0.04166666667 l 0 -0.25 \" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"  transform=\"translate(%d %d) rotate(90)\"/>\n",LINE_WIDTH,x,y);
}

void place_capacitor_horizontal(int x, int y, FILE* ptr)
{
	fprintf(ptr," \
	<g transform = \"translate(%d,%d)\"> \
		<path d=\" \
			M 0 0 \
			l 0.4 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M 0.4 -0.25 \
			l 0 0.5 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M 0.6 -0.25 \
			l 0 0.5 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
		<path d=\" \
			M 0.6 0 \
			l 0.4 0 \
			\" stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"bevel\" fill=\"none\"/> \
 	</g> \
 	",x,y,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH,LINE_WIDTH);
}

void place_inductor_horizontal(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<path \
		d=\" \
			M 0,0 \
			L 0,-5.5 \
			C 0,-5.5 -4,-5.5 -4,-9.5 \
			C -4,-13.5 0,-13.5 0,-13.5 \
			C 0,-13.5 -4,-13.5 -4,-17.5 \
			C -4,-21.5 0,-21.5 0,-21.5 \
			C 0,-21.5 -4,-21.5 -4,-25.5 \
			C -4,-29.5 0,-29.5 0,-29.5 \
			C 0,-29.5 -4,-29.5 -4,-33.5 \
			C -4,-37.5 0,-37.5 0,-37.5 \
			L 0,-43 \
		\" \
		stroke=\"black\" stroke-width=\"%f\" stroke-linejoin=\"miter\" fill=\"none\" fill-rule=\"evenodd\" fill-opacity=\"0.75\" stroke-linecap=\"butt\" stroke-opacity=\"1\" transform=\"translate(%d,%d) scale(0.02325581395) rotate(90) \" />\n ",(43*LINE_WIDTH),x,y);
}

void place_ac_horizontal(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.02125,0.022727272727272728)\"> <g transform=\"translate(-2.992383,-25.08161)\"> <path d=\"m 40,25 c 0,8.284271 -6.715729,15 -15,15 -8.284271,0 -15,-6.715729 -15,-15 0,-8.284271 6.715729,-15 15,-15 8.284271,0 15,6.715729 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\"/> <path d=\"M 10,25 3,25\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 40,25 11,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 16,25.000005 c 0,0 1.5,-5.000001 4.5,-5.000001 3,0 6,10.000002 9,10.000002 3,0 4.5,-5.000001 4.5,-5.000001\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

void place_current_horizontal(int x,int y, FILE* ptr)
{
	fprintf(ptr, "<g transform=\"translate(%d,%d) scale(0.022727272727272728,0.02125)\"> <g transform=\"translate(-2.992383,-25.08161)\"> <path d=\"m 25,40 c 8.284271,0 15,-6.715729 15,-15 0,-8.284271 -6.715729,-15 -15,-15 -8.284271,0 -15,6.715729 -15,15 0,8.284271 6.715729,15 15,15 l 0,0 z\" style=\"opacity:1;fill:none;fill-opacity:1;stroke:#000000;stroke-width:%f;stroke-linecap:square;stroke-miterlimit:4;stroke-dasharray:none;stroke-dashoffset:0;stroke-opacity:1\" /> <path d=\"M 10,25 3,25\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 40,25 7,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path d=\"m 23.540261,25.136017 11.951034,0\" style=\"fill:none;fill-opacity:0.75;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"/> <path style=\"fill:#000000;fill-rule:evenodd;stroke:#000000;stroke-width:%f;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1;fill-opacity:1\" d=\"m 18.552775,25.136017 4.951033,-3.210011 0.05441,6.63765 z\"/> </g> </g>\n",x,y,(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH),(43*LINE_WIDTH));
}

void make_element_horizontal(int x1,int y1,int x2,int y2,enum component_type type,char* name,FILE* ptr)
{
	draw_text_horizontal(x1,y1,name,type,ptr);
	switch(type)
	{
		case resistor:
			draw_resistor_horizontal(x1,y1,x2,y2,ptr);
			break;
		case inductor:
			draw_inductor_horizontal(x1,y1,x2,y2,ptr);
			break;
		case capacitor:
			draw_capacitor_horizontal(x1,y1,x2,y2,ptr);
			break;
		case voltage:
			draw_ac_horizontal(x1,y1,x2,y2,ptr);
			break;
		case current:
			draw_current_horizontal(x1,y1,x2,y2,ptr);
			break;
	}
}

 int main()
 {
 	for(int i=0;i<20005;i++){
	arr[i]="abhi";                       // NOTE THE USE OF ARR[20005]
	}									 // use make_element_horizontal and make_element_vertical to make circuits
 	FILE* fl = fopen("test_2.svg","w");  // it will be easy job for you 
 	start_svg(10,10,fl);
 	draw_resistor_vertical(1,0,1,4,fl);
 	draw_capacitor_vertical(3,2,3,4,fl);
 	draw_inductor_vertical(2,1,2,3,fl);
 	draw_ac_vertical(5,1,5,3,fl);
 	draw_current_vertical(6,1,6,3,fl);
 	draw_capacitor_horizontal(5,4,6,4,fl);
 	draw_line(1,0,6,0,fl);
 	draw_line(6,3,6,4,fl);
 	draw_line(1,4,5,4,fl);
 	draw_line(2,0,2,1,fl);
 	draw_line(2,2,2,4,fl);
 	draw_line(3,0,3,2,fl);
 	draw_line(5,0,5,1,fl);
 	draw_line(5,2,5,4,fl);
 	draw_line(6,0,6,1,fl);
 	draw_text_vertical(1,0,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",resistor,fl);
 	draw_text_vertical(3,2,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",capacitor,fl);
 	draw_text_vertical(2,1,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",inductor,fl);
 	draw_text_vertical(5,1,"SINE ( 0.0 1.0 10Khz 0.0S 0.0 )",voltage,fl);
 	draw_net_text_vertical(1,0,1,"Net1",fl);
 	draw_ground(3,4,fl);
 	end_svg(fl);
 	fclose(fl);
 }