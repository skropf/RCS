#ifndef cmp_str_h
#define cmp_str_h


struct str_cmp
{
   bool operator()(char const *a, char const *b)
   {
      return strcmp(a, b) < 0;
   }
};

#endif