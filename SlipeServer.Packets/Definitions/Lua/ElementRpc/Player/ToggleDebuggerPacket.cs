﻿using SlipeServer.Packets.Builder;
using SlipeServer.Packets.Enums;
using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace SlipeServer.Packets.Definitions.Lua.ElementRpc.Player
{
    public class ToggleDebuggerPacket : Packet
    {
        public override PacketId PacketId => PacketId.PACKET_ID_LUA;
        public override PacketReliability Reliability => PacketReliability.ReliableSequenced;
        public override PacketPriority Priority => PacketPriority.High;

        public bool Visible { get; set; }


        public ToggleDebuggerPacket(bool visible)
        {
            this.Visible = visible;
        }

        public override void Read(byte[] bytes)
        {
            throw new NotImplementedException();
        }

        public override byte[] Write()
        {
            var builder = new PacketBuilder();
            builder.Write((byte)ElementRpcFunction.TOGGLE_DEBUGGER);
            builder.Write((byte)(Visible ? 1 : 0));
            return builder.Build();
        }
    }
}
