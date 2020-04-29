#pragma once
/** IDIF: Indented Data Interchange Format
 *  A nice way to print data from the shell, which is also machine-readable
 *  It's kind of like YAML, but much simpler */

#include "hal.h"

struct IdifPrinter {
    BaseSequentialStream *chp;
    uint8_t indent_level;
};

struct IdifPrinter idif_init(BaseSequentialStream *chp);
/** Prints "- name:" and indents */
void idif_print_arr_record(struct IdifPrinter *p, char *name);
/** Prints "- name: value" and indents */
void idif_print_arr_field(struct IdifPrinter *p, char *name, char *fmt, ...);
/** Prints "- value" */
void idif_print_arr_val(struct IdifPrinter *p, char *fmt, ...);
/** Prints "name:" and indents */
void idif_print_record(struct IdifPrinter *p, char *name);
/** Prints "name: value" */
void idif_print_field(struct IdifPrinter *p, char *name, char *fmt, ...);
void idif_dedent(struct IdifPrinter *p);
