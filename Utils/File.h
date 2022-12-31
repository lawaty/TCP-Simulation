class File
{
private:
  string filename;
  ifstream in;

public:
  File(string filename)
  {
    this->filename = filename;
    in.open(filename);
  }

  bool exists()
  {
    return in ? true : false;
  }

  double getSize()
  {
    return (double)in.tellg();
  }

  /**
   * Methods reads the next 'len' characters from a file
  */
  string read(int len)
  {
    string buffer;
    char c;
    for(int i = 0;i < len; i++){
      if(!in.get(c))
        break;

      buffer += c;
    }

    return buffer;
  }
};