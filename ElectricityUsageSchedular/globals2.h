#pragma once
#include "unmanaged.h"
namespace GlobalObjectsRaza
{
    using namespace System::Windows::Forms;
    public ref class Globals
    {
    public:
        static UnmanagedGlobals* unmanagedGlobals = new UnmanagedGlobals();
    };
}

