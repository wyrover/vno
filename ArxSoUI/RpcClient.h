#pragma once

#include <boost/shared_ptr.hpp>
#include <thrift/Thrift.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

#include <thrift/gen-cpp/CbmService.h>

typedef boost::shared_ptr<TTransport> TransportPtr;
typedef boost::shared_ptr<TProtocol> ProtocolPtr;
typedef boost::shared_ptr<cbm::CbmServiceClient> ServiceClientPtr;

#define HOST "localhost"
#define PORT1 9100
#define PORT2 9090

template<class Service>
class RpcClient
{
public:
	RpcClient(const std::string& host=HOST, int port=PORT1)
	{
		this->host = host;
		this->port = port;
	}

	void start()
	{
		TransportPtr socket(new TSocket(host, port));
		TransportPtr transport(new TBufferedTransport(socket));
		ProtocolPtr protocol(new TBinaryProtocol(transport));
		boost::shared_ptr<Service> client(new Service(protocol));

		this->transport = transport;
		this->protocol = protocol;
		this->client = client;
		this->transport->open();
	}

	boost::shared_ptr<Service> get()
	{
		return this->client;
	}

	void close()
	{
		if(this->transport != 0)
		{
			this->transport->close();
		}
	}

private:
	TransportPtr transport;
	ProtocolPtr protocol;
	boost::shared_ptr<Service> client;
	std::string host;
	int port;
};
