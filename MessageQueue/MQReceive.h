
#ifndef MessageQueue_MQReceive_h
#define MessageQueue_MQReceive_h


// Library includes

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace MQ {


class MQReceive : public Extensions::ExtensionMethod
{
public:
	MQReceive()
	: ExtensionMethod(nullptr, "msgrcv", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("wait", Designtime::BoolType::TYPENAME, false, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();
		auto param_wait   = (*it++).value().toBool();

		std::string method_result;
		if ( param_handle > 0 && param_handle < (int)mMQs.size() ) {
			auto& queue = mMQs[param_handle];

			struct Message_t message;

			auto msgflg = (param_wait ? 0 : IPC_NOWAIT);
			if ( msgrcv(queue, &message, sizeof message.mText, 0, msgflg) != -1 ) {
				method_result = std::string(message.mText );
			}
		}

		*result = Runtime::StringType( method_result );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
