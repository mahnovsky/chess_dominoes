#include "CCheckerBoard.h"
#include "CRender.h"
#include "CDominoes.h"

CCheckerBoard::CCheckerBoard() :
  _Width(8),
  _Height(8),
  _Size(_Width*_Height),
  _TileWidth(30),
  _TileHeight(30),
  _TileOffsetX(20),
  _TileOffsetY(20),
  _DomWidth(_TileWidth*0.8),
  _DomHeight(_TileHeight*0.8),
  _Tiles(_Size),
  _Domino()
{
}

CCheckerBoard::~CCheckerBoard()
{
  for(int i = 0;i < _Size/2; ++i)
  {
    if(_Domino[i] != 0)
      delete _Domino[i];
  }
}

void CCheckerBoard::InitCheckBoard()
{
  float x = _TileOffsetX,
        y = _TileOffsetY;
  unsigned long color = MACRO_COLOR_R8G8B8(0,0,0);
  bool is_color = false;
  for(int i = 0; i < _Size; ++i)
  {
    if(!(i%_Width) && i != 0)
    {
      is_color = !is_color;
      x = _TileOffsetX;
      y += _TileHeight;
    }
    else if(i != 0)
      x += _TileWidth;

    is_color = !is_color;
    color = is_color ? MACRO_COLOR_R8G8B8(0,0,0) :
          MACRO_COLOR_R8G8B8(255,255,255);
    _Tiles[i].SetColor(color);
    _Tiles[i].SetSize(_TileWidth,_TileHeight);
    _Tiles[i].SetPosition(x,y);
    _Tiles[i].SetEnable(true);
    _Tiles[i].SetNodeID(i);
    _SetLeftNode(_Tiles[i],i);
    _SetRightNode(_Tiles[i],i);
    _SetUpNode(_Tiles[i],i);
    _SetDownNode(_Tiles[i],i);
  }

  srand(timeGetTime());
}

void CCheckerBoard::DrawCheckBoard(CRender* render)
{
  for(int i = 0; i < _Size; ++i)
  {
    _Tiles[i].DrawSelf(render);
  }
  int size_domino = _Domino.size();
  for(int i = 0; i < size_domino; ++i)
  {
    if(_Domino[i] != 0)
      _Domino[i]->DrawSelf(render);
  }
}

bool CCheckerBoard::AddDminoes(int x, int y, bool hor)
{
  int ix =  (x - _TileOffsetX)/_TileWidth;
  int iy =  (y - _TileOffsetY)/_TileHeight;
  int index = _XYToIndex(ix,iy);
  if(index < 0 || index >= _Tiles.size())
    return false;

  CNode* tile = &_Tiles[index];

  if(tile->GetLayerUp() != 0 || !tile->IsEnable())
     return false;

  int index1 = -1;
  int width = _DomWidth;
  int height = _DomHeight;

  if(hor)
  {
    index1 = tile->GetNodeID(CNode::NI_RIGHT);
    width = _DomWidth*2;
  }
  else
  {
    index1 = tile->GetNodeID(CNode::NI_UP);
    height = _DomHeight*2;
  }

  if(index1 == -1)
    return false;

  CNode* tile1 = &_Tiles[index1];

  if(tile1->IsEnable() && tile1->GetLayerUp() == 0)
  {
    CDominoes* dom = new CDominoes(hor);

    float dw = static_cast<float>(_TileWidth - _DomWidth)/(hor ? 1 : 2);
    float dh = static_cast<float>(_TileHeight - _DomHeight)/(hor ? 2 : 1);
    float pos_x = tile->GetPositionX() + dw;
    float pos_y = tile->GetPositionY() + dh;

    dom->SetSize(width,height);
    dom->SetPosition(pos_x,pos_y);
    tile->SetLayerUp(dom);
    tile1->SetLayerUp(dom);
    dom->SetLayerDown(tile);
    dom->SetEnable(true);
    _Domino.push_back(dom);
    return true;
  }

  return false;
}

int CCheckerBoard::_IndexToX(int index)
{
  return (index%_Width);
}

int CCheckerBoard::_IndexToY(int index)
{
  return (index/_Width);
}

int CCheckerBoard::_XYToIndex(int x, int y)
{
  return (x + y*_Width);
}


void CCheckerBoard::_SetLeftNode(CNode& node, int index)
{
  int x = _IndexToX(index);
  int y = _IndexToY(index);
  if(x > 0)
  {
    int i = _XYToIndex(x-1,y);
    node.SetNodeID(i,CNode::NI_LEFT);
  }
}

void CCheckerBoard::_SetRightNode(CNode& node, int index)
{
  int x = _IndexToX(index);
  int y = _IndexToY(index);
  if(x < (_Width - 1))
  {
    int i = _XYToIndex(x+1,y);
    node.SetNodeID(i,CNode::NI_RIGHT);
  }
}

void CCheckerBoard::_SetUpNode(CNode& node, int index)
{
  int x = _IndexToX(index);
  int y = _IndexToY(index);
  if(y < (_Height - 1))
  {
    int i = _XYToIndex(x,y+1);
    node.SetNodeID(i,CNode::NI_UP);
  }
}

void CCheckerBoard::_SetDownNode(CNode& node, int index)
{
  if(index == 18)
    index = 18;
  int x = _IndexToX(index);
  int y = _IndexToY(index);
  if(y > 0)
  {
    int i = _XYToIndex(x,y-1);
    node.SetNodeID(i,CNode::NI_DOWN);
  }
}

int CCheckerBoard::GetTilesCount() const
{
  return _Size;
}

int CCheckerBoard::GetTilesWidth() const
{
  return _TileWidth;
}

int CCheckerBoard::GetTilesHeight() const
{
  return _TileHeight;
}

int CCheckerBoard::GetOffsetX() const
{
  return _TileOffsetX;
}

int CCheckerBoard::GetOffsetY() const
{
  return _TileOffsetY;
}

int CCheckerBoard::GetBoardWidth() const
{
  return _Width;
}

void CCheckerBoard::SetEnableTile(int x, int y, bool enable)
{
  int ix = (x - _TileOffsetX)/_TileWidth;
  int iy = (y - _TileOffsetY)/_TileHeight;
  int index = _XYToIndex(ix,iy);
  if(index >= 0 && index < _Tiles.size())
    _Tiles[index].SetEnable(enable);
}

void CCheckerBoard::ClearDomino()
{
  for(int i = _Tiles.size() - 1;i >= 0 ; --i)
  {
    _Tiles[i].SetLayerUp(0);
  }
  for(int i = _Domino.size() - 1;i >= 0; --i)
  {
    delete _Domino[i];
    _Domino.pop_back();
  }
}
