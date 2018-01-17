# PORT library short introduction

In this short introduction the basic functions of the port library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name          | Value(s)            | Type | Master | Slave | Description                  |
|---------------|:--------------------|:----:|:------:|:-----:|------------------------------|

## Initial Function

```c
unsigned char port_init(unsigned char port, unsigned char direction, unsigned char pullup);
```

#### port
| Value(s)   | Function | Description            |
|-----------:|:--------:|------------------------|
| 0b00000001 | PORTA    | Select and setup PORTA |
| 0b00000010 | PORTB    | Select and setup PORTB |
| 0b00000100 | PORTC    | Select and setup PORTC |
| 0b00001000 | PORTD    | Select and setup PORTD |

#### direction
| Value(s)      | Option           | Function                             |
|--------------:|:-----------------|:-------------------------------------|
| unsigned char | 0=Input/1=Output | Setup the direction of each port bit |

#### pullup
| Value(s)      | Option           | Function                                                 |
|--------------:|:-----------------|:---------------------------------------------------------|
| unsigned char | 0=none/1=active  | Setup the pullup of each port bit (works only for input) |

#### Function Return
| Return | Status              |
|-------:|:-------------------:|
| 0x00   | PORT setup complete |
| 0xFF   | PORT setup failed   |

---

## Disable Function

```c
unsigned char port_disable(unsigned char port);
```

#### port
| Value(s)   | Function | Description                  |
|-----------:|:--------:|------------------------------|
| 0b00000001 | PORTA    | Disable PORTA (set to input) |
| 0b00000010 | PORTB    | Disable PORTB (set to input) |
| 0b00000100 | PORTC    | Disable PORTC (set to input) |
| 0b00001000 | PORTD    | Disable PORTD (set to input) |

#### Function Return
| Return | Status                |
|-------:|:---------------------:|
| 0x00   | PORT disable complete |
| 0xFF   | PORT disable failed   |

---

## Write Function

```c
unsigned char port_write(unsigned char port, unsigned char data, unsigned char logic);
```

#### port
| Value(s)   | Function | Description    |
|-----------:|:--------:|----------------|
| 0b00000001 | PORTA    | Write to PORTA |
| 0b00000010 | PORTB    | Write to PORTB |
| 0b00000100 | PORTC    | Write to PORTC |
| 0b00001000 | PORTD    | Write to PORTD |

#### data
| Value(s)      | Function                             |
|--------------:|:-------------------------------------|
| unsigned char | Data which should be written to PORT |

#### pullup
| Value(s)      | Option           | Function                                                 |
|--------------:|:-----------------|:---------------------------------------------------------|
| unsigned char | 0=none/1=active  | Setup the pullup of each port bit (works only for input) |

#### logic
| Value(s) | Function | Description            |
|---------:|:--------:|------------------------|
| 0        | direct   | Write direct to port   |
| 1        | or       | Write with or to port  |
| 2        | and      | Write with and to port |

#### Function Return
| Return | Status              |
|-------:|:-------------------:|
| 0x00   | PORT setup complete |
| 0xFF   | PORT setup failed   |

---

## Read Function

```c
unsigned char pin_read(unsigned char pin, unsigned char bit, unsigned char logic);
```

#### pin
| Value(s)   | Function | Description    |
|-----------:|:--------:|----------------|
| 0b00000001 | PINA     | Read from PINA |
| 0b00000010 | PINB     | Read from PINB |
| 0b00000100 | PINC     | Read from PINC |
| 0b00001000 | PIND     | Read from PIND |

#### bit
| Value(s)      | Function                           |
|--------------:|:-----------------------------------|
| unsigned char | Select which bit(s) should be read |

#### logic
| Value(s) | Function              |
|---------:|:----------------------|
| 0x00     | Select negative logic |
| 0xFF     | Select positive logic |

#### Function Return
| Return | Status                  |
|-------:|:-----------------------:|
| 0x00   | PIN bit(s) is/are set   |
| 0xFF   | PIN bit(s) is/are unset |

---








