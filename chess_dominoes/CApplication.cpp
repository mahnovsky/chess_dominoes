#include "CApplication.h"
#include "CWindow.h"
#include "CRender.h"
#include <assert.h>
#include <iostream>

CApplication* CApplication::_Self;

CApplication::CApplication() :
  _Msg(),
  _WndClass(),
  _ClassName(L"MyApplication"),
  _Instance(0),
  _IsInit(false),
  _MainWindow(0),
  _Render(0)
{}

CApplication::~CApplication()
{
  delete _Render;
  delete _MainWindow;
}

HINSTANCE CApplication::GetAppInstance() const
{
  return _Instance;
}

const wstring& CApplication::GetAppClassName() const
{
  return _ClassName;
}

void CApplication::InitWindowClass(const wstring& class_name)
{
  _ClassName                = class_name;
  _WndClass.cbClsExtra      = 0;
  _WndClass.cbWndExtra      = 0;
  _WndClass.hbrBackground   = 0;
  _WndClass.hCursor         = LoadCursor(0,IDC_ARROW);
  _WndClass.hIcon           = LoadIcon(0,IDI_APPLICATION);
  _WndClass.hInstance       = _Instance = GetModuleHandle(0);
  _WndClass.lpfnWndProc     = _WndProc;
  _WndClass.lpszClassName   = _ClassName.c_str();
  _WndClass.lpszMenuName    = 0;
  _WndClass.style           = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  ATOM result = RegisterClass(&_WndClass);
  assert(result != 0);
  _IsInit = true;
}

void CApplication::RunApplication()
{
  Init();
  if(_Render != 0)
  {
    POINT size = _MainWindow->GetSize();
    _Render->Resize(size.x,size.y);
  }
  while(true)
  {
    if( PeekMessage(&_Msg,0,0,0,PM_REMOVE) )
    {
      if(_Msg.message == WM_QUIT)
        break;
      DispatchMessage(&_Msg);
    }
    Update();
    if(_Render != 0)
    {
      _Render->Begin();
        Draw(_Render);
      _Render->End();
    }
  }
}

LRESULT __stdcall CApplication::_WndProc(HWND hWnd,UINT msg, WPARAM wParam, LPARAM lParam)
{
  POINT pos;
  static int client_height;
  switch(msg)
  {
  case WM_DESTROY: PostQuitMessage(0); break;
  case WM_SIZE: _Self->_Render ? _Self->_Render->Resize(LOWORD(lParam), HIWORD(lParam)) : 0;
                client_height = HIWORD(lParam); break;
  case WM_MOUSEMOVE: pos.x = LOWORD(lParam); 
                    pos.y = client_height - HIWORD(lParam); 
                    _Self->OnMouseMove(pos);
                     break;
  case WM_LBUTTONDOWN: pos.x = LOWORD(lParam); 
                       pos.y = client_height - HIWORD(lParam); 
                       _Self->OnMouseLeftClick(pos);
                       std::cout<<"mouse left click p(x,y) = "<<pos.x<<','<<pos.y<<'\n'; break;
  default : return DefWindowProc(hWnd,msg,wParam,lParam);
  }

  return 0;
}

CWindow* CApplication::GetMainWindow()
{
  if(_MainWindow == 0)
  {
    _MainWindow = new CWindow(this);
  }
  return _MainWindow;
}

CRender* CApplication::GetRender()
{
  if(_Render == 0)
  {
    _Render = new CRender(this);
  }
  return _Render;
}

POINT CApplication::GetScreenSize() const 
{
  POINT size;
  size.x = GetSystemMetrics(SM_CXSCREEN);
  size.y = GetSystemMetrics(SM_CYSCREEN);
  return size;
}

bool CApplication::IsInit() const
{
  return _IsInit;
}
