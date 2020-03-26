# UART library short introduction

In this short introduction the basic functions of the uart library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name          | Value(s)            | Description                                         |
|---------------|:--------------------|-----------------------------------------------------|
| F_CPU         | System Clock        | Setup the system clock speed                        |
| BAUD          | Baudrate            | 9600 / 19200 / ...                                  |
| UART_DATASIZE | Datasize            | 5,6,...,8                                           |
| UART_PARITY   | Parity              | 0 (none), 1 (even), 2(odd)                          |
| UART_STOPBITS | Stopbits            | 1,2                                                 |
| UART_RXC_ECHO | Echo                | Enabled: Received data will be returned to sender   |
| UARTRXCIE     | defined/undefined   | Receiver Interrupt processing                       |
| UARTTXCIE     | defined/undefined   | Transmitter Interrupt processing                    |
| UARTUDRIE     | defined/undefined   | Data register interrupt processing                  |

## Initial Function

```c
void uart_init(void);
```

---

## Transmit single character

```c
int uart_putchar(char c, FILE *stream);
```

#### c
| Value(s)      | Description                                |
|--------------:|:------------------------------------------:|
| unsigned char | Byte/ASCII char for transmission over UART |

#### stream
| Value(s)      | Description                                |
|--------------:|:------------------------------------------:|
| FILE          | Pointer to file stream (stdout, stderr)    |

---

## Receive single character

```c
int uart_getchar(FILE *stream);
```

#### stream
| Value(s)      | Description                                |
|--------------:|:------------------------------------------:|
| FILE          | Pointer to file stream (stdin)             |

#### Function Return
| Return        | Status                             |
|--------------:|:----------------------------------:|
| 0x00          | Error during transmission occurred |
| unsigned char | Received data                      |

---

## Reset Function
Clear errors that occurred during transmissions

```c
void uart_error(void);
```

---
