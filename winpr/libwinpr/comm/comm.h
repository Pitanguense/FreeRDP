/**
 * WinPR: Windows Portable Runtime
 * Serial Communication API
 *
 * Copyright 2014 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 * Copyright 2014 Hewlett-Packard Development Company, L.P. 
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

#ifndef WINPR_COMM_PRIVATE_H
#define WINPR_COMM_PRIVATE_H

#ifndef _WIN32

#include <linux/serial.h>
#include <sys/eventfd.h>

#include <winpr/comm.h>

#include "../handle/handle.h"

/**
 * IOCTLs table according the remote serial driver:
 * http://msdn.microsoft.com/en-us/library/windows/hardware/dn265347%28v=vs.85%29.aspx
 */
typedef enum _REMOTE_SERIAL_DRIVER_ID
{
	RemoteSerialDriverUnknown = 0,
	RemoteSerialDriverSerialSys,
	RemoteSerialDriverSerCxSys,
	RemoteSerialDriverSerCx2Sys /* default fallback, see also CommDeviceIoControl() */
} REMOTE_SERIAL_DRIVER_ID;

struct winpr_comm
{
	WINPR_HANDLE_DEF();

	int fd;

	int fd_read;
	int fd_read_event; /* as of today, only used by _purge() */
	
	int fd_write;
	int fd_write_event; /* as of today, only used by _purge() */

	/* permissive mode on errors if TRUE (default is FALSE). 
	 *
	 * Since not all features are supported, some devices and applications
	 * can still be functional on such errors.
	 *
	 * TODO: command line switch or getting rid of it.
	 */
	BOOL permissive;

	// TMP: to be renamed serverSerialDriverId
	REMOTE_SERIAL_DRIVER_ID remoteSerialDriverId;

	COMMTIMEOUTS timeouts;
	
	CRITICAL_SECTION EventsLock; /* protects counters, WaitEventMask and PendingEvents */
	struct serial_icounter_struct counters;
	ULONG WaitEventMask;
	ULONG PendingEvents;

	/* NB: CloseHandle() has to free resources */
};

typedef struct winpr_comm WINPR_COMM;

void _comm_setRemoteSerialDriver(HANDLE hComm, REMOTE_SERIAL_DRIVER_ID);

/* TMP: TODO: move all specific defines and types here? at least SERIAL_EV_* */
#define SERIAL_EV_FREERDP_WAITING	0x4000 /* bit unused by SERIAL_EV_* */
#define SERIAL_EV_FREERDP_STOP     	0x8000 /* bit unused by SERIAL_EV_* */

#define FREERDP_PURGE_TXABORT		0x00000001 /* abort pending transmission */
#define FREERDP_PURGE_RXABORT		0x00000002 /* abort pending reception */

#endif /* _WIN32 */

#endif /* WINPR_COMM_PRIVATE_H */
