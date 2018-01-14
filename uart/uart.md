# UART library short introduction

In this short introduction the basic functions of the uart library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name          | Value(s)            | Description                        |
|---------------|:--------------------|------------------------------------|
| F_CPU         | System Clock        | Setup the system clock speed       |
| BAUD          | Baudrate            | 9600 / 19200 / ...                 |
| U2XEN         | defined/undefined   | Samplerate of UART databit         |
| UARTRXCIE     | defined/undefined   | Receiver Interrupt processing      |
| UARTTXCIE     | defined/undefined   | Transmitter Interrupt processing   |
| UARTUDRIE     | defined/undefined   | Data register interrupt processing |

## Initial Function

```c
void uart_init(unsigned char datasize, unsigned char parity, unsigned char stopbits);
```

#### datasize
| Value(s) | Description          |
|---------:|:--------------------:|
| 5        | 5 Bit mode           |
| 6        | 6 Bit mode           |
| 7        | 7 Bit mode           |
| 8        | 8 Bit mode (default) |
| 6        | 9 Bit mode           |

#### parity
| Value(s) | Description               |
|---------:|:-------------------------:|
| 'N'      | Parity bit none (default) |
| 'O'      | Parity bit Odd            |
| 'E'      | Parity bit Even           |

#### stopbits
| Value(s) | Description          |
|---------:|:--------------------:|
| 1        | 1 Stopbit (default)  |
| 2        | 2 Stopbits           |

---

## Disable Function

```c
void uart_disable(void);
```

---

## Transmit single character

```c
void uart_setchar(unsigned char data)
```

#### data
| Value(s)      | Description                                |
|--------------:|:------------------------------------------:|
| unsigned char | Byte/ASCII char for transmission over UART |

---

## Transmit string

```c
void uart_setstring(unsigned char *string, unsigned char delimiter)	
```

#### *string (POINTER)
| Value(s)      | Description                              |
|--------------:|:----------------------------------------:|
| unsigned char | Pointer to Array with '\0' escape string |

#### delimiter
| Value(s) | Description                  |
|---------:|:----------------------------:|
| 0        | ASCII character NUL          |
| 1        | ASCII character CR           |
| 2        | ASCII character LF           |
| 3        | ASCII character LF + CR      |
| 4        | ASCII character TAB          |
| 5        | ASCII character SPACE        |
| 6        | ASCII character ESC          |

---

## Receive single character

```c
unsigned char uart_getchar(unsigned char *data, unsigned char echo)
```

#### *data (POINTER)
| Value(s)      | Description                                                            |
|--------------:|:----------------------------------------------------------------------:|
| unsigned char | Pointer to byte which will be filled after UART data has been received |

#### echo
| Value(s) | Description                            |
|---------:|:--------------------------------------:|
| 0x00     | no Echo (Transmission over UART)       |
| 0xFF     | Send received character back over UART |

#### Function Return
| Return | Status                    |
|-------:|:-------------------------:|
| 0x00   | No Data has been received |
| 0xFF   | Data has been received    |
| 0x01   | Frame error               |
| 0x02   | Receiver overflow         |
| 0x03   | Parity error              |

---

## Receive string

```c
unsigned char uart_getstring(unsigned char *string, unsigned char length, unsigned char delimiter, unsigned char echo)
```

#### *string (POINTER)
| Value(s)      | Description               |
|--------------:|:-------------------------:|
| unsigned char | Pointer to array (buffer) |

#### length
| Value(s)      | Description            |
|--------------:|:----------------------:|
| unsigned char | Size of array (buffer) |

#### delimiter
| Value(s)      | Description                                     |
|--------------:|:-----------------------------------------------:|
| unsigned char | ASCII character when received data has finished |

#### echo
| Value(s) | Description                                      |
|---------:|:------------------------------------------------:|
| 0x00     | no Echo (Transmission over UART)                 |
| 0xF0     | Send received string back over UART with CR + LF |
| 0xFF     | Send received string back over UART              |

#### Function Return
| Return | Status                                          |
|-------:|:-----------------------------------------------:|
| 0x00   | Data has been received                          |
| 0xFF   | Array (buffer) overflow / delimiter not found   |
| 0x01   | Frame error                                     |
| 0x02   | Receiver overflow                               |
| 0x03   | Parity error                                    

---

## Reset Function
Clear the UART status register

```c
void uart_reset(void);
```

---

