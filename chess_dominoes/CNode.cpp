#include "CNode.h"
#include "CRender.h"

CNode::CNode() :
  _Color(0),
  _IsEnable(false),
  _PosX1(0),
  _PosY1(0),
  _PosX2(0),
  _PosY2(0),
  _Width(10),
  _Height(10),
  _LayerUp(0),
  _LayerDown(0),
  _ID(-1)
{
  memset(_Indexes,-1,sizeof(_Indexes));
}

CNode::~CNode()
{}

void CNode::SetColor(unsigned long color)
{
  _Color = color;
}


void CNode::SetPosition(float x, float y)
{
  _PosX1 = x;
  _PosY1 = y;
  _PosX2 = x + _Width;
  _PosY2 = y + _Height;
}

void CNode::SetEnable(bool enable)
{
  _IsEnable = enable;
}
 
void CNode::SetSize(int w, int h)
{
  _Width = w;
  _Height = h;
}

void CNode::SetLayerUp(CNode* node)
{
  _LayerUp = node;
}

void CNode::SetLayerDown(CNode* node)
{
  if(node)
    _LayerDown = node;
}

void CNode::SetNodeID(int id, E_NODE_INDEXES ni)
{
  if(id >= 0 && ni == NI_CENTER)
    _ID = id;
  else if(id >= 0)
    _Indexes[ni] = id;
}

bool CNode::IsEnable() const
{
  return _IsEnable;
}
  
long CNode::GetColor() const
{
  return _Color;
}
  
float CNode::GetPositionX() const
{
  return _PosX1;
}

float CNode::GetPositionY() const
{
  return _PosY1;
}

int CNode::GetWidth() const
{
  return _Width;
}
  
int CNode::GetHeight() const
{
  return _Height;
}

CNode* CNode::GetLayerUp() const
{
  return _LayerUp;
}

CNode* CNode::GetLayerDown() const
{
  return _LayerDown;
}

int CNode::GetNodeID(E_NODE_INDEXES ni) const
{
  if(ni == NI_CENTER)
    return _ID;
  else 
    return _Indexes[ni];
}
