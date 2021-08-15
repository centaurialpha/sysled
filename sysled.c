#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

static const char *sys_led_device = "led1";
static const char *wifi_led_device = "ath9k_htc-phy0";

static uint8_t  parse_args(int argc, char **argv, char *state, bool *all) {
    int opt;

    while ((opt = getopt(argc, argv, ":a:")) != -1) {
        switch (opt) {
            case 'a':
                if (strcmp(optarg, "on") == 0 || strcmp(optarg, "off") == 0) {
                    strcpy(state, optarg);
                    *all = true;
                } else {
                    printf("USAGE");
                }
                break;
            case '?':
                printf("Unknown %c", optopt);
                break;
            case ':':
                printf("Falta arg para %c", optopt);
        }
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
        printf("ERROR");
    }

    fclose(fp);
}

int main(int argc, char **argv) {
    char state[3] = {0};
    bool all = false;

    parse_args(argc, argv, state, &all);

    if (all) {
        write_trigger(sys_led_device, "input", state);
        write_trigger(wifi_led_device, "phy0tpt", state);
    }

    return 0;
}
