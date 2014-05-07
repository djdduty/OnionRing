#ifndef BC_STRING_H
#define BC_STRING_H

#include <Utils/BcVector.h>
#include <Utils/EngineMacros.h>
#include <stdint.h>
#include <stdarg.h>

#define GS BcString() +
#define AllocStr(Sz) AllocArray(char,Sz)

namespace BearClaw {

class BcString;

BcString Format(const char *Text,...);

typedef BcVector <BcString> TokenList;
typedef BcVector <Index> SIndexList;

class BcString
{
public:
    BcString();
    BcString(const char *String);
    BcString(char *String);
    BcString(u32 Len,char *String);
    ~BcString();

    void SetFromFormat(const char *Text,...);

    Index FindAllOf(char Character,SIndexList &Indices) const;
    Index FindAllOf(char *String,SIndexList &Indices) const;
    Index FindAllOf(const char *String,SIndexList &Indices) const;
    Index FindAllOf(const BcString &String,SIndexList &Indices) const;

    Index FindFirst(char Character) const;
    Index FindFirst(char *String) const;
    Index FindFirst(const char *String) const;
    Index FindFirst(const BcString &String) const;

    bool Contains(char Character,Index Num = 0) const;
    bool Contains(const char *String,Index Num = 0) const;
    bool Contains(char *String,Index Num = 0) const;
    bool Contains(const BcString &String,Index Num = 0) const;

    void Clear();

    void Erase(Index From,Index To);

    void Erase(Index Idx);

    void EraseTo(Index Idx);

    void EraseFrom(Index Idx);

    BcString Substr(Index From,Index To) const;

    void Insert(Index Idx,const BcString &String);

    void Replace(char Character,char With);

    void Replace(const BcString &String,const BcString &With);

    void Remove(char Character);

    void Remove(const BcString &String);

    Index GetTokens(const BcString &Separators,TokenList &Tokens) const;

    f32 ToFloat() const;
    f64 ToDouble() const;
    i32 ToInt() const;

    char *Ptr();
    const char *Ptr() const;

    Index Length() const;

    void operator =(const char *String);
    void operator =(char *String);
    void operator =(char Character);
    bool operator ==(const char *String) const;
    bool operator ==(char *String) const;
    bool operator ==(char Character) const;
    bool operator !=(const BcString &String) const;
    bool operator !=(const char *String) const;
    bool operator !=(char *String) const;
    bool operator !=(char Character) const;
    void operator +=(const BcString &String);
    void operator +=(const char *String);
    void operator +=(char *String);
    void operator +=(char Character);
    void operator +=(i32 Num);
    void operator +=(f32 fNum);
    BcString operator +(const BcString &String) const;
    BcString operator +(const char *String) const;
    BcString operator +(char *String) const;
    BcString operator +(char Character) const;
    BcString operator +(i32 Num) const;
    BcString operator +(f32 fNum) const;
    char &operator [](Index Idx) {RecalcHash = true; return Str[Idx];}
    //char operator [](Index Idx) const {return Str[Idx];}
    void operator --();
    operator char *();
    operator const char *() const;

    //Hash function
    size_t operator()(const BcString &S) const;

protected:
    bool RecalcHash;
    size_t Hash;
    BcVector <char,Index>Str;
};
}

#endif
