/*
 * Copyright (c) 2009-2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>

#include "client.h"
#include "server.h"

/*
 * simple client/server linux console app 
 * do testowania komunikacji via COAP 
 * Constrained Application Protocol
 * 
 * uruchomienie klienta   coapss -c [ server_addr:serverport | server_addr ]
 * uruchomienie servera   coapss -s [ server_addr:serverport | server_addr ]
 * default serverport 1818                                
 */
uint16_t  sport;

int mode_client(char  *srvparam)
{
    const char *dsvr = "localhost";
    if(srvparam==NULL) srvparam = dsvr;
    else 
    {
        // parse argument, addres:port 
        // or only         addres
        char *p = strchr(srvparam, ':');
        if(p)
        {
            *p = 0; 
            sport = atoi(++p);
        }
    }
    if(sport) coap_client(srvparam, sport);
    
    return 0;
}

int mode_server(char   *srvparam)
{
    if(srvparam!=NULL) sport = atoi(srvparam);
    if(sport) coap_server(sport);
    return 0;
}


int main(int argc, char**argv) {
    int     opt;
    char    mode;
    char    *saddr;

    if(argc<=1) 
    {
        printf("COAP client: coapss -c [ server_addr:serverport | server_addr ]\n");
        printf("COAP server: coapss -s [ serverport ]\n");
        printf("             default serverport: 1818\n");
        return 0;
    }
    
    /* default port 1818 */
    sport = 1818;
    mode = 's';
    while ((opt = getopt(argc, argv, "s::c::")) != -1) 
    {
        switch (opt) {
            case 's': saddr = optarg; 
                      break;
            case 'c': mode = 'c'; 
                      saddr = optarg; 
                      break; 
        }
    }

    opt = 0;
    if(mode=='c')  opt =  mode_client( saddr );
    else opt = mode_server( saddr );
    
    return opt;
}
