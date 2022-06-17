# CRC-AX.25
This program calculates the FCS (Frame Check Sequence) through CRC and the corrent ISO standard - this was made very quickly and was a faster way than testing it directly on the RP2040 (for the A30B Project)...
Please compile as such:
```
gcc CRC16.c -o crc16
```
You should expect the following results:
```
./crc16 ABC
CRC16 Algorithm tester
INPUT:           ABC
ORIGINAL:        0100 0001  | 0100 0010  | 0100 0011  | 
FLIPPED:         1000 0010  | 0100 0010  | 1100 0010  | 
RESULT:          f4f9
RESULT:          1111 0100 1111 1001 
```
