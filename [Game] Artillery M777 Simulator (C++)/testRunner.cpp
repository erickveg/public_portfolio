
#include "testGround.h"
#include "testPosition.h"
#include "testProjectile.h"
#include "testVelocity.h"

void testRunner()
{
   TestGround().run();
   TestPosition().run();
   TestProjectile().run();
   TestVelocity().run();
}

//int main()
//{
//   testRunner();
//
//   return 0;
//}