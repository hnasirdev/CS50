// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
   // for(int i=0; i<strlen(fraction); i++){

        if (fraction[0]=='1' && fraction[2]=='8'){
            return 1;
        }
        else if(fraction[0]=='1' && fraction[2]=='4'){
            return 2;
        }
        else if(fraction[0]=='3' && fraction[2]=='8'){
            return 3;
        }
        else if(fraction[0]=='1' && fraction[2]=='2'){
            return 4;
        }

            return 0;



   // }
    //if 1/8 return 1
    //if 1/4 return 2
    //if 1/2 returns 4
    //if 3/8 return 3;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO

    //Define main frequencies
    double a4=440;
    double a4sharp = pow(2.0, 0.0833)*a4;
    double a4b = a4/pow(2.0, 0.0833);
    double b4 = pow(2.0,0.1666)*a4;
    double c4 = pow(2.0,0.25)*(a4/2); //a4/2 is a3
    double d4 = pow(2.0,0.41666)*(a4/2);
    double e4 = pow(2.0,0.5833)*(a4/2);
    double f4 = pow(2.0,0.6666)*(a4/2);
    double g4 = pow(2.0,0.8333)*(a4/2);
    double freq;



    if(note[0]=='A'){
        if(note[1]=='#'){
            if(note[2]=='1'){

                freq = round(a4sharp/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq = round(a4sharp/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq = round(a4sharp/2);
                return (int)freq;
            }
            if(note[2]=='4'){
                freq = round(a4sharp);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq = round(a4sharp*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq = round(a4sharp*4);
                return (int)freq;
            }
        }
        else if(note[1]=='b'){
            if(note[2]=='1'){
                //freq = round((pow(2.0,0.0833)*a4freq)/8);
                freq = round(a4b/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq = round(a4b/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq = round(a4b/2);
                return (int)freq;
            }
             if(note[2]=='4'){
                freq = round(a4b);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq = round(a4b*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq = round(a4b*4);
                return (int)freq;
            }
        }
        else if(note[1]=='1'){
            freq = round(a4/8);
            return (int)freq;
        }
        else if(note[1]=='2'){
            freq = round(a4/4);
            return (int)freq;
        }
        else if(note[1]=='3'){
            freq = round(a4/2);
            return (int)freq;
        }
        else if(note[1]=='4'){
            return a4;
        }
        else if(note[1]=='5'){
            freq = round(a4*2);
            return (int)freq;
        }
        else if(note[1]=='6'){
            freq = round(a4*4);
            return (int)freq;
        }

    }



    else if (note[0]=='B'){
        if(note[1]=='#'){
            if(note[2]=='1'){
                //b#1 so find b#4 and / 8
                freq = round((pow(2.0,0.25)*a4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq = round((pow(2.0,0.25)*a4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq = round((pow(2.0,0.25)*a4)/2);
                return (int)freq;
            }
            if(note[2]=='4'){
                freq = round((pow(2.0,0.25)*a4));
                return (int)freq;
            }
            if(note[2]=='5'){
                freq = round((pow(2.0,0.25)*a4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq = round((pow(2.0,0.25)*a4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='b'){
            if(note[2]=='1'){
                //a#4 = Bb4
                freq = round(a4sharp/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq = round(a4sharp/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq = round(a4sharp/2);
                return (int)freq;
            }
             if(note[2]=='4'){
                freq = a4sharp;
                return (int)freq;
            }
            if(note[2]=='5'){
                freq = round(a4sharp*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq = round(a4sharp*4);
                return (int)freq;
            }
        }
        else if(note[1]=='1'){
            freq = round((pow(2.0,0.1666)*a4)/8);
            return (int)freq;
        }
        else if(note[1]=='2'){
            freq = round((pow(2.0,0.1666)*a4)/4);
            return (int)freq;
        }
        else if(note[1]=='3'){
            freq = round((pow(2.0,0.1666)*a4)/2);
            return (int)freq;
        }
        else if(note[1]=='4'){
            freq = round((pow(2.0,0.1666)*a4));
            return (int)freq;

        }
        else if(note[1]=='5'){
            freq = round((pow(2.0,0.1666)*a4)*2);
            return (int)freq;
        }
        else if(note[1]=='6'){
            freq = round((pow(2.0,0.1666)*a4)/4);
            return (int)freq;
        }

    }
    else if (note[0]=='C'){
        if(note[1]=='#'){
            if(note[2]=='1'){
                //c#1 so find c#4 and / 8
                freq=round((pow(2.0,0.0833)*c4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*c4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*c4)/2);
                return (int)freq;
            }
            if(note[2]=='4'){
                //C#4
                freq=round(pow(2.0,0.0833)*c4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*c4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*c4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='b'){
            if(note[2]=='1'){

                freq=round(b4/16);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round(b4/8);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round(b4/4);
                return (int)freq;
            }
             if(note[2]=='4'){
                //Cb4 = b3
                freq=round(b4/2);
                return (int)freq;
            }
            if(note[2]=='5'){
                //cb5=b4
                freq=round(b4);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round(b4*2);
                return (int)freq;
            }
        }
        else if(note[1]=='1'){
            //C1
            freq=round(c4/8);
            return (int)freq;
        }
        else if(note[1]=='2'){
            freq = round(c4/4);
            return (int)freq;
        }
        else if(note[1]=='3'){

            freq = round(c4/2);
            return (int)freq;
        }
        else if(note[1]=='4'){
            //c4
            freq = round(c4);
            return (int)freq;

        }
        else if(note[1]=='5'){
            freq = round(c4*2);
            return (int)freq;
        }
        else if(note[1]=='6'){
            freq= round(c4*4);
            return (int)freq;
        }


    }

    else if(note[0]=='D'){
        if(note[1]=='#'){
            if(note[2]=='1'){
                //D#1 so find D#4 and / 8
                freq=round((pow(2.0,0.0833)*d4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*d4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*d4)/2);
                return (int)freq;
            }
            if(note[2]=='4'){
                //D#4
                freq=round(pow(2.0,0.0833)*d4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*d4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*d4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='b'){
            if(note[2]=='1'){

                freq=round((pow(2.0,0.0833)*c4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*c4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*c4)/2);
                return (int)freq;
            }
             if(note[2]=='4'){
                //db4 = c#4
                freq=round(pow(2.0,0.0833)*c4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*c4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*c4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='1'){
            //C1
            freq=round(d4/8);
            return (int)freq;
        }
        else if(note[1]=='2'){
            freq = round(d4/4);
            return (int)freq;
        }
        else if(note[1]=='3'){

            freq = round(d4/2);
            return (int)freq;
        }
        else if(note[1]=='4'){
            //d4
            freq = round(d4);
            return (int)freq;

        }
        else if(note[1]=='5'){
            freq = round(d4*2);
            return (int)freq;
        }
        else if(note[1]=='6'){
            freq= round(d4*4);
            return (int)freq;
        }




    }

    else if(note[0]=='E'){
        if(note[1]=='#'){
            if(note[2]=='1'){
                //E#1 so find E#4 and / 8
                freq=round((pow(2.0,0.0833)*e4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*e4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*e4)/2);
                return (int)freq;
            }
            if(note[2]=='4'){
                //E#4
                freq=round(pow(2.0,0.0833)*e4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*e4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*e4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='b'){
            if(note[2]=='1'){

                freq=round((pow(2.0,0.0833)*d4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*d4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*d4)/2);
                return (int)freq;
            }
             if(note[2]=='4'){
                //Eb4 = D#4
                freq=round(pow(2.0,0.0833)*d4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*d4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*d4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='1'){
            //E1
            freq=round(e4/8);
            return (int)freq;
        }
        else if(note[1]=='2'){
            freq = round(e4/4);
            return (int)freq;
        }
        else if(note[1]=='3'){

            freq = round(e4/2);
            return (int)freq;
        }
        else if(note[1]=='4'){
            //e4
            freq = round(e4);
            return (int)freq;

        }
        else if(note[1]=='5'){
            freq = round(e4*2);
            return (int)freq;
        }
        else if(note[1]=='6'){
            freq= round(e4*4);
            return (int)freq;
        }




    }


    else if(note[0]=='F'){
        if(note[1]=='#'){
            if(note[2]=='1'){
                //E#1 so find E#4 and / 8
                freq=round((pow(2.0,0.0833)*f4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*f4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*f4)/2);
                return (int)freq;
            }
            if(note[2]=='4'){
                //F#4
                freq=round(pow(2.0,0.0833)*f4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*f4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*f4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='b'){
            if(note[2]=='1'){

                freq=round(e4/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round(e4/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round(e4/2);
                return (int)freq;
            }
             if(note[2]=='4'){
                //fb4 = e4
                freq=round(e4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round(e4*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round(e4*4);
                return (int)freq;
            }
        }
        else if(note[1]=='1'){
            //E1
            freq=round(f4/8);
            return (int)freq;
        }
        else if(note[1]=='2'){
            freq = round(f4/4);
            return (int)freq;
        }
        else if(note[1]=='3'){

            freq = round(f4/2);
            return (int)freq;
        }
        else if(note[1]=='4'){
            //f4
            freq = round(f4);
            return (int)freq;

        }
        else if(note[1]=='5'){
            freq = round(f4*2);
            return (int)freq;
        }
        else if(note[1]=='6'){
            freq= round(f4*4);
            return (int)freq;
        }

    }

    else if(note[0]=='G'){
        if(note[1]=='#'){
            if(note[2]=='1'){
                //E#1 so find E#4 and / 8
                freq=round((pow(2.0,0.0833)*g4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*g4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*g4)/2);
                return (int)freq;
            }
            if(note[2]=='4'){
                //G#4
                freq=round(pow(2.0,0.0833)*g4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*g4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*g4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='b'){
            if(note[2]=='1'){

                freq=round((pow(2.0,0.0833)*f4)/8);
                return (int)freq;
            }
            if(note[2]=='2'){
                freq=round((pow(2.0,0.0833)*f4)/4);
                return (int)freq;
            }
            if(note[2]=='3'){
                freq=round((pow(2.0,0.0833)*f4)/2);
                return (int)freq;
            }
             if(note[2]=='4'){
                //gb4 = f#4
                freq=round(pow(2.0,0.0833)*f4);
                return (int)freq;
            }
            if(note[2]=='5'){
                freq=round((pow(2.0,0.0833)*f4)*2);
                return (int)freq;
            }
            if(note[2]=='6'){
                freq=round((pow(2.0,0.0833)*f4)*4);
                return (int)freq;
            }
        }
        else if(note[1]=='1'){
            //E1
            freq=round(g4/8);
            return (int)freq;
        }
        else if(note[1]=='2'){
            freq = round(g4/4);
            return (int)freq;
        }
        else if(note[1]=='3'){

            freq = round(g4/2);
            return (int)freq;
        }
        else if(note[1]=='4'){
            //g4
            freq = round(g4);
            return (int)freq;

        }
        else if(note[1]=='5'){
            freq = round(g4*2);
            return (int)freq;
        }
        else if(note[1]=='6'){
            freq= round(g4*4);
            return (int)freq;
        }

    }

        return 0;






}

// Determines whether a string represents a rest
bool is_rest(string s)
{

    if(strncmp(s,"",2)==0){
        return true;
    }
    else
    {
        return false;
    }

    // TODO
}
