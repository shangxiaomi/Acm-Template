LinearBasis Merge(LinearBasis A, LinearBasis B)
{ //线性基求交
    LinearBasis All, C, D;
    All.clear();
    C.clear();
    D.clear();
    for (int i = 31; i >= 0; i--)
    { //先把A线性基放入ALL中
        All.basis[i] = A.basis[i];
        D.basis[i] = 1;
        D.basis[i] <<= i;
    }
    for (int i = 31; i >= 0; i--)
    {
        if (B.basis[i])
        { //对每一个B中的线性基试图插入A中，如果能插入，说明这个B中的线性基和A线性无关，如果不能插入，说明线性有关，就是AB的交
            UI v = B.basis[i], k = 0;
            bool can = true;
            for (int j = 31; j >= 0; j--)
            {
                if ((v >> j) & 1)
                { //试图插入过程
                    if (All.basis[j])
                    {
                        v ^= All.basis[j];
                        k ^= D.basis[j];
                    }
                    else
                    {
                        can = false;
                        All.basis[j] = v;
                        D.basis[j] = k;
                        break;
                    }
                }
            }
            if (can)
            { //线性有关，即可插入
                UI v = 0;
                for (int j = 31; j >= 0; j--)
                {
                    if ((k >> j) & 1)
                    {
                        v ^= A.basis[j];
                    }
                }
                C.insert(v);
            }
        }
    }
    C.build(); //生成线性基
    return C;
}