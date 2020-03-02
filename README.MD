<h1>Light Controller</h1>
<p>
This repository contains source code for simple light controller based on <i>Arduino</i>
dev board. The controller has various inputs:
</p>

<ul>
<li>Photoresistor</li>
<li>Potentiometer</li>
<li>PIR sensor</li>
</ul>

<p>
The output is in the form of Relay module that controls the power cord to the light.
</p>

<h3>Logic</h3>
<p>
The photoresistor relays the information about current light level to the arduino via a simple voltage divider. This information is compared to the limit value and if it is evaluated as sufficient the relay is turned on. The potentiometer serves as fine-tuning device to increase or decrease the light level limit value.
</p>