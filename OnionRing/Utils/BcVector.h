#ifndef BC_VECTOR_H
#define BC_VECTOR_H

/*
 * Ignore this code... it is old and re-written, it used to be a home-made vector using dynamic allocated
 * arrays, but now it is just an addon util to the std vector, which is kind of pointless, but
 * needed, this is the reason for the codes after return;
 * It is so messy because it is old, will clean up later.
 */


#include <System/BcTypes.h>
#include <new>
#include <vector>

using namespace std;
namespace BearClaw
    {
        template <typename StorageType,typename SizeType = i32>
        class BcVector
            {
                public:
                    BcVector(SizeType Reserve = SizeType(10)) : ReserveSz(Reserve), Elements(0), Sz(0), MemSz(0), NextResize(0)
                        {
                        }
                    ~BcVector()
                        {
                            if(Size() != 0) Clear();
                        }
                    void Clear()
                        {
                            vElements.clear();
                            return;

                            if(Sz == 0 || MemSz == 0) return;
                            if(!Elements) return;
                            free(Elements); //delete Elements; //DON'T USE DELETE[]
                            Elements = 0;
                            Sz = 0;
                            MemSz = 0;
                        }
                    void Alloc(SizeType Count)
                        {
                            vElements.clear();
                            vElements.reserve(Count);

                            return;
                            Clear();
                            Elements = (StorageType *)malloc(sizeof(StorageType) * Count);
                            MemSz = sizeof(StorageType) * Count;
                            memset(Elements,0,MemSz);
                        }
                    SizeType Size() const
                        {
                            return vElements.size();
                            return Sz;
                        }
                    void Erase(SizeType Idx)
                        {
                            vElements.erase(vElements.begin() + Idx);
                            return;

                            for(SizeType i = Idx;i < Sz - 1;i++)
                            {
                                Elements[i] = Elements[i + 1];
                            }
                            Sz--;
                        }
                    void Erase(SizeType Idx1,SizeType Idx2)
                        {
                            if(Size() == 0) return;
                            vElements.erase(vElements.begin() + Idx1,vElements.begin() + Idx2);
                            return;

                            if(Idx2 < Idx1)
                            {
                                SizeType T = Idx2;
                                Idx2 = Idx1;
                                Idx1 = T;
                            }

                            SizeType Len = (Idx2 - Idx1);
                            for(SizeType i = Idx1;i < Sz - Len;i++)
                            {
                                Elements[i] = Elements[Idx2 + (i - Idx1)];
                            }
                            Sz -= Len;
                        }
                    void Insert(SizeType Idx,const StorageType &Var)
                        {
                            if(Size() == 0) return;
                            vElements.insert(vElements.begin() + Idx,Var);
                            return;

                            if(SpacesLeft() == 0) Resize();

                            for(SizeType i = Sz;i > Idx;i--)
                            {
                                Elements[i] = Elements[i - 1];
                            }
                            Elements[Idx] = Var;
                            Sz++;
                        }
                    void Remove(const StorageType &Var)
                        {
                            if(Sz == 0) return;
                            for(Index i = 0;i < Size();i++)
                            {
                                if(Elements[i] == Var)
                                {
                                    Erase(i);
                                    return;
                                }
                            }
                        }
                    void PushBack(const StorageType &Var)
                        {
                            if(Size() == 0) Alloc(ReserveSz);
                            vElements.push_back(Var);
                            return;

                            if(SpacesLeft() == 0) Resize();
                            new (&Elements[Sz]) StorageType(Var);
                            Sz++;
                        }
                    void PushFront(const StorageType &Var)
                        {
                            Insert(0,Var);
                        }
                    void PopBack()
                        {
                            vElements.pop_back();
                            return;
                            Sz--;
                        }
                    void PopFront()
                        {
                            Erase(0);
                        }
                    void operator +=(const StorageType &Var)
                        {
                            PushBack(Var);
                        }
                    StorageType &operator[](SizeType Idx)
                        {
                            return vElements[Idx];
                        }
                    StorageType operator[](SizeType Idx) const
                        {
                            return (vElements[Idx]);
                        }
                    StorageType *Ptr()
                        {
                            return &vElements[0];
                        }
                    StorageType *Ptr() const
                        {
                            return const_cast <char *>(&vElements[0]);
                        }


                protected:
                    void Resize()
                        {
                            SizeType Elems = NextResize + ReserveSz;
                            StorageType *NewElems = (StorageType *)malloc(sizeof(StorageType) * Elems);
                            memset(NewElems,0,Elems * sizeof(StorageType));
                            for(SizeType i = 0;i < Sz;i++) NewElems[i] = Elements[i];

                            if(Elements) free(Elements); //delete Elements; //DON'T USE DELETE[]

                            Elements = NewElems;
                            MemSz = Elems * sizeof(StorageType);
                            NextResize += ReserveSz;
                            ReserveSz *= 2; //Dynamic reserve size (keeps small vectors small in memory while not slowing large vector usage)
                        }
                    SizeType SpacesLeft() const
                        {
                            return NextResize - Sz;
                        }

                    vector <StorageType>vElements;


                    SizeType ReserveSz;
                    StorageType *Elements;
                    SizeType Sz;
                    SizeType MemSz;
                    SizeType NextResize;

            };
    };

#endif
