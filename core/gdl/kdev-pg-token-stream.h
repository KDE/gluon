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

//krazy:excludeall=inline
#ifndef KDEV_PG_TOKEN_STREAM_H
#define KDEV_PG_TOKEN_STREAM_H

#include <QtCore/QtGlobal>

#include "kdev-pg-location-table.h"

namespace KDevPG
{

class Token {
  public:
    int kind;
    qint64 begin;
    qint64 end;
};

/**
 * This class stores a stream of tokens and has an associated location table.
 * You can add tokens and traverse them (Java-style unidirectional iterator with random access).
 * Internal representation similar to a std::vector (capacity gets multiplied if it get exceeded).
 * @todo Fix inconsistencies in naming: advance vs. next vs. nextToken, token vs. nextToken
 */
template<class T>
class TokenStreamBase
{
public:
  typedef T Token;
  TokenStreamBase()
    : mTokenBuffer(0),
      mTokenBufferSize(0),
      mIndex(0),
      mTokenCount(0),
      mLocationTable(0)
  {
    reset();
  }

  ~TokenStreamBase()
  {
    if (mTokenBuffer)
      ::free(mTokenBuffer);
    if (mLocationTable)
      delete mLocationTable;
  }
  
  /**
   * Clears the stream.
   * @note It does not free the reserved memory, because usually as much memory is required as before.
   * @note It will not affect the location table.
   * @sa free
   */
  inline void reset()
  {
    mIndex = 0;
    mTokenCount = 0;
  }
  
  /**
   * Clears the stream and frees all memory.
   * @note It will not affect the location table.
   * @sa reset
   */
  inline void free()
  {
    mIndex = 0;
    mTokenCount = 0;
    ::free(mTokenBuffer);
  }
  
  /**
   * The number of tokens in the stream.
   */
  inline qint64 size() const
  {
    return mTokenCount;
  }
  
  /**
   * The current position in the stream.
   * @sa tokenIndex
   */
  inline qint64 index() const
  {
    return mIndex;
  }
  
  /**
   * The index of the token returned by the last invocation of advance/nextToken.
   * @sa index
   */
  inline qint64 tokenIndex() const
  {
    if( mIndex )
      return mIndex - 1;
    return mIndex;
  }
  
  /**
   * Sets the position in the stream.
   * All tokens will be unaffected.
   */
  inline void rewind(qint64 index)
  {
    mIndex = index;
  }
  
  /**
   * Returns the token at the specified position in the stream.
   */
  inline T const &token(qint64 index) const
  {
    return mTokenBuffer[index];
  }
  
  /**
   * Returns the token at the specified position in the stream.
   */
  inline T &token(qint64 index)
  {
    return mTokenBuffer[index];
  }
  
  /**
   * Returns the token kind at the next position and advances.fect the 
   * @sa advance
   */
  inline int nextToken()
  {
    return mTokenBuffer[mIndex++].kind;
  }
  
  /**
   * Pushes a new token to the stream.
   * @warning This function does not affect the position!
   * @return The new uninitialized token
   * @sa advance
   */
  inline T &next()
  {
    if (mTokenCount == mTokenBufferSize)
    {
      if (mTokenBufferSize == 0)
        mTokenBufferSize = 1024;
      
      mTokenBufferSize <<= 2;
      
      mTokenBuffer = reinterpret_cast<T*>
      (::realloc(mTokenBuffer, mTokenBufferSize * sizeof(T)));
    }
    
    return mTokenBuffer[mTokenCount++];
  }
  
  /**
   * Advances and returns the token at the current position.
   * @sa nextToken
   * @sa next
   */
  inline T &advance()
  {
    if (mIndex == mTokenCount)
    {
      if(mTokenCount++ == mTokenBufferSize)
      {
        if (mTokenBufferSize == 0)
          mTokenBufferSize = 1024;
        
        mTokenBufferSize <<= 2;
        
        mTokenBuffer = reinterpret_cast<T*>
        (::realloc(mTokenBuffer, mTokenBufferSize * sizeof(T)));
      }
    }
    
    return mTokenBuffer[mIndex++];
  }
  
  /**
   * Current token in the stream.
   */
  inline T &curr()
  {
    return mTokenBuffer[mIndex];
  }
  
  /**
   * Last token in the stream.
   */
  inline T &back()
  {
    return mTokenBuffer[mTokenCount];
  }
  
  /**
   * First token in the stream.
   */
  inline T &front()
  {
    return mTokenBuffer[0];
  }
  
  /**
   * @return The associated location table.
   */
  inline LocationTable *locationTable()
  {
    if (!mLocationTable)
      mLocationTable = new LocationTable();

    return mLocationTable;
  }
  
  /**
   * Coordinates of the beginning of the first token.
   */
  inline void startPosition(qint64 index, qint64 *line, qint64 *column)
  {
    if (!mLocationTable)
      {
        *line = 0; *column = 0;
      }
    else
      mLocationTable->positionAt(token(index).begin, line, column);
  }
  
  /**
   * Coordinate at the end of all tokens.
   */
  inline void endPosition(qint64 index, qint64 *line, qint64 *column)
  {
    if (!mLocationTable)
      {
        *line = 0; *column = 0;
      }
    else
      mLocationTable->positionAt(token(index).end, line, column);
  }

private:
  T *mTokenBuffer;
  qint64 mTokenBufferSize;
  qint64 mIndex;
  qint64 mTokenCount;
  LocationTable *mLocationTable;

private:
  TokenStreamBase(TokenStreamBase const &other);
  void operator = (TokenStreamBase const &other);
};


class TokenStream : public TokenStreamBase<Token>
{
};


}

#endif // KDEV_PG_TOKEN_STREAM_H

