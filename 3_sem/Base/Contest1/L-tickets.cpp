#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

const int BASE = 1000000000;

class BigInteger {
public:
        BigInteger() {
                bignum = { 0 };
                sign = true;
        }
        BigInteger(int num) {
                if (num >= 0) sign = true;
                else {
                        sign = false;
                        num = -num;
                }
                if (num >= BASE) {
                        bignum = { num % BASE, num / BASE };
                }
                else {
                        bignum = { num };
                }
        }

        void Swap(BigInteger& rhs) {
                std::swap(bignum, rhs.bignum);
                std::swap(sign, rhs.sign);
        }

        BigInteger& operator= (const BigInteger& other) {
                if (*this == other) return *this;
                BigInteger copy = other;
                Swap(copy);
                return *this;
        }

        void delete_zeroes() {
                while (bignum.size() && bignum.back() == 0) {
                        bignum.pop_back();
                }
                if (bignum.empty()) *this = 0;
        }

        bool operator== (const BigInteger& other) const {
                return bignum == other.bignum && sign == other.sign;
        }

        bool operator< (const BigInteger& other) const {
                if (sign != other.sign) {
                        return other.sign;
                }
                if (bignum.size() != other.bignum.size()) {
                        if (sign) {
                                return bignum.size() < other.bignum.size();
                        }
                        return bignum.size() > other.bignum.size();
                }
                size_t ind = bignum.size();
                while (ind-- > 0) {
                        if (bignum[ind] != other.bignum[ind]) {
                                if (sign) {
                                        return bignum[ind] < other.bignum[ind];
                                }
                                return bignum[ind] > other.bignum[ind];
                        }
                        if (!ind) break;
                }
                return false;
        }

        bool operator> (const BigInteger& other) const {
                return other < *this;
        }

        bool operator>= (const BigInteger& other) const {
                return *this == other || other < *this;
        }

        bool operator<= (const BigInteger& other) const {
                return *this == other || *this < other;
        }

        bool operator != (const BigInteger& other) const {
                return !(*this == other);
        }

        BigInteger operator-() const {
                BigInteger copy = *this;
                if (copy == 0) return copy;
                copy.sign = !copy.sign;
                return copy;
        }

        BigInteger abs() const {
                BigInteger copy = *this;
                copy.sign = true;
                return copy;
        }


        BigInteger& operator+= (const BigInteger& other) {
                if (sign == other.sign) {
                        bool carry = 0;
                        for (size_t i = 0; i < std::max(bignum.size(), other.bignum.size()) || carry; ++i) {
                                if (i == bignum.size())
                                        bignum.push_back(0);

                                if (i < other.bignum.size()) {
                                        bignum[i] += carry + other.bignum[i];
                                }
                                else {
                                        bignum[i] += carry;
                                }

                                carry = bignum[i] >= BASE;
                                if (carry)  bignum[i] -= BASE;
                        }
                        return *this;
                }
                BigInteger left = *this;
                BigInteger right = other;
                left.sign = true;
                right.sign = true;
                bool flag = 0;
                if (left < right) {
                        flag = 1;
                        std::swap(left.bignum, right.bignum);
                }

                bool carry = 0;
                for (size_t i = 0; i < right.bignum.size() || carry; ++i) {
                        if (i < right.bignum.size()) {
                                left.bignum[i] -= carry + right.bignum[i];
                        }
                        else {
                                left.bignum[i] -= carry;
                        }

                        carry = left.bignum[i] < 0;
                        if (carry) left.bignum[i] += BASE;
                }
                left.delete_zeroes();
                bignum = left.bignum;
                if (left == 0) sign = 1;
                else sign ^= flag;
                return *this;
        }

        BigInteger& operator-= (const BigInteger& other) {
                *this += -other;
                return *this;
        }

        BigInteger& operator*= (const BigInteger& other) {
                BigInteger result;
                result.bignum.resize(bignum.size() + other.bignum.size());
                for (size_t i = 0; i < bignum.size(); ++i) {
                        long long carry = 0;
                        for (size_t j = 0; j < other.bignum.size() || carry; ++j) {
                                if (i + j >= result.bignum.size()) result.bignum.push_back(0);
                                long long nw = carry + result.bignum[i + j];
                                if (j < other.bignum.size()) {
                                        nw += bignum[i] * 1LL * other.bignum[j];
                                }
                                result.bignum[i + j] = nw % BASE;
                                carry = nw / BASE;
                        }
                }
                result.sign = sign == other.sign;
                result.delete_zeroes();
                *this = result;
                return *this;
        }

        std::string toString() const {
                if (bignum.size() == 0) {
                        return "0";
                }
                std::string ans = "";
                if (!sign) ans.push_back('-');
                ans += std::to_string(bignum.back());
                size_t ind = bignum.size() - 1;
                while (ind-- > 0) {
                        std::string nw = std::to_string(bignum[ind]);
                        for (size_t j = 0; j < 9 - nw.size(); ++j) ans.push_back('0');
                        ans += nw;
                        if (ind == 0) break;
                }
                return ans;
        }

