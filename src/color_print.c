
#include "color_print.h"

print_color_t COLOR_NONE = "";
print_color_t COLOR_BLACK = "\033[30m";
print_color_t COLOR_RED = "\033[31m";
print_color_t COLOR_GREEN = "\033[32;5m";
print_color_t COLOR_YELLOW = "\033[33m";
print_color_t COLOR_BLUE = "\033[34m";
print_color_t COLOR_MAGENTA = "\033[35m";
print_color_t COLOR_CYAN = "\033[36m";
print_color_t COLOR_WHITE = "\033[37m";
print_color_t COLOR_L_GRAY = "\033[90m";
print_color_t COLOR_L_RED = "\033[91m";
print_color_t COLOR_L_GREEN = "\033[92m";
print_color_t COLOR_L_YELLOW = "\033[93m";
print_color_t COLOR_L_BLUE = "\033[94m";
print_color_t COLOR_L_MAGENTA = "\033[95m";
print_color_t COLOR_L_CYAN = "\033[96m";
print_color_t COLOR_L_WHITE = "\033[97m";


const char *_reset = "\033[94m";

const char *_newline = "\r\n";


void color_print(print_color_t Color, char* Text, ...){
	va_list args;

	va_start(args, Text);

	printf(Color);
	vprintf(Text, args);

	va_end(args);
}

void color_printf(print_color_t Color, char* Text, ...){
    va_list args;

    va_start(args, Text);

    printf(Color);
    vprintf(Text, args);
    printf(_reset);

    va_end(args);
}

