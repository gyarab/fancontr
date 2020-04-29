EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 12
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4500 3500 5900 3500
$Comp
L power:+12V #PWR020
U 1 1 5D5751BB
P 5900 3700
AR Path="/5D5674A6/5D5751BB" Ref="#PWR020"  Part="1" 
AR Path="/5D58361C/5D5751BB" Ref="#PWR023"  Part="1" 
AR Path="/5D5881AE/5D5751BB" Ref="#PWR026"  Part="1" 
AR Path="/5D59370E/5D5751BB" Ref="#PWR029"  Part="1" 
AR Path="/5D5AAFF5/5D5751BB" Ref="#PWR?"  Part="1" 
AR Path="/5D60A83C/5D5751BB" Ref="#PWR050"  Part="1" 
F 0 "#PWR023" H 5900 3550 50  0001 C CNN
F 1 "+12V" V 5915 3828 50  0000 L CNN
F 2 "" H 5900 3700 50  0001 C CNN
F 3 "" H 5900 3700 50  0001 C CNN
	1    5900 3700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5D5751C1
P 5900 3800
AR Path="/5D5674A6/5D5751C1" Ref="#PWR021"  Part="1" 
AR Path="/5D58361C/5D5751C1" Ref="#PWR024"  Part="1" 
AR Path="/5D5881AE/5D5751C1" Ref="#PWR027"  Part="1" 
AR Path="/5D59370E/5D5751C1" Ref="#PWR030"  Part="1" 
AR Path="/5D5AAFF5/5D5751C1" Ref="#PWR?"  Part="1" 
AR Path="/5D60A83C/5D5751C1" Ref="#PWR051"  Part="1" 
F 0 "#PWR024" H 5900 3550 50  0001 C CNN
F 1 "GND" H 5905 3627 50  0000 C CNN
F 2 "" H 5900 3800 50  0001 C CNN
F 3 "" H 5900 3800 50  0001 C CNN
	1    5900 3800
	0    1    1    0   
$EndComp
$Comp
L Custom_Symbols:Fan_4Pin J?
U 1 1 5D5751C7
P 6100 3700
AR Path="/5D5751C7" Ref="J?"  Part="1" 
AR Path="/5D5674A6/5D5751C7" Ref="J6"  Part="1" 
AR Path="/5D58361C/5D5751C7" Ref="J7"  Part="1" 
AR Path="/5D5881AE/5D5751C7" Ref="J8"  Part="1" 
AR Path="/5D59370E/5D5751C7" Ref="J9"  Part="1" 
AR Path="/5D5AAFF5/5D5751C7" Ref="J?"  Part="1" 
AR Path="/5D60A83C/5D5751C7" Ref="J16"  Part="1" 
F 0 "J7" V 6254 3412 50  0000 R CNN
F 1 "Fan_4Pin" V 6163 3412 50  0000 R CNN
F 2 "Custom_Footprints:PinHeader_1x04_P2.54mm_Horizontal_NoSilk" H 6100 3700 50  0001 C CNN
F 3 "~" H 6100 3700 50  0001 C CNN
	1    6100 3700
	-1   0    0    1   
$EndComp
Text HLabel 4500 3500 0    50   Input ~ 0
PWM_In
Text HLabel 4500 3600 0    50   Input ~ 0
RPM_Sense
Wire Wire Line
	4500 3600 5900 3600
$EndSCHEMATC