        BigInteger& operator/=(const BigInteger& other) {
                bool bl = sign == other.sign;
                BigInteger lleft, rright;
                if (lleft < rright) {
                        *this = 0;
                        return *this;
                }
                BigInteger result, now;
                size_t ind = bignum.size();
                now += bignum[ind - 1];
                while (ind-- > 0) {
                        int l = 0;
                        int r = BASE;
                        while (l + 1 < r) {
                                int m = (l + r) / 2;
                                BigInteger t = other.abs();
                                t *= m;
                                if (t > now) {
                                        r = m;
                                }
                                else l = m;
                        }
                        BigInteger t = other.abs();
                        t *= l;
                        now -= t;
                        result *= BASE;
                        result += l;
                        if (ind == 0) break;
                        now *= BASE;
                        now += bignum[ind - 1];
                }
                result.sign = bl;
                result.delete_zeroes();
                *this = result;
                return *this;
        }

        explicit operator bool() const {
                return !(bignum.size() == 1 && !bignum[0]);
        }

        BigInteger& operator++() {
                *this += 1;
                return *this;
        }

        BigInteger& operator--() {
                *this -= 1;
                return *this;
        }

        BigInteger operator++(int) {
                BigInteger copy = *this;
                ++(*this);
                return copy;
        }

        BigInteger operator--(int) {
                BigInteger copy = *this;
                --(*this);
                return copy;
        }

        BigInteger& operator%=(const BigInteger& other) {
                BigInteger copy = *this;
                copy /= other;
                copy *= other;
                *this -= copy;
                return *this;
        }


        friend std::istream& operator>> (std::istream& in, BigInteger& num);

private:
        std::vector<int> bignum;
        bool sign;
};

BigInteger operator+ (const BigInteger& l_num, const BigInteger& r_num) {
        BigInteger copy = l_num;
        copy += r_num;
        return copy;
}

BigInteger operator- (const BigInteger& l_num, const BigInteger& r_num) {
        BigInteger copy = l_num;
        copy += -r_num;
        return copy;
}

BigInteger operator* (const BigInteger& l_num, const BigInteger& r_num) {
        BigInteger copy = l_num;
        copy *= r_num;
        return copy;
}

BigInteger operator/ (const BigInteger& l_num, const BigInteger& r_num) {
        BigInteger copy = l_num;
        copy /= r_num;
        return copy;
}

BigInteger operator% (const BigInteger& l_num, const BigInteger& r_num) {
        BigInteger copy = l_num;
        copy %= r_num;
        return copy;
}

BigInteger gcd(BigInteger a, BigInteger b) {
        if (b == 0) return a;
        return gcd(b, a % b);
}

BigInteger big_pow(const BigInteger& left, const BigInteger& right) {
        if (right == 0) return 1;
        if (right == 1) return left;
        BigInteger ans = big_pow(left, (right / 2));
        if (right % 2) return ans * ans * left;
        return ans * ans;
}

std::ostream& operator<< (std::ostream& out, const BigInteger& num)
{
        std::string ans = num.toString();
        out << ans;
        return out;
}

std::istream& operator>>(std::istream& in, BigInteger& num) {
        std::string str;
        in >> str;
        std::vector<int> new_num;
        size_t bl = 0;
        if (str[0] == '-') {
                num.sign = false;
                bl = 1;
        }
        else {
                num.sign = true;
        }
        size_t ind = str.size();
        while (ind > bl) {
                if (ind <= 9 + bl) {
                        new_num.push_back(atoi(str.substr(bl, ind - bl).c_str()));
                        break;
                }
                new_num.push_back(atoi(str.substr(ind - 9, 9).c_str()));
                ind -= 9;
        }
        num.bignum = new_num;
        num.delete_zeroes();
        return in;
}




int main() {
    int M = 0, N = 0;
    std::cin >> N >> M;
    N /= 2;
    int mx_sm = M * N;
    // BigInteger mx_sm(9);
    // mx_sm = mx_sm * BigInteger(N);

    std::vector<std::vector<BigInteger>> nums(N + 2, std::vector<BigInteger>(mx_sm, BigInteger(0)));

    for (int it = 0; it < M; ++it) {
        nums[1][it] = BigInteger(1);
    }

    for (int dig_cnt = 2; dig_cnt <= N; ++dig_cnt) {
        for (int cur_sum = 0; cur_sum <= dig_cnt * (M - 1); ++cur_sum) {
            for (int base_sm = std::max(0, cur_sum - M + 1); base_sm <= cur_sum; ++base_sm) {
                nums[dig_cnt][cur_sum] += nums[dig_cnt - 1][base_sm];
            }
        }
    }
    BigInteger res(0);

    for (int it  = 0; it <= N * (M - 1); ++it) {
        res += nums[N][it] * nums[N][it];
    }

    std::cout << res << "\n";

    // for (int col = 1; col <= N; ++col) {
    //     for (int row = 0; row <= N*(M-1); ++row) {
    //         std::cout  << "\t" << nums[col][row];
    //     }
    //     std::cout << "\n";
    // }
    // for (auto &row : nums) {
    //     for (auto &col : row) {
    //         std::cout << "\t" << col;
    //     }
    //     std::cout << "\n";
    // }

    return 0;
}