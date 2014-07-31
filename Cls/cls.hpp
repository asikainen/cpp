/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef cls_hpp
#define cls_hpp

// File containing definitions for various classes.

class Cat
{
public:
  Cat(int age):itsAge(age) { HowManyCats++;}
  Cat() { HowManyCats++;}
  virtual ~Cat() { HowManyCats--;}
  virtual int GetAge() { return itsAge;}
  virtual void SetAge(int age) { itsAge = age;}
  static int HowManyCats;

private:
  int itsAge;
};

#endif
