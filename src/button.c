
#include "button.h"
#include <string.h>

void button_init(struct button *self)
{
  memset(self, 0, sizeof(*self));
}

void button_deinit(struct button *self)
{
  self = NULL;
}

void button_add_callback(struct button *self, struct button_callback *cb)
{
  self->cb = cb;
}

void button_remove_callback(struct button *self, struct button_callback *cb)
{
  self->cb = NULL;
}

void button_do_something(struct button *self, int val)
{
  if (self->cb)
  {
    self->cb->cb(self->cb);
  }
}

void button_handler(struct button *self, int val)
{
  printf("button_handler val: %d\n", val);
}