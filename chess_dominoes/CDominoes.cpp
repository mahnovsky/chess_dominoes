#include "CDominoes.h"
#include "CRender.h"

CDominoes::CDominoes(bool hor) :
  CNode(),
  _PointCount(rand()%2),
  _IsHorizontal(hor)
{
  _Color = MACRO_COLOR_R8G8B8(150,150,0);
  _LinePointColor = MACRO_COLOR_R8G8B8(0,255,0);
}

CDominoes::~CDominoes()
{}

void CDominoes::DrawSelf(CRender* render)
{
  if( IsEnable() )
  {
    render->DrawRect(_PosX1,_PosY1,_PosX2,_PosY2,_Color);
    float x1 = 0, y1 = 0,
          x2 = 0, y2 = 0;
    if(_IsHorizontal)
    {
      y1 = _PosY1;
      y2 = _PosY2;
      x1 = _PosX1 + _Width/2;
      x2 = _PosX2 - _Width/2;
    }
    else
    {
      x1 = _PosX1;
      x2 = _PosX2;
      y1 = _PosY1 + _Height/2;
      y2 = _PosY2 - _Height/2;
    }
    render->DrawLine(x1,y1,x2,y2,_LinePointColor);

    if(_PointCount == 0)
    {
      if(_IsHorizontal)
      {
        x1 -= _Width/4;
        x2 += _Width/4;
        y1 += _Height/2;
        y2 -= _Height/2;
      }
      else
      {
        y1 -= _Height/4;
        y2 += _Height/4;
        x1 += _Width/2;
        x2 -= _Width/2;
      }
      render->DrawPoint(x1,y1,_LinePointColor);
      render->DrawPoint(x2,y2,_LinePointColor);
    }
    else if(_PointCount == 1)
    {
      for(int i = 0;i < 2;++i)
      {
        if(_IsHorizontal)
        {
          if(i == 0)
          {
            x1 += _Width/4;
            x2 -= _Width/4;
          }
          y1 += (_Height/4 + _Height/4*i);
          y2 -= (_Height/4 + _Height/4*i);
        }
        else
        {
          if(i == 0)
          {
            y1 -= _Height/4;
            y2 += _Height/4;
          } 
          x1 += (_Width/4 + _Width/4*i);
          x2 -= (_Width/4 + _Width/4*i);
        }
        render->DrawPoint(x1,y1,_LinePointColor);
        render->DrawPoint(x2,y2,_LinePointColor);
      }
    }
  }
} 