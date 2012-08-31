// A wrapper around Crypto++'s eccrypto.h that includes FHMQV.

#ifndef __CLOUDLESS_ECCRYPTO_H
#define __CLOUDLESS_ECCRYPTO_H

#include <cryptopp/eccrypto.h>

#ifndef CRYPTOPP_FHMQV_H
#include "fhmqv.h"

namespace CryptoPP
{

    //! Fully Hashed Menezes-Qu-Vanstone in GF(p) with key validation,
    /*! <a href="http://eprint.iacr.org/2009/408">A Secure and Efficient Authenticated DiffieHellman Protocol</a>
        Note: this is FHMQV, Protocol 5, from page 11; and not FHMQV-C.
    */
    template <class EC, class COFACTOR_OPTION = CPP_TYPENAME DL_GroupParameters_EC<EC>::DefaultCofactorOption, class HASH = SHA256>
    struct FHMQV
    {
        typedef FHMQV_Domain<DL_GroupParameters_EC<EC>, COFACTOR_OPTION, HASH> Domain;
    };

} // namespace CryptoPP

#endif // CRYPTOPP_FHMQV_H

#endif // __CLOUDLESS_ECRYPTO_H
