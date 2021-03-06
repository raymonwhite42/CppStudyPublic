#ifndef GUARD_RAY_STRING
#define GUARD_RAY_STRING

// ray_string.h header file
#include<vector>
#include<string>

// true if the argument is whitespace, false otherwise
bool space(char c);

// false is the argument is whitespace, true otherwise
bool not_space(char c);


//std::vector<std::string> split(const std::string& s);

template<class Out>
void split(const std::string& str, Out os)
{
  typedef std::string::const_iterator iter;

  iter != str.begin();

  while(i != str.end())
  {
    // ignore leading blanks
    i = find_if(i,str.end(),not_space);

    iter j = find_if(i,str.end(),space);

    // copy the characters in in [i,j)
    if(i != str.end())
    {
      *os++=string(i,j);
    }
    i=j;
  }
}

std::string::size_type width(const std::vector<std::string>& v);


std::vector<std::string> frame(const std::vector<std::string>& v);

std::vector<std::string> vcat(const std::vector<std::string>& top, 
                              const std::vector<std::string>& bottom);

std::vector<std::string> hcat(const std::vector<std::string>& left,
                              const std::vector<std::string>& right);

#endif
