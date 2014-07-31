/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef point_hpp
#define point_hpp

// Pi
static const double pi = acos(-1.0);  // Pi

// class Point; 2D point
template <class T>
class Point
{
public:
  // Variables
  T x;
  T y;

  // Constr. & destr.
  Point(const T = 0, const T = 0);
  ~Point();

  // Operators
  inline Point<T> & operator = (const Point<T> &);
  inline Point<T> & operator -= (const Point<T> &);
  inline Point<T> & operator += (const Point<T> &);

  // Methods
  inline Point<T> & Rotate(const double);

  // Friend function
  friend ostream& operator << <T>(ostream &, const Point<T> &);
};

// Constructor
template <class T>
Point<T> :: Point(const T x_, const T y_) :
  x (x_),
  y (y_)
{}

// Destructor
template<class T>
Point<T> :: ~Point()
{}

// Subtraction with substitution
template <class T>
inline Point<T>& Point<T>::operator -= (Point<T> const& p)
{
  x -= p.x;
  y -= p.y;
  return *this;
}

// Addition with substitution
template <class T>
inline Point<T>& Point<T>::operator += (Point<T> const& p)
{
  x += p.x;
  y += p.y;
  return *this;
}

// Output
template <class T>
ostream& operator << (ostream &output, const Point<T> & p)
{
  output << p.x << " " << p.y << endl;
  return output;
}

// Rotation (theta given in degrees)
template <class T>
inline Point<T> & Point<T> :: Rotate(const double theta)
{
  const T xold = x, yold = y;
  const double ct = cos(theta), st = sin(theta);
  x = xold * ct - yold * st;
  y = xold * st + yold * ct;
  return *this;
}

#endif
