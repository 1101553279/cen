/*
 * Copyright (c) 2008, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Debugging command for testing reliable unicast (runicast)
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "contiki-conf.h"
#include "shell-rime-debug.h"

#include "dev/leds.h"

#include "lib/random.h"

#include "net/rime/rime.h"
#include "net/rime/route.h"
#include "net/rime/trickle.h"

#include "net/rime/timesynch.h"

#include <stdio.h>
#ifndef HAVE_SNPRINTF
int snprintf(char *str, size_t size, const char *format, ...);
#endif /* HAVE_SNPRINTF */
#include <string.h>

#define COLLECT_MSG_HDRSIZE 2
struct collect_msg {
  uint16_t timestamp;
  uint8_t data[1];
};

static struct runicast_conn ruc;
/*---------------------------------------------------------------------------*/
PROCESS(shell_runicast_process, "runicast");
SHELL_COMMAND(runicast_command,
	      "runicast",
	      "runicast <node addr>: reliably unicast data to specific neighbor",
	      &shell_runicast_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(shell_runicast_process, ev, data)
{
  struct shell_input *input;
  static linkaddr_t receiver;
  int len;
  const char *nextptr;
  struct collect_msg *msg;
  char buf[30];
  
  PROCESS_BEGIN();
  
  receiver.u8[0] = shell_strtolong(data, &nextptr);
  if(nextptr == data || *nextptr != '.') {
    shell_output_str(&runicast_command,
		     "runicast <receiver>: recevier must be specified", "");
    PROCESS_EXIT();
  }
  ++nextptr;
  receiver.u8[1] = shell_strtolong(nextptr, &nextptr);

  snprintf(buf, sizeof(buf), "%d.%d", receiver.u8[0], receiver.u8[1]);
  shell_output_str(&runicast_command, "Sending runicast packets to ", buf);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == shell_event_input);
    input = data;

    len = input->len1 + input->len2;

    if(len == 0) {
      PROCESS_EXIT();
    }
    
    if(len < PACKETBUF_SIZE) {
      packetbuf_clear();
      packetbuf_set_datalen(len + COLLECT_MSG_HDRSIZE);
      msg = packetbuf_dataptr();
      memcpy(msg->data, input->data1, input->len1);
      memcpy(msg->data + input->len1, input->data2, input->len2);
#if TIMESYNCH_CONF_ENABLED
      msg->timestamp = timesynch_time();
#else
      msg->timestamp = 0;
#endif
      /*      printf("Sending %d bytes\n", len);*/
      runicast_send(&ruc, &receiver, 4);
    }
  }
  PROCESS_END();
}
static void
recv_ruc(struct runicast_conn *c, const linkaddr_t *from, uint8_t seqno)
{
  struct collect_msg *msg;
  rtimer_clock_t latency;
#if TIMESYNCH_CONF_ENABLED
  rtimer_clock_t timestamp;
#endif /* TIMESYNCH_CONF_ENABLED */
  
  msg = packetbuf_dataptr();

#if TIMESYNCH_CONF_ENABLED
  memcpy(&timestamp, &msg->timestamp, sizeof(timestamp));
  latency = timesynch_time() - timestamp;
#else
  latency = 0;
#endif

  printf("runicast message received from %d.%d, latency %lu ms, seqno %d, data '%.*s'\n",
	 from->u8[0], from->u8[1],
	 (1000L * latency) / RTIMER_ARCH_SECOND,
         seqno,
	 packetbuf_datalen() - COLLECT_MSG_HDRSIZE,
	 msg->data);
}
static void
sent_ruc(struct runicast_conn *c, const linkaddr_t *to, uint8_t tx)
{
  printf("runicast message sent to %d.%d, %d transmissions\n",
	 to->u8[0], to->u8[1],
	 tx);
}
static void
timedout_ruc(struct runicast_conn *c, const linkaddr_t *to, uint8_t tx)
{
  printf("runicast message to %d.%d timed out after %d transmissions\n",
	 to->u8[0], to->u8[1],
	 tx);
}
static const struct runicast_callbacks runicast_callbacks = {recv_ruc,
                                                             sent_ruc,
                                                             timedout_ruc};
/*---------------------------------------------------------------------------*/
void
shell_rime_debug_runicast_init(void)
{
  runicast_open(&ruc, SHELL_RIME_CHANNEL_RUNICAST,
	       &runicast_callbacks);
  shell_register_command(&runicast_command);
}
/*---------------------------------------------------------------------------*/
