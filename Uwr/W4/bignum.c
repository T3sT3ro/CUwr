//
// Created by Tooster on 08.11.2017.
//


/**
 * Kod jest skomplikowany, ale działa
 * Jakby był w C++ byłoby o wiele prościej
 * C narzuca ograniczenia np.
 *  - nie można zwrócić z funkcji lokalnej tablicy
 *  - nie ma dobrej kontroli nad wychodzeniem poza pamięć
 *  - nie można przekazać zmiennych jako referencji jak w C++ etc.
 *
 *  Najgorsze z tego wszystkiego jest dzielenie
 */
#include <stdio.h>
#include <stdbool.h>

#define MAX_DIGITS 100
#define MAX_INPUT_DIGITS 30
#define MAX_BUFFER (MAX_INPUT_DIGITS + 2)

struct bignum {
    bool sign; // 0=+ 1=-
    short digits;
    short w[MAX_DIGITS]; //cyfry, liczba przesunięta do końca tablica
};

/// zwraca bignuma z tablicy znaków
/// nie przekazywać jako pierwszy argument pojedńczych charów
struct bignum makeBignum(char *input, short length) {
    // inicjalizacja
    struct bignum ret;
    ret.sign = false; // 1 dla dodatniego, -1 dla ujemnego
    short digits = 0;
    for (int i = 0; i < MAX_DIGITS; ++i)
        ret.w[i] = 0;
    char a[MAX_DIGITS];
    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (i < length)
            a[i] = input[i];
        else
            a[i] = 0;
    }


    // liczenie z ilu cyfr się składa
    for (int i = 0; i < MAX_INPUT_DIGITS + 1; ++i)
        if (a[i] == '-' || (a[i] >= '0' && a[i] <= '9'))
            digits++;
    if (a[0] == '-') {
        ret.sign = true;
        digits--;
    }

    // jeśli liczba ma więcej niż 30 znaków, zwraca pustą tablicę
    if (digits > MAX_INPUT_DIGITS)
        return ret;


    ret.digits = digits;
    // zamienia liczby zapisane jako chary na shorty, czyli '0'->0, '1'->1 itd.
    for (int j = 0 + ret.sign, i = MAX_DIGITS - digits; j < digits + ret.sign; ++j, ++i)
        ret.w[i] = a[j] - '0';

    return ret;
}

/// sprawdza czy |A| < |B| (potrzebne przy odejmowaniu)
bool compareLess(struct bignum A, struct bignum B) {
    if (A.digits != B.digits)
        return A.digits < B.digits;
    for (int i = 0; i < A.digits; ++i) {
        if (A.w[MAX_DIGITS - A.digits + i] != B.w[MAX_DIGITS - A.digits + i])
            return A.w[MAX_DIGITS - A.digits + i] < B.w[MAX_DIGITS - A.digits + i];
    }
    return false;
}

short zliczCyfry(struct bignum A) {
    // zlicza na nowo ilość cyfr
    short digits = MAX_DIGITS;
    for (int j = 0; j < MAX_DIGITS && A.w[j] == 0; ++j)
        digits--;
    return digits;
}

/// dodaje dwa bignumy o takim samym znaku
struct bignum dodaj(struct bignum A, struct bignum B) {

    //inicjalizuje zwracanego bignuma
    struct bignum ret = makeBignum("0", 1);
    //jeśli liczby ujemne, dodaj normalnie i zwróć ze znakiem '-'
    if (A.sign == 1 && B.sign == 1) {
        A.sign = 0;
        B.sign = 0;
        ret.sign = 1;
    }
    // dodawaj od końca z przenoszeniem carry do następnej komórki
    for (int i = MAX_DIGITS - 1; i > 0; --i) {
        ret.w[i] += A.w[i] + B.w[i];
        if (ret.w[i] > 9) {
            ret.w[i] -= 10;
            ret.w[i - 1]++;
        }
    }
    // popraw pole 'digits' bignuma jeśli było przepełnienie
    ret.digits = zliczCyfry(ret);


    return ret;
}

/// odejmuje dwa bignumy o dodatnich znakach
struct bignum odejmij(struct bignum A, struct bignum B) {
    // inicjalizuje zwracanego bignuma
    struct bignum ret = makeBignum("0", 1);
    // jeśli dla a-b, b>a odejmij b-a i ustaw znak na '-', dzięki czemu samo odejmowanie jest zawsze > 0
    if (compareLess(A, B)) {
        ret = odejmij(B, A);
        ret.sign = 1;
        return ret;
    }
    // od tyłu odejmuje i "pożycza" od następnych w razie konieczności
    for (int i = MAX_DIGITS - 1; i > MAX_DIGITS - A.digits - 1; --i) {
        ret.w[i] += A.w[i] - B.w[i];
        if (ret.w[i] < 0) {
            ret.w[i] += 10;
            ret.w[i - 1]--;
        }
    }

    ret.digits = zliczCyfry(ret);

    return ret;
}

/// mnoży dwa bignumy gdzie A > B
struct bignum pomnoz(struct bignum A, struct bignum B) {
    if (compareLess(A, B))
        return pomnoz(B, A);

    struct bignum ret = makeBignum("0", 1);
    // ustawia znak wyniku
    if (A.sign ^ B.sign)
        ret.sign = 1;

