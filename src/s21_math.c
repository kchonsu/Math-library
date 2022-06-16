#include "s21_math.h"

long double s21_tan(double x) {
    return (s21_sin(x)/s21_cos(x));
}

long double s21_sqrt(double x) {
    long double result = 1;
    if (x < 0) {
        result = s21_NAN;
    } else {
        double arg = 0;
        for (; s21_fabs(result - arg) > s21_EPS; ) {
            arg = result;
            result = 0.5 * (arg +x/arg);
        }
    }
    return result;
}

long double s21_sin(double x) {
    if (x > 2 * s21_PI || x < -2 * s21_PI) x = s21_fmod(x, 2 * s21_PI);
    long double result = 0;
    double arg = x;
    for (long int count =1; s21_fabs(arg) > s21_EPS; count++) {
        result += arg;
        arg = -1 * arg * x * x / ((2 * count) * (2 * count + 1));
    }
    return result;
}

long double s21_pow(double base, double i) {
    long double result;
    int flag = 0;
    int check = 0;
    if (base < 0) {
        if (s21_floor(i) - i == 0) {
            base = s21_abs(base);
            if ((int)i % 2 != 0) check = 1;
        } else {
            result = s21_NAN;
            flag = 1;
        }
    }
    if (i == -s21_INF)  {
        if (base != -1 && base != 1) result = 0;
        else
            result = 1;
    } else if (i == s21_INF) {
        if (base == -1 || base == 1) result = 1;
        else if (base < -1) result = s21_INF;
        else
            result = 0;
    } else if (flag != 1) {
        result = s21_exp(i * s21_log(base));
    }
    if (check == 1) result = -result;
    return result;
}

long double s21_log(double x) {
    long double result = 0;
    long double arg = x - 1;
    if (x > 0 && x < 2) {
        for (long int count = 1; s21_fabs(arg) > s21_EPS; count++) {
            result += arg;
            arg = -1 * arg * (x - 1) * count / (count + 1);
        }
    } else  if (x >= 2) {
        arg = (x - 1) / x;
        for (long int count = 1 ; s21_fabs(arg) > s21_EPS; count++) {
            result += arg;
            arg = arg * count * (x - 1) / ((count + 1) * x);
        }
    } else if (x == 0) {
        result = -s21_INF;
    } else if (x < 0) {
        result = s21_NAN;
    }
    return result;
}

long double s21_fmod(double x, double y) {
    double count = 1;
    double y2 = 0;
    double result = 0;
    while (y2 <= s21_fabs(x)) {
        y2 = s21_fabs(y);
        y2 *= count;
        count++;
    }
    result = s21_fabs(x)-(s21_fabs(y) * (count - 2));
    if (s21_fabs(x) < s21_fabs(y)) result = x;
    if (x < 0) result = -result;
    return (y != 0) ? result : s21_NAN;
}

long double s21_floor(double x) {
    long long int y = x;
    return ((double)y > x) ? y - 1 : y;
}

int s21_abs(int x) {
    return (x < 0) ? x *= -1 : x;
}

long double s21_exp(double x) {
    int flag = 0;
    if (x < 0) x *= -1, flag = 1;
    long double result = 1;
    double arg = x;
    for (long int count =1 ; s21_fabs(arg) > s21_EPS && result < s21_MAX_double; count++) {
        result += arg;
        arg = arg * x /(count+1);
    }
    if (flag == 1) {
        result = result > s21_MAX_double ? 0 : 1./result;
    }
    return result > s21_MAX_double ? s21_INF : result;
}

long double s21_cos(double x) {
    if (x > 2 * s21_PI || x < -2 * s21_PI) x = s21_fmod(x, 2 * s21_PI);
    return (s21_sin(s21_PI/2 - x));
}

long double s21_ceil(double x) {
    long long int y = x;
    return ((double)y < x) ? y + 1 : y;
}

long double s21_arctan(double x) {
    long double result = 0;
    double arg = x;
    for (long int count = 1; s21_fabs(arg) > s21_EPS; count++) {
        result += arg;
        arg = -1* arg * x * x * (2 * count - 1)/(2 * count + 1);
    }
    return result;
}

long double s21_atan(double x) {
    long double result = 0;
    if (x == 1 || x == -1 || x == 0) {
        result = (x == 0) ? 0 : (x == 1) ? s21_PI/4: -s21_PI/4;
    } else if (x > 1 || x < -1) {
        result = x > 1 ? s21_PI / 2 - s21_arctan(1 / x) : -s21_PI / 2 -  s21_arctan(1 / x);
    } else {
        result = s21_arctan(x);
    }
    return result;
}

long double s21_asin(double x) {
    long double result = 0;
    if (x > 1 || x < -1) {
            result = s21_NAN;
    } else if (x == -1 || x == 1) {
        result = s21_PI / 2 * x;
    } else {
        double arg = x;
        for (long int count = 1; s21_fabs(arg) > s21_EPS; count++) {
            result += arg;
            arg = arg * x * x * (2 * count - 1)* (2 * count - 1)/(2 * count * (2 * count + 1));
        }
    }
    return result;
}

long double s21_acos(double x) {
    return (s21_PI/2. - s21_asin(x));
}

long double s21_fabs(double x) {
    return (x < 0) ? x *= -1 : x;
}
