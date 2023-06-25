#include <iostream>
#include "cmath"
#include <vector>
#include <deque>
#include <iomanip>

double const elevation = 3659; // Enter elevation of the airport
double const rwyhead = 212; // enter runway bearing
double const cruhead = 81; // enter cruise heading
double const winddirection = 240; // wind blowing FROM
double const windspeed = 28; // enter knots
double const payload = 125000; // pounds
char const direction = 'E'; // which way are we headed?
double const distance = 617;
double const localt = 2500;
double const desdistance = 94; // 400 = 120nm, 390 = 117nm, 380 = 114nm, 370 = 111nm, 360 = 108nm, 350 = 105nm, 340 = 102nm, 330 = 99nm, 320 = 96nm, 310 = 93nm, 300 = 90nm, 290 = 87nm, 280 = 84nm
double const runwaylength = 10502; // departure runway
double const runwaycondition = 'D'; // D for Dry, W for Wet


// not usually modified
int const lapserate = 1000.0;
double const temp = 59; // Enter temp in F here
double const taxifuel = 4000; // 2000 each


// you don't need a weatherman to know which way the wind blows 
std::tuple<double, double, double> wind(double heading) {

double component = 0;
double headwind = 0;
double tailwind = 0;

int diff = std::abs(heading - winddirection);

int remainder = diff % 5;
    if (diff == 0 || diff == 1) {
      diff = diff;
    } else if (remainder == 0) {
        diff = diff;
    } else {
        diff += 5 - remainder;
      }

  std::vector<int> angles = {0, 1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200, 205, 210, 215, 220, 225, 230, 235, 240, 245, 250, 255, 260, 265, 270, 275, 280, 285, 290, 295, 300, 305, 310, 315, 320, 325, 330, 335, 340, 345, 350, 355};
  std::vector<double> sine = {0.0, 0.017, 0.087, 0.17, 0.25, 0.34, 0.42, 0.5, 0.57, 0.64, 0.70, 0.75, 0.81, 0.86, 0.90, 0.94, 0.96, 0.98, 0.99, 1.00, 0.99, 0.98, 0.96, 0.94, 0.90, 0.86, 0.81, 0.75, 0.70, 0.64, 0.57, 0.5, 0.42, 0.34, 0.25, 0.17, 0.087, 0.0, 0.087, 0.17, 0.25, 0.34, 0.42, 0.5, 0.57, 0.64, 0.70, 0.75, 0.81, 0.86, 0.90, 0.94, 0.96, 0.98, 0.99, 1.00, 0.99, 0.98, 0.96, 0.94, 0.90, 0.86, 0.81, 0.75, 0.70, 0.64, 0.57, 0.5, 0.42, 0.34, 0.25, 0.17, 0.087};

  for (int i = 0; i < angles.size(); i++)
    if (diff == angles[i]) {
      component = windspeed * sine[i];
      
        }

if (diff >= 0 && diff <= 90 || diff >= 270 && diff <= 359) {
  headwind = windspeed - component;
  } else if (diff >= 90 && diff <= 270) {
    tailwind = windspeed - component;
    } else {
    std::cout << "Error0101: Invalid takeoff heading and/or wind directions parameters.\n";
  }

return std::make_tuple(component, headwind, tailwind);

    }


