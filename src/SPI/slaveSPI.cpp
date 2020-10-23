
#include <SPI.h>

volatile boolean received;
volatile byte Slavereceived, Slavesend;

void setup()
{
    Serial.begin(9600);

    pinMode(MISO, OUTPUT); //Sets MISO as OUTPUT (Have to Send data to Master IN

    SPCR |= _BV(SPE); //Turn on SPI in Slave Mode

    received = false;

    SPI.attachInterrupt(); //Interuupt ON is set for SPI commnucation
}

ISR(SPI_STC_vect) //Inerrrput routine function
{
    Slavereceived = SPDR; // Value received from master if store in variable slavereceived
    received = true;      //Sets received as True
}

void loop()
{
    if (received)
    {
        if (Slavereceived == 5)
        {
            Serial.println("Slave RECIEVED 5");
        }
        else
        {
            Serial.println("Slave RECIEVED SOMETHING ELSE");
        }

        Slavesend = 7;
        SPDR = Slavesend; //Sends the x value to master via SPDR
        delay(1000);
    }
}