#include "fc_idif.h"
#include "chprintf.h"
#include "fc_config.h"

static void print_indents(struct IdifPrinter *p) {
    for(int i = p->indent_level; i; i--) {
        chprintf(p->chp, "  ");
    }
}
struct IdifPrinter idif_init(BaseSequentialStream *chp) {
    return (struct IdifPrinter) {
        .chp = chp,
        .indent_level =0,
    };
}
void idif_print_arr_record(struct IdifPrinter *p, char *name) {
    print_indents(p);
    chprintf(p->chp, "- %s" EOL, name);
    p->indent_level++;
}
void idif_print_arr_field(struct IdifPrinter *p, char *name, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    print_indents(p);
    chprintf(p->chp, "- %s: ", name);
    chvprintf(p->chp, fmt, args);
    chprintf(p->chp, EOL);
    va_end(args);
    p->indent_level++;
}
void idif_print_arr_val(struct IdifPrinter *p, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    print_indents(p);
    chprintf(p->chp, "- ");
    chvprintf(p->chp, fmt, args);
    chprintf(p->chp, EOL);
    va_end(args);
}
void idif_print_record(struct IdifPrinter *p, char *name) {
    print_indents(p);
    chprintf(p->chp, "%s" EOL, name);
    p->indent_level++;
}
void idif_print_field(struct IdifPrinter *p, char *name, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    print_indents(p);
    chprintf(p->chp, "%s: ", name);
    chvprintf(p->chp, fmt, args);
    chprintf(p->chp, EOL);
    va_end(args);
}
void idif_dedent(struct IdifPrinter *p) {
    p->indent_level--;
}
