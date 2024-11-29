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
        static DataGridView^ Gtable2 = gcnew DataGridView();
        static DataGridView^ Gtable3 = gcnew DataGridView();
        static DataGridView^ Gtable4 = gcnew DataGridView();
        static DataGridView^ Gtable5 = gcnew DataGridView();
        static DataGridView^ Gtable6 = gcnew DataGridView();
        static DataGridView^ Gtable7 = gcnew DataGridView();
        static DataGridView^ GTable8 = gcnew DataGridView();
        static List<Week::Tables^>^ monthlyTables = gcnew List<Week::Tables^>();
    };
}
