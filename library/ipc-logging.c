/*
 * MIT License
 *
 * Copyright (c) 2017 Alexander Chumakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "ipc-logging.h"

#include <time.h>
#include <stdarg.h>

void ipc_log_out(int level, int line, const char *func, const char *format, ...)
{
  char levelMarker;
  FILE *stream = stderr;

  switch (level) {
  case IPC_LOG_LEVEL_DEBUG:
    stream = stdout;
    levelMarker = 'D';
    break;
  case IPC_LOG_LEVEL_INFO:
    stream = stdout;
    levelMarker = 'I';
    break;
  case IPC_LOG_LEVEL_WARNING:
    levelMarker = 'W';
    break;
  case IPC_LOG_LEVEL_ERROR:
    levelMarker = 'E';
    break;
  case IPC_LOG_LEVEL_FATAL:
    levelMarker = 'F';
    break;
  default:
    levelMarker = 'U';
    break;
  }

  time_t logTime = 0;
  time(&logTime);

  struct tm logTimeStruct;
  gmtime_r(&logTime, &logTimeStruct);
  fprintf(stream, "[%2.2d:%2.2d:%2.2d]",
    logTimeStruct.tm_hour, logTimeStruct.tm_min, logTimeStruct.tm_sec);

  fprintf(stream, "[%c]", levelMarker);

  fprintf(stream, "[%s:%d] ", func, line);

  va_list arg;
  va_start(arg, format);
  vfprintf(stream, format, arg);

  fprintf(stream, "\n");
}
