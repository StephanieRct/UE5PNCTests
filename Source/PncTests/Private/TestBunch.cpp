// Fill out your copyright notice in the Description page of Project Settings.


#include "common.h"
#include "TestFixture.h"

using PNC::Size_t;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_ChunkPointer, "Pnc.4-Bunch.0-ChunkPointer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_ChunkPointer::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    PNC::Bunch chunk = PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUCKETPOINTER_STRUCTDATA(chunk, kSize_NodeCount, kSize_NodeCapacity);

    PNC::ChunkPointer& chunkPointer = chunk;
    TEST_VALID_CHUNKPOINTER_STRUCTDATA(chunkPointer, kSize_NodeCount);

    PNC::BucketPointer& bucketPointer = chunk;
    TEST_VALID_BUCKETPOINTER_STRUCTDATA(bucketPointer, kSize_NodeCount, kSize_NodeCapacity);

    PNC::BunchPointer& bunchPointer = chunk;
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(bunchPointer, kSize_NodeCount, kSize_NodeCapacity);

    const Size_t index = bunchPointer.AddNode();
    UTEST_EQUAL(TEXT("Added Node Index"), index, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA(chunkPointer, kSize_NodeCount + 1);
    TEST_VALID_BUCKETPOINTER_STRUCTDATA(bucketPointer, kSize_NodeCount + 1, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(bunchPointer, kSize_NodeCount + 1, kSize_NodeCapacity);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_Construct_StructData, "Pnc.4-Bunch.0-Construct-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_Construct_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_MoveConstruction, "Pnc.4-Bunch.1-MoveConstruction", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_MoveConstruction::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);
    
    ResetCallCounter();
    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bunch(std::move(*chunkFrom));
    
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_MoveAssignment_Self, "Pnc.4-Bunch.2-MoveAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_MoveAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = std::move(*chunkFromAndTo);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    delete chunkFromAndTo;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_MoveAssignment_VoidNull_StructData, "Pnc.4-Bunch.2-MoveAssignment-VoidNull-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_MoveAssignment_VoidNull_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new PNC::Bunch();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

    ResetCallCounter();
    auto allocationCountBefore = pnc_allocation_count;
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_MoveAssignment_StructData_VoidNull, "Pnc.4-Bunch.2-MoveAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_MoveAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new PNC::Bunch();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);

    ResetCallCounter();
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_MoveAssignment_StructData_StructData_SameStruct, "Pnc.4-Bunch.2-MoveAssignment-StructData-StructData-SameStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_MoveAssignment_StructData_StructData_SameStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacityLow, kSize_NodeCountLow);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCountLow, kSize_NodeCapacityLow);

    ResetCallCounter();
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_MoveAssignment_StructData_StructData_DiffStruct, "Pnc.4-Bunch.2-MoveAssignment-StructData-StructData-DiffStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_MoveAssignment_StructData_StructData_DiffStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bunch(&fix.Data->StructureBW, kSize_NodeCapacityLow, kSize_NodeCountLow);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCountLow, kSize_NodeCapacityLow);

    ResetCallCounter();
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

// TODO Chunk.MoveAssignment-VoidNull-VoidData
// 
// TODO Chunk.ConstructChunkPointer-StructData (construct a Chunk copy of a ChunkPointer)
// TODO Chunk.ConstructChunkPointer-VoidNull
// TODO Chunk.ConstructChunkPointer-StructNull
// TODO Chunk.ConstructChunkPointer-VoidData Fails
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_CopyConstruction_VoidNull, "Pnc.4-Bunch.3-CopyConstruction-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_CopyConstruction_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bunch();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    ResetCallCounter();
    auto* chunkTo = new PNC::Bunch(*chunkFrom);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_CopyConstruction_StructData, "Pnc.4-Bunch.3-CopyConstruction-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_CopyConstruction_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    ResetCallCounter();
    auto* chunkTo = new PNC::Bunch(*chunkFrom);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);

    TEST_COMPONENT_VALUE("Copy Construction TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

// Copy to chunk with enough space
// Copy to chunk without enough space

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_CopyAssignment_Self, "Pnc.4-Bunch.4-CopyAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_CopyAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = *chunkFromAndTo;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    delete chunkFromAndTo;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_CopyAssignment_VoidNull_StructData, "Pnc.4-Bunch.4-CopyAssignment-VoidNull-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_CopyAssignment_VoidNull_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new PNC::Bunch();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));

    TEST_COMPONENT_VALUE("Copy Assignment TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_CopyAssignment_StructData_VoidNull, "Pnc.4-Bunch.4-CopyAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_CopyAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bunch();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_CopyAssignment_StructData_StructData_SameStruct, "Pnc.4-Bunch.4-CopyAssignment-StructData-StructData-SameStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_CopyAssignment_StructData_StructData_SameStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacityLow, kSize_NodeCountLow);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCountLow, kSize_NodeCapacityLow);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_GREATER(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_CopyAssignment_StructData_StructData_DiffStruct, "Pnc.4-Bunch.4-CopyAssignment-StructData-StructData-DiffStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_CopyAssignment_StructData_StructData_DiffStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bunch(&fix.Data->StructureBW, kSize_NodeCapacityLow, kSize_NodeCountLow);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCountLow, kSize_NodeCapacityLow);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_GREATER(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_AddNode, "Pnc.4-Bunch.5-AddNode", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_AddNode::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, 0, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    PNC::Size_t index = chunk->AddNodes(kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Added Node Index"), index, 0);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_AddNode_GrowEmpty, "Pnc.4-Bunch.5-AddNode-GrowEmpty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_AddNode_GrowEmpty::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    ResetCallCounter();
    auto*const chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacityLow, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, 0, kSize_NodeCapacityLow);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), kSize_NodeCapacityLow);

    ResetCallCounter();
    const PNC::Size_t index = chunk->AddNodes(kSize_NodeCapacity);
    const PNC::Size_t expectedCapacity = std::max(kSize_NodeCapacityLow * 2, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Added Node Index"), index, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, expectedCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    delete chunk;
    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_AddNode_GrowFull, "Pnc.4-Bunch.5-AddNode-GrowFull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_AddNode_GrowFull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    ResetCallCounter();
    auto*const chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacityLow, kSize_NodeCapacityLow);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacityLow, kSize_NodeCapacityLow);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);

    ResetCallCounter();
    const PNC::Size_t index = chunk->AddNodes(kSize_NodeCapacity);
    const PNC::Size_t expectedCapacity = std::max(kSize_NodeCapacityLow * 2, kSize_NodeCapacityLow + kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Added Node Index"), index, kSize_NodeCapacityLow);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacityLow + kSize_NodeCapacity, expectedCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_NodeCapacityLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    delete chunk;
    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_RemoveNode_All, "Pnc.4-Bunch.6-RemoveNode-All", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_RemoveNode_All::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNode(0, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_0, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_RemoveNode_Midsection, "Pnc.4-Bunch.6-RemoveNode-Midsection", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_RemoveNode_Midsection::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>(); 
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA); 
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i; 

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNode(kSize_NodeCapacityMidStart, kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity - kSize_NodeCapacityMidCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityMidStart; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }
    // Nodes from the end should have moved to the removed nodes
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityMidCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[kSize_NodeCapacityMidStart + i].Value, kSize_NodeCapacity - kSize_NodeCapacityMidCount + i);
    }
    for (PNC::Size_t i = kSize_NodeCapacityMidStart + kSize_NodeCapacityMidCount; i < kSize_NodeCapacity - kSize_NodeCapacityMidCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity - kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_RemoveNode_End, "Pnc.4-Bunch.6-RemoveNode-End", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_RemoveNode_End::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>(); 
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA); 
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i; 

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNode(kSize_NodeCapacityBeginStart, kSize_NodeCapacityBeginCount);
    const PNC::Size_t newNodeCount = kSize_NodeCapacity - kSize_NodeCapacityBeginCount;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, newNodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityBeginCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_NodeCapacityBeginCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityBeginCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, kSize_NodeCapacity - kSize_NodeCapacityBeginCount + i);
    }
    for (PNC::Size_t i = kSize_NodeCapacityBeginStart + kSize_NodeCapacityBeginCount; i < kSize_NodeCapacity - kSize_NodeCapacityBeginCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }


    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity - kSize_NodeCapacityBeginCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_RemoveNodeKeepOrder_Midsection, "Pnc.4-Bunch.6-RemoveNodeKeepOrder-Midsection", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_RemoveNodeKeepOrder_Midsection::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>();
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA);
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i;

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNodeKeepOrder(kSize_NodeCapacityMidStart, kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity - kSize_NodeCapacityMidCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_NodeCapacity - (kSize_NodeCapacityMidStart + kSize_NodeCapacityMidCount));
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    
    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityMidStart; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }
    for (PNC::Size_t i = kSize_NodeCapacityMidStart; i < kSize_NodeCapacity - kSize_NodeCapacityMidCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i + kSize_NodeCapacityMidCount);
    }

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity - kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_RemoveNodeKeepOrder_End, "Pnc.4-Bunch.6-RemoveNodeKeepOrder-End", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_RemoveNodeKeepOrder_End::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>(); 
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA); 
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i; 

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNodeKeepOrder(kSize_NodeCapacityEndStart, kSize_NodeCapacityEndCount);
    const PNC::Size_t newNodeCount = kSize_NodeCapacity - kSize_NodeCapacityEndCount;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, newNodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityEndCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < newNodeCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity - kSize_NodeCapacityEndCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bunch_Clear, "Pnc.4-Bunch.7-Clear", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bunch_Clear::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bunch(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->Clear();
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_BUNCHPOINTER_STRUCTDATA(*chunk, 0, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}
