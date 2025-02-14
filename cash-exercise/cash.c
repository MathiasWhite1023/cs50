#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // all the variables that can exist
    int change_owned;
    do
    {
        change_owned = get_int("Change owned: ");
    }
    while(change_owned<0);

    int quotient_division_change_25 = change_owned / 25;
    int remainder_division_change_25 = change_owned % 25;
    int quotient_division_change_10 = remainder_division_change_25 / 10;
    int remainder_division_change_10 = remainder_division_change_25 % 10;
    int quotient_division_change_5 = remainder_division_change_10 / 5;
    int remainder_division_change_5 = remainder_division_change_10 % 5;
    int quotient_division_change_1 = remainder_division_change_5 / 1;

    // if a certain number o change cant be divided by the highest coin, the rest of that divion
    // will go to the nest line and the quocient will be stored int the quotient_division_change_X
    // and the remainder on the variables remainder_division_change_X, on the end of every boolean
    // expression, if its true, the code will add the all the quotient_division_change_X that has
    // been calculated and stored
    if (remainder_division_change_25 == 0)
    {
        printf("%d\n", quotient_division_change_25);
    }
    else if (remainder_division_change_25 > 0)
    {
        remainder_division_change_10 = remainder_division_change_25 % 10;
        if (remainder_division_change_10 == 0)
        {
            quotient_division_change_10 = remainder_division_change_25 / 10;
            printf("%d\n", quotient_division_change_25 + quotient_division_change_10);
        }
        else if (remainder_division_change_10 > 0)
        {
            remainder_division_change_5 = remainder_division_change_10 % 5;
            if (remainder_division_change_5 == 0)
            {
                quotient_division_change_5 = remainder_division_change_10 / 5;
                printf("%d\n", quotient_division_change_25 + quotient_division_change_10 +
                                   quotient_division_change_5);
            }
            else
            {
                quotient_division_change_1 = remainder_division_change_5 / 1;
                printf("%d\n", quotient_division_change_25 + quotient_division_change_10 +
                                   quotient_division_change_5 + quotient_division_change_1);
            }
        }
    }
}
