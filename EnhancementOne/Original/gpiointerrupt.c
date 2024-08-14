/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/UART2.h>

/* Driver configuration */
#include "ti_drivers_config.h"

//Definitions

#define DISPLAY(x) UART2_write(uart, &output, x, NULL)
#define timerPeriod 100
#define numTasks 3
#define checkButtonPeriod 200
#define checkTemperaturePeriod 500
#define updateHeatModeAndServerPeriod 1000

/*
 * =======Task Type=========
 * Defines structure for tasks
 */
typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*tickFunction)(int);
} task;

//Driver Handles
I2C_Handle i2c;
Timer_Handle timer0;
UART2_Handle uart;

/*
 * ========Global Variables=========
 */
//UART Variables
char output[64];
int bytesToSend;

//I2C variables
static const struct{
    uint8_t address;
    uint8_t resultReg;
    char *id;
}
sensors[3] = {
    { 0x48, 0x0000, "11X" },
    { 0x49, 0x0000, "116" },
    { 0x41, 0x0001, "006" }
};
uint8_t txBuffer[1];
uint8_t rxBuffer[2];
I2C_Transaction i2cTransaction;

//Timer Variable
volatile unsigned char TimerFlag = 0;

//Thermostat Global Variables
enum BUTTON_STATES {INCREASE_TEMPERATURE, DECREASE_TEMPERATURE, BUTTON_INIT} BUTTON_STATE;
enum TEMPERATURE_SENSOR_STATES {READ_TEMPERATURE, TEMPERATURE_SENSOR_INIT};
enum HEATING_STATES {HEAT_OFF, HEAT_ON, HEAT_INIT};
int16_t ambientTemperature;
int16_t setPoint = 20;
int seconds = 0;

/*
 * ===========Callbacks============
 */
//Callback to increase temperature
void gpioIncreaseTemperatureCallback(uint_least8_t index){
    BUTTON_STATE = INCREASE_TEMPERATURE;
}

//Callback to decrease temperature
void gpioDecreaseTemperatureCallback(uint_least8_t index){
    BUTTON_STATE = DECREASE_TEMPERATURE;
}

//Timer callback
void timerCallback(Timer_Handle myHandle, int_fast16_t status){
    TimerFlag = 1;
}

/*
 * ========Initializations========
 */
//UART2 Initialization
void initUART(void){
    UART2_Params uartParams;

    //Driver configuration
    UART2_Params_init(&uartParams);
    uartParams.writeMode = UART2_Mode_BLOCKING;
    uartParams.readMode = UART2_Mode_BLOCKING;
    uartParams.readReturnMode = UART2_ReadReturnMode_FULL;
    uartParams.baudRate = 115200;

    uart = UART2_open(CONFIG_UART2_0, &uartParams);
    if(uart == NULL){
        while(1);
    }
}

//I2C Initialization
void initI2C(void){
    int8_t i, found;
    I2C_Params i2cParams;

    DISPLAY(snprintf(output, 64, "Initializing I2C Driver -"));

    //Driver initialization
    I2C_init();

    //Driver Configuration
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;

    //Open Driver
    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
    if(i2c == NULL){
        DISPLAY(snprintf(output, 64, "Failed\n\r"));
        while(1);
    }

    DISPLAY(snprintf(output, 32, "Passed\n\r"));

    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.readCount = 0;

    found = false;
    for(i = 0; i < 3; i++){
        i2cTransaction.targetAddress = sensors[i].address;
        txBuffer[0] = sensors[i].resultReg;

        DISPLAY(snprintf(output, 64, "Is this %s? ", sensors[i].id));
        if(I2C_transfer(i2c, &i2cTransaction)){
            DISPLAY(snprintf(output, 64, "Found\n\r"));
            found = true;
            break;
        }
        DISPLAY(snprintf(output, 64, "No\n\r"));
    }

    if(found){
        DISPLAY(snprintf(output, 64, "Detected TMP%s I2C Address %x\n\r", sensors[i].id, i2cTransaction.targetAddress));
    }
    else{
        DISPLAY(snprintf(output, 64, "Temperature sensor not found, contact professor\n\r"));
    }
}

//GPIO Initialization
void initGPIO(void){
    GPIO_init();

    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);

    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioIncreaseTemperatureCallback);

    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    if(CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1){
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioDecreaseTemperatureCallback);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }

    BUTTON_STATE = BUTTON_INIT;
}

