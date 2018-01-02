# LCD library short introduction

In this short introduction the basic function of the lcd library and their usage are described. If there are any issues or improvements please feel free to report.

## Directives

| Name                | Value(s)      | Description                                |
|---------------------|:--------------|--------------------------------------------|
| F_CPU               | System Clock  | Setup the system clock speed               |
| F_LCD               | LCD Clock     | LCD clock speed .../100000/...             |
| LCD_DDR_CTRL        | DDRx          | Control data direction register            |
| LCD_PORT_CTRL       | PORTx         | Control port                               |
| LCD_RS              | Px(0..7)      | Register select pin                        |
| LCD_E               | Px(0..7)      | Clock line                                 |
| LCD_DDR_DATA        | DDRx          | Data direction register                    |
| LCD_PORT_DATA       | PORTx         | Data port                                  |
| LCD_DB0             | Px(0..7       | Pin for databit (0)/Display bit (4)        |
| LCD_DB1             | Px(0..7       | Pin for databit (1)/Display bit (5)        |
| LCD_DB2             | Px(0..7       | Pin for databit (2)/Display bit (6)        |
| LCD_DB3             | Px(0..7       | Pin for databit (3)/Display bit (7)        |
| LCD_COLUMNS         | 1 - 20        | Columns in each row                        |
| LCD_START_ADDR      | 0x80          | Start position of LCD ram                  |
|                     |               |                                            |
| LCD_STARTUP_TIME    | 10            | Statup time in ms                          |
| LCD_RETURN_TIME     | 2             | Return home time in ms                     |
| LCD_ENTRY_TIME      | 37 (not used) | Entry mode time in us                      |
| LCD_DISPLAY_TIME    | 37 (not used) | Display time in us                         |
| LCD_SHIFT_TIME      | 37 (not used) | Shift cursor time in us                    |
| LCD_FUNCTION_TIME   | 37            | Function time in us                        |
| LCD_WRITE_TIME      | 37            | Write data time in us                      |
| LCD_CMD_TIME        | 37            | Command execution time in us               |
|                     |               |                                            |
| LCD_CLEAR           | 0b00000001    | Clear screen instruction                   |
| LCD_HOME            | 0b00000010    | Return home instruction                    |
| LCD_ENTRY           | 0b00000100    | Entry mode instruction                     |
| LCD_ENTRY_INCREMENT | 0b00000010    | Add to entry mode to increment cursor      |
| LCD_ENTRY_SHIFT     | 0b00000001    | Add to entry mode to shift data            |
| LCD_DISPLAY         | 0b00001000    | Display instruction                        |
| LCD_DISPLAY_ON      | 0b00000100    | Add to display to enable it                |
| LCD_CURSOR_ON       | 0b00000010    | Add to display to enable cursor            |
| LCD_BLINK_ON        | 0b00000001    | Add to display to enable cursor blink      |
| LCD_SHIFT           | 0b00010000    | Shift instruction                          |
| LCD_SHIFT_DISPLAY   | 0b00001000    | Add to shift to shift display              |
| LCD_SHIFT_RIGHT     | 0b00000100    | Add to shift to shift display/cursor right |
| LCD_FUNCTION        | 0b00100000    | Function instruction                       |
| LCD_FUNCTION_8BIT   | 0b00010000    | Add to function to enable 8 bit mode       |
| LCD_FUNCTION_2LINE  | 0b00001000    | Add to function to enable 2 line mode      |
| LCD_FUNCTION_5x10   | 0b00000100    | Add to function to enable 5x10 LCD mode    |
|                     |               |                                            |
| LCD_CGADDR          | 0b01000000    | Character generator RAM address            |
| LCD_CGADDR_CHAR0    | 0b00000000    | Start position of first CGRAM character    |
| LCD_CGADDR_CHAR1    | 0b00000001    | Start position of first CGRAM character    |
| LCD_CGADDR_CHAR2    | 0b00000010    | Start position of first CGRAM character    |
| LCD_CGADDR_CHAR3    | 0b00000011    | Start position of first CGRAM character    |
| LCD_CGADDR_CHAR4    | 0b00000100    | Start position of first CGRAM character    |
| LCD_CGADDR_CHAR5    | 0b00000101    | Start position of first CGRAM character    |
| LCD_CGADDR_CHAR6    | 0b00000110    | Start position of first CGRAM character    |
| LCD_CGADDR_CHAR7    | 0b00000111    | Start position of first CGRAM character    |
| LCD_DDADDR          | 0b10000000    | Character data ROM address                 |
|                     |               |                                            |
| LCD_SPACE           | 0x20          | ASCII space character                      |
| LCD_NULL            | 0x00          | ASCII '\0' escape string                   |

## Initial Function

```c
void lcd_init(void)
```

---

## Disable Function

```c
void lcd_disable(void)
```

---

## Clock Function

```c
void lcd_clock(void)
```

---

## Write data Function

```c
void lcd_set(unsigned char data)
```

#### data
| Value(s)            | Description                     |
|--------------------:|:-------------------------------:|
| unsigned char (7:4) | Write data to databus bit (7:4) |

---

## Write instruction to Display

```c
void lcd_cmd(unsigned char data)
```

#### data
| Value(s)      | Description                  |
|--------------:|:----------------------------:|
| unsigned char | Write instruction to display |

---

## Write character to Display

```c
void lcd_char(unsigned char data)
```

#### data
| Value(s)      | Description           |
|--------------:|:---------------------:|
| unsigned char | Write data to display |

---

## Write string to display

```c
void lcd_string(const unsigned char *data)
```

#### *data (POINTER)
| Value(s)      | Description                              |
|--------------:|:----------------------------------------:|
| unsigned char | Pointer to Array with '\0' escape string |

---

## Clear display

```c
void lcd_clear(void)
```

---

## Cursor @ home

```c
void lcd_home(void)
```

---

## Set Cursor on display

```c
void lcd_cursor(unsigned char x, unsigned char y)
```

#### x
| Value(s)      | Description                                     |
|--------------:|:-----------------------------------------------:|
| unsigned char | Cursor position on line y (1-4) column x (1-20) |

#### y
| Value(s)      | Description                    |
|--------------:|:------------------------------:|
| unsigned char | Cursor position on line y (1-4)|

---

## Write Pattern to CGRAM

```c
void lcd_pattern(unsigned char address, const unsigned char *data)
```

#### address
| Value(s)      | Description         |
|--------------:|:-------------------:|
| unsigned char | CGRAM start address |

#### *data (POINTER)
| Value(s)      | Description                              |
|--------------:|:----------------------------------------:|
| unsigned char | Pointer to Array with '\0' escape string |

---

## Write unsigned long to display

```c
void lcd_ul2ascii(const unsigned long data, unsigned char base, unsigned char length)
```

#### data
| Value(s)      | Description                               |
|--------------:|:-----------------------------------------:|
| unsigned long | Number which should be converted to ASCII |

#### base
| Value(s)      | Description                     |
|--------------:|:-------------------------------:|
| unsigned char | Base for conversion 2/10/16/... |

#### length
| Value(s)      | Description                             |
|--------------:|:---------------------------------------:|
| unsigned char | Colums which the number uses on display |

---

## Write signed long to display

```c
void lcd_sl2ascii(const signed long data, unsigned char base, unsigned char length)
```

#### data
| Value(s)      | Description                               |
|--------------:|:-----------------------------------------:|
| signed long   | Number which should be converted to ASCII |

#### base
| Value(s)      | Description                     |
|--------------:|:-------------------------------:|
| unsigned char | Base for conversion 2/10/16/... |

#### length
| Value(s)      | Description                             |
|--------------:|:---------------------------------------:|
| unsigned char | Colums which the number uses on display |

---

## Write double to display

```c
void lcd_d2ascii(const double data, unsigned char length, unsigned char precision)
```

#### data
| Value(s)      | Description                               |
|--------------:|:-----------------------------------------:|
| double        | Number which should be converted to ASCII |

#### length
| Value(s)      | Description                 |
|--------------:|:---------------------------:|
| unsigned char | Length before decimal point |

#### precision
| Value(s)      | Description                   |
|--------------:|:-----------------------------:|
| unsigned char | Precision after decimal point |

---

