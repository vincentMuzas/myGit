#include "main.h"

int main(int argc, char **argv)
{
    t_usage usage = parse_args(argc, argv);

    if (usage.method != NULL)
    {
        return usage.method(argc - 2, &argv[2]);
    }
    return EXIT_FAILURE;
}
