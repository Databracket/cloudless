/**
 * @file
 *
 * @section LICENSE
 *
 * Copyright (c) 2012 Databracket, LLC.
 * Copyright (c) 2012 Other contributors as noted in the AUTHORS file
 *
 * This file is part of Cloudless.
 *
 * Cloudless is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cloudless is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * A collection of MODPs for Deffie Hellman based algorithms.
*/

#include <cloudless/crypto/dh_modp.hpp>

namespace cloudless
{

namespace crypto
{

    // MODP_5

    const CryptoPP::Integer MODP_5::p("0x"
            "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd1"
            "29024e088a67cc74020bbea63b139b22514a08798e3404dd"
            "ef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245"
            "e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7ed"
            "ee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3d"
            "c2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f"
            "83655d23dca3ad961c62f356208552bb9ed529077096966d"
            "670c354e4abc9804f1746c08ca237327ffffffffffffffff");
    const CryptoPP::Integer MODP_5::q("0x"
            "7fffffffffffffffe487ed5110b4611a62633145c06e0e68"
            "948127044533e63a0105df531d89cd9128a5043cc71a026e"
            "f7ca8cd9e69d218d98158536f92f8a1ba7f09ab6b6a8e122"
            "f242dabb312f3f637a262174d31bf6b585ffae5b7a035bf6"
            "f71c35fdad44cfd2d74f9208be258ff324943328f6722d9e"
            "e1003e5c50b1df82cc6d241b0e2ae9cd348b1fd47e9267af"
            "c1b2ae91ee51d6cb0e3179ab1042a95dcf6a9483b84b4b36"
            "b3861aa7255e4c0278ba36046511b993ffffffffffffffff");
    const CryptoPP::Integer MODP_5::g("0x2");

    // MODP_14

    const CryptoPP::Integer MODP_14::p("0x"
            "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd1"
            "29024e088a67cc74020bbea63b139b22514a08798e3404dd"
            "ef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245"
            "e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7ed"
            "ee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3d"
            "c2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f"
            "83655d23dca3ad961c62f356208552bb9ed529077096966d"
            "670c354e4abc9804f1746c08ca18217c32905e462e36ce3b"
            "e39e772c180e86039b2783a2ec07a28fb5c55df06f4c52c9"
            "de2bcbf6955817183995497cea956ae515d2261898fa0510"
            "15728e5a8aacaa68ffffffffffffffff");
    const CryptoPP::Integer MODP_14::q("0x"
            "7fffffffffffffffe487ed5110b4611a62633145c06e0e68"
            "948127044533e63a0105df531d89cd9128a5043cc71a026e"
            "f7ca8cd9e69d218d98158536f92f8a1ba7f09ab6b6a8e122"
            "f242dabb312f3f637a262174d31bf6b585ffae5b7a035bf6"
            "f71c35fdad44cfd2d74f9208be258ff324943328f6722d9e"
            "e1003e5c50b1df82cc6d241b0e2ae9cd348b1fd47e9267af"
            "c1b2ae91ee51d6cb0e3179ab1042a95dcf6a9483b84b4b36"
            "b3861aa7255e4c0278ba3604650c10be19482f23171b671d"
            "f1cf3b960c074301cd93c1d17603d147dae2aef837a62964"
            "ef15e5fb4aac0b8c1ccaa4be754ab5728ae9130c4c7d0288"
            "0ab9472d455655347fffffffffffffff");
    const CryptoPP::Integer MODP_14::g("0x2");

    // MODP_15

