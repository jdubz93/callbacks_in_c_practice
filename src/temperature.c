#include "temperature.h"
#include <string.h>

#define MAX_CALLBACKS 10

void temperature_sensor_init(temperature_sensor_t *self)
{
  memset(self, 0, sizeof(*self));
  self->cb_count = 0;
}

void temperature_sensor_deinit(temperature_sensor_t *self)
{
  self->cb_count = 0;
  self = NULL;
}

void temperature_sensor_add_callback(temperature_sensor_t *self, struct temperature_callback *cb)
{
  if (self->cb_count < MAX_CALLBACKS)
  {
    self->callbacks[self->cb_count++] = cb;
  }
}

void temperature_sensor_remove_callback(temperature_sensor_t *self, struct temperature_callback *cb)
{
  for (int i = 0; i < self->cb_count; i++)
  {
    if (self->callbacks[i] == cb)
    {
      for (int j = i; j < self->cb_count - 1; j++)
      {
        self->callbacks[j] = self->callbacks[j + 1];
      }

      self->cb_count--;
    }
  }
}

void temperature_changed(temperature_sensor_t *self, int newTemperature)
{
  for (int i = 0; i < self->cb_count; i++)
  {
    self->callbacks[i]->cb(newTemperature);
  }
}

void air_conditioner_handler(int temperature)
{
  if (temperature > 30)
  {
    printf("Temperature is %d°C! Turning on the air conditioner.\n", temperature);
  }
}

void heater_handler(int temperature)
{
  if (temperature < 20)
  {
    printf("Temperature is %d°C! Turning on the heater.\n", temperature);
  }
}