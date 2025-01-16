#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define SUCCEED 0
#define ERROR -1

#define MINUS_FLAG 0b1
#define PLUS_FLAG 0b10
#define SPACE_FLAG 0b100

#define H_LENGH_FLAG 0b1
#define L_LENGH_FLAG 0b10
#define L_CAPS_LENGH_FLAG 0b100

typedef enum SPECIFICATORS { C, F, S, PERCENT, I, U, D } SPECIFICATORS;

int ParseSpecificator(const char **format_pointer, int *flags, int *width,
                      int *precision, int *length, SPECIFICATORS *specificator);
int GetFlags(const char **format_pointer, int *flags);
int GetWidth(const char **format_pointer, int *width);
int GetPrecision(const char **format_pointer, int *precision);
int GetLength(const char **format_pointer, int *length);
int GetSpecificatior(const char **format_pointer, SPECIFICATORS *specificator);
int IsFlag(char c);
int IsDigit(char c);
int IsSpecificator(char c);
int IntToString(char **string_pointer, long long int number, int flags,
                int width, int precision, int radix);
int DoubleToString(char **string_pointer, double number, int flags, int width,
                   int precision);
int GetNumberLength(long long number, int radix);
int StringToString(char **string_pointer, char *string_input, int flags,
                   int width, int precision);
int CharToString(char **string_pointer, char char_input, int flags, int width);
int s21_sprintf(char *str, const char *format, ...) {
  int flags = 0, width = 0, precision = 0, length = 0;
  SPECIFICATORS specificator;
  int status = SUCCEED;
  va_list argument_list;
  va_start(argument_list, format);
  long long number;
  double double_number;
  char symbol;
  char *string_for_print;
  long long num_of_printed_char = 0;
  while (status == SUCCEED && *format) {
    if (*format != '%') {
      *str = *format++;
      str++;
      num_of_printed_char++;
    } else {
      format++;
      status = ParseSpecificator(&format, &flags, &width, &precision, &length,
                                 &specificator);
      switch (specificator) {
        case C:
          symbol = (char)va_arg(argument_list, int);
          num_of_printed_char += CharToString(&str, symbol, flags, width);
          break;
        case F:
          double_number = va_arg(argument_list, double);
          num_of_printed_char +=
              DoubleToString(&str, double_number, flags, width, precision);
          break;
        case S:
          string_for_print = va_arg(argument_list, char *);
          num_of_printed_char +=
              StringToString(&str, string_for_print, flags, width, precision);
          break;
        case PERCENT:
          *str = '%';
          str++;
          num_of_printed_char++;
          break;
        case I:
          number = va_arg(argument_list, long);
          number = (length & H_LENGH_FLAG) ? (short)number : number;
          number = (length & L_LENGH_FLAG) ? number : (int)number;
          num_of_printed_char +=
              IntToString(&str, number, flags, width, precision, 10);
          break;
        case U:
          if (flags & SPACE_FLAG) flags = flags - SPACE_FLAG;
          if (flags & PLUS_FLAG) flags = flags - PLUS_FLAG;
          number = va_arg(argument_list, long unsigned int);
          number =
              (length & H_LENGH_FLAG) ? (short unsigned int)number : number;
          number = (length & L_LENGH_FLAG) ? number : (unsigned int)number;
          num_of_printed_char +=
              IntToString(&str, number, flags, width, precision, 10);
          break;
        case D:
          number = va_arg(argument_list, long);
          number = (length & H_LENGH_FLAG) ? (short)number : number;
          number = (length & L_LENGH_FLAG) ? number : (int)number;
          num_of_printed_char +=
              IntToString(&str, number, flags, width, precision, 10);
          break;
        default:
          break;
      }
    }
  }
  *str = 0;
  va_end(argument_list);
  return num_of_printed_char;
}

int ParseSpecificator(const char **format_pointer, int *flags, int *width,
                      int *precision, int *length,
                      SPECIFICATORS *specificator) {
  int status = SUCCEED;
  status = GetFlags(format_pointer, flags);
  if (status == SUCCEED) status = GetWidth(format_pointer, width);
  if (status == SUCCEED) status = GetPrecision(format_pointer, precision);
  if (status == SUCCEED) status = GetLength(format_pointer, length);
  if (status == SUCCEED)
    status = GetSpecificatior(format_pointer, specificator);
  return status;
}

