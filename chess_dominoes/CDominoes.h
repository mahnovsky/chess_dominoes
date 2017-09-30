#ifndef _CDOMINOES_H_
#define _CDOMINOES_H_

#include "CNode.h"
#include <stdlib.h>

class CDominoes : public CNode
{
private:
  const int         _PointCount;
  unsigned long     _LinePointColor;
  bool              _IsHorizontal;
public:
  CDominoes(bool hor);
  ~CDominoes();

  void DrawSelf(CRender* render);
};

#endif