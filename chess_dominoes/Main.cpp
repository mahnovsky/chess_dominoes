#include "CGame.h"
#include "CWindow.h"
#include "CRender.h"

int main()
{
  CApplication* app = CApplication::GetApplication<CGame>();
  CWindow* window = app->GetMainWindow();
  CRender* render = app->GetRender();
  window->SetTitle(L"Chess & Dominoes");

  app->InitWindowClass(L"Chess_Dominoes");

  if( !window->InitWindow() )
    return 1;

  if( !render->InitRender() )
    return 1;

  app->RunApplication();

  return 0;
}
