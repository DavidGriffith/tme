/* $Id: tape.c,v 1.1 2003/08/05 03:27:12 fredette Exp $ */

/* generic/tape.c - generic tape implementation support: */

/*
 * Copyright (c) 2003 Matt Fredette
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Matt Fredette.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <tme/common.h>
_TME_RCSID("$Id: tape.c,v 1.1 2003/08/05 03:27:12 fredette Exp $");

/* includes: */
#include <tme/generic/tape.h>

/* this scores a tape connection: */
int
tme_tape_connection_score(struct tme_connection *conn,
			  unsigned int *_score)
{
  struct tme_tape_connection *conn_tape;
  struct tme_tape_connection *conn_tape_other;

  /* both sides must be tape connections: */
  assert(conn->tme_connection_type == TME_CONNECTION_TAPE);
  assert(conn->tme_connection_other->tme_connection_type == TME_CONNECTION_TAPE);

  /* you cannot connect a tape to a tape, or a tape frontend to a tape
     frontend: */
  conn_tape = (struct tme_tape_connection *) conn;
  conn_tape_other = (struct tme_tape_connection *) conn->tme_connection_other;
  *_score
    = ((conn_tape->tme_tape_connection_read != NULL
	|| conn_tape->tme_tape_connection_write != NULL)
       != (conn_tape_other->tme_tape_connection_read != NULL
	   || conn_tape_other->tme_tape_connection_write != NULL));
  return (TME_OK);
}
