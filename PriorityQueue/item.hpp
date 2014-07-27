#ifndef item_hpp
#define item_hpp

// class Item
class Item
{
private: // private members
  int _key;
  double _value;

public: // public methods
  Item(int key = 0, double value = 0) :
    _key(key), _value(value) {}

  int GetKey() { return _key; }
  double GetValue() { return _value; }
  void SetKey(int key) { _key = key; }
  void SetValue(double value) { _value = value; }
};

#endif
