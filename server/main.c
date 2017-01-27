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
#include "ipc-logging.h"
#include "ipc-library-api.h"

#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

static bool TheContinueFlag = false;

static void sighandler(int signum);

int main(int argc, char **argv)
{
  /* Initialization */
  TheContinueFlag = true;
  signal(SIGINT, sighandler);
  ipc_library_init();
  IpcChannel *const ipcChannel = ipc_channel_new();
  ipc_channel_start(ipcChannel);

  while (TheContinueFlag) {
    sleep(1);
  }

  /* Deinitialization */
  ipc_channel_stop(ipcChannel);

  /* Cleanup */
  ipc_channel_free(ipcChannel);

  IPC_LOG_DEBUG("Finished.");
  return 0;
}

void sighandler(int signum)
{
  IPC_LOG_DEBUG("Terminating");
  TheContinueFlag = false;
}