int GetFlags(const char **format_pointer, int *flags) {
  const char *format = *format_pointer;
  int status = SUCCEED;
  int _flags = 0;

  while (status == SUCCEED && IsFlag(*format)) {
    if (*format == '+') {
      if (_flags & PLUS_FLAG) {
        status = ERROR;
      } else {
        _flags |= PLUS_FLAG;
      }
      format++;
    } else if (*format == '-') {
      if (_flags & MINUS_FLAG) {
        status = ERROR;
      } else {
        _flags |= MINUS_FLAG;
      }
      format++;
    } else if (*format == ' ') {
      if (_flags & SPACE_FLAG) {
        status = ERROR;
      } else {
        _flags |= SPACE_FLAG;
      }
      format++;
    } else {
      status = ERROR;
    }
  }
  *flags = status == SUCCEED ? _flags : 0;
  *format_pointer = format;
  return status;
}

int GetWidth(const char **format_pointer, int *width) {
  const char *format = *format_pointer;
  int status = SUCCEED;
  unsigned int _width = 0;

  while (status == SUCCEED && IsDigit(*format)) {
    _width *= 10;
    _width += *format - '0';
    if (_width > INT_MAX) {
      status = ERROR;
    } else {
      format++;
    }
  }
  if (status == SUCCEED) {
    *format_pointer = format;
    *width = (int)_width;
  }
  return status;
}

int GetPrecision(const char **format_pointer, int *precision) {
  const char *format = *format_pointer;
  int status = SUCCEED;
  unsigned int _precision = 0;

  if (*format == '.') {
    format++;
    while (status == SUCCEED && IsDigit(*format)) {
      _precision *= 10;
      _precision += *format - '0';
      format++;
      if (_precision + *format - '0' > INT_MAX) {
        status = ERROR;
      }
    }
    if (status == SUCCEED) {
      *format_pointer = format;
      *precision = (int)_precision;
    }
  } else {
    *precision = -1;
  }
  return status;
}

int GetLength(const char **format_pointer, int *length) {
  const char *format = *format_pointer;
  int _length = 0;
  int status = SUCCEED;

  if (*format == 'h') {
    _length |= H_LENGH_FLAG;
    format++;
  } else if (*format == 'l') {
    _length |= L_LENGH_FLAG;
    format++;
  }

  *length = status == SUCCEED ? _length : *length;
  *format_pointer = format;
  return status;
}

int GetSpecificatior(const char **format_pointer, SPECIFICATORS *specificator) {
  char format = (*format_pointer)[0];
  SPECIFICATORS _specificator = 0;
  int status = SUCCEED;

  if (IsSpecificator(format)) {
    if (format == 'c') {
      _specificator = C;
    } else if (format == 'f') {
      _specificator = F;
    } else if (format == 's') {
      _specificator = S;
    } else if (format == '%') {
      _specificator = PERCENT;
    } else if (format == 'i') {
      _specificator = I;
    } else if (format == 'u') {
      _specificator = U;
    } else if (format == 'd') {
      _specificator = D;
    } else {
      status = ERROR;
    }
  } else {
    status = ERROR;
  }
  *specificator = status == SUCCEED ? _specificator : *specificator;
  *format_pointer += 1;
  return status;
}

int IsFlag(char c) { return c == '+' || c == '-' || c == ' '; }

int IsDigit(char c) { return c >= '0' && c <= '9'; }

int IsSpecificator(char c) {
  return c == 'c' || c == 'd' || c == 'i' || c == 'f' || c == 's' || c == 'u' ||
         c == '%';
}

