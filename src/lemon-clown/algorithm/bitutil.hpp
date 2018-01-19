namespace BitUtil {
    template<class T> inline T lowbit(T x) { return x&-x; }

    template<class T> inline T bitcounti(T x) {
        x = (x&0x55555555) + ((x>>1)&0x55555555);
        x = (x&0x33333333) + ((x>>2)&0x33333333);
        x = (x&0x0f0f0f0f) + ((x>>4)&0x0f0f0f0f);
        x = (x&0x00ff00ff) + ((x>>8)&0x00ff00ff);
        x = (x&0x0000ffff) + ((x>>16)&0x0000ffff);
        return x;
    }

    template<class T> inline T bitcountl(T x) {
        x = (x&0x5555555555555555LL) + ((x>>1)&0x5555555555555555LL);
        x = (x&0x3333333333333333LL) + ((x>>2)&0x3333333333333333LL);
        x = (x&0x0f0f0f0f0f0f0f0fLL) + ((x>>4)&0x0f0f0f0f0f0f0f0fLL);
        x = (x&0x00ff00ff00ff00ffLL) + ((x>>8)&0x00ff00ff00ff00ffLL);
        x = (x&0x0000ffff0000ffffLL) + ((x>>16)&0x0000ffff0000ffffLL);
        x = (x&0x00000000ffffffffLL) + ((x>>32)&0x00000000ffffffffLL);
        return x;
    }
}
