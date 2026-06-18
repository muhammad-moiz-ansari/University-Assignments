/*
        Your Name: Muhammad Moiz Ansari
        Your Roll#: 23i-0523 
        Your Section: BS(CS)-F

*/

#include<iostream>
#include<cmath>
using namespace std;

// DON'T CHANGE THE PROTOTYPES OF FUNCTION 

//----------------------- Q1 -----------------------

char* BaseConverter(float number, int base)
{
    //Initializations
    float num_temp = fabs(number);
    
    float ftemp,
        dec = 0,
        adec;     //After decimal
    int itemp,
        temp1,
        temp2,
        rem,
        bdec = num_temp,  //Before decimal
        count = 0,
        dec_check = 0,
        adec_l = 0;

    int* arr1 = nullptr;
    int* arr2 = new int[30];

    itemp = bdec;
    adec = num_temp - bdec;

    //---------- Before Decimal ----------
    //Checking number of iterations for multiple division
    while (itemp >= base)
    {
        itemp = itemp / base;
        ++count;
    }
    
    cout << count << endl;

    arr1 = new int[count + 1];

    temp1 = num_temp;

    //Multiple division
    for (int i = count; i >= 0; --i)
    {
        temp2 = temp1 / base;
        rem = temp1 - (temp2 * base);
        arr1[i] = rem;
        temp1 = temp2;
    }

    for (int i = 0; i <= count; ++i)
    {
        cout << arr1[i];
    }
        
    cout << endl;

    //---------- After Decimal ----------
    if (adec != 0)
    {
        dec_check = 1;
        ftemp = adec;

        do
        {
            ftemp = ftemp * base;
            itemp = ftemp;
            arr2[adec_l] = itemp;
            ftemp = ftemp - itemp;

            ++adec_l;
        } while (ftemp != 0 && adec_l < 15);

        for (int j = 0; j < adec_l; ++j)
        {
            cout << arr2[j];
        }
            

    }
    //---------- Negative Numbers ----------
    
    if (number < 0)
    {
        //(r-1)'s Compliment:
        for (int i = count; i >= 0; --i)
        {
            arr1[i] = (base - 1) - arr1[i];
        }

        //r's Compliment:
        for (int i = count; i >= 0; --i)
        {
            arr1[i] += 1;
            if (arr1[i] > (base - 1))
                arr1[i] -= base;
            else
                break;
        }

    }
    //---------- Stringing ----------

    int str_size = (count + 1) + dec_check + adec_l;
    char* str = new char[str_size];

    int j = 0;
    for (int k = 0; k < (count + 1); ++k, ++j)  //Before decimal
    {
        if (base > 10)
        {
            if(arr1[k]>9)
                str[j] = arr1[k] + 55;
            else
                str[j] = arr1[k] + 48;
        }
        else
            str[j] = arr1[k] + 48;
    }
    if (dec_check)  //Decimal point
        str[j++] = '.';
    

    for (int k = 0; k < adec_l; ++k, ++j)   //After decimal
    {
        if (base > 10)
        {
            if (arr2[k] > 9)
                str[j] = arr2[k] + 55;
            else
                str[j] = arr2[k] + 48;
        }
        else
            str[j] = arr2[k] + 48;
    }

    str[j] = '\0';

    cout << endl;
    cout << str;
    return str;
}


//----------------------- Q2 -----------------------

void makeBook(char* text, char***& book, int totalPages)
{
    int totalLines = 10,
        totalChar = 40,
        linech = 0,
        templch = 0,
        charch = 0,
        tempcch = 0,
        pagech=0,
        newpg=0,
        
        pagenum=1,
        linenum=1,
        charnum=0,

        templnum,
        tempcnum,
        itemp;
    bool cch = 0,
         lch = 0,
         pch = 0;
    book = new char** [++totalPages];
    for (int i = 0; i < totalPages; ++i)
    {
        book[i] = new char* [10];
        for (int j = 0; j < 10; ++j)
            book[i][j] = new char[40];
    }
    for (int i = 0; *(text + i) != '\0'; ++i)
    {
        templnum = linenum;
        tempcnum = charnum;
        itemp = i;
        tempcch = 1;
        templch = 1;
        //Temp char check
        for (; !(book[pagenum-1][linenum-1][tempcnum] >= 'a' && book[pagenum-1][linenum-1][tempcnum] <= 'z' || book[pagenum-1][linenum - 1][tempcnum] >= 'A' && book[pagenum - 1][linenum - 1][tempcnum] <= 'Z' || book[pagenum - 1][linenum - 1][tempcnum] == '\''); ++tempcnum, ++itemp)
        {
            book[pagenum-1][linenum-1][tempcnum] = *(text + itemp);
            if (tempcnum > totalChar)
            {
                tempcch = 0;
                break;
            }
        }
        if (tempcch == 0)
        {
            ++templnum;
        }
        if (templnum > totalLines)
        {
            templch = 0;
        }
        if (templch == 0)
        {
            newpg = 1;
        }
        if (newpg == 1)
        {
            //insert(book, totalPages, charnum);
        }

        if (tempcch < totalChar)
            cch = 1;
        if (templch < totalLines)
            lch = 1;
        
       // if (temppch < totalPages)
         //   pch = 1;
        if (lch == 1 && cch == 1 && pch==1)
        {
            book[pagenum][linenum][charnum++] = *(text + i);
        }
    }
}

