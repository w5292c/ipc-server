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

#include "ipc-channel.h"

#include "ipc-common.h"
#include "ipc-logging.h"

#include <stdlib.h>
#include <pthread.h>

typedef struct _IpcChannel {
  pthread_t channelTId;
} IpcChannel;

static void *ipc_channel_thread(void *arg);

IpcChannel *ipc_channel_new(void)
{
  IpcChannel *const self = calloc(1, sizeof (IpcChannel));
  return self;
}

void ipc_channel_free(IpcChannel *self)
{
  free(self);
}

void ipc_channel_stop(IpcChannel *self)
{
  IPC_LOG_DEBUG("Request to stop the IPC channel");
}

void ipc_channel_start(IpcChannel *self)
{
  if (self->channelTId) {
    IPC_LOG_ERROR("Already started");
    return;
  }

  IPC_LOG_DEBUG("Starting channel engine...");
  IPC_LOG_DEBUG("Starting channel engine: done.");
}

void *ipc_channel_thread(void *data)
{
  IpcChannel *const self = (IpcChannel *)data;
  IPC_UNUSED(self);

  return NULL;
}
