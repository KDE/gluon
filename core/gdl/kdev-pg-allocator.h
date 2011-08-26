 /*
  This file is part of kdev-pg
  Copyright 2005, 2006 Roberto Raggi <roberto@kdevelop.org>

  Permission to use, copy, modify, distribute, and sell this software and its
  documentation for any purpose is hereby granted without fee, provided that
  the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
  KDEVELOP TEAM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
  AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef KDEV_PG_ALLOCATOR_H
#define KDEV_PG_ALLOCATOR_H

#include <memory>
#include <cstdlib>
#include <cstring>

#include <QtCore/QtGlobal>

namespace KDevPG
{

template <class _Tp>
class Allocator
{
public:
  typedef _Tp valueType;
  typedef _Tp* pointer;
  typedef const _Tp* constPointer;
  typedef _Tp& reference;
  typedef const _Tp& constReference;
  typedef ::std::size_t sizeType;
  typedef qint64 differenceType;

  static const sizeType maxBlockCount = sizeType( -1);

  Allocator()
  {
    sBlockIndex = sizeType(-1);
    sCurrentIndex = 0;
    sStorage = 0;
    sCurrentBlock = 0;
  }

  ~Allocator()
  {
      if (sStorage != 0)
      {
        for (sizeType index = 0; index <= sBlockIndex; ++index)
          delete[] sStorage[index];
        std::free(sStorage);
      }
  }
  
  bool contains(void* ptr)
  {
    for(sizeType i = 0; i <= sBlockIndex; ++i)
      if(ptr >= (void*)(sStorage[i]) && ptr < (void*)(sStorage[i] + sBlockSize))
        return true;
    return false;
  }

  pointer address(reference __val)
  {
    return &__val;
  }
  constPointer address(constReference __val) const
  {
    return &__val;
  }

  pointer allocate(sizeType __n, const void* = 0)
  {
    const sizeType bytes = __n * sizeof(_Tp);

    if (sCurrentBlock == 0
        || sBlockSize < sCurrentIndex + bytes)
      {
        ++sBlockIndex;

        sStorage = reinterpret_cast<char**>
          (std::realloc(sStorage, sizeof(char*) * (1 + sBlockIndex)));

        sCurrentBlock = sStorage[sBlockIndex] = reinterpret_cast<char*>
          (new char[sBlockSize]);

        std::memset(sCurrentBlock, 0, sBlockSize);
        sCurrentIndex = 0;
      }

    pointer p = reinterpret_cast<pointer>
      (sCurrentBlock + sCurrentIndex);

    sCurrentIndex += bytes;

    return p;
  }

  void deallocate(pointer __p, sizeType __n)
  {}

  sizeType maxSize() const
  {
    return sizeType( -1) / sizeof(_Tp);
  }

  void contruct(pointer __p, constReference __val)
  {
    new (__p) _Tp(__val);
  }
  void destruct(pointer __p)
  {
    __p->~_Tp();
  }

private:
  template <class _Tp1>
  class Rebind
  {
    typedef Allocator<_Tp1> other;
  };

  template <class _Tp1>
  Allocator(const Allocator<_Tp1> &__o)
  {}

private:
  static const sizeType sBlockSize;
  sizeType sBlockIndex;
  sizeType sCurrentIndex;
  char *sCurrentBlock;
  char **sStorage;
};

template <class _Tp>
const typename Allocator<_Tp>::sizeType
Allocator<_Tp>::sBlockSize = 1 << 16; // 64K

}

#endif // KDEV_PG_ALLOCATOR_H
