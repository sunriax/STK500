# PWM library short introduction

In this short introduction the basic function of the pwm library and their usage are described. If there are any issues or improvements please feel free to report.

## Calculation

### Square Generation

**With match equal 0**

![Square](http://latex.codecogs.com/gif.latex?f_%7BSQUARE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B255*2*PRESCALER%7D)

```LATEX
f_{SQUARE}=\frac{F_{CPU}}{256*2*PRESCALER}
```

**With match not equal 0**

![Square](http://latex.codecogs.com/gif.latex?f_%7BSQUARE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7BMATCH*2*PRESCALER%7D)

```LATEX
f_{SQUARE}=\frac{F_{CPU}}{MATCH*2*PRESCALER}
```

### Rectangle Generation

![Rectangle](http://latex.codecogs.com/gif.latex?f_%7BRECTANGLE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B255*PRESCALER*STEP%7D)

```LATEX
f_{RECTANGLE}=\frac{F_{CPU}}{255*PRESCALER*\frac{256}{STEP*2}}
```

### Sawtooth Generation

![Sawtooth](http://latex.codecogs.com/gif.latex?f_%7BRECTANGLE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B510*PRESCALER*%5Cfrac%7B256%7D%7BSTEP*2%7D%7D)

```LATEX
f_{SAWTOOTH}=\frac{F_{CPU}}{255*PRESCALER*STEP}
```

### Triangle Generation

![Triangle](http://latex.codecogs.com/gif.latex?f_%7BRECTANGLE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B255*PRESCALER*%5Cfrac%7B256%7D%7BSTEP%7D%7D)

```LATEX
f_{TRIANGLE}=\frac{F_{CPU}}{255*PRESCALER*\frac{256}{STEP}}
```

### Ramp Generation

![Ramp](https://latex.codecogs.com/gif.latex?f_%7BRAMP%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B%5Cfrac%7B255%7D%7B2%7D*PRESCALER*%28%5Cfrac%7B510%7D%7BUP%7D+%5Cfrac%7B510%7D%7BDOWN%7D%29%7D)

```LATEX
f_{RAMP}=\frac{F_{CPU}}{\frac{255}{2}*PRESCALER*(\frac{510}{UP}+\frac{510}{DOWN})}
```

### Sine Generation

![Sine](http://latex.codecogs.com/gif.latex?f_%7BSINE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B256*4*%281+TABLE_%7BLENGTH%7D*%28HOLD_%7BVALUE%7D+1%29%29%7D)

```LATEX
f_{SINE}=\frac{F_{CPU}}{256*4*(1+TABLE_{LENGTH}*(HOLD_{VALUE}+1))*PRESCALER}
```

## Directives

| Name             | Value(s)            | Description                                                |
|------------------|:--------------------|------------------------------------------------------------|
| PWM_DDR          | DDRx                | Data direction register                                    |
| PWM_PORT         | PORTx               | Signal port                                                |
| PWM_PIN          | PINx                | Signal pin                                                 |
| PWM_PIN_OTHER    | Px(0..7)            | Special Pin for toggle bit (0..7)                          |
| PWM_PIN_OC0      | Px(0..7)            | Default Pin for toggle bit (0..7)                          |
| PWM_SQUARE       | defined/undefined   | Enable square function                                     |
| PWM_LINEAR       | defined/undefined   | Enable linear functions (rectangle/sawtooth/triangle/ramp) |
| PWM_SINE         | defined/undefined   | Enable sine function                                       |
| PWM_OCIE         | defined/undefined   | Enables timer compare match vector                         |
| PWM_TOIE         | defined/undefined   | Enables timer overflow vector                              |

## Initial Function

```c
void pwm_init(unsigned char prescaler)
```

#### prescaler
| Value(s)            | Description                                 |
|--------------------:|:-------------------------------------------:|
| unsigned char (2:0) | Setup prescaler (1/8/64/256/1024) for timer |

---

## Disable Function

```c
void pwm_disable(void)
```

---

## Square Function
_(see calculation for match initialisation)_

```c
void pwm_init(unsigned char match)
```

#### prescaler
| Value(s)      | Description                                  |
|--------------:|:--------------------------------------------:|
| unsigned char | Setup square frequency for PWM(50:50) signal |

---

## Linear Function
_(see calculation for step initialisation)_

```c
void pwm_init(unsigned char type, unsigned int step)
```

#### type
| Value(s) | Description               |
|---------:|:-------------------------:|
| 0x01     | Generate rectangle signal |
| 0x02     | Generate sawtooth signal  |
| 0x03     | Generate triangle signal  |
| 0x04     | Generate ramp signal      |

#### type
| Value(s)            | Description                                                           |
|--------------------:|:---------------------------------------------------------------------:|
| unsigned int (7:0)  | Rectange PWM width setting and sawtooth/triangle/ramp step up setting |
| unsigned int (15:8) | Triangle/Ramp step down setting                                       |

---

## Sine Function
_(see calculation for hold initialisation)_
**Choose a PWM_SINE_TABLE**

```c
void pwm_sine(unsigned char hold);
```

#### hold
| Value(s)      | Description                                                      |
|--------------:|:----------------------------------------------------------------:|
| unsigned char | Setup how long a sine value form TABLE is hold on the PWM output |

---







