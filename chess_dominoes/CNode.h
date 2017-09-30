#ifndef _CNODE_H_
#define _CNODE_H_

class CRender;

class CNode
{
protected:
  unsigned long       _Color;
  bool                _IsEnable;
  float               _PosX1, _PosY1;
  float               _PosX2, _PosY2;
  int                 _Width, _Height;
  CNode*              _LayerUp;
  CNode*              _LayerDown;
  int                 _ID;
  int                 _Indexes[4];
public:
  CNode();
  ~CNode();

  enum E_NODE_INDEXES 
  {
    NI_LEFT,
    NI_RIGHT,
    NI_UP,
    NI_DOWN,
    NI_CENTER
  };

  virtual void DrawSelf(CRender* render){}
  
  void SetColor(unsigned long color);
  void SetPosition(float x, float y);
  void SetEnable(bool enable);
  void SetSize(int w, int h);
  void SetLayerUp(CNode* node);
  void SetLayerDown(CNode* node);
  void SetNodeID(int id, E_NODE_INDEXES ni = NI_CENTER);

  bool IsEnable() const;
  long GetColor() const;
  float GetPositionX() const;
  float GetPositionY() const;
  int GetWidth() const;
  int GetHeight() const;
  CNode* GetLayerUp() const;
  CNode* GetLayerDown() const;
  int GetNodeID(E_NODE_INDEXES ni = NI_CENTER) const;
};


#endif