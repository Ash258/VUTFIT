/*******************************************************************************
Mikrokontroler se v tomto projektu aktivne nevyuziva
******************************************************************************/
#include <string.h>
#include <fitkitlib.h>

/*******************************************************************************
 * Vypis uzivatelske napovedy fce se vykona pri prikazu "help" po vypise
 * systemoveho helpu
*******************************************************************************/
void print_user_help(void) {}

/*******************************************************************************
 * Dekodovani a vykonani uzivatelskych prikazu
*******************************************************************************/
unsigned char decode_user_cmd(char *cmd_ucase, char *cmd)
{
   return (CMD_UNKNOWN);
}

/**
  \brief  Inicializace HW komponent po naprogramovani FPGA, tato funkce musi byt defimovana
  v uzivatelskem programu.
 */
void inline fpga_initialized() {}


/*******************************************************************************
 * HLAVNI FUNKCE MAIN
*******************************************************************************/
int main(void) {
  initialize_hardware();

  set_led_d6(1);                       // rozsviceni D6
  set_led_d5(1);                       // rozsviceni D5

  for (;;)  {
    terminal_idle();                       // obsluha terminalu
  } 

}

