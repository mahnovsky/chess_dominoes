#include "CGame.h"
#include "CRender.h"
#include <iostream>

CGame::CGame() :   
  CApplication(),
  _Board(),
  _Aggregate(_Board),
  _IsDone(true),
  _BtnStart(),
  _BtnClear(),
  _BtnPaste(),
  _BtnCut(),
  _IsPasteActive(false),
  _IsCutActive(false),
  _Buttons(),
  _Metods()
{}

CGame::~CGame()
{}


void CGame::Init() 
{
  _Board.InitCheckBoard();
  _Board.SetEnableTile(0,0,false);
  _Board.SetEnableTile(7,7,false);

  _BtnStart.SetText("Start",0);
  _Buttons.push_back(&_BtnStart);
  _Metods.insert(std::pair< CButton*,void (CGame::*)()>(&_BtnStart,&CGame::Start) );

  _BtnClear.SetText("Clear",0);
  _Buttons.push_back(&_BtnClear);
  _Metods.insert(std::pair< CButton*,void (CGame::*)()>(&_BtnClear,&CGame::Clear) );

  _BtnPaste.SetText("Paste",0);
  _Buttons.push_back(&_BtnPaste);
  _Metods.insert(std::pair< CButton*,void (CGame::*)()>(&_BtnPaste,&CGame::Paste) );

  _BtnCut.SetText("Cut",0);
  _Buttons.push_back(&_BtnCut);
  _Metods.insert(std::pair< CButton*,void (CGame::*)()>(&_BtnCut,&CGame::Cut) );

  for(int i = 0;i < _Buttons.size(); ++i)
  {
    _Buttons[i]->SetStatesColor(MACRO_COLOR_R8G8B8(255,255,0),
                                MACRO_COLOR_R8G8B8(0,255,255),
                                MACRO_COLOR_R8G8B8(150,150,0));
    _Buttons[i]->SetEnable(true);
    _Buttons[i]->SetNodeID(i);
    _Buttons[i]->SetSize(150,40);
  }

  _BtnStart.SetPosition(300,200);
  _BtnClear.SetPosition(300,150);
  _BtnPaste.SetPosition(300,100);
  _BtnCut.SetPosition(300,50);

  _Aggregate.InitAggregate();
}

void CGame::Draw(CRender* render)
{
  _Board.DrawCheckBoard(render);
  for(int i = 0;i < _Buttons.size(); ++i)
    _Buttons[i]->DrawSelf(render);
}

void CGame::Update()
{
  if(!_IsDone)
  {
    _IsDone = !_Aggregate.NextDominoes();
  }
} 

void CGame::OnMouseLeftClick(POINT& pos)
{
  if(_IsPasteActive)
  {
    _IsPasteActive = false;
    _Board.SetEnableTile(pos.x,pos.y,true);
  }
  else if(_IsCutActive)
  {
    _IsCutActive = false;
    _Board.SetEnableTile(pos.x,pos.y,false);
  }
  for(int i = 0;i < _Buttons.size(); ++i)
  {
    if( _Buttons[i]->HitTest(pos.x,pos.y) )
    { 
      _Buttons[i]->Press();
     (this->*_Metods[ _Buttons[i] ])();
    }
    else
      _Buttons[i]->Normal();
  }
}

void CGame::OnMouseMove(POINT& pos)
{
  for(int i = 0;i < _Buttons.size(); ++i)
  {
    if( _Buttons[i]->HitTest(pos.x,pos.y) )
      _Buttons[i]->Hover();
    else
      _Buttons[i]->Normal();
  }
}

void CGame::Start()
{
  _Aggregate.InitAggregate();
  _IsDone = false;
  std::cout<< "start aggregate.\n";
}

void CGame::Clear()
{
  if( _IsDone )
  { 
    _Board.ClearDomino();
    std::cout<< "domino clear.\n";
  }
}

void CGame::Paste()
{
  _IsPasteActive = true;
  std::cout<< "paste active.\n";
}

void CGame::Cut()
{
  _IsCutActive = true;
  std::cout<< "cut active.\n";
}

