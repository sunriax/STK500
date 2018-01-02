# TWI library short introduction

In this short introduction the basic function of the twi library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name          | Value(s)              | Description                        |
|---------------|:----------------------|------------------------------------|
| F_CPU         | System Clock          | Setup the system speed             |
| F_TWI         | TWI Clock             | .../100000/400000/...              |
| TWI_PRESCALE  | 0/1/2/3               | Samplerate of UART databit         |
| TWI_BITRATE   | none                  | Calculation of bitrate             |
| TWI_ADDRESS   | unsigned char (1-126) | Controller Slave address           |
| TWI_BROADCAST | 0=not/1=listen        | Accept general calls               |
| TWI_ACK       | 0x01                  | Acknowledge command                |
| TWI_NACK      | 0x01                  | Not Acknowledge command            |
| TWI_WRITE     | 0x00                  | Write command                      |
| TWI_READ      | 0x01                  | Read command                       |

**ATmega16 TWI status codes (!!!Do not change!!!)**
| Name                          | Value(s) | Description                                   |
|-------------------------------|:---------|-----------------------------------------------|
| TWI_STATUS_START              | 0x08     | Status after start bit has been sent          |
| TWI_STATUS_REPEATED_START     | 0x10     | Status after repeated start bit has been sent |
| TWI_STATUS_ADDRESS_WRITE_NACK | 0x18     | Status after address + write + nack           |
| TWI_STATUS_ADDRESS_WRITE_ACK  | 0x20     | Status after address + write + ack            |
| TWI_STATUS_DATA_WRITE_NACK    | 0x28     | Status after data + write + nack              |
| TWI_STATUS_DATA_WRITE_ACK     | 0x30     | Status after data + write + ack               |
| TWI_STATUS_ADDRESS_READ_NACK  | 0x38     | Status after address + read + nack            |
| TWI_STATUS_ADDRESS_READ_ACK   | 0x40     | Status after address + read + ack             |
| TWI_STATUS_DATA_READ_NACK     | 0x48     | Status after data + read + nack               |
| TWI_STATUS_DATA_READ_ACK      | 0x50     | Status after data + read + ack                |

## Initial Function

```c
unsigned char twi_init(unsigned char operation);
```

#### operation
| Value(s) | Description           |
|---------:|:---------------------:|
| 0x00     | Slave mode            |
| 0xFF     | Master mode (default) |

#### Function Return
| Return        | Status                         |
|--------------:|:------------------------------:|
| unsigned char | BIT (7:3) TWS7-TWS3, BIT2 TWWC |

---

## Transmit start bit

```c
unsigned char twi_start(void)
```

#### Function Return
| Return | Status             |
|-------:|:------------------:|
| 0x00   | Start successfully |
| 0xFF   | Start failure      |

---

## Transmit stop bit

```c
void twi_stop(void)
```

---

## Transmit address

```c
unsigned char twi_address(unsigned char address)
```

#### address
| Value(s)              | Description                   |
|----------------------:|:-----------------------------:|
| unsinged char (0-127) | Write TWI call address to bus |

#### Function Return
| Return | Status             |
|-------:|:------------------:|
| 0x00   | Call successfully  |
| 0xFF   | Call failure       |

---

## Transmit data

```c
unsigned char twi_set(unsigned char data)
```

#### data
| Value(s)      | Description           |
|--------------:|:---------------------:|
| unsigned char | Write TWI data to bus |

#### Function Return
| Return | Status                     |
|-------:|:--------------------------:|
| 0x00   | Transmit data successfully |
| 0xFF   | Transmit data failure      |

---

## Receive data

```c
unsigned char twi_get(unsigned char *data)
```

#### *data
| Value(s)                   | Description                                                            |
|---------------------------:|:----------------------------------------------------------------------:|
| ACK/NACK / (unsigned char) | Pointer to data byte (setup ACK/NACK) data is written to the data byte |

#### Function Return
| Return | Status                    |
|-------:|:-------------------------:|
| 0x00   | Receive data successfully |
| 0xFF   | Receive data failure      |

---

