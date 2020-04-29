EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 12
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Custom_Symbols:Fan_3Pin J15
U 1 1 5D5BB0FA
P 7000 4000
AR Path="/5D5B12C9/5D5BB0FA" Ref="J15"  Part="1" 
AR Path="/5D5DC66E/5D5BB0FA" Ref="J14"  Part="1" 
AR Path="/5D5E688C/5D5BB0FA" Ref="J11"  Part="1" 
AR Path="/5D5EF4F5/5D5BB0FA" Ref="J12"  Part="1" 
AR Path="/5D61A1B6/5D5BB0FA" Ref="J13"  Part="1" 
AR Path="/5D5AAFF5/5D5BB0FA" Ref="J10"  Part="1" 
AR Path="/5E891FD9/5D5BB0FA" Ref="J?"  Part="1" 
AR Path="/5E892449/5D5BB0FA" Ref="J?"  Part="1" 
F 0 "J10" H 6524 3969 50  0000 R CNN
F 1 "Fan_3Pin" H 6524 4060 50  0000 R CNN
F 2 "Custom_Footprints:PinHeader_1x03_P2.54mm_Horizontal_NoSilk" H 7000 4000 50  0001 C CNN
F 3 "~" H 7000 4000 50  0001 C CNN
	1    7000 4000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR049
U 1 1 5D5BC6B6
P 5900 5150
AR Path="/5D5B12C9/5D5BC6B6" Ref="#PWR049"  Part="1" 
AR Path="/5D5DC66E/5D5BC6B6" Ref="#PWR046"  Part="1" 
AR Path="/5D5E688C/5D5BC6B6" Ref="#PWR037"  Part="1" 
AR Path="/5D5EF4F5/5D5BC6B6" Ref="#PWR040"  Part="1" 
AR Path="/5D61A1B6/5D5BC6B6" Ref="#PWR043"  Part="1" 
AR Path="/5D5AAFF5/5D5BC6B6" Ref="#PWR034"  Part="1" 
AR Path="/5E891FD9/5D5BC6B6" Ref="#PWR?"  Part="1" 
AR Path="/5E892449/5D5BC6B6" Ref="#PWR?"  Part="1" 
F 0 "#PWR049" H 5900 4900 50  0001 C CNN
F 1 "GND" H 5905 4977 50  0000 C CNN
F 2 "" H 5900 5150 50  0001 C CNN
F 3 "" H 5900 5150 50  0001 C CNN
	1    5900 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR048
U 1 1 5D5C3AB4
P 5400 4000
AR Path="/5D5B12C9/5D5C3AB4" Ref="#PWR048"  Part="1" 
AR Path="/5D5DC66E/5D5C3AB4" Ref="#PWR045"  Part="1" 
AR Path="/5D5E688C/5D5C3AB4" Ref="#PWR036"  Part="1" 
AR Path="/5D5EF4F5/5D5C3AB4" Ref="#PWR039"  Part="1" 
AR Path="/5D61A1B6/5D5C3AB4" Ref="#PWR042"  Part="1" 
AR Path="/5D5AAFF5/5D5C3AB4" Ref="#PWR033"  Part="1" 
AR Path="/5E891FD9/5D5C3AB4" Ref="#PWR?"  Part="1" 
AR Path="/5E892449/5D5C3AB4" Ref="#PWR?"  Part="1" 
F 0 "#PWR048" H 5400 3850 50  0001 C CNN
F 1 "+12V" V 5400 4150 50  0000 L CNN
F 2 "" H 5400 4000 50  0001 C CNN
F 3 "" H 5400 4000 50  0001 C CNN
	1    5400 4000
	0    -1   -1   0   
