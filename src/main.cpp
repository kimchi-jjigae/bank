#include "bank.hpp"
#include "global.hpp"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    setupGlobals();

    Bank bank;
    bank.run();
}
