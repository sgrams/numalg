template <class T>
class MyMatrix {
  public:
    int width;
    T** matrix;
    T*  vector;

    MyMatrix (int Width) {
      this->width  = Width;
      this->matrix = new T*[width];
      for (int i = 0; i < width; i++)
      {
        matrix[i] = new T[width];
      }
      vector = new T[width];
    }
}