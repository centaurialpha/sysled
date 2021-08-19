#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include <unistd.h>
#include "power_device.h"

#define WIFI_FLAG 0b01
#define LED1_FLAG 0b10

static void print_usage() {
    printf("-------------------------\n");
    printf("Turn on/off LED1 and WiFi adapter LEDs\n"
           "Options are:\n"
           "    --help: print this help\n"
           "    -w: turn on/off WiFi adapter led\n"
           "    -l: turn on/off LED1 led\n");

}

static bool check_state(char *state) {
    bool ok = false;
    if (strcmp(state, "on") == 0 || strcmp(state, "off") == 0)
        ok = true;
    return ok;
}

static uint8_t parse_args(int argc, char **argv, char *wifi_state, char *led1_state, uint8_t *flags) {
    int opt;

    while ((opt = getopt(argc, argv, ":w:l:")) != -1) {
        switch (opt) {
            case 'w':
                if (!check_state(optarg)) {
                    print_usage();
                    return 1;
                }
                *flags |= WIFI_FLAG;
                strcpy(wifi_state, optarg);
                break;
            case 'l':
                if (!check_state(optarg)) {
                    print_usage();
                    return 1;
                }
                *flags |= LED1_FLAG;
                strcpy(led1_state, optarg);
                break;
            case ':':
                printf("Option -%c need a value (on|off)\n", optopt);
                break;
            case '?':
                printf("Unknown option %c\n", optopt);
                break;
        }
    }

    return 0;

}

int main(int argc, char **argv) {
    char wifi_state[3] = {0};
    char led1_state[3] = {0};
    uint8_t flags = 0b0;

    if (getuid() != 0) {
        printf("Please run sysled with sudo\n");
        return 1;
    }

    if (parse_args(argc, argv, wifi_state, led1_state, &flags)){
        // Error when parse cli
        return 1;
    }

    if (flags & WIFI_FLAG) {
        if (strcmp(wifi_state, "on") == 0)
            turn_on(&wifi_d);
        else
            turn_off(&wifi_d);
    }
    if (flags & LED1_FLAG) {
        if (strcmp(led1_state, "on") == 0)
            turn_on(&led1_d);
        else
            turn_off(&led1_d);
    }

    return 0;
}
