#ifndef _POWER_DEVICE_H
#define _POWER_DEVICE_H
#include <stdio.h>

typedef struct {
    char *name;
    char *path;
    char *trigger;
} device_t;

extern const device_t led1_d;
extern const device_t wifi_d;

void turn_on(const device_t *);
void turn_off(const device_t *);
void write_trigger(char *, char *);

#endif
