#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

static const char *sys_led_device = "led1";
static const char *wifi_led_device = "ath9k_htc-phy0";

static void print_usage() {
    printf("-------------------------\n");
    printf("Turn on/off LED1 and WiFi adapter LEDs\n"
           "Options are:\n"
           "    --help: print this help\n"
           "    -a: turn on/off LED1 and WiFi adapter leds\n"
           "    -w: turn on/off WiFi adapter led\n"
           "    -l: turn on/off LED1 led\n");

}

static uint8_t parse_args(int argc, char **argv, char *state, bool *wifi, bool *led1) {
    int opt;

    while ((opt = getopt(argc, argv, ":a:w:l:")) != -1) {
        switch (opt) {
            case 'a':
                *wifi = true;
                *led1 = true;
                strcpy(state, optarg);
                break;
            case 'w':
                strcpy(state, optarg);
                *wifi = true;
                break;
            case 'l':
                strcpy(state, optarg);
                *led1 = true;
                break;
        }
    }

    if (strcmp(state, "on") != 0 && strcmp(state, "off") != 0) {
        print_usage();
        return 1;
    }

    return 0;

}

void write_trigger(const char *device, char *trigger, char *state) {
    char trigger_path[100];

    strcpy(trigger_path, "/sys/class/leds/");
    strcat(trigger_path, device);
    strcat(trigger_path, "/trigger");

    printf("    Changing state of %s to %s\n", device, state);

    FILE *fp = fopen(trigger_path, "w");
    if (fp) {
        if (strcmp(state, "off") == 0) {
            fprintf(fp, "none");
        } else {
            fprintf(fp, trigger);
        }

    } else {
        printf("ERROR\n");
    }

    fclose(fp);
}

int main(int argc, char **argv) {
    char state[3] = {0};
    bool wifi = false;
    bool led1 = false;

    if (parse_args(argc, argv, state, &wifi, &led1)){
        // Error when parse cli
        return 1;
    }

    if (wifi) {
        write_trigger(wifi_led_device, "phy0tpt", state);
    }
    if (led1) {
        write_trigger(sys_led_device, "input", state);
    }

    return 0;
}