//Timer Initialization
void initTimer(void){
    Timer_Params timerParams;

    Timer_init();

    Timer_Params_init(&timerParams);
    timerParams.period = 100000;
    timerParams.periodUnits = Timer_PERIOD_US;
    timerParams.timerMode = Timer_CONTINUOUS_CALLBACK;
    timerParams.timerCallback = timerCallback;

    timer0 = Timer_open(CONFIG_TIMER_0, &timerParams);

    if(timer0 == NULL){
        while(1){}
    }
    if(Timer_start(timer0) == Timer_STATUS_ERROR){
        while(1){}
    }
}

/*
 * ======adjustSetPointTemperature
 *
 * Check the state of buttons to increase or decrease if a
 * button was pressed then resets Button_Pressed
 */
int adjustSetPointTemperature(int state){
    switch(state)
    {
        case INCREASE_TEMPERATURE:
            if(setPoint < 99){
                setPoint++;
            }
            BUTTON_STATE = BUTTON_INIT;
            break;
        case DECREASE_TEMPERATURE:
            if(setPoint > 0){
                setPoint--;
            }
            BUTTON_STATE = BUTTON_INIT;
            break;
    }
    state = BUTTON_STATE;

    return state;
}

/*
 * ========readTemp=========
 * Read and return current temp from sensor
 */
int16_t readTemp(void){
    int16_t temperature = 0;
    float temperature_c = 0;

    i2cTransaction.readCount = 2;
    if(I2C_transfer(i2c, &i2cTransaction)){
        temperature = (rxBuffer[0] << 8) | (rxBuffer[1]);

        if(temperature == NULL){
                    DISPLAY(snprintf(output, 64, "Error reading temperature sensor(%d)\n\r", i2cTransaction.status));
                    DISPLAY(snprintf(output, 64, "Please power cycle board by unplugging USB and plugging back in.\n\r"));
        }

        temperature_c = temperature * 0.0078125;

        return temperature_c;
    }
}

/*
 * ========getAmbientTemperature======
 *
 * Checks if temperature should be read
 */
int getAmbientTemperature(int state){
    switch(state)
    {
        case TEMPERATURE_SENSOR_INIT:
            state = READ_TEMPERATURE;
            break;
        case READ_TEMPERATURE:
            ambientTemperature = readTemp();
            break;
    }

    return state;
}


/*
 * ========SetHeatMode=========
 * Turns Heat on or off (LED on or off) depending
 * on ambient temperature. On indicates Heat on (lower
 * than set-point and Off indicates Heat off (higher
 * than set-point).
 */
int setHeatMode(int state){
    if(seconds != 0){
        //determines if heat is needed or not
        if (ambientTemperature < setPoint){
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
            state = HEAT_ON;
        }
        else{
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
            state = HEAT_OFF;
        }

        //Status sent to server
        DISPLAY(snprintf(output,
                         64,
                         "<%02d,%02d,%d,%04d>\n\r",
                         ambientTemperature,
                         setPoint,
                         state,
                         seconds));
    }

    seconds++;
    return state;
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    task tasks[numTasks] = {
         //Task 1 - Update Set Point and Check Button State
         {
              .state = BUTTON_INIT,
              .period = checkButtonPeriod,
              .elapsedTime = checkButtonPeriod,
              .tickFunction = &adjustSetPointTemperature
         },
         //Task 2 - Get Temp from Sensor
         {
              .state = TEMPERATURE_SENSOR_INIT,
              .period = checkTemperaturePeriod,
              .elapsedTime = checkTemperaturePeriod,
              .tickFunction = &getAmbientTemperature
         },
         //Task 3 - Update Heat and server
         {
              .state = HEAT_INIT,
              .period = updateHeatModeAndServerPeriod,
              .elapsedTime = updateHeatModeAndServerPeriod,
              .tickFunction = &setHeatMode
         }
    };

    initUART();
    initI2C();
    initGPIO();
    initTimer();

    while(1) {
        unsigned int i = 0;
        for( i = 0; i < numTasks; i++){
            if(tasks[i].elapsedTime >= tasks[i].period)
            {
                tasks[i].state = tasks[i].tickFunction(tasks[i].state);
                tasks[i].elapsedTime = 0;
            }
            tasks[i].elapsedTime += timerPeriod;
        }

        while(!TimerFlag){}

        TimerFlag = 0;
        timer0++;
    }

    return (NULL);
}
