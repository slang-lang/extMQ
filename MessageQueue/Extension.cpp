
// Header
#include "Extension.h"

// Library includes

// Project includes
#include "MQClose.h"
#include "MQOpen.h"
#include "MQReceive.h"
#include "MQSend.h"

// Namespace declarations


namespace MQ {


Extension::Extension()
: AExtension( "extMQ", "0.2.0" )
{
	// initialize pipes
	mMQs[0] = 0;
}

void Extension::initialize( Extensions::ExtensionNamespace* scope )
{
	//std::cout << "Extension::initialize()" << std::endl;

	(void)scope;

	// global vars/consts currently don't work for extensions :-(
}

void Extension::provideMethods( Extensions::ExtensionMethods& methods )
{
	methods.push_back( new MQClose() );
	methods.push_back( new MQOpenByID() );
	methods.push_back( new MQOpenByName() );
	methods.push_back( new MQReceive() );
	methods.push_back( new MQSend() );
}


}


extern "C" Extensions::AExtension* factory( void ) {
	return dynamic_cast<Extensions::AExtension*>( new MQ::Extension() );
}
