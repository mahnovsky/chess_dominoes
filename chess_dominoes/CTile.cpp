#include "CTile.h"
#include "CRender.h"

CTile::CTile() :
  CNode()
{}

CTile::~CTile()
{}

void CTile::DrawSelf(CRender* render)
{
  if(IsEnable())
    render->DrawRect(_PosX1,_PosY1,_PosX2,_PosY2,_Color);
}