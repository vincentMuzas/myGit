#include "main.h"

int main(int argc, char **argv) {
    t_usage *usage = get_usage(argc, argv);

    bool found = false;
    for (int i = 0; i < USAGE_ARGS_COUNT; i++) {
        if (usage[i].val != NULL) {
            printf("Found: %s with value: %s\n", usage[i].name, usage[i].val);
            found = true;
        }
        if (i == USAGE_ARGS_COUNT - 1 && !found) {
            print_usage(usage);
            break;
        }
    }
    return 0;
}

void print_usage(t_usage *usage) {
    for (int i = 0; usage[i].name != NULL; i++) {
        printf("%s: %s", usage[i].name, usage[i].desc);
    }
}