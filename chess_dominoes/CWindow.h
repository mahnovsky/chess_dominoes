#ifndef _CWINDOW_H_
#define _CWINDOW_H_

#include <Windows.h>
#include <string>

using std::wstring;
class CApplication;

class CWindow
{
private:
  CApplication*         _Application;
  HWND                  _WndHandle;
  wstring               _Title;
  POINT                 _Pos;
  POINT                 _Size;
  bool                  _IsInit;
public:
  CWindow(CApplication* app);
  ~CWindow();

  bool InitWindow(const wstring& title, POINT& pos, POINT size);
  bool InitWindow();

  HWND GetWndHandle() const; 
  POINT GetPosition() const;
  POINT GetSize() const;
  bool IsInit() const;

  void SetPosition(const POINT& pos);
  void SetSize(const POINT& size);
  void SetTitle(const wstring& title);
};

#endif