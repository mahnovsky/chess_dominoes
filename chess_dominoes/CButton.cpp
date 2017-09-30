#include "CButton.h"
#include "CRender.h"


CButton::CButton() :
  CNode(),
  _Text(),
  _TextColor(0),
  _TextPosX(0),
  _TextPosY(0),
  _NormalColor(0),
  _HoverColor(0),
  _PressColor(0)
{}

CButton::~CButton()
{}

void CButton::DrawSelf(CRender* render)
{
  if(IsEnable())
  {
    _TextPosX = _PosX1 + _Width*0.2;
    _TextPosY = _PosY1 + _Height*0.15;
    render->DrawRect(_PosX1,_PosY1,_PosX2,_PosY2,_Color);
    render->DrawString(_Text,_TextPosX,_TextPosY,_TextColor);
  }
}

bool CButton::HitTest(int x,int y)
{
  return (x >= _PosX1 && x <= _PosX2 && y >= _PosY1 && y <= _PosY2);
}

void CButton::SetText(const string& text,unsigned long text_color)
{
  _Text = text;
  _TextColor = text_color;
}

void CButton::Normal()
{
  _Color = _NormalColor;
}

void CButton::Hover()
{
  _Color = _HoverColor;
}

void CButton::Press()
{
  _Color = _PressColor;
}

void CButton::SetStatesColor(unsigned long normal, unsigned long hover, unsigned long press)
{
  _NormalColor = normal;
  _HoverColor = hover;
  _PressColor = press;
  _Color = _NormalColor;
}