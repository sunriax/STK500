# SPI library short introduction

In this short introduction the basic function of the spi library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name          | Value(s)            | Type | Master | Slave | Description                  |
|---------------|:--------------------|:----:|:------:|:-----:|------------------------------|
| SPI2X         | none                |      |        |       | SPI double speed mode        |
| SPI_SPIE      | none                |      |        |       | SPI interrupt control enable |
| SPI_DDR       | DDRA/B/C/D/...      | REG  |        |       | SPI Data direction register  |
| SPI_PORT      | PORTA/B/C/D/...     | REG  |        |       | SPI Port                     |
| SPI_SS        | PA/B/C/D/...(1..x)  | I/O  |   O    |   I   | SPI Slave select pin         |
| SPI_MOSI      | PA/B/C/D/...(1..x)  | I/O  |   O    |   I   | SPI Master out slave in pin  |
| SPI_MISO      | PA/B/C/D/...(1..x)  | I/O  |   I    |   O   | SPI Master in slave out pin  |
| SPI_SCK       | PA/B/C/D/...(1..x)  | I/O  |   O    |   I   | SPI Clock pin                |
| SPI_WCOL_PORT | PORTA/B/C/D/...     | REG  |        |       | SPI Error display port       |
| SPI_WCOL_PIN  | PA/B/C/D/...(1..x)  | I/O  |   O    |   I   | SPI Error display pin        |


## Initial Function

```c
unsigned char spi_init(unsigned char operation, unsigned char direction, unsigned char polarity, unsigned char spiclock);
```

#### operation
| Value(s) | Function | Description            |
|---------:|:--------:|------------------------|
| 0x00     | Master   | SPI Master mode        | 
| 0xFF     | Slave    | SPI Slave mode         |

#### direction
| Value(s) |  Function   |
|---------:|:-----------:|
| 0x00     | MSB first   |
| 0xFF     | LSB first   |

#### polarity
| Value(s) | Idle | Phase  |
|---------:|:----:|:------:|
| 0x00     | LOW  | Offset |
| 0x01     | LOW  | Direct |
| 0x02     | HIGH | Offset |
| 0x03     | HIGH | Direct |

#### spiclock
| Value(s) | SPI2X=0      | SPI2X=1     |
|---------:|--------------|-------------|
| 0x00     | Sysclock/4   | Sysclock/2  |
| 0x01     | Sysclock/16  | Sysclock/8  |
| 0x02     | Sysclock/64  | Sysclock/32 |
| 0x03     | Sysclock/128 | Sysclock/64 |

#### Function Return
| Return | Status           |
|-------:|:----------------:|
| 0xFF   | Master abort     |
| SPCR   | Control Register |

---

## SPI Slave Select Function

```c
void spi_select(unsigned char mode);
```

#### mode
| Value(s) | Status | Description                 |
|---------:|:------:|-----------------------------|
| 0x00     | OFF    | SPI Slave select off (HIGH) | 
| 0xFF     | ON     | SPI Slave select on (LOW)   |

---

## SPI Transfer Function

```c
unsigned char spi_transfer(unsigned char data);
```

#### data
| Value(s)      | Description         |
|--------------:|---------------------|
| unsigned char | Transmit data byte  | 

#### Function Return
| Return        | Status              |
|--------------:|:-------------------:|
| unsigned char | Received data byte  |

---
