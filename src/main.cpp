/**
 * @file 	main.cpp
 * @author 	Andrew Woska (andrew@woska.org)
 * @date 	10/11/2023
 * @brief	First test using the MCU
 *
 * last updated 10/11/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

int main(int argc, char *argv[]) {
	setup_default_uart();
	printf("Hello people\r\n");
	return 0;
}

