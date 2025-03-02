
#ifndef MessageQueue_Extension_h
#define MessageQueue_Extension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace MQ {


class Extension : public Extensions::AExtension
{
public:
    Extension();
    ~Extension() = default;

public:
    void initialize( Extensions::ExtensionNamespace* scope );
    void provideMethods( Extensions::ExtensionMethods& methods );
};


}


#endif
