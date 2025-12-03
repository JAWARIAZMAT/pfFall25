#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
	if(fuel==0) return 0;
	if( planet==totalPlanets) return 1;
	int fuel1;
	if(planet%4==0) fuel1 =fuel+solarBonus-consumption+recharge;
	else fuel1=fuel-consumption+recharge;
	printf("Planet %d: Fuel Remaining = %d",planet,fuel1);
	return calculateFuel(fuel1,consumption,recharge,solarBonus,planet+1,totalPlanets);
}
