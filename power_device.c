#include "power_device.h"

void turn_on(const device_t *device) {
    printf("[*] Turning on %s\n", device->name);
    write_trigger(device->path, device->trigger);
}

void turn_off(const device_t *device) {
    printf("[*] Turning off %s\n", device->name);
    write_trigger(device->path, "none");
}

void write_trigger(char *path, char *trigger) {
    FILE *fp = fopen(path, "w");
    if (!fp) {
        printf("Error\n");
    } else {
        fprintf(fp, trigger);
    }
    fclose(fp);
}

const device_t wifi_d = {
    .name = "ath9k_htc-phy0",
    .path = "/sys/class/leds/ath9k_htc-phy0/trigger",
    .trigger = "phy0tpt",
};

const device_t led1_d = {
    .name = "led1",
    .path = "/sys/class/leds/led1/trigger",
    .trigger = "input",
};
