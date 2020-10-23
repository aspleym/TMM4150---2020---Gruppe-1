from serial import Serial
import os
import time
try:
    os.system("rfcomm bind /dev/rfcomm0 00:0E:EA:CF:4A:1F")
    port = Serial("/dev/rfcomm0", baudrate=9600)
except:
    print("CANT FINT ANYTINGH IN rfcomm0")
 
# reading and writing data from and to arduino serially.                                      
# rfcomm0 -> this could be different
def blink(l_axis, r_axis, button1, button2, button3, button4):
    l_int = int(l_axis* -9.9) + 9
    r_int = int(r_axis* -9.9) + 9
    msg = "<" + str(l_int) + "," + str(r_int) + "," + str(button1) + "," + str(button2) + "," + str(button3) + "," + str(button4) + ">"
    #port.write([x.encode('utf-8') for x in msg])
    print(msg)
    try: 
        port.write(msg.encode('utf-8'))
    except:
        print("CANT CONNECT")
    #rcv = port.readline()
    #if rcv:
    #    print(rcv)
    #00:0E:EA:CF:4A:1F
    time.sleep( 0.1 )
