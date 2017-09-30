#ifndef _CAGGREGATE_H_
#define _CAGGREGATE_H_

#include "CCheckerBoard.h"

class CAggregate
{
private:
  CCheckerBoard&        _Board;
  const unsigned long   _UpdateTime;
  unsigned long         _CurrentTime;
  int                   _OffsetX;
  int                   _OffsetY;
  float                 _PosX;
  float                 _PosY;
  int                   _TileWidth;
  int                   _BoardWidth;
  int                   _CurrentNode;
public:
  CAggregate(CCheckerBoard& board);
  ~CAggregate();

  void InitAggregate();
  bool NextDominoes();
};

#endif