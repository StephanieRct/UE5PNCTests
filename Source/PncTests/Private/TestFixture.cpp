
#include "TestFixture.h"

CallCounter CallCounter::Instance;

void ResetCallCounter()
{
    CallCounter::Instance.Reset();
}

void TestAssert()
{
    pnc_assert(false == true);
}
void TestAssertf(int a)
{
    pnc_assertf(false == true, TEXT("This is my assertf with argument of value '%d'"), a);
}
void TestAssertNoEntry()
{
    pnc_assert_no_entry_return();
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Fixture_Exceptions, "Pnc.0Fixture.Exceptions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Fixture_Exceptions::RunTest(const FString& Parameters)
{
    try
    {
        TestAssert();
        UTEST_TRUE(TEXT("pnc_assert must throw an execption"), false);
    }
    catch (const FString& msg)
    {
        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
    }
    catch(...)
    {
        UTEST_TRUE(TEXT("pnc_assert throws unknown execption, should be a FString"), false);
    }

    try
    {
        TestAssertf(5);
        UTEST_TRUE(TEXT("pnc_assertf must throw an execption"), false);
    }
    catch (const FString& msg)
    {
        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
    }
    catch (...)
    {
        UTEST_TRUE(TEXT("pnc_assertf throws unknown execption, should be a FString"), false);
    }

    try
    {
        TestAssertNoEntry();
        UTEST_TRUE(TEXT("pnc_assert_no_entry_return must throw an execption"), false);
    }
    catch (const FString& msg)
    {
        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
    }
    catch (...)
    {
        UTEST_TRUE(TEXT("pnc_assert_no_entry_return throws unknown execption, should be a FString"), false);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Fixture_Data, "Pnc.0Fixture.Data", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Fixture_Data::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    UTEST_EQUAL(TEXT("StructureA Component Type A index"), fix.Data->StructureA.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_EQUAL(TEXT("StructureB Component Type B index"), fix.Data->StructureB.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_EQUAL(TEXT("StructureV Component Type V index"), fix.Data->StructureV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    
    UTEST_GREATER_EQUAL(TEXT("StructureAB Component Type A index"), fix.Data->StructureAB.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAB Component Type B index"), fix.Data->StructureAB.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureVW Component Type V index"), fix.Data->StructureVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureVW Component Type W index"), fix.Data->StructureVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureAV Component Type A index"), fix.Data->StructureAV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAV Component Type V index"), fix.Data->StructureAV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureBV Component Type B index"), fix.Data->StructureBV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureBV Component Type V index"), fix.Data->StructureBV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureABV Component Type A index"), fix.Data->StructureABV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABV Component Type B index"), fix.Data->StructureABV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABV Component Type V index"), fix.Data->StructureABV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureAVW Component Type A index"), fix.Data->StructureAVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAVW Component Type V index"), fix.Data->StructureAVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAVW Component Type W index"), fix.Data->StructureAVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureBVW Component Type B index"), fix.Data->StructureBVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureBVW Component Type V index"), fix.Data->StructureBVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureBVW Component Type W index"), fix.Data->StructureBVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type A index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type B index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type V index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type W index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);
    
    FIXEND;
}
