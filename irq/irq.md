# IRQ library short introduction

In this short introduction the basic functions of the irq library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name    | Value(s)              | Description                                                |
|---------|:----------------------|------------------------------------------------------------|
| IRQ_ISR | defined/undefined     | Enable Interrupt handler                                   |

## IRQ Initialization

```c
unsigned char irq_init(unsigned char mode)
```

#### presacler
| Value(s)  | Description               |
|----------:|:-------------------------:|
| 0x00      | INT0 PIN low state        |
| 0x01      | INT0 PIN state changing   |
| 0x02      | INT0 PIN falling edge     |
| 0x03      | INT0 PIN rising edge      |

#### Function Return
| Return | Status                                |
|-------:|:-------------------------------------:|
| MCUCR  | MCU control register (see datasheet)  |

---

## IRQ Status

(Only works with IRQ_ISR undefined)

```c
unsigned char irq_status(void)
```

#### Function Return
| Return | Status                  |
|-------:|:------------------------|
| 0x00   | No interrupt set        |
| 0xFF   | INT0 interrupt flag set |

---




