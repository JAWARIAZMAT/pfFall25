#include <stdio.h>

float calculateRepayment(float loan, float interestrate, int years){
	if(loan<=0 || years==0){
		return 0;
	}
    printf("year %d: remaining loan=%f",years,loan);
	printf("\n");
	int newloan=(loan-25000)*(1+interestrate);
    return 25000 + calculateRepayment(newloan,interestrate,years-1);
}

int main(){
	float loan=100000;
	float interestrate=0.05;
	int years=3;
	float ans = calculateRepayment(loan,interestrate,years);
	return 0;
}
