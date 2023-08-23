/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#include "asf.h"

// Configuracoes do LED    1
#define LED1_PIO PIOA                         // periferico que controla o LED
#define LED1_PIO_ID ID_PIOA                   // ID do periférico PIOC (controla LED)
#define LED1_PIO_IDX 0                        // NO EXT = 7
#define LED1_PIO_IDX_MASK (1 << LED1_PIO_IDX) // Mascara para CONTROLARMOS o LED

// Configuracoes do Botao 1
#define BUT1_PIO          PIOD                 // periferico que controla o LED
#define BUT1_PIO_ID       ID_PIOD              // ID do periférico PIOC (controla Botao)
#define BUT1_PIO_IDX      28                   // NO EXT = 9
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX) // Mascara para CONTROLARMOS o Botao

// Configuracoes do LED    2
#define LED2_PIO          PIOC
#define LED2_PIO_ID       ID_PIOC
#define LED2_PIO_IDX      30                  // NO EXT = 8
#define LED2_PIO_IDX_MASK (1 << LED2_PIO_IDX)

// Configuracoes do Botao 2
#define BUT2_PIO          PIOC
#define BUT2_PIO_ID       ID_PIOC
#define BUT2_PIO_IDX      31                   // NO EXT = 3
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX)

// Configuracoes do LED    3
#define LED3_PIO          PIOB
#define LED3_PIO_ID       ID_PIOB
#define LED3_PIO_IDX      2                    // NO EXT = 6
#define LED3_PIO_IDX_MASK (1 << LED3_PIO_IDX)

// Configuracoes do Botao 3
#define BUT3_PIO          PIOA
#define BUT3_PIO_ID       ID_PIOA
#define BUT3_PIO_IDX      19                   // NO EXT = 4
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Função de inicialização do uC
void init(void) {
    // Initialize the board clock
    sysclk_init();

    // Desativa WatchDog Timer
    WDT->WDT_MR = WDT_MR_WDDIS;

    // Inicializa PIO do LED 1
    pmc_enable_periph_clk(LED1_PIO_ID);
    // Inicializa PIO do Botao 1
    pmc_enable_periph_clk(BUT1_PIO_ID);

    // Inicializa PIO do LED 2
    pmc_enable_periph_clk(LED2_PIO_ID);
    // Inicializa PIO do Botao 2
    pmc_enable_periph_clk(BUT2_PIO_ID);

    // Inicializa PIO do LED 3
    pmc_enable_periph_clk(LED3_PIO_ID);
    // Inicializa PIO do Botao 3
    pmc_enable_periph_clk(BUT3_PIO_ID);

    pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
    pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_DEFAULT);
    pio_pull_up(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_PULLUP);

    pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
    pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_DEFAULT);
    pio_pull_up(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_PULLUP);

    pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);
    pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_DEFAULT);
    pio_pull_up(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_PULLUP);
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void) {
    // inicializa sistema e IOs
    init();

    // super loop
    // aplicacoes embarcadas não devem sair do while(1).
    while (1) {
        // Pisca LED 1 e Desliga com Botao 1

        if (!pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK)) {
            for (int i = 0; i < 10; i++) {
                pio_set(LED1_PIO, LED1_PIO_IDX_MASK);   // Coloca 1 no pino LED
                delay_ms(100);                          // Delay por software de 250 ms
                pio_clear(LED1_PIO, LED1_PIO_IDX_MASK); // Coloca 0 no pino do LED
                delay_ms(100);                          // Delay por software de 250 ms
            }
        } else {
            pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
        }
        // Botao 2 e LED 2

        if (!pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK)) {
            for (int i = 0; i < 10; i++) {
                pio_set(LED2_PIO, LED2_PIO_IDX_MASK);   // Coloca 1 no pino LED2
                delay_ms(250);                          // Delay por software de 500 ms
                pio_clear(LED2_PIO, LED2_PIO_IDX_MASK); // Coloca 0 no pino do LED2
                delay_ms(250);                          // Delay por software de 500 ms
            }
        } else {
            pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
        }
        // Botao 3 e LED 3

        if (!pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK)) {
            for (int i = 0; i < 10; i++) {
                pio_set(LED3_PIO, LED3_PIO_IDX_MASK);   // Coloca 1 no pino LED
                delay_ms(500);                          // Delay por software de 200 ms
                pio_clear(LED3_PIO, LED3_PIO_IDX_MASK); // Coloca 0 no pino do LED
                delay_ms(500);                          // Delay por software de 200 ms
            }
        } else {
            pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
        }
    }
    return 0;
}