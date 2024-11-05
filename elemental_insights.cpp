#include <graphics.h>
#pragma link<winbgim.a>
#include <iostream>
#include <string>
#include <cmath>
#include <cstring>  // Added for strcpy
using namespace std;

// Structure to hold element information with additional properties
struct Element {
    char symbol[3];        // Changed from const char* to char array
    char name[20];         // Changed from const char* to char array
    int atomicNumber;
    double atomicWeight;
    char electronConfig[30]; // Changed from const char* to char array
    int color;
    int x;
    int y;
    double atomicRadius;
    double electronegativity;
    char block[2];         // Changed from const char* to char array
};

// [Rest of the constants remain the same]
const int boxSize = 60;
const int baseX = 50;
const int baseY = 30;
const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 900;

const int ALKALI_METAL = LIGHTBLUE;
const int ALKALINE_EARTH = LIGHTMAGENTA;
const int TRANSITION_METAL = LIGHTGRAY;
const int POST_TRANSITION = YELLOW;
const int METALLOID = BROWN;
const int NONMETAL = LIGHTGREEN;
const int NOBLE_GAS = LIGHTRED;
const int LANTHANIDE = CYAN;
const int ACTINIDE = LIGHTCYAN;

// Function to draw electron shells [remains the same]
void drawElectronShells(Element elem, int centerX, int centerY) {
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    
    int shells = 0;
    if(elem.atomicNumber <= 2) shells = 1;
    else if(elem.atomicNumber <= 10) shells = 2;
    else if(elem.atomicNumber <= 18) shells = 3;
    else if(elem.atomicNumber <= 36) shells = 4;
    else if(elem.atomicNumber <= 54) shells = 5;
    else if(elem.atomicNumber <= 86) shells = 6;
    else shells = 7;
    
    for(int i = 1; i <= shells; i++) {
        circle(centerX, centerY, i * 20);
    }
}

// Function to draw element categories legend
void drawLegend() {
    const int legendX = WINDOW_WIDTH - 200;
    const int legendY = 100;
    const int boxW = 15;
    const int spacing = 25;
    
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    setcolor(WHITE);
    outtextxy(legendX, legendY - 30, (char*)"Element Categories:");
    
    const char* categories[] = {
        "Alkali Metals",
        "Alkaline Earth",
        "Transition Metals",
        "Post-Transition",
        "Metalloids",
        "Nonmetals",
        "Noble Gases",
        "Lanthanides",
        "Actinides"
    };
    
    int colors[] = {
        ALKALI_METAL,
        ALKALINE_EARTH,
        TRANSITION_METAL,
        POST_TRANSITION,
        METALLOID,
        NONMETAL,
        NOBLE_GAS,
        LANTHANIDE,
        ACTINIDE
    };
    
    for(int i = 0; i < 9; i++) {
        setfillstyle(SOLID_FILL, colors[i]);
        bar(legendX, legendY + i*spacing, legendX + boxW, legendY + boxW + i*spacing);
        setcolor(WHITE);
        outtextxy(legendX + boxW + 5, legendY + i*spacing, (char*)categories[i]);
    }
}

// Function to display element details in an enhanced popup
void showElementDetails(Element elem) {
    int oldBkColor = getbkcolor();
    int oldColor = getcolor();
    
    int popupWidth = 500;
    int popupHeight = 400;
    int popupX = (getmaxx() - popupWidth) / 2;
    int popupY = (getmaxy() - popupHeight) / 2;
    
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(BLACK);
    bar(popupX, popupY, popupX + popupWidth, popupY + popupHeight);
    rectangle(popupX, popupY, popupX + popupWidth, popupY + popupHeight);
    
    drawElectronShells(elem, popupX + popupWidth/4, popupY + popupHeight/2);
    
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    
    char buffer[100];
    sprintf(buffer, "Element: %s (%s)", elem.name, elem.symbol);
    outtextxy(popupX + 20, popupY + 40, buffer);
    
    sprintf(buffer, "Atomic Number: %d", elem.atomicNumber);
    outtextxy(popupX + 20, popupY + 80, buffer);
    
    sprintf(buffer, "Atomic Weight: %.3f", elem.atomicWeight);
    outtextxy(popupX + 20, popupY + 120, buffer);
    
    sprintf(buffer, "Block: %s", elem.block);
    outtextxy(popupX + 20, popupY + 160, buffer);
    
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    sprintf(buffer, "Electron Config: %s", elem.electronConfig);
    outtextxy(popupX + 20, popupY + 200, buffer);
    
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    outtextxy(popupX + 20, popupY + 320, (char*)"Click anywhere to close");
    
    while(!ismouseclick(WM_LBUTTONDOWN)) {
        delay(100);
    }
    clearmouseclick(WM_LBUTTONDOWN);
    
    setbkcolor(oldBkColor);
    setcolor(oldColor);
    cleardevice();
}

