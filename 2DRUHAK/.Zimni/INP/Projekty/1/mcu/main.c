#include <fitkitlib.h>

void print_user_help(void) { }

unsigned char decode_user_cmd(char *cmd_ucase, char *cmd) {

    return (CMD_UNKNOWN);

}

void fpga_initialized() { }

int main(void)
{
    initialize_hardware();

    while (1) 
    {
        terminal_idle();  // obsluha terminalu
    }
}

