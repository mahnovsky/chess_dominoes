#include "CWindow.h"
#include "CApplication.h"

CWindow::CWindow(CApplication* app) :
  _Application(app),
  _WndHandle(0),
  _Title(L""),
  _Pos(),
  _Size(),
  _IsInit(false)
{
  POINT screen = _Application->GetScreenSize(); 
  _Size.x = 500;
  _Size.y = 300;
  _Pos.x = (screen.x / 2) - (_Size.x / 2);
  _Pos.y = (screen.y / 2) - (_Size.y / 2);
}

CWindow::~CWindow()
{}

bool CWindow::InitWindow()
{
  _WndHandle = CreateWindow(_Application->GetAppClassName().c_str(),
                            _Title.c_str(), WS_SYSMENU | WS_VISIBLE |
                            WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                            _Pos.x,_Pos.y,_Size.x,_Size.y,
                            0,0,_Application->GetAppInstance(),0);

  return (_IsInit = (_WndHandle != 0));
}

bool CWindow::InitWindow(const wstring& title, POINT& pos, POINT size)
{
  _Title = title;
  _Pos.x = pos.x;
  _Pos.y = pos.y;
  _Size.x = size.x;
  _Size.y = size.y;

  _WndHandle = CreateWindow(_Application->GetAppClassName().c_str(),
                            _Title.c_str(), WS_SYSMENU | WS_VISIBLE |
                            WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                            _Pos.x,_Pos.y,_Size.x,_Size.y,
                            0,0,_Application->GetAppInstance(),0);

  return (_IsInit = (_WndHandle != 0));
}


HWND CWindow::GetWndHandle() const
{
  return _WndHandle;
}

POINT CWindow::GetPosition() const 
{
  return _Pos;
}

POINT CWindow::GetSize() const
{
  return _Size;
}

void CWindow::SetPosition(const POINT& pos)
{
  _Pos.x = pos.x;
  _Pos.y = pos.y;
  MoveWindow(_WndHandle,_Pos.x,_Pos.y,_Size.x,_Size.y,TRUE);
}

void CWindow::SetSize(const POINT& size)
{
  _Size.x = size.x;
  _Size.y = size.y;
  MoveWindow(_WndHandle,_Pos.x,_Pos.y,_Size.x,_Size.y,TRUE);
}

void CWindow::SetTitle(const wstring& title)
{
  _Title = title;
}

bool CWindow::IsInit() const
{
  return _IsInit;
}