// Function to draw a single element box with improved styling
void drawElement(Element& elem) {
    setcolor(elem.color);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(elem.x, elem.y, elem.x + boxSize, elem.y + boxSize);
    
    char num[5];
    sprintf(num, "%d", elem.atomicNumber);
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(elem.x + 5, elem.y + 5, num);
    
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 2);
    outtextxy(elem.x + (boxSize/4), elem.y + (boxSize/3), elem.symbol);
    
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(elem.x + boxSize - 15, elem.y + boxSize - 15, elem.block);
}

// Function to check if mouse click is inside element box [remains the same]
bool isClickInElement(int mouseX, int mouseY, Element elem) {
    return (mouseX >= elem.x && mouseX <= elem.x + boxSize &&
            mouseY >= elem.y && mouseY <= elem.y + boxSize);
}

int main() {
    // Initialize graphics
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Interactive Periodic Table");
    setbkcolor(BLACK);
    cleardevice();
    
    // Create and initialize elements array
    Element elements[118];  // Declare array
    
    // Initialize first element as example (you'll need to do this for all elements)
   // Initialize all elements
// Period 1
strcpy(elements[0].symbol, "H");
strcpy(elements[0].name, "Hydrogen");
strcpy(elements[0].electronConfig, "1s1");
strcpy(elements[0].block, "s");
elements[0].atomicNumber = 1;
elements[0].atomicWeight = 1.008;
elements[0].color = NONMETAL;
elements[0].x = baseX;
elements[0].y = baseY;

strcpy(elements[1].symbol, "He");
strcpy(elements[1].name, "Helium");
strcpy(elements[1].electronConfig, "1s2");
strcpy(elements[1].block, "s");
elements[1].atomicNumber = 2;
elements[1].atomicWeight = 4.003;
elements[1].color = NOBLE_GAS;
elements[1].x = baseX + (17 * boxSize);
elements[1].y = baseY;

// Period 2
strcpy(elements[2].symbol, "Li");
strcpy(elements[2].name, "Lithium");
strcpy(elements[2].electronConfig, "2s1");
strcpy(elements[2].block, "s");
elements[2].atomicNumber = 3;
elements[2].atomicWeight = 6.941;
elements[2].color = ALKALI_METAL;
elements[2].x = baseX;
elements[2].y = baseY + boxSize;

strcpy(elements[3].symbol, "Be");
strcpy(elements[3].name, "Beryllium");
strcpy(elements[3].electronConfig, "2s2");
strcpy(elements[3].block, "s");
elements[3].atomicNumber = 4;
elements[3].atomicWeight = 9.012;
elements[3].color = ALKALINE_EARTH;
elements[3].x = baseX + boxSize;
elements[3].y = baseY + boxSize;

strcpy(elements[4].symbol, "B");
strcpy(elements[4].name, "Boron");
strcpy(elements[4].electronConfig, "2s2 2p1");
strcpy(elements[4].block, "p");
elements[4].atomicNumber = 5;
elements[4].atomicWeight = 10.811;
elements[4].color = METALLOID;
elements[4].x = baseX + (12 * boxSize);
elements[4].y = baseY + boxSize;

strcpy(elements[5].symbol, "C");
strcpy(elements[5].name, "Carbon");
strcpy(elements[5].electronConfig, "2s2 2p2");
strcpy(elements[5].block, "p");
elements[5].atomicNumber = 6;
elements[5].atomicWeight = 12.011;
elements[5].color = NONMETAL;
elements[5].x = baseX + (13 * boxSize);
elements[5].y = baseY + boxSize;

strcpy(elements[6].symbol, "N");
strcpy(elements[6].name, "Nitrogen");
strcpy(elements[6].electronConfig, "2s2 2p3");
strcpy(elements[6].block, "p");
elements[6].atomicNumber = 7;
elements[6].atomicWeight = 14.007;
elements[6].color = NONMETAL;
elements[6].x = baseX + (14 * boxSize);
elements[6].y = baseY + boxSize;

strcpy(elements[7].symbol, "O");
strcpy(elements[7].name, "Oxygen");
strcpy(elements[7].electronConfig, "2s2 2p4");
strcpy(elements[7].block, "p");
elements[7].atomicNumber = 8;
elements[7].atomicWeight = 15.999;
elements[7].color = NONMETAL;
elements[7].x = baseX + (15 * boxSize);
elements[7].y = baseY + boxSize;

strcpy(elements[8].symbol, "F");
strcpy(elements[8].name, "Fluorine");
strcpy(elements[8].electronConfig, "2s2 2p5");
strcpy(elements[8].block, "p");
elements[8].atomicNumber = 9;
elements[8].atomicWeight = 18.998;
elements[8].color = NONMETAL;
elements[8].x = baseX + (16 * boxSize);
elements[8].y = baseY + boxSize;

strcpy(elements[9].symbol, "Ne");
strcpy(elements[9].name, "Neon");
strcpy(elements[9].electronConfig, "2s2 2p6");
strcpy(elements[9].block, "p");
elements[9].atomicNumber = 10;
elements[9].atomicWeight = 20.180;
elements[9].color = NOBLE_GAS;
elements[9].x = baseX + (17 * boxSize);
elements[9].y = baseY + boxSize;

// Period 3
strcpy(elements[10].symbol, "Na");
strcpy(elements[10].name, "Sodium");
strcpy(elements[10].electronConfig, "3s1");
strcpy(elements[10].block, "s");
elements[10].atomicNumber = 11;
elements[10].atomicWeight = 22.990;
elements[10].color = ALKALI_METAL;
elements[10].x = baseX;
elements[10].y = baseY + (2 * boxSize);

// Period 3 (continued)
strcpy(elements[11].symbol, "Mg");
strcpy(elements[11].name, "Magnesium");
strcpy(elements[11].electronConfig, "3s2");
strcpy(elements[11].block, "s");
elements[11].atomicNumber = 12;
elements[11].atomicWeight = 24.305;
elements[11].color = ALKALINE_EARTH;
elements[11].x = baseX + boxSize;
elements[11].y = baseY + (2 * boxSize);

strcpy(elements[12].symbol, "Al");
strcpy(elements[12].name, "Aluminum");
strcpy(elements[12].electronConfig, "3s2 3p1");
strcpy(elements[12].block, "p");
elements[12].atomicNumber = 13;
elements[12].atomicWeight = 26.982;
elements[12].color = POST_TRANSITION;
elements[12].x = baseX + (12 * boxSize);
elements[12].y = baseY + (2 * boxSize);

strcpy(elements[13].symbol, "Si");
strcpy(elements[13].name, "Silicon");
strcpy(elements[13].electronConfig, "3s2 3p2");
strcpy(elements[13].block, "p");
elements[13].atomicNumber = 14;
elements[13].atomicWeight = 28.086;
elements[13].color = METALLOID;
elements[13].x = baseX + (13 * boxSize);
elements[13].y = baseY + (2 * boxSize);

strcpy(elements[14].symbol, "P");
strcpy(elements[14].name, "Phosphorus");
strcpy(elements[14].electronConfig, "3s2 3p3");
strcpy(elements[14].block, "p");
elements[14].atomicNumber = 15;
elements[14].atomicWeight = 30.974;
elements[14].color = NONMETAL;
elements[14].x = baseX + (14 * boxSize);
elements[14].y = baseY + (2 * boxSize);

strcpy(elements[15].symbol, "S");
strcpy(elements[15].name, "Sulfur");
strcpy(elements[15].electronConfig, "3s2 3p4");
strcpy(elements[15].block, "p");
elements[15].atomicNumber = 16;
elements[15].atomicWeight = 32.065;
elements[15].color = NONMETAL;
elements[15].x = baseX + (15 * boxSize);
elements[15].y = baseY + (2 * boxSize);

strcpy(elements[16].symbol, "Cl");
strcpy(elements[16].name, "Chlorine");
strcpy(elements[16].electronConfig, "3s2 3p5");
strcpy(elements[16].block, "p");
elements[16].atomicNumber = 17;
elements[16].atomicWeight = 35.453;
elements[16].color = NONMETAL;
elements[16].x = baseX + (16 * boxSize);
elements[16].y = baseY + (2 * boxSize);

strcpy(elements[17].symbol, "Ar");
strcpy(elements[17].name, "Argon");
strcpy(elements[17].electronConfig, "3s2 3p6");
strcpy(elements[17].block, "p");
elements[17].atomicNumber = 18;
elements[17].atomicWeight = 39.948;
elements[17].color = NOBLE_GAS;
elements[17].x = baseX + (17 * boxSize);
elements[17].y = baseY + (2 * boxSize);

// Period 4 (first part)
strcpy(elements[18].symbol, "K");
strcpy(elements[18].name, "Potassium");
strcpy(elements[18].electronConfig, "4s1");
strcpy(elements[18].block, "s");
elements[18].atomicNumber = 19;
elements[18].atomicWeight = 39.098;
elements[18].color = ALKALI_METAL;
elements[18].x = baseX;
elements[18].y = baseY + (3 * boxSize);

strcpy(elements[19].symbol, "Ca");
strcpy(elements[19].name, "Calcium");
strcpy(elements[19].electronConfig, "4s2");
strcpy(elements[19].block, "s");
elements[19].atomicNumber = 20;
elements[19].atomicWeight = 40.078;
elements[19].color = ALKALINE_EARTH;
elements[19].x = baseX + boxSize;
elements[19].y = baseY + (3 * boxSize);

// First row transition metals
strcpy(elements[20].symbol, "Sc");
strcpy(elements[20].name, "Scandium");
strcpy(elements[20].electronConfig, "3d1 4s2");
strcpy(elements[20].block, "d");
elements[20].atomicNumber = 21;
elements[20].atomicWeight = 44.956;
elements[20].color = TRANSITION_METAL;
elements[20].x = baseX + (2 * boxSize);
elements[20].y = baseY + (3 * boxSize);
// Period 4 (continued - transition metals)
strcpy(elements[21].symbol, "Ti");
strcpy(elements[21].name, "Titanium");
strcpy(elements[21].electronConfig, "3d2 4s2");
strcpy(elements[21].block, "d");
elements[21].atomicNumber = 22;
elements[21].atomicWeight = 47.867;
elements[21].color = TRANSITION_METAL;
elements[21].x = baseX + (3 * boxSize);
elements[21].y = baseY + (3 * boxSize);

strcpy(elements[22].symbol, "V");
strcpy(elements[22].name, "Vanadium");
strcpy(elements[22].electronConfig, "3d3 4s2");
strcpy(elements[22].block, "d");
elements[22].atomicNumber = 23;
elements[22].atomicWeight = 50.942;
elements[22].color = TRANSITION_METAL;
elements[22].x = baseX + (4 * boxSize);
elements[22].y = baseY + (3 * boxSize);

strcpy(elements[23].symbol, "Cr");
strcpy(elements[23].name, "Chromium");
strcpy(elements[23].electronConfig, "3d5 4s1");
strcpy(elements[23].block, "d");
elements[23].atomicNumber = 24;
elements[23].atomicWeight = 51.996;
elements[23].color = TRANSITION_METAL;
elements[23].x = baseX + (5 * boxSize);
elements[23].y = baseY + (3 * boxSize);

strcpy(elements[24].symbol, "Mn");
strcpy(elements[24].name, "Manganese");
strcpy(elements[24].electronConfig, "3d5 4s2");
strcpy(elements[24].block, "d");
elements[24].atomicNumber = 25;
elements[24].atomicWeight = 54.938;
elements[24].color = TRANSITION_METAL;
elements[24].x = baseX + (6 * boxSize);
elements[24].y = baseY + (3 * boxSize);

strcpy(elements[25].symbol, "Fe");
strcpy(elements[25].name, "Iron");
strcpy(elements[25].electronConfig, "3d6 4s2");
strcpy(elements[25].block, "d");
elements[25].atomicNumber = 26;
elements[25].atomicWeight = 55.845;
elements[25].color = TRANSITION_METAL;
elements[25].x = baseX + (7 * boxSize);
elements[25].y = baseY + (3 * boxSize);

strcpy(elements[26].symbol, "Co");
strcpy(elements[26].name, "Cobalt");
strcpy(elements[26].electronConfig, "3d7 4s2");
strcpy(elements[26].block, "d");
elements[26].atomicNumber = 27;
elements[26].atomicWeight = 58.933;
elements[26].color = TRANSITION_METAL;
elements[26].x = baseX + (8 * boxSize);
elements[26].y = baseY + (3 * boxSize);

strcpy(elements[27].symbol, "Ni");
strcpy(elements[27].name, "Nickel");
strcpy(elements[27].electronConfig, "3d8 4s2");
strcpy(elements[27].block, "d");
elements[27].atomicNumber = 28;
elements[27].atomicWeight = 58.693;
elements[27].color = TRANSITION_METAL;
elements[27].x = baseX + (9 * boxSize);
elements[27].y = baseY + (3 * boxSize);

strcpy(elements[28].symbol, "Cu");
strcpy(elements[28].name, "Copper");
strcpy(elements[28].electronConfig, "3d10 4s1");
strcpy(elements[28].block, "d");
elements[28].atomicNumber = 29;
elements[28].atomicWeight = 63.546;
elements[28].color = TRANSITION_METAL;
elements[28].x = baseX + (10 * boxSize);
elements[28].y = baseY + (3 * boxSize);

strcpy(elements[29].symbol, "Zn");
strcpy(elements[29].name, "Zinc");
strcpy(elements[29].electronConfig, "3d10 4s2");
strcpy(elements[29].block, "d");
elements[29].atomicNumber = 30;
elements[29].atomicWeight = 65.38;
elements[29].color = TRANSITION_METAL;
elements[29].x = baseX + (11 * boxSize);
elements[29].y = baseY + (3 * boxSize);

// Period 4 (p-block)
strcpy(elements[30].symbol, "Ga");
strcpy(elements[30].name, "Gallium");
strcpy(elements[30].electronConfig, "3d10 4s2 4p1");
strcpy(elements[30].block, "p");
elements[30].atomicNumber = 31;
elements[30].atomicWeight = 69.723;
elements[30].color = POST_TRANSITION;
elements[30].x = baseX + (12 * boxSize);
elements[30].y = baseY + (3 * boxSize);

strcpy(elements[31].symbol, "Ge");
strcpy(elements[31].name, "Germanium");
strcpy(elements[31].electronConfig, "3d10 4s2 4p2");
strcpy(elements[31].block, "p");
elements[31].atomicNumber = 32;
elements[31].atomicWeight = 72.64;
elements[31].color = METALLOID;
elements[31].x = baseX + (13 * boxSize);
elements[31].y = baseY + (3 * boxSize);

strcpy(elements[32].symbol, "As");
strcpy(elements[32].name, "Arsenic");
strcpy(elements[32].electronConfig, "3d10 4s2 4p3");
strcpy(elements[32].block, "p");
elements[32].atomicNumber = 33;
elements[32].atomicWeight = 74.922;
elements[32].color = METALLOID;
elements[32].x = baseX + (14 * boxSize);
elements[32].y = baseY + (3 * boxSize);

strcpy(elements[33].symbol, "Se");
strcpy(elements[33].name, "Selenium");
strcpy(elements[33].electronConfig, "3d10 4s2 4p4");
strcpy(elements[33].block, "p");
elements[33].atomicNumber = 34;
elements[33].atomicWeight = 78.96;
elements[33].color = NONMETAL;
elements[33].x = baseX + (15 * boxSize);
elements[33].y = baseY + (3 * boxSize);

strcpy(elements[34].symbol, "Br");
strcpy(elements[34].name, "Bromine");
strcpy(elements[34].electronConfig, "3d10 4s2 4p5");
strcpy(elements[34].block, "p");
elements[34].atomicNumber = 35;
elements[34].atomicWeight = 79.904;
elements[34].color = NONMETAL;
elements[34].x = baseX + (16 * boxSize);
elements[34].y = baseY + (3 * boxSize);

strcpy(elements[35].symbol, "Kr");
strcpy(elements[35].name, "Krypton");
strcpy(elements[35].electronConfig, "3d10 4s2 4p6");
strcpy(elements[35].block, "p");
elements[35].atomicNumber = 36;
elements[35].atomicWeight = 83.798;
elements[35].color = NOBLE_GAS;
elements[35].x = baseX + (17 * boxSize);
elements[35].y = baseY + (3 * boxSize);

// Period 5 (s-block)
strcpy(elements[36].symbol, "Rb");
strcpy(elements[36].name, "Rubidium");
strcpy(elements[36].electronConfig, "5s1");
strcpy(elements[36].block, "s");
elements[36].atomicNumber = 37;
elements[36].atomicWeight = 85.468;
elements[36].color = ALKALI_METAL;
elements[36].x = baseX;
elements[36].y = baseY + (4 * boxSize);

strcpy(elements[37].symbol, "Sr");
strcpy(elements[37].name, "Strontium");
strcpy(elements[37].electronConfig, "5s2");
strcpy(elements[37].block, "s");
elements[37].atomicNumber = 38;
elements[37].atomicWeight = 87.62;
elements[37].color = ALKALINE_EARTH;
elements[37].x = baseX + boxSize;
elements[37].y = baseY + (4 * boxSize);

// Period 5 (d-block)
strcpy(elements[38].symbol, "Y");
strcpy(elements[38].name, "Yttrium");
strcpy(elements[38].electronConfig, "4d1 5s2");
strcpy(elements[38].block, "d");
elements[38].atomicNumber = 39;
elements[38].atomicWeight = 88.906;
elements[38].color = TRANSITION_METAL;
elements[38].x = baseX + (2 * boxSize);
elements[38].y = baseY + (4 * boxSize);

strcpy(elements[39].symbol, "Zr");
strcpy(elements[39].name, "Zirconium");
strcpy(elements[39].electronConfig, "4d2 5s2");
strcpy(elements[39].block, "d");
elements[39].atomicNumber = 40;
elements[39].atomicWeight = 91.224;
elements[39].color = TRANSITION_METAL;
elements[39].x = baseX + (3 * boxSize);
elements[39].y = baseY + (4 * boxSize);

strcpy(elements[40].symbol, "Nb");
strcpy(elements[40].name, "Niobium");
strcpy(elements[40].electronConfig, "4d4 5s1");
strcpy(elements[40].block, "d");
elements[40].atomicNumber = 41;
elements[40].atomicWeight = 92.906;
elements[40].color = TRANSITION_METAL;
elements[40].x = baseX + (4 * boxSize);
elements[40].y = baseY + (4 * boxSize);

strcpy(elements[41].symbol, "Mo");
strcpy(elements[41].name, "Molybdenum");
strcpy(elements[41].electronConfig, "4d5 5s1");
strcpy(elements[41].block, "d");
elements[41].atomicNumber = 42;
elements[41].atomicWeight = 95.96;
elements[41].color = TRANSITION_METAL;
elements[41].x = baseX + (5 * boxSize);
elements[41].y = baseY + (4 * boxSize);

strcpy(elements[42].symbol, "Tc");
strcpy(elements[42].name, "Technetium");
strcpy(elements[42].electronConfig, "4d5 5s2");
strcpy(elements[42].block, "d");
elements[42].atomicNumber = 43;
elements[42].atomicWeight = 98;
elements[42].color = TRANSITION_METAL;
elements[42].x = baseX + (6 * boxSize);
elements[42].y = baseY + (4 * boxSize);

strcpy(elements[43].symbol, "Ru");
strcpy(elements[43].name, "Ruthenium");
strcpy(elements[43].electronConfig, "4d7 5s1");
strcpy(elements[43].block, "d");
elements[43].atomicNumber = 44;
elements[43].atomicWeight = 101.07;
elements[43].color = TRANSITION_METAL;
elements[43].x = baseX + (7 * boxSize);
elements[43].y = baseY + (4 * boxSize);

strcpy(elements[44].symbol, "Rh");
strcpy(elements[44].name, "Rhodium");
strcpy(elements[44].electronConfig, "4d8 5s1");
strcpy(elements[44].block, "d");
elements[44].atomicNumber = 45;
elements[44].atomicWeight = 102.91;
elements[44].color = TRANSITION_METAL;
elements[44].x = baseX + (8 * boxSize);
elements[44].y = baseY + (4 * boxSize);

strcpy(elements[45].symbol, "Pd");
strcpy(elements[45].name, "Palladium");
strcpy(elements[45].electronConfig, "4d10");
strcpy(elements[45].block, "d");
elements[45].atomicNumber = 46;
elements[45].atomicWeight = 106.42;
elements[45].color = TRANSITION_METAL;
elements[45].x = baseX + (9 * boxSize);
elements[45].y = baseY + (4 * boxSize);

strcpy(elements[46].symbol, "Ag");
strcpy(elements[46].name, "Silver");
strcpy(elements[46].electronConfig, "4d10 5s1");
strcpy(elements[46].block, "d");
elements[46].atomicNumber = 47;
elements[46].atomicWeight = 107.87;
elements[46].color = TRANSITION_METAL;
elements[46].x = baseX + (10 * boxSize);
elements[46].y = baseY + (4 * boxSize);

strcpy(elements[47].symbol, "Cd");
strcpy(elements[47].name, "Cadmium");
strcpy(elements[47].electronConfig, "4d10 5s2");
strcpy(elements[47].block, "d");
elements[47].atomicNumber = 48;
elements[47].atomicWeight = 112.41;
elements[47].color = TRANSITION_METAL;
elements[47].x = baseX + (11 * boxSize);
elements[47].y = baseY + (4 * boxSize);

// Period 5 (p-block)
strcpy(elements[48].symbol, "In");
strcpy(elements[48].name, "Indium");
strcpy(elements[48].electronConfig, "4d10 5s2 5p1");
strcpy(elements[48].block, "p");
elements[48].atomicNumber = 49;
elements[48].atomicWeight = 114.82;
elements[48].color = POST_TRANSITION;
elements[48].x = baseX + (12 * boxSize);
elements[48].y = baseY + (4 * boxSize);

strcpy(elements[49].symbol, "Sn");
strcpy(elements[49].name, "Tin");
strcpy(elements[49].electronConfig, "4d10 5s2 5p2");
strcpy(elements[49].block, "p");
elements[49].atomicNumber = 50;
elements[49].atomicWeight = 118.71;
elements[49].color = POST_TRANSITION;
elements[49].x = baseX + (13 * boxSize);
elements[49].y = baseY + (4 * boxSize);

strcpy(elements[50].symbol, "Sb");
strcpy(elements[50].name, "Antimony");
strcpy(elements[50].electronConfig, "4d10 5s2 5p3");
strcpy(elements[50].block, "p");
elements[50].atomicNumber = 51;
elements[50].atomicWeight = 121.76;
elements[50].color = METALLOID;
elements[50].x = baseX + (14 * boxSize);
elements[50].y = baseY + (4 * boxSize);

strcpy(elements[51].symbol, "Te");
strcpy(elements[51].name, "Tellurium");
strcpy(elements[51].electronConfig, "4d10 5s2 5p4");
strcpy(elements[51].block, "p");
elements[51].atomicNumber = 52;
elements[51].atomicWeight = 127.60;
elements[51].color = METALLOID;
elements[51].x = baseX + (15 * boxSize);
elements[51].y = baseY + (4 * boxSize);

strcpy(elements[52].symbol, "I");
strcpy(elements[52].name, "Iodine");
strcpy(elements[52].electronConfig, "4d10 5s2 5p5");
strcpy(elements[52].block, "p");
elements[52].atomicNumber = 53;
elements[52].atomicWeight = 126.90;
elements[52].color = NONMETAL;
elements[52].x = baseX + (16 * boxSize);
elements[52].y = baseY + (4 * boxSize);

strcpy(elements[53].symbol, "Xe");
strcpy(elements[53].name, "Xenon");
strcpy(elements[53].electronConfig, "4d10 5s2 5p6");
strcpy(elements[53].block, "p");
elements[53].atomicNumber = 54;
elements[53].atomicWeight = 131.29;
elements[53].color = NOBLE_GAS;
elements[53].x = baseX + (17 * boxSize);
elements[53].y = baseY + (4 * boxSize);

// Period 6 (s-block)
strcpy(elements[54].symbol, "Cs");
strcpy(elements[54].name, "Cesium");
strcpy(elements[54].electronConfig, "6s1");
strcpy(elements[54].block, "s");
elements[54].atomicNumber = 55;
elements[54].atomicWeight = 132.91;
elements[54].color = ALKALI_METAL;
elements[54].x = baseX;
elements[54].y = baseY + (5 * boxSize);

strcpy(elements[55].symbol, "Ba");
strcpy(elements[55].name, "Barium");
strcpy(elements[55].electronConfig, "6s2");
strcpy(elements[55].block, "s");
elements[55].atomicNumber = 56;
elements[55].atomicWeight = 137.33;
elements[55].color = ALKALINE_EARTH;
elements[55].x = baseX + boxSize;
elements[55].y = baseY + (5 * boxSize);

// Lanthanides (placed in separate row below main table)
strcpy(elements[56].symbol, "La");
strcpy(elements[56].name, "Lanthanum");
strcpy(elements[56].electronConfig, "5d1 6s2");
strcpy(elements[56].block, "f");
elements[56].atomicNumber = 57;
elements[56].atomicWeight = 138.91;
elements[56].color = LANTHANIDE;
elements[56].x = baseX + (2 * boxSize);
elements[56].y = baseY + (7 * boxSize);

strcpy(elements[57].symbol, "Ce");
strcpy(elements[57].name, "Cerium");
strcpy(elements[57].electronConfig, "4f1 5d1 6s2");
strcpy(elements[57].block, "f");
elements[57].atomicNumber = 58;
elements[57].atomicWeight = 140.12;
elements[57].color = LANTHANIDE;
elements[57].x = baseX + (3 * boxSize);
elements[57].y = baseY + (7 * boxSize);

// Lanthanides (elements 57-71)
strcpy(elements[56].symbol, "La");
strcpy(elements[56].name, "Lanthanum");
strcpy(elements[56].electronConfig, "5d1 6s2");
strcpy(elements[56].block, "f");
elements[56].atomicNumber = 57;
elements[56].atomicWeight = 138.91;
elements[56].color = LANTHANIDE;
elements[56].x = baseX + (2 * boxSize);
elements[56].y = baseY + (7 * boxSize);

strcpy(elements[57].symbol, "Ce");
strcpy(elements[57].name, "Cerium");
strcpy(elements[57].electronConfig, "4f1 5d1 6s2");
strcpy(elements[57].block, "f");
elements[57].atomicNumber = 58;
elements[57].atomicWeight = 140.12;
elements[57].color = LANTHANIDE;
elements[57].x = baseX + (3 * boxSize);
elements[57].y = baseY + (7 * boxSize);

strcpy(elements[58].symbol, "Pr");
strcpy(elements[58].name, "Praseodymium");
strcpy(elements[58].electronConfig, "4f3 6s2");
strcpy(elements[58].block, "f");
elements[58].atomicNumber = 59;
elements[58].atomicWeight = 140.91;
elements[58].color = LANTHANIDE;
elements[58].x = baseX + (4 * boxSize);
elements[58].y = baseY + (7 * boxSize);

strcpy(elements[59].symbol, "Nd");
strcpy(elements[59].name, "Neodymium");
strcpy(elements[59].electronConfig, "4f4 6s2");
strcpy(elements[59].block, "f");
elements[59].atomicNumber = 60;
elements[59].atomicWeight = 144.24;
elements[59].color = LANTHANIDE;
elements[59].x = baseX + (5 * boxSize);
elements[59].y = baseY + (7 * boxSize);

strcpy(elements[60].symbol, "Pm");
strcpy(elements[60].name, "Promethium");
strcpy(elements[60].electronConfig, "4f5 6s2");
strcpy(elements[60].block, "f");
elements[60].atomicNumber = 61;
elements[60].atomicWeight = 145;
elements[60].color = LANTHANIDE;
elements[60].x = baseX + (6 * boxSize);
elements[60].y = baseY + (7 * boxSize);

strcpy(elements[61].symbol, "Sm");
strcpy(elements[61].name, "Samarium");
strcpy(elements[61].electronConfig, "4f6 6s2");
strcpy(elements[61].block, "f");
elements[61].atomicNumber = 62;
elements[61].atomicWeight = 150.36;
elements[61].color = LANTHANIDE;
elements[61].x = baseX + (7 * boxSize);
elements[61].y = baseY + (7 * boxSize);

strcpy(elements[62].symbol, "Eu");
strcpy(elements[62].name, "Europium");
strcpy(elements[62].electronConfig, "4f7 6s2");
strcpy(elements[62].block, "f");
elements[62].atomicNumber = 63;
elements[62].atomicWeight = 151.96;
elements[62].color = LANTHANIDE;
elements[62].x = baseX + (8 * boxSize);
elements[62].y = baseY + (7 * boxSize);

strcpy(elements[63].symbol, "Gd");
strcpy(elements[63].name, "Gadolinium");
strcpy(elements[63].electronConfig, "4f7 5d1 6s2");
strcpy(elements[63].block, "f");
elements[63].atomicNumber = 64;
elements[63].atomicWeight = 157.25;
elements[63].color = LANTHANIDE;
elements[63].x = baseX + (9 * boxSize);
elements[63].y = baseY + (7 * boxSize);

strcpy(elements[64].symbol, "Tb");
strcpy(elements[64].name, "Terbium");
strcpy(elements[64].electronConfig, "4f9 6s2");
strcpy(elements[64].block, "f");
elements[64].atomicNumber = 65;
elements[64].atomicWeight = 158.93;
elements[64].color = LANTHANIDE;
elements[64].x = baseX + (10 * boxSize);
elements[64].y = baseY + (7 * boxSize);

strcpy(elements[65].symbol, "Dy");
strcpy(elements[65].name, "Dysprosium");
strcpy(elements[65].electronConfig, "4f10 6s2");
strcpy(elements[65].block, "f");
elements[65].atomicNumber = 66;
elements[65].atomicWeight = 162.50;
elements[65].color = LANTHANIDE;
elements[65].x = baseX + (11 * boxSize);
elements[65].y = baseY + (7 * boxSize);

strcpy(elements[66].symbol, "Ho");
strcpy(elements[66].name, "Holmium");
strcpy(elements[66].electronConfig, "4f11 6s2");
strcpy(elements[66].block, "f");
elements[66].atomicNumber = 67;
elements[66].atomicWeight = 164.93;
elements[66].color = LANTHANIDE;
elements[66].x = baseX + (12 * boxSize);
elements[66].y = baseY + (7 * boxSize);

strcpy(elements[67].symbol, "Er");
strcpy(elements[67].name, "Erbium");
strcpy(elements[67].electronConfig, "4f12 6s2");
strcpy(elements[67].block, "f");
elements[67].atomicNumber = 68;
elements[67].atomicWeight = 167.26;
elements[67].color = LANTHANIDE;
elements[67].x = baseX + (13 * boxSize);
elements[67].y = baseY + (7 * boxSize);

strcpy(elements[68].symbol, "Tm");
strcpy(elements[68].name, "Thulium");
strcpy(elements[68].electronConfig, "4f13 6s2");
strcpy(elements[68].block, "f");
elements[68].atomicNumber = 69;
elements[68].atomicWeight = 168.93;
elements[68].color = LANTHANIDE;
elements[68].x = baseX + (14 * boxSize);
elements[68].y = baseY + (7 * boxSize);

strcpy(elements[69].symbol, "Yb");
strcpy(elements[69].name, "Ytterbium");
strcpy(elements[69].electronConfig, "4f14 6s2");
strcpy(elements[69].block, "f");
elements[69].atomicNumber = 70;
elements[69].atomicWeight = 173.05;
elements[69].color = LANTHANIDE;
elements[69].x = baseX + (15 * boxSize);
elements[69].y = baseY + (7 * boxSize);

strcpy(elements[70].symbol, "Lu");
strcpy(elements[70].name, "Lutetium");
strcpy(elements[70].electronConfig, "4f14 5d1 6s2");
strcpy(elements[70].block, "f");
elements[70].atomicNumber = 71;
elements[70].atomicWeight = 174.97;
elements[70].color = LANTHANIDE;
elements[70].x = baseX + (16 * boxSize);
elements[70].y = baseY + (7 * boxSize);




    // [Initialize rest of elements similarly]
    
    // Draw title
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    outtextxy(baseX, 5, (char*)"Interactive Periodic Table of Elements");
    
    // Draw legend
    drawLegend();
    
    // Draw periodic table
    for(int i = 0; i < 118; i++) {
        drawElement(elements[i]);
    }
    
    // Main event loop
    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            
            for(int i = 0; i < 118; i++) {
                if(isClickInElement(mouseX, mouseY, elements[i])) {
                    showElementDetails(elements[i]);
                    // Redraw everything
                    cleardevice();
                    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
                    setcolor(WHITE);
                    outtextxy(baseX, 5, (char*)"Interactive Periodic Table of Elements");
                    drawLegend();
                    for(int j = 0; j < 118; j++) {
                        drawElement(elements[j]);
                    }
                    break;
                }
            }
        }
        delay(100);
    }
    
    closegraph();
    return 0;
}
