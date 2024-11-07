#include "pch.h"
#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  EUS::LoginForm form;
  Application::Run(% form);

  Application::Exit();

  return 0;
}