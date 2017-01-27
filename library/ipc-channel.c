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

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define IPC_PORT_NUMBER (1070)
#define IPC_POLLING_TIME_USEC (100000)
#define IPC_CHANNEL_CONNECTIONS_NUMBER (4)

typedef struct _IpcChannel {
  bool aliveFlag;
  pthread_t channelThread;
} IpcChannel;

static void *ipc_channel_thread(void *arg);

IpcChannel *ipc_channel_new(void)
{
  IpcChannel *const self = calloc(1, sizeof (IpcChannel));
  self->aliveFlag = true;

  return self;
}

void ipc_channel_free(IpcChannel *self)
{
  free(self);
}

void ipc_channel_stop(IpcChannel *self)
{
  IPC_LOG_DEBUG("Request to stop the IPC channel");
  self->aliveFlag = false;
  const int res = pthread_join(self->channelThread, NULL);
  if (res) {
    IPC_LOG_ERROR("Failed stopping the IPC thread, code: %d", res);
    return;
  }

  IPC_LOG_DEBUG("Stopped the IPC thread");
}

void ipc_channel_start(IpcChannel *self)
{
  if (self->channelThread) {
    IPC_LOG_ERROR("Already started");
    return;
  }

  IPC_LOG_DEBUG("Starting channel engine...");
  const int res = pthread_create(&self->channelThread, NULL, ipc_channel_thread, self);
  if (res) {
    self->aliveFlag = false;
    IPC_LOG_ERROR("Failed creating the IPC thread, code: %d", res);
    return;
  }

  IPC_LOG_DEBUG("Starting channel engine: done.");
}

void *ipc_channel_thread(void *data)
{
  IpcChannel *const self = (IpcChannel *)data;
  IPC_UNUSED(self);

  const int sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  if (-1 == sockfd) {
    self->aliveFlag = false;
    IPC_LOG_ERROR("Failed creating socket for IPC, code: %d", errno);
    return NULL;
  }

  struct sockaddr_in address;
  memset(&address, 0, sizeof (address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(IPC_PORT_NUMBER);

  int res = bind(sockfd, (const struct sockaddr *)&address, sizeof (address));
  if (res) {
    IPC_LOG_ERROR("Failed binding the IPC channel, code: %d", errno);
    self->aliveFlag = false;
    close(sockfd);
    return NULL;
  }

  res = listen(sockfd, IPC_CHANNEL_CONNECTIONS_NUMBER);
  if (res) {
    IPC_LOG_ERROR("Failed starting listening, code: %d", errno);
    self->aliveFlag = false;
    close(sockfd);
    return NULL;
  }

  while (self->aliveFlag) {
    const int clientSocket = accept4(sockfd, NULL, NULL, 0);
    if (-1 == clientSocket) {
      if (EAGAIN != errno) {
        IPC_LOG_ERROR("Failed accepting new connection, code: %d", errno);
        break;
      }
    } else {
      IPC_LOG_DEBUG("Got new connection, %d", clientSocket);
      /** @todo Implement handling the new connection */
      close(clientSocket);
    }
    usleep(IPC_POLLING_TIME_USEC);
  }

  /* Cleanup */
  self->aliveFlag = false;
  close(sockfd);
  return NULL;
}
