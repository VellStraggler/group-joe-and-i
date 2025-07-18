/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    David Wells
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/


#pragma once

#include "howitzer.h"
#include "unitTest.h"

 /*******************************
  * TEST HOWITZER
  * A friend class for Howitzer which contains the Howitzer unit tests
  ********************************/
class TestHowitzer : public UnitTest
{
public:
   void run()
   {
      // Ticket 1: Getters
      defaultConstructor();
      getPosition_zero();
      getPosition_middle();
      getMuzzleVelocity_slow();
      getMuzzleVelocity_standard();
      getElevation_up();
      getElevation_right();
      getElevation_left();

      // Ticket 2: Setters
      generatePosition_small();
      generatePosition_large();
      raise_rightDown();
      raise_rightUp();
      raise_leftDown();
      raise_leftUp();
      rotate_clock();
      rotate_counterClock();
      rotate_wrapClock();
      rotate_wrapCounterClock();

      report("Howitzer");
   }

private:
   double metersFromPixels = -1.0;

   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    DEFAULT CONSTRUCTOR
     * input:   nothing
     * output:  zeros (except angle is at 45 degrees,
     *                 and the muzzle velocity is correct)
     *********************************************/
   void defaultConstructor()
   {
      Howitzer h = Howitzer();
      assertEquals(0, h.getPosition().getMetersX());
      assertEquals(0, h.getPosition().getMetersY());
   }

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GET POSITION ZERO
     * input:   h.pos=(0,0)
     * output:  pos=(0,0)
     *********************************************/
   void getPosition_zero()
   {
      Howitzer h = Howitzer();
      assertEquals(0, h.getPosition().getMetersX());
      assertEquals(0, h.getPosition().getMetersY());
   }

   /*********************************************
    * name:    GET POSITION MIDDLE
     * input:   h.pos=(123.4, 567.8)
     * output:  pos=(123.4, 567.8)
    *********************************************/
   void getPosition_middle()
   {
      Howitzer h = Howitzer(123.4, 567.8);
      assertEquals(123.4, h.getPosition().getMetersX());
      assertEquals(567.8, h.getPosition().getMetersY());
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - SLOW SPEED
     * input:   h.muzzleVelocity=(24.68)
     * output:  m=24.68
    *********************************************/
   void getMuzzleVelocity_slow()
   {
      Howitzer h = Howitzer();
      h.muzzleVelocity = 24.68;
      assertEquals(24.68, h.getMuzzleVelocity());
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - STANDARD SPEED
     * input:   h.muzzleVelocity=(827.00)
     * output:  m=827
    *********************************************/
   void getMuzzleVelocity_standard()
   {
      Howitzer h = Howitzer();
      h.muzzleVelocity = 827.00;
      assertEquals(827.00, h.getMuzzleVelocity());
   }

   /*********************************************
    * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
    *********************************************/
   void getElevation_up()
   {
      Howitzer h = Howitzer();
      h.elevation = Angle(0);
      assertEquals(Angle(0).getDegrees(), h.getElevation().getDegrees());
   }

   /*********************************************
    * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
    *********************************************/
   void getElevation_right()
   {
      Howitzer h = Howitzer();
      h.elevation = Angle(0.4);
      assertEquals(.4, h.getElevation().getDegrees());
   }

   /*********************************************
    * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
    *********************************************/
   void getElevation_left()
   {
      Howitzer h = Howitzer();
      h.elevation = Angle(5.8);
      assertEquals(5.8, h.getElevation().getDegrees());
   }

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GENERATE POSITION small board
     * input:   (10px, 10px)
     * output:  1px <= x <= 9px
     *********************************************/
   void generatePosition_small()
   {
      Position board = Position(10, 10);
      Howitzer h = Howitzer();
      h.generatePosition(board);
      double x = h.getPosition().getMetersX();
      assertUnit(x >= 1 && x <= 9);
   }

   /*********************************************
   * name:    GENERATE POSITION large board
   * input:   (1000px, 1000px)
   * output:  100px <= x <= 900px
   *********************************************/
   void generatePosition_large()
   {
      Position board = Position(1000, 1000);
      Howitzer h = Howitzer();
      h.generatePosition(board);
      double x = h.getPosition().getMetersX();
      assertUnit(x >= 100 && x <= 900);
   }

   /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
   void raise_rightDown()
   {
      Howitzer h = Howitzer();
      Angle a = Angle();
      a.setRadians(0.5);
      h.elevation = a;
      h.raise(-.1);
      assertEquals(0.6, h.getElevation().getRadians());
   }

   /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_rightUp()
   {
      Howitzer h = Howitzer();
      Angle a = Angle();
      a.setRadians(0.5);
      h.elevation = a;
      h.raise(.1);
      assertEquals(0.4, h.getElevation().getRadians());
   }

   /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=-0.6radians
    *********************************************/
   void raise_leftDown()
   {
      Howitzer h = Howitzer();
      h.elevation.setRadians(-.5);
      h.raise(-.1);
      double ans = h.getElevation().getRadians() - (M_PI * 2);
      assertEquals(-0.6, ans);
   }

   /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=-0.4radians
    *********************************************/
   void raise_leftUp()
   {
      Howitzer h = Howitzer();
      h.elevation.setRadians(-.5);
      h.raise(.1);
      assertEquals(-0.4, h.getElevation().getRadians() - (2 * M_PI));
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
   void rotate_clock()
   {
      Howitzer h = Howitzer();
      Angle a = Angle();
      a.setRadians(1.23);
      h.elevation = a;
      h.rotate(.3);
      assertEquals(1.53, h.getElevation().getRadians());
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
   void rotate_counterClock()
   {
      Howitzer h = Howitzer();
      Angle a = Angle();
      a.setRadians(1.23);
      h.elevation = a;
      h.rotate(-.3);
      assertEquals(.93, h.getElevation().getRadians());
   }

   /*********************************************
    * name:    ROTATE CLOCKWISE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 (2pi + -0.1) rotate=.2
    * output:  h.elevation=.1
    *********************************************/
   void rotate_wrapClock()
   {
      Howitzer h = Howitzer();
      h.elevation.setRadians((2 * M_PI) - .1);
      h.rotate(.2);
      double ans = h.getElevation().getRadians();
      assertEquals(.1, ans);
   }

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
    * input:   h.elevation=0.1 rotate=-.2 - 4PI
    * output:  h.elevation=6.1 (2pi + -0.1)
    *********************************************/
   void rotate_wrapCounterClock()
   {
      Howitzer h = Howitzer();
      h.elevation.setRadians(0.1);
      h.rotate(-.2 - (4 * M_PI));
      assertEquals(((2 * M_PI) - .1), h.getElevation().getRadians());
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

    // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1100.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
};
