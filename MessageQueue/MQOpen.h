
#ifndef MessageQueue_MQOpen_h
#define MessageQueue_MQOpen_h


// Library includes

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace MQ {


class MQOpenByID : public Extensions::ExtensionMethod
{
public:
	MQOpenByID()
	: ExtensionMethod(nullptr, "msgget", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("id", Designtime::Int32Type::TYPENAME));
		//params.push_back(Parameter::CreateDesigntime("mode", Designtime::Int32Type::TYPENAME, 666, true));
		params.push_back(Parameter::CreateDesigntime("create", Designtime::BoolType::TYPENAME, false, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_id     = (*it++).value().toInt();
			//auto param_mode   = (*it++).value().toInt();
			auto param_create = (*it++).value().toBool();

			auto queue_handle = mMQs.size();
			auto& queue       = mMQs[queue_handle] = -1;
			key_t key         = param_id;

			queue = msgget(key, 0666 | (param_create ? IPC_CREAT : 0));

			if ( queue == -1 ) {
				queue_handle = 0;
			}

			*result = Runtime::Int32Type( static_cast<int>(queue_handle) );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};

class MQOpenByName : public Extensions::ExtensionMethod
{
public:
	MQOpenByName()
	: ExtensionMethod(nullptr, "msgget", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("name", Designtime::StringType::TYPENAME));
		//params.push_back(Parameter::CreateDesigntime("mode", Designtime::Int32Type::TYPENAME, 666, true));
		params.push_back(Parameter::CreateDesigntime("create", Designtime::BoolType::TYPENAME, false, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_name   = (*it++).value().toStdString();
			//auto param_mode   = (*it++).value().toInt();
			auto param_create = (*it++).value().toBool();

			auto queue_handle = mMQs.size();
			auto& queue       = mMQs[queue_handle] = -1;
			key_t key;

			if ( (key = ftok(param_name.c_str(), 'B')) != -1 ) {
				queue = msgget(key, 0666 | (param_create ? IPC_CREAT : 0));
			}

			if ( queue == -1 ) {
				queue_handle = 0;
			}

			*result = Runtime::Int32Type( static_cast<int>(queue_handle) );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
