
#include <System/OS/PlatformIncludes.h>
#include <Utils/BcString.h>
#include <stdio.h>

#define Min(x,y) ((x) < (y) ? (x) : (y))
#define Max(x,y) ((x) > (y) ? (x) : (y))
#define MAX_STRING_FORMATTING_SIZE 256

namespace BearClaw
    {
        BcString Format(const char *Text,...)
            {
                va_list List;
                va_start(List,Text);
                int Size = strlen(Text) + MAX_STRING_FORMATTING_SIZE;
                //char Formatted[Size]; <--- Not acceptable on other compilers apparently
                char *Formatted =  AllocStr(Size);

                vsnprintf(Formatted,Size,Text,List);
                va_end(List);

                BcString Str;
                for(Index i = 0;Formatted[i] != '\0';i++)
                {
                    Str += Formatted[i];
                }
                Str += '\0';

				free (Formatted);
                return Str;
            }
        BcString::BcString()
            {
            }
        BcString::BcString(const char *Text)
            {
                RecalcHash = true;
                Str.Clear();
                for(Index i = 0;Text[i] != '\0';i++)
                {
                    Str.PushBack(Text[i]);
                }
                Str.PushBack('\0');
            }
        BcString::BcString(char *String)
            {
                RecalcHash = true;
                Str.Clear();
                for(Index i = 0;String[i] != '\0';i++)
                {
                    Str.PushBack(String[i]);
                }
                Str.PushBack('\0');
            }
        BcString::BcString(u32 Length,char *String)
            {
                RecalcHash = true;
                Str.Clear();
                for(Index i = 0;i < Length;i++)
                {
                    Str.PushBack(String[i]);
                }
                if(Str[Str.Size() - 1] != '\0') Str.PushBack('\0');
            }
        BcString::~BcString()
            {
            }

        void BcString::SetFromFormat(const char *Text,...)
            {
                va_list List;
                va_start(List,Text);
                int Size = strlen(Text) + MAX_STRING_FORMATTING_SIZE;
                //char Formatted[Size];
                char * const Formatted = (char*)malloc(Size * sizeof(char));
                vsnprintf(Formatted,Size,Text,List);
                va_end(List);

                RecalcHash = true;
                Str.Clear();
                for(Index i = 0;Formatted[i] != '\0';i++)
                {
                    Str.PushBack(Formatted[i]);
                }
                Str.PushBack('\0');
            }
        Index BcString::FindAllOf(char Character,SIndexList &Indices) const
            {
                Index Count = 0;
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == Character) { Indices.PushBack(i); Count++; }
                }
                return Count;
            }
        Index BcString::FindAllOf(char *String,SIndexList &Indices) const
            {
                Index Count = 0;
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == String[0])
                    {
                        bool IsIt = false;
                        char c = String[0];
                        int s = 0;
                        while(c != '\0' && i + s < Length())
                        {
                            IsIt = c == Str[i + s];
                            if(!IsIt) break;
                            s++;
                            c = String[s];
                        }
                        if(IsIt) { Indices.PushBack(i); Count++; }
                    }
                }
                return Count;
            }
        Index BcString::FindAllOf(const char *String,SIndexList &Indices) const
            {
                Index Count = 0;
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == String[0])
                    {
                        bool IsIt = false;
                        char c = String[0];
                        int s = 0;
                        while(c != '\0' && i + s < Length())
                        {
                            IsIt = (c == Str[i + s]);
                            if(!IsIt) break;
                            s++;
                            c = String[s];
                        }
                        if(IsIt) { Indices.PushBack(i); Count++;}
                    }
                }
                return Count;
            }
        Index BcString::FindAllOf(const BcString &String,SIndexList &Indices) const
            {
                Index Count = 0;
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == String[(Index)0])
                    {
                        bool IsIt = false;
                        for(Index s = 0;s < String.Length() - 1 && i + s < Length();s++)
                        {
                            IsIt = (Str[i + s] == String[s]);
                            if(!IsIt) break;
                        }
                        if(IsIt) { Indices.PushBack(i); Count++; }
                    }
                }
                return Count;
            }

        Index BcString::FindFirst(char Character) const
            {
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == Character) { return i; }
                }
                return 0;
            }
        Index BcString::FindFirst(char *String) const
            {
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == String[0])
                    {
                        bool IsIt = false;
                        char c = String[0];
                        int s = 0;
                        while(c != '\0' && i + s < Length())
                        {
                            IsIt = c == Str[i + s];
                            if(!IsIt) break;
                            s++;
                            c = String[s];
                        }
                        if(IsIt) { return i; }
                    }
                }
                return 0;
            }
        Index BcString::FindFirst(const char *String) const
            {
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == String[0])
                    {
                        bool IsIt = false;
                        char c = String[0];
                        int s = 0;
                        while(c != '\0' && i + s < Length())
                        {
                            IsIt = (c == Str[i + s]);
                            if(!IsIt) break;
                            s++;
                            c = String[s];
                        }
                        if(IsIt) { return i; }
                    }
                }
                return 0;
            }
        Index BcString::FindFirst(const BcString &String) const
            {
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == String[(Index)0])
                    {
                        bool IsIt = false;
                        for(Index s = 0;s < String.Length() - 1 && i + s < Length();s++)
                        {
                            IsIt = (Str[i + s] == String[s]);
                            if(!IsIt) break;
                        }
                        if(IsIt) { return i; }
                    }
                }
                return 0;
            }

        bool BcString::Contains(char Character,Index Num) const
            {
                if(Num == 0)
                {
                    for(Index i = 0;i < Length();i++)
                    {
                        if(Str[i] == Character) return true;
                    }
                    return false;
                }
                Index Occurrences = 0;
                for(Index i = 0;i < Length();i++)
                {
                    if(Str[i] == Character) Occurrences++;
                }
                return Occurrences = Num;
            }
        bool BcString::Contains(const char *String,Index Num) const
            {
                BcVector <Index>Indices;
                FindAllOf(String,Indices);
                if(Num == 0) return Indices.Size() > 0;
                return Indices.Size() == Num;
            }
        bool BcString::Contains(char *String,Index Num) const
            {
                BcVector <Index>Indices;
                FindAllOf(String,Indices);
                if(Num == 0) return Indices.Size() > 0;
                return Indices.Size() == Num;
            }
        bool BcString::Contains(const BcString &String,Index Num) const
            {
                BcVector <Index>Indices;
                FindAllOf(String,Indices);
                if(Num == 0) return Indices.Size() > 0;
                return Indices.Size() == Num;
            }
        void BcString::Clear()
            {
                RecalcHash = true;
                Str.Clear();
            }
        void BcString::Erase(Index From,Index To)
            {
                RecalcHash = true;
                Str.Erase(Min(From,To),Max(From,To));
                if(Str[Str.Size() - 1] != 0) Str.PushBack(0);
            }
        void BcString::Erase(Index Idx)
            {
                RecalcHash = true;
                Str.Erase(Idx);
                if(Str[Str.Size() - 1] != 0) Str.PushBack(0);
            }
        void BcString::EraseTo(Index Idx)
            {
                RecalcHash = true;
                Str.Erase(0,Idx);
            }
        void BcString::EraseFrom(Index Idx)
            {
                RecalcHash = true;
                Str.Erase(Idx,Str.Size());
            }
        BcString BcString::Substr(Index From,Index To) const
            {
                i32 mn = Min(From,To);
                i32 mx = Max(From,To);
                //if(mn == mx) ERROR("Substr indices must not be equal.\n");

                BcString String;

                for(i32 i = mn;i < mx;i++)
                {
                    String.Str.PushBack(Str[i]);
                }

                if(String.Str[String.Length() - 1] != 0) String.Str.PushBack(0);
                return String;
            }
        void BcString::Insert(Index Idx,const BcString &String)
            {
                RecalcHash = true;
                for(Index i = 0;i < String.Length();i++)
                {
                    if(String[i] != '\0') Str.Insert(Idx + i,String[i]);
                }
            }

        void BcString::Replace(char Character,char With)
            {
                BcVector <Index>Indices;
                FindAllOf(Character,Indices);
                if(Indices.Size() == 0) return;
                RecalcHash = true;
                for(Index i = 0;i < Indices.Size();i++)
                {
                    Str[Indices[i]] = Character;
                }
            }
        void BcString::Replace(const BcString &String,const BcString &With)
            {
                BcVector <Index>Indices;
                FindAllOf(String,Indices);
                if(Indices.Size() == 0) return;
                RecalcHash = true;
                Index Offset = 0;
                Index StrSz = String.Length() - 1;
                Index WithSz = With.Length() - 1;

                for(Index i = 0;i < Indices.Size();i++)
                {
                    Index nIdx = Indices[i] + Offset;

                    //Erase String
                    Erase(nIdx,nIdx + StrSz);

                    //Insert With
                    Insert(nIdx,With);

                    //Offset Indices
                    Offset -= StrSz;
                    Offset += WithSz;
                }
            }
        void BcString::Remove(char Character)
            {
                BcVector <Index>Indices;
                FindAllOf(Character,Indices);
                if(Indices.Size() == 0) return;
                RecalcHash = true;
                for(Index i = 0;i < Indices.Size();i++)
                {
                    Str.Erase(Indices[i]);
                }
            }
        void BcString::Remove(const BcString &String)
            {
                BcVector <Index>Indices;
                FindAllOf(String,Indices);
                if(Indices.Size() == 0) return;
                RecalcHash = true;
                Index Offset = 0;
                Index StrSz = String.Length() - 1;

                for(Index i = 0;i < Indices.Size();i++)
                {
                    Index nIdx = Indices[i] + Offset;

                    //Erase String
                    Erase(nIdx,nIdx + StrSz);

                    //Offset Indices
                    Offset -= StrSz;
                }
            }
        Index BcString::GetTokens(const BcString &Separators,TokenList &Tokens) const
            {
                BcVector <Index>SepIndices;
                BcString Token;
                for(Index i = 0;i < Length();i++)
                {
                    bool IsSeparator = false;
                    for(Index s = 0;s < Separators.Length() - 1;s++)
                    {
                        IsSeparator = (Str[i] == Separators[s]);
                        if(IsSeparator) break;
                    }

                    if(!IsSeparator) { Token += Str[i]; }
                    else if(Token.Length() != 0) { Token += '\0'; Tokens.PushBack(Token); Token.Clear(); }
                }
                if(Token.Length() != 0) Tokens.PushBack(Token);
                return Tokens.Size();
            }
        f32 BcString::ToFloat() const
            {
                return atof(Ptr());
            }
        f64 BcString::ToDouble() const
            {
                return strtod(Ptr(),0);
            }
        i32 BcString::ToInt() const
            {
                return atoi(Ptr());
            }
        char *BcString::Ptr()
            {
                return &Str[0];
            }
        const char *BcString::Ptr() const
            {
                return Str.Ptr();
            }

        Index BcString::Length() const
            {
                return Str.Size();
            }

        void BcString::operator =(const char *String)
            {
                RecalcHash = true;
                Str.Clear();

                Index i = 0;
                for(;String[i] != '\0';i++)
                {
                    Str.PushBack(String[i]);
                }
                if(i == 0) return;
                Str.PushBack('\0');
            }
        void BcString::operator =(char *String)
            {
                RecalcHash = true;
                Str.Clear();
                Index i = 0;
                for(;String[i] != '\0';i++)
                {
                    Str.PushBack(String[i]);
                }
                if(i == 0) return;
                Str.PushBack('\0');
            }
        void BcString::operator =(char Character)
            {
                RecalcHash = true;
                Str.Clear();
                if(Character == 0) return;
                Str.PushBack(Character);
            }
        /*bool BcString::operator ==(const BcString &String) const
            {
                if(Length() != String.Length()) return false;
                for(Index i = 0;i < Length();i++) if(Str[i] != String[i]) return false;
                return true;
            }*/
        bool BcString::operator ==(const char *String) const
            {
                if(Str.Size() == 0) return String[0] == 0;
                Index EndOffset = 0;

                if(Str[Str.Size() - 1] == '\0') EndOffset = 1;
                for(int i = 0;i < Length() - EndOffset;i++) if(Str[i] != String[i]) return false;
                return true;
            }
        bool BcString::operator ==(char *String) const
            {
                if(Str.Size() == 0) return String[0] == 0;
                Index EndOffset = 0;

                if(Str[Str.Size() - 1] == '\0') EndOffset = 1;
                for(int i = 0;i < Length() - EndOffset;i++) if(Str[i] != String[i]) return false;
                return true;
            }
        bool BcString::operator !=(const BcString &String) const
            {
                if(Str.Size() == 0) return String[0] == 0;
                Index EndOffset = 0;

                if(Str[Str.Size() - 1] == '\0') EndOffset = 1;
                for(int i = 0;i < Length() - EndOffset;i++) if(Str[i] != String[i]) return true;
                return false;
            }
        bool BcString::operator !=(const char *String) const
            {
                if(Str.Size() == 0) return String[0] != 0;
                Index EndOffset = 0;

                if(Str[Str.Size() - 1] == '\0') EndOffset = 1;
                for(int i = 0;i < Length() - EndOffset;i++) if(Str[i] != String[i]) return true;
                return false;
            }
        bool BcString::operator !=(char *String) const
            {
                if(Str.Size() == 0) return String[0] != 0;
                Index EndOffset = 0;

                if(Str[Str.Size() - 1] == '\0') EndOffset = 1;
                for(int i = 0;i < Length() - EndOffset;i++) if(Str[i] != String[i]) return true;
                return false;
            }
        bool BcString::operator !=(char Character) const
            {
                if(Length() != 1) return true;
                return Str[0] != Character;
            }
        void BcString::operator +=(const BcString &String)
            {
                if(String.Length() == 0) return;
                RecalcHash = true;
                if(Str.Size() > 0 && Str[Str.Size() - 1] == 0) Str.Erase(Str.Size() - 1);
                for(Index i = 0;i < String.Length();i++) Str.PushBack(String[i]);
                if(Str[Length() - 1] != 0) Str.PushBack(0);
            }
        void BcString::operator +=(const char *String)
            {
                RecalcHash = true;
                if(Str.Size() > 0 && Str[Str.Size() - 1] == 0) Str.Erase(Str.Size() - 1);
                for(Index i = 0;String[i] != '\0';i++)
                {
                    Str.PushBack(String[i]);
                }
                Str.PushBack(0);
            }
        void BcString::operator +=(char *String)
            {
                RecalcHash = true;
                if(Str.Size() > 0 && Str[Str.Size() - 1] == 0) Str.Erase(Str.Size() - 1);
                for(Index i = 0;String[i] != '\0';i++)
                {
                    Str.PushBack(String[i]);
                }
                Str.PushBack(0);
            }
        void BcString::operator +=(char Characer)
            {
                RecalcHash = true;
                if(Str.Size() > 0 && Str[Str.Size() - 1] == 0) Str.Erase(Str.Size() - 1);
                Str.PushBack(Characer);
                if(Str[Length() - 1] != 0) Str.PushBack(0);
            }
        void BcString::operator +=(i32 Num)
            {
                char sNum[32];
                sprintf(sNum,"%d",Num);
                *this += sNum;

            }
        void BcString::operator +=(f32 fNum)
            {
                char sNum[64];
                sprintf(sNum,"%f",fNum);
                *this += sNum;
            }
        BcString BcString::operator +(const BcString &String) const
            {
                BcString S;
                S += Ptr();
                S += String;
                return S;
            }
        BcString BcString::operator +(const char *String) const
            {
                BcString S;
                S += Ptr();
                S += String;
                return S;
            }
        BcString BcString::operator +(char *String) const
            {
                BcString S;
                S += Ptr();
                S += String;
                return S;
            }
        BcString BcString::operator +(char Character) const
            {
                BcString S;
                S += Ptr();
                S += Character;
                return S;
            }
        BcString BcString::operator +(i32 Num) const
            {
                BcString S;
                S += Ptr();
                S += Num;
                return S;
            }
        BcString BcString::operator +(f32 fNum) const
            {
                BcString S;
                S += Ptr();
                S += fNum;
                return S;
            }
        /*
        char &BcString::operator [](Index Idx)
            {
                RecalcHash = true;
                return Str[Idx];
            }
        char BcString::operator [](Index Idx) const
            {
                return Str[Idx];
            }
        */
        void BcString::operator --()
            {
                RecalcHash = true;
                Str.Erase(Str.Size() - 1);
            }

        BcString::operator char *()
            {
                return Ptr();
            }
        BcString::operator const char *() const
            {
                return Ptr();
            }

        size_t BcString::operator()(const BcString &Str) const
            {
                BcString &S = const_cast<BcString &>(Str);
                if(!S.RecalcHash) return S.Hash;
                const char *Ptr = S.Ptr();
                unsigned long _Hash = 0;
                for(;*Ptr;++Ptr) _Hash = 5 * _Hash + *Ptr;
                S.Hash = size_t(_Hash);
                S.RecalcHash = false;
                return S.Hash;
            }
    };