int IntToString(char **string_pointer, long long int number, int flags,
                int width, int precision, int radix) {
  int old_precision = precision;
  precision = precision == -1 ? 0
                              : precision + (number < 0 || flags & PLUS_FLAG ||
                                             flags & SPACE_FLAG);
  int length = GetNumberLength(number, radix) +
               (number < 0 || flags & PLUS_FLAG || flags & SPACE_FLAG);
  width = (length >= width) ? length : width;
  width = (width > precision) ? width : precision;
  char *string = *string_pointer;
  s21_memset(string, ' ', width);
  long long int abs_number = number >= 0 ? number : -number;
  char *end_of_number =
      (flags & MINUS_FLAG)
          ? (length > precision) ? (string + length) : (string + precision)
          : (string + width);
  end_of_number--;
  char *end_of_symbol = (length > precision) ? (end_of_number + 1 - length)
                                             : (end_of_number + 1 - precision);
  char *precision_end = end_of_number;
  for (; precision; precision--, precision_end--) {
    *precision_end = '0';
  }

  if (flags & PLUS_FLAG) {
    *end_of_symbol = number >= 0 ? '+' : '-';
  } else if (flags & SPACE_FLAG) {
    *end_of_symbol = number >= 0 ? ' ' : '-';
  } else if (number < 0) {
    *end_of_symbol = '-';
  }
  if (!abs_number) {
    *end_of_number = '0';
  } else {
    for (; abs_number > 0; abs_number /= radix, end_of_number--) {
      *end_of_number = abs_number % radix + '0';
    }
  }

  width = (number == 0 && precision == 0 && (flags & SPACE_FLAG) == 0 &&
           old_precision == 0)
              ? 0
              : width;
  *string_pointer += width;
  return width;
}

int DoubleToString(char **string_pointer, double number, int flags, int width,
                   int precision) {
  char *string = *string_pointer;
  int temp = 0;
  precision = (precision == -1) ? 6 : precision;
  int i = precision;
  int j = 0;
  long double abs_number = number >= 0 ? number : -number;
  s21_size_t int_length = 1;
  if (abs_number >= 1) {
    int_length = GetNumberLength(abs_number, 10);
  }
  s21_size_t length = int_length + precision +
                      (number < 0 || flags & PLUS_FLAG || flags & SPACE_FLAG) +
                      (precision != 0);
  width -= length;

  abs_number = abs_number * pow(10, precision);
  long double intpart = 0;
  long double fractpart = modfl(abs_number, &intpart);
  if (fractpart != 0.5) {
    abs_number = roundl(abs_number);
  } else if ((int)abs_number % 2 == 0) {
    abs_number = floorl(abs_number);
  } else {
    abs_number = roundl(abs_number);
  }
  i += int_length;

  while (width > 0 && (flags & MINUS_FLAG) == 0) {
    string[j] = ' ';
    j++;
    width--;
  }

  if (flags & PLUS_FLAG) {
    string[j] = number >= 0 ? '+' : '-';
    j++;
  } else if (flags & SPACE_FLAG) {
    string[j] = number >= 0 ? ' ' : '-';
    j++;
  } else if (number < 0) {
    string[j] = '-';
    j++;
  }

  while (i > 0) {
    temp = fmodl(abs_number / (powl(10, i - 1)), 10);
    string[j] = temp + '0';
    i--;
    j++;
    if (i == precision && i != 0) {
      string[j] = '.';
      j++;
    }
  }

  while (width > 0) {
    string[j] = ' ';
    j++;
    width--;
  }
  string[j] = '\0';
  *string_pointer += j;
  return j;
}

int GetNumberLength(long long number, int radix) {
  number = number < 0 ? -number : number;
  return (number >= 1) ? (int)(log(number) / log(radix)) + 1 : 1;
}

int StringToString(char **string_pointer, char *string_input, int flags,
                   int width, int precision) {
  char *string = *string_pointer;
  char null[7] = "(null)";
  string_input = (string_input) ? string_input : null;
  // Length of the formatted string
  int length = s21_strlen(string_input);
  // Shortening the string to the precision
  length = (precision <= length && precision >= 0) ? precision : length;
  // Adding extra spaces if width is greater than length
  width = (length >= width) ? length : width;
  s21_memset(string, ' ', width);
  if (!(flags & MINUS_FLAG)) {  // Left alignment
    string += width - length;
  }
  while (length) {
    *string = *string_input;
    string++;
    string_input++;
    length--;
  }
  *string_pointer += width;
  return width;
}

int CharToString(char **string_pointer, char char_input, int flags, int width) {
  char *string = *string_pointer;
  width = (1 >= width) ? 1 : width;
  s21_memset(string, ' ', width);
  if (!(flags & MINUS_FLAG)) {  // Left alignment
    string += width - 1;
  }
  *string = char_input;
  string++;
  *string_pointer += width;
  return width;
}
