/*
 *   Copyright (C) 2015,2016,2017,2018 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if !defined(NXDNControl_H)
#define	NXDNControl_H

#include "RSSIInterpolator.h"
#include "NXDNNetwork.h"
#include "NXDNDefines.h"
// #include "YSFPayload.h"
#include "RingBuffer.h"
#include "StopWatch.h"
// #include "YSFFICH.h"
#include "Display.h"
#include "Defines.h"
#include "Timer.h"
#include "Modem.h"

#include <string>

class CNXDNControl {
public:
	CNXDNControl(unsigned int ran, unsigned int id, bool selfOnly, CNXDNNetwork* network, CDisplay* display, unsigned int timeout, bool duplex, bool remoteGateway, CRSSIInterpolator* rssiMapper);
	~CNXDNControl();

	bool writeModem(unsigned char* data, unsigned int len);

	unsigned int readModem(unsigned char* data);

	void clock(unsigned int ms);

private:
	unsigned int               m_ran;
	unsigned int               m_id;
	bool                       m_selfOnly;
	CNXDNNetwork*              m_network;
	CDisplay*                  m_display;
	bool                       m_duplex;
	bool                       m_remoteGateway;
	CRingBuffer<unsigned char> m_queue;
	RPT_RF_STATE               m_rfState;
	RPT_NET_STATE              m_netState;
	CTimer                     m_rfTimeoutTimer;
	CTimer                     m_netTimeoutTimer;
	CTimer                     m_packetTimer;
	CTimer                     m_networkWatchdog;
	CStopWatch                 m_elapsed;
	unsigned int               m_rfFrames;
	unsigned int               m_netFrames;
	unsigned int               m_netLost;
	unsigned int               m_rfErrs;
	unsigned int               m_rfBits;
	unsigned int               m_netErrs;
	unsigned int               m_netBits;
	unsigned char              m_netN;
	CRSSIInterpolator*         m_rssiMapper;
	unsigned char              m_rssi;
	unsigned char              m_maxRSSI;
	unsigned char              m_minRSSI;
	unsigned int               m_aveRSSI;
	unsigned int               m_rssiCount;
	FILE*                      m_fp;

	bool processVWData(bool valid, unsigned char *data);
	bool processDNData(bool valid, unsigned char *data);
	bool processFRData(bool valid, unsigned char *data);

	void writeQueueRF(const unsigned char* data);
	void writeQueueNet(const unsigned char* data);
	void writeNetwork(const unsigned char* data, unsigned int count);
	void writeNetwork();

	void scrambler(unsigned char* data) const;

	void writeEndRF();
	void writeEndNet();

	bool openFile();
	bool writeFile(const unsigned char* data);
	void closeFile();
};

#endif