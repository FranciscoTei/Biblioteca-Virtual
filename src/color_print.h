
#ifndef COLOR_PRINT_H_
#define COLOR_PRINT_H_


#include <stdio.h>
#include <string.h>
#include <stdarg.h>

typedef const char*		print_color_t;


extern print_color_t COLOR_NONE;
extern print_color_t COLOR_BLACK;
extern print_color_t COLOR_RED;
extern print_color_t COLOR_GREEN;
extern print_color_t COLOR_YELLOW;
extern print_color_t COLOR_BLUE;
extern print_color_t COLOR_MAGENTA;
extern print_color_t COLOR_CYAN;
extern print_color_t COLOR_WHITE;
extern print_color_t COLOR_L_GRAY;
extern print_color_t COLOR_L_RED;
extern print_color_t COLOR_L_GREEN;
extern print_color_t COLOR_L_YELLOW;
extern print_color_t COLOR_L_BLUE;
extern print_color_t COLOR_L_MAGENTA;
extern print_color_t COLOR_L_CYAN;
extern print_color_t COLOR_L_WHITE;



void color_print(print_color_t Color, char* Text, ...);
void color_printf(print_color_t Color, char* Text, ...);

#endif
