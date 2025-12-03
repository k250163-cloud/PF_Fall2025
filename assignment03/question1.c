#include <stdio.h>
#include <math.h>

float calculateRepayment(float loan, float interestRate, int years, int currentYear, float annualInstallment) {

    if (years <= 0 || loan <= 0) {
        if (loan <= 0) {
            printf("Year %d: Loan isfully paid.......!\n", currentYear - 1);
        } else {
            printf("Year %d: term has fully ended you  remaining loan is = %.2f\n", currentYear, loan);
        }
        return 0;
    }
    float interest = loan * interestRate;
    float totalDue = loan + interest;
    
    float payment = (annualInstallment < totalDue) ? annualInstallment : totalDue;
    float newLoan = totalDue - payment;
    
    printf("Year %d: Remaining loan is = %.2f\n", currentYear, newLoan);
    

    return payment + calculateRepayment(newLoan, interestRate, years - 1, currentYear + 1, annualInstallment);
}


float calculateAnnualInstallment(float initialLoan, float interestRate, int totalYears) {
    if (interestRate == 0) {
        return initialLoan / totalYears; 
    }
    
    // using formual which is P = [L * r * (1+r)^n] / [(1+r)^n - 1]
    float r = interestRate;
    int n = totalYears;
    float numerator = initialLoan * r * pow(1 + r, n);
    float denominator = pow(1 + r, n) - 1;
    
    return numerator / denominator;
}

float calculateRepaymentextra(float loan, float interestRate, int years, int currentYear, 
                                 float annualInstallment, float extraPayment) {
        if (years <= 0 || loan <= 0) {
        if (loan <= 0) {
            printf("Year %d: Loan has been fully paid\n", currentYear - 1);
        } else {
            printf("Year %d: Term has ended.Your Remaining loan is = %.2f\n", currentYear, loan);
        }
        return 0;
    }
    float interest = loan * interestRate;
    float totalDue = loan + interest;
    
    float regularPayment = (annualInstallment < totalDue) ? annualInstallment : totalDue;
    float tempBalance = totalDue - regularPayment;
    
    float actualExtra = 0;
    if (extraPayment > 0 && tempBalance > 0) {
        actualExtra = (extraPayment < tempBalance) ? extraPayment : tempBalance;
        tempBalance -= actualExtra;
    }
    
    float totalPay = regularPayment + actualExtra;
    
    printf("Year %d: Remaining loan = %.2f", currentYear, tempBalance);
    if (extraPayment > 0) {
        printf(" (Extra payment applied: %.2f)", actualExtra);
    }
    printf("\n");
    return totalPay + calculateRepaymentextra(tempBalance, interestRate, years - 1, 
                                                     currentYear + 1, annualInstallment, extraPayment);
}

int main() {
    printf("LOAN REPAYMENT CALCULATION \n");
    
    float startLoan = 100000;
    float interest = 0.05;
    int years = 3;
    
    float annualInstallment = calculateAnnualInstallment(startLoan, interest, years);
    printf("Fixed Annual Installment: %f\n", annualInstallment);
    printf("Basic Recursive Function:\n");
    float total = calculateRepayment(startLoan, interest, years, 1, annualInstallment);
    printf("Total Repayment: %f\n", total);
    
    printf("\nWith Extra Payments:\n");
    float totalextra = calculateRepaymentextra(startLoan, interest, years, 1, 
                                                      annualInstallment, 5000);
    printf("Total Repayment with Extra: %.2f\n", totalextra);
    
    return 0;
}