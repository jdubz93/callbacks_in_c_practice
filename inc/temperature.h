#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CALLBACKS 10

struct temperature_callback
{
  void (*cb)(struct temperature_callback *cb);
};

typedef struct
{
  struct temperature_callback *callbacks[MAX_CALLBACKS];
  int cb_count;
} temperature_sensor_t;

void temperature_sensor_init(temperature_sensor_t *self);
void temperature_sensor_deinit(temperature_sensor_t *self);
void temperature_sensor_add_callback(temperature_sensor_t *self, struct temperature_callback *cb);
void temperature_sensor_remove_callback(temperature_sensor_t *self, struct temperature_callback *cb);
void temperature_changed(temperature_sensor_t *self, int new_temperature);
void air_conditioner_handler(int temperature);
void heater_handler(int temperature);

#endif // TEMPERATURE_H
