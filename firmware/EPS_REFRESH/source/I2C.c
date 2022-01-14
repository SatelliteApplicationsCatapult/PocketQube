/*
 * I2C.c
 *
 *  Created on: 12 Sep 2019
 *      Author: Ken.Diep
 */
#include "fsl_i2c.h"

#define EXAMPLE_I2C_SLAVE_BASEADDR I2C0
#define I2C_SLAVE_CLK_SRC I2C0_CLK_SRC
#define I2C_SLAVE_CLK_FREQ CLOCK_GetFreq(I2C0_CLK_SRC)

#define I2C_DATA_LENGTH 8U
#define I2C_MASTER_SLAVE_ADDR_7BIT 0x2A //I2C address of the EPS

uint8_t g_slave_buff[I2C_DATA_LENGTH];
uint8_t inData; //Data from OBC

//Receive command from OBC
//Wait for flag

static void i2c_slave_callback(I2C_Type *base, i2c_slave_transfer_t *xfer, void *userData)
{
    switch (xfer->event)
    {
        /*  Address match event */
        case kI2C_SlaveAddressMatchEvent:
            xfer->data = NULL; //Gets the member called data from the struct that xfer points to
            xfer->dataSize = 0;
            break;
        /*  Transmit request */
        case kI2C_SlaveTransmitEvent:
            /*  Update information for transmit process */
            xfer->data = &g_slave_buff[2];
            xfer->dataSize = g_slave_buff[1];
            break;

        /*  Receive request */
        case kI2C_SlaveReceiveEvent:
            /*  Update information for received process */
            xfer->data = g_slave_buff;
            xfer->dataSize = I2C_DATA_LENGTH;
            break;

        /*  Transfer done */
        case kI2C_SlaveCompletionEvent:
            g_SlaveCompletionFlag = true;
            xfer->data = NULL;
            xfer->dataSize = 0;
            break;

        default:
            g_SlaveCompletionFlag = false;
            break;
    }
}

//Put this in main code

i2c_slave_config_t slaveConfig;

I2C_SlaveGetDefaultConfig(&slaveConfig);
slaveConfig.addressingMode = kI2C.Address7bit;
slaveConfig.slaveAddress = I2C_MASTER_SLAVE_ADDR_7BIT;
slaveConfig.upperAddress = 0; //Unused

I2C_SlaveInit(EXAMPLE_I2C_SLAVE_BASEADDR, &slaveConfig, I2C_SLAVE_CLK_FREQ);

for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        g_slave_buff[i] = 0;
    }

memset(&g_s_handle, 0, sizeof(g_s_handle)); //Populate g_s_handle with zeros

I2C_SlaveTransferCreateHandle(EXAMPLE_I2C_SLAVE_BASEADDR, &g_s_handle, i2c_slave_callback, NULL);

I2C_SlaveTransferNonBlocking(EXAMPLE_I2C_SLAVE_BASEADDR, &g_s_handle,
                             kI2C_SlaveCompletionEvent | kI2C_SlaveAddressMatchEvent);

/*  wait for transfer completed. */
while (!g_SlaveCompletionFlag)
{
}
g_SlaveCompletionFlag = false;

PRINTF("Slave received data :");
for (uint32_t i = 0U; i < g_slave_buff[1]; i++)
{
    if (i % 8 == 0)
    {
        PRINTF("\r\n");
    }
    PRINTF("0x%2x  ", g_slave_buff[2 + i]);
}
PRINTF("\r\n\r\n");

/* Wait for master receive completed.*/
while (!g_SlaveCompletionFlag)
{
}
g_SlaveCompletionFlag = false;
