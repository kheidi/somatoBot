#Encoder Counter

The Encoder counter program runs on a dedicated Atmega328p processor
and serve as an SPI slave device that manages digital encoder counting 
for 3 digital encoders, representing the Crank, left pedal, and right Pedal

when the encoder counter device recieves the ASCII for 's' (which is 
0x53) it will 's'end the counter values in the order of the following 
table. 

|encoder | command | steps/rev | return type |
|:------:|:-------:|:---------:|:-----------:|
|Crank   |0x01     |6000       | int         |
|Right   |0x02     |1024       | int         |
|Left    |0x03     |1024       | int         |

As the table implies, its also possible to access these values individually, 
by sending the command, and reading  the return value for the proper number
of bytes. 

here is an example of how one might read the value of the crank into 
an int.

~~~C++
#define GetCrank 0x01

int crankCount;
SPI.transfer(GetCrank);                     //ask for the crank variable
delayMicros(10);                            //wait a bit for command to be processed, possibly with delay fxn
crankCount = SPI.transfer(0)<<8;            //recieve high Byte and shift it over
crankCount |= SPI.transfer(0);              //recieve lower byte and or it in 
~~~

when reading with the 's' command, simply repeat the process 2 more times, only sending 
0's, and with no need for additional delays. 