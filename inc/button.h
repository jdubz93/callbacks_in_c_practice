#ifndef BUTTON_H
#define BUTTON_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct button
{
  struct button_callback *cb;
};

struct button_callback
{
  void (*cb)(struct button_callback *cb);
};

void button_init(struct button *self);
void button_deinit(struct button *self);
void button_add_callback(struct button *self, struct button_callback *cb);
void button_remove_callback(struct button *self, struct button_callback *cb);
void button_do_something(struct button *self, int val);
void button_handler(struct button *self, int val);

#endif // BUTTON_H
