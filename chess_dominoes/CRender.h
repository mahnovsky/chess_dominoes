#ifndef _CRENDER_H_
#define _CRENDER_H_

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <string>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#define MACRO_COLOR_R8G8B8(r,g,b) (UINT)((r)+(g<<8)+(b<<16))

using std::string;

class CApplication;
class CWindow;

class CRender
{
private:
  CApplication*       _Application;
  HDC                 _DC;
  HGLRC               _RC;
  bool                _IsInit;
  HFONT               _FontHandle;
  GLuint              _BaseList;
public:
  CRender(CApplication* app);
  ~CRender();
  
  bool InitRender();
  void InitFont();
  void DrawRect(float x1,float y1, float x2, float y2, unsigned long color);
  void DrawLine(float x1,float y1, float x2, float y2, unsigned long color);
  void DrawPoint(float x,float y, unsigned long color);
  void DrawString(const string& str, float x, float y, unsigned long color);

  void Resize(int w, int h);
  void Begin() const;
  void End() const;
  bool IsInit() const;
};

#endif