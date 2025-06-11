
#ifndef MessageQueue_MQClose_h
#define MessageQueue_MQClose_h


// Library includes

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace MQ {


class MQClose : public Extensions::ExtensionMethod
{
public:
	MQClose()
	: ExtensionMethod(nullptr, "msgctl", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();

		int method_result = 0;
		if ( param_handle > 0 && param_handle < (int)mMQs.size() ) {
			auto& queue = mMQs[param_handle];

			method_result = msgctl(queue, IPC_RMID, NULL);
		}

		*result = Runtime::Int32Type( method_result );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
