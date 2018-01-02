# ADC library short introduction

In this short introduction the basic function of the adc library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name                | Value(s) | Description                                                 |
|---------------------|:---------|-------------------------------------------------------------|
| ADC_REF             | 0x00     | AREF/                                                       |
|                     | 0x01     | AVCC                                                        |
|                     | 0x03     | 2.56V                                                       |
| ADC_CHANNEL_MODE    | 0x00     | 8 unipolar channels                                         |
|                     | 0x01     | 2 differential channels with amplification                  |
|                     | 0x02     | 7 differential channels through ADC1 (negativ)              |
|                     | 0x03     | 5 differential channels through ADC2 (negativ)              |
| ADC_MODE            | 0x00     | Single transformation                                       |
|                     | 0x01     | Permanent transformation                                    |
| ADC_DATA_SHIFT      | 0x00     | Right shift ( MSB -> Bit 10/ LSB -> Bit 0                   |
|                     | 0x01     | Left shift ( MSB -> Bit 16/ LSB -> Bit 6                    |
| ADC_PRESCALER       | 0x00     | F_ADC = F_CPU / 2                                           |
|                     | 0x01     | F_ADC = F_CPU / 2                                           |
|                     | 0x02     | F_ADC = F_CPU / 4                                           |
|                     | 0x03     | F_ADC = F_CPU / 8                                           |
|                     | 0x04     | F_ADC = F_CPU / 16                                          |
|                     | 0x05     | F_ADC = F_CPU / 32                                          |
|                     | 0x06     | F_ADC = F_CPU / 64                                          |
|                     | 0x07     | F_ADC = F_CPU / 128                                         |
| ADC_NOISE_REDUCTION | none     | For reducing Noise during conversion (0=disabled/1=enabled) |
| ADC_TRIGGER_SOURCE  | 0x00     | Free running mode                                           |
|                     | 0x01     | Analog comarator mode                                       |
|                     | 0x02     | External Interrupt (0)                                      |
|                     | 0x03     | Timer 0 compare                                             |
|                     | 0x04     | Timer 0 overflow                                            |
|                     | 0x05     | Timer 1 compare B                                           |
|                     | 0x06     | Timer 1 overflow                                            |
|                     | 0x07     | Timer 1 capture                                             |
| ADC_ADIE            | none     | ADC conversion through interrupt (uncomment to enable)      |

## Initial Function

```c
void adc_init(void)
```

---

## Disable Function

```c
void adc_disable(void)
```

---

## Select A/D Channel

```c
void adc_channel(unsigned char channel)
```

#### channel
| Value(s)    | Description          |
|------------:|:--------------------:|
| 0x00 - 0x07 | Select channel 0 - 7 |

---

## Read A/D Channel data

```c
unsigned int adc_read(void)
```

#### Function Return
| Return       | Status                                 |
|-------------:|:--------------------------------------:|
| unsigned int | ADC Data (10 Bit) Right/Left justified |

---

## Build average from A/D Channel data

```c
unsigned int adc_average(unsigned char size)
```

#### size
| Value(s)      | Description                                          |
|--------------:|:----------------------------------------------------:|
| unsigned char | How many samples should be used for average building |

#### Function Return
| Return       | Status                       |
|-------------:|:----------------------------:|
| unsigned int | builded average from samples |

---