// here we go
int main() {

// crosscheck
  if (elevation < 0 || elevation > 20000) {
    std::cout << "Error001: Elevation out of range\n";
      exit(1); 
} if (rwyhead < 0 || rwyhead > 360) {
    std::cout << "Error002: Runway Heading out of range\n";
      exit(1); 
} if (cruhead < 0 || cruhead > 360) {
    std::cout << "Error002C: Cruise Heading out of range\n";
      exit(1);     
} if (winddirection < 0 || winddirection > 360) {
    std::cout << "Error003: Wind Direction out of range\n";
      exit(1);
} if (windspeed < 0 || windspeed > 40) {
    std::cout << "Error004: Wind Speed out of manufacturer range\n";
      exit(1);
} if (payload < 0 || payload > 225000) {
    std::cout << "Error005: Payload out of manufacturer range\n";
      exit(1);
} if (direction != 'W' && direction != 'w' && direction != 'E' && direction != 'e') {
    std::cout << "Error006: Invalid direction. Enter 'W' for West or 'E' for East\n";
      exit(1);
} if (distance < 0 || distance > 7511) {
    std::cout << "Error007: Distance out of range\n";
      exit(1);
} if (localt < 0 || localt > 15000) {
    std::cout << "Error009: LOC Altitude out of range\n";
      exit(1);
} if (desdistance < 0 || desdistance > 200) {
    std::cout << "Error010: Descent Distance out of range\n";
      exit(1);
} if (runwaylength < 6000 || runwaylength > 20000) {
    std::cout << "Error011: Runway Length out of range\n";
      exit(1);
} if (lapserate != 1000) {
    std::cout << "Error012: Invalid Lapse Rate\n";
      exit(1);
} if (temp < -20 || temp > 200) {
    std::cout << "Error013: Temperature (F) out of range\n";
      exit(1);
} if (taxifuel < 0 || taxifuel > 10000) {
    std::cout << "Error014: Taxi Fuel out of range\n";
      exit(1);
} if (runwaycondition != 'W' && runwaycondition != 'D') {
    std::cout << "Error017: Invalid Runway Condition. Enter 'D' if dry and 'W' if wet\n";
      exit(1);
}

std::cout << "* Speed Unit: Knots  /  Weight Unit: Pounds  /  Fuel Unit: Pounds *\n";

// what altitude is it gon' freeze?
double freezelevel; // The altitude at which the air is expected to be 32 degrees
int surftemp = (temp - 32.0) * (5.0 / 9.0); // Celsius
double subamount = 0; 

subamount = surftemp / 2.0;
  
freezelevel = (subamount * lapserate) + elevation;
  
std::cout << "Freeze Level: " << freezelevel << " ft\n";


// here's the way the wind blows
double rwycomponent = 0;
double rwyheadwind = 0; 
double rwytailwind = 0;
double crucomponent = 0; 
double cruheadwind = 0; 
double crutailwind = 0;

    std::tie(rwycomponent, rwyheadwind, rwytailwind) = wind(rwyhead);
    std::cout << "Takeoff:\n";
    std::cout << "    Crosswind: " << rwycomponent << std::endl;
    std::cout << "    Headwind: " << rwyheadwind << std::endl;
    std::cout << "    Tailwind: " << rwytailwind << std::endl;

    std::tie(crucomponent, cruheadwind, crutailwind) = wind(cruhead);
    std::cout << "Cruise:\n";
    std::cout << "    Crosswind: " << crucomponent << std::endl;
    std::cout << "    Headwind: " << cruheadwind << std::endl;
    std::cout << "    Tailwind: " << crutailwind << std::endl;


// we don't wanna run out of fuel
double cruisespeed = 480;
double fuelcruisetime = 12.5;
double averagespeed = 0;
double averageclimbspeed = 0;
double desspeed = 373; // average descent airspeed

cruisespeed -= cruheadwind;
cruisespeed += crutailwind;

int e = 300;
while (e < distance) {
  e++;
  fuelcruisetime += 0.125;
    }

 if (cruheadwind > 0) {
   fuelcruisetime += (cruheadwind * 0.00005) * (distance);
 } else if (crutailwind > 0) {
    fuelcruisetime -= (crutailwind * 0.00005) * (distance);
  }

double displayfuelcruisetime = floor(fuelcruisetime);

  std::cout << "Estimated Cruise Time: " << displayfuelcruisetime << " min\n";

averageclimbspeed = (160 + cruisespeed) / 2;
averageclimbspeed -= cruheadwind;
averageclimbspeed += crutailwind;

desspeed -= cruheadwind;
desspeed += crutailwind;

averagespeed = ((averageclimbspeed * 20) + (cruisespeed * fuelcruisetime) + (desspeed * 20)) / (40 + fuelcruisetime);


 // average flight TAS
 double TOW = 0;

std::cout << "Average Flight Speed: " << floor(averagespeed) << "\n";


// how much fuel do you think we'll burn??
  double estimatedfuel = 15000;

int a = 0;
while (a < distance + 1) {
  a++;
  estimatedfuel += 50;
  }

int b = 0;
while (b < payload + 1) {
  b++;
  estimatedfuel += 0.1;
  }

int c = 0;
while (c < cruheadwind + 1 || c < crutailwind + 1) {
  c++;
  if (cruheadwind > 0) {
  estimatedfuel += cruheadwind * 10;
  } else if (crutailwind > 0) {
    estimatedfuel -= crutailwind * 10;
    }
      }

std::cout << "Estimated Fuel: " << floor(estimatedfuel) << "\n";

// 357000 is maximum takeoff weight (656000) - empty weight (299000)
// the load is rounded down to accurately predict fuel burn throughout the flight
double preload = (estimatedfuel + payload) / 357000;

double load = preload;
load = floor(10 * load);// floor(10 * load + 0.5f) / 10 will round up from .5
if (preload >= 0.1 && preload - 0.02 < load / 10) {
  load -= 1;
  }

if (load > 10) {
  load = 10;
}
std::cout << "Pre Load: " << preload << "\n";
std::cout << "Load: " << load << "\n";
std::cout << "Estimated TOW: " << (299000 + estimatedfuel + payload) << "\n";


// Fuel Burn, Optimal Cruise Altitude, Climb N1 and Cruise N1 calculated based on Load
double fuelburn = 0;
double cruisealt = 0;

std::vector<int> Vload {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
std::vector<double> Vburn {20000, 21000, 22000, 23000, 24000, 25000, 26000, 27000, 28000, 29000, 30000};

std::vector<int> Valt {380, 370, 370, 350, 330, 330, 310, 310, 310, 310, 310};

for (int I = 0; I < Vload.size(); I++) 
  if (load == Vload[I]) {
    load = Vload[I];
    fuelburn = Vburn[I];
    cruisealt = Valt[I];
  }

if (load > 1 && direction == 'W') {
  cruisealt -= 10;
} else if (load == 1 && direction == 'W') {
    cruisealt += 10;
  }

int y = 0;
while (y < distance + 1 && y < 2500) {
  y++;
  fuelburn -= (fuelburn * 0.00008);
    }

if (runwaycondition == 'W') {
  fuelburn += fuelburn * 0.03;
}   // rain will increase fuel consumption slightly

std::cout << "Fuel Burn: " << fuelburn << " ibs/hour\n"; 
std::cout << "Optimal Cruise Altitude: " << cruisealt << "\n";
std::cout << "Climb N1:\n" << "   100 - 200 alt: 94%   200 - 300 alt: 95%   300 - cruise alt: 96%\n";
std::cout << "Target Cruise N1: Mach .843\n";


// Temperature at Cruise Altitude
double crumeter = 0;    // cruise alt in meters
double SAT = 0;    // static air temperature
double Sfah = 0;  // display SAT in fahrenheit
double kel = 0;   // SAT in Kelvin
double ramrise = 0;   
double TAT = 0;   // total air temperature
double Tfah = 0;  // display TAT in fahrenheit

crumeter = (cruisealt * 100) / 3.281;

if (cruisealt > 360) {
  SAT = -56.46;
} else {
    SAT = 15.04 - (0.00649 * crumeter);
  }

kel = SAT + 273.15;     // celcius to Kelvin

ramrise = kel * 0.2 * pow(0.843, 2);

TAT = kel + ramrise;

Sfah = (SAT * 9/5) + 32;

Tfah = (TAT - 273.15) * 9/5 + 32;

std::cout << "Cruise SAT: " << floor(Sfah) << " F";
std::cout << "    Cruise TAT: " << floor(Tfah) << " F\n";


// fuel calculation
double triptime = 0;
int T = 0;
int dishours = 0; // display trip hours
int dismin = 0; // display trip minutes
double tripfuel = 0;
double contfuel = 0;
double altfuel = 0;
double resfuel = 0;
double fuelinpounds = 0;
double gatefuel = 0;

triptime = (distance / averagespeed);

T = int(triptime * 60);
dishours = T / 60;
dismin = T % 60;

std::cout << "Triptime: " << dishours << " hr & " << dismin << " min    /   " << floor(triptime * 60) << " min    /   " << triptime << " hrs\n";

tripfuel = (fuelburn * triptime);
std::cout << "Tripfuel: " << round(tripfuel) << "\n";

contfuel = (tripfuel * 0.05);
std::cout << "Contingency Fuel: " << round(contfuel) << "\n";

altfuel = (50 / averagespeed) * fuelburn;

if (runwaycondition == 'W' || windspeed >= 20) {
  altfuel *= 2;
    }
std::cout << "Alternate Fuel: " << round(altfuel) << "\n";

resfuel = (0.75 * fuelburn);
std::cout << "Reserve Fuel: " << round(resfuel) << "\n";

fuelinpounds = (taxifuel + tripfuel + contfuel + altfuel + resfuel);

if (fuelinpounds > 377000) {
  fuelinpounds = 377000;
}
std::cout << "    Total Fuel: " << round(fuelinpounds);

std::cout << std::fixed << std::setprecision(1) << "      Estimated Gate Fuel: " << (contfuel + altfuel + resfuel) / 1000 << "\n" << std::setprecision(0);


// Fuel Capacity: 377,000 pounds


// TOW Calculation
TOW = (fuelinpounds + payload + 299000);
std::cout << "    TOW: " << TOW;

if (TOW > 656000) {
  std::cout << "  WARNING: TOW EXCEEDS MANUFACTURER LIMITS\n";
  }


// COG Calculation
double COG = 0.1;

  int H = 300000;
while (H < TOW + 1) {
  H++;
  COG += 0.00000812324;
    }

std::cout << std::fixed << std::setprecision(1) << "            COG: " << COG << "\n" << std::setprecision(0);

// Maximum Permissible Takeoff Weight (MPTOW)
double MPTOW = 656000;
double reduceTOW = 0;

  int U = 10000;
while (U > runwaylength + 1) {
  U--;
  MPTOW -= 50;
    }

  int v = 0;
while (v < elevation + 1) {
  v++;
  MPTOW -= 15.021781583295779;
    }

  int W = 0;
while (W < rwyheadwind + 1) {
  W++;
  MPTOW += 1000;
    }

  int x = 0;
while (x < rwytailwind + 1) {
  x++;
  MPTOW -= 1000;
    }

if (TOW > MPTOW) {
  reduceTOW = TOW - MPTOW;
  std::cout << "***FATAL ERROR: TOW EXCEEDS MPTOW. REDUCE TOW BY " << reduceTOW << " POUNDS\n";
    exit(0);
} else if (MPTOW > 656000) {
    std::cout << "Maximum Permissible TOW: FULL CAPACITY\n";
  } else {
    std::cout << "Maximum Permissible TOW: " << MPTOW << "\n";
  }


// how long is this thing going to take?
int climbtime = 20;
int cruisetime = 0;
int destime = (desdistance / desspeed) * 60;
  
cruisetime = (triptime * 60) - climbtime - destime;

if (cruisetime < 0) {
  cruisetime = 0;
  std::cout << "*Insufficient flight time to reach optimal cruise altitude.\n";
  }

std::cout << "Second Source Estimated Cruise Time: " << cruisetime << " min\n";

std::cout << "Time descending to LOC: " << destime << " min\n";


// how steep can we descend without making the passengers sick?
int fpm = 0;
cruisealt *= 100;
fpm = (cruisealt / destime);
  
int remainder2 = fpm % 100;
if (remainder2 != 0) {
  fpm = fpm + 100 - remainder2;
}

std::cout << "Optimal Descent FPM: " << fpm << " fpm\n";


// how fast do we gotta get to fly?
int flaps = 0;
double V1 = 109;
double V2 = 140;
double VR = 130;

  int m = 300000;
while (m < TOW + 1) {
  m++;
  V1 += 0.000117647058824;
  V2 += 0.000112044817927;
  VR += 0.000134453781513; 
    }

  int p = 0;
while (p < rwyheadwind + 1) {
    p++;
    V1 += 0.5;
    VR -= 0.5;
  }

  int q = 0;
while (q < rwytailwind + 1) {
    q++;
    V1 -= 2;
    V2 += 1;
  }

  if (runwaylength < 10000) {
  int r = 10000;
while (r > runwaylength - 1) {
    r--;
    V1 -= 0.008;
    V2 -= 0.005;
    VR -= 0.005;
  }
}

if (runwaylength >= 10000) {
    int s = 10000;
  while (s < runwaylength + 1) {
      s++;
      V1 += 0.00005;
  }
}
  int t = 0;
while (t < elevation + 1) {
    t++;
    V1 -= 0.002;
    V2 += 0.0005;
    VR += 0.00025;
  }

if (runwaycondition == 'W') {
    int u = 18045;
  while (u > runwaylength + 1) {
    u--;
    V1 -= 0.001203819012038;
  }
    }

if (V1 > VR || V1 > V2) {
  V1 = VR - 1;
    }

if (VR > 186) {
  VR = 186;
    }

V1 = floor(V1);
V2 = floor(V2);
VR = floor(VR);

std::cout << "V1: " << V1 << "\n";
std::cout << "V2: " << V2 << "\n";
std::cout << "VR: " << VR << "\n"; 
  

// flaps for takeoff?
double trim = 17;

std::deque<int> degree = {1, 5, 15, 20};
  
if (rwycomponent >= 10) {
    degree.push_front(1);
      trim += 5;
  }
if (runwaylength < 9843 || elevation >= 5000) {
    degree.erase(degree.begin());
  }

if (TOW > 300000 && TOW < 397000) {
  flaps = degree[0];
} else if (TOW < 529000) {
    flaps = degree[1];      
} else if (TOW < 657000) {    
    flaps = degree[2];
  }
std::cout << "Flap Setting: " << flaps << "\n";


// and how bout trim for takeoff?

// trim variable initiated in Flaps

  int J = 299000;
while (J < TOW + 1) {
  J++;
  trim += 0.00003921568;
    }

  int K = 0;
while (K < rwyheadwind + 1 || K < rwytailwind + 1) {
  K++;
  if (rwyheadwind > 0) {
    trim -= 0.6;
  } else {
      trim += 0.6;
        if (rwytailwind > 11) {
            std::cout << "WARNING: TAKEOFF TAILWIND EXCEEDS SAFE OPERATING LIMITS\n";
              exit(0);
        }
          }
            }

  int L = 10000;
while (L > runwaylength + 1) {
  L--;
  trim += 0.0025;
    }

  int M = 0;
while (M < elevation + 1) {
  M++;
  trim += 0.001;
    }

if (trim < 0) {
  trim = 0;
    }

std::cout << "Takeoff Trim: " << trim;

}

// have a nice flight !
    

      

        