$EndComp
Text HLabel 5400 4600 0    50   Input ~ 0
PWM_In
$Comp
L Device:D_Schottky_Small D2
U 1 1 5D86C107
P 5900 4100
AR Path="/5D5AAFF5/5D86C107" Ref="D2"  Part="1" 
AR Path="/5D5E688C/5D86C107" Ref="D3"  Part="1" 
AR Path="/5D5EF4F5/5D86C107" Ref="D4"  Part="1" 
AR Path="/5D61A1B6/5D86C107" Ref="D5"  Part="1" 
AR Path="/5D5DC66E/5D86C107" Ref="D6"  Part="1" 
AR Path="/5D5B12C9/5D86C107" Ref="D7"  Part="1" 
AR Path="/5E891FD9/5D86C107" Ref="D?"  Part="1" 
AR Path="/5E892449/5D86C107" Ref="D?"  Part="1" 
F 0 "D2" V 5850 4000 50  0000 C CNN
F 1 "D_Small" V 5950 3900 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" V 5900 4100 50  0001 C CNN
F 3 "~" V 5900 4100 50  0001 C CNN
	1    5900 4100
	0    1    1    0   
$EndComp
$Comp
L Device:L_Small L5
U 1 1 5DABA74D
P 6050 4200
AR Path="/5D5DC66E/5DABA74D" Ref="L5"  Part="1" 
AR Path="/5D5AAFF5/5DABA74D" Ref="L1"  Part="1" 
AR Path="/5D5E688C/5DABA74D" Ref="L2"  Part="1" 
AR Path="/5D5EF4F5/5DABA74D" Ref="L3"  Part="1" 
AR Path="/5D61A1B6/5DABA74D" Ref="L4"  Part="1" 
AR Path="/5D5B12C9/5DABA74D" Ref="L6"  Part="1" 
AR Path="/5E891FD9/5DABA74D" Ref="L?"  Part="1" 
AR Path="/5E892449/5DABA74D" Ref="L?"  Part="1" 
F 0 "L1" V 6000 4150 50  0000 L CNN
F 1 "10uH @ 400mA" V 5900 3700 50  0000 L CNN
F 2 "Inductor_SMD:L_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6050 4200 50  0001 C CNN
F 3 "~" H 6050 4200 50  0001 C CNN
	1    6050 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5900 4800 5900 5150
Wire Wire Line
	5900 4200 5950 4200
Wire Wire Line
	6150 4200 6200 4200
Connection ~ 6200 4200
Wire Wire Line
	5400 4000 5900 4000
Connection ~ 6200 4000
Wire Wire Line
	5400 3900 6200 3900
Text HLabel 5400 3900 0    50   Input ~ 0
RPM_Sense_12V
$Comp
L Device:R_Small R12
U 1 1 5E88504E
P 6200 3800
AR Path="/5D5B12C9/5E88504E" Ref="R12"  Part="1" 
AR Path="/5D5E688C/5E88504E" Ref="R7"  Part="1" 
AR Path="/5D5EF4F5/5E88504E" Ref="R8"  Part="1" 
AR Path="/5D61A1B6/5E88504E" Ref="R9"  Part="1" 
AR Path="/5D5DC66E/5E88504E" Ref="R10"  Part="1" 
AR Path="/5D5AAFF5/5E88504E" Ref="R11"  Part="1" 
AR Path="/5E891FD9/5E88504E" Ref="R?"  Part="1" 
AR Path="/5E892449/5E88504E" Ref="R?"  Part="1" 
F 0 "R11" H 6259 3846 50  0000 L CNN
F 1 "10k" H 6259 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6200 3800 50  0001 C CNN
F 3 "~" H 6200 3800 50  0001 C CNN
	1    6200 3800
	1    0    0    -1  
$EndComp
Connection ~ 6200 3900
Wire Wire Line
	6200 3900 6800 3900
