import math
from time import sleep_ms
import machine

pin = machine.Pin(2, machine.Pin.OUT)
led = machine.PWM(pin, freq=1000)

def set_duty(l, d, t):
    l.duty(d)
    sleep_ms(t)

def pulse(l, t):
    for i in range(10):
        d = int(1023 - math.sin(i / 10 * math.pi) * 1023)
        set_duty(led, d, t)
    set_duty(led, 1023, t)

while True:
    pulse(led, 50)
    sleep_ms(500)