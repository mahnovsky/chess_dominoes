#ifndef _CCHECKERBOARD_H_
#define _CCHECKERBOARD_H_

#include "CTile.h"
#include <vector>

using std::vector;
class CRender;
class CDominoes;

class CCheckerBoard
{
private:
  const int     _Width;
  const int     _Height;
  const int     _Size;
  const int     _TileWidth;
  const int     _TileHeight;
  const int     _TileOffsetX;
  const int     _TileOffsetY;
  const int     _DomWidth;
  const int     _DomHeight;
  vector<CTile> _Tiles;
  vector<CDominoes*> _Domino;

  void _SetLeftNode(CNode& node, int index);
  void _SetRightNode(CNode& node, int index);
  void _SetUpNode(CNode& node, int index);
  void _SetDownNode(CNode& node, int index);
  int _IndexToX(int index);
  int _IndexToY(int index);
  int _XYToIndex(int x, int y);
public:
  CCheckerBoard();
  ~CCheckerBoard();

  void InitCheckBoard();
  void DrawCheckBoard(CRender* render);
  bool AddDminoes(int x, int y, bool hor);
  void ClearDomino();

  void SetEnableTile(int x, int y, bool enable);

  int GetTilesCount() const;
  int GetTilesWidth() const;
  int GetTilesHeight() const;
  int GetOffsetX() const;
  int GetOffsetY() const;
  int GetBoardWidth() const;
};


#endif