    int carry = 0;
    for (int k = 0; k < B.digits; ++k) {
        for (int j = 0; j < A.digits + 1; ++j) { // + 1 żeby dodać jeszcze overflow od carry
            ret.w[MAX_DIGITS - 1 - k - j] +=
                    (carry + B.w[MAX_DIGITS - 1 - k] * A.w[MAX_DIGITS - 1 - j]) % 10;
            carry = (carry + B.w[MAX_DIGITS - 1 - k] * A.w[MAX_DIGITS - 1 - j]) / 10;
        }
    }

    // przepycha złe wyniki dodawania, gdzie ret.w moze wyglądać [0][0][49][71][23]
    for (int i = MAX_DIGITS - 1; i > 0; --i) {
        if (ret.w[i] > 9) {
            ret.w[i - 1] += ret.w[i] / 10;
            ret.w[i] %= 10;
        }
    }

    // zlicza na nowo ilość cyfr
    ret.digits = zliczCyfry(ret);

    return ret;
}

/// zwykłe odejmowanie pisemne, lepiej się nie zagłębiać bo jest pełno zabawy z indeksami itd. !DZIAŁA!
struct bignum podziel(struct bignum A, struct bignum B) {
    if (compareLess(A, B)) // 3 / 100 = 0
        return makeBignum("0", 1);

    struct bignum ret = makeBignum("0", 1);
    // ustawia znak wyniku
    if (A.sign ^ B.sign)
        ret.sign = 1;

    // subA to ta część w dzieleniu pisemnym, dla której sprawdzamy ile razy B się w niej mieści
    struct bignum subA = makeBignum("0", 1);
    subA.sign = 0;
    subA.digits = B.digits - 1;
    for (int i = 0; i < B.digits - 1; ++i)
        subA.w[MAX_DIGITS - B.digits + 1 + i] = A.w[MAX_DIGITS - A.digits + i];

    for (int i = 0; i < A.digits - B.digits + 1; ++i) {
        // ściąga z A kolejną cyfrę (przechodzi poziom niżej w mnożeniu pisemnym)
        subA = pomnoz(subA, makeBignum("10", 2));
        struct bignum nextDigit = makeBignum("1", 1);
        nextDigit.w[MAX_DIGITS - 1] = A.w[MAX_DIGITS - A.digits + B.digits - 1 + i];
        subA = dodaj(subA, nextDigit);

        ret = pomnoz(ret, makeBignum("10", 2));

        // sprawdza ile razy B mieści się w subA
        struct bignum tmp = makeBignum("0", 1);
        short times = 0;
        while (!compareLess(subA, dodaj(tmp, B))) {
            tmp = dodaj(tmp, B);
            times++;
        }
        // dodaje kolejną cyfrę do wyniku
        struct bignum nextRetDigit = makeBignum("1", 1);
        nextRetDigit.w[MAX_DIGITS - 1] = times;
        ret = dodaj(ret, nextRetDigit);
        subA = odejmij(subA, tmp);
    }

    return ret;
}

/// ładnie wypisuje bignuma
void wypisz(struct bignum A) {
    if (A.sign == 1)
        putchar('-');
    for (int i = 0; i < A.digits; ++i)
        putchar(A.w[i + MAX_DIGITS - A.digits] + '0');
}

int main() {
    char A[MAX_BUFFER];
    char B[MAX_BUFFER];
    char op; // char oznaczający operację (+,-)
    for (int i = 0; i < MAX_INPUT_DIGITS + 2; ++i)
        A[i] = B[i] = 0;

    printf("Wpisz maksymalnie trzydziestocyfrowe liczby ze znakiem operacji (+, -, * lub /)\n");
    printf("Wszystkie elementy wpisuj w nowych liniach.\n");

    fgets(A, MAX_BUFFER, stdin);
    scanf("%c ", &op);
    fgets(B, MAX_BUFFER, stdin);

    //stwórz nowe bignumy z wczytanych ciągów znaków
    struct bignum BigA = makeBignum(A, MAX_BUFFER);
    struct bignum BigB = makeBignum(B, MAX_BUFFER);

    putchar('=');
    if (op == '+') {
        if (BigA.sign == 1 && BigB.sign == 0) { // inaczej -a+b = b-a
            BigA.sign = 0;
            BigB.sign = 0;
            wypisz(odejmij(BigB, BigA));
        } else if (BigA.sign == 0 && BigB.sign == 1) { // inaczej a+-b = a-b
            BigA.sign = 0;
            BigB.sign = 0;
            wypisz(odejmij(BigA, BigB));
        } else
            wypisz(dodaj(BigA, BigB)); // dodaj normalnie
    } else if (op == '-') {
        if (BigA.sign == 1 && BigB.sign == 0) { // inaczej -a-b = -(a+b)
            BigA.sign = 1;
            BigB.sign = 1;
            wypisz(dodaj(BigA, BigB));
        } else if (BigA.sign == 0 && BigB.sign == 1) { // inaczej a--b = a+b
            BigA.sign = 0;
            BigB.sign = 0;
            wypisz(dodaj(BigA, BigB));
        } else if (BigA.sign == 1 && BigB.sign == 1) { // inaczej -a--b = -a+b = b-a
            BigA.sign = 0;
            BigB.sign = 0;
            wypisz(odejmij(BigB, BigA));
        } else
            wypisz(odejmij(BigA, BigB)); //  odejmij normalnie
    } else if (op == '*') {
        wypisz(pomnoz(BigA, BigB));
    } else if (op == '/') {
        wypisz(podziel(BigA, BigB));
    }
    putchar('\n');
    return 0;
}