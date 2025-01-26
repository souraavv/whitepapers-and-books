package opensource.souravsh;

public class StringHashing {

    /**
     *
     * logic - summation(s[i] * p^i) % mod;
     * == summation (s[i] & p^i % mod) % mod;
     * @param str - Input String
     * @return hashValue of string
     *
     * @note  Using hashing will not be 100% deterministically correct,
     * because two complete different strings might have the same hash
     * (the hashes collide)
     */

    public static long computeHash(String str) {
        final int prime = 31;
        final int mod = 1_000_000_007;

        long hashValue = 0;
        long primePower = 1;

        for (char c: str.toCharArray()) {
            hashValue = (hashValue + (c - 'a' + 1) * primePower) % mod;
            primePower = (primePower * prime) % mod;
        }
        return hashValue;
    }
}
