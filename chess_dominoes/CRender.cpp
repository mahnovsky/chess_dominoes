#include "CRender.h"
#include "CApplication.h"
#include "CWindow.h"


CRender::CRender(CApplication* app) :
  _Application(app),
  _DC(0),
  _RC(0),
  _IsInit(false),
  _FontHandle(0),
  _BaseList(0)
{}

CRender::~CRender()
{}

bool CRender::InitRender()
{
  if(!_Application->IsInit())
    return false;

  CWindow* win = _Application->GetMainWindow();
  if( !win->IsInit() )
    return false;

  _DC = GetDC(win->GetWndHandle());
  if(_DC == 0)
    return false;
  
  int format = 0;
  PIXELFORMATDESCRIPTOR pfd=            // pfd �������� Windows ����� ����� ����� �� ����� ������� ������
  {
    sizeof(PIXELFORMATDESCRIPTOR),            // ������ ����������� ������� ������� ��������
    1,                  // ����� ������
    PFD_DRAW_TO_WINDOW |              // ������ ��� ����
    PFD_SUPPORT_OPENGL |              // ������ ��� OpenGL
    PFD_DOUBLEBUFFER,              // ������ ��� �������� ������
    PFD_TYPE_RGBA,                // ��������� RGBA ������
    32,                  // ���������� ��� ������� �����
    0, 0, 0, 0, 0, 0,              // ������������� �������� �����
    0,                  // ��� ������ ������������
    0,                  // ��������� ��� ������������
    0,                  // ��� ������ ����������
    0, 0, 0, 0,                // ���� ���������� ������������
    32,                  // 32 ������ Z-����� (����� �������)
    0,                  // ��� ������ ���������
    0,                  // ��� ��������������� �������
    PFD_MAIN_PLANE,                // ������� ���� ���������
    0,                  // ���������������
    0, 0, 0                  // ����� ���� ������������
  };

  format = ChoosePixelFormat(_DC,&pfd);
  if(format == 0)
    return false;
  
  if( !SetPixelFormat(_DC,format,&pfd) )
    return false;

  _RC = wglCreateContext(_DC);
  if(_RC == 0)
    return false;

  if( !wglMakeCurrent(_DC,_RC) )
    return false;
  
  InitFont();

  glClearColor(0.5,0.5,0.5,0);
  glLineWidth(3);
  glPointSize(3);

  return (_IsInit = true);
}

void CRender::InitFont()
{
  _BaseList = glGenLists(96);
  _FontHandle = CreateFontA(-24,
        0, 
        0,        // ���� ���������
        0,        // ���� �������
        FW_BOLD,      // ������ ������
        FALSE,        // ������
        FALSE,        // �������������
        FALSE,        // ��������������
        ANSI_CHARSET,      // ������������� ������ ��������
        OUT_TT_PRECIS,      // �������� ������
        CLIP_DEFAULT_PRECIS,    // �������� ���������
        ANTIALIASED_QUALITY,    // �������� ������
        FF_DONTCARE|DEFAULT_PITCH,
        "Courier New");

  SelectObject(_DC, _FontHandle);

  wglUseFontBitmaps(_DC, 32, 96, _BaseList);
}

void CRender::DrawRect(float x1,float y1, float x2, float y2,unsigned long color)
{
  glColor3ubv((const  GLubyte*)&color);
  glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x1,y2);
    glVertex2f(x2,y2);
    glVertex2f(x2,y1);
  glEnd();
}

void CRender::DrawLine(float x1,float y1, float x2, float y2,unsigned long color)
{
  glColor3ubv((const  GLubyte*)&color);
  glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
  glEnd();
}

void CRender::DrawPoint(float x,float y,unsigned long color)
{
  glColor3ubv((const  GLubyte*)&color);
  glBegin(GL_POINTS);
    glVertex2f(x,y);
  glEnd();
}

void CRender::DrawString(const string& str, float x, float y, unsigned long color)
{
  glColor3ubv((const  GLubyte*)&color);
  glRasterPos2f(x,y);
  glPushAttrib(GL_LIST_BIT);
  glListBase(_BaseList - 32); 
  glCallLists(str.size(), GL_UNSIGNED_BYTE, str.data());
  glPopAttrib();
}

void CRender::Resize(int w, int h)
{
  glViewport(0,0,w,h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0,w,0,h,-1,1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void CRender::Begin() const
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
}

void CRender::End() const
{
  SwapBuffers(_DC);
}

bool CRender::IsInit() const
{
  return _IsInit;
}