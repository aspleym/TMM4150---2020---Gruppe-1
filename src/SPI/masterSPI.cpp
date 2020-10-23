#include <SPI.h> //Library for SPI

int x;
void setup(void)

{
    Serial.begin(9600); //Starts Serial Communication at Baud Rate 115200

    SPI.begin(); //Begins the SPI commnuication
    //SPI.setClockDivider(SPI_2XCLOCK_MASK); //Sets clock for SPI communication at 8 (16/8=2Mhz)
    digitalWrite(SS, HIGH); // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
}

void loop(void)
{
    byte Mastersend, Mastereceive;

    digitalWrite(SS, LOW); //Starts communication with Slave connected to master

    Mastersend = 5;
    Mastereceive = SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave

    if (Mastereceive == 7)
    {
        Serial.println("Master RECIEVED 7");
    }
    else
    {
        Serial.println("Master RECIEVED SOMETHING ELSE");
    }
    delay(1000);
}