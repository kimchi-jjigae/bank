#include "bank.hpp"
#include "global.hpp"

int main(int argc, char *argv[])
{
    setupGlobals();

    Bank bank;
    bank.run();
}
