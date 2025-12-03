#include <stdio.h>
void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    int leftFuel;
    int currentPlanet = planet;
    if (currentPlanet > totalPlanets) {
        printf("journey is  completed\n");
        printf("The spacecraft successfully visited all %d planets.\n", totalPlanets);
        return;
    }
	int remainingfuel=fuel - consumption;
    leftFuel = remainingfuel  + recharge;

    if (currentPlanet % 4 == 0) {
        leftFuel += solarBonus;
        printf("solar charge add by bonue of %d added at Planet %d\n", solarBonus, currentPlanet);
    }

    if (leftFuel <0||leftFuel== 0) {
        printf("planet %d: fuel Remaining = 0\n", currentPlanet);
        printf("journey fialed or unsucceful\n");
        printf("Fuel was exhausted after Planet %d. The spacecraft is unable to complete the journey.\n", currentPlanet);
        return;
    }
   printf("Planet %d: Fuel Remaining = %d\n", currentPlanet, leftFuel);


    calculateFuel(leftFuel, consumption, recharge, solarBonus, currentPlanet + 1, totalPlanets);
}

int main() {
    int initial_fuel = 50;
    int consumption = 10;
    int recharge = 2;
    int bonus = 15;
    int total_planets = 7;

    printf("Spacecraft Simulation\n");
    printf("Initial Fuel: %d\n", initial_fuel);
    printf("consumption on  each stop= %d, recharge on each  stop= %d, solar bonus(after 4 ) %d\n", 
           consumption, recharge, bonus);
    printf("planets that will be visited= %d\n", total_planets);

    calculateFuel(initial_fuel, consumption, recharge, bonus, 1, total_planets);

    return 0;
}