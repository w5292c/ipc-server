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
#ifndef W5292C_IPC_LOGGING_H
#define W5292C_IPC_LOGGING_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
  IPC_LOG_LEVEL_DEBUG   = 0,
  IPC_LOG_LEVEL_INFO    = 1,
  IPC_LOG_LEVEL_WARNING = 2,
  IPC_LOG_LEVEL_ERROR   = 3,
  IPC_LOG_LEVEL_FATAL   = 4,
} IPC_LOG_LEVEL;

#define IPC_LOG_DEBUG(format, ...)   ipc_log_out(IPC_LOG_LEVEL_DEBUG, \
                                       __LINE__, __func__, format, ##__VA_ARGS__)
#define IPC_LOG_INFO(format, ...)    ipc_log_out(IPC_LOG_LEVEL_INFO, \
                                       __LINE__, __func__, format, ##__VA_ARGS__)
#define IPC_LOG_WARNING(format, ...) ipc_log_out(IPC_LOG_LEVEL_WARNING, \
                                       __LINE__, __func__, format, ##__VA_ARGS__)
#define IPC_LOG_ERROR(format, ...)   ipc_log_out(IPC_LOG_LEVEL_ERROR, \
                                       __LINE__, __func__, format, ##__VA_ARGS__)
#define IPC_LOG_FATAL(format, ...)   ipc_log_out(IPC_LOG_LEVEL_FATAL, \
                                       __LINE__, __func__, format, ##__VA_ARGS__)

void ipc_log_out(int level, int line, const char *func, const char *format, ...);

#ifdef __cplusplus
} /* extern "C" { */
#endif /* __cplusplus */

#endif /* W5292C_IPC_LOGGING_H */