$Comp
L power:+12V #PWR0120
U 1 1 5E885C0A
P 6200 3700
AR Path="/5D5B12C9/5E885C0A" Ref="#PWR0120"  Part="1" 
AR Path="/5D5E688C/5E885C0A" Ref="#PWR0115"  Part="1" 
AR Path="/5D5EF4F5/5E885C0A" Ref="#PWR0116"  Part="1" 
AR Path="/5D61A1B6/5E885C0A" Ref="#PWR0117"  Part="1" 
AR Path="/5D5DC66E/5E885C0A" Ref="#PWR0118"  Part="1" 
AR Path="/5D5AAFF5/5E885C0A" Ref="#PWR0119"  Part="1" 
AR Path="/5E891FD9/5E885C0A" Ref="#PWR?"  Part="1" 
AR Path="/5E892449/5E885C0A" Ref="#PWR?"  Part="1" 
F 0 "#PWR0120" H 6200 3550 50  0001 C CNN
F 1 "+12V" H 6215 3873 50  0000 C CNN
F 2 "" H 6200 3700 50  0001 C CNN
F 3 "" H 6200 3700 50  0001 C CNN
	1    6200 3700
	1    0    0    -1  
$EndComp
Text Label 6800 4200 3    50   ~ 0
Fan_GND
$Comp
L Device:Q_NMOS_GSD Q7
U 1 1 5D5CC9A3
P 5800 4600
AR Path="/5D5B12C9/5D5CC9A3" Ref="Q7"  Part="1" 
AR Path="/5D5DC66E/5D5CC9A3" Ref="Q6"  Part="1" 
AR Path="/5D5E688C/5D5CC9A3" Ref="Q3"  Part="1" 
AR Path="/5D5EF4F5/5D5CC9A3" Ref="Q4"  Part="1" 
AR Path="/5D61A1B6/5D5CC9A3" Ref="Q5"  Part="1" 
AR Path="/5D5AAFF5/5D5CC9A3" Ref="Q2"  Part="1" 
AR Path="/5E891FD9/5D5CC9A3" Ref="Q?"  Part="1" 
AR Path="/5E892449/5D5CC9A3" Ref="Q?"  Part="1" 
F 0 "Q2" H 6006 4646 50  0000 L CNN
F 1 "LGE2300" H 6006 4555 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TSOT-23" H 6000 4700 50  0001 C CNN
F 3 "https://www.tme.eu/Document/bf2e77ec4ce4a2e1ce1235739925ec99/LGE2300.pdf" H 5800 4600 50  0001 C CNN
	1    5800 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C16
U 1 1 5D5CF1A5
P 6200 4100
AR Path="/5D5B12C9/5D5CF1A5" Ref="C16"  Part="1" 
AR Path="/5D5DC66E/5D5CF1A5" Ref="C15"  Part="1" 
AR Path="/5D5E688C/5D5CF1A5" Ref="C12"  Part="1" 
AR Path="/5D5EF4F5/5D5CF1A5" Ref="C13"  Part="1" 
AR Path="/5D61A1B6/5D5CF1A5" Ref="C14"  Part="1" 
AR Path="/5D5AAFF5/5D5CF1A5" Ref="C11"  Part="1" 
AR Path="/5E891FD9/5D5CF1A5" Ref="C?"  Part="1" 
AR Path="/5E892449/5D5CF1A5" Ref="C?"  Part="1" 
F 0 "C11" H 6300 4150 50  0000 L CNN
F 1 "10uF @ 25V" H 6300 4050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6200 4100 50  0001 C CNN
F 3 "~" H 6200 4100 50  0001 C CNN
	1    6200 4100
	1    0    0    -1  
$EndComp
Connection ~ 5900 4000
Wire Wire Line
	5900 4000 6200 4000
Wire Wire Line
	6800 4100 6800 4200
Wire Wire Line
	6200 4000 6800 4000
Wire Wire Line
	6200 4200 6800 4200
Text Notes 5450 3150 0    50   ~ 0
The capacitor and inductor values don't need to be exact,\nbigger is (mostly) better.
Wire Wire Line
	5900 4200 5900 4400
Connection ~ 5900 4200
Wire Wire Line
	5400 4600 5600 4600
$EndSCHEMATC
