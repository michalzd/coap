/*
 * Copyright (C) 2019 mimi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/* 
 * File:   coap.h
 *         CoAP message structure 
 *         https://tools.ietf.org/html/rfc7252
 * 
 * Author: mimi
 * Created on 21 września 2019, 18:22
 */

#ifndef COAP_H
#define COAP_H

#ifdef __cplusplus
extern "C" {
#endif

#define COAP_DEFAULT_MAX_AGE     60     /* default maximum object lifetime in seconds */
#define COAP_DEFAULT_VERSION      1     /* version of CoAP supported */
#define COAP_DEFAULT_SCHEME  "coap"     /* the default scheme for CoAP URIs */

/* CoAP message types */
#define COAP_MESSAGE_CON       0 /* confirmable message (requires ACK/RST) */
#define COAP_MESSAGE_NON       1 /* non-confirmable message (one-shot message) */
#define COAP_MESSAGE_ACK       2 /* used to acknowledge confirmable messages */
#define COAP_MESSAGE_RST       3 /* indicates error in received messages */

/* CoAP request methods */
#define COAP_REQUEST_GET       1
#define COAP_REQUEST_POST      2
#define COAP_REQUEST_PUT       3
#define COAP_REQUEST_DELETE    4
#define COAP_REQUEST_FETCH     5 /* RFC 8132 */
#define COAP_REQUEST_PATCH     6 /* RFC 8132 */
#define COAP_REQUEST_IPATCH    7 /* RFC 8132 */
    
/* CoAP response code 
 * Structure of a Response Code 
 *  0 1 2 3 4 5 6 7
 * +-----+---------+
 * |class|  detail |
 * +-----+---------+
 */
#define COAP_CODE ( klass, detail )   ((klass << 5) | detail)

/* code classes */
#define COAP_CODE_CLASS_REQUEST               0
#define COAP_CODE_CLASS_RESPONSE              2
#define COAP_CODE_CLASS_CLIENT_ERROR          4
#define COAP_CODE_CLASS_SERVER_ERROR          5

/* code class: response */    
#define COAP_CODE_OK            COAP_CODE(2,00)   
#define COAP_CODE_CREATED       COAP_CODE(2,01)   
#define COAP_CODE_DELETED       COAP_CODE(2,02)   
#define COAP_CODE_VALID         COAP_CODE(2,03)   
#define COAP_CODE_CHANGED       COAP_CODE(2,04)   
#define COAP_CODE_CONTENT       COAP_CODE(2,05)   

/* code class: client errors */
#define COAP_CODE_BAD_REQUEST                 COAP_CODE(4,00)
#define COAP_CODE_UNAUTHORIZED                COAP_CODE(4,01)
#define COAP_CODE_BAD_OPTION                  COAP_CODE(4,02)
#define COAP_CODE_FORBIDDEN                   COAP_CODE(4,03)
#define COAP_CODE_NOT_FOUND                   COAP_CODE(4,04)
#define COAP_CODE_METHOD_NOT_ALLOWED          COAP_CODE(4,05)
#define COAP_CODE_NOT_ACCEPTABLE              COAP_CODE(4,06)
#define COAP_CODE_PRECONDITION_FAILED         COAP_CODE(4,12)
#define COAP_CODE_REQUEST_ENTITY_TOO_LARGE    COAP_CODE(4,13)
#define COAP_CODE_UNSUPPORTED_CONTENT_FORMAT  COAP_CODE(4,15)

/* code class: server errors */
#define COAP_CODE_INTERNAL_SERVER_ERROR       COAP_CODE(5,00)
#define COAP_CODE_NOT_IMPLEMENTED             COAP_CODE(5,01)
#define COAP_CODE_BAD_GATEWAY                 COAP_CODE(5,02)
#define COAP_CODE_SERVICE_UNAVAILABLE         COAP_CODE(5,03)
#define COAP_CODE_GATEWAY_TIMEOUT             COAP_CODE(5,04)
#define COAP_CODE_PROXYING_NOT_SUPPORTED      COAP_CODE(5,05)

/* code class: signals */
#define COAP_SIGNALING_CSM     COAP_CODE(7,01)
#define COAP_SIGNALING_PING    COAP_CODE(7,02)
#define COAP_SIGNALING_PONG    COAP_CODE(7,03)
#define COAP_SIGNALING_RELEASE COAP_CODE(7,04)
#define COAP_SIGNALING_ABORT   COAP_CODE(7,05)
    
/* media type encoding */
#define COAP_MEDIATYPE_TEXT_PLAIN                 0 /* text/plain (UTF-8) */
#define COAP_MEDIATYPE_APPLICATION_LINK_FORMAT   40 /* application/link-format */
#define COAP_MEDIATYPE_APPLICATION_XML           41 /* application/xml */
#define COAP_MEDIATYPE_APPLICATION_OCTET_STREAM  42 /* application/octet-stream */
#define COAP_MEDIATYPE_APPLICATION_RDF_XML       43 /* application/rdf+xml */
#define COAP_MEDIATYPE_APPLICATION_EXI           47 /* application/exi  */
#define COAP_MEDIATYPE_APPLICATION_JSON          50 /* application/json  */
#define COAP_MEDIATYPE_APPLICATION_CBOR          60 /* application/cbor  */

/* Content formats from RFC 8152 */
#define COAP_MEDIATYPE_APPLICATION_COSE_SIGN     98 /* application/cose; cose-type="cose-sign"     */
#define COAP_MEDIATYPE_APPLICATION_COSE_SIGN1    18 /* application/cose; cose-type="cose-sign1"    */    



/* 
 * message format:
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |Ver| T |  TKL  |      Code     |          Message ID           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Token (if any, TKL bytes) ...
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Options (if any) ...
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 1 1 1 1 1 1 1|    Payload (if any) ...
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
 * 
 * 
 */    
struct coap_message_t 
{
  uint8_t   type;              /* message type */
  uint8_t   code;              /* request method (value 1--10) or response code (value 40-255) */
  uint8_t   max_hdr_size;      /* space reserved for protocol-specific header */
  uint8_t   hdr_size;          /* actaul size used for protocol-specific header */
  uint8_t   token_length;      /* length of Token */
  uint16_t  transaction_id;    /* transaction id, if any, in regular host byte order */
  uint16_t  max_delta;         /* highest option number */
  size_t    alloc_size;        /* allocated storage for token, options and payload */
  size_t    used_size;         /* used bytes of storage for token, options and payload */
  size_t    max_size;          /* maximum size for token, options and payload, or zero for variable size pdu */
  uint8_t   *token;            /* first byte of token, if any, or options */
  uint8_t   *data;             /* first byte of payload, if any */
};


    
#ifdef __cplusplus
}
#endif

#endif /* COAP_H */

