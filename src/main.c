#include "button.h"
#include "temperature.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
  struct button btn;
  struct button_callback btn_cb = {.cb = button_handler};
  temperature_sensor_t sensor;
  struct temperature_callback ac_callback = {.cb = air_conditioner_handler};
  struct temperature_callback heater_callback = {.cb = heater_handler};

  button_init(&btn);

  button_add_callback(&btn, &btn_cb);

  temperature_sensor_init(&sensor);
  temperature_sensor_add_callback(&sensor, &ac_callback);
  temperature_sensor_add_callback(&sensor, &heater_callback);

  button_do_something(&btn, 12);
  temperature_changed(&sensor, 35);
  temperature_changed(&sensor, 15);

  button_remove_callback(&btn, &btn_cb);
  button_deinit(&btn);
  temperature_sensor_remove_callback(&sensor, &ac_callback);
  temperature_sensor_remove_callback(&sensor, &heater_callback);
  temperature_sensor_deinit(&sensor);

  return EXIT_SUCCESS;
}