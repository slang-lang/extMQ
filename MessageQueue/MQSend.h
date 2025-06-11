
#ifndef MessageQueue_MQSend_h
#define MessageQueue_MQSend_h


// Library includes

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace MQ {


class MQSend : public Extensions::ExtensionMethod
{
public:
	MQSend()
	: ExtensionMethod(nullptr, "msgsnd", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("message", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle  = (*it++).value().toInt();
		auto param_message = (*it++).value().toStdString();

		int method_result = 0;
		if ( param_handle > 0 && param_handle < (int)mMQs.size() ) {
			auto& queue = mMQs[param_handle];

			struct Message_t message;
			message.mType = 1;

			if ( param_message.size() >= 512 ) {
				param_message.resize(512);
			}

			snprintf(message.mText, param_message.size(), "%s", param_message.c_str());
			message.mText[param_message.size()] = '\0';

			method_result = msgsnd(queue, &message, param_message.size() + 1, 0);
		}

		*result = Runtime::Int32Type( method_result );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
