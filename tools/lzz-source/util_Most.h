// util_Most.h
//

#ifndef LZZ_util_Most_h
#define LZZ_util_Most_h
#define LZZ_INLINE inline
namespace util
{
  template <typename In>
  In most (In first, In last);
}
namespace util
{
  template <typename In, typename Cmp>
  In most (In first, In last, Cmp cmp);
}
namespace util
{
  template <typename In>
  In most (In first, In last)
  {
    In i = first, most_i;
    int c = 1, most_c = 0;
    while (++ first != last)
    {
      if (* i == * first)
      {
        c ++;
      }
      else
      {
        if (c > most_c)
        {
          most_c = c;
          most_i = i;
        }
        i = first;
        c = 1;
      }
    }
    if (c > most_c)
    {
      most_i = i;
    }
    return most_i;
  }
}
namespace util
{
  template <typename In, typename Cmp>
  In most (In first, In last, Cmp cmp)
  {
    In i = first, most_i;
    int c = 1, most_c = 0;
    while (++ first != last)
    {
      if (cmp (* i, * first))
      {
        c ++;
      }
      else
      {
        if (c > most_c)
        {
          most_c = c;
          most_i = i;
        }
        i = first;
        c = 1;
      }
    }
    if (c > most_c)
    {
      most_i = i;
    }
    return most_i;
  }
}
#undef LZZ_INLINE
#endif