    const CryptoPP::Integer MODP_15::p("0x"
            "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd1"
            "29024e088a67cc74020bbea63b139b22514a08798e3404dd"
            "ef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245"
            "e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7ed"
            "ee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3d"
            "c2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f"
            "83655d23dca3ad961c62f356208552bb9ed529077096966d"
            "670c354e4abc9804f1746c08ca18217c32905e462e36ce3b"
            "e39e772c180e86039b2783a2ec07a28fb5c55df06f4c52c9"
            "de2bcbf6955817183995497cea956ae515d2261898fa0510"
            "15728e5a8aaac42dad33170d04507a33a85521abdf1cba64"
            "ecfb850458dbef0a8aea71575d060c7db3970f85a6e1e4c7"
            "abf5ae8cdb0933d71e8c94e04a25619dcee3d2261ad2ee6b"
            "f12ffa06d98a0864d87602733ec86a64521f2b18177b200c"
            "bbe117577a615d6c770988c0bad946e208e24fa074e5ab31"
            "43db5bfce0fd108e4b82d120a93ad2caffffffffffffffff");
    const CryptoPP::Integer MODP_15::q("0x"
            "7fffffffffffffffe487ed5110b4611a62633145c06e0e68"
            "948127044533e63a0105df531d89cd9128a5043cc71a026e"
            "f7ca8cd9e69d218d98158536f92f8a1ba7f09ab6b6a8e122"
            "f242dabb312f3f637a262174d31bf6b585ffae5b7a035bf6"
            "f71c35fdad44cfd2d74f9208be258ff324943328f6722d9e"
            "e1003e5c50b1df82cc6d241b0e2ae9cd348b1fd47e9267af"
            "c1b2ae91ee51d6cb0e3179ab1042a95dcf6a9483b84b4b36"
            "b3861aa7255e4c0278ba3604650c10be19482f23171b671d"
            "f1cf3b960c074301cd93c1d17603d147dae2aef837a62964"
            "ef15e5fb4aac0b8c1ccaa4be754ab5728ae9130c4c7d0288"
            "0ab9472d45556216d6998b8682283d19d42a90d5ef8e5d32"
            "767dc2822c6df785457538abae83063ed9cb87c2d370f263"
            "d5fad7466d8499eb8f464a702512b0cee771e9130d697735"
            "f897fd036cc504326c3b01399f643532290f958c0bbd9006"
            "5df08babbd30aeb63b84c4605d6ca371047127d03a72d598"
            "a1edadfe707e884725c16890549d69657fffffffffffffff");
    const CryptoPP::Integer MODP_15::g("0x2");

    // MODP_16

    const CryptoPP::Integer MODP_16::p("0x"
            "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd1"
            "29024e088a67cc74020bbea63b139b22514a08798e3404dd"
            "ef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245"
            "e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7ed"
            "ee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3d"
            "c2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f"
            "83655d23dca3ad961c62f356208552bb9ed529077096966d"
            "670c354e4abc9804f1746c08ca18217c32905e462e36ce3b"
            "e39e772c180e86039b2783a2ec07a28fb5c55df06f4c52c9"
            "de2bcbf6955817183995497cea956ae515d2261898fa0510"
            "15728e5a8aaac42dad33170d04507a33a85521abdf1cba64"
            "ecfb850458dbef0a8aea71575d060c7db3970f85a6e1e4c7"
            "abf5ae8cdb0933d71e8c94e04a25619dcee3d2261ad2ee6b"
            "f12ffa06d98a0864d87602733ec86a64521f2b18177b200c"
            "bbe117577a615d6c770988c0bad946e208e24fa074e5ab31"
            "43db5bfce0fd108e4b82d120a92108011a723c12a787e6d7"
            "88719a10bdba5b2699c327186af4e23c1a946834b6150bda"
            "2583e9ca2ad44ce8dbbbc2db04de8ef92e8efc141fbecaa6"
            "287c59474e6bc05d99b2964fa090c3a2233ba186515be7ed"
            "1f612970cee2d7afb81bdd762170481cd0069127d5b05aa9"
            "93b4ea988d8fddc186ffb7dc90a6c08f4df435c934063199"
            "ffffffffffffffff");
    const CryptoPP::Integer MODP_16::q("0x"
            "7fffffffffffffffe487ed5110b4611a62633145c06e0e68"
            "948127044533e63a0105df531d89cd9128a5043cc71a026e"
            "f7ca8cd9e69d218d98158536f92f8a1ba7f09ab6b6a8e122"
            "f242dabb312f3f637a262174d31bf6b585ffae5b7a035bf6"
            "f71c35fdad44cfd2d74f9208be258ff324943328f6722d9e"
            "e1003e5c50b1df82cc6d241b0e2ae9cd348b1fd47e9267af"
            "c1b2ae91ee51d6cb0e3179ab1042a95dcf6a9483b84b4b36"
            "b3861aa7255e4c0278ba3604650c10be19482f23171b671d"
            "f1cf3b960c074301cd93c1d17603d147dae2aef837a62964"
            "ef15e5fb4aac0b8c1ccaa4be754ab5728ae9130c4c7d0288"
            "0ab9472d45556216d6998b8682283d19d42a90d5ef8e5d32"
            "767dc2822c6df785457538abae83063ed9cb87c2d370f263"
            "d5fad7466d8499eb8f464a702512b0cee771e9130d697735"
            "f897fd036cc504326c3b01399f643532290f958c0bbd9006"
            "5df08babbd30aeb63b84c4605d6ca371047127d03a72d598"
            "a1edadfe707e884725c16890549084008d391e0953c3f36b"
            "c438cd085edd2d934ce1938c357a711e0d4a341a5b0a85ed"
            "12c1f4e5156a26746ddde16d826f477c97477e0a0fdf6553"
            "143e2ca3a735e02eccd94b27d04861d1119dd0c328adf3f6"
            "8fb094b867716bd7dc0deebb10b8240e68034893ead82d54"
            "c9da754c46c7eee0c37fdbee48536047a6fa1ae49a0318cc"
            "ffffffffffffffff");
    const CryptoPP::Integer MODP_16::g("0x2");

