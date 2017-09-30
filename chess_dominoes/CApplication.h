#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include <Windows.h>
#include <string>

#pragma comment(lib,"winmm.lib");

using std::wstring;
class CWindow;
class CRender;

class CApplication
{
protected:
   ~CApplication();
private:
  static CApplication*  _Self;
  MSG                   _Msg;
  WNDCLASS              _WndClass;
  wstring               _ClassName;
  HINSTANCE             _Instance;
  bool                  _IsInit;

  CWindow*              _MainWindow; 
  CRender*              _Render; 
  static LRESULT __stdcall _WndProc(HWND hWnd,UINT msg, WPARAM wParam, LPARAM lParam);
public:
  CApplication();

  void InitWindowClass(const wstring& class_name);
  void RunApplication();

  HINSTANCE GetAppInstance() const;
  const wstring& GetAppClassName() const; 
  CWindow* GetMainWindow();
  CRender* GetRender();
  POINT GetScreenSize() const;
  bool IsInit() const;

  virtual void Init(){}
  virtual void Update(){}
  virtual void Draw(CRender* render){}
  
  virtual void OnMouseLeftClick(POINT& pos){}
  virtual void OnMouseMove(POINT& pos){}

  template <class T>
  static CApplication* GetApplication()
  {
    if(_Self == 0)
    {
      _Self = new T();
    }
    return _Self;
  }
};


#endif