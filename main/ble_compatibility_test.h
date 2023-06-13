#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t word_transfer[100] = {};
static uint8_t length_word_transfer = 0;
uint8_t* get_word_transfer();
uint8_t get_length_word_transfer();

enum
{
    IDX_SVC,
    IDX_CHAR_A,
    IDX_CHAR_VAL_A,
    IDX_CHAR_CFG_A,

    IDX_CHAR_B,
    IDX_CHAR_VAL_B,
    IDX_CHAR_CFG_B,

    IDX_CHAR_C,
    IDX_CHAR_VAL_C,
    IDX_CHAR_CFG_C,
    IDX_CHAR_CFG_C_2,

    HRS_IDX_NB,
};

void init_BLE(void);
//void connect_BLE(void);
//void disconnect_BLE(void);