    // MODP_17

    const CryptoPP::Integer MODP_17::p("0x"
            "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd1"
            "29024e088a67cc74020bbea63b139b22514a08798e3404dd"
            "ef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245"
            "e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7ed"
            "ee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3d"
            "c2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f"
            "83655d23dca3ad961c62f356208552bb9ed529077096966d"
            "670c354e4abc9804f1746c08ca18217c32905e462e36ce3b"
            "e39e772c180e86039b2783a2ec07a28fb5c55df06f4c52c9"
            "de2bcbf6955817183995497cea956ae515d2261898fa0510"
            "15728e5a8aaac42dad33170d04507a33a85521abdf1cba64"
            "ecfb850458dbef0a8aea71575d060c7db3970f85a6e1e4c7"
            "abf5ae8cdb0933d71e8c94e04a25619dcee3d2261ad2ee6b"
            "f12ffa06d98a0864d87602733ec86a64521f2b18177b200c"
            "bbe117577a615d6c770988c0bad946e208e24fa074e5ab31"
            "43db5bfce0fd108e4b82d120a92108011a723c12a787e6d7"
            "88719a10bdba5b2699c327186af4e23c1a946834b6150bda"
            "2583e9ca2ad44ce8dbbbc2db04de8ef92e8efc141fbecaa6"
            "287c59474e6bc05d99b2964fa090c3a2233ba186515be7ed"
            "1f612970cee2d7afb81bdd762170481cd0069127d5b05aa9"
            "93b4ea988d8fddc186ffb7dc90a6c08f4df435c934028492"
            "36c3fab4d27c7026c1d4dcb2602646dec9751e763dba37bd"
            "f8ff9406ad9e530ee5db382f413001aeb06a53ed9027d831"
            "179727b0865a8918da3edbebcf9b14ed44ce6cbaced4bb1b"
            "db7f1447e6cc254b332051512bd7af426fb8f401378cd2bf"
            "5983ca01c64b92ecf032ea15d1721d03f482d7ce6e74fef6"
            "d55e702f46980c82b5a84031900b1c9e59e7c97fbec7e8f3"
            "23a97a7e36cc88be0f1d45b7ff585ac54bd407b22b4154aa"
            "cc8f6d7ebf48e1d814cc5ed20f8037e0a79715eef29be328"
            "06a1d58bb7c5da76f550aa3d8a1fbff0eb19ccb1a313d55c"
            "da56c9ec2ef29632387fe8d76e3c0468043e8f663f4860ee"
            "12bf2d5b0b7474d6e694f91e6dcc4024ffffffffffffffff");
    const CryptoPP::Integer MODP_17::q("0x"
            "7fffffffffffffffe487ed5110b4611a62633145c06e0e68"
            "948127044533e63a0105df531d89cd9128a5043cc71a026e"
            "f7ca8cd9e69d218d98158536f92f8a1ba7f09ab6b6a8e122"
            "f242dabb312f3f637a262174d31bf6b585ffae5b7a035bf6"
            "f71c35fdad44cfd2d74f9208be258ff324943328f6722d9e"
            "e1003e5c50b1df82cc6d241b0e2ae9cd348b1fd47e9267af"
            "c1b2ae91ee51d6cb0e3179ab1042a95dcf6a9483b84b4b36"
            "b3861aa7255e4c0278ba3604650c10be19482f23171b671d"
            "f1cf3b960c074301cd93c1d17603d147dae2aef837a62964"
            "ef15e5fb4aac0b8c1ccaa4be754ab5728ae9130c4c7d0288"
            "0ab9472d45556216d6998b8682283d19d42a90d5ef8e5d32"
            "767dc2822c6df785457538abae83063ed9cb87c2d370f263"
            "d5fad7466d8499eb8f464a702512b0cee771e9130d697735"
            "f897fd036cc504326c3b01399f643532290f958c0bbd9006"
            "5df08babbd30aeb63b84c4605d6ca371047127d03a72d598"
            "a1edadfe707e884725c16890549084008d391e0953c3f36b"
            "c438cd085edd2d934ce1938c357a711e0d4a341a5b0a85ed"
            "12c1f4e5156a26746ddde16d826f477c97477e0a0fdf6553"
            "143e2ca3a735e02eccd94b27d04861d1119dd0c328adf3f6"
            "8fb094b867716bd7dc0deebb10b8240e68034893ead82d54"
            "c9da754c46c7eee0c37fdbee48536047a6fa1ae49a014249"
            "1b61fd5a693e381360ea6e593013236f64ba8f3b1edd1bde"
            "fc7fca0356cf298772ed9c17a09800d7583529f6c813ec18"
            "8bcb93d8432d448c6d1f6df5e7cd8a76a267365d676a5d8d"
            "edbf8a23f36612a5999028a895ebd7a137dc7a009bc6695f"
            "acc1e500e325c9767819750ae8b90e81fa416be7373a7f7b"
            "6aaf3817a34c06415ad42018c8058e4f2cf3e4bfdf63f479"
            "91d4bd3f1b66445f078ea2dbffac2d62a5ea03d915a0aa55"
            "6647b6bf5fa470ec0a662f6907c01bf053cb8af7794df194"
            "0350eac5dbe2ed3b7aa8551ec50fdff8758ce658d189eaae"
            "6d2b64f617794b191c3ff46bb71e0234021f47b31fa43077"
            "095f96ad85ba3a6b734a7c8f36e620127fffffffffffffff");
    const CryptoPP::Integer MODP_17::g("0x2");

