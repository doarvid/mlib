/*
 * Copyright (c) 2017-2019, Patrick Pelissier
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * + Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * + Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef MSTARLIB_SERIAL_JSON_H
#define MSTARLIB_SERIAL_JSON_H

#include "m-core.h"
#include "m-string.h"

static inline m_serial_return_code_t
m_serial_json_write_boolean(m_serial_write_t serial, const bool data)
{
  FILE *f = (FILE *)serial->data[0];
  int n = fprintf(f, "%s", data ? "true" : "false");
  return n > 0 ? M_SERIAL_OK_DONE : M_SERIAL_FAIL;
}

static inline m_serial_return_code_t
m_serial_json_write_integer(m_serial_write_t serial,const long long data, const size_t size_of_type)
{
  (void) size_of_type; // Ignored
  FILE *f = (FILE *)serial->data[0];
  int n = fprintf(f, "%lld", data);
  return n > 0 ? M_SERIAL_OK_DONE : M_SERIAL_FAIL;  
}

static inline m_serial_return_code_t
m_serial_json_write_float(m_serial_write_t serial, const long double data, const size_t size_of_type)
{
  (void) size_of_type; // Ignored
  FILE *f = (FILE *)serial->data[0];
  int n = fprintf(f, "%Lf", data);
  return n > 0 ? M_SERIAL_OK_DONE : M_SERIAL_FAIL;
}

static inline m_serial_return_code_t
m_serial_json_write_string(m_serial_write_t serial, const char data[])
{
  FILE *f = (FILE *)serial->data[0];
  int n = fprintf(f, "\"%s\"", data); // TODO: escape some characters
  return n > 0 ? M_SERIAL_OK_DONE : M_SERIAL_FAIL;
}

static inline m_serial_return_code_t
m_serial_json_write_array_start(m_serial_write_t serial, const size_t number_of_elements)
{
  return M_SERIAL_FAIL;
}

static inline  m_serial_return_code_t m_serial_json_write_array_next(m_serial_write_t serial){   return M_SERIAL_FAIL; }
static inline   m_serial_return_code_t m_serial_json_write_array_end(m_serial_write_t serial){   return M_SERIAL_FAIL; }
static inline   m_serial_return_code_t m_serial_json_write_map_start(m_serial_write_t serial, const size_t number_of_elements){   return M_SERIAL_FAIL; }
static inline   m_serial_return_code_t m_serial_json_write_map_value(m_serial_write_t serial){   return M_SERIAL_FAIL; }
static inline   m_serial_return_code_t m_serial_json_write_map_next(m_serial_write_t serial){   return M_SERIAL_FAIL; }
static inline   m_serial_return_code_t m_serial_json_write_map_end(m_serial_write_t serial){   return M_SERIAL_FAIL; }

static inline   m_serial_return_code_t m_serial_json_write_tuple_start(m_serial_write_t serial){
  FILE *f = (FILE *)serial->data[0];
  int n = fprintf(f, "{");
  return n > 0 ? M_SERIAL_OK_CONTINUE : M_SERIAL_FAIL;
}

static inline   m_serial_return_code_t m_serial_json_write_tuple_id(m_serial_write_t serial, const char *const field_name[], const int max, const int index){
  FILE *f = (FILE *)serial->data[0];
  int n = fprintf(f, "%c\"%s\":", index == 0 ? ' ' : ',', field_name[index]);
  return n > 0 ? M_SERIAL_OK_CONTINUE : M_SERIAL_FAIL;
}

static inline   m_serial_return_code_t m_serial_json_write_tuple_end(m_serial_write_t serial){
  FILE *f = (FILE *)serial->data[0];
  int n = fprintf(f, "}");
  return n > 0 ? M_SERIAL_OK_CONTINUE : M_SERIAL_FAIL;
}

static inline   m_serial_return_code_t m_serial_json_write_variant_start(m_serial_write_t serial, const char *const field_name[], const int max, const int index){   return M_SERIAL_FAIL; }
static inline   m_serial_return_code_t m_serial_json_write_variant_end(m_serial_write_t serial){   return M_SERIAL_FAIL; }

static const m_serial_write_interface_t m_serial_write_json_interface = {
  m_serial_json_write_boolean,
  m_serial_json_write_integer,
  m_serial_json_write_float,
  m_serial_json_write_string, 
  m_serial_json_write_array_start,
  m_serial_json_write_array_next,
  m_serial_json_write_array_end,
  m_serial_json_write_map_start,
  m_serial_json_write_map_value,
  m_serial_json_write_map_next,
  m_serial_json_write_map_end,
  m_serial_json_write_tuple_start,
  m_serial_json_write_tuple_id,
  m_serial_json_write_tuple_end,
  m_serial_json_write_variant_start,
  m_serial_json_write_variant_end
};

static inline void m_serial_write_json_init(m_serial_write_t serial, FILE *f)
{
  serial->interface = &m_serial_write_json_interface;
  serial->data[0] = (void*) f;
}

static inline void m_serial_write_json_clear(m_serial_write_t serial)
{
  (void) serial; // Nothing to do
}

#endif
