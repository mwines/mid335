//CMPS 335
//mid335.cpp
// Author :  Michael Wines
// 5/14/2015
//
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4
float range[108] ={16.35, 17.32,18.3,19.45,20.6,21.83,23.12,24.5,25.96,27.5,29.14,30.87,32.7,34.65,36.71,38.89,41.2,43.65,46.25,49,51.91,55,58.27,61.74,65.41,16.35,17.32,18.35,19.45,20.6,21.83,23.12,24.5,25.96,27.5,29.14,30.87,32.7,34.65,36.71,38.89,41.2,43.65,46.25,49,51.91,55,58.27,61.74,65.41,69.3,311.13,329.63,349.23,369.99,392,415.3,440,466.16,493.88,523.25,554.37,587.33,622.25,659.25,698.46,739.99,783.99,830.61,880,932.33,987.77,1046.5,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760,1864.66,1975.53,2093,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520,3729.31,3951.07,4186.01,4434.92,4698.63,4978.03,5274.04,5587.65,5919.91,6271.93,6644.88,7040,7458.62,7902.13};

typedef enum {
    C = 1,
    Cs,
    D,
    Ds,
    E,
    F,
    Fs,
    G,
    Gs,
    A,
    As,
    B,
    END = B,
    HALF_STEPS_PER_OCTAVE = B 
} note_t;

double freq(note_t note, int octave_delta);
double freqequ(note_t note, int octave_delta, float t) {
    float temp = freq(note, octave_delta)*t;
    return temp ;

}


int main(int argc, char *argv[])
{
    note_t note;
    int octave_delta;
    float tolerance;
    if (argc <= 3) {
	cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA>" << endl;
	return 0;
    }
    tolerance = atof(argv[3]);
    if(argc == 4) {
	cout <<"Your tolerance = " << tolerance << endl;
    }
    //
    note = (note_t)(toupper(argv[1][0]) - 64);
    switch(toupper(argv[1][0])) {
	case 'A': note = A; break;
	case 'B': note = B; break;
	case 'C': note = C; break;
	case 'D': note = D; break;
	case 'E': note = E; break;
	case 'F': note = F; break;
    }
    //You may call your unit test here...
    //if( note == 'Z' && octave_delta == 0) {
    //unit test
    cout << "note\t" << "octave\t"  << "value\t" << "diff" << endl;
    cout << "----\t" << "------\t"  << "-----\t" << "-----------" << endl;
    for(int i = 0; i < 8; i++) {
	for(int j = 1; j < 13; j++) {
	    double tol = freqequ((note_t)j, i, tolerance);
	    double value = freq((note_t) j, i);
	    double diff = (range[i*8 +j-1])-(freq((note_t)j,i));
	    cout << j << "\t" << i << "\t"  << value << "\t" << abs(value -value- diff);
	    if(value <= range[i*8+j-1]+ tol && value >= range[i*8+j-1]-tol) {			//It seems like the logic for finding the Range[]
		cout << "\t good" << endl;							//is incorrect and returns good for the first 12
	    }											//variables in the array
	    else
		cout <<"\t  bad" << endl;
	}
    }	
/*    	if (note > END) {
	cout << "Invalid note!" << endl;
	return 1;
	}
*/	octave_delta = atoi(argv[2]);
    cout << HALF_STEPS_PER_OCTAVE << endl;
    cout << freq(note, octave_delta) << endl;
    return 0;
}

//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
    double freq;
    double factor;
    double a;
    int n;
    int octave = octave_delta - F0_octave;

    a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
    n = note - F0_note;
    freq = F0 * pow(a, (double)n);
    factor = pow(2.0, (double)octave);
    freq = freq * factor;
    return freq;
}