void cut(char***& book, int totalPages, int FromPage, int ToPage, int FromLine, int ToLine, int FromWord, int ToWord, char*& clipboard)
{
    return;
}

void copy(char***& book, int totalPages, int FromPage, int ToPage, int FromLine, int ToLine, int FromWord, int ToWord, char*& clipboard)
{
    return;
}

void paste(char***& book, int totalPages, char* clipboard, int atPage, int atLine, int afterWord)
{
    return;
}

void Delete(char***& book, int totalPages, int page) // For page deletion
{
    return;
}

void Delete(char***& book, int totalPages, int page, int line) //For line deletion
{
    return;
}

void DeleteText(char***& book, int totalPages, char* text) //For text deletion
{
    return;
}

void insert(char***& book, int totalPages, int position) // insert empty page after position
{
    return;
}

void insert(char***& book, int totalPages, int page, int position) // insert empty line on page
{
    return;
}

void insertText(char***& book, int totalPages, int page, int line, int word, char* text)// Insert text after the word.
{
    return;
}

void removeDoubleSpaces(char***& book, int& totalPages)
{
    return;
}

void concatenateBooks(char***& book1, int totalPages1, char***& book2, int totalPages2, char***& newBook, int& newPages)
{
    return;
}

char* toString(char***& book, int totalPages) //return book with format given below
{
    return '\0';
}


//----------------------- Q3 -----------------------

//Column wise
bool check_cd(int** board, int r, int c, int queens)
{
    if (r < queens)
    {
        if (board[r][c] == 0)
        {
            check_cd(board, ++r, c, queens);
        }
        else
            return false;
    }
    else if (board[r - 1][c] == 1)
        return true;
}
bool check_cu(int** board, int r, int c, int queens)
{
    if (r >= 0)
    {
        if (board[r][c] == 0)
        {
            check_cu(board, --r, c, queens);
        }
        else
            return false;
    }
    else if (board[r + 1][c] == 1)
        return true;
}

//Row wise
bool check_rd(int** board, int r, int c, int queens)
{
    if (c < queens)
    {
        if (board[r][c] == 0)
        {
            check_rd(board, r, ++c, queens);
        }
        else
            return false;
    }
    else if (board[r][c - 1] == 1)
        return true;
}
bool check_ru(int** board, int r, int c, int queens)
{
    if (c >= 0)
    {
        if (board[r][c] == 0)
        {
            check_ru(board, r, --c, queens);
        }
        else
            return false;
    }
    else if (board[r][c + 1] == 1)
        return true;
}

//Diogonal wise
bool check_dd(int** board, int r, int c, int queens)
{
    if (r < queens && c < queens)
    {
        if (board[r][c] == 0)
        {
            check_dd(board, ++r, ++c, queens);
        }
        else
            return false;
    }
    else if (board[r - 1][c - 1] == 1)
        return true;
}
bool check_du(int** board, int r, int c, int queens)
{
    if (r >= 0 && c >= 0)
    {
        if (board[r][c] == 0)
        {
            check_du(board, --r, --c, queens);
        }
        else
            return false;
    }
    else if (board[r + 1][c + 1] == 1)
        return true;
}

//Diogonal-2 wise
bool check_d2d(int** board, int r, int c, int queens)
{
    if (r < queens && c >= 0)
    {
        if (board[r][c] == 0)
        {
            check_d2d(board, ++r, --c, queens);
        }
        else
            return false;
    }
    else if (board[r - 1][c - 1] == 1)
        return true;
}
bool check_d2u(int** board, int r, int c, int queens)
{
    if (r >= 0 && c < queens)
    {
        if (board[r][c] == 0)
        {
            check_d2u(board, --r, ++c, queens);
        }
        else
            return false;
    }
    else if (board[r + 1][c + 1] == 1)
        return true;
}

bool royalHarmony(int**& board, int row, int column, int queens)
{
    if (row == queens || column == queens)
        return true;


    if (check_cu(board, row, column, queens) && check_cd(board, row, column, queens) && check_ru(board, row, column, queens) && check_rd(board, row, column, queens) && check_du(board, row, column, queens) && check_dd(board, row, column, queens) && check_d2u(board, row, column, queens) && check_d2d(board, row, column, queens))
    {
        board[row][column] = 1;

        if (row < queens)
        {
            return royalHarmony(board, row+1, column, queens);
        }

    }
    else
    {
        if (row > queens)
        {
            royalHarmony(board, ++row, column, queens);
        }
        else
        {
            if (column < queens)
            {
                return royalHarmony(board, row, column + 1, queens);
            }
            else if (column > queens)
                return true;
        }

    }
    if (row >= queens)
        return true;
    else
        return false;

}

//----------------------- Q4 -----------------------

//-------- Pattern 1 --------
void sp_st(int i)
{
    if (i > 0)
    {
        if ((i - 1) == 0)
            cout << "*\n";
        else
            cout << " ";
        sp_st(--i);
    }
}

