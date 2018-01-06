# PWM library short introduction

In this short introduction the basic function of the pwm library and their usage are described. If there are any issues or improvements please feel free to report.

## Calculation

#### Square Generation

**With match equal 0**

![Square](http://latex.codecogs.com/gif.download?f_%7BSQUARE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B256*2*PRESCALER%7D "Square equation")

```LATEX
f_{SQUARE}=\frac{F_{CPU}}{256*2*PRESCALER}
```

**With match not equal 0**

![Square](http://latex.codecogs.com/gif.download?f_%7BSQUARE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7BMATCH*2*PRESCALER%7D "Square equation")

```LATEX
f_{SQUARE}=\frac{F_{CPU}}{MATCH*2*PRESCALER}
```

#### Rectangle Generation

![Rectangle](https://latex.codecogs.com/gif.download?f_%7BRECTANGLE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B255*PRESCALER*STEP%7D "Square equation")

```LATEX
f_{RECTANGLE}=\frac{F_{CPU}}{255*PRESCALER*\frac{256}{STEP*2}}
```

#### Sawtooth Generation

![Sawtooth](https://latex.codecogs.com/gif.download?f_%7BRECTANGLE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B510*PRESCALER*%5Cfrac%7B256%7D%7BSTEP*2%7D%7D "Square equation")

```LATEX
f_{SAWTOOTH}=\frac{F_{CPU}}{255*PRESCALER*STEP}
```

#### Triangle Generation

![Triangle](https://latex.codecogs.com/gif.download?f_%7BRECTANGLE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B255*PRESCALER*%5Cfrac%7B256%7D%7BSTEP%7D%7D "Square equation")

```LATEX
f_{TRIANGLE}=\frac{F_{CPU}}{255*PRESCALER*\frac{256}{STEP}}
```

#### Ramp Generation


#### Sine Generation

![Sine](https://latex.codecogs.com/gif.download?f_%7BSINE%7D%3D%5Cfrac%7BF_%7BCPU%7D%7D%7B256*4*%281+TABLE_%7BLENGTH%7D*%28HOLD_%7BVALUE%7D+1%29%29%7D "Sine equation")

```LATEX
f_{SINE}=\frac{F_{CPU}}{256*4*(1+TABLE_{LENGTH}*(HOLD_{VALUE}+1))*PRESCALER}
```

## Directives

| Name             | Value(s)            | Description                             |
|------------------|:--------------------|-----------------------------------------|
| PWM_DDR          | DDRx                | Data direction register                 |
| PWM_PORT         | PORTx               | Signal port                             |
| PWM_PIN          | PINx                | Signal pin                              |
| PWM_PIN_OTHER    | Px(0..7)            | Special Pin for toggle bit (0..7)       |
| PWM_PIN_OC0      | Px(0..7)            | Default Pin for toggle bit (0..7)       |
| PWM_SQUARE       | none                | Enable square function (when defined)   |
| PWM_SAWTOOTH     | none                | Enable sawtooth function (when defined) |
| PWM_TRIANGLE     | none                | Enable triangle function (when defined) |

