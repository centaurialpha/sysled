#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>
#include "power_device.h"

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

static uint8_t parse_args(int argc, char **argv, char *state, bool *wifi, bool *led1) {
    int opt;

    while ((opt = getopt(argc, argv, ":w:l:")) != -1) {
        switch (opt) {
            case 'w':
                if (strcmp(optarg, "on") == 0)
                    *wifi = true;
                strcpy(state, optarg);
                break;
            case 'l':
                if (strcmp(optarg, "on") == 0)
                    *led1 = true;
                strcpy(state, optarg);
                break;
            case ':':
                printf("Option -%c need a value (on|off)\n", optopt);
                break;
            case '?':
                printf("Unknown option %c\n", optopt);
                break;
        }
    }
    if (!check_state(state)) {
        print_usage();
        return 1;
    }

    return 0;

}

int main(int argc, char **argv) {
    char state[3] = {0};
    bool wifi = false;
    bool led1 = false;

    if (getuid() != 0) {
        printf("Please run sysled with sudo\n");
        return 1;
    }

    if (parse_args(argc, argv, state, &wifi, &led1)){
        // Error when parse cli
        return 1;
    }

    if (wifi) {
        turn_on(&wifi_d);
    } else {
        turn_off(&wifi_d);
    }
    if (led1) {
        turn_on(&led1_d);
    } else {
        turn_off(&led1_d);
    }

    return 0;
}
