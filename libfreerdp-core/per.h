/**
 * FreeRDP: A Remote Desktop Protocol Client
 * ASN.1 Packed Encoding Rules (BER)
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PER_H
#define __PER_H

#include <freerdp/utils/stream.h>

void
per_write_length(STREAM* s, int length);
void
per_write_choice(STREAM* s, uint8 choice);
void
per_write_selection(STREAM* s, uint8 selection);
void
per_write_number_of_sets(STREAM* s, uint8 number);
void
per_write_padding(STREAM* s, int length);
void
per_write_object_identifier(STREAM* s, uint8 oid[6]);
void
per_write_octet_string(STREAM* s, uint8* oct_str, int length, int min);
void
per_write_numeric_string(STREAM* s, uint8* num_str, int length, int min);

#endif /* __PER_H */
