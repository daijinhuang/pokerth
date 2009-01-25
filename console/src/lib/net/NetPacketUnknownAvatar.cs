﻿/***************************************************************************
 *   Copyright (C) 2009 by Lothar May                                      *
 *                                                                         *
 *   This file is part of pokerth_console.                                 *
 *   pokerth_console is free software: you can redistribute it and/or      *
 *   modify it under the terms of the GNU Affero General Public License    *
 *   as published by the Free Software Foundation, either version 3 of     *
 *   the License, or (at your option) any later version.                   *
 *                                                                         *
 *   pokerth_console is distributed in the hope that it will be useful,    *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the                                *
 *   GNU Affero General Public License along with pokerth_console.         *
 *   If not, see <http://www.gnu.org/licenses/>.                           *
 ***************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.IO;


namespace pokerth_lib
{
	class NetPacketUnknownAvatar : NetPacket
	{
		public NetPacketUnknownAvatar()
			: base(NetPacket.NetTypeUnknownAvatar)
		{
		}

		public NetPacketUnknownAvatar(int size, BinaryReader r)
			: base(NetPacket.NetTypeUnknownAvatar)
		{
			if (size != 8)
				throw new NetPacketException("NetPacketUnknownAvatar invalid size.");
			Properties.Add(PropType.RequestId,
				Convert.ToString(IPAddress.NetworkToHostOrder((int)r.ReadUInt32())));
		}

		public override void Accept(INetPacketVisitor visitor)
		{
			visitor.VisitUnknownAvatar(this);
		}

		public override byte[] ToByteArray()
		{
			throw new NotImplementedException();
		}
	}
}