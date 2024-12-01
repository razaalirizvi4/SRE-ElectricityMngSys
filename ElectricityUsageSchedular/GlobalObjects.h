#pragma once
#include "week.h"
namespace GlobalObjects
{
    using namespace System::Windows::Forms;
    using namespace System::Collections::Generic;
    public ref class Globals
    {
    public:
        static DataGridView^ Gtable = gcnew DataGridView();
        static List<Week::Tables^>^ monthlyTables = gcnew List<Week::Tables^>();
    };
}
