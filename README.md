# OverCurrnt-Relay-IDMT-
[For Details click this link]
Over-current protection is a very important element in power systems. 
This protection is essential in order to minimize disturbances caused by 
any failure in the system and to ensure continuous power delivery.
Over current relays are one of the devices used to achieve these purposes. 
The over-current relays initiate the corrective mechanism to determine
 the operation time of the relay. Thus, the over-current relays must have 
high reliability and accuracy to detect any fault currents present and 
determine the operation time. The entire system will tremendously affected 
if the relays fail to trip or cause mal-tripping. An over-current relay
is implemented on a high speed and high performance 
digital signal processor (DSP).  
The simulation was carried out using MATLAB/Simulink. Then, the 
relay was implemented on LM4F123GXL based on two different methods
Digital Relay
Numeric Relay

Computer-based system with software-based protection algorithms for the detection of electrical faults.
Also called  microprocessor type protective relays
Replacements for electro mechanical protective relays.
Over Current Relay
When the current flowing into the overcurrent relay exceeds a set point amount, 
the relay operates with or without an intended time delay and trips the associated circuit breakers.
IDMT (inverse definite minimum time)
IDMT is the relay which starts to operate after the intended time delay. 
Greater the fault currents, the shorter are their operating time


Algorithm 
Current is sampled At least sampling rate >=2(Signal Frequency ) Nquist Criteria
RMS Value of I is Calculated
Then Operating time is calculated using algorithm. 
If Irms>Iset Timers starts ticking
Circuit Breaker is tripped after time 




