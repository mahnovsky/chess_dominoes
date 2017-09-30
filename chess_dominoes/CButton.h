#ifndef _CBUTTON_H_
#define _CBUTTON_H_

#include "CNode.h"
#include <string>

using std::string;

class CButton : public CNode
{
private:
  unsigned long     _TextColor;
  string            _Text;
  float             _TextPosX;
  float             _TextPosY;
  unsigned long     _NormalColor;
  unsigned long     _HoverColor;
  unsigned long     _PressColor;
public:
  CButton();
  ~CButton();
  
  void DrawSelf(CRender* render);
  void SetText(const string& text,unsigned long text_color);
  void SetStatesColor(unsigned long normal, unsigned long hover, unsigned long press);
  bool HitTest(int x, int y);

  void Hover();
  void Normal();
  void Press();
};

#endif