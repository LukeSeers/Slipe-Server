#include <iostream>
#include "mta/shared/sdk/SharedUtil.h";
#include "mta/server/core/CDynamicLibrary.h";
#include "mta/server/sdk/core/CServerInterface.h";
#include "mta/shared/sdk/SharedUtil.h";
#include "mta/shared/sdk/net/Packets.h";
#include "mta/shared/sdk/net/bitstream.h";
#include "mta/server/sdk/net/CNetServer.h";
#include <bitset>
#include <map>
#include <iomanip>

typedef void(__stdcall* PacketCallback)(unsigned char, unsigned long, char[], unsigned long, bool, unsigned int);

class NetWrapper
{
private:
    uint16_t id;
    static uint16_t nextId;
    static std::map<uint16_t, NetWrapper*> netWrappers;
    static std::map<NetServerPlayerID, NetWrapper*> netWrappersPerSocket;

	CNetServer* network;
	std::map<ulong, NetServerPlayerID> sockets;
	bool running;
	PacketCallback registeredCallback;
	std::thread runThread;

    void runPulseLoop();
    void testMethod();
public:
    NetWrapper();
    uint16_t getId();

    void destroy();

    bool packetHandler(unsigned char ucPacketID, const NetServerPlayerID& Socket, NetBitStreamInterface* pBitStream, SNetExtraInfo* pNetExtraInfo);
    void sendPacket(unsigned long address, unsigned char packetId, unsigned char* payload, unsigned long payloadSize, unsigned char priority, unsigned char reliability);
    void setSocketVersion(unsigned long address, unsigned short version);
    BSTR getClientSerialAndVersion(unsigned long address, uint16_t& serialSize, uint16_t& extraSize, uint16_t& versionSize);
    int init(const char* netDllFilePath, const char* idFile, const char* ip, unsigned short port, unsigned int playerCount, const char* serverName, PacketCallback callback);
    void start();
    void stop();
    bool isValidSocket(NetServerPlayerID id);

    static NetWrapper* getNetWrapper(int id);
    static NetWrapper* getNetWrapper(NetServerPlayerID id);
};

