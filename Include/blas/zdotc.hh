#ifndef _zdotc_HH_
#define _zdotc_HH_

#include <CDC8600.hh>

namespace CDC8600
{
    namespace BLAS
    {
        // y = x
        void zdotc    (u64 n, c128 *x, i64 incx, c128 *y, i64 incy, c128 *z);
        void zdotc_cpp(u64 n, c128 *x, i64 incx, c128 *y, i64 incy, c128 *z);
	void zdotc_asm();
    } // namespace BLAS
}; // namespace CDC8600

#endif
