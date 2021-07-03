#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include "src/physics.h"

class FixtureTests : public CppUnit::TestFixture{
    public:

    void setUp() override
    {
        printf("Setup is called\n");
    }

    void tearDown() override
    {
        printf("tearDown is called\n");
    }

    //test set 1: tesing thing position and collision

    //test 1
    void testSetPosition()
    {
        Thing thing{5.0f, 10.0f, 1.0f};
        thing.setPosition(10, 15);
        thing.update();

        CPPUNIT_ASSERT(thing.getX() == 10.0f);
        CPPUNIT_ASSERT(thing.getY() == 15.0f);
    }


    //test 2
    void testThingMoves()
    {
        Thing thing{5.0f, 10.0f, 1.0f};
        thing.applyForce(1, 1);
        thing.update();

        CPPUNIT_ASSERT(thing.getX() == 6.0f);
        CPPUNIT_ASSERT(thing.getY() == 11.0f);
    }

    //test 3
    void testCollision()
    {
        Thing thing{5.0f, 10.0f, 1.0f};
        Thing otherThing{4.0f,9.0f, 1.0f};
        otherThing.applyForce(1,1);
        otherThing.update();

        CPPUNIT_ASSERT(thing.didCollide(otherThing));
    }

    //test set 2: creating world and adding things

    //test 1

        void testWorld()
    {
        World world{600.0f, 300.0f, 1};

        CPPUNIT_ASSERT(world.getWidth() == 600.0f);
        CPPUNIT_ASSERT(world.getHeight() == 300.0f);
    }

    //test 2
    void testAddThing()
    {
        World world{600.0f, 300.0f, 1};
        Thing thing1{11.0f, 15.0f, 1.0f};
        Thing thing2{10.0f, 15.0f, 1.0f};
        world.addThing(&thing1);
        world.addThing(&thing2);
        
        CPPUNIT_ASSERT(world.countThings() > 0);
    }

     //test 3
    void testRemoveFromWorld()
    {
        World world{600.0f, 300.0f, 1};
        Thing thing1{11.0f, 15.0f, 1.0f};
        world.addThing(&thing1);
        world.removeThing(&thing1);

        CPPUNIT_ASSERT(world.countThings() < 1);
    }

    //test set 3: testing world physics

    //test 1
    void testWorldCollision()
    {
        World world{600.0f, 300.0f, 1};
        Thing thing1{11.0f, 15.0f, 1.0f};
        Thing thing2{10.0f, 15.0f, 1.0f};
        world.addThing(&thing1);
        world.addThing(&thing2);

        CPPUNIT_ASSERT(world.didThingsCollide(&thing1,&thing2));
        CPPUNIT_ASSERT(thing1.getX() == 10.0f);
        CPPUNIT_ASSERT(thing1.getY() == 14.0f);
        CPPUNIT_ASSERT(thing2.getX() == 9.0f);
        CPPUNIT_ASSERT(thing1.getY() == 14.0f);            
    }

    //test 2
    void testWorldBounds()
    {
        World world{600.0f, 300.0f, 1};
        Thing thing1{1.0f, -1500.0f, 1.0f};
        world.addThing(&thing1);

        CPPUNIT_ASSERT(world.isThingOutOfBounds(&thing1));
        CPPUNIT_ASSERT(world.countThings() == 0);
    }
    
    //test 3
    void testGravity()
    {
        World world{600.0f, 300.0f, 1};
        Thing thing1{300.0f, 10.0f, 1.0f};
        world.applyGravity(2.0, &thing1);

        CPPUNIT_ASSERT_EQUAL(world.getHeight(), thing1.getY());
    }

};

int main()
{
    CppUnit::TextUi::TestRunner runner{};
    // test set 1
        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test set position",
        &FixtureTests::testSetPosition
    });

    runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test force",
        &FixtureTests::testThingMoves
    });

        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test collision",
        &FixtureTests::testCollision
    });
    // test set 2
        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test world params",
        &FixtureTests::testWorld
    });

        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test add thing to world",
        &FixtureTests::testAddThing
    });

        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test remove thing from world",
        &FixtureTests::testRemoveFromWorld
    });

    // test set 3
        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test collision of things inside world",
        &FixtureTests::testWorldCollision
    });

        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test world bounds",
        &FixtureTests::testWorldBounds
    });

        runner.addTest(new CppUnit::TestCaller<FixtureTests>{
        "test gravity",
        &FixtureTests::testGravity
    });





    runner.run();
  

    return 0;
}