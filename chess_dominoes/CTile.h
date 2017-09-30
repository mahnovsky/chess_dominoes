#ifndef _CTILE_H_
#define _CTILE_H_

#include "CNode.h"

class CTile : public CNode
{

public:
  CTile();
  ~CTile();

  void DrawSelf(CRender* render);
};

#endif