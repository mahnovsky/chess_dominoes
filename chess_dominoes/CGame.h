#ifndef _CGAME_H_
#define _CGAME_H_

#include "CApplication.h"
#include "CAggregate.h"
#include "CButton.h"
#include <map>

using std::map;

class CGame : public CApplication
{
private:
  CCheckerBoard     _Board;
  CAggregate        _Aggregate;
  bool              _IsDone;
  CButton           _BtnStart;
  CButton           _BtnClear;
  CButton           _BtnPaste;
  CButton           _BtnCut;
  bool              _IsPasteActive;
  bool              _IsCutActive;
  vector<CButton*>  _Buttons;
  map<CButton*,void (CGame::*)() > _Metods;
public:
  CGame();
  ~CGame();

  void Init();
  void Draw(CRender* render);
  void Update();

  void Start();
  void Clear();
  void Paste();
  void Cut();

  //! events
  void OnMouseMove(POINT& p);
  void OnMouseLeftClick(POINT& p);
};

#endif
