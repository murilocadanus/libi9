#include "MessageQueue.hpp"
#include <activemq/library/ActiveMQCPP.h>
#include <cms/ConnectionFactory.h>
#include "Configuration.hpp"
#include "EventQueue.hpp"
#include <util/Log.hpp>

#define TAG "[MessageQueue] "

namespace Sascar {

using namespace activemq::library;

MessageQueue MessageQueue::instance;

MessageQueue::MessageQueue()
	: pConn(NULL)
	, pSession(NULL)
	, pDestination(NULL)
	, pConsumer(NULL)
	, sName("")
{
	// Init library
	ActiveMQCPP::initializeLibrary();
}

MessageQueue::~MessageQueue()
{
	// Shutdown library
	ActiveMQCPP::shutdownLibrary();
}

bool MessageQueue::Initialize()
{
	Info(TAG "Initialize");

	string target = pConfiguration->GetActiveMQTarget();
	string user = pConfiguration->GetActiveMQUser();
	string password = pConfiguration->GetActiveMQPassword();
	string queue = pConfiguration->GetActiveMQQueue();

	// Intantiate a connection factory
	ConnectionFactory *connFactory = cms::ConnectionFactory::createCMSConnectionFactory(target);

	try
	{
		// Create a connection
		pConn = connFactory->createConnection();

		// Start queue connection
		pConn->start();

		// Create session from connection
		pSession = pConn->createSession(cms::Session::AUTO_ACKNOWLEDGE);

		// Create destination from session
		pDestination = pSession->createQueue(queue);

		// Create a consumer from queue destination
		pConsumer = pSession->createConsumer(pDestination);

	}
	catch(CMSException &e)
	{
		Error(TAG "Error when trying to connect to message queue: %s", e.getMessage().c_str());
		return false;
	}

	// Release from heap connection factory
	delete connFactory;

	return true;
}

bool MessageQueue::Update(float dt)
{
	// Receive message
	Message *message = pConsumer->receive(pConfiguration->GetActiveMQTimeout());

	// Notify case there is some message at queue
	if(message != NULL)
	{
		// Create a event queue to notify listeners
		EventMessageQueue ev;
		ev.SetName(message->getStringProperty("arquivo"));

		// Notify Listeners
		this->SendEventQueueNotifyChange(&ev);
	}
	return true;
}

bool MessageQueue::Shutdown()
{
	Info(TAG "Shutdown");
	return true;
}

}
