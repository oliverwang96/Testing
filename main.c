/* 
 * File:   main.c
 * Author: Chris Hajduk
 *
 * Created on August 21, 2014, 11:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GPS.h"
#include "main.h"
#include "HunterTruckAPI.h"
#include "debug.h"

#include "OutputCompare.h"
#include "InterchipDMA.h"
#include "PWM.h"

_FOSCSEL(FNOSC_FRC); // Internal FRC oscillator
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
_FWDT(FWDTEN_OFF & WDTPOST_PS2048 & WDTPRE_PR128); //32,128
/*
 * 
 */


void delay(int delayTime)
{
    int startTime = getMin()*60 + getSec();

    do
    {
        background();
        //setDebugFloat((float)startTime);
        //setDebugInt((int)(getMin()*60 + getSec()));
    }while( ((int)(getMin()*60 + getSec()) - delayTime) <= startTime);

}

long double findDis(long double lat1, long double lon1, long double lat2, long double lon2)
{
    long double theta1 = lat1 * (PI/180);
    long double theta2 = lat2 * (PI/180);
    long double deltaT = (lat2-lat1) * (PI/180);
    long double deltaG = (lon2 - lon1) * (PI/180);

    long double a = sin(deltaT/2) * sin(deltaT/2) +
                    cos(theta1) * cos(theta2) * sin(deltaG/2) * sin(deltaG/2);
    long double c = fabsl(2 * asin(sqrt(a)) * -1000);

    setDebugFloat(6371*c);
    return 6371 * c;
}
int main(int argc, char** argv) {

    initTruck();

        //START TYPING YOUR CODE HERE

    //PHASE 1 CODE
//            delay(2);
//
//            setThrottle(20);
//            delay(10);
//
//            setThrottle(0);
//            delay(2);
//
//            setThrottle(-20);
//            delay(10);
//
//            setThrottle(0);
//            setSteering(50);
//            delay(2);
//
//            setThrottle(20);
//            delay(10);
//
//            setThrottle(0);
//            setSteering(-50);
//            delay(2);
//
//            setThrottle(20);
//            delay(10);
//
//            setThrottle(0);


    //PHASE 2

//    setSteering(0);
//    delay(10);
//
//        long double startLat = GPS.latitude;
//        long double startLon = GPS.longitude;
//
//
//        setThrottle(30);
//
//        while(findDis(startLat,startLon,GPS.latitude,GPS.longitude) <=10)
//        {
//            background();
//        }
//
//
//       setThrottle(0);
//       delay(2);
//
//       startLat = GPS.latitude;
//       startLon = GPS.longitude;
//
//       setThrottle(-30);
//       while(findDis(startLat,startLon,GPS.latitude,GPS.longitude) <=10)
//       {
//           background();
//       }

    //PHASE 3
    setSteering(0);
    delay(5);

        setThrottle(30);
        delay(1);

        long double startLat = GPS.latitude;
        long double startLon = GPS.longitude;

        int heading = GPS.heading;

        while(findDis(startLat,startLon,GPS.latitude,GPS.longitude) <=20)
        {
            if(abs(GPS.heading - heading) < 2) setSteering(0);
            else if(GPS.heading < heading) setSteering(-30);
            else if (GPS.heading > heading) setSteering(30);
            background();
        }


        int rightHeading = GPS.heading + 90;
        if(rightHeading > 180) rightHeading -= 360;

        setSteering(-50);
        while(GPS.heading < rightHeading - 5 || GPS.heading > rightHeading + 5)
        {
            background();
        }
        setSteering(0);
        delay(3);

        int leftHeading = GPS.heading - 90;
        if(leftHeading < -180) leftHeading += 360;

        setSteering(50);
        while(GPS.heading < leftHeading - 5 || GPS.heading > leftHeading + 5)
        {
            background();
        }
        setSteering(0);

        delay(3);

        //PHASE 4
        long double startLat = GPS.latitude;
        long double startLon = GPS.longitude;

        int heading = 40;

        setThrottle(30);

        while(findDis(startLat,startLon,GPS.latitude,GPS.longitude) <=100)
        {
         if(abs(GPS.heading - heading) < 2) setSteering(0);
         else if(GPS.heading < heading) setSteering(-50);
         else if (GPS.heading > heading) setSteering(50);
        }
        
        setThrottle(0);

        // Phase 6
        // Step 1
        long double startLat = GPS.latitude;
        long double startLon = GPS.longitude;

        long double home_latitude = startLat;
        long double home_longitude = startLon;

        int heading = GPS.heading;
        long double target_latitude = startLat + 0.0001;
        long double target_longitude = startLon;

        setThrottle(30);

        while(findDis(target_latitude, target_longitude,GPS.latitude,GPS.longitude) <= 0.5)
        {
         if(abs(GPS.heading - heading) < 2) setSteering(0);
         else if(GPS.heading < heading) setSteering(-50);
         else if (GPS.heading > heading) setSteering(50);
        }

        setThrottle(0);

        // Step 2
        long double startLat = GPS.latitude;
        long double startLon = GPS.longitude;

        int heading = GPS.heading;
        long double target_latitude = startLat;
        long double target_longitude = startLon + 0.0001;

        setThrottle(30);

        while(findDis(target_latitude, target_longitude,GPS.latitude,GPS.longitude) <= 0.5)
        {
         if(abs(GPS.heading - heading) < 2) setSteering(0);
         else if(GPS.heading < heading) setSteering(-50);
         else if (GPS.heading > heading) setSteering(50);
        }

        setThrottle(0);

        // Step 3
        long double startLat = GPS.latitude;
        long double startLon = GPS.longitude;

        int heading = GPS.heading;
        long double target_latitude = startLat - 0.0001;
        long double target_longitude = startLon;

        setThrottle(30);

        while(findDis(target_latitude, target_longitude,GPS.latitude,GPS.longitude) <= 0.5)
        {
         if(abs(GPS.heading - heading) < 2) setSteering(0);
         else if(GPS.heading < heading) setSteering(-50);
         else if (GPS.heading > heading) setSteering(50);
        }

        setThrottle(0);

        // Step 4
        long double startLat = GPS.latitude;
        long double startLon = GPS.longitude;

        int heading = GPS.heading;
        //long double target_latitude = startLat;
        //long double target_longitude = startLon  - 0.0001;

        setThrottle(30);

        while(findDis(home_latitude, home_longitude,GPS.latitude,GPS.longitude) <= 0.5)
        {
         if(abs(GPS.heading - heading) < 2) setSteering(0);
         else if(GPS.heading < heading) setSteering(-50);
         else if (GPS.heading > heading) setSteering(50);
        }

        setThrottle(0);

        // Phase 7
        // 7-1
        long double startLat = GPS.latitude;
        long double startLon = GPS.longitude;

        int heading = GPS.heading;
        long double target_latitude = 0;
        long double target_longitude = 0; // 0 will be replaced with actual waypoint at competition

        setThrottle(30);

        while(findDis(target_latitude, target_longitude,GPS.latitude,GPS.longitude) <= 0.5)
        {
         if(abs(GPS.heading - heading) < 2) setSteering(0);
         else if(GPS.heading < heading) setSteering(-50);
         else if (GPS.heading > heading) setSteering(50);
        }

        setThrottle(0);

        // Phase 8



//        This is an example of how you can print the GPS time to the debugging interface.
//        char str[16];
//        sprintf((char *)&str, "GPS: %f", GPS.time);
//        debug((char *)&str);
        
        background();

    
    return (EXIT_SUCCESS);
}