    // MODP_18

    const CryptoPP::Integer MODP_18::p("0x"
            "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd1"
            "29024e088a67cc74020bbea63b139b22514a08798e3404dd"
            "ef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245"
            "e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7ed"
            "ee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3d"
            "c2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f"
            "83655d23dca3ad961c62f356208552bb9ed529077096966d"
            "670c354e4abc9804f1746c08ca18217c32905e462e36ce3b"
            "e39e772c180e86039b2783a2ec07a28fb5c55df06f4c52c9"
            "de2bcbf6955817183995497cea956ae515d2261898fa0510"
            "15728e5a8aaac42dad33170d04507a33a85521abdf1cba64"
            "ecfb850458dbef0a8aea71575d060c7db3970f85a6e1e4c7"
            "abf5ae8cdb0933d71e8c94e04a25619dcee3d2261ad2ee6b"
            "f12ffa06d98a0864d87602733ec86a64521f2b18177b200c"
            "bbe117577a615d6c770988c0bad946e208e24fa074e5ab31"
            "43db5bfce0fd108e4b82d120a92108011a723c12a787e6d7"
            "88719a10bdba5b2699c327186af4e23c1a946834b6150bda"
            "2583e9ca2ad44ce8dbbbc2db04de8ef92e8efc141fbecaa6"
            "287c59474e6bc05d99b2964fa090c3a2233ba186515be7ed"
            "1f612970cee2d7afb81bdd762170481cd0069127d5b05aa9"
            "93b4ea988d8fddc186ffb7dc90a6c08f4df435c934028492"
            "36c3fab4d27c7026c1d4dcb2602646dec9751e763dba37bd"
            "f8ff9406ad9e530ee5db382f413001aeb06a53ed9027d831"
            "179727b0865a8918da3edbebcf9b14ed44ce6cbaced4bb1b"
            "db7f1447e6cc254b332051512bd7af426fb8f401378cd2bf"
            "5983ca01c64b92ecf032ea15d1721d03f482d7ce6e74fef6"
            "d55e702f46980c82b5a84031900b1c9e59e7c97fbec7e8f3"
            "23a97a7e36cc88be0f1d45b7ff585ac54bd407b22b4154aa"
            "cc8f6d7ebf48e1d814cc5ed20f8037e0a79715eef29be328"
            "06a1d58bb7c5da76f550aa3d8a1fbff0eb19ccb1a313d55c"
            "da56c9ec2ef29632387fe8d76e3c0468043e8f663f4860ee"
            "12bf2d5b0b7474d6e694f91e6dbe115974a3926f12fee5e4"
            "38777cb6a932df8cd8bec4d073b931ba3bc832b68d9dd300"
            "741fa7bf8afc47ed2576f6936ba424663aab639c5ae4f568"
            "3423b4742bf1c978238f16cbe39d652de3fdb8befc848ad9"
            "22222e04a4037c0713eb57a81a23f0c73473fc646cea306b"
            "4bcbc8862f8385ddfa9d4b7fa2c087e879683303ed5bdd3a"
            "062b3cf5b3a278a66d2a13f83f44f82ddf310ee074ab6a36"
            "4597e899a0255dc164f31cc50846851df9ab48195ded7ea1"
            "b1d510bd7ee74d73faf36bc31ecfa268359046f4eb879f92"
            "4009438b481c6cd7889a002ed5ee382bc9190da6fc026e47"
            "9558e4475677e9aa9e3050e2765694dfc81f56e880b96e71"
            "60c980dd98edd3dfffffffffffffffff");
    const CryptoPP::Integer MODP_18::q("0x"
            "7fffffffffffffffe487ed5110b4611a62633145c06e0e68"
            "948127044533e63a0105df531d89cd9128a5043cc71a026e"
            "f7ca8cd9e69d218d98158536f92f8a1ba7f09ab6b6a8e122"
            "f242dabb312f3f637a262174d31bf6b585ffae5b7a035bf6"
            "f71c35fdad44cfd2d74f9208be258ff324943328f6722d9e"
            "e1003e5c50b1df82cc6d241b0e2ae9cd348b1fd47e9267af"
            "c1b2ae91ee51d6cb0e3179ab1042a95dcf6a9483b84b4b36"
            "b3861aa7255e4c0278ba3604650c10be19482f23171b671d"
            "f1cf3b960c074301cd93c1d17603d147dae2aef837a62964"
            "ef15e5fb4aac0b8c1ccaa4be754ab5728ae9130c4c7d0288"
            "0ab9472d45556216d6998b8682283d19d42a90d5ef8e5d32"
            "767dc2822c6df785457538abae83063ed9cb87c2d370f263"
            "d5fad7466d8499eb8f464a702512b0cee771e9130d697735"
            "f897fd036cc504326c3b01399f643532290f958c0bbd9006"
            "5df08babbd30aeb63b84c4605d6ca371047127d03a72d598"
            "a1edadfe707e884725c16890549084008d391e0953c3f36b"
            "c438cd085edd2d934ce1938c357a711e0d4a341a5b0a85ed"
            "12c1f4e5156a26746ddde16d826f477c97477e0a0fdf6553"
            "143e2ca3a735e02eccd94b27d04861d1119dd0c328adf3f6"
            "8fb094b867716bd7dc0deebb10b8240e68034893ead82d54"
            "c9da754c46c7eee0c37fdbee48536047a6fa1ae49a014249"
            "1b61fd5a693e381360ea6e593013236f64ba8f3b1edd1bde"
            "fc7fca0356cf298772ed9c17a09800d7583529f6c813ec18"
            "8bcb93d8432d448c6d1f6df5e7cd8a76a267365d676a5d8d"
            "edbf8a23f36612a5999028a895ebd7a137dc7a009bc6695f"
            "acc1e500e325c9767819750ae8b90e81fa416be7373a7f7b"
            "6aaf3817a34c06415ad42018c8058e4f2cf3e4bfdf63f479"
            "91d4bd3f1b66445f078ea2dbffac2d62a5ea03d915a0aa55"
            "6647b6bf5fa470ec0a662f6907c01bf053cb8af7794df194"
            "0350eac5dbe2ed3b7aa8551ec50fdff8758ce658d189eaae"
            "6d2b64f617794b191c3ff46bb71e0234021f47b31fa43077"
            "095f96ad85ba3a6b734a7c8f36df08acba51c937897f72f2"
            "1c3bbe5b54996fc66c5f626839dc98dd1de4195b46cee980"
            "3a0fd3dfc57e23f692bb7b49b5d212331d55b1ce2d727ab4"
            "1a11da3a15f8e4bc11c78b65f1ceb296f1fedc5f7e42456c"
            "911117025201be0389f5abd40d11f8639a39fe3236751835"
            "a5e5e44317c1c2eefd4ea5bfd16043f43cb41981f6adee9d"
            "03159e7ad9d13c53369509fc1fa27c16ef9887703a55b51b"
            "22cbf44cd012aee0b2798e628423428efcd5a40caef6bf50"
            "d8ea885ebf73a6b9fd79b5e18f67d1341ac8237a75c3cfc9"
            "2004a1c5a40e366bc44d00176af71c15e48c86d37e013723"
            "caac7223ab3bf4d54f1828713b2b4a6fe40fab74405cb738"
            "b064c06ecc76e9efffffffffffffffff");
    const CryptoPP::Integer MODP_18::g("0x2");

} // namespace crypto

} // namespace cloudless
