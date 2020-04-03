/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 University of Campinas (Unicamp)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: xie yingying <xyynku@163.com>
 */

#include "ns3/log.h"
#include "wifi-elements.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("WifiElements");


// definition of class wifiAp

WifiAp::WifiAp (const Address& address):
	m_address(address)
{
	NS_LOG_FUNCTION (this);
}

void
WifiAp::SetChannelInfo (const uint8_t& channel, const uint16_t& frequency,
						const uint16_t& channelWidth,
						const WifiPhyStandard& standard)
{
	NS_LOG_FUNCTION (this << standard << channel << frequency << channelWidth);
	m_standard = standard;
	m_channelNumber = channel;
	m_frequency = frequency;
	m_channelWidth = channelWidth;
	
}

void
WifiAp::SetMac48Address (const uint8_t buffer[6])
{
	NS_LOG_FUNCTION (this);
	m_mac48address.CopyFrom (buffer);
}

Mac48Address
WifiAp::GetMac48Address (void)
{
	NS_LOG_FUNCTION (this);
	return m_mac48address;
}

// definition of class wifiNetWorkStatus

WifiNetworkStatus::WifiNetworkStatus()
{
	NS_LOG_FUNCTION (this);
	InitializeFrequencyUnused();
}

void
WifiNetworkStatus::AddApMac48address (const Mac48Address& mac48address)
{
	NS_LOG_FUNCTION (this);
	m_apsMac48address.insert (mac48address);
}

void
WifiNetworkStatus::InitializeFrequencyUnused ()
{
	NS_LOG_FUNCTION (this);
	for (auto it : WifiPhy::GetChannelToFrequencyWidthMap())
	{
		if (it.first.second == WIFI_PHY_STANDARD_UNSPECIFIED)
		{
			m_frequencyUnused.insert (it.second);
		}
	}
	NS_LOG_INFO("m_frequencyUnused.size():" << m_frequencyUnused.size());
}
void
WifiNetworkStatus::UpdateFrequencyUsed (Address address, 
										uint16_t frequency, uint16_t width)
{
	NS_LOG_FUNCTION (this << address << frequency << width);
	FrequencyWidthPair pair(frequency, width);
	if (m_frequencyUsed.find (pair) != m_frequencyUsed.end())
	{
		NS_LOG_INFO("find in m_frequencyUsed");
		m_frequencyUsed[pair].insert(address);
	}
	else
	{
		std::set<Address> addr;
		addr.insert(address);
		m_frequencyUsed.insert(std::make_pair(pair,addr));
		//m_frequencyUsed[pair] = addr;
		m_frequencyUnused.erase (pair);
	}
	
}



} //namespace ns3
