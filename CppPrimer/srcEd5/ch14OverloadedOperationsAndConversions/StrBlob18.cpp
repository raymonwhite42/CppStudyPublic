#include"StrBlob18.h"
#include"./../common/rr.h"


#include<iostream>
using std::cout; using std::ostream; using std::endl;

#include<algorithm>
using std::transform;

#include<iterator>
using std::ostream_iterator;

#include<string>
using std::string;

#include<algorithm>
using std::lexicographical_compare;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// equality operators

bool operator==(const StrBlob& lhs, const StrBlob& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  return *lhs.data_spt == *rhs.data_spt;
}

bool operator!=(const StrBlob& lhs, const StrBlob& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  return !(lhs==rhs);
}

/////////////////////////////////////////////////////////////////////////////
// relational operators
bool operator<(const StrBlob& lhs, const StrBlob& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  // Checks if the first range [first1, last1) is lexicographically 
  // less than the second range [first2, last2).
  return lexicographical_compare(
           lhs.data_spt->cbegin(), lhs.data_spt->cend(),
           rhs.data_spt->cbegin(), rhs.data_spt->cend());
}

bool operator>(const StrBlob& lhs, const StrBlob& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  // lhs > rhs implies rhs < lhs.
  return rhs < lhs;
}

bool operator<=(const StrBlob& lhs, const StrBlob& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  // lhs <= rhs implies !(lhs>rhs) implies !(rhs<lhs)
  // we use the last one because, putting everything in terms of < uses less
  // indirection.
  //
  //  Careful, to take out the !, we need to invert both equality and 
  //  inequality. I.e. !(rhs<lhs) == rhs >= lhs, as opposed to rhs > lhs
  return !(rhs<lhs);
}

bool operator>=(const StrBlob& lhs, const StrBlob& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  // lhs >= rhs implies !(lhs<rhs)
  return !(lhs<rhs);
}


/////////////////////////////////////////////////////////////////////////////
//copy control

// copy assignment op, needs valuelike behaviour.
StrBlob& StrBlob::operator=(const StrBlob& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  data_spt = make_shared<vector<string>>(*rhs.data_spt);
  return *this; // return this (the lhs)
}

// move assignment op, needs valuelike behaviour.
StrBlob& StrBlob::operator=(StrBlob&& rhs) noexcept
{
  rr::greet(__PRETTY_FUNCTION__);

  if(this != &rhs)
  {
    data_spt = std::move(rhs.data_spt);
    rhs.data_spt = nullptr; // remember to leave rhs in a valid state.
  }

  return *this; // return the lhs (this).
}


////////////////////////////////////////////////////////////////////////////
// StrBlob members

// printing everything for checking and debugging.
ostream& StrBlob::printall(ostream& os) const
{
  os << "emp " << this->empty() << ", size " << this->size() << ": ";
  transform(data_spt->begin(),data_spt->end(),
            ostream_iterator<string>(os," "),
            [](const string& s)->string
            {return s;});
  return os;
}

// Check if i is in [0, size), if i >= size, throw error.
// No need to check negative, since size_type is unsigned
void StrBlob::check(size_type i, const std::string &msg) const
{
  if( i >= data_spt->size())
    throw std::out_of_range(msg);
}

// Removes the last element, the element at the back. We have to make sure
// that there is at least one element.
void StrBlob::pop_back()
{
  // How does this work? Well, check(i,msg) will throw an error 
  // if i >= size. Thus, if 0 >= size, then it must be that size == 0, since
  // size cannot be negative. If this is not true (i.e. there is at least 
  // one element in StrBlob), then we can safely continue.
  check(0,"pop_back on empty StrBlob");
  return data_spt->pop_back();
}

// access the first element.
string& StrBlob::front()
{
  rr::greet(__PRETTY_FUNCTION__,this);

  check(0,"front on empty StrBlob");
  return data_spt->front();
}

// access the last element.
string& StrBlob::back()
{
  rr::greet(__PRETTY_FUNCTION__,this);

  check(0,"back on empty StrBlob");
  return data_spt->back();
}

// access the first element.
const string& StrBlob::front() const
{
  rr::greet(__PRETTY_FUNCTION__,this);

  check(0,"front on empty StrBlob");
  return data_spt->front();
}

// access the last element.
const string& StrBlob::back() const
{
  rr::greet(__PRETTY_FUNCTION__,this);

  check(0,"back on empty StrBlob");
  return data_spt->back();
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// operators for StrBlobPtr and ConstStrBlobPtr


// Equality operators
bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{  return lhs.curr == rhs.curr; }

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{ return !(lhs == rhs); }

bool operator==(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{ return lhs.curr == rhs.curr; }

bool operator!=(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{ return !(lhs == rhs); }

////////////////////////////////////////////////////////////////////////////
// inequality operators

// exer14-18 inequality operators
bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);
  // What does it mean for two iterators to be less than?
  // We compare their current positions.
  return lhs.curr < rhs.curr;
}
bool operator>(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);
  // Although we can use >, it's good practice to define everything in terms
  // of <.
  // Thus, lhs > rhs implies rhs < lhs
  return rhs < lhs;
}
bool operator<=(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);
  // lhs<=rhs implies !(lhs>rhs) (now sub in the meaning of >) 
  // implies !(rhs<lhs)
  return !(rhs < lhs);
}
bool operator>=(const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);

  // recall to invert >=, we need to use the one that's left, i.e. <
  // lhs >= rhs == !(lhs < rhs)
  return !(lhs < rhs);
}

// exer14-18 inequality operators///////////////////////////////////////////
bool operator<(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);
  return lhs.curr < rhs.curr;
}

bool operator>(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);
  // lhs > rhs == rhs < lhs
  return rhs < lhs;
}

bool operator<=(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);
  // lhs<=rhs == !(lhs>rhs) == !(rhs < lhs)
  return !(rhs < lhs);
}

bool operator>=(const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{
  rr::greet(__PRETTY_FUNCTION__);
  // lhs>=rhs == !(lhs < rhs)
  return !(lhs < rhs);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


StrBlobPtr StrBlob::begin()
{
  return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
  return StrBlobPtr(*this, size());
}

ConstStrBlobPtr StrBlob::cbegin()
{
  return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::cend()
{
  return ConstStrBlobPtr(*this, size());
}