void RecursivePattern1(int start, int end)
{
    int n = start;
    sp_st(start);
    if (start < end / 2)
    {
        start += 1;

        RecursivePattern1(start, end);

        if (end % 2 == 0)
            sp_st(start - 1);
        else
        {
            sp_st(start);
            if (start == 2)
                sp_st(--start);
        }
    }

}

//-------- Pattern 2 --------
void spaces2(int i)
{
    if (i > 0)
    {
        cout << " ";
        spaces2(--i);
    }
}

void stars2(int i, int j)
{
    if (i > 0)
    {
        cout << "*";
        i -= 1;
        stars2(i, j);
    }
}

void RecursivePattern2(int n1, int n2)
{
    if (n1 > 0)
    {
        stars2(n1, n2);
        spaces2(2 * (n2 - n1));
        stars2(n1, n2);
        --n1;

        cout << "\n";
        RecursivePattern2(n1, n2);

        ++n1;
        stars2(n1, n2);
        spaces2(2 * (n2 - n1));
        stars2(n1, n2);
        cout << endl;

    }
}


//-------- Pattern 3 --------
void dot(int i)
{
    if (i > 0)
    {
        cout << ".";
        dot(--i);
    }
}
void stars3(int i)
{
    if (i > 0)
    {
        cout << "*";
        stars3(--i);
    }
}

void spaces3(int i)
{
    if (i > 0)
    {
        if ((i - 1) == 0)
            cout << "#";
        else
            cout << " ";
        spaces3(--i);
    }
}

void RecursivePattern3(int n1, int n2)
{
    if (n1 > 0)
    {
        spaces3(n1);
        dot(n1);
        stars3(2 * (n2 - n1));
        cout << "|";
        stars3(2 * (n2 - n1));
        dot(n1);

        --n1;

        cout << "#\n";
        RecursivePattern3(n1, n2);

        n1 += 2;
        if (n1 <= n2)
        {
            spaces3(n1);
            dot(n1);
        }
        stars3(2 * (n2 - n1));
        if (n1 <= n2)
            cout << "|";
        stars3(2 * (n2 - n1));
        if (n1 <= n2)
        {
            dot(n1);
            cout << "#\n";
        }

    }
}


//----------------------- Q5 -----------------------

struct SavingAccount
{
    char* name;
    float annualInterestRate;
    double savingBalance;
    char* accountNum;
};

void OpenCustomerAccount(SavingAccount* savers[], int& accountsOpen, char* name, float interestRate, double balance) // a function to create a new account and assign it an account number.
{
    

    savers[accountsOpen] = new SavingAccount();
    
    //Name:
    int name_s = 0;
    for (; *(name + name_s) != '\0'; ++name_s)
    {
        ++name_s;
    }
    savers[accountsOpen]->name = new char[name_s+1];
    for (int i = 0; i < (name_s + 1); ++i)
    {
        *(savers[accountsOpen]->name + i) = *(name + i);
        if (i == name_s)
            *(savers[accountsOpen]->name + i) = '\0';
    }

    //Annual Interest Rate:
    savers[accountsOpen]->annualInterestRate = interestRate;

    //Saving Balance:
    savers[accountsOpen]->savingBalance = balance;

    //Account Number:
    savers[accountsOpen]->accountNum = new char[5];

    savers[accountsOpen]->accountNum[0] = 'S';
    savers[accountsOpen]->accountNum[1] = 'A';
    if (accountsOpen < 10)
        savers[accountsOpen]->accountNum[2] = '0';
    else
        savers[accountsOpen]->accountNum[2] = 48 + accountsOpen / 10;

    savers[accountsOpen]->accountNum[3] = 48 + accountsOpen % 10;
    savers[accountsOpen]->accountNum[4] = '\0';

    accountsOpen++;

}

float calculateMonthlyInterest(SavingAccount* saver) // that calculates the monthly interest by multiplying the balance by annualInterestRate divided by 12
{
    return saver->savingBalance * (saver->annualInterestRate / 12);
}

void modifyInterestRate(SavingAccount* saver, float newValue)
{
    saver->annualInterestRate = newValue;
}

int SearchCustomer(SavingAccount* savers[], int accountsOpen, char* accountNum) // a function that searches for an account using an account number. If the customer is found it returns the array index otherwise return -1
{
    if (accountsOpen > 0)
    {
        int name_l = 0;
        for (; *(accountNum + name_l) != '\0'; ++name_l);

        for (int i = 0; i < 100; ++i)
        {
            if ((*(accountNum)-48 < 0) || name_l > 2)
                return -1;
            if (*(savers[i]->accountNum + 2) == *accountNum)
            {
                if (*(savers[i]->accountNum + 3) == *(accountNum + 1))
                    return i;
            }
        }
        return -1;
    }
}

bool UpdateAccountBalance(SavingAccount* savers[], int accountsOpen, char* accountNumVal, double balanceVal) // a function that updates a customer’s balance
{
    int index;
    index=SearchCustomer(savers, accountsOpen, accountNumVal);

    savers[index]->savingBalance = balanceVal;
    return 0;
}