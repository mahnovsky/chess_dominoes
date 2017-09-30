#include "CAggregate.h"
#include "CCheckerBoard.h"
#include <Windows.h>

CAggregate::CAggregate(CCheckerBoard& board) :
  _Board(board),
  _UpdateTime(200),
  _CurrentTime(0),
  _OffsetX(0),
  _OffsetY(0),
  _PosX(0),
  _PosY(0),
  _TileWidth(0),
  _BoardWidth(0),
  _CurrentNode(0)
{}

CAggregate::~CAggregate()
{}

void CAggregate::InitAggregate()
{
  _OffsetX = _Board.GetOffsetX();
  _OffsetY = _Board.GetOffsetY();
  _PosX = _OffsetX;
  _PosY = _OffsetY;
  _TileWidth = _Board.GetTilesWidth();
  _BoardWidth = _Board.GetBoardWidth()*_TileWidth;
  _CurrentTime = timeGetTime() + _UpdateTime;
  _CurrentNode = 0;
}

bool CAggregate::NextDominoes()
{
  if(timeGetTime() >= _CurrentTime)
  {
    _CurrentTime = timeGetTime() + _UpdateTime;
    if(_CurrentNode >= _Board.GetTilesCount())
      return false;

    if( !_Board.AddDminoes(_PosX,_PosY,true) )
      _Board.AddDminoes(_PosX,_PosY,false);

    ++_CurrentNode;
    _PosX += _TileWidth;
    if(_PosX >= _BoardWidth)
    {
      _PosX = _OffsetX;
      _PosY += _Board.GetTilesHeight();
    }
  }
  return true;
}