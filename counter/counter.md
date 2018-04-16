# COUNTER library short introduction

In this short introduction the basic functions of the counter library and their usage are described. If there are any issues or improvements please feel free to report.

## Time Calculation

### Timer overflow setup

![Overflow](http://latex.codecogs.com/gif.latex?t_%7BOverflow%7D%3D%5Cfrac%7B256*PRESCALER%7D%7BF_%7BCPU%7D%7D)

```LATEX
t_{Overflow}=\frac{256*PRESCALER}{F_{CPU}}
```

### Timer compare match setup

![Compare](http://latex.codecogs.com/gif.latex?t_%7BCompare%7D%3D%5Cfrac%7B%281+OCR%29*PRESCALER%7D%7BF_%7BCPU%7D%7D)

```LATEX
t_{Compare}=\frac{(1+OCR)*PRESCALER}{F_{CPU}}
```

## Directives

| Name           | Value(s)              | Description                                                |
|----------------|:----------------------|------------------------------------------------------------|
| COUNTER_TOGGLE | 0x00 - 0x03           | Setup PORT toggle mode (none, toggle, clear, set)          |
| COUNTER_CTC    | defined/undefined     | Enable CTC mode (defined)/Enable overflow mode (undefined) |
| COUNTER_ISR    | defined/undefined     | Enable Interrupt handler
                                |
## Counter Initialization

```c
unsigned char counter_init(unsigned char prescaler)
```

#### presacler
| Value(s) | Description                       |
|---------:|:---------------------------------:|
| 0x00     | no prescaler selected             |
| 0x01     | F_CPU                             |
| 0x02     | F_CPU/8                           |
| 0x03     | F_CPU/64                          |
| 0x04     | F_CPU/256                         |
| 0x05     | F_CPU/1024                        |
| 0x06     | External Clock (T0, falling edge) |
| 0x07     | External Clock (T0, rising edge)  |

#### Function Return
| Return | Status                                |
|-------:|:-------------------------------------:|
| TCCR0  | Timer Counter Control Register status |

---

## Counter Reset

```c
void counter_reset(void)
```

---

## Counter Start

```c
void counter_start(unsigned char prescaler)
```

#### prescaler
| Value(s)      | Description                                                                            |
|--------------:|:--------------------------------------------------------------------------------------:|
| unsigned char | If zero value before stop will be used, otherwise the new prescaler value will be used |

---

## Counter Stop

```c
void counter_stop(void)
```

---

## Counter Limit

(Only works with COUNTER_CTC defined)

```c
void counter_limit(unsigned char data)
```

#### prescaler
| Value(s)      | Description                                |
|--------------:|:------------------------------------------:|
| unsigned char | Sets up the counter compare match register |

---

## Counter Overflow

(Only works with COUNTER_ISR undefined)

```c
unsigned char counter_overflow(void)
```

#### Function Return
| Return | Status                                          |
|-------:|:-----------------------------------------------:|
| 0x00   | No interrupt set                                |
| 0xFF   | Timer Overflow/Compare match interrupt flag set |

